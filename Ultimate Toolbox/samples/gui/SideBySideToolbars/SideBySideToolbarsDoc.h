// SideBySideToolbarsDoc.h : interface of the CSideBySideToolbarsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIDEBYSIDETOOLBARSDOC_H__CF4D52F1_FC9A_46C5_83CF_D6BDEACFF985__INCLUDED_)
#define AFX_SIDEBYSIDETOOLBARSDOC_H__CF4D52F1_FC9A_46C5_83CF_D6BDEACFF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSideBySideToolbarsDoc : public CDocument
{
protected: // create from serialization only
	CSideBySideToolbarsDoc();
	DECLARE_DYNCREATE(CSideBySideToolbarsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSideBySideToolbarsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSideBySideToolbarsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSideBySideToolbarsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDEBYSIDETOOLBARSDOC_H__CF4D52F1_FC9A_46C5_83CF_D6BDEACFF985__INCLUDED_)
