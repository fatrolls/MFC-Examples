#ifndef __MEMORY_FIXED_MEMORY_POOL_HPP
#define __MEMORY_FIXED_MEMORY_POOL_HPP


#include "SGIMemoryPool.hpp"

namespace async
{

	namespace memory
	{


		// 定长大小__BYTES = 10 * 1024

		template<bool __IS_MT, size_t __BYTES, typename AllocT = MallocAllocateTraits>
		class FixedMemoryPool
		{
		public:
			typedef typename LockTypeTraits<__IS_MT>::value_type LockType;
			typedef thread::CAutoLock<LockType>			AutoLock;
			typedef AllocT								AllocType;

			// 多线程共享时，应该让变量具有volatile修饰，而单线程应该让其尽量优化提高速度
			union obj;
			typedef typename ValueTypeVolatileTraits<obj, __IS_MT>::value_type	ObjPtrType;


		private:
			// 每次初始化时尝试往free - list中增加元素的数量
			static const size_t __NUM_NODE = 20;
			static const size_t __ALIGN = 4;

			// ROUND_UP 将bytes上调至__ALIGN的倍数
			enum { ROUND = (__BYTES + __ALIGN - 1) & ~(__ALIGN - 1) };

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
			ObjPtrType m_pFreeLists[1];


		public:
			FixedMemoryPool()
				: m_pStartFree(NULL)
				, m_pEndFree(NULL)
				, m_szHeap(0)
			{
				::memset((void *)m_pFreeLists, 0, 1 * sizeof(ObjPtrType));
			}

			~FixedMemoryPool()
			{
				clear();
			}

		private:
			FixedMemoryPool(const FixedMemoryPool &);
			FixedMemoryPool &operator=(const FixedMemoryPool &);

		public:
			// n必须大于0
			void *Allocate(size_t n)
			{
				assert(n == __BYTES);

				// 寻找free - lists中适当的一个
				ObjPtrType *pFreeListTemp = m_pFreeLists;
				obj *pResult = NULL;

				// 调用构造函数时需要加锁
				{
					AutoLock lock(m_lock);	

					pResult = *pFreeListTemp;

					if( pResult == NULL )
					{	
						// 如果没有找到可用的则申请
						pResult = ReFill(ROUND);
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
				assert(n == __BYTES);

				// 得到内存池地址
				obj *pTemp = reinterpret_cast<obj *>(p);
				ObjPtrType *pFreeListTemp = m_pFreeLists;

				{
					AutoLock lock(m_lock);

					// 回收。改变Next指针，将返回的节点放在List开头
					pTemp->pFreeListLink = *pFreeListTemp;
					*pFreeListTemp = pTemp;
				}

			}

		private:
			// ROUND_UP 将bytes上调至__ALIGN的倍数
			static inline size_t ROUNDUP(size_t bytes)
			{
				return ((bytes) + __ALIGN - 1) & ~(__ALIGN - 1);
			}

		private:
			// 返回一个大小为n的对象,并加入大小为n的其他区块到free - list
			obj *ReFill(size_t n)
			{
				// 缺省为__NUM_NODE个新区块,如果内存空间不足，获得的区块书可能小于20
				size_t nObjs = __NUM_NODE;

				// 调用ChunkAlloc,尝试取得nObjs个区块
				// nObjs是以Pass By reference传递
				char *pChunk = ChunkAlloc(n, nObjs);

				// 如果只获得一个区块,则这个区块就分配给调用者,无新空闲区块
				if( 1 == nObjs )
					return reinterpret_cast<obj *>(pChunk);

				// 否则调整free - list，注入新区块
				ObjPtrType *pFreeListTemp  = m_pFreeLists;

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
					// 内存池剩余空间不够一个区块
					// 需要获取的内存, 注意第一次分配都要两倍于szTotal的大小
					// 同时要加上原有的m_szHeap / 4的对齐值
					size_t szGet = 2 * szTotal + ROUNDUP(m_szHeap >> 4);

					// 配置Heap空间，用来补充内存池
					m_pStartFree = reinterpret_cast<char *>(AllocType::Allocate(szGet));

					if( NULL == m_pStartFree )
					{
						// 没有分配到内存，转给MallocMemoryPool
						m_pEndFree = 0;
						m_pStartFree = reinterpret_cast<char *>(MallocMemoryPool::Allocate(szGet));
						if( NULL == m_pStartFree )
							throw std::bad_alloc("FixedMemoryPool");
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


		typedef FixedMemoryPool<true, 10 * 1024>	MTFixedMemoryPool;
		typedef FixedMemoryPool<false, 10 * 1024>	STFixedMemoryPool;

	}
}




#endif