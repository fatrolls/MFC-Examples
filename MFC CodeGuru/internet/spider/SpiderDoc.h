// SpiderDoc.h : interface of the CSpiderDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPIDERDOC_H__26AC102C_E049_11D1_8F58_B6D09489096E__INCLUDED_)
#define AFX_SPIDERDOC_H__26AC102C_E049_11D1_8F58_B6D09489096E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSpiderDoc : public CDocument
{
protected: // create from serialization only
	CSpiderDoc();
	DECLARE_DYNCREATE(CSpiderDoc)

// Attributes
public:
	static CSpiderDoc * GetDoc();


// Operations
public:
	BOOL ShowURL(LPCTSTR lpString);
	BOOL CheckURLUpdate (LPCTSTR lpString);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpiderDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpiderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpiderDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPIDERDOC_H__26AC102C_E049_11D1_8F58_B6D09489096E__INCLUDED_)
