#ifndef __IOCP_DISPATCHER_HPP
#define __IOCP_DISPATCHER_HPP


#include "Object.hpp"

#include "IOCP.hpp"
#include <vector>



namespace async
{

	namespace IOCP 
	{
		struct AsyncResult;
		typedef pointer<AsyncResult> AsyncResultPtr;

		typedef std::tr1::function<void(const AsyncResultPtr &asyncResult)> AsyncCallbackFunc;


		//---------------------------------------------------------------------------
		// class AsyncResult
		// 间接层，负责缓冲区、收发者和回调函数

		struct AsyncResult
			: public OVERLAPPED
			, public Object
		{
			AsyncResult::AsyncResult(const ObjectPtr &sender, const ObjectPtr &buffer,
				const ObjectPtr &asyncState, const ObjectPtr &internalState, const AsyncCallbackFunc &callback)
				: m_sender(sender), m_buffer(buffer), m_asynState(asyncState), m_internalState(internalState), m_callback(callback)
			{
				RtlZeroMemory((OVERLAPPED *)this, sizeof(OVERLAPPED));
			}

			ObjectPtr	m_sender;
			ObjectPtr	m_buffer;
			ObjectPtr	m_asynState;
			ObjectPtr	m_internalState;
			AsyncCallbackFunc m_callback;

		private:
			AsyncResult();
		};


		// -----------------------------------------------------------------
		// 获取系统合适的线程数
		extern size_t GetFitThreadNum(size_t perCPU = 2);



		//------------------------------------------------------------------
		// class IODispatcher
		// 完成端口实现

		class IODispatcher
		{
		public:
			// 线程容器类型
			typedef std::vector<HANDLE>		Threads;
			typedef Threads::iterator		ThreadsIter;

		private:
			// IOCP Handle
			CIOCP m_hIOCP;
			// 线程容器
			std::vector<HANDLE>	m_threads;

		public:
			IODispatcher(size_t numThreads = 0);
			~IODispatcher();

		public:
			// 绑定设备到完成端口
			void Bind(HANDLE hObject);
			// 向完成端口投递请求
			void Post(const AsyncResultPtr &ar);

			// 停止服务
			void Stop();

		private:
			void _ThreadIO();

		private:
			static size_t WINAPI _ThreadIOImpl(LPVOID pObj);
		};
	}


}


#endif