
#include "MyFTP.h"
#define FTP_AUTH		"li19950717"
 /*  在cloudmonitor 上线后如果服务器端的客户端版本较高 要更新cloudmonitor自身 则直接开启一个进程
  *  ：MyCreateProcess("Update.exe", NULL);
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




	/*USER class 中加一个CloudVersion的成员变量 来做自更新功能
	CloudVersion ver;
	
	
	// 获取当前程序的版本号
	cout << "Current Version: " << ver.GetCurVersion() << endl;

	if (2 == argc && 0 == strncmp(UPDATE_ARGS, argv[1], sizeof(UPDATE_ARGS)))
	{
		EnableLog();
	}

	// 获取服务端保存的最新版本号
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


	// 获取最新版本的文件哈希列表
	if (!ver.RequestHashList())
	{
		printf("Request Latest HashList failed.\n");
		WriteToLog("Request Latest HashList failed");
		return 1;
	}
	WriteToLog("Request Latest HashList Ok");


	// 根据文件哈希不同，获取所有‘更新’的文件
	// 这里可以使用像获得关键字列表的方法，得到文件
	if (!ver.DownloadLatestFiles(TMPDOWN_DIR))
	{
		printf("Download Latest Files failed.\n");
		WriteToLog("Download Latest Files failed");
		return 1;
	}
	WriteToLog("Download Latest Files Ok");

	// 用临时目录中的文件替换安装根目录的文件
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
