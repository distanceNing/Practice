/* ************************************************************************
 *       Filename:  mysql_data.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/25/2017 09:28:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <vector>
#include <string>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <iostream>
class mysql_data
{
public:
	typedef std::vector<boost::shared_ptr<std::string> > data_structer;
	mysql_data(){}
	void push_back( char* str);
	const char* operator[](int i)
	{
		if(i<element.size())
			return (element[i])->c_str();
		else
			std::cerr<<"accross of range!\n";
	}
	int size()
	{
		return element.size();
	}
private:
	data_structer element;
};


