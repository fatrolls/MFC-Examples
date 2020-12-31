// Copyright (C) BrigSoft, 2003.
// http://www.brigsoft.com
// FilesDragDropView.cpp : implementation of the CFilesDragDropView class
//

#include "stdafx.h"
#include "FilesDragDrop.h"

#include "FilesDragDropDoc.h"
#include "FilesDragDropView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropView

IMPLEMENT_DYNCREATE(CFilesDragDropView, CListView)

BEGIN_MESSAGE_MAP(CFilesDragDropView, CListView)
	//{{AFX_MSG_MAP(CFilesDragDropView)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBeginDrag)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropView construction/destruction

CFilesDragDropView::CFilesDragDropView()
{
	// TODO: add construction code here

}

CFilesDragDropView::~CFilesDragDropView()
{
}

BOOL CFilesDragDropView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT |LVS_SHOWSELALWAYS;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropView drawing

void CFilesDragDropView::OnDraw(CDC* pDC)
{
	CFilesDragDropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CFilesDragDropView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

//AR
	VERIFY( m_DropTarget.Register(this) );

	CRect cr;
	GetClientRect(&cr);
	GetListCtrl().InsertColumn(0,"File",LVCFMT_LEFT, cr.Width(), -1);

}

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropView printing

BOOL CFilesDragDropView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFilesDragDropView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFilesDragDropView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropView diagnostics

#ifdef _DEBUG
void CFilesDragDropView::AssertValid() const
{
	CListView::AssertValid();
}

void CFilesDragDropView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFilesDragDropDoc* CFilesDragDropView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFilesDragDropDoc)));
	return (CFilesDragDropDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilesDragDropView message handlers

BOOL CFilesDragDropView::DataObjectToList (COleDataObject* const pDataObject)
{
	if( pDataObject->IsDataAvailable( CF_HDROP ) )
	{
		STGMEDIUM StgMed;
		FORMATETC fmte = {	CF_HDROP,
        					(DVTARGETDEVICE FAR *)NULL,
        					DVASPECT_CONTENT,
        					-1,
        					TYMED_HGLOBAL 
						};
		if( pDataObject->GetData( CF_HDROP, &StgMed, &fmte ) )
		{
			
			if(! FileNamesToList( (HDROP)StgMed.hGlobal ) ){
				return FALSE;
			}
			
			if (StgMed.pUnkForRelease){
				StgMed.pUnkForRelease->Release();
			}
			else	{
				::GlobalFree(StgMed.hGlobal);
			}
			return TRUE;
		}
	}

	return FALSE;
}


BOOL CFilesDragDropView::FileNamesToList( HDROP hDrop )
{

	UINT cFiles = ::DragQueryFile(hDrop, (UINT)-1, NULL, 0);				
	
	if(cFiles <= 0){
		ASSERT(0);
		return FALSE;
	}

	char szFile[MAX_PATH];
	
	for( UINT count = 0; count < cFiles; count++ )
	{
		::DragQueryFile(hDrop, count, szFile, sizeof(szFile));
		GetListCtrl().InsertItem(0,szFile);

	}

	return TRUE;
}


BOOL CFilesDragDropView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	
	BOOL bRet = DataObjectToList(pDataObject);
	if(dropEffect != DROPEFFECT_COPY){
		// To do: delete files for Move Files here.
		//ASSERT(0);
	}
	return bRet;
}

DROPEFFECT CFilesDragDropView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( ! pDataObject->IsDataAvailable( CF_HDROP ) ){
		return DROPEFFECT_NONE;
	}

	DROPEFFECT de = DROPEFFECT_NONE;

	if ( dwKeyState & MK_CONTROL ){
		de = DROPEFFECT_COPY;
	}
	else{
		de = DROPEFFECT_MOVE;
	}
	
	return de; 
}

void CFilesDragDropView::OnEditPaste() 
{
	COleDataObject DataObject;

	if( DataObject.AttachClipboard() )
	{
		DataObjectToList(&DataObject);
	}
	
}

void CFilesDragDropView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// Past menu point is enable if there are files oc clipboard
	COleDataObject odj;
	pCmdUI->Enable(FALSE);

	if( odj.AttachClipboard() )
	{
		if( odj.IsDataAvailable( CF_HDROP ) ){
			pCmdUI->Enable(TRUE);
		}
	}	
	
}

void CFilesDragDropView::OnEditCopy() 
{
	FileNamesToClipBoard();
	
}

BOOL CFilesDragDropView::PrepareFileBuff(CDropFiles& DropFiles) const
{
	CListCtrl& mylist = GetListCtrl();
	POSITION pos = mylist.GetFirstSelectedItemPosition();

	if( pos == NULL){
		return FALSE;
	}

	while (pos) {		
		int index = mylist.GetNextSelectedItem(pos);
		DropFiles.AddFile( mylist.GetItemText(index, 0) );
	}

	DropFiles.CreateBuffer();

	return TRUE;
}


void CFilesDragDropView::FileNamesToClipBoard( )
{
	CDropFiles DropFiles;

	if(!PrepareFileBuff(DropFiles)){
		return;
	}
	
	if (OpenClipboard())
	{
		BeginWaitCursor();
		::EmptyClipboard();
		
		HGLOBAL hMem = ::GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, DropFiles.GetBuffSize());		
		memcpy( (char*)::GlobalLock(hMem), DropFiles.GetBuffer(), DropFiles.GetBuffSize() );
		::SetClipboardData (CF_HDROP, hMem  );

		::CloseClipboard();
		EndWaitCursor();
	}
}


void CFilesDragDropView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();

	if(pos){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
	
}


void CFilesDragDropView::OnEditCut() 
{
	FileNamesToClipBoard();
	DeleteSelectedFiles();	
}

void CFilesDragDropView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();

	if(pos){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
	
}


void CFilesDragDropView::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CDropFiles DropFiles;
	
	if(!PrepareFileBuff(DropFiles)){
		ASSERT(0);
	}

	COleDropSource DropSource;
	COleDataSource DropData;

	HGLOBAL hMem = ::GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, DropFiles.GetBuffSize());		
	memcpy( (char*)::GlobalLock(hMem), DropFiles.GetBuffer(), DropFiles.GetBuffSize() );
	::GlobalUnlock(hMem);

	DropData.CacheGlobalData( CF_HDROP, hMem );
	DROPEFFECT de = DropData.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE,NULL);

	if(de == DROPEFFECT_COPY){
		// Copy files if CTRL btn is hold;
	}
	else{
		// Move files, as default;
		DeleteSelectedFiles();
	}

	
	*pResult = 0;
}

void CFilesDragDropView::DeleteSelectedFiles()
{
	
	CListCtrl& mylist = GetListCtrl();
	POSITION pos = mylist.GetFirstSelectedItemPosition();
	if (pos == NULL) return; 
	
	UINT nSelCount = mylist.GetSelectedCount();
	if(nSelCount==0) return;
	
	int*  ForDelete = new int [nSelCount];
	
	int i = 0, index = 0;

	while (pos) {
		index = mylist.GetNextSelectedItem(pos);
		ForDelete[i] = index;
		i++;
	}

	for(i = nSelCount-1; i >= 0; i--) { 
		mylist.DeleteItem(ForDelete[i]);
	}

	delete[] ForDelete;

}

