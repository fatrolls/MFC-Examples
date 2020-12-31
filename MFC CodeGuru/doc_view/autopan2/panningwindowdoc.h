// PanningWindowDoc.h : interface of the CPanningWindowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANNINGWINDOWDOC_H__675D465F_02AF_11D2_B5CF_000000000000__INCLUDED_)
#define AFX_PANNINGWINDOWDOC_H__675D465F_02AF_11D2_B5CF_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Shape.h"

class CPanningWindowDoc : public CDocument
{
protected: // create from serialization only
	CPanningWindowDoc();
	DECLARE_DYNCREATE(CPanningWindowDoc)

// Attributes
public:
	CSize GetDrawingSize() const;
	CArray< CShape *, CShape *> m_arrShapes;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanningWindowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPanningWindowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CSize m_sizeDrawing;

// Generated message map functions
protected:
	//{{AFX_MSG(CPanningWindowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANNINGWINDOWDOC_H__675D465F_02AF_11D2_B5CF_000000000000__INCLUDED_)
