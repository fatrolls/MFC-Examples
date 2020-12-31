#include <iostream>
#include <string>

#define URL_PROTOCOL_STRING			L"URL:%s Protocol"
#define URL_PROTOCOL				L"URL Protocol"
#define URL_PROTOCOL_DEFAULTICON	L"DefaultIcon"
#define URL_PROTOCOL_COMMAND		L"Shell\\Open\\command"
#define URL_PROTOCOL_OPEN			L"Shell\\Open"
#define URL_PROTOCOL_SHELL			L"Shell"

class CustomURLProtocol
{
	private:
		std::wstring		m_wszProtocolName;
		std::wstring		m_wszCompanyName;
		std::wstring		m_wszAppPath;

		DWORD				m_dwErrorCode;
		std::wstring		m_wszErrorMsg;

		void				FormatErrorMsg();

	public:

		std::wstring getProtocolName() {return m_wszProtocolName;}
		std::wstring getCompanyName() {return m_wszCompanyName;}
		std::wstring getAppPath() {return m_wszAppPath;}
		std::wstring getErrorMsg(){return m_wszErrorMsg;};

		void setProtocolName(std::wstring pwProtocolName){m_wszProtocolName = pwProtocolName;}
		void setCompanyName(std::wstring pwCompanyName){m_wszCompanyName = pwCompanyName;}
		void setAppPath(std::wstring pwAppPath){m_wszAppPath = pwAppPath;}
		
		CustomURLProtocol();
		CustomURLProtocol(std::wstring pwProtocolName, std::wstring pwCompanyName, std::wstring pwAppPath);

		int CreateCustomProtocol();
		int DeleteCustomProtocol();
};