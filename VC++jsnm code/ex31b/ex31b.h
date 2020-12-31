#if !defined(AFX_EX31B_H__209D8D55_9566_11D0_85BF_8BCD68D6DF70__INCLUDED_)
#define AFX_EX31B_H__209D8D55_9566_11D0_85BF_8BCD68D6DF70__INCLUDED_

// EX31B.H - Header file for your Internet Server
//    ex31b Filter

#include "resource.h"


class CEx31bFilter : public CHttpFilter
{
public:
	CEx31bFilter();
	~CEx31bFilter();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CEx31bFilter)
	public:
	virtual BOOL GetFilterVersion(PHTTP_FILTER_VERSION pVer);
	virtual DWORD OnReadRawData(CHttpFilterContext* pCtxt, PHTTP_FILTER_RAW_DATA pRawData);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx31bFilter)
	//}}AFX_MSG
private:
	HWND m_hWndDest;
	HANDLE m_hProcessDest;
	void SendTextToWindow(char* pchData);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX31B_H__209D8D55_9566_11D0_85BF_8BCD68D6DF70__INCLUDED)
