#if !defined(AFX_TEXTOBJECT_H__4F168D58_C210_11D2_9E60_00104B08CC22__INCLUDED_)
#define AFX_TEXTOBJECT_H__4F168D58_C210_11D2_9E60_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextObject.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CTextObject command target

class CTextObject : public CCmdTarget
{
	DECLARE_DYNCREATE(CTextObject)

	CTextObject();           // protected constructor used by dynamic creation

// Attributes
public:
	char* m_pText;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextObject)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTextObject();

	// Generated message map functions
	//{{AFX_MSG(CTextObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	BEGIN_INTERFACE_PART(PersistStream, IPersistStream)
		STDMETHOD(GetClassID)(LPCLSID);
		STDMETHOD(IsDirty)();
		STDMETHOD(Load)(LPSTREAM);
		STDMETHOD(Save)(LPSTREAM, BOOL);
		STDMETHOD(GetSizeMax)(ULARGE_INTEGER FAR*);
	END_INTERFACE_PART(PersistStream)

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CTextObject)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CTextObject)
	afx_msg VARIANT GetText();
	afx_msg void SetText(const VARIANT FAR& newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTOBJECT_H__4F168D58_C210_11D2_9E60_00104B08CC22__INCLUDED_)
