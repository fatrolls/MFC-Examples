// RulerBarDoc.h : interface of the CRulerBarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULERBARDOC_H__12E49E91_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
#define AFX_RULERBARDOC_H__12E49E91_E788_11D2_A7F6_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRulerBarDoc : public CDocument
{
protected: // create from serialization only
	CRulerBarDoc();
	DECLARE_DYNCREATE(CRulerBarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulerBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRulerBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRulerBarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULERBARDOC_H__12E49E91_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
