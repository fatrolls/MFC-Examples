// VisualStudioLikeDemoDoc.h : interface of the CVisualStudioLikeDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALSTUDIOLIKEDEMODOC_H__73A06A41_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
#define AFX_VISUALSTUDIOLIKEDEMODOC_H__73A06A41_E209_11D2_A7ED_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVisualStudioLikeDemoDoc : public CDocument
{
protected: // create from serialization only
	CVisualStudioLikeDemoDoc();
	DECLARE_DYNCREATE(CVisualStudioLikeDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualStudioLikeDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualStudioLikeDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualStudioLikeDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALSTUDIOLIKEDEMODOC_H__73A06A41_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
