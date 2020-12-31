// ex10cDoc.h : interface of the CEx10cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX10CDOC_H__1A050A1D_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10CDOC_H__1A050A1D_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx10cDoc : public CDocument
{
protected: // create from serialization only
	CEx10cDoc();
	DECLARE_DYNCREATE(CEx10cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx10cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10CDOC_H__1A050A1D_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
