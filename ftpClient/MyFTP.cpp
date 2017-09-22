#include "MyFTP.h"


FTP_API MyFTP::connect2Server(char * conIP, UINT  conPort)
{
	if (!sock.Connect(conIP, conPort))
		return -1;
	if(serverResponse().length()>0)
		printf("@@@@Response: %s", m_strResponse.c_str());
	return 0;
}

FTP_API MyFTP::Send2Server(const std::string str,Csocket &dataSock)
{
	memset(sendBuffer, '\0', MAX_BUF_LEN);
	strncpy(sendBuffer, str.c_str(), MAX_BUF_LEN);
	return dataSock.Send(sendBuffer,strlen(sendBuffer));
}

FTP_API MyFTP::login2Server(const std::string userID, const std::string userPass)
{
	int flag = -1;
	
	Send2Server(parseCommand(FTP_COMMAND_USERNAME, userID),this->sock);
	
	flag = parseResponse(serverResponse());
	printf("@@@@Response: %s", m_strResponse.c_str());
	if (flag != 331)
		return flag;
	
	Send2Server(parseCommand(FTP_COMMAND_PASSWORD, userPass), this->sock);
	
	flag = parseResponse(serverResponse());
	printf("@@@@Response: %s", m_strResponse.c_str());
	if (flag != 230)
		printf("Login Error!\n");
	return flag;

}

const std::string MyFTP::serverResponse()
{
	memset(recvBuffer,'\0', MAX_BUF_LEN);
	size_t size=sock.Receive(recvBuffer, MAX_BUF_LEN);
	m_strResponse = std::string(recvBuffer);
	return m_strResponse;
}

const std::string MyFTP::parseCommand(const unsigned int command, const std::string &strParam)
{
	if (command < FTP_COMMAND_BASE || command > FTP_COMMAND_END)
	{
		return "";
	}

	std::string strCommandLine;

	m_nCurrentCommand = command;
	m_commandStr.clear();

	switch (command)
	{
	case FTP_COMMAND_USERNAME:
		strCommandLine = "USER ";
		break;
	case FTP_COMMAND_PASSWORD:
		strCommandLine = "PASS ";
		break;
	case FTP_COMMAND_QUIT:
		strCommandLine = "QUIT ";
		break;
	case FTP_COMMAND_CURRENT_PATH:
		strCommandLine = "PWD ";
		break;
	case FTP_COMMAND_TYPE_MODE:
		strCommandLine = "TYPE ";
		break;
	case FTP_COMMAND_PSAV_MODE:
		strCommandLine = "PASV ";
		break;
	case FTP_COMMAND_DIR:
		strCommandLine = "LIST ";
		break;
	case FTP_COMMAND_CHANGE_DIRECTORY:
		strCommandLine = "CWD ";
		break;
	case FTP_COMMAND_DELETE_FILE:
		strCommandLine = "DELE ";
		break;
	case FTP_COMMAND_DELETE_DIRECTORY:
		strCommandLine = "RMD ";
		break;
	case FTP_COMMAND_CREATE_DIRECTORY:
		strCommandLine = "MKD ";
		break;
	case FTP_COMMAND_RENAME_BEGIN:
		strCommandLine = "RNFR ";
		break;
	case FTP_COMMAND_RENAME_END:
		strCommandLine = "RNTO ";
		break;
	case FTP_COMMAND_FILE_SIZE:
		strCommandLine = "SIZE ";
		break;
	case FTP_COMMAND_DOWNLOAD_FILE:
		strCommandLine = "RETR ";
		break;
	case FTP_COMMAND_DOWNLOAD_POS:
		strCommandLine = "REST ";
		break;
	default:
		break;
	}

	strCommandLine += strParam;
	strCommandLine += "\r\n";

	m_commandStr = strCommandLine;
	printf("parseCommand: %s\n", m_commandStr.c_str());

	return m_commandStr;
}

FILE * MyFTP::createLocalFile(const std::string localPath)
{
	const char* type = m_transMode == ascii ? "w": "wb";
	return fopen(localPath.c_str(), type);
}

const std::string MyFTP::Pasv()
{
	if (Send2Server(parseCommand(FTP_COMMAND_PSAV_MODE, ""), this->sock) < 0)
		return "";
	else
	{ 
		 printf("@@@@Response: %s\n", serverResponse().c_str());
		 ParseString();
		 return m_strResponse;
	}
		
}

FTP_API MyFTP::ParseString()
{
	//PASV ·µ»ØÖµ "227 Entering Passive Mode (114,215,19,63,237,34).\r\n"
	
	size_t nBegin = m_strResponse.find_first_of("(");
	size_t nEnd = m_strResponse.find_first_of(")");
	std::string strData = m_strResponse.substr(nBegin + 1, nEnd - nBegin - 1);
	char *str = const_cast<char*>(strData.c_str());
	char *temp = strtok(str, ",");  
	int i = 1;
	while (temp) 
	{
		switch (i) 
		{
		case 1:
		{
			m_strServerIP = std::string(temp);  
			break;
		}
		case 2:
		{
			m_strServerIP += '.';
			m_strServerIP += temp;
			break;
		}
		case 3:
		{
			m_strServerIP += '.';
			m_strServerIP += temp;
			break;
		}
		case 4:
			m_strServerIP += '.';
			m_strServerIP += temp;
			break;
		case 5:
			m_nServerPort = atoi(temp)*256;
			break;
		case 6:
			m_nServerPort += atoi(temp);
		default:
			break;
		}
		i++;
		temp = strtok(NULL, ",");
	}
	return 0;
}

