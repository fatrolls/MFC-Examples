#include "stdafx.h"
#include "Object.hpp"



namespace async
{

	namespace IOCP
	{

		Callback::AllocCallback Callback::m_allocCallback;
		Callback::DeallocCallback Callback::m_deallocCallback;


		void Callback::Alloc(size_t size)
		{
			static volatile LONG uAllocCount = 0;
			static volatile LONG uAllocSize = 0;

			if( uAllocCount >= LONG_MAX )
				uAllocCount = 0;
			if( uAllocSize >= LONG_MAX )
				uAllocSize = 0;

			::InterlockedExchangeAdd(&uAllocCount, 1);
			::InterlockedExchangeAdd(&uAllocSize, size);

			if( m_allocCallback != NULL )
				m_allocCallback(uAllocCount, uAllocSize);
		}

		void Callback::Dealloc(size_t size)
		{
			static volatile LONG uDeallocCount = 0;
			static volatile LONG uDeallocSize = 0;

			if( uDeallocCount >= LONG_MAX )
				uDeallocCount = 0;
			if( uDeallocSize >= LONG_MAX )
				uDeallocSize = 0;

			::InterlockedExchangeAdd(&uDeallocCount, 1);
			::InterlockedExchangeAdd(&uDeallocSize, size);

			if( m_deallocCallback != NULL )
				m_deallocCallback(uDeallocCount, uDeallocSize);
		}


		void Callback::RegisterCallback(AllocCallback allocCallback, DeallocCallback deallocCallback)
		{
			m_allocCallback = allocCallback;
			m_deallocCallback = deallocCallback;
		}
	}

}