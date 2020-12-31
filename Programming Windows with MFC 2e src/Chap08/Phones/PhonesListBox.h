#if !defined(AFX_PHONESLISTBOX_H__7BE4B250_90ED_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_PHONESLISTBOX_H__7BE4B250_90ED_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhonesListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhonesListBox window

class CPhonesListBox : public CListBox
{
// Construction
public:
	CPhonesListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhonesListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	void NewEntry();
	virtual ~CPhonesListBox();

	// Generated message map functions
protected:
	CFont m_font;
	//{{AFX_MSG(CPhonesListBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditItem();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONESLISTBOX_H__7BE4B250_90ED_11D2_8E53_006008A82731__INCLUDED_)
