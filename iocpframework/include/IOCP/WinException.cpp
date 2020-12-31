#include "stdafx.h"
#include "WinException.hpp"

#include <sstream>


namespace async
{


	namespace IOCP
	{

		Win32Exception::Win32Exception(const std::string &apiName, unsigned long dwErrCode)
		{
			std::ostringstream oss;
			char *buffer = NULL;
			::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				0, dwErrCode, 0, (LPSTR)&buffer, 0, 0);
			oss << "Win32 Error(" << dwErrCode << ") at " << apiName << ": " << buffer;

			::LocalFree(buffer);
			m_info = oss.str();
		}

		Win32Exception::~Win32Exception()
		{
		}

		const char * Win32Exception::what() const
		{
			return m_info.c_str();
		}
	}


}