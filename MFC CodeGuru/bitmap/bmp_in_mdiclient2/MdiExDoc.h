// MdiExDoc.h : interface of the CMdiExDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDIEXDOC_H__250DE49D_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_)
#define AFX_MDIEXDOC_H__250DE49D_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMdiExDoc : public CDocument
{
protected: // create from serialization only
	CMdiExDoc();
	DECLARE_DYNCREATE(CMdiExDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdiExDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMdiExDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMdiExDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIEXDOC_H__250DE49D_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_)
