#ifndef PINGPARMLIST
#define PINGPARMLIST

typedef struct CPingParmListTag
{
	LPVOID  m_Events;
	HANDLE  m_hEventStartPing;
	HANDLE  m_hEventPingDone;
	HANDLE  m_hEventKillPing;
	HANDLE  m_hEventPingDead;
	HANDLE  PingSocket;
	HINSTANCE Icmpdll;
	CHAR	hostname[128];
	BOOL	bKill;
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
	
}CPingParmList,*PPINGPARMLIST;



#endif