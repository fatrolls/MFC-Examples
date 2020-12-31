// IE4ControlsDemoDoc.h : interface of the CIE4ControlsDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IE4CONTROLSDEMODOC_H__6754292A_A55F_11D1_B231_444553540000__INCLUDED_)
#define AFX_IE4CONTROLSDEMODOC_H__6754292A_A55F_11D1_B231_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CIE4ControlsDemoDoc : public CDocument
{
protected: // create from serialization only
	CIE4ControlsDemoDoc();
	DECLARE_DYNCREATE(CIE4ControlsDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIE4ControlsDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIE4ControlsDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIE4ControlsDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IE4CONTROLSDEMODOC_H__6754292A_A55F_11D1_B231_444553540000__INCLUDED_)
