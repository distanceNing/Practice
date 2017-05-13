#include <unistd.h>
#include <string>
enum error_num
{
	no_file=3,
	permission_denied,
};
int check_permission(const char* const file_name);
