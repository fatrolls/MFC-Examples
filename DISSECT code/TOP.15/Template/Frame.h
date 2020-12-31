// $$frame_hfile$$.h : interface of the $$FRAME_CLASS$$ class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

$$IF(PROJTYPE_MDI)
class $$FRAME_CLASS$$ : public $$FRAME_BASE_CLASS$$
{
	DECLARE_DYNAMIC($$FRAME_CLASS$$)
public:
	$$FRAME_CLASS$$();
$$ELSE
class $$FRAME_CLASS$$ : public $$FRAME_BASE_CLASS$$
{
protected: // create from serialization only
	$$FRAME_CLASS$$();
	DECLARE_DYNCREATE($$FRAME_CLASS$$)
$$ENDIF

// Attributes
$$IF(SPLITTER_SDI)
protected:
	CSplitterWnd m_wndSplitter;
$$ENDIF //SPLITTER_SDI
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$FRAME_CLASS$$)
$$IF(SPLITTER_SDI || FRAME_STYLES)
	public:
$$ENDIF
$$IF(SPLITTER_SDI)
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
$$ENDIF
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~$$FRAME_CLASS$$();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
$$IF(TOOLBAR || STATUSBAR)

protected:  // control bar embedded members
$$IF(STATUSBAR)	
	CStatusBar  m_wndStatusBar;
$$ENDIF //STATUSBAR
$$IF(TOOLBAR)
	CToolBar    m_wndToolBar;
$$ENDIF //TOOLBAR
$$ENDIF //TOOLBAR || STATUSBAR

// Generated message map functions
protected:
	//{{AFX_MSG($$FRAME_CLASS$$)
$$IF(TOOLBAR || STATUSBAR)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
$$ENDIF //TOOLBAR || STATUSBAR
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
