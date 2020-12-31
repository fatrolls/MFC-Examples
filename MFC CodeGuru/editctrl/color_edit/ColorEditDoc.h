// ColorEditDoc.h : interface of the CColorEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

//  Copyright (c) 1996-1997, Keith Rule
//  You may freely use or modify this code provided this 
//  copyright is included in all derived versions.

#if !defined(AFX_COLOREDITDOC_H__F6898251_462B_11D1_B99D_00A0C9763A0A__INCLUDED_)
#define AFX_COLOREDITDOC_H__F6898251_462B_11D1_B99D_00A0C9763A0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "undo.h"
#include "ColorString.h"

class CColorEditDoc : public CDocument, public CColorStringUpdate, public CUndo
{
protected: // create from serialization only
	CColorEditDoc();
	DECLARE_DYNCREATE(CColorEditDoc)

// Attributes
public:
	CColorString	m_text;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString Range(long start, long end);
	long Offset2Line(long offset);
	CString GetLine(long index);
	long GetLength();
	COLORREF GetColor(long pos);
	TCHAR GetAt(long pos);
	long GetLineOffset(long index);
	long GetLineCount();
	void DoColorStringUpdate(BOOL bDataChangedFlag = TRUE);
	void DeleteContents(void);
	virtual ~CColorEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CColorEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CColorEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDITDOC_H__F6898251_462B_11D1_B99D_00A0C9763A0A__INCLUDED_)
