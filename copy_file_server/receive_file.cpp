#include "receive_file.h"

int receive_file(const char * const filename,Csocket &sock)
{
	int write_type;
	sock.Receive(&write_type,sizeof(write_type));
	const char* write=write_type? "w":"wb";
	FILE* fp=fopen(filename,write); 
	char buffer[BUF_SIZE];
	memset(buffer, '\0', BUF_SIZE);
	int recv_size=0;
	int size;
	while ((size=sock.Receive(buffer, BUF_SIZE))>0)
	{
		fwrite(buffer, 1, size, fp);
		recv_size += size;
		printf("recv size: %d\n",recv_size);
	}
	return recv_size;
}
