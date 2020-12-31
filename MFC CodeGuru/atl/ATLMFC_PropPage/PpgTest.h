#if !defined(AFX_PPGTEST_H__13BC2960_6570_11D1_8F98_000000000000__INCLUDED_)
#define AFX_PPGTEST_H__13BC2960_6570_11D1_8F98_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PpgTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgTest dialog

class CPpgTest : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPpgTest)

// Construction
public:
	CPpgTest();
	~CPpgTest();

// Dialog Data
	//{{AFX_DATA(CPpgTest)
	enum { IDD = IDD_OLE_PROPPAGE_LARGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgTest)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGTEST_H__13BC2960_6570_11D1_8F98_000000000000__INCLUDED_)
