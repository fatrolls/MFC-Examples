#ifndef __MYSTRING_32167_H
#define __MYSTRING_32167_H

#pragma warning(disable:4786)

#include <cctype>
#include <algorithm>
#include <string>
using namespace std;

//typedef std::string MyString;
//typedef std::string::size_type MyStrPos;

//×Ö·û´®´¦Àíº¯Êý
void string_tolower ( string & str ); 
void string_toupper ( string & str );
std::string& replace_all(std::string& str,const std::string& old_value,const std::string& new_value);
std::string& replace_all_distinct(std::string& str,const std::string& old_value,const std::string& new_value);
string::size_type find_first_nospace(string str);
string::size_type rfind_first_nospace(string str);
void trimleft(string &str);
void trimright(string &str);
void trim(string& str, const string drop = " ");
void trimleft(string& str, const string drop);
void trimright(string& str, const string drop);
string readline(const string& buffer,string::size_type &curpos, const string symbol="\n");

long get_file_size( const char* filename );
long get_file_size( FILE* fp);

#endif