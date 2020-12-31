// CustomizeManagerDoc.h : interface of the CCustomizeManagerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMIZEMANAGERDOC_H__F8CA3858_21D3_41FD_B720_15875E934869__INCLUDED_)
#define AFX_CUSTOMIZEMANAGERDOC_H__F8CA3858_21D3_41FD_B720_15875E934869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomizeManagerDoc : public CDocument
{
protected: // create from serialization only
	CCustomizeManagerDoc();
	DECLARE_DYNCREATE(CCustomizeManagerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeManagerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomizeManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomizeManagerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEMANAGERDOC_H__F8CA3858_21D3_41FD_B720_15875E934869__INCLUDED_)
