#ifndef __SGI_MEMORYPOOL_HPP
#define __SGI_MEMORYPOOL_HPP


#include "../MultiThread/Lock.hpp"
#include "SGIMallocPool.hpp"
#include <vector>
#include <algorithm>




/*
	实现分析:
	该内存池采用HASH-LIST数据结构管理数据,分配一块内存时,如果所要求的内存超过了某个数量就直接调用malloc分配内存, 
	否则首先进行数据对齐,根据这个对齐的结果得到所在的HASH表,在该HASH-LIST中查找时候存在可用的节点,
	如果有就直接返回,否则每次以20个节点元素为数量开始增加LIST中的元素数量,
	如果仍然分配失败了就去下一个HASH表中查找可用内存,依次类推
*/



namespace async
{

	namespace memory
	{

		// 单线程不需要volatile，多线程则需要
		template<typename T, bool __IS_MT>
		struct ValueTypeVolatileTraits
		{
			typedef T* volatile 		value_type;
		};
		template<typename T>
		struct ValueTypeVolatileTraits<T, false>
		{
			typedef T*					value_type;
		};


		// 锁选择器
		template<bool __IsMt>
		struct LockTypeTraits
		{
			typedef thread::CAutoCriticalSection	value_type;
		};
		template<>
		struct LockTypeTraits<false>
		{
			typedef thread::CAutoNull				value_type;
		};


		// Win32 上分配内存方式

		struct VirtualAllocateTraits
		{
			static void *Allocate(size_t size)
			{
				void *p = ::VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_EXECUTE_READWRITE);
				::VirtualLock(p, size);

				return p;
			}

			static void Deallocate(void *p, size_t size)
			{
				::VirtualUnlock(p, size);
				::VirtualFree(p, size, MEM_RELEASE);
			}
		};

		struct HeapAllocateTraits
		{
			static HANDLE GetHeap()
			{
				static HANDLE heap = NULL;

				if( heap == NULL )
				{
					heap = ::HeapCreate(0, 0, 0);

					// 设置低碎片堆
					ULONG uHeapFragValue = 2;
					::HeapSetInformation(heap, HeapCompatibilityInformation, &uHeapFragValue, sizeof(ULONG));
				}

				return heap;
			}

			static void *Allocate(size_t size)
			{
				return ::HeapAlloc(GetHeap(), HEAP_ZERO_MEMORY, size);;
			}

			static void Deallocate(void *p, size_t/* size*/)
			{
				::HeapFree(GetHeap(), 0, p);
			}
		};

		struct MallocAllocateTraits
		{
			static void *Allocate(size_t size)
			{
				return std::malloc(size);
			}

			static void Deallocate(void *p, size_t)
			{
				return std::free(p);
			}
		};


		// 小型区块的上限 __MAX_BYTES = 256

		template<bool __IS_MT, size_t __MAX_BYTES, typename AllocT = MallocAllocateTraits>
		class SGIMemoryPool
		{
		public:
			typedef typename LockTypeTraits<__IS_MT>::value_type LockType;
			typedef thread::CAutoLock<LockType>			AutoLock;
			typedef AllocT								AllocType;

			// 多线程共享时，应该让变量具有volatile修饰，而单线程应该让其尽量优化提高速度
			union obj;
			typedef typename ValueTypeVolatileTraits<obj, __IS_MT>::value_type	ObjPtrType;



		private:
			// 小型区块的上调边界
			static const size_t __ALIGN = 8;

			// free-lists的个数
			static const size_t __NUM_FREE_LISTS = __MAX_BYTES / __ALIGN;

			// 每次初始化时尝试往free - list中增加元素的数量
			static const size_t __NUM_NODE = 20;

			// Chunk allocation state
		private:
			// 内存池起始位置
			char *m_pStartFree;
			// 内存池结束位置
			char *m_pEndFree;
			// 所分配的空间大小
			size_t m_szHeap;

			typedef std::vector<std::pair<void *, size_t>> Bufs;
			Bufs m_bufs;

			// 线程锁
			LockType m_lock;	

		private:
			// free - lists的节点构造
			union obj
			{
				union obj *pFreeListLink;
				char clientData[1];		/* The client sees this*/
			};

			// free - lists数组
			ObjPtrType m_pFreeLists[__NUM_FREE_LISTS];


