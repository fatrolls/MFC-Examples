// VarSplitDoc.h : interface of the CVarSplitDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARSPLITDOC_H__233727CD_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
#define AFX_VARSPLITDOC_H__233727CD_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CVarSplitDoc : public CDocument
{
protected: // create from serialization only
	CVarSplitDoc();
	DECLARE_DYNCREATE(CVarSplitDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVarSplitDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVarSplitDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVarSplitDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VARSPLITDOC_H__233727CD_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
