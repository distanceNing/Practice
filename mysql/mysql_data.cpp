/* ************************************************************************
 *       Filename:  mysql_data.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  04/25/2017 10:01:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include "mysql_data.h"

void mysql_data::push_back( char* str)
{

	element.push_back(boost::shared_ptr<std::string> (new std::string(str))) ;
}



