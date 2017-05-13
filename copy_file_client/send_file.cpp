#include "send_file.h"
 int is_text_file(const char *filename)  
 {  
	FILE *fp = fopen(filename, "rb");  
	long white_list_char_count = 0;  
	int read_len;  
	unsigned char byte;  
	while ((read_len = fread(&byte, 1, 1, fp)) > 0)  
	{  
		if (byte == 9 || byte == 10 || byte == 13 || (byte >= 32 && byte <= 255))  
		white_list_char_count++;  
		else if ((byte <= 6) || (byte >= 14 && byte <= 31))  
				return 0; 
	}  
  fclose(fp);  
	return (white_list_char_count >= 1) ? 1 : 0;  
}  

int send_file(const char * const filename,Csocket &sock)
{
	int ret=is_text_file(filename);
	sock.Send(&ret,sizeof(ret));
	int send_size = 0;
	int size;
	int fd=open(filename,O_RDONLY);
	assert(fd>0);
	struct stat stat_buf;
	fstat(fd,&stat_buf);
	send_size=sendfile(sock.GetSocket(),fd,NULL,stat_buf.st_size);
	return send_size;
}
											  
