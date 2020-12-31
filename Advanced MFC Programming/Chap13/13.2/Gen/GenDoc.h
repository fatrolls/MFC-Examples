// GenDoc.h : interface of the CGenDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENDOC_H__21AF865A_30FF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GENDOC_H__21AF865A_30FF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGenDoc : public CDocument
{
protected: // create from serialization only
	CGenDoc();
	DECLARE_DYNCREATE(CGenDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGenDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENDOC_H__21AF865A_30FF_11D1_9C9A_444553540000__INCLUDED_)
