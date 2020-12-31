// fanDoc.h : interface of the CFanDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FANDOC_H__477B0C5B_6FB8_11D3_9803_0088CC094230__INCLUDED_)
#define AFX_FANDOC_H__477B0C5B_6FB8_11D3_9803_0088CC094230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFanDoc : public CDocument
{
protected: // create from serialization only
	CFanDoc();
	DECLARE_DYNCREATE(CFanDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFanDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFanDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFanDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FANDOC_H__477B0C5B_6FB8_11D3_9803_0088CC094230__INCLUDED_)
