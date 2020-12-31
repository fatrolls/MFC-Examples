#ifndef __IOCP_WIN_EXCEPTION_HPP
#define __IOCP_WIN_EXCEPTION_HPP


#include "../Basic.hpp"

#include <stdexcept>
#include <string>


namespace async
{


	namespace IOCP
	{
		//-------------------------------------------------------------------
		// class Win32Exception

		class Win32Exception 
			: public std::exception 
		{
		private:
			std::string m_info;

		public:
			Win32Exception(const std::string &apiName, unsigned long dwErrCode = ::GetLastError());
			~Win32Exception();

		public:
			const char * what() const;
		};
	}

}

#endif