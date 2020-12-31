struct CInetThreadParms
{
	HWND    m_hwndNotifyInetDone;
	LPVOID  m_mythread;
	HANDLE  m_hEventStartInet;
	HANDLE  m_hEventInetDone;
	HANDLE  m_hEventKillInet;
	HANDLE  m_hEventInetDead;
	BOOL ipstats;
	BOOL ifstats;
	BOOL icmpstats;
	BOOL tcpstats;
	BOOL udpstats;
	BOOL connections;
	BOOL routtable;
	BOOL allopts;
	BOOL resolveaddrs;
}; 


