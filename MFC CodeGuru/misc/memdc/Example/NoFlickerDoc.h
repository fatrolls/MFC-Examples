// NoFlickerDoc.h : interface of the CNoFlickerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOFLICKERDOC_H__62D4188B_23A8_11D1_9EA4_00AA00B515FB__INCLUDED_)
#define AFX_NOFLICKERDOC_H__62D4188B_23A8_11D1_9EA4_00AA00B515FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CNoFlickerDoc : public CDocument
{
protected: // create from serialization only
	CNoFlickerDoc();
	DECLARE_DYNCREATE(CNoFlickerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoFlickerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNoFlickerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNoFlickerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOFLICKERDOC_H__62D4188B_23A8_11D1_9EA4_00AA00B515FB__INCLUDED_)
