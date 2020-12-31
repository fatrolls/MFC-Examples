#if !defined(AFX_PG2_H__DE9611DD_F003_11D1_A7E2_E88B6FC70000__INCLUDED_)
#define AFX_PG2_H__DE9611DD_F003_11D1_A7E2_E88B6FC70000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Pg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPg2 dialog

class CPg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPg2)

// Construction
public:
	CPg2();
	~CPg2();

// Dialog Data
	//{{AFX_DATA(CPg2)
	enum { IDD = IDD_PAGE2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPg2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PG2_H__DE9611DD_F003_11D1_A7E2_E88B6FC70000__INCLUDED_)
