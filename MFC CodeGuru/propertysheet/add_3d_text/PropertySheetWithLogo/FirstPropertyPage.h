#if !defined(AFX_FIRSTPROPERTYPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_FIRSTPROPERTYPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FirstPropertyPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirstPropertyPage dialog

class CFirstPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFirstPropertyPage)

// Construction
public:
	CFirstPropertyPage();
	~CFirstPropertyPage();

// Dialog Data
	//{{AFX_DATA(CFirstPropertyPage)
	enum { IDD = IDD_PROPERTYSHEETWITHLOGO_DIALOG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFirstPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFirstPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTPROPERTYPAGE_H__D17EA811_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