bool MyFTP::createDataLink(Csocket & dataSocket)
{
	Pasv();
	dataSocket.CreatSocket();
	if (!dataSocket.Connect(m_strServerIP.c_str(), m_nServerPort))
	{
		printf("data Socket Error : %d \n", GetLastError());
		return false;
	}
	return true;
}

FTP_API MyFTP::setTransferMode(TransType mode)
{
	m_transMode = mode;
	switch (mode)
	{
	case binary:
		m_commandStr = parseCommand(FTP_COMMAND_TYPE_MODE, "I");
		break;
	case ascii:
		m_commandStr = parseCommand(FTP_COMMAND_TYPE_MODE, "A");
		break;
	default:
		break;
	}

	if (Send2Server(m_commandStr, this->sock) < 0)
	{
		return -1;
	}
	else
	{
		printf("@@@@Response: %s", serverResponse().c_str());
		return parseResponse(m_strResponse);
	}
}

FTP_API MyFTP::parseResponse(const std::string & str)
{
	if (str.empty())
	{
		printf("str is empty !\n");
		return -1;
	}
	std::string strData = str.substr(0, 3);
	unsigned int val = atoi(strData.c_str());

	return val;
	
}

long MyFTP::getFileLength(const std::string &strRemoteFile,Csocket&  dataSocket)
{
	if (Send2Server(parseCommand(FTP_COMMAND_FILE_SIZE, strRemoteFile),dataSocket) < 0)
	{
		return -1;
	}
	serverResponse();
	printf("@@@@Response: %s\n", m_strResponse.c_str());

	std::string strData = m_strResponse.substr(0, 3);
	unsigned long val = atol(strData.c_str());

	if (val == 213)
	{
		strData = m_strResponse.substr(4);
		printf("strData: %s\n", strData.c_str());
		val = atol(strData.c_str());
		return val;
	}
	return -1;
}

size_t MyFTP::getData(Csocket&  dataSocket)
{
	memset(recvBuffer, '\0', MAX_BUF_LEN);
	return dataSocket.Receive(recvBuffer, MAX_BUF_LEN);
}

FTP_API MyFTP::downLoadFile(const std::string & strRemoteFile, const std::string & strLocalFile,  const int pos, const unsigned int length)
{
	Csocket  dataSocket;

	if (!createDataLink(dataSocket))
	{
		printf("Create Data Link \n");
		return -1;
	}

	FILE *file = NULL;
	unsigned long nDataLen = FTP_DEFAULT_BUFFER;
	char strPos[MAX_PATH] = { 0 };
	
	if ((length != 0) && (length < nDataLen))
	{
		nDataLen = length;
	}
	char *dataBuf = new char[nDataLen];
	
	sprintf(strPos, "%d", pos);

	
	if (Send2Server(parseCommand(FTP_COMMAND_DOWNLOAD_POS, strPos),this->sock) < 0)
	{
		return -1;
	}
	
	printf("@@@@Response: %s\n", serverResponse().c_str());

	if (Send2Server(parseCommand(FTP_COMMAND_DOWNLOAD_FILE, strRemoteFile), this->sock) < 0)
	{
		return -1;
	}
	
	printf("@@@@Response: %s\n", serverResponse().c_str());

	file = createLocalFile(std::string(  strLocalFile));
	if (file == NULL)
	{
		printf("CreateLocalFile Error !\n");
		return -1;
	}

	int len = 0;
	int nReceiveLen = 0;
	while ((len = getData(dataSocket)) > 0)
	{
		nReceiveLen += len;
		int num = fwrite(recvBuffer, 1, len, file);  
		printf("fwrite num : %d \n", num);
		if (nReceiveLen == length && length != 0)
			break;
		if ((nReceiveLen + nDataLen) > length  && length != 0)
		{
			delete[]dataBuf;
			nDataLen = length - nReceiveLen;
			dataBuf = new char[nDataLen];
		}
	}
	fclose(file);
	return 0;
}

const std::string MyFTP::Dir(const std::string &path)
{
	Csocket dataSocket;

	if (!createDataLink(dataSocket))
	{
		printf("Create Data Link \n");
		return "";
	}
	if (Send2Server(parseCommand(FTP_COMMAND_DIR, path), this->sock) < 0)
	{
		
		dataSocket.CloseSocket();
		return "";
	}
	else
	{
		memset(recvBuffer, '\0', MAX_BUF_LEN);
		while(dataSocket.Receive(recvBuffer, MAX_BUF_LEN)>0)
		{
			printf("@@@@Response: \n%s\n", recvBuffer);
			memset(recvBuffer, '\0', MAX_BUF_LEN);
		}
		
		
		dataSocket.CloseSocket();
		return m_strResponse;
	}

}

FTP_API MyFTP::CD(const std::string &path)
{
	Csocket dataSocket;

	if (createDataLink(dataSocket) < 0)
	{
		return -1;
	}
	if (Send2Server(parseCommand(FTP_COMMAND_CHANGE_DIRECTORY, path),dataSocket) < 0)
	{
		return -1;
	}
	printf("@@@@Response: %s\n", serverResponse().c_str());
	return parseResponse(m_strResponse);
}