// InetThread.h : header file
//




typedef BOOL (CALLBACK* SEQUERY)(BYTE,RFC1157VarBindList*,AsnInteger*,AsnInteger*);
typedef BOOL (CALLBACK* SEINIT)(DWORD,HANDLE*,AsnObjectIdentifier*);

/////////////////////////////////////////////////////////////////////////////
// CInetThread thread

class CInetThread : public CWinThread
{
	DECLARE_DYNCREATE(CInetThread)
protected:
	CInetThread();           // protected constructor used by dynamic creation
public:
	void Kill();
	HINSTANCE inetdll;
	HANDLE snmpevent;
	BOOL CleanUp();
	BOOL bKill;
	BOOL RunInet(CInetThreadParms *inetparms);
	BOOL Start();
	CInetThread(CInetThreadParms *inetparms);
	SEINIT SnmpExtensionInit;
	SEQUERY SnmpExtensionQuery;
	

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInetThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInetThread();

	// Generated message map functions
	//{{AFX_MSG(CInetThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	
		
	BOOL DoUdpStats(CInetThreadParms *inetparms);
	BOOL DoTcpStats(CInetThreadParms *inetparms);
	BOOL DoRouteTable(CInetThreadParms *inetparms);
	BOOL DoIpStats(CInetThreadParms *inetparms);
	BOOL DoIfStats(CInetThreadParms *inetparms);
	BOOL DoIcmpStats(CInetThreadParms *inetparms);
	BOOL PrintLine(CInetThreadParms *inetparms,
					CHAR * line);
	
	BOOL DoConnections(CInetThreadParms *inetparms);


	BOOL PrintConnInfo(CInetThreadParms *inetparms,
						AsnObjectIdentifier * obj,
						CHAR * conntype);
	BOOL PrintRouteInfo(CInetThreadParms *inetparms,AsnObjectIdentifier *obj);
	void Make_Oid(AsnObjectIdentifier* dst,UINT n, UINT* src);
	void Free_Var(RFC1157VarBind *var);

};

/////////////////////////////////////////////////////////////////////////////
