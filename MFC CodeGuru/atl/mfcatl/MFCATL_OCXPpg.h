#if !defined(AFX_MFCATL_OCXPPG_H__A9EE6E94_5F04_11D1_934C_E4CFDA000000__INCLUDED_)
#define AFX_MFCATL_OCXPPG_H__A9EE6E94_5F04_11D1_934C_E4CFDA000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MFCATL_OCXPpg.h : Declaration of the CMFCATL_OCXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXPropPage : See MFCATL_OCXPpg.cpp.cpp for implementation.

class CMFCATL_OCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMFCATL_OCXPropPage)
	DECLARE_OLECREATE_EX(CMFCATL_OCXPropPage)

// Constructor
public:
	CMFCATL_OCXPropPage();

// Dialog Data
	//{{AFX_DATA(CMFCATL_OCXPropPage)
	enum { IDD = IDD_PROPPAGE_MFCATL_OCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMFCATL_OCXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCATL_OCXPPG_H__A9EE6E94_5F04_11D1_934C_E4CFDA000000__INCLUDED)
