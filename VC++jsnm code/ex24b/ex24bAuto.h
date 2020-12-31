#ifndef __EX24BAUTO_H__
#define __EX24BAUTO_H__

// Ex24bAuto.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CEx24bAuto command target

class CEx24bAuto : public CCmdTarget
{
	DECLARE_DYNCREATE(CEx24bAuto)

	CEx24bAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24bAuto)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEx24bAuto();

	// Generated message map functions
	//{{AFX_MSG(CEx24bAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CEx24bAuto)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CEx24bAuto)
	long m_lData;
	afx_msg void OnLongDataChanged();
	VARIANT m_vaTextData;
	afx_msg void OnTextDataChanged();
	afx_msg BOOL DisplayDialog();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __EX24BAUTO_H__
