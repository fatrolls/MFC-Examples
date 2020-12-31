// MetaFileDoc.h : interface of the CMetaFileDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_METAFILEDOC_H__D6580AF0_EA6C_11D1_8856_0080C83F712F__INCLUDED_)
#define AFX_METAFILEDOC_H__D6580AF0_EA6C_11D1_8856_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "OXMetaFile.h"


class CMetaFileDoc : public CDocument
{
protected: // create from serialization only
	CMetaFileDoc();
	DECLARE_DYNCREATE(CMetaFileDoc)

// Attributes
public:
	COXMetaFile m_MetaFile;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaFileDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMetaFileDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMetaFileDoc)
	afx_msg void OnFileCreateMetafile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METAFILEDOC_H__D6580AF0_EA6C_11D1_8856_0080C83F712F__INCLUDED_)
