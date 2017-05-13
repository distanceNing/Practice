#include <iostream>
#include "Csocket.h"
const int PORT=9000;
#include "send_file.h"
#include "check_permission.h"

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		std::cerr << "argc < 4 !\n ";
		return -1;
	}
	const char* local_file_name=argv[2];
	int flag=check_permission(local_file_name);
	if(flag==no_file)
	{
		std::cerr<<"No this file !\n";
		return -1;
	}
	if(flag==permission_denied)
	{
		std::cerr<<"Local file permission denied!\n";
		return -1;
	}
	Csocket sock;
	sock.CreatSocket();
	char* fromIP = argv[1];                
	UINT fromPort=PORT;			 //defaut port is 9000
	if (!sock.Connect(fromIP, fromPort))
	{
		std::cout << "connect fail !\n";
		return -1;
	}
	char* file_name = argv[3];               
	sock.Send(file_name, strlen(file_name));
	int ret;
	sock.Receive(&ret, sizeof(ret));
	if (ret == no_file)
	{
		std::cout << "No this directory!\n";
		return -1;
	}
	if (ret==permission_denied)
	{
		std::cout << "Permission denied!\n";
		return -1;
	}

	int size = send_file(local_file_name, sock);
	std::cout<<"send size: "<<size<<std::endl;
	std::cout<<"copy successful!\n";
	
	return 0;

}
