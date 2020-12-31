// $$child_frame_hfile$$.h : interface of the $$CHILD_FRAME_CLASS$$ class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class $$CHILD_FRAME_CLASS$$ : public $$CHILD_FRAME_BASE_CLASS$$
{
	DECLARE_DYNCREATE($$CHILD_FRAME_CLASS$$)
public:
	$$CHILD_FRAME_CLASS$$();

// Attributes
$$IF(SPLITTER_MDI)
protected:
	CSplitterWnd m_wndSplitter;
$$ENDIF //SPLITTER_MDI
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$CHILD_FRAME_CLASS$$)
$$IF(SPLITTER_MDI || CHILD_FRAME_STYLES)
	public:
$$ENDIF
$$IF(SPLITTER_MDI)
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
$$ENDIF //SPLITTER_MDI
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~$$CHILD_FRAME_CLASS$$();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG($$CHILD_FRAME_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
$$ENDIF
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
