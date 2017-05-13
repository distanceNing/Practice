#include "check_permission.h"

int check_permission(const char* const file_name)
{
	int ret=0;
	std::string str(file_name);	
	std::string::iterator start=str.end();
	while(*(--start)!='/'){}
	str.erase(++start,str.end());
	if(access(str.c_str(),F_OK)!=0)
	{
		ret =no_file;
		return ret;
	}
	if(access(str.c_str(),W_OK)!=0)
		ret=permission_denied;
	return ret;
}

