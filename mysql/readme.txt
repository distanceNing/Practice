mysql_data��
	typedef std::vector<boost::shared_ptr<std::string> > data_structer;
	�������Ϊ�˱��������ѯ���Ľ������
	ÿһ���ֶζ�������һ��string���У���Ϊ�Ƕ�̬�����ڴ�����������ָ����������Դ��
 MySQL:private uncopyable
	�������MySQL�ĸ��ֲ�����
	
	bool InitMySQL();
	��ʼ��
	bool ConnectMySQL(const char* host,const char* user,const char* passwd,const char*database,unsigned int port,const char* unix_socket,unsigned long client_flag);
	�������ݿ�
	bool QueryNoResultSet(const char* const sql_sentence);
	�˺���������û�н�����Ĳ�ѯ��䡣
	mysql_data* QueryResultSet(const char* const sql_sentence,int& row,int& fetch);
	�˺��������������ؽ�����Ĳ�ѯ��䣬����ֵΪ�������ݽṹ��ָ�룬����������ָ�������档
	
	�����private�̳�uncopyable,����private�̳�has a�����ԣ���������л����ĳЩ���ԡ�
	����MySQL�������Ƕ�һ�޶��ģ����ɸ��ƣ���ֵ��