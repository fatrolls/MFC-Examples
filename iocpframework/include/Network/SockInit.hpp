#ifndef __NETWORK_WINSOCK_INIT_HPP
#define __NETWORK_WINSOCK_INIT_HPP

#include "../IOCP/WinException.hpp"
#include <memory>



namespace async
{

	namespace network
	{
		namespace Internal
		{
			//------------------------------------------------------------------
			// class SockInit

			template<int Major = 2, int Minor = 0>
			class SockInit
			{
			private:
				static SockInit instance_;

				struct _SockInit;
				std::tr1::shared_ptr<_SockInit> ref_;

			private:
				// 执行真实的初始化
				struct _SockInit
				{
				private:
					int result_;

				public:
					_SockInit()
					{
						WSADATA wsa_data;
						result_ = ::WSAStartup(MAKEWORD(Major, Minor), &wsa_data);
					}

					~_SockInit()
					{
						::WSACleanup();
					}

					int Result() const
					{
						return result_;
					}

					// Singleton
					static std::tr1::shared_ptr<_SockInit> Instance()
					{
						static std::tr1::shared_ptr<_SockInit> init(new _SockInit);
						return init;
					}
				};

			public:
				SockInit()
					: ref_(_SockInit::Instance())
				{
					if( this != &instance_ && ref_->Result() != 0 )
					{
						throw async::IOCP::Win32Exception("WSAStartup");
					}
				}

				~SockInit()
				{
				}

			private:
				SockInit(const SockInit &);
				SockInit &operator=(const SockInit &);
			};

			template<int Major, int Minor>
			SockInit<Major, Minor> SockInit<Major, Minor>::instance_;

		}
	}
}



#endif