		public:
			SGIMemoryPool()
				: m_pStartFree(NULL)
				, m_pEndFree(NULL)
				, m_szHeap(0)
			{
				//STATIC_ASSERT(__NUM_FREE_LISTS != 0, __NUM_FREE_LISTS);

				m_bufs.reserve(__NUM_FREE_LISTS);
				::memset((void *)m_pFreeLists, 0, __NUM_FREE_LISTS * sizeof(ObjPtrType));
			}

			~SGIMemoryPool()
			{
				clear();
			}

		private:
			SGIMemoryPool(const SGIMemoryPool &);
			SGIMemoryPool &operator=(const SGIMemoryPool &);

		public:
			// n必须大于0
			void *Allocate(size_t n)
			{
				// 大于__MAX_BYTES就用MallocAllocator
				if( n > __MAX_BYTES )
				{
					return MallocMemoryPool::Allocate(n);
				}

				// 寻找free - lists中适当的一个
				ObjPtrType *pFreeListTemp = m_pFreeLists + FREELISTINDEX(n);
				obj *pResult = NULL;

				// 调用构造函数时需要加锁
				{
					AutoLock lock(m_lock);	

					pResult = *pFreeListTemp;

					if( pResult == NULL )
					{	
						// 如果没有找到可用的free - list，准备重新填充free - list
						pResult = ReFill(ROUNDUP(n));
					}
					else
					{
						// 调整free list,使其指向下一个List的节点，当分配完毕时，头结点为NULL
						*pFreeListTemp = pResult->pFreeListLink;
					}

				}

				return pResult;
			}


			// p不能为空
			void Deallocate(void *p, size_t n)
			{
				// 大于__MAX_BYTES就用MallocAllocator
				if( n > __MAX_BYTES )
					return MallocMemoryPool::Deallocate(p, n);

				// 寻找free - lists中适当的一个
				obj *pTemp = reinterpret_cast<obj *>(p);
				ObjPtrType *pFreeListTemp = m_pFreeLists + FREELISTINDEX(n);

				{
					AutoLock lock(m_lock);

					// 调整对应的free - list,回收。改变Next指针，将返回的节点放在List开头
					pTemp->pFreeListLink = *pFreeListTemp;
					*pFreeListTemp = pTemp;
				}

			}


			void *Reallocate(void *p, size_t szOld, size_t szNew)
			{
				// 如果大于__MAX_BYTES就用MallocAllocator
				if( szOld > __MAX_BYTES && szNew > __MAX_BYTES) 
				{
					return MallocMemoryPool::Reallocate(p, szOld, szNew);
				}

				// 如果圆整后的大小相同则直接返回
				if( ROUNDUP(szOld) == ROUNDUP(szNew) ) 
					return p;

				// 再次申请空间
				void *pResult = Allocate(szNew);

				// 判断选择更大的数据
				size_t szcopy = szNew > szOld ? szOld : szNew;
				::memmove(pResult, p, szcopy);

				// 删除原先的数据
				Deallocate(p, szOld);

				return pResult;

			}


		private:
			// ROUND_UP 将bytes上调至__ALIGN的倍数
			static inline size_t ROUNDUP(size_t bytes)
			{
				return ((bytes) + __ALIGN - 1) & ~(__ALIGN - 1);
			}

			// 根据区块大小，决定使用第n号free - lists。n从0号起
			static inline size_t FREELISTINDEX(size_t bytes)
			{
				return (((bytes) + __ALIGN - 1) / __ALIGN) - 1;
			}

		private:
			// 返回一个大小为n的对象,并加入大小为n的其他区块到free - list
			obj *ReFill(size_t n)
			{
				// 缺省为__NUM_NODE个新区块,如果内存空间不足，获得的区块书可能小于20
				size_t nObjs = __NUM_NODE;

				// 调用ChunkAlloc,尝试取得nObjs个区块为free - list的新区块
				// nObjs是以Pass By reference传递
				char *pChunk = ChunkAlloc(n, nObjs);

				// 如果只获得一个区块,则这个区块就分配给调用者，free - list无新区块
				if( 1 == nObjs )
					return reinterpret_cast<obj *>(pChunk);

				// 否则调整free - list，注入新区块
				ObjPtrType *pFreeListTemp  = m_pFreeLists + FREELISTINDEX(n);

				// 在Chunk空间内建立free - list
				// pResult准备返回给客户端
				obj *pResult = reinterpret_cast<obj *>(pChunk);

				obj *pCurObj = NULL, *pNextObj = NULL;

				// 请求了一个单位的内存，减少一个计数
				--nObjs;
				// 需要返回一个单位的内存，从下一个单位开始将剩余的obj连接起来, 导引free - list指向新配置空间
				*pFreeListTemp = pNextObj = reinterpret_cast<obj *>(pChunk + n);

				// 将free - list的各区块串接起来
				// 从1开始,第0个返回
				for(size_t i = 1; ; ++i)
				{
					pCurObj = pNextObj;
					pNextObj = reinterpret_cast<obj *>(reinterpret_cast<char *>(pNextObj) + n);

					if( nObjs == i )
					{
						// 分配完毕, 下一个节点为NULL, 退出循环
						pCurObj->pFreeListLink = NULL;
						break;
					}
					else
					{
						pCurObj->pFreeListLink = pNextObj;
					}
				}

				return pResult;
			}

