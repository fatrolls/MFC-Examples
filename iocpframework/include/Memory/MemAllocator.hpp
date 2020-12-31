#ifndef __MEM_ALLOCATOR_HPP
#define __MEM_ALLOCATOR_HPP

#include <type_traits>



namespace async
{
	namespace memory
	{

		// -----------------------------------------------------------------
		// class MemAllocator
		// ¿‡À∆”⁄std::allocator

		template<typename T, typename AllocT>
		class MemAllocator
		{
		public:
			typedef typename std::tr1::remove_volatile<T>::type		NonVolatileValueType;
			typedef typename std::tr1::remove_const<NonVolatileValueType>::type value_type;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;
			typedef typename value_type&							reference;
			typedef const value_type&								const_reference;
			typedef size_t											size_type;
			typedef ptrdiff_t										difference_type;
			typedef AllocT											BufferType;

			// rebind allocator to type U
			template<typename U>
			struct rebind 
			{
				typedef MemAllocator<U, AllocT> other;
			};

		private:
			AllocT *m_alloc;

		public:
			explicit MemAllocator(AllocT &alloc)
				: m_alloc(&alloc)
			{
			}
			MemAllocator(const MemAllocator &rhs)
				: m_alloc(rhs.m_alloc)
			{
			}
			template<typename U>
			MemAllocator(const MemAllocator<U, AllocT>& rhs)
				: m_alloc(rhs.m_alloc)
			{
			}
			~MemAllocator()
			{
			}

		public:
			pointer Address(reference value) const 
			{
				return &value;
			}
			const_pointer Address(const_reference value) const 
			{
				return &value;
			}

			size_type MaxSize() const
			{
				size_type count = static_cast<size_type>(-1) / sizeof(value_type);

				return 0 < count ? count : 1;
			}

			pointer allocate() 
			{
				pointer ret = reinterpret_cast<pointer>(m_alloc->Allocate(sizeof(value_type)));

				return ret;
			}

			pointer allocate(size_type num, const void* = 0) 
			{
				pointer ret = reinterpret_cast<pointer>(m_alloc->Allocate(num * sizeof(value_type)));

				return ret;
			}

			void deallocate(pointer p) 
			{
				Destroy(p);
				return m_alloc->Deallocate(p, sizeof(value_type));
			}
			void deallocate(pointer p, size_type num) 
			{
				return m_alloc->Deallocate(p, num * sizeof(value_type));
			}

			void Construct(pointer p)
			{
				//__Construct(p);
			}

			template<typename Arg>
			void Construct(pointer p, const Arg& value)
			{
				//__Construct(p, value);
			}

			void Destroy(pointer p) 
			{
				//__Destroy(p);
			}
		};


	}

}




#endif