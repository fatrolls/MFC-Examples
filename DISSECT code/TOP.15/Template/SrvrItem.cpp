// $$srvritem_ifile$$.cpp : implementation of the $$SRVRITEM_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"

$$IF(CRecordView || CDaoRecordView)
#include "$$recset_hfile$$.h"
$$ENDIF
#include "$$doc_hfile$$.h"
#include "$$srvritem_hfile$$.h"
$$IF(CONTAINER_SERVER)
#include "$$cntritem_hfile$$.h"
$$ENDIF

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$SRVRITEM_CLASS$$ implementation

IMPLEMENT_DYNAMIC($$SRVRITEM_CLASS$$, $$SRVRITEM_BASE_CLASS$$)

$$SRVRITEM_CLASS$$::$$SRVRITEM_CLASS$$($$DOC_CLASS$$* pContainerDoc)
	: $$SRVRITEM_BASE_CLASS$$(pContainerDoc, TRUE)
{
$$IF(VERBOSE)
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
$$ENDIF
}

$$SRVRITEM_CLASS$$::~$$SRVRITEM_CLASS$$()
{
$$IF(VERBOSE)
	// TODO: add cleanup code here
$$ENDIF
}

void $$SRVRITEM_CLASS$$::Serialize(CArchive& ar)
{
$$IF(VERBOSE)
	// $$SRVRITEM_CLASS$$::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.

$$ENDIF
	if (!IsLinkedItem())
	{
		$$DOC_CLASS$$* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

BOOL $$SRVRITEM_CLASS$$::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
$$IF(VERBOSE)
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

$$ENDIF
	if (dwDrawAspect != DVASPECT_CONTENT)
		return $$SRVRITEM_BASE_CLASS$$::OnGetExtent(dwDrawAspect, rSize);
$$IF(VERBOSE)

	// $$SRVRITEM_CLASS$$::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.
$$ENDIF

	$$DOC_CLASS$$* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

$$IF(VERBOSE)
	// TODO: replace this arbitrary size

$$ENDIF
	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC units

	return TRUE;
}

BOOL $$SRVRITEM_CLASS$$::OnDraw(CDC* pDC, CSize& rSize)
{
$$IF(VERBOSE)
	// Remove this if you use rSize
$$ENDIF
	UNREFERENCED_PARAMETER(rSize);

	$$DOC_CLASS$$* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

$$IF(VERBOSE)
	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
$$ENDIF
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

$$IF(VERBOSE)
	// TODO: add drawing code here.  Optionally, fill in the HIMETRIC extent.
	//  All drawing takes place in the metafile device context (pDC).

$$IF(CONTAINER_SERVER)
	// TODO: also draw embedded $$CNTRITEM_CLASS$$ objects.

$$ENDIF
$$ENDIF
$$IF(CONTAINER_SERVER)
	// The following code draws the first item at an arbitrary position.

	// TODO: remove this code when your real drawing code is complete

	POSITION pos = pDoc->GetStartPosition();
	$$CNTRITEM_CLASS$$* pItem = ($$CNTRITEM_CLASS$$*)pDoc->GetNextClientItem(pos);
	if (pItem != NULL)
		pItem->Draw(pDC, CRect(10, 10, 1010, 1010));
$$ENDIF
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// $$SRVRITEM_CLASS$$ diagnostics

#ifdef _DEBUG
void $$SRVRITEM_CLASS$$::AssertValid() const
{
	$$SRVRITEM_BASE_CLASS$$::AssertValid();
}

void $$SRVRITEM_CLASS$$::Dump(CDumpContext& dc) const
{
	$$SRVRITEM_BASE_CLASS$$::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
