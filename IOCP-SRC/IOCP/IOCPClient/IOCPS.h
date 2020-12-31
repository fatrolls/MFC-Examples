// IOCPS.h: interface for the IOCPS class. V 1.15
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCPS_H__4D63F25E_B852_46D7_9A42_CF060F5E544D__INCLUDED_)
#define AFX_IOCPS_H__4D63F25E_B852_46D7_9A42_CF060F5E544D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Determines the size of the first bytes who tells you how big the message are. (pakage heap)  
#define MINIMUMPACKAGESIZE sizeof(UINT)
#define MAXIMUMPACKAGESIZE 512
#define MAXIMUMSEQUENSENUMBER 5001
#define MAXIMUMPAYLOADSIZE MAXIMUMPACKAGESIZE-MINIMUMPACKAGESIZE


#define IOCPSERVERVERSION "IOCP Server/Client system written by Amin Gholiha. Copyright (C) 2005"
#define TRANSFERFILEFUNCTIONALITY  // to use filetransfer (transmitfile function) 

/*
*  Add this if you whant to be able to block sertain IP address or
*  just allow one connection per IP.
*/
#define SIMPLESECURITY


// Winsock 2. Works only under Win XP and Win NT2k. 
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "mswsock.h"

#include "IOCPBuffer.h"


#include "afxmt.h" // CCritical section.. 


// CMAP 
#include <afxtempl.h>



class CIOCPBuffer;
struct ClientContext;


template<>
inline UINT AFXAPI HashKey(unsigned int& key)
{
	// default identity hash - works for most primitive values
	return ((UINT)(void*)(unsigned int)key) >> 4;
}

typedef CMap<unsigned int, unsigned int&, ClientContext*, ClientContext* > ContextMap;
typedef CMap<unsigned int, unsigned int&, CIOCPBuffer *, CIOCPBuffer * > BufferMap;

/*
* Type of operations. 
*
*/
enum IOType 
{
	IOInitialize, // The client just connected
	IORead, // Read from the client. 
	IOReadCompleted, // Read completed
	IOWrite, // Write to the Client
	IOWriteCompleted, // Write Completed.
	IOZeroByteRead, // Read zero Byte from client (dummy for avoiding The System Blocking error) 
	IOZeroReadCompleted, // Read Zero Byte  completed. (se IOZeroByteRead)
	IOTransmitFileCompleted, //TransmitFileCompleted.
	IOPostedPackage, // Used to post Packages into IOCP port. 
};

enum JobType
{
	Job_SendText2Client,
	Job_SendFileInfo,
	Job_StartFileTransfer,
	Job_AbortFileTransfer
};

/*
* This is what We put in the JobQueue
*
*
*/

struct JobItem
{
	JobType m_command;
	unsigned int m_ClientID;
	CString m_Data;
};



/*
* This struct is used to past around some information about the 
* client. 
*
*/
struct ClientContext
{
	SOCKET				m_Socket; // The Connection socket. 
	CCriticalSection m_ContextLock; // The lock used to update and read variabels. 
	unsigned int			m_ID; // Reserved for DisconnectClient if needed. 
	int					m_nNumberOfPendlingIO; // Very Important variable used with ReleaseClientContext. (Avoids Access Violation)
	//
	// Send in order variables. 
	//
	unsigned int					m_SendSequenceNumber;
	unsigned int					m_CurrentSendSequenceNumber;
	BufferMap						m_SendBufferMap;
	//
	// Read in order variables
	//
	unsigned int					m_ReadSequenceNumber;
	unsigned int					m_CurrentReadSequenceNumber;
	BufferMap						m_ReadBufferMap;
	//
	// File transfer stuff. 
	//
#ifdef TRANSFERFILEFUNCTIONALITY	
	CFile m_File;
	unsigned int m_iMaxFileBytes;
	unsigned int m_iFileBytes; 
	BOOL m_bFileSendMode;
	BOOL m_bFileReceivedMode;
#endif

	// Package Overlapped Buffer..
	// Used to get a complete package when we have several pending reads. 
	CIOCPBuffer* m_pBuffOverlappedPackage;	

	// Extra info you can put what ever you whant here.. 
	CString m_sReceived;
	int m_iNumberOfReceivedMsg;
	BOOL m_bUpdate;

};



