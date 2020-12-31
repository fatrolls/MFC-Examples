#if !defined(AFX_FILESDROPSOURCE_H__6CB3A95B_082F_4B39_928E_86E2D44A5A1F__INCLUDED_)
#define AFX_FILESDROPSOURCE_H__6CB3A95B_082F_4B39_928E_86E2D44A5A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilesDropSource.h : header file
//
#include <afxole.h>

/////////////////////////////////////////////////////////////////////////////
// CFilesDropSource document

class CFilesDropSource : public COleDropSource
{
public:
	CFilesDropSource();	// protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesDropSource)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilesDropSource();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFilesDropSource)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESDROPSOURCE_H__6CB3A95B_082F_4B39_928E_86E2D44A5A1F__INCLUDED_)
