#if !defined(AFX_PROPPAGE_H__93FA2B36_1A5D_4897_8880_D41FA8F670F8__INCLUDED_)
#define AFX_PROPPAGE_H__93FA2B36_1A5D_4897_8880_D41FA8F670F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPage dialog

class CPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPage)

// Construction
public:
	CPropPage();
	~CPropPage();

// Dialog Data
	//{{AFX_DATA(CPropPage)
	enum { IDD = IDD_PROPPAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE_H__93FA2B36_1A5D_4897_8880_D41FA8F670F8__INCLUDED_)
