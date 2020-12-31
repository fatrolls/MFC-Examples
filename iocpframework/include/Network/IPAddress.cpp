#include "stdafx.h"
#include "IPAddress.hpp"


namespace async
{

	namespace network
	{

		IPAddress::IPAddress(u_long address)
			: address(address)
		{
		}

		u_long IPAddress::Address() const
		{
			return address;
		}

		bool IPAddress::operator==(const IPAddress &ipaddr)
		{
			return address == ipaddr.address;
		}

		bool IPAddress::operator!=(const IPAddress &ipaddr)
		{
			return address != ipaddr.address;
		}

		IPAddress IPAddress::Parse(const std::string &str)
		{
			u_long address = ::ntohl(::inet_addr(str.c_str()));

			return IPAddress(address);
		}
	}

}