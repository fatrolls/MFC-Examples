// TabViewsDoc.h : interface of the CTabViewsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABVIEWSDOC_H__14C16330_675D_11D2_A753_525400DAF3CE__INCLUDED_)
#define AFX_TABVIEWSDOC_H__14C16330_675D_11D2_A753_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTabViewsDoc : public CDocument
{
protected: // create from serialization only
	CTabViewsDoc();
	DECLARE_DYNCREATE(CTabViewsDoc)

// Attributes
public:

// Operations
public:

	CEditView* GetPrimaryView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabViewsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabViewsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabViewsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEWSDOC_H__14C16330_675D_11D2_A753_525400DAF3CE__INCLUDED_)
