#if !defined(AFX_PG1_H__DE9611DC_F003_11D1_A7E2_E88B6FC70000__INCLUDED_)
#define AFX_PG1_H__DE9611DC_F003_11D1_A7E2_E88B6FC70000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Pg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPg1 dialog

class CPg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPg1)

// Construction
public:
	CPg1();
	~CPg1();

// Dialog Data
	//{{AFX_DATA(CPg1)
	enum { IDD = IDD_PAGE1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPg1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PG1_H__DE9611DC_F003_11D1_A7E2_E88B6FC70000__INCLUDED_)
