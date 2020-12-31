// VBScriptEditorDoc.h : interface of the CVBScriptEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VBSCRIPTEDITORDOC_H__EDDE6D4F_C472_11D1_8635_00403395B157__INCLUDED_)
#define AFX_VBSCRIPTEDITORDOC_H__EDDE6D4F_C472_11D1_8635_00403395B157__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CVBScriptEditorDoc : public CDocument
{
protected: // create from serialization only
	CVBScriptEditorDoc();
	DECLARE_DYNCREATE(CVBScriptEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVBScriptEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVBScriptEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVBScriptEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VBSCRIPTEDITORDOC_H__EDDE6D4F_C472_11D1_8635_00403395B157__INCLUDED_)
