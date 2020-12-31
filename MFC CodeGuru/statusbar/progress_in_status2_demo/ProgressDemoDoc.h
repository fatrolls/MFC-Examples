// ProgressDemoDoc.h : interface of the CProgressDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRESSDEMODOC_H__DA78950A_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_PROGRESSDEMODOC_H__DA78950A_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CProgressDemoDoc : public CDocument
{
protected: // create from serialization only
	CProgressDemoDoc();
	DECLARE_DYNCREATE(CProgressDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgressDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProgressDemoDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDEMODOC_H__DA78950A_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_)
