/* ************************************************************************
 *       Filename:  mysql_cpp.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/23/2017 11:56:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <mysql.h>
#include <iostream>
#include <string.h>
#include "uncopyable.h"
#include "mysql_data.h"
class MySQL:private uncopyable
{
private:
	MYSQL *conn_ptr;

public:
	MySQL();
	bool InitMySQL();
	bool ConnectMySQL(const char* host,const char* user,const char* passwd,const char*database,unsigned int port,const char* unix_socket,unsigned long client_flag);
	bool QueryNoResultSet(const char* const sql_sentence);
	mysql_data* QueryResultSet(const char* const sql_sentence,int& row,int& fetch);
	~MySQL()
	{
		mysql_close(conn_ptr);
	}
	
};


