#ifndef _MESSAGEQ_H_
#define _MESSAGEQ_H_

#include <vector>

using namespace std;

typedef struct SSingleMessage
{
	void* message;
	DWORD length;
}SSingleMessage;

class CMessageQueue
{
	public:
		CMessageQueue();
		~CMessageQueue();
		unsigned long InsertMessage(void* Msg, DWORD length, unsigned long pos);
		unsigned long AddMessage(void* Msg, DWORD length);
		unsigned long AddSingleMessage(void* Msg, DWORD length);
		void* GetMessage(unsigned long Num, DWORD& length);
		void* PeekMessage(unsigned long Num, DWORD& length);
		void* GetFirstMessage(DWORD& length);
		unsigned long GetMsgCount();
		void DeleteAllMessages();
		void RemoveAllMessages();
		void DeleteMessage(unsigned long Num);
		void RemoveMessage(unsigned long Num);
		BOOL IsMsgValid(unsigned long Num);
		void BlockQueue();
		void UnBlockQueue();
		void SetQueueFlag();
		HANDLE GetQueueFlag(){return QueueFull;};
		BOOL IsQueueFull(){return (WaitForSingleObject(QueueFull, 0) == WAIT_OBJECT_0);};
	protected:
		vector<SSingleMessage> MsgQueue;
		CRITICAL_SECTION UsageFlag;
		HANDLE QueueFull;
};

#endif