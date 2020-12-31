// $$cntritem_ifile$$.cpp : implementation of the $$CNTRITEM_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"

$$IF(CRecordView || CDaoRecordView)
#include "$$recset_hfile$$.h"
$$ENDIF
#include "$$doc_hfile$$.h"
#include "$$view_hfile$$.h"
#include "$$cntritem_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$CNTRITEM_CLASS$$ implementation

IMPLEMENT_SERIAL($$CNTRITEM_CLASS$$, $$CNTRITEM_BASE_CLASS$$, 0)

$$IF(CRichEditView)
$$CNTRITEM_CLASS$$::$$CNTRITEM_CLASS$$(REOBJECT* preo, $$DOC_CLASS$$* pContainer)
	: $$CNTRITEM_BASE_CLASS$$(preo, pContainer)
$$ELSE //!CRichEditView
$$CNTRITEM_CLASS$$::$$CNTRITEM_CLASS$$($$DOC_CLASS$$* pContainer)
	: $$CNTRITEM_BASE_CLASS$$(pContainer)
$$ENDIF //CRichEditView
{
$$IF(VERBOSE)
	// TODO: add one-time construction code here
	
$$ENDIF
}

$$CNTRITEM_CLASS$$::~$$CNTRITEM_CLASS$$()
{
$$IF(VERBOSE)
	// TODO: add cleanup code here
	
$$ENDIF
}
$$IF(!CRichEditView)

void $$CNTRITEM_CLASS$$::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	$$CNTRITEM_BASE_CLASS$$::OnChange(nCode, dwParam);
$$IF(VERBOSE)

	// When an item is being edited (either in-place or fully open)
	//  it sends OnChange notifications for changes in the state of the
	//  item or visual appearance of its content.

	// TODO: invalidate the item by calling UpdateAllViews
	//  (with hints appropriate to your application)

	GetDocument()->UpdateAllViews(NULL);
		// for now just update ALL views/no hints
$$ENDIF
}

BOOL $$CNTRITEM_CLASS$$::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);
$$IF(VERBOSE)

	// During in-place activation $$CNTRITEM_CLASS$$::OnChangeItemPosition
	//  is called by the server to change the position of the in-place
	//  window.  Usually, this is a result of the data in the server
	//  document changing such that the extent has changed or as a result
	//  of in-place resizing.
	//
	// The default here is to call the base class, which will call
	//  $$CNTRITEM_BASE_CLASS$$::SetItemRects to move the item
	//  to the new position.
$$ENDIF

	if (!$$CNTRITEM_BASE_CLASS$$::OnChangeItemPosition(rectPos))
		return FALSE;

$$IF(VERBOSE)
	// TODO: update any cache you may have of the item's rectangle/extent

$$ENDIF
	return TRUE;
}

void $$CNTRITEM_CLASS$$::OnGetItemPosition(CRect& rPosition)
{
	ASSERT_VALID(this);
$$IF(VERBOSE)

	// During in-place activation, $$CNTRITEM_CLASS$$::OnGetItemPosition
	//  will be called to determine the location of this item.  The default
	//  implementation created from AppWizard simply returns a hard-coded
	//  rectangle.  Usually, this rectangle would reflect the current
	//  position of the item relative to the view used for activation.
	//  You can obtain the view by calling $$CNTRITEM_CLASS$$::GetActiveView.

	// TODO: return correct rectangle (in pixels) in rPosition
$$ENDIF

	rPosition.SetRect(10, 10, 210, 210);
}

void $$CNTRITEM_CLASS$$::OnActivate()
{
    // Allow only one inplace activate item per frame
    $$VIEW_CLASS$$* pView = GetActiveView();
    ASSERT_VALID(pView);
    COleClientItem* pItem = GetDocument()->GetInPlaceActiveItem(pView);
    if (pItem != NULL && pItem != this)
        pItem->Close();
    
    $$CNTRITEM_BASE_CLASS$$::OnActivate();
}

void $$CNTRITEM_CLASS$$::OnDeactivateUI(BOOL bUndoable)
{
	$$CNTRITEM_BASE_CLASS$$::OnDeactivateUI(bUndoable);

    // Hide the object if it is not an outside-in object
    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
}

void $$CNTRITEM_CLASS$$::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

$$IF(VERBOSE)
	// Call base class first to read in $$CNTRITEM_BASE_CLASS$$ data.
	// Since this sets up the m_pDocument pointer returned from
	//  $$CNTRITEM_CLASS$$::GetDocument, it is a good idea to call
	//  the base class Serialize first.
$$ENDIF
	$$CNTRITEM_BASE_CLASS$$::Serialize(ar);

$$IF(VERBOSE)
	// now store/retrieve data specific to $$CNTRITEM_CLASS$$
$$ENDIF
	if (ar.IsStoring())
	{
$$IF(VERBOSE)
		// TODO: add storing code here
$$ENDIF
	}
	else
	{
$$IF(VERBOSE)
		// TODO: add loading code here
$$ENDIF
	}
}
$$IF(CONTAINER_SERVER)

BOOL $$CNTRITEM_CLASS$$::CanActivate()
{
$$IF(VERBOSE)
	// Editing in-place while the server itself is being edited in-place
	//  does not work and is not supported.  So, disable in-place
	//  activation in this case.
$$ENDIF
	$$DOC_CLASS$$* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(COleServerDoc)));
	if (pDoc->IsInPlaceActive())
		return FALSE;

$$IF(VERBOSE)
	// otherwise, rely on default behavior
$$ENDIF
	return COleClientItem::CanActivate();
}
$$ENDIF
$$ENDIF //!CRichEditView

/////////////////////////////////////////////////////////////////////////////
// $$CNTRITEM_CLASS$$ diagnostics

#ifdef _DEBUG
void $$CNTRITEM_CLASS$$::AssertValid() const
{
	$$CNTRITEM_BASE_CLASS$$::AssertValid();
}

void $$CNTRITEM_CLASS$$::Dump(CDumpContext& dc) const
{
	$$CNTRITEM_BASE_CLASS$$::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
