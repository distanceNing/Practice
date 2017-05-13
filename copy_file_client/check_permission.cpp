#include "check_permission.h"

int check_permission(const char* const file_name)
{
	if(access(file_name,F_OK)!=0)
		return no_file;
	if(access(file_name,R_OK)!=0)
		return permission_denied;
	return 0;
}

