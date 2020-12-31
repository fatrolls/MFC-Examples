// captionDoc.h : interface of the CCaptionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAPTIONDOC_H__A536239C_6034_11D1_B4DF_006097608B1F__INCLUDED_)
#define AFX_CAPTIONDOC_H__A536239C_6034_11D1_B4DF_006097608B1F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CCaptionDoc : public CDocument
{
protected: // create from serialization only
	CCaptionDoc();
	DECLARE_DYNCREATE(CCaptionDoc)

// Attributes
public:

// Operations
public:
  virtual void SetModifiedFlag(BOOL);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptionDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCaptionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCaptionDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTIONDOC_H__A536239C_6034_11D1_B4DF_006097608B1F__INCLUDED_)
