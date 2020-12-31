

//
// Parameter list structure passed to this thread
//
struct CPingThreadParmList
{
	HWND    m_hwndNotifyPingDone;
	LPVOID  m_mythread;
	HANDLE  m_hEventStartPing;
	HANDLE  m_hEventPingDone;
	HANDLE  m_hEventKillPing;
	HANDLE  m_hEventPingDead;
	CHAR	hostname[128];
	BOOL	opt_resolve;
	BOOL	opt_dontfragment;
	BOOL	opt_interrupt;
	BOOL    opt_rrloose;
	BOOL    opt_rrstrict;
	BOOL    opt_tracert;
	int		opt_ttl_val;
	int		opt_packetlen_val;
	int		opt_numpackets_val;
	int		opt_rroute_val;
	int		opt_timestamp_val;
	int		opt_tos_val;
	int		opt_timeout_val;
	//CStringArray m_PingOutPut;
	CStringArray opt_rrdata;
};

//
// main thread proc
//
//UINT CPingThreadProc(LPVOID lparam);