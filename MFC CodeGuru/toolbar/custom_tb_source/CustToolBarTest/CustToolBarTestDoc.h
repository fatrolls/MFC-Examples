// CustToolBarTestDoc.h : interface of the CCustToolBarTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTTOOLBARTESTDOC_H__761D39E4_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_CUSTTOOLBARTESTDOC_H__761D39E4_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CCustToolBarTestDoc : public CDocument
{
protected: // create from serialization only
	CCustToolBarTestDoc();
	DECLARE_DYNCREATE(CCustToolBarTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustToolBarTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustToolBarTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustToolBarTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTTOOLBARTESTDOC_H__761D39E4_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