class IOCPS  
{

private:
	// Aborts A socket without removing it from contextmap.	
	inline void AbortiveClose(ClientContext *mp);
	// Adds nSize bytes to buffer and flush the other buffer. 
	inline BOOL AddAndFlush(CIOCPBuffer *pFromBuff, CIOCPBuffer *pToBuff, UINT nSize);
	// Add a client Context to hashMap,.
	inline BOOL AddClientContext(ClientContext* mp);
	// Allocates a ClientContext and return a pointer ot it. 
	inline ClientContext* AllocateContext();
	// Do a Asyncorn Read.
	inline BOOL ARead(ClientContext *pContext,CIOCPBuffer *pOverlapBuff=NULL);
	// Used to bin sockets to Completionport. 
	inline BOOL AssociateSocketWithCompletionPort(SOCKET socket, HANDLE hCompletionPort, DWORD dwCompletionKey);
	// Makes tha last peperation for an connection so IOWORKER can start to work with it. 
	inline BOOL AssociateIncomingClientWithContext(SOCKET clientSocket);
	// Unlocks the memory used by the overlapped IO, to avoid WSAENOBUFS problem. 
	inline BOOL AZeroByteRead(ClientContext *pContext,CIOCPBuffer *pOverlapBuff);
	// Creates a CreateCompletionPort
	inline BOOL CreateCompletionPort();
	// Functions used to post request into IOCP (simulate received packages)
	BOOL PostPackage(ClientContext *pContext,CIOCPBuffer *pOverlapBuff);

#if defined TRANSFERFILEFUNCTIONALITY	
	inline void AddToFile(ClientContext *pContext, DWORD dwIoSize, CIOCPBuffer *pOverlapBuff);
	inline void OnTransmitFileCompleted(ClientContext *pContext, CIOCPBuffer *pOverlapBuff);
	// DO an Transmitfile.
	inline BOOL StartSendFile(ClientContext *pContext);
	// Perpares for file receive
	inline BOOL PrepareReceiveFile(ClientContext *pContext, LPCTSTR lpszFilename,DWORD dwFileSize);
	// Perpared for file send
	inline BOOL PrepareSendFile(ClientContext *pContext, LPCTSTR lpszFilename);
	// Disables file send
	inline BOOL DisableSendFile(ClientContext *pContext);
	// Disables file receive. 
	inline BOOL DisableReceiveFile(ClientContext *pContext);
#endif	


#ifdef SIMPLESECURITY	
public:
	void OneIPPerConnection(BOOL bVal=TRUE);
protected: 
	CCriticalSection m_OneIPPerConnectionLock;
	CPtrList m_OneIPPerConnectionList;
	CCriticalSection m_BanIPLock;
	CPtrList m_BanIPList;

	static int CALLBACK ConnectAcceptCondition(IN LPWSABUF lpCallerId,
		IN LPWSABUF lpCallerData,
		IN OUT LPQOS lpSQOS,
		IN OUT LPQOS lpGQOS,
		IN LPWSABUF lpCalleeId, 
		OUT LPWSABUF lpCalleeData,
		OUT GROUP FAR *g,
		IN DWORD dwCallbackData);

	void ClearBanList();
	//inline void DisconnectIfBanned(SOCKET &Socket);
	inline BOOL IsInBannedList(sockaddr_in* pCaller);
	inline BOOL IsAlreadyConnected(sockaddr_in* pCaller);

	// Disconnect immediately  if the incoming IP already exist. 
	//inline void DisconnectIfIPExist(SOCKET &Socket);
	inline void AddToBanList(SOCKET &Socket);
private: 

#endif
	// Clears the memory of the ClientContext (Also disconnects) 
	inline void FreeClientContext();
	// Disconnects A client. 
	inline void DisconnectClient(ClientContext* pContext, BOOL bGraceful=FALSE);
	// Used to avoid access violation..
	inline int ExitIOLoop(ClientContext *pContext);
	// Used to avoid access violation..
	inline void EnterIOLoop(ClientContext *pContext);
	// clear the memory of the buffers. Should only be called when no pendling operations are in use. 
	inline void FreeBuffers();
	// Used to  avoid inorder packages (if you are useing more than one I/O Worker Thread)  
	inline CIOCPBuffer * GetNextReadBuffer(ClientContext *pContext,CIOCPBuffer *pBuff=NULL);
	// Used to  avoid inorder packages (if you are useing more than one I/O Worker Thread)  
	inline CIOCPBuffer* GetNextSendBuffer(ClientContext *pContext,CIOCPBuffer *pBuff=NULL);
	inline void IncreaseSendSequenceNumber(ClientContext *pContext);
	inline void IncreaseReadSequenceNumber(ClientContext *pContext);
	// Used to avoid inorder Read packages
	inline void MakeOrderdRead(ClientContext *pContext,CIOCPBuffer *pBuff);


	// Used by IO Workers. 
	inline void OnWriteCompleted(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff);
	inline void OnWrite(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff);
	inline void OnReadCompleted(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff=NULL);
	inline void OnRead(ClientContext *pContext,CIOCPBuffer *pOverlapBuff=NULL);
	inline void OnInitialize(ClientContext* pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff=NULL);
	inline void OnPostedPackage(ClientContext *pContext,CIOCPBuffer *pOverlapBuff);


