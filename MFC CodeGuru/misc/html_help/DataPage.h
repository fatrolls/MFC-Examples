#if !defined(AFX_DATAPAGE_H__8CE99832_B818_11D1_B855_444553540000__INCLUDED_)
#define AFX_DATAPAGE_H__8CE99832_B818_11D1_B855_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DataPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataPage dialog

class CDataPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataPage)

// Construction
public:
	CDataPage();
	~CDataPage();

// Dialog Data
	//{{AFX_DATA(CDataPage)
	enum { IDD = IDD_DATA };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPAGE_H__8CE99832_B818_11D1_B855_444553540000__INCLUDED_)
