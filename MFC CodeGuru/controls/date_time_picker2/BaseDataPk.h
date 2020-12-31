#if !defined(AFX_BASEDATAPK_H__D7484F59_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
#define AFX_BASEDATAPK_H__D7484F59_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BaseDataPk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseDataPk window

class CBaseDataPk : public CStatic
{
private:
	CWnd m_pk;
	COleDateTime m_curData;
	COleDateTime m_lowData;
	COleDateTime m_highData;
    CBaseDataPk* m_pDataBuddy;  // buddy (for have a range ofvdate)
void ShowDataControl();  

 public:
 // Construction
	CBaseDataPk();
	void SetRange(COleDateTime* dt1,COleDateTime* dt2,BOOL nulvalue = FALSE,BOOL updatecurvalue = TRUE);
	void SetRange(int dayback,int dayafter,BOOL nullvalue = FALSE,BOOL updatecurvalue = TRUE);
  // create and fill control
	BOOL  SetData(UINT idc,CWnd* parent,BOOL empty = TRUE,BOOL updown = FALSE);
  // Attributes
public:
	COleDateTime* GetCurDate() { return &m_curData; }
    CBaseDataPk* GetBuddy() { return m_pDataBuddy; }
    void SetBuddy(CBaseDataPk* p) {  m_pDataBuddy = p; }
	BOOL IsNullDate()  { return (m_curData.GetStatus() == COleDateTime::null) ; }
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseDataPk)
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBaseDataPk();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBaseDataPk)
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
// 
virtual void OnDateChanged(BOOL valid);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEDATAPK_H__D7484F59_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
