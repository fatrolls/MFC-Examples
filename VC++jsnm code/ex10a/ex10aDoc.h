// ex10aDoc.h : interface of the CEx10aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX10ADOC_H__297A65EB_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10ADOC_H__297A65EB_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx10aDoc : public CDocument
{
protected: // create from serialization only
	CEx10aDoc();
	DECLARE_DYNCREATE(CEx10aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx10aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10ADOC_H__297A65EB_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
