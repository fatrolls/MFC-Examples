// ex27bView.cpp : implementation of the CEx27bView class
//

#include "stdafx.h"
#include "ex27b.h"

#include "ex27bDoc.h"
#include "ex27bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27bView

IMPLEMENT_DYNCREATE(CEx27bView, CScrollView)

BEGIN_MESSAGE_MAP(CEx27bView, CScrollView)
	//{{AFX_MSG_MAP(CEx27bView)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPYTO, OnEditCopyto)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYTO, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_PASTEFROM, OnEditPastefrom)
	ON_COMMAND(ID_EDIT_INSERTOBJECT, OnEditInsertobject)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERTOBJECT, OnUpdateEditInsertobject)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27bView construction/destruction

CEx27bView::CEx27bView() : m_sizeTotal(20000, 25000), 
    // 20 x 25 cm when printed
	m_rectTracker(0, 0, 0, 0) 
{
	m_cfObjDesc = ::RegisterClipboardFormat(CF_OBJECTDESCRIPTOR);
	m_cfEmbedded = ::RegisterClipboardFormat(CF_EMBEDDEDOBJECT);
}

CEx27bView::~CEx27bView()
{
}

BOOL CEx27bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27bView drawing

void CEx27bView::OnDraw(CDC* pDC)
{
    CEx27bDoc* pDoc = GetDocument();

	if(pDoc->m_lpOleObj != NULL) {
		VERIFY(::OleDraw(pDoc->m_lpOleObj, DVASPECT_CONTENT,
				pDC->GetSafeHdc(), m_rectTracker) == S_OK);
	}
    
	m_tracker.m_rect = m_rectTracker;
    pDC->LPtoDP(m_tracker.m_rect);   // device
	if(pDoc->m_bHatch) {
		m_tracker.m_nStyle |= CRectTracker::hatchInside;
	}
	else {
		m_tracker.m_nStyle &= ~CRectTracker::hatchInside;
	}
	m_tracker.Draw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27bView printing

BOOL CEx27bView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

void CEx27bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx27bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx27bView diagnostics

#ifdef _DEBUG
void CEx27bView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx27bView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx27bDoc* CEx27bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx27bDoc)));
	return (CEx27bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27bView message handlers

void CEx27bView::OnInitialUpdate() 
{
	TRACE("CEx27bView::OnInitialUpdate\n");
	m_rectTracker = CRect(1000, -1000, 5000, -5000);
	m_tracker.m_nStyle = CRectTracker::solidLine | 
		CRectTracker::resizeOutside;
    SetScrollSizes(MM_HIMETRIC, m_sizeTotal);
	CScrollView::OnInitialUpdate();
}

void CEx27bView::OnEditCopy() 
{
	COleDataSource* pSource = SaveObject();
	if(pSource) {
		pSource->SetClipboard(); // OLE deletes data source 
    }
}

void CEx27bView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
    // serves Copy, Cut, and Copy To
    pCmdUI->Enable(GetDocument()->m_lpOleObj != NULL);
}

void CEx27bView::OnEditCopyto() 
{
    // Copy text to an .STG file (nothing special about STG ext)
    CFileDialog dlg(FALSE, "stg", "*.stg");
    if (dlg.DoModal() != IDOK) {
        return;
    }
    CEx27bDoc* pDoc = GetDocument();
    // Create a structured storage home for the object (m_pStgSub).
    //  Create a root storage file, then a substorage named "sub."
	LPSTORAGE pStgRoot;
	VERIFY(::StgCreateDocfile(dlg.GetPathName().AllocSysString(),
		   STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE,
		   0, &pStgRoot) == S_OK);
	ASSERT(pStgRoot != NULL);
	
	LPSTORAGE pStgSub;
    VERIFY(pStgRoot->CreateStorage(CEx27bDoc::s_szSub,
    	   STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,
    	   0, 0, &pStgSub) == S_OK); 
	ASSERT(pStgSub != NULL);

	// Get the IPersistStorage* for the object
	LPPERSISTSTORAGE pPS = NULL;
	VERIFY(pDoc->m_lpOleObj->QueryInterface(IID_IPersistStorage,
		  (void**) &pPS) == S_OK);
    // Finally, save the object in its new home in the user's file

	VERIFY(::OleSave(pPS, pStgSub, FALSE) == S_OK); 
	// FALSE means different stg
	pPS->SaveCompleted(NULL);  // What does this do?
	pPS->Release();

	pStgSub->Release();
	pStgRoot->Release();
}

