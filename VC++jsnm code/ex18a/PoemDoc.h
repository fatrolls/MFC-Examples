// PoemDoc.h : interface of the CPoemDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POEMDOC_H__3E2BDA8B_892A_11D0_8FE3_00C04FC2A0C2__INCLUDED_)
#define AFX_POEMDOC_H__3E2BDA8B_892A_11D0_8FE3_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPoemDoc : public CDocument
{
protected: // create from serialization only
	CPoemDoc();
	DECLARE_DYNCREATE(CPoemDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPoemDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	CStringArray m_stringArray;
	virtual ~CPoemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPoemDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POEMDOC_H__3E2BDA8B_892A_11D0_8FE3_00C04FC2A0C2__INCLUDED_)
