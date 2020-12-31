#ifndef __NETWORK_IP_ADDRESS_HPP
#define __NETWORK_IP_ADDRESS_HPP


#include "../Basic.hpp"
#include <string>


namespace async
{


	namespace network
	{

		class IPAddress 
		{
		private:
			u_long address;

		public:
			IPAddress(u_long address);

		public:
			u_long Address() const;
			bool operator==(const IPAddress &ipaddr);
			bool operator!=(const IPAddress &ipaddr);


			static IPAddress Parse(const std::string &str);
		};
	}


}



#endif