void CEx27bView::OnEditCut() 
{
    OnEditCopy();
    GetDocument()->OnEditClearAll();
}

void CEx27bView::OnEditPaste() 
{
	CEx27bDoc* pDoc = GetDocument();
	COleDataObject dataObject;
	VERIFY(dataObject.AttachClipboard());
	pDoc->DeleteContents();
	DoPasteObjectDescriptor(&dataObject);
	DoPasteObject(&dataObject);
	SetViewAdvise();
	GetSize();
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
}

void CEx27bView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    // Make sure that object data is available
	COleDataObject dataObject;
	if (dataObject.AttachClipboard() &&
    	dataObject.IsDataAvailable(m_cfEmbedded)) {
        pCmdUI->Enable(TRUE);
    } else {
    	pCmdUI->Enable(FALSE);
    }
}

void CEx27bView::OnEditPastefrom() 
{
	CEx27bDoc* pDoc = GetDocument();
    // Paste from an .STG file
    CFileDialog dlg(TRUE, "stg", "*.stg");
    if (dlg.DoModal() != IDOK) {
        return;
    }
    // Open the storage and substorage
	LPSTORAGE pStgRoot;
	VERIFY(::StgOpenStorage(dlg.GetPathName().AllocSysString(), NULL,
		   STGM_READ|STGM_SHARE_EXCLUSIVE,
		   NULL, 0, &pStgRoot) == S_OK);
	ASSERT(pStgRoot != NULL);
	
	LPSTORAGE pStgSub;
	VERIFY(pStgRoot->OpenStorage(CEx27bDoc::s_szSub, NULL,
		   STGM_READ|STGM_SHARE_EXCLUSIVE,
		   NULL, 0, &pStgSub) == S_OK);
	ASSERT(pStgSub != NULL);

    // Copy the object data from the user storage to the temporary storage
	VERIFY(pStgSub->CopyTo(NULL, NULL, NULL, 
		   pDoc->m_pTempStgSub)  == S_OK);
    // Finally, load the object -- pClientSite not necessary
	LPOLECLIENTSITE pClientSite =
		(LPOLECLIENTSITE) pDoc->GetInterface(&IID_IOleClientSite);
	ASSERT(pClientSite != NULL);
	pDoc->DeleteContents();
	VERIFY(::OleLoad(pDoc->m_pTempStgSub, IID_IOleObject, pClientSite,
		  (void**) &pDoc->m_lpOleObj) == S_OK);
	SetViewAdvise();
	pStgSub->Release();
	pStgRoot->Release();
	GetSize();
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
}

void CEx27bView::OnEditInsertobject() 
{
	CEx27bDoc* pDoc = GetDocument();
	COleInsertDialog dlg;
	if( dlg.DoModal() == IDCANCEL) return;
    // no addrefs done for GetInterface
	LPOLECLIENTSITE pClientSite =
				(LPOLECLIENTSITE) pDoc->GetInterface(&IID_IOleClientSite);
	ASSERT(pClientSite != NULL);
	pDoc->DeleteContents();
	VERIFY(::OleCreate(dlg.GetClassID(), IID_IOleObject, 
		   OLERENDER_DRAW, NULL, pClientSite, pDoc->m_pTempStgSub, 
		   (void**) &pDoc->m_lpOleObj) == S_OK);
	SetViewAdvise();

	pDoc->m_lpOleObj->DoVerb(OLEIVERB_SHOW, NULL, pClientSite, 0, 
		NULL, NULL); // OleRun doesn´t show it
	SetNames();
	GetDocument()->SetModifiedFlag();
	GetSize();
	pDoc->UpdateAllViews(NULL);
}

