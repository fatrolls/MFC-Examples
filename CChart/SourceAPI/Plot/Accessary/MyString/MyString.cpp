#include "stdafx.h"
#include "MyString.h"
#include "sys/stat.h"
////////////////////////////////////////////////////////////////////////////////////////////////
//
//定义一些操作字符串的函数

void string_tolower ( string & str ) 
{
	transform(str.begin(),str.end(),str.begin(),tolower);
}

void string_toupper ( string & str ) 
{
	transform(str.begin(),str.end(),str.begin(),toupper);
}

string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)   
{   
    while(true)
	{
		string::size_type   pos(0);   
        if(   (pos=str.find(old_value))!=string::npos   )   
            str.replace(pos,old_value.length(),new_value);   
        else   break;   
    }   
    return   str;   
}

string&   replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)   
{   
    for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())
	{
        if(   (pos=str.find(old_value,pos))!=string::npos   )   
            str.replace(pos,old_value.length(),new_value);   
        else   break;   
    }   
    return   str;   
}

string::size_type find_first_nospace(string str)
{
	string::size_type i=0;
	do
	{
		if(i==str.size()-1)
		{
			if(isspace(str[i]))
				return string::npos;
			else
				return str.size()-1;
		}
		if(isspace(str[i]))
		{
			i++;
			continue;
		}
		else
		{
			return i;
		}
	}while(true);
}

string::size_type rfind_first_nospace(string str)
{
	string::size_type i=str.size()-1;
	do
	{
		if(i==0)
		{
			if(isspace(str[i]))
				return string::npos;
			else
				return 0;
		}
		if(isspace(str[i]))
		{
			i--;
			continue;
		}
		else
		{
			return i;
		}
	}while(true);
}

void trimleft(string &str)
{
	string::size_type idx=find_first_nospace(str);
	if(idx!=string::npos && idx<str.size() )str.erase(0,idx);
}

void trimright(string &str)
{
	string::size_type idx=rfind_first_nospace(str);
	if(idx!=string::npos && idx<str.size() )str.erase(idx+1);
}

void trim(string& str, const string drop)
{
	// trim right
	str.erase(str.find_last_not_of(drop)+1);
	// trim left
	str.erase(0,str.find_first_not_of(drop));
} 

void trimleft(string& str, const string drop)
{
	// trim left
	str.erase(0,str.find_first_not_of(drop));
} 

void trimright(string& str, const string drop)
{
	// trim right
	str.erase(str.find_last_not_of(drop)+1);
}

//对字符串操作，模拟读文件的一行，默认以\n为换行的符号
string readline(const string& buffer,string::size_type &curpos, const string symbol)
{
	string ret;
	string::size_type pos;
	pos=buffer.find_first_of(symbol,curpos);
	if(pos==string::npos)
	{
		curpos=0;
		return "";
	}
	else
	{
		ret=buffer.substr(curpos,pos-curpos);
		curpos=pos+1;
		return ret;
	}
}

long get_file_size( const char* filename )
{
	struct stat f_stat; 
	if( stat( filename, &f_stat ) == -1 )
	{
		return -1; 
	}
	return (long)f_stat.st_size; 
}

long get_file_size( FILE* fp)
{
	long curpos,filesize;
	curpos=ftell(fp);
	fseek(fp,0L,SEEK_END);
    filesize=ftell(fp); 
	fseek(fp,curpos,SEEK_SET);
	return filesize;
}