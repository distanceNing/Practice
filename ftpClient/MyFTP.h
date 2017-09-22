#pragma once
#include "Csocket.h"
#include "define.h"
#include <string>
#include <list>
#define MAX_BUF_LEN 4096

//return 0 = OK
class MyFTP
{
public:
	enum TransType
	{
		binary=1,
		ascii
	};

	MyFTP() {
		sock.CreatSocket();
	}

	FTP_API connect2Server(char* conIP, UINT conPort= FTP_DEFAULT_PORT);
		
	FTP_API MyFTP::Send2Server(const std::string str, Csocket &dataSock);

	FTP_API login2Server(const std::string useID,const std::string userPass);

	const std::string  serverResponse();

	const std::string Pasv();
	
	const std::string Dir(const std::string &path);

	FTP_API CD(const std::string &path);

	FTP_API MyFTP::setTransferMode(TransType mode);

	long MyFTP::getFileLength(const std::string &strRemoteFile, Csocket&  dataSocket);

	size_t getData(Csocket&  dataSocket);

	FTP_API downLoadFile(const std::string &strRemoteFile, const std::string &strLocalFile, const int pos = 0, const unsigned int length = 0);

	FTP_API quitServer(void);


	~MyFTP() {
		sock.CloseSocket();
	}
private:
	FTP_API parseResponse(const std::string &str);

	const std::string MyFTP::parseCommand(const unsigned int command, const std::string &strParam);
	
	FILE* createLocalFile(const std::string localPath);

	FTP_API MyFTP::ParseString();

	bool createDataLink(Csocket &dataSocket);

	char sendBuffer[MAX_BUF_LEN];
	
	char recvBuffer[MAX_BUF_LEN];
	
	TransType m_transMode;

	Csocket sock;
	
	
	// !服务器的IP  
	std::string m_strServerIP;

	// !服务器Port  
	unsigned int m_nServerPort;

	// !服务器回应信息缓存  
	std::string m_strResponse;

	// !保存命令参数  
	std::string m_commandStr;

	// ！当前使用的命令参数  
	unsigned int m_nCurrentCommand;

	std::string strCommandLine;
	
};

