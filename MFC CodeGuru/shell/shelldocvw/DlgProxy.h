// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__A773FE7B_4192_11D1_AE13_006097D60BAC__INCLUDED_)
#define AFX_DLGPROXY_H__A773FE7B_4192_11D1_AE13_006097D60BAC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CShelldocDlg;

/////////////////////////////////////////////////////////////////////////////
// CShelldocDlgAutoProxy command target

class CShelldocDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CShelldocDlgAutoProxy)

	CShelldocDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CShelldocDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShelldocDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CShelldocDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CShelldocDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CShelldocDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CShelldocDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__A773FE7B_4192_11D1_AE13_006097D60BAC__INCLUDED_)