			// 配置一块大空间,可容纳nObjs个大小为size的区块
			// 分配单位尺寸为size, 共nObjs个元素
			// 这些内存在物理地址上是连在一起的, 返回其指针
			char *ChunkAlloc(size_t sz, size_t &nObjs)
			{
				size_t szTotal = sz * nObjs;
				// 内存池剩余空间
				size_t szLeft =  m_pEndFree - m_pStartFree;

				char *pResult = NULL;
				if( szLeft >= szTotal )
				{
					// 内存池剩余空间满足需求
					pResult = m_pStartFree;

					// 移动指向剩余空间的指针
					m_pStartFree += szTotal;

					return pResult;
				}
				else if( szLeft >= sz )
				{
					// 内存池剩余空间不能完全满足需求量，但足够一个以上的区块
					// 改变申请的大小
					nObjs = szLeft / sz;

					// 移动指向剩余空间的指针
					szTotal = sz * nObjs;
					pResult = m_pStartFree;
					m_pStartFree += szTotal;

					return pResult;
				}
				else 
				{
					// 以下让内存池中的剩余还有利用价值
					if( szLeft > 0 )
					{
						// 先配给适当的free - list, 寻找适当的free - list
						ObjPtrType *pFreeListTemp = m_pFreeLists + FREELISTINDEX(szLeft);

						// 调整free - list，将内存池中的残余空间编入
						reinterpret_cast<obj *>(m_pStartFree)->pFreeListLink = *pFreeListTemp;
						*pFreeListTemp = reinterpret_cast<obj *>(m_pStartFree);
					}

					// 内存池剩余空间不够一个区块
					// 需要获取的内存, 注意第一次分配都要两倍于szTotal的大小
					// 同时要加上原有的m_szHeap / 4的对齐值
					size_t szGet = 2 * szTotal + ROUNDUP(m_szHeap >> 4);

					// 配置Heap空间，用来补充内存池
					m_pStartFree = reinterpret_cast<char *>(AllocType::Allocate(szGet));

					if( NULL == m_pStartFree )
					{
						// Heap空间不足
						ObjPtrType *pFreeList = NULL; 
						obj *pTemp = NULL;

						for(int i = sz; i <= __MAX_BYTES; i += __ALIGN)
						{
							pFreeList = m_pFreeLists + FREELISTINDEX(i);
							pTemp = *pFreeList;

							if( NULL == pTemp )
							{
								// free - list上有未用区块，调整出并释放
								*pFreeList = pTemp->pFreeListLink;
								m_pStartFree = reinterpret_cast<char *>(pTemp);
								m_pEndFree = m_pStartFree + i;

								// 递归调用，修正nObjs
								return ChunkAlloc(sz, nObjs);
							}
						}

						// 没有分配到内存，转给MallocMemoryPool
						m_pEndFree = 0;
						m_pStartFree = reinterpret_cast<char *>(MallocMemoryPool::Allocate(szGet));
					}

					// 存储起来提供释放
					m_bufs.push_back(std::make_pair(m_pStartFree, szGet));

					m_szHeap += szGet;
					m_pEndFree = m_pStartFree + szGet;

					// 递归调用，修正nObjs
					return ChunkAlloc(sz, nObjs);
				}
			}

			// 清空内存
			void clear()
			{
				for(Bufs::iterator iter = m_bufs.begin();
					iter != m_bufs.end(); ++iter)
				{
					AllocType::Deallocate(iter->first, iter->second);
				}
				m_bufs.clear();
			}
		};


		typedef SGIMemoryPool<true, 256>				SGIMTMemoryPool;
		typedef SGIMemoryPool<false, 256>				SGISTMemoryPool;

	}
}

#endif