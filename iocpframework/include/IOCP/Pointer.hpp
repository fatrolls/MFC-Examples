#ifndef __IOCP_POINTER_HPP
#define __IOCP_POINTER_HPP


namespace async
{


	namespace IOCP
	{

		//-----------------------------------------------------
		// class pointer
		// 引用计数指针

		template<typename T>
		class pointer 
		{
		private:
			T *m_pObject;

		public:
			pointer(T *t)
			{
				_Bind(t);
			}
			template<typename U>
			pointer(U *p)
			{
				_Bind(p);
			}

			pointer(const pointer<T> &t)
			{
				_Bind(t.Get());
			}
			template<typename U>
			pointer(const pointer<U> &u)
			{
				_Bind(u.Get());
			}

			~pointer()
			{		
				_Unbind();
			}


			pointer<T> &operator=(T *t)
			{
				_Unbind();
				_Bind(t);

				return *this;
			}
			template<typename U>
			pointer<T> &operator=(U *p)
			{
				_Unbind();
				_Bind(p);

				return *this;
			}

			pointer<T> & operator=(const pointer<T> &t)
			{
				_Unbind();
				_Bind(t.Get());

				return *this;
			}
			template<typename U>
			pointer<T> & operator=(const pointer<U> &u)
			{
				if( m_pObject != u.Get() ) 
				{
					_Unbind();
					_Bind(u.Get());
				}

				return *this;
			}


			T &operator*()
			{
				return *m_pObject;
			}
			T &operator*() const
			{
				return *m_pObject;
			}
			T *operator->()
			{
				return m_pObject;
			}
			T *operator->() const
			{
				return m_pObject;
			}

			T *Get()
			{
				return m_pObject;
			}
			T *Get() const
			{
				return m_pObject;
			}


			bool operator==(const pointer<T> &t) const
			{
				return m_pObject == t.Get();
			}

			bool operator!=(const pointer<T> &t) const
			{
				return m_pObject != t.Get();
			}



			template<typename U>
			bool operator==(const pointer<U> &u) const
			{
				return m_pObject == u.Get();
			}

			template<typename U>
			bool operator!=(const pointer<U> &u) const
			{
				return m_pObject != u.Get();
			}

		private:
			void _Bind(T *p)
			{
				p->AddRef();
				m_pObject = p;
			}
			template<typename U>
			void _Bind(U *p)
			{
				p->AddRef();
				m_pObject = reinterpret_cast<T *>(p);
			}

			void _Unbind()
			{		
				m_pObject->Release();
			}

		};


	}


}




#endif