	// Used to avoid SYSTEM Blocking Bugg. 
	inline void OnZeroByteReadCompleted(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff=NULL);
	inline void OnZeroByteRead(ClientContext *pContext,CIOCPBuffer *pOverlapBuff=NULL);
	// Process the internal messages. 
	inline void ProcessIOMessage(CIOCPBuffer *pOverlapBuff, ClientContext* pContext, DWORD dwSize);	
	// Process received Packages 
	inline void ProcessPackage(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff);
	// Used to clean up the Send and receive hash map. 
	// Deletes the ClientContext or just put it in the FreeClientContext list. 
	inline BOOL ReleaseClientContext(ClientContext *pContext);
	// Release buffers. 
	inline void ReleaseBufferMap(BufferMap *map);
	//Closes The Worker Threads
	inline void ShutDownWorkers();
	// Closes The IO Workers
	inline void ShutDownIOWorkers();
	//  Splits a buffer into two. Used to handle halffinished received messages. 
	inline CIOCPBuffer * SplitBuffer(CIOCPBuffer * pBuff,UINT nSize);
	// Used to avoid inorder package.
	inline void SetSendSequenceNumber(ClientContext *pContext,CIOCPBuffer *pBuff);
	// Worker, Listener, IOWorker.  
	static UINT WorkerThreadProc(LPVOID pParam);
	static UINT IOWorkerThreadProc(LPVOID pParam);
	static UINT ListnerThreadProc(LPVOID pParam);
	//Signals No more Accepting Connections.. 
	BOOL m_bServerStarted;

	//Signals ShutDown
	volatile BOOL m_bShutDown;
	//Signals No more Accepting Connections.. 
	volatile BOOL m_bAcceptConnections;
	// Signals No more Jobs. 
	volatile BOOL m_bAcceptJobs;
	// Används för att binda alla socets till GetQueuedCompletionStatus
	HANDLE					m_hCompletionPort;
	// Om vi får en connecction request.. 
	HANDLE					m_hEvent; 
	// Socket som vi använder för att lyssna... 
	SOCKET					m_socListen;   
	// Tråden som lyssnar på connections 

	CWinThread* m_pListenThread;

	// IO Worker Thread list. 
	CPtrList m_IOWorkerList;

	// Creating Context and sockets are expencive therefor we have this list.
	// All the dead connection are placed in this list for reuse. 
	CCriticalSection m_FreeContextListLock;
	CPtrList m_FreeContextList;


	// Free Buffer List.. 
	CCriticalSection m_FreeBufferListLock;
	CPtrList m_FreeBufferList;

	// OccupiedBuffer List.. (Buffers that is currently used) 
	CCriticalSection m_BufferListLock;
	CPtrList m_BufferList;


	// Maximum number of buffer which is not used. 
	int m_iMaxNumberOfFreeBuffer;

	// Maximum number of Contexts who is in the FreeContextList
	int m_iMaxNumberOfFreeContext;
	// The server version 
	CString m_sServerVersion;
	// Starts Thi IOCP Workers. 
	BOOL SetupIOWorkers();
	// Starts The Connection Listner Thread. 
	BOOL SetupListner();

	// Contains the result of winsock init. 
	int m_iWSAInitResult;

	// Number of IOWorkers running..
	int m_nIOWorkers;
	// Number of IOWorker. 
	int m_iMaxIOWorkers;
	// Maximum Number of Connections. 
	int m_iMaxNumConnections;

	// Port number. 
	int m_nPortNumber; 

	// Number of Workers running intitially. 
	int m_nOfWorkers;

	// Workqueue used with the ThreadPool.
	CCriticalSection m_JobQueueLock;
	CPtrList m_JobQueueList;

	// We save our workers here. 	
	CMapWordToPtr m_WorkerThreadMap;
	CCriticalSection m_WorkerThreadMapLock;
	// One ipPerConnection 
	BOOL m_bOneIPPerConnection;
	// Number of Pendling Reads, used for performance
	int m_iNumberOfPendlingReads;
	// When Set to TRUE Reads are processed In Order.. 
	BOOL m_bReadInOrder;
	// Make the sends in order. 
	BOOL m_bSendInOrder;
	// get a pointer to the worker given the worker ID. (Warning DWORD->Word conversion Error ? )
	CWinThread* GetWorker(WORD WorkerID);

public: 