void CEx27bView::OnUpdateEditInsertobject(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->m_lpOleObj == NULL);
}

void CEx27bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	TRACE("**Entering CEx27bView::OnLButtonDown -- point = (%d, %d)\n", point.x, point.y);
	 if(m_tracker.Track(this, point, FALSE, NULL)) {
		CClientDC dc(this);
		OnPrepareDC(&dc);
		m_rectTracker = m_tracker.m_rect;
		dc.DPtoLP(m_rectTracker); // Update logical coords
		GetDocument()->UpdateAllViews(NULL);
	}
	TRACE("**Leaving CEx27bView::OnLButtonDown\n");
}

void CEx27bView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if(m_tracker.HitTest(point) == CRectTracker::hitNothing) return;
	// Activate the object
    CEx27bDoc* pDoc = GetDocument();
	if(pDoc->m_lpOleObj != NULL) {
		LPOLECLIENTSITE pClientSite =
				(LPOLECLIENTSITE) pDoc->GetInterface(&IID_IOleClientSite);
		ASSERT(pClientSite != NULL);
		VERIFY(pDoc->m_lpOleObj->DoVerb(OLEIVERB_OPEN, NULL, pClientSite, 0,
			GetSafeHwnd(), CRect(0, 0, 0, 0)) == S_OK);
		SetNames();
		GetDocument()->SetModifiedFlag();
	}
}

BOOL CEx27bView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_tracker.SetCursor(pWnd, nHitTest)) {
		return TRUE;
	}
	else {
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	}
}

//////////////////////////////////////////////////////////////////////////////////

void CEx27bView::SetViewAdvise() 
{								
	CEx27bDoc* pDoc = GetDocument();
	if(pDoc->m_lpOleObj != NULL) {
		LPVIEWOBJECT2 pViewObj;
		pDoc->m_lpOleObj->QueryInterface(IID_IViewObject2, 
			(void**) &pViewObj);
		LPADVISESINK pAdviseSink = 
			(LPADVISESINK) pDoc->GetInterface(&IID_IAdviseSink);
		VERIFY(pViewObj->SetAdvise(DVASPECT_CONTENT, 0, pAdviseSink) 
			== S_OK);
		pViewObj->Release();
	}
}

void CEx27bView::SetNames() // sets host names
{								
	CEx27bDoc* pDoc = GetDocument();
	CString strApp = AfxGetApp()->m_pszAppName;
	if(pDoc->m_lpOleObj != NULL) {
		pDoc->m_lpOleObj->SetHostNames(strApp.AllocSysString(), NULL);
	}
}

void CEx27bView::GetSize()
{
	CEx27bDoc* pDoc = GetDocument();
	if(pDoc->m_lpOleObj != NULL) {
		SIZEL size;	  // Ask the component for its size
		pDoc->m_lpOleObj->GetExtent(DVASPECT_CONTENT, &size);
		m_rectTracker.right = m_rectTracker.left + size.cx;
		m_rectTracker.bottom = m_rectTracker.top - size.cy;
	}
}

BOOL CEx27bView::DoPasteObject(COleDataObject* pDataObject)
{
	TRACE("Entering CEx27bView::DoPasteObject\n");
    // Update command UI should keep us out of here if not 
	//  CF_EMBEDDEDOBJECT
    if (!pDataObject->IsDataAvailable(m_cfEmbedded)) {
		TRACE("CF_EMBEDDEDOBJECT format is unavailable\n");
    	return FALSE;
    }
	CEx27bDoc* pDoc = GetDocument();
    // Now create the object from the IDataObject*.
	//  OleCreateFromData will use CF_EMBEDDEDOBJECT format if available.
	LPOLECLIENTSITE pClientSite = 
			(LPOLECLIENTSITE) pDoc->GetInterface(&IID_IOleClientSite);
	ASSERT(pClientSite != NULL);
	VERIFY(::OleCreateFromData(pDataObject->m_lpDataObject, 
		   IID_IOleObject,OLERENDER_DRAW, NULL, pClientSite, 
		   pDoc->m_pTempStgSub, (void**) &pDoc->m_lpOleObj) == S_OK);
	return TRUE;
}

