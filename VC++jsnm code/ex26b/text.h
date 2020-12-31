#ifndef __TEXT_H__
#define __TEXT_H__
// CText command target

class CText : public CCmdTarget
{
private:
	char* m_pchText;

	DECLARE_DYNCREATE(CText)

	CText();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CText)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CText();

	// Generated message map functions
	//{{AFX_MSG(CText)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CText)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CText)
	afx_msg VARIANT GetText();
	afx_msg void SetText(const VARIANT FAR& newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(PersistStream, IPersistStream)
		STDMETHOD(GetClassID)(LPCLSID);
		STDMETHOD(IsDirty)();
		STDMETHOD(Load)(LPSTREAM);
		STDMETHOD(Save)(LPSTREAM, BOOL);
		STDMETHOD(GetSizeMax)(ULARGE_INTEGER FAR*);
	END_INTERFACE_PART(PersistStream)
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __TEXT_H__
