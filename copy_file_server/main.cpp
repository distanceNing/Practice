#include <iostream>
#include <unistd.h>
#include "Csocket.h"
#include <memory>
#include "receive_file.h"
#include "check_permission.h"
const int PORT=9000;
int main()
{
	Csocket sock;
	sock.CreatSocket(AF_INET, SOCK_STREAM, PORT);
	sock.Listen();
	char fromIP[20];
	UINT fromPort;
	char file_name[256];
	while(true)
	{
		std::cout<<"wait for connection!\n";
		std::auto_ptr<Csocket> sock_temp(new Csocket);
		sock.Accept(*sock_temp, fromIP, fromPort);
		std::cout << "fromIP: " << fromIP << std::endl;
		std::cout << "fromPort: " << fromPort << std::endl;

		int size = sock_temp->Receive(file_name, 256);
		int ret=check_permission(file_name);
	
		if(!ret)									//ret=0 :check successful	
		{
			sock_temp->Send(&ret,sizeof(int)); 
			file_name[size]='\0';
			if(!access(file_name,F_OK))				//file exists
			{
				std::cout<<"File exists!\n";
				file_name[size]='?';
				file_name[size+1]='\0';
			}
	
			int flag=receive_file(file_name,*sock_temp);
			std::cout<<"copy successful: "<<file_name<<std::endl;
		}
		else
		{
			sock_temp->Send(&ret,sizeof(int));		//return error_num 
		}
	}
	return 0;
}
