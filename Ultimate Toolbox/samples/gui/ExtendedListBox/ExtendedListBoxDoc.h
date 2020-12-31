// ExtendedListBoxDoc.h : interface of the CExtendedListBoxDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXTENDEDLISTBOXDOC_H__21FF47EB_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_)
#define AFX_EXTENDEDLISTBOXDOC_H__21FF47EB_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExtendedListBoxDoc : public CDocument
{
protected: // create from serialization only
	CExtendedListBoxDoc();
	DECLARE_DYNCREATE(CExtendedListBoxDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendedListBoxDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendedListBoxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExtendedListBoxDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDEDLISTBOXDOC_H__21FF47EB_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_)
