// OutLookStyleDoc.h : interface of the COutLookStyleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKSTYLEDOC_H__C50FD4FA_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
#define AFX_OUTLOOKSTYLEDOC_H__C50FD4FA_CEFA_11D1_9B01_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class COutLookStyleDoc : public CDocument
{
protected: // create from serialization only
	COutLookStyleDoc();
	DECLARE_DYNCREATE(COutLookStyleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutLookStyleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutLookStyleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutLookStyleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKSTYLEDOC_H__C50FD4FA_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
