#ifndef __IOCP_BUFFER_HPP
#define __IOCP_BUFFER_HPP



#include "Object.hpp"


namespace async
{


	namespace IOCP
	{

		//-------------------------------------------------------------------
		// class BufferT
		// 提供缓冲区服务，支持STL标准接口

		template<typename T, size_t __DefaultSize, typename AllocT>
		class BufferT
			: public Object
		{
		public:
			typedef T			value_type;
			typedef T*			pointer;
			typedef const T*	const_pointer;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef AllocT		AllocType;

			typedef typename AllocType::BufferType BufferType;

			//typedef typename AllocType BufferType;

		private:
			static BufferType BufferPool;
			AllocType m_alloc;

			value_type *m_pBuf;
			size_t m_nBufSize;
			size_t m_nAllocSize;

		public:
			BufferT()
				: m_alloc(BufferPool)
				, m_nAllocSize(__DefaultSize)
				, m_nBufSize(0)
			{
				m_pBuf = _Allocate(m_nAllocSize);
			}
			explicit BufferT(size_t nSize)
				: m_alloc(BufferPool)
				, m_nAllocSize(nSize)
				, m_nBufSize(0)
			{
				if( nSize < 4 )
					m_nAllocSize = 4;

				m_pBuf = _Allocate(m_nAllocSize);
			}
			BufferT(const_pointer pStr, size_t nSize)
				: m_alloc(BufferPool)
				, m_nAllocSize(nSize)
				, m_nBufSize(nSize)
			{
				if( m_nAllocSize < 4 )
					m_nAllocSize = 4;

				m_pBuf = _Allocate(m_nAllocSize);
				RtlMoveMemory(m_pBuf, pStr, m_nBufSize);
			}
			virtual ~BufferT()
			{
				m_alloc.deallocate(m_pBuf, m_nAllocSize);
			}

		public:
			pointer begin()
			{
				return m_pBuf;
			}
			const_pointer begin() const
			{
				return m_pBuf;
			}

			pointer end()
			{
				return m_pBuf + m_nBufSize;
			}
			const_pointer end() const
			{
				return m_pBuf + m_nBufSize;
			}

			size_t size() const
			{
				return m_nBufSize;
			}
			size_t allocSize() const
			{
				return m_nAllocSize;
			}

			void resize(size_t nNewSize)
			{
				if( nNewSize <= m_nAllocSize )
					m_nBufSize = nNewSize;
				else
				{
					m_nAllocSize = nNewSize;

					pointer pNewBuf = _Allocate(m_nAllocSize);

					RtlMoveMemory(pNewBuf, m_pBuf, m_nBufSize);
					m_alloc.deallocate(m_pBuf, m_nAllocSize);

					m_pBuf = pNewBuf;
				}
			}

			pointer data(size_t offset = 0)
			{
				return m_pBuf + offset;
			}
			const_pointer data(size_t offset = 0) const
			{
				return m_pBuf + offset;
			}


		private:
			pointer _Allocate(size_t nSize)
			{
				pointer pBuf = m_alloc.allocate(nSize);
				ZeroMemory(pBuf, nSize);

				return pBuf;
			}
		};

		template<typename T, size_t __DefaultSize, typename AllocT>
		typename BufferT<T, __DefaultSize, AllocT>::BufferType BufferT<T, __DefaultSize, AllocT>::BufferPool;


	} // end of IOCP


} // end of async





#endif