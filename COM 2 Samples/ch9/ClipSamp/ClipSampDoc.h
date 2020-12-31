// ClipSampDoc.h : interface of the CClipSampDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPSAMPDOC_H__1D48F68D_DFF7_11D2_9E78_00104B08CC22__INCLUDED_)
#define AFX_CLIPSAMPDOC_H__1D48F68D_DFF7_11D2_9E78_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dib.h"

class CClipSampDoc : public CDocument
{
public:
    CDib m_dib;
    BOOL m_bDragHere; // for drags between two wins linked to this doc
protected: // create from serialization only
	CClipSampDoc();
	DECLARE_DYNCREATE(CClipSampDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipSampDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClipSampDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	//{{AFX_MSG(CClipSampDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPSAMPDOC_H__1D48F68D_DFF7_11D2_9E78_00104B08CC22__INCLUDED_)
