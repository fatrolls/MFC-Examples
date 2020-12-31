#if !defined(AFX_DLGROTATE_H__4DDB3383_9804_11D5_8DD4_D76CCF55323D__INCLUDED_)
#define AFX_DLGROTATE_H__4DDB3383_9804_11D5_8DD4_D76CCF55323D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRotate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRotate dialog

class DlgRotate : public CDialog
{
// Construction
public:
	DlgRotate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRotate)
	enum { IDD = IDD_DIALOG1 };
	float	m_angle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRotate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgRotate)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROTATE_H__4DDB3383_9804_11D5_8DD4_D76CCF55323D__INCLUDED_)
