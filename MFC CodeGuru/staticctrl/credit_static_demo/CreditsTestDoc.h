// CreditsTestDoc.h : interface of the CCreditsTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREDITSTESTDOC_H__E110A1AB_E319_11D1_9E4E_00A0245800CF__INCLUDED_)
#define AFX_CREDITSTESTDOC_H__E110A1AB_E319_11D1_9E4E_00A0245800CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CCreditsTestDoc : public CDocument
{
protected: // create from serialization only
	CCreditsTestDoc();
	DECLARE_DYNCREATE(CCreditsTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreditsTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCreditsTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCreditsTestDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREDITSTESTDOC_H__E110A1AB_E319_11D1_9E4E_00A0245800CF__INCLUDED_)
