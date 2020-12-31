#if !defined(AFX_PATHCOMBOBOX_H__710413F1_AC66_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_PATHCOMBOBOX_H__710413F1_AC66_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPathComboBox window

class CPathComboBox : public CComboBoxEx
{
// Construction
public:
	CPathComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetPath();
	BOOL SetPath (LPCTSTR pszPath);
	virtual ~CPathComboBox();

	// Generated message map functions
protected:
	void GetSubstring (int& nStart, CString& string, CString& result);
	int m_nIndexEnd;
	int m_nIndexStart;
	BOOL m_bFirstCall;
	CImageList m_il;
	//{{AFX_MSG(CPathComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHCOMBOBOX_H__710413F1_AC66_11D2_8E53_006008A82731__INCLUDED_)
