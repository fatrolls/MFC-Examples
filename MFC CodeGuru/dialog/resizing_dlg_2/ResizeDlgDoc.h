// ResizeDlgDoc.h : interface of the CResizeDlgDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESIZEDLGDOC_H__74620F6C_C16B_11D1_A051_0000B435810F__INCLUDED_)
#define AFX_RESIZEDLGDOC_H__74620F6C_C16B_11D1_A051_0000B435810F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CResizeDlgDoc : public CDocument
{
protected: // create from serialization only
	CResizeDlgDoc();
	DECLARE_DYNCREATE(CResizeDlgDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeDlgDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizeDlgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResizeDlgDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEDLGDOC_H__74620F6C_C16B_11D1_A051_0000B435810F__INCLUDED_)
