mysql_data：
	typedef std::vector<boost::shared_ptr<std::string> > data_structer;
	这个类是为了保存解析查询语句的结果集。
	每一个字段都保存在一个string当中，因为是动态分配内存所以用智能指针来管理资源。
 MySQL:private uncopyable
	这个类是MySQL的各种操作。
	
	bool InitMySQL();
	初始化
	bool ConnectMySQL(const char* host,const char* user,const char* passwd,const char*database,unsigned int port,const char* unix_socket,unsigned long client_flag);
	连接数据库
	bool QueryNoResultSet(const char* const sql_sentence);
	此函数用来做没有结果集的查询语句。
	mysql_data* QueryResultSet(const char* const sql_sentence,int& row,int& fetch);
	此函数是用来做返回结果集的查询语句，返回值为上述数据结构的指针，建议用智能指针来保存。
	
	这个类private继承uncopyable,根据private继承has a的特性，派生类具有基类的某些特性。
	所以MySQL的连接是独一无二的，不可复制，赋值。