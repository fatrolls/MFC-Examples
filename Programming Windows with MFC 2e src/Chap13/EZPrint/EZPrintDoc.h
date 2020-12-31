// EZPrintDoc.h : interface of the CEZPrintDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EZPRINTDOC_H__3A83FDEB_A3E6_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_EZPRINTDOC_H__3A83FDEB_A3E6_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEZPrintDoc : public CDocument
{
protected: // create from serialization only
	CEZPrintDoc();
	DECLARE_DYNCREATE(CEZPrintDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEZPrintDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEZPrintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEZPrintDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EZPRINTDOC_H__3A83FDEB_A3E6_11D2_8E53_006008A82731__INCLUDED_)