BOOL CEx27bView::DoPasteObjectDescriptor(COleDataObject* pDataObject)
{
	TRACE("Entering CEx27bView::DoPasteObjectDescriptor\n");
	STGMEDIUM stg;
	FORMATETC fmt;
	CEx27bDoc* pDoc = GetDocument();
    if (!pDataObject->IsDataAvailable(m_cfObjDesc)) {
		TRACE("OBJECTDESCRIPTOR format is unavailable\n");
    	return FALSE;
    }
	SETFORMATETC(fmt, m_cfObjDesc, DVASPECT_CONTENT, NULL, 
		TYMED_HGLOBAL, -1);
	VERIFY(pDataObject->GetData(m_cfObjDesc, &stg, &fmt));
	
	return TRUE;
}

// helper function used for clipboard and drag-drop 
COleDataSource* CEx27bView::SaveObject()
{
	TRACE("Entering CEx27bView::SaveObject\n");
	CEx27bDoc* pDoc = GetDocument();
    if (pDoc->m_lpOleObj != NULL) {
		COleDataSource* pSource = new COleDataSource();
        
        // CODE FOR OBJECT DATA
        FORMATETC fmte;
        SETFORMATETC(fmte, m_cfEmbedded, DVASPECT_CONTENT, NULL,
            TYMED_ISTORAGE, -1);
        STGMEDIUM stgm;
        stgm.tymed = TYMED_ISTORAGE;
        stgm.pstg = pDoc->m_pTempStgSub;
        stgm.pUnkForRelease = NULL;
		pDoc->m_pTempStgSub->AddRef();   // must do both!
		pDoc->m_pTempStgRoot->AddRef();
		pSource->CacheData(m_cfEmbedded, &stgm, &fmte);

		// metafile needed too
		MakeMetafilePict(pSource);
		
		// CODE FOR OBJECT DESCRIPTION DATA
		HGLOBAL hObjDesc = ::GlobalAlloc(GMEM_SHARE, sizeof(OBJECTDESCRIPTOR));
		LPOBJECTDESCRIPTOR pObjDesc =
		    (LPOBJECTDESCRIPTOR) ::GlobalLock(hObjDesc);
		pObjDesc->cbSize = sizeof(OBJECTDESCRIPTOR);
		pObjDesc->clsid	= CLSID_NULL;
		pObjDesc->dwDrawAspect = 0;
		pObjDesc->dwStatus = 0;
		pObjDesc->dwFullUserTypeName = 0;
		pObjDesc->dwSrcOfCopy = 0;
	   	pObjDesc->sizel.cx = 0;
    	pObjDesc->sizel.cy = 0;
    	pObjDesc->pointl.x = 0;
    	pObjDesc->pointl.y = 0;
		::GlobalUnlock(hObjDesc);
		pSource->CacheGlobalData(m_cfObjDesc, hObjDesc);
		return pSource;
	}
	return NULL;
}

BOOL CEx27bView::MakeMetafilePict(COleDataSource* pSource)
{
	CEx27bDoc* pDoc = GetDocument();
	COleDataObject dataObject;
	LPDATAOBJECT pDataObj; // OLE object's IDataObject interface
	VERIFY(pDoc->m_lpOleObj->QueryInterface(IID_IDataObject,
		  (void**) &pDataObj) == S_OK);
	dataObject.Attach(pDataObj);
    FORMATETC fmtem;
    SETFORMATETC(fmtem, CF_METAFILEPICT, DVASPECT_CONTENT, NULL,
        TYMED_MFPICT, -1);
    if (!dataObject.IsDataAvailable(CF_METAFILEPICT, &fmtem)) {
		TRACE("CF_METAFILEPICT format is unavailable\n");
    	return FALSE;
    }
	// Just copy the metafile handle from the OLE object
	//  to the clipboard data object
    STGMEDIUM stgmm;
	VERIFY(dataObject.GetData(CF_METAFILEPICT, &stgmm, &fmtem));
	pSource->CacheData(CF_METAFILEPICT, &stgmm, &fmtem);
	return TRUE;
}
