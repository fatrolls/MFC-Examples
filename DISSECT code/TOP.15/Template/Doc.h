/*
  This project was created using the Top Studio AppWizard

  $$PROJ_COMMENT$$

  Project: $$Root$$
  Author : $$PROJ_AUTHOR$$
  Date   : $$PROJ_DATE$$
*/

// $$doc_hfile$$.h : interface of the $$DOC_CLASS$$ class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)

class $$SRVRITEM_CLASS$$;
$$ENDIF // SERVERS

class $$DOC_CLASS$$ : public $$DOC_BASE_CLASS$$
{
protected: // create from serialization only
	$$DOC_CLASS$$();
	DECLARE_DYNCREATE($$DOC_CLASS$$)

// Attributes
public:
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
	$$SRVRITEM_CLASS$$* GetEmbeddedItem()
		{ return ($$SRVRITEM_CLASS$$*)$$DOC_BASE_CLASS$$::GetEmbeddedItem(); }
$$ENDIF
$$IF(CRecordView || CDaoRecordView)
	$$RECSET_CLASS$$ $$RECSET_VARIABLE$$;
$$ENDIF

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$DOC_CLASS$$)
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
$$ENDIF
	public:
	virtual BOOL OnNewDocument();
$$IF(!DB_NO_FILE)
	virtual void Serialize(CArchive& ar);
$$ENDIF
	//}}AFX_VIRTUAL
$$IF(CRichEditView)
	virtual $$CNTRITEM_BASE_CLASS$$* CreateClientItem(REOBJECT* preo) const;
$$ENDIF //CRichEditView

// Implementation
public:
	virtual ~$$DOC_CLASS$$();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
$$IF(ACTIVE_DOC_SERVER)
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);
$$ENDIF

// Generated message map functions
protected:
	//{{AFX_MSG($$DOC_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
$$ENDIF
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
$$IF(AUTOMATION)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH($$DOC_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
$$ENDIF
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
$$ENDIF
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
