#ifndef __SGI_MALLOC_MEMORYPOOL_HPP
#define __SGI_MALLOC_MEMORYPOOL_HPP



#include <iostream>
#include <new>
#include <exception>



namespace async
{

	namespace memory
	{


		class MallocMemoryPool
		{
			// 仿造set_new_handler(),指定自己的out-of-memory handler
			typedef void (*pFuncOOMHandler)();

		private:
			static pFuncOOMHandler m_pFuncOOMHandler;

		private:
			// 以下函数用来处理内存不足
			// oom : out of memory
			static void *OOMMalloc(size_t sz)
			{
				pFuncOOMHandler pHandler = NULL;
				void *pResult = NULL;

				// 不断尝试释放、配置、在释放、在配置...
				for( ; ; )
				{
					pHandler = m_pFuncOOMHandler;

					if( NULL == pHandler )
						throw std::bad_alloc();

					// 调用处理函数,企图释放内存
					(*pHandler)();

					// 再次尝试配置内存
					pResult = std::malloc(sz);
					if( pResult )
						return pResult;
				}
			}


			static void *OOMRealloc(void *p, size_t sz)
			{
				pFuncOOMHandler pHandler = NULL;
				void *pResult = NULL;

				// 不断尝试释放、配置、在释放、在配置...
				for( ; ; )
				{
					pHandler = m_pFuncOOMHandler;

					if( NULL == pHandler )
						throw std::bad_alloc();

					// 调用处理函数,企图释放内存
					(*pHandler)();

					// 再次尝试配置内存
					pResult = std::realloc(p, sz);
					if( pResult )
						return pResult;
				}
			}



		public:
			static void *Allocate(size_t sz)
			{
				// 直接使用malloc
				void *pResult = std::malloc(sz);

				// 如果无法满则要求时,改用OOMMalloc
				if( NULL == pResult )
					pResult = OOMMalloc(sz);

				return pResult;
			}

			static void Deallocate(void *p, size_t/* sz*/)
			{
				// 直接使用free
				std::free(p);
			}


			static void *Reallocate(void *p, size_t/* szOld*/, size_t szNew)
			{
				// 直接使用realloc
				void *pResult = std::realloc(p, szNew);

				// 无法满足要求时, 改用OOMRealloc
				if( NULL == pResult )
					pResult = OOMRealloc(p, szNew);

				return pResult;
			}


			// 仿造set_new_handler(),指定自己的out-of-memory handler
			static void (*MallocMemoryPool::pFuncSetOOMHandler(pFuncOOMHandler pFunc))()
			{
				pFuncOOMHandler pOldFunc = m_pFuncOOMHandler;
				m_pFuncOOMHandler = pFunc;

				return pOldFunc;
			}
		};

		// __declspec(selectany) 防止LNK2005
		__declspec(selectany) MallocMemoryPool::pFuncOOMHandler MallocMemoryPool::m_pFuncOOMHandler = NULL;
	}
}


#endif