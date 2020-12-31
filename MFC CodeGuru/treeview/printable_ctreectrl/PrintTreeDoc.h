// PrintTreeDoc.h : interface of the CPrintTreeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTTREEDOC_H__3FF2884C_DDEA_11D1_80B0_0000F87772A5__INCLUDED_)
#define AFX_PRINTTREEDOC_H__3FF2884C_DDEA_11D1_80B0_0000F87772A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPrintTreeDoc : public CDocument
{
protected: // create from serialization only
	CPrintTreeDoc();
	DECLARE_DYNCREATE(CPrintTreeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintTreeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrintTreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrintTreeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTTREEDOC_H__3FF2884C_DDEA_11D1_80B0_0000F87772A5__INCLUDED_)
