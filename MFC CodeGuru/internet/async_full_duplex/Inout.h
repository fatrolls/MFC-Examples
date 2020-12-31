#ifndef _INOUT_H_
#define _INOUT_H_

#include "messageq.h"

typedef void (InOutCallbackFunc)(void* param);

class CInOutConnection
{
	public:
		CInOutConnection();
		~CInOutConnection();

		//Public data
		enum {DEFAULT_FRAME = 0x76453201};//DWORD
		enum {DEFAULT_HEADER_SIZE = 8};//DWORD
		enum {DEFAULT_TIMEOUT = 3600, NO_TIMEOUT = 0xFFFFFFFF};//DWORD - timeout in seconds
		enum {NUMBER_OF_THREADS = 4};
		DWORD TimeOutInit;
		//timeout guard
		CRITICAL_SECTION timeoutGuard;
		DWORD TimeOutCounter;
		long CurrentThreadCount;

		virtual BOOL CreateThreads();
		virtual BOOL CreateThreadsEx(){return TRUE;};
		virtual BOOL WaitThreadsToStart();

		//adding callbacks and listening windows
		void SetCallbackFunction(void* newFunc);
		void ClearCallBackFunction();
		void SetCallbackWindow(HWND window, int MessageId);
		void ClearCallbackWindow();

		virtual void SetTerminate();
		virtual BOOL Terminate();
		virtual void WaitForTermination();
		HANDLE GetTerminateHandle(){return m_IsTerminated;};
		//queue
		CMessageQueue* GetInQueue(){return &InQueue;};
		CMessageQueue* GetOutQueue(){return &OutQueue;};
		//message preprocessing
		virtual void PreprocessIncomingMessage(void* message, int length);
		virtual void PreprocessOutgoingMessage(void* message);

		//Idle action
		virtual void OnSyncThreadIdle();
		virtual void OnInThreadIdle();
		virtual void OnOutThreadIdle();
		virtual void OnServiceTimer(); //called each second from service thread

		//Error messages handlers
		virtual void OnInThreadError();
		virtual void OnOutThreadError();
		//thread initialization rutines
		virtual BOOL InitInThread();
		virtual BOOL InitOutThread();
		virtual BOOL InitSyncThread();
		//thread termination status
		virtual void InThreadTerminated();
		virtual void OutThreadTerminated();
		virtual void SyncThreadTerminated();
		//send/receive message attributes
		virtual void* InternalReceiveMessage(int* Error, int* length);
		virtual void* cioReceiveMessage(int* Error, int* length);
		virtual BOOL cioSendMessage(void* msg, int msg_size);

		virtual void* PrepareMessageToSend(void* msg, DWORD length, DWORD& len);
		virtual int GetHeaderLength();
		virtual BOOL IsCorrectHeader(char* header);
		virtual int GetMessageSizeFromHeader(char* header);
		//message process routines
		virtual void ProcessMessage();
		virtual void ProcessCurrentMessage(void* msg, DWORD length);
		//connection validity
		virtual BOOL IsConnectionValid();
		virtual void ResetConnection();
		//thread bookkeeping
		virtual void AddThread(){::InterlockedIncrement(&CurrentThreadCount);};
		virtual void RemoveThread(){::InterlockedDecrement(&CurrentThreadCount);};
		virtual int GetAllThreadsCount(){return NUMBER_OF_THREADS;};

	protected:
		CMessageQueue InQueue;
		CMessageQueue OutQueue;
		//terminate event
		HANDLE m_IsTerminated;
		//window callback
		HWND callbackWindow;
		int MsgId;
		//callback function
		void* CallbackFunc;
};

#endif
