// ex26cDoc.h : interface of the CEx26cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26CDOC_H__4EBFDD7B_5F7D_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX26CDOC_H__4EBFDD7B_5F7D_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx26cDoc : public CDocument
{
protected: // create from serialization only
	CEx26cDoc();
	DECLARE_DYNCREATE(CEx26cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26CDOC_H__4EBFDD7B_5F7D_11D0_848F_00400526305B__INCLUDED_)
