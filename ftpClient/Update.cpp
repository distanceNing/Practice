
#include "MyFTP.h"
#define FTP_AUTH		"li19950717"
 /*  ��cloudmonitor ���ߺ�����������˵Ŀͻ��˰汾�ϸ� Ҫ����cloudmonitor���� ��ֱ�ӿ���һ������
  *  ��MyCreateProcess("Update.exe", NULL);
  */
int main(int argc, char *argv[])
{
	char serverIP[]="114.215.19.63";
	MyFTP ftpClient;
	if (ftpClient.connect2Server(serverIP) == -1)
		return -1;
	ftpClient.login2Server("Quanjiang",FTP_AUTH);
	std::string file("/var/ftp/CloudMonitor/v1.22/autoStart.exe");
	ftpClient.downLoadFile(file, std::string("data.exe"));
	//ftpClient.Dir("/var/");




	/*USER class �м�һ��CloudVersion�ĳ�Ա���� �����Ը��¹���
	CloudVersion ver;
	
	
	// ��ȡ��ǰ����İ汾��
	cout << "Current Version: " << ver.GetCurVersion() << endl;

	if (2 == argc && 0 == strncmp(UPDATE_ARGS, argv[1], sizeof(UPDATE_ARGS)))
	{
		EnableLog();
	}

	// ��ȡ����˱�������°汾��
	if (!ver.GetLatestVersion())
	{
		WriteToLog("GetLatestVersion() FAILED");
		printf("GetLatestVersion() FAILED\n");
		return 1;
	}
	WriteToLog("GetLatestVersion Ok");


	if (!ver.WhetherUpdate())
	{
		printf("Already Latest Version.\n");
		WriteToLog("Already Latest Version.");
		return 0;
	}
	WriteToLog("Begin Fetch HashList");


	// ��ȡ���°汾���ļ���ϣ�б�
	if (!ver.RequestHashList())
	{
		printf("Request Latest HashList failed.\n");
		WriteToLog("Request Latest HashList failed");
		return 1;
	}
	WriteToLog("Request Latest HashList Ok");


	// �����ļ���ϣ��ͬ����ȡ���С����¡����ļ�
	// �������ʹ�����ùؼ����б�ķ������õ��ļ�
	if (!ver.DownloadLatestFiles(TMPDOWN_DIR))
	{
		printf("Download Latest Files failed.\n");
		WriteToLog("Download Latest Files failed");
		return 1;
	}
	WriteToLog("Download Latest Files Ok");

	// ����ʱĿ¼�е��ļ��滻��װ��Ŀ¼���ļ�
	if (!ver.ReplaceFiles(TMPDOWN_DIR))
	{ 
		printf("Replace Files failed.\n");
		WriteToLog("Replace Files failed");
		ver.RollBack();
		return 1;
	}
	WriteToLog("Replace Files Ok");
	*/
	return 0;
}
