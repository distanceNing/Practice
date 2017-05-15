/* ************************************************************************
 *       Filename:  uncopyable.h
 *    Description:  
 *        Version:  1.0
 *        Created:  04/25/2017 07:49:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

class uncopyable
{
private:
	uncopyable(const uncopyable& copy){}
	uncopyable& operator=(const uncopyable& assign){}
		
public:
	uncopyable(){}
	~uncopyable(){}
};

