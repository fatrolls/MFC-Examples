// ex10bDoc.h : interface of the CEx10bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX10BDOC_H__297A6601_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10BDOC_H__297A6601_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx10bDoc : public CDocument
{
protected: // create from serialization only
	CEx10bDoc();
	DECLARE_DYNCREATE(CEx10bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx10bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10BDOC_H__297A6601_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
