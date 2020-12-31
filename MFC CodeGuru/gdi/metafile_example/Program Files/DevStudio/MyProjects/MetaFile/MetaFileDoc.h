// MetaFileDoc.h : interface of the CMetaFileDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_METAFILEDOC_H__A1E5FA4E_C54E_11D1_97F8_00000E7CC122__INCLUDED_)
#define AFX_METAFILEDOC_H__A1E5FA4E_C54E_11D1_97F8_00000E7CC122__INCLUDED_

#include "meta.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "meta.h"

class CMetaFileDoc : public CDocument
{
protected: // create from serialization only
	CMetaFileDoc();
	DECLARE_DYNCREATE(CMetaFileDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaFileDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CMetaFile& GetMetaFile();
	virtual ~CMetaFileDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CMetaFile m_meta;
	//{{AFX_MSG(CMetaFileDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METAFILEDOC_H__A1E5FA4E_C54E_11D1_97F8_00000E7CC122__INCLUDED_)
