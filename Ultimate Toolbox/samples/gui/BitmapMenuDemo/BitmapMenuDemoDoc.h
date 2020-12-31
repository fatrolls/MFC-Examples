// BitmapMenuDemoDoc.h : interface of the CBitmapMenuDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPMENUDEMODOC_H__1E4F0C0E_88DA_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_BITMAPMENUDEMODOC_H__1E4F0C0E_88DA_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CBitmapMenuDemoDoc : public CDocument
{
protected: // create from serialization only
	CBitmapMenuDemoDoc();
	DECLARE_DYNCREATE(CBitmapMenuDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapMenuDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBitmapMenuDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBitmapMenuDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPMENUDEMODOC_H__1E4F0C0E_88DA_11D1_A3D5_0080C83F712F__INCLUDED_)