	// Functions used to post request into IOCP (simulate received packages)
	BOOL PostPackage(int iClientId, CIOCPBuffer *pOverlapBuff);
	// Enable SYN-Flood protection in registry. 
	BOOL XPNTSYNFloodProtection(int iValue=0,int iTcpMaxHalfOpen=100, int iTcpMaxHalfOpenRetried=80, int iTcpMaxPortsExhausted=5,int  iTcpMaxConnectResponseRetransmissions=3);

#if defined TRANSFERFILEFUNCTIONALITY

	BOOL PrepareSendFile(SOCKET clientSocket, CString Filename);
	BOOL DisableSendFile(SOCKET ClientId);
	BOOL DisableReceiveFile(SOCKET clientSocket);
	BOOL PrepareReceiveFile(SOCKET clientSocket, LPCTSTR lpszFilename,DWORD dwFileSize);
	// DO an Transmitfile.
	BOOL StartSendFile(SOCKET clientSocket);
#endif

	// Returns TRUE if The server/client are started. 
	BOOL IsStarted();
	int GetNumberOfConnections();
	// Returns the Ip Adress of a Remote hoste given the Socket, 
	CString GetHostAddress(SOCKET socket);
	// Send the Data in pBuff to all the clients. 
	BOOL ASendToAll(CIOCPBuffer *pBuff);
	// Disconnect A client. 
	void DisconnectClient(unsigned int iID);
	// Connects to A IP Adress. 
	BOOL Connect(const CString& strIPAddr, int nPort);
	// Return the computers IP Address. 
	CString GetHostIP();
	// Starts the server, 
	BOOL Start(int nPort=999,int iMaxNumConnections=1201,int iMaxIOWorkers=1,int nOfWorkers=0,int iMaxNumberOfFreeBuffer=100,int iMaxNumberOfFreeContext=50,BOOL bOrderedSend=TRUE, BOOL bOrderedRead=TRUE,int iNumberOfPendlingReads=5);

	IOCPS();
	virtual ~IOCPS();

	// Called to do some work. 
	virtual inline void ProcessJob(JobItem *pJob,IOCPS* pServer);
	// Get a Job. 
	JobItem* GetJob();
	// Adds a job to the queue. 
	BOOL AddJob(JobItem *pJob);
	// Clear the Job from the heap. 
	inline void FreeJob(JobItem *pJob);

	// Sets the number of Workers can be called anytime. 
	BOOL SetWorkers(int nThreads);

	// Disconnects all the clients. 
	void DisconnectAll();

	BOOL ASend(int ClientId,CIOCPBuffer *pOverlapBuff);



	// Finds a clien in the Client context Hashmap (NOT THREAD SAFE)..
	ClientContext* FindClient(unsigned iClient);

	// ShutDowns The Server. 
	void ShutDown();

	// Starts the server. 
	BOOL Startup();

	// We put all the Context (Open connections) into this String2Pointer HashMap. 
	CCriticalSection m_ContextMapLock;
	ContextMap m_ContextMap;

	// return the Key (The hostnamn+ socketnr) of a socket. (must be Unique). 
	CString GetHostKeyName(SOCKET socket);	
protected:
	volatile int m_NumberOfActiveConnections;
	// Called when a new connection have been established.. 
	virtual void NotifyNewConnection(ClientContext *pcontext);
	// Called when a empty ClientContext structure are allocated. 
	virtual void NotifyNewClientContext(ClientContext *pContext);
	// A client have Disconnected. 
	virtual void NotifyDisconnectedClient(ClientContext *pContext);
	// File send/Transefer Completed. 
	virtual void NotifyFileCompleted(ClientContext *pcontext);
	// A Package have arrived. 
	virtual inline void NotifyReceivedPackage(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	// An ClientContext is going to be deleted insert more cleanup code if nesseary.  
	virtual void NotifyContextRelease(ClientContext *pContext);
	// An Write have been Completed
	virtual inline void NotifyWriteCompleted(ClientContext *pContext, DWORD dwIoSize,CIOCPBuffer *pOverlapBuff);
	// Used for log
	virtual void AppendLog(CString msg);
	// Do a Asyncorn Send. Never call this function outside of Notifyxxxx(...) functions. 
	BOOL ASend(ClientContext *pContext,CIOCPBuffer *pOverlapBuff);

	// deletes the buffer or just put it in the FreeBufferList to optimze performance. 
	BOOL ReleaseBuffer(CIOCPBuffer *pBuff);

	// Creates a new buffer or returns a buffer from the FreeBufferList and configure the buffer. 
	CIOCPBuffer* AllocateBuffer(int nType);

	// Error Convertion.. 
	CString ErrorCode2Text(DWORD dw);


};

#endif // !defined(AFX_MYIOCPSERVER_H__4D63F25E_B852_46D7_9A42_CF060F5E544D__INCLUDED_)
