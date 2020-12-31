// $$view_hfile$$.h : interface of the $$VIEW_CLASS$$ class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

$$IF(CONTAINER || CONTAINER_SERVER)
class $$CNTRITEM_CLASS$$;

$$ENDIF
$$IF(CRecordView || CDaoRecordView)
class $$RECSET_CLASS$$;

$$ENDIF
class $$VIEW_CLASS$$ : public $$VIEW_BASE_CLASS$$
{
protected: // create from serialization only
	$$VIEW_CLASS$$();
	DECLARE_DYNCREATE($$VIEW_CLASS$$)
$$IF(CRecordView || CDaoRecordView || CFormView)

public:
	//{{AFX_DATA($$VIEW_CLASS$$)
	enum{ IDD = IDD_$$SAFE_ROOT$$_FORM };
$$IF(CRecordView || CDaoRecordView)
	$$RECSET_CLASS$$* m_pSet;
$$ENDIF
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
$$ENDIF

// Attributes
public:
	$$DOC_CLASS$$* GetDocument();
$$IF(CONTAINER || CONTAINER_SERVER)
$$IF(!CRichEditView)
$$IF(VERBOSE)
	// m_pSelection holds the selection to the current $$CNTRITEM_CLASS$$.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not $$CNTRITEM_CLASS$$ objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
$$ENDIF //VERBOSE
	$$CNTRITEM_CLASS$$* m_pSelection;
$$ENDIF //!CRichEditView
$$ENDIF //CONTAINERS

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$VIEW_CLASS$$)
	public:
$$IF(CRecordView)
	virtual CRecordset* OnGetRecordset();
$$ENDIF
$$IF(CDaoRecordView)
	virtual CDaoRecordset* OnGetRecordset();
$$ENDIF
$$IF(CFormView || CRecordView || CDaoRecordView)
$$ELIF(!CRichEditView);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
$$ENDIF // !(CFormView || CRecordView || CDaoRecordView)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
$$IF(CFormView || CRecordView || CDaoRecordView)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
$$ENDIF //CFormView || CRecordView || CDaoRecordView
$$IF(CScrollView || CONTAINER || CONTAINER_SERVER || CRecordView || CDaoRecordView || CTreeView || CListView)
	virtual void OnInitialUpdate(); // called first time after construct
$$ENDIF
$$IF(PRINT)
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
$$IF(!CRichEditView)
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
$$ENDIF //!CRichEditView
$$IF(CFormView)
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
$$ENDIF //CFormView
$$ENDIF //PRINT
$$IF(CONTAINER || CONTAINER_SERVER)
$$IF(!CRichEditView)
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
$$ENDIF //!CRichEditView
$$ENDIF //CONTAINER || CONTAINER_SERVER
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~$$VIEW_CLASS$$();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG($$VIEW_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
$$ENDIF
$$IF(CONTAINER || CONTAINER_SERVER)
	afx_msg void OnDestroy();
$$IF(!CRichEditView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
$$ENDIF //!CRichEditView
$$ENDIF //CONTAINER || CONTAINER_SERVER
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
	afx_msg void OnCancelEditSrvr();
$$ENDIF //SERVERS
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in $$view_ifile$$.cpp
inline $$DOC_CLASS$$* $$VIEW_CLASS$$::GetDocument()
   { return ($$DOC_CLASS$$*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
