// ComTestDoc.h : interface of the CComTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMTESTDOC_H__AD9CD86E_B103_11D0_968D_444553540000__INCLUDED_)
#define AFX_COMTESTDOC_H__AD9CD86E_B103_11D0_968D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CComTestDoc : public CDocument
{
protected: // create from serialization only
	CComTestDoc();
	DECLARE_DYNCREATE(CComTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CComTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMTESTDOC_H__AD9CD86E_B103_11D0_968D_444553540000__INCLUDED_)
