
extern CDaoDatabase* InitializeDAO();
extern void TerminateDAO(CDaoDatabase* pDB);
extern DWORD WaitAndPumpMessages(HANDLE hWait, DWORD dwTimeout);


extern _AFX_DAO_STATE* AFX_CDECL AfxGetDaoState();
extern DWORD dwDBEngineSlot;


class _AFX_DAO_STATE : public CNoTrackObject
{
public:
	// Handle initialization and cleanup of OLE and DAO
	_AFX_DAO_STATE();
	virtual ~_AFX_DAO_STATE();

	// MFC/DAO global data
	BOOL m_bOleInitialized;
	DAODBEngine* m_pDAODBEngine;
	CMapPtrToPtr m_mapWorkspaces;
};
