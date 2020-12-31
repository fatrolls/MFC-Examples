// VistaDoc.h : interface of the CVistaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISTADOC_H__3597FEAB_A70E_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_VISTADOC_H__3597FEAB_A70E_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVistaDoc : public CDocument
{
protected: // create from serialization only
	CVistaDoc();
	DECLARE_DYNCREATE(CVistaDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVistaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	CPalette* GetPalette();
	CBitmap* GetBitmap();
	virtual ~CVistaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CPalette m_palette;
	CBitmap m_bitmap;
	//{{AFX_MSG(CVistaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISTADOC_H__3597FEAB_A70E_11D2_8E53_006008A82731__INCLUDED_)
