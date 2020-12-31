#include <cstdio>
#include <cstring>
#include "astring.hpp"
using namespace std;


String1::String1(const char *str)
{
    if ( str == NULL ) //strlen在参数为NULL时会抛异常才会有这步判断
    {
        m_data = new char[1] ;
        m_data[0] = '\0' ;
    }
    else
    {
        m_data = new char[strlen(str) + 1];
        strcpy(m_data,str);
    }

}

String1::String1(const String1 &another)
{
    m_data = new char[strlen(another.m_data) + 1];
    strcpy(m_data,another.m_data);
}


String1& String1::operator=(const String1 &rhs)
{
    if ( this == &rhs)
        return *this ;
    delete []m_data; //删除原来的数据，新开一块内存
    m_data = new char[strlen(rhs.m_data) + 1];
    strcpy(m_data,rhs.m_data);
    return *this ;
}


String1::~String1()
{
    delete []m_data ;
}
