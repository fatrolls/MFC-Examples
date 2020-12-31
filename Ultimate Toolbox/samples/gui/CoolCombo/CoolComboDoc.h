// CoolComboDoc.h : interface of the CCoolComboDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COOLCOMBODOC_H__FE6B1BCF_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_)
#define AFX_COOLCOMBODOC_H__FE6B1BCF_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCoolComboDoc : public CDocument
{
protected: // create from serialization only
	CCoolComboDoc();
	DECLARE_DYNCREATE(CCoolComboDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolComboDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoolComboDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCoolComboDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLCOMBODOC_H__FE6B1BCF_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_)
