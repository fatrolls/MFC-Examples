// MyPropertyPage1.h : header file
//

#ifndef __MYPROPERTYPAGE1_H__
#define __MYPROPERTYPAGE1_H__

#include	"cdxCSizingDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage1 dialog

class CMyPropertyPage1 : public cdxCSizingPropPage
{
	DECLARE_DYNCREATE(CMyPropertyPage1)

// Construction
public:
	CMyPropertyPage1();
	virtual ~CMyPropertyPage1();

// Dialog Data
	//{{AFX_DATA(CMyPropertyPage1)
	enum { IDD = IDD_PROPPAGE1 };
	CEdit	m_wndEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage1)
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive( );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage2 dialog

class CMyPropertyPage2 : public cdxCSizingPropPage
{
	DECLARE_DYNCREATE(CMyPropertyPage2)

// Construction
public:
	CMyPropertyPage2();
	virtual ~CMyPropertyPage2();

// Dialog Data
	//{{AFX_DATA(CMyPropertyPage2)
	enum { IDD = IDD_PROPPAGE2 };
	CScrollBar	m_wndVScroll;
	CScrollBar	m_wndHScroll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage2)
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive( );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __MYPROPERTYPAGE1_H__
