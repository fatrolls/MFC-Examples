// BackgroundPainterDoc.h : interface of the CBackgroundPainterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKGROUNDPAINTERDOC_H__24987B1F_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
#define AFX_BACKGROUNDPAINTERDOC_H__24987B1F_8DEB_11D2_A792_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBackgroundPainterDoc : public CDocument
{
protected: // create from serialization only
	CBackgroundPainterDoc();
	DECLARE_DYNCREATE(CBackgroundPainterDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackgroundPainterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBackgroundPainterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBackgroundPainterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKGROUNDPAINTERDOC_H__24987B1F_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
