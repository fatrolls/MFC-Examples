// PingThread.h : header file
//
#define ICMP_ERRMSG_SIZE 8
#ifdef _DEBUG
#define PNGINBUFSIZE 512+ICMP_ERRMSG_SIZE+ECHO_REPLY_LEN 
#define PNGOUTBUFSIZE 512
#else
#define PNGINBUFSIZE 8192+ICMP_ERRMSG_SIZE+ECHO_REPLY_LEN
#define PNGOUTBUFSIZE 8192
#endif
#define LBLINESIZE 132    // list box line size

#define MAXHOSTSIZE 128
// DLL entries
typedef HANDLE (*ICMPCREATEFILE)(void);
typedef BOOL (*ICMPCLOSEHANDLE)(HANDLE);
typedef DWORD  (*ICMPSENDECHO)(HANDLE,ULONG,LPVOID,WORD,
							  LPVOID,
							  LPVOID,DWORD,DWORD);



UINT CPingThreadProc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// CPingThread thread

class CPingThread : public CWinThread
{
	DECLARE_DYNCREATE(CPingThread)
protected:
	CPingThread();           // protected constructor used by dynamic creation

// Attributes
public:
	CStringArray m_PingOutPut;
	HINSTANCE Icmpdll;
	HANDLE PingSocket;
	ICMPCREATEFILE IcmpCreateFile;
	ICMPCLOSEHANDLE IcmpCloseHandle;
	ICMPSENDECHO IcmpSendEcho;
	void CleanUp();
	BOOL RunTracert(CPingThreadParmList *lppingvars);
	CPingThread(CPingThreadParmList *lpPingvars);
	BOOL Running();
	BOOL Start();
	void Kill();
	BOOL RunPing(CPingThreadParmList *lppingvars);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPingThread)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
//protected:
public:
	virtual ~CPingThread();

	// Generated message map functions
	//{{AFX_MSG(CPingThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL TracertReply(CPingThreadParmList *lppingvars,
						struct icmp_reply *lpReply,
						UINT ttl,
						UINT probe,
						ULONG Timestamp);
	void PrintLine(LPSTR szMsg,CPingThreadParmList *lppingvars);
	//CPingThreadParmList *lpPingParms;
	//CPingThreadParmList PingThreadParms;
	BOOL ProcessReply(CPingThreadParmList *lppingvars,
						struct icmp_reply *lpReply);
	ULONG GetAddr(LPCTSTR szHost,struct in_addr *inaddr = NULL);
	BOOL Icmp_SetOpts(CPingThreadParmList *lppingvars,
						struct ipopt_info *lpIpopt,
						UCHAR *optdata,
						INT optsize);
	BOOL Icmp_Sendto(CPingThreadParmList *lppingvars,
							  CHAR *OUTBuf,
							  CHAR *INBuf,
							  struct ipopt_info *lpIpopt,
							  ULONG sendaddr,
							  INT maxoutbuffsize,
							  INT maxinbuffsize);
	BOOL Icmp_Close(HANDLE h);
	HANDLE Icmp_Open();
	//
	// Ping thread private data
	//
	BOOL bKill;
	DWORD NumberOfEchoReplies;
	
	
};

/////////////////////////////////////////////////////////////////////////////
