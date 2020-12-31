// $$cntritem_hfile$$.h : interface of the $$CNTRITEM_CLASS$$ class
//

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class $$DOC_CLASS$$;
class $$VIEW_CLASS$$;

class $$CNTRITEM_CLASS$$ : public $$CNTRITEM_BASE_CLASS$$
{
	DECLARE_SERIAL($$CNTRITEM_CLASS$$)

// Constructors
public:
$$IF(CRichEditView)
	$$CNTRITEM_CLASS$$(REOBJECT* preo = NULL, $$DOC_CLASS$$* pContainer = NULL);
$$ELSE
	$$CNTRITEM_CLASS$$($$DOC_CLASS$$* pContainer = NULL);
$$ENDIF //CRichEditView
$$IF(VERBOSE)
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.
$$ENDIF

// Attributes
public:
	$$DOC_CLASS$$* GetDocument()
		{ return ($$DOC_CLASS$$*)$$CNTRITEM_BASE_CLASS$$::GetDocument(); }
	$$VIEW_CLASS$$* GetActiveView()
		{ return ($$VIEW_CLASS$$*)$$CNTRITEM_BASE_CLASS$$::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$CNTRITEM_CLASS$$)
	public:
$$IF(!CRichEditView)
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
$$ENDIF //!CRichEditView
	protected:
$$IF(!CRichEditView)
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
$$IF(CONTAINER_SERVER)
	virtual BOOL CanActivate();
$$ENDIF
$$ENDIF //!CRichEditView
	//}}AFX_VIRTUAL

// Implementation
public:
	~$$CNTRITEM_CLASS$$();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
$$IF(!CRichEditView)
	virtual void Serialize(CArchive& ar);
$$ENDIF //!CRichEditView
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
