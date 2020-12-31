// Gallery.h : header file
//

#ifndef GALLERY_H
#define GALLERY_H

#include "ROEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CGallery dialog

class CGallery : public CDialog
{
// Construction
public:
	CGallery(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGallery();

// Dialog Data
	//{{AFX_DATA(CGallery)
	enum { IDD = IDD_GALLERY };
	CROEdit	m_Edit;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGallery)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_font;

	// Generated message map functions
	//{{AFX_MSG(CGallery)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif //GALLERY_H
