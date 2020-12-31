#pragma once


/////////////////////////////////////////////////////////////////////////////
// CMCCtrl window
class CPopupCalendar;

class CMCCtrl : public CMonthCalCtrl
{
// Construction
public:
	CMCCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMCCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMCCtrl();

	inline void SetPopupCalendar(CPopupCalendar	*pPopupCalendar)
	{
		m_pPopupCalendar = pPopupCalendar;
	}
	// Generated message map functions
protected:
	//{{AFX_MSG(CMCCtrl)
	afx_msg void OnSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CPopupCalendar	*m_pPopupCalendar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
