// DIBManagerView.cpp : implementation of the CDIBManagerView class
//

#include "stdafx.h"
#include "DIBManager.h"

#include "MainFrm.h"
#include "DIBManagerDoc.h"
#include "DIBManagerView.h"
#include "ChildFrm.h"

#include "ExportDlg.h"
#include "ScaleRollupDlg.h"
#include "ImageInfoDlg.h"
#include "ResampleImageDlg.h"

#include "oxbmpfle.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerView

IMPLEMENT_DYNCREATE(CDIBManagerView, COXZoomView)

BEGIN_MESSAGE_MAP(CDIBManagerView, COXZoomView)
	//{{AFX_MSG_MAP(CDIBManagerView)
	ON_COMMAND(ID_VIEW_ZOOM_IN, OnViewZoomIn)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_IN, OnUpdateViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOM_OUT, OnViewZoomOut)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_OUT, OnUpdateViewZoomOut)
	ON_COMMAND(ID_VIEW_ZOOM_TO_100, OnViewZoomTo100)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_TO_100, OnUpdateViewZoomTo100)
	ON_COMMAND(ID_VIEW_ZOOM_TO_WINDOW, OnViewZoomToWindow)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ZOOM, OnUpdateZoom)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SIZE, OnUpdateSize)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PARAMETERS, OnUpdateParameters)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_UPDATE_COMMAND_UI(ID_FILE_PROTECTED, OnUpdateFileProtected)
	ON_COMMAND(ID_FILE_PROTECTED, OnFileProtected)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_ZOOM_LEVEL_DLG, OnViewZoomLevelDlg)
	ON_WM_QUERYNEWPALETTE()
    ON_WM_PALETTECHANGED()
	ON_COMMAND(ID_VIEW_IMAGE_INFO, OnViewImageInfo)
	ON_COMMAND(ID_VIEW_RESAMPLE_IMAGE, OnViewResampleImage)
	//}}AFX_MSG_MAP
	ON_ROLLUP_NOTIFICATION()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerView construction/destruction

CDIBManagerView::CDIBManagerView()
{
	// TODO: add construction code here
	
	SetSmoothScrolling(TRUE);
	SetSmoothEnvironment();
}

CDIBManagerView::~CDIBManagerView()
{
}

BOOL CDIBManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerView drawing

void CDIBManagerView::OnDraw(CDC* pDC)
{
	CDIBManagerDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	// get the size of image
	CSize sizeDIB=pDoc->GetDIBSize();
	CRect rect(0,0,sizeDIB.cx,sizeDIB.cy);
	CRect rectPaint=rect;
	// transform coordinates of boundary rectangle
	// taking into account current zoom level
	NormalToScaled(&rectPaint);

	///
	// we have to revert Y-coordinates
	// to get right print output
	UINT diff=rect.bottom-rect.top;
	rect.bottom=sizeDIB.cy-rect.top;
	rect.top=rect.bottom-diff;
	///
	DrawDIB(pDC,rectPaint,rect);
}

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerView printing

BOOL CDIBManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDIBManagerView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CDIBManagerDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add extra initialization before printing

    pInfo->SetMaxPage(pDoc->CalcDIBNumPage(this,pDC));
}

void CDIBManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDIBManagerView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

	// print current page
	PrintPage(pDC, pInfo);
}

void CDIBManagerView::PrintPage(CDC* pDC, CPrintInfo* pInfo)
{
	CDIBManagerDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	// define size of image on printer taking into account current zoom level
	CSize sizeDIB=pDoc->GetDIBSize();
	CRect rect(0,0,sizeDIB.cx,sizeDIB.cy);
	NormalToScaled(&rect);
	NormalToPrinted(pDC,&rect);

	// define the rectangle for current printing page
	// based on the number of all pages in the image
	int xPrinterRes=pDC->GetDeviceCaps(HORZRES);
	int yPrinterRes=pDC->GetDeviceCaps(VERTRES);
	CRect rectPage(xPrinterRes*((pInfo->m_nCurPage-1)%pDoc->m_nXPage),
		yPrinterRes*((pInfo->m_nCurPage-1)/pDoc->m_nXPage),
		xPrinterRes*((pInfo->m_nCurPage-1)%pDoc->m_nXPage)+xPrinterRes,
		yPrinterRes*((pInfo->m_nCurPage-1)/pDoc->m_nXPage)+yPrinterRes);
	// if size of page is bigger than size of remaining image
	// then make them equal
	if(rectPage.right>rect.right)
	{
		rectPage.right=rect.right;
	}
	if(rectPage.bottom>rect.bottom)
	{
		rectPage.bottom=rect.bottom;
	}

	// get the coordinates of part of image that is going to be printed
	// on the current page
	CRect rectDIB=rectPage;
	PrintedToNormal(pDC,&rectDIB);
	ScaledToNormal(&rectDIB);
	///
	// we have to revert Y-coordinates
	// to get right print output
	UINT diff=rectDIB.bottom-rectDIB.top;
	rectDIB.bottom=sizeDIB.cy-rectDIB.top;
	rectDIB.top=rectDIB.bottom-diff;
	///

	rectPage+=CSize(-rectPage.left,-rectPage.top);

	DrawDIB(pDC,rectPage,rectDIB);
}

BOOL CDIBManagerView::DrawDIB(CDC* pDC, CRect& rectDest, CRect& rectSrc)
{
	CDIBManagerDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	// set neccessary map mode
	int oldMapMode;
	oldMapMode=pDC->SetMapMode(MM_TEXT);

	// depending on current palette use original or dithered image 
	// to render image on display
	int bSuccess;
	if(!pDoc->CheckUseDithered())
	{
		bSuccess=pDoc->m_dib.Paint(pDC,rectDest,rectSrc);
	}
	else
	{
		bSuccess=pDoc->m_dibDither.Paint(pDC,rectDest,rectSrc);
	}

	pDC->SetMapMode(oldMapMode);

	return bSuccess;
}

void CDIBManagerView::NormalToScaled(CRect* pRect)
{
	int nZoomLevel=GetZoomLevel();

	// scale coordinates from normal to scaled 
	// taking into account current zoom level
	if(nZoomLevel!=100)
	{
		pRect->left=((long)((long)pRect->left*(long)nZoomLevel))/(100L);
		pRect->top=((long)((long)pRect->top*(long)nZoomLevel))/(100L);
		pRect->right=((long)((long)pRect->right*(long)nZoomLevel))/(100L);
		pRect->bottom=((long)((long)pRect->bottom*(long)nZoomLevel))/(100L);
	}
}

void CDIBManagerView::NormalToScaled(CPoint* pPoint)
{
	int nZoomLevel=GetZoomLevel();

	// scale coordinates from normal to scaled 
	// taking into account current zoom level
	if(nZoomLevel!=100)
	{
		pPoint->x=((long)((long)pPoint->x*(long)nZoomLevel))/(100L);
		pPoint->y=((long)((long)pPoint->y*(long)nZoomLevel))/(100L);
	}
}

void CDIBManagerView::ScaledToNormal(CRect* pRect)
{
	int nZoomLevel=GetZoomLevel();

	// scale coordinates from scaled to normal
	// taking into account current zoom level
	if(nZoomLevel!=100)
	{
		pRect->left=((long)((long)pRect->left*100L))/((long)nZoomLevel);
		pRect->top=((long)((long)pRect->top*100L))/((long)nZoomLevel);
		pRect->right=((long)((long)pRect->right*100L))/((long)nZoomLevel);
		pRect->bottom=((long)((long)pRect->bottom*100L))/((long)nZoomLevel);
	}
}

void CDIBManagerView::ScaledToNormal(CPoint* pPoint)
{
	int nZoomLevel=GetZoomLevel();

	// scale coordinates from scaled to normal
	// taking into account current zoom level
	if(nZoomLevel!=100)
	{
		pPoint->x=((long)((long)pPoint->x*100L))/((long)nZoomLevel);
		pPoint->y=((long)((long)pPoint->y*100L))/((long)nZoomLevel);
	}
}

void CDIBManagerView::NormalToPrinted(CDC* pDC, CRect* pRect)
{
	// scale coordinates from display to printer
	// taking into account screen and current printer DPI
	int xPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSX);
	int yPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSY);

	CClientDC dc(this);
	int xScreenDPI=dc.GetDeviceCaps(LOGPIXELSX);
	int yScreenDPI=dc.GetDeviceCaps(LOGPIXELSY);

	if(xPrinterDPI!=xScreenDPI || yPrinterDPI!=yScreenDPI)
	{
		pRect->left=((long)((long)pRect->left*(long)xPrinterDPI))/((long)xScreenDPI);
		pRect->top=((long)((long)pRect->top*(long)yPrinterDPI))/((long)yScreenDPI);
		pRect->right=((long)((long)pRect->right*(long)xPrinterDPI))/((long)xScreenDPI);
		pRect->bottom=((long)((long)pRect->bottom*(long)yPrinterDPI))/((long)yScreenDPI);
	}
}

void CDIBManagerView::NormalToPrinted(CDC* pDC, CPoint* pPoint)
{
	// scale coordinates from display to printer
	// taking into account screen and current printer DPI
	int xPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSX);
	int yPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSY);

	CClientDC dc(this);
	int xScreenDPI=dc.GetDeviceCaps(LOGPIXELSX);
	int yScreenDPI=dc.GetDeviceCaps(LOGPIXELSY);

	if(xPrinterDPI!=xScreenDPI || yPrinterDPI!=yScreenDPI)
	{
		pPoint->x=((long)((long)pPoint->x*(long)xPrinterDPI))/((long)xScreenDPI);
		pPoint->y=((long)((long)pPoint->y*(long)yPrinterDPI))/((long)yScreenDPI);
	}
}

void CDIBManagerView::PrintedToNormal(CDC* pDC, CRect* pRect)
{
	// scale coordinates from printer to display
	// taking into account screen and current printer DPI
	int xPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSX);
	int yPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSY);

	CClientDC dc(this);
	int xScreenDPI=dc.GetDeviceCaps(LOGPIXELSX);
	int yScreenDPI=dc.GetDeviceCaps(LOGPIXELSY);

	if(xPrinterDPI!=xScreenDPI || yPrinterDPI!=yScreenDPI)
	{
		pRect->left=((long)((long)pRect->left*(long)xScreenDPI))/((long)xPrinterDPI);
		pRect->top=((long)((long)pRect->top*(long)yScreenDPI))/((long)yPrinterDPI);
		pRect->right=((long)((long)pRect->right*(long)xScreenDPI))/((long)xPrinterDPI);
		pRect->bottom=((long)((long)pRect->bottom*(long)yScreenDPI))/((long)yPrinterDPI);
	}
}

void CDIBManagerView::PrintedToNormal(CDC* pDC, CPoint* pPoint)
{
	// scale coordinates from printer to display
	// taking into account screen and current printer DPI
	int xPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSX);
	int yPrinterDPI=pDC->GetDeviceCaps(LOGPIXELSY);

	CClientDC dc(this);
	int xScreenDPI=dc.GetDeviceCaps(LOGPIXELSX);
	int yScreenDPI=dc.GetDeviceCaps(LOGPIXELSY);

	if(xPrinterDPI!=xScreenDPI || yPrinterDPI!=yScreenDPI)
	{
		pPoint->x=((long)((long)pPoint->x*(long)xScreenDPI))/((long)xPrinterDPI);
		pPoint->y=((long)((long)pPoint->y*(long)yScreenDPI))/((long)yPrinterDPI);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerView diagnostics

#ifdef _DEBUG
void CDIBManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CDIBManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIBManagerDoc* CDIBManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIBManagerDoc)));
	return(CDIBManagerDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
//  A view's OnInitialUpdate() overrideable function is called immediately
//  after the frame window is created, and the view within the frame
//  window is attached to its document.  This provides the scroll view the
//  opportunity to set its size(m_totalSize) based on the document size.
void CDIBManagerView::OnInitialUpdate() 
{
	CDIBManagerDoc* pDoc=GetDocument();

	// get the size of DIB image to set ScrollSize of view window
	CSize sizeDIB=pDoc->m_dib.GetSize();
	CRect rectDIB=CRect(0,0,sizeDIB.cx,sizeDIB.cy);
	SetDeviceScrollSizesRelative(MM_TEXT,rectDIB);
	SetZoomAlign(ZV_CENTER);

}

void CDIBManagerView::OnViewZoomIn() 
{
	// TODO: Add your command handler code here

	// up current zoom level on 100% if it is more than 100% already
	// or on 10% otherwise
	int nZoomLevel=GetZoomLevel();
	if(nZoomLevel<ID_MAX_ZOOM_LEVEL)
	{
		int nMargin=nZoomLevel>=100 ? 100 : 10;
		nZoomLevel+=nMargin;
		SetZoomLevel(nZoomLevel);
		if(GetZoomLevel()>ID_MAX_ZOOM_LEVEL)
		{
			SetZoomLevel(ID_MAX_ZOOM_LEVEL);
		}
		// if roll-up ZoomLevel dialog is active then
		// notify it that current zoom level is changed
		NotifyZoomChanged();
	}
}

void CDIBManagerView::OnUpdateViewZoomIn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(ID_MAX_ZOOM_LEVEL>GetZoomLevel());
}

void CDIBManagerView::OnViewZoomOut() 
{
	// TODO: Add your command handler code here
	
	// down current zoom level on 100% if it is more than 100% already
	// or on 10% otherwise
	int nZoomLevel=GetZoomLevel();
	if(nZoomLevel>ID_MIN_ZOOM_LEVEL)
	{
		int nMargin=nZoomLevel>100 ? 100 : 10;
		nZoomLevel-=nMargin;
		if(nZoomLevel<nMargin)
		{
			nZoomLevel=nMargin;
		}
		SetZoomLevel(nZoomLevel);
		if(GetZoomLevel()<ID_MIN_ZOOM_LEVEL)
		{
			SetZoomLevel(ID_MIN_ZOOM_LEVEL);
		}
		// if roll-up ZoomLevel dialog is active then
		// notify it that current zoom level is changed
		NotifyZoomChanged();
	}
}

void CDIBManagerView::OnUpdateViewZoomOut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(ID_MIN_ZOOM_LEVEL<GetZoomLevel());
}

void CDIBManagerView::OnViewZoomTo100() 
{
	// TODO: Add your command handler code here
	
	// zoom to original size
	SetZoomLevel(100);
	// if roll-up ZoomLevel dialog is active then
	// notify it that current zoom level is changed
	NotifyZoomChanged();
}

void CDIBManagerView::OnUpdateViewZoomTo100(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL bZoomLevelEqual100=100==GetZoomLevel() ? TRUE : FALSE;

	pCmdUI->Enable(!bZoomLevelEqual100);
	pCmdUI->SetCheck(bZoomLevelEqual100);

}

void CDIBManagerView::OnViewZoomToWindow() 
{
	// TODO: Add your command handler code here
	
	// zoom to the size of the containing window
	ZoomToWindow();
	if(GetZoomLevel()>ID_MAX_ZOOM_LEVEL)
	{
		SetZoomLevel(ID_MAX_ZOOM_LEVEL);
	}
	// if roll-up ZoomLevel dialog is active then
	// notify it that current zoom level is changed
	NotifyZoomChanged();
}

void CDIBManagerView::OnUpdateZoom(CCmdUI* pCmdUI)
{
	CString string="";
	string.Format(_T("%u%%"),GetZoomLevel());
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(string);
}

void CDIBManagerView::OnUpdateSize(CCmdUI* pCmdUI)
{
	// put length in bytes of image StatusBar 
	CString string="";
	CDIBManagerDoc* pDoc=GetDocument();
	if(pDoc!=NULL)
	{
		DWORD dwSize=pDoc->m_dwImageSize;
		// if length in bytes is less than 1 kilobyte then show it in bytes
		// otherwise in kilobytes
		if(dwSize<1024)
		{
			string.Format(_T("%u byte%s"),dwSize,dwSize>1 ? "s" : "");
		}
		else
		{
			string.Format(_T("%u.%1u KB"),dwSize/1024,((dwSize%1024)*10)/1024);
		}
	}
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(string);
}

void CDIBManagerView::OnUpdateParameters(CCmdUI* pCmdUI)
{
	// put the size of image on StatusBar
	CString string="";
	CDIBManagerDoc* pDoc=GetDocument();
	if(pDoc!=NULL)
	{
		CSize sizeDIB=pDoc->m_dib.GetSize();
		string.Format(_T("%4u:%u"),sizeDIB.cx,sizeDIB.cy);
	}
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(string);
}


void CDIBManagerView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	CDIBManagerDoc* pDoc=GetDocument();
	// we can save changes to current document only if 
	// image is of DIB format
	pCmdUI->Enable(pDoc->m_tf==CDIBManagerDoc::TF_DIB && 
		pDoc->IsModified());
}

void CDIBManagerView::OnFileExport() 
{
	// TODO: Add your command handler code here
	
	// we can save DIB image as JPEG
	CDIBManagerDoc* pDoc=GetDocument();

	CExportDlg exportDlg;

	// copy current DIB image to the temporary file that 
	// will be transformed into JPEG file
	CArchive ar(&exportDlg.m_tmpBMPFile, CArchive::store);
	pDoc->m_dib.Write(ar);
	ar.Close();
	exportDlg.m_tmpBMPFile.SeekToBegin();

	if(exportDlg.DoModal()==IDOK)
	{
	}

}

void CDIBManagerView::OnUpdateFileProtected(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck(GetDocument()->m_bProtected);
}

void CDIBManagerView::OnFileProtected() 
{
	// TODO: Add your command handler code here

	CDIBManagerDoc* pDoc=GetDocument();
	pDoc->m_bProtected=!pDoc->m_bProtected;
	// mark document as dirty only if we really changed the 
	// original protection
	if(pDoc->m_bProtected==pDoc->m_bInitiallyProtected)
	{
		pDoc->SetModifiedFlag(FALSE);
	}
	else
	{
		pDoc->SetModifiedFlag();
	}
}

void CDIBManagerView::OnDestroy() 
{
	COXZoomView::OnDestroy();
	
	// TODO: Add your message handler code here
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	
	// notify roll-up ZoomLevel Dialog that 
	// current view is about to be destroyed
	CScaleRollupDlg *pScaleRollupDlg=pApp->GetScaleRollupDlg();
	pScaleRollupDlg->ReleaseRecipient(this);
}

void CDIBManagerView::OnSetFocus(CWnd* pOldWnd) 
{
	COXZoomView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
	// as far as we get focus
	// simply set our view as message recipient
	CScaleRollupDlg *pScaleRollupDlg=((CDIBManagerApp *)AfxGetApp())->GetScaleRollupDlg();
	if(!pScaleRollupDlg->IsOwner( this ))
	{
		pScaleRollupDlg->SetRecipient(this);

		NotifyZoomChanged();
	}

	DoRealizePalette(TRUE,TRUE);
}

BOOL CDIBManagerView::OnRollupMessage(CWnd* pWndRollup,UINT message,UINT rollupID)
{
	// get messages from roll-up ZoomLevel Dialog
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;

	CScaleRollupDlg *pScaleRollupDlg=pApp->GetScaleRollupDlg();
	if(pScaleRollupDlg->GetRollupID() == rollupID)
	{
		switch(message)
		{
		// apply set zoom level to the current image
		case ID_APPLY:
			{
				SetZoomLevel(((CScaleRollupDlg*)pWndRollup)->m_nZoomLevel);
				break;
			}
		case IDCANCEL:
			{
				pScaleRollupDlg->DestroyWindow();	
				pMainFrame->m_bShowZoomLevelDlg=FALSE;
			}
		default:
			{
				TRACE2("Unhandled message %d from Rollup %d\n",message,rollupID);
				break;
			}
		}
    }
    // messages from other rollups are being ignored!!!
    return TRUE;
}

void CDIBManagerView::OnViewZoomLevelDlg() 
{
	// TODO: Add your command handler code here

	// open roll-up ZoomLevel Dialog
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;
	CDIBManagerDoc* pDoc=GetDocument();

	pMainFrame->m_bShowZoomLevelDlg=!pMainFrame->m_bShowZoomLevelDlg;
	CScaleRollupDlg *pScaleRollupDlg=pApp->GetScaleRollupDlg();
	if(pMainFrame->m_bShowZoomLevelDlg)
	{
		TCHAR szTitle[20];
		UTBStr::tcscpy(szTitle,20, _T("Zoom Level"));

		// set initial values of dialog vars
		pScaleRollupDlg->m_nZoomLevel=GetZoomLevel();
		CSize sizeDIB=pDoc->m_dib.GetSize();
		pScaleRollupDlg->m_nOrigWidth=sizeDIB.cx;
		pScaleRollupDlg->m_nOrigHeight=sizeDIB.cy;
	
		// create roll-up
		pScaleRollupDlg->CreateRollUp(this, 6458, szTitle);
		pScaleRollupDlg->ShowWindow(SW_SHOWNORMAL);

		pScaleRollupDlg->SendMessage(IDM_OX_RU_ARRANGE);

		SetFocus();
	}
	else
	{
		pScaleRollupDlg->DestroyWindow();
	}
}

void CDIBManagerView::NotifyZoomChanged() 
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;
	CDIBManagerDoc* pDoc=GetDocument();

	CScaleRollupDlg *pScaleRollupDlg=pApp->GetScaleRollupDlg();

	// if roll-up ZoomLevel Dialog is active then
	// set values of dialog vars
	if(pMainFrame->m_bShowZoomLevelDlg)
	{
		CSize sizeDIB=pDoc->m_dib.GetSize();
		pScaleRollupDlg->m_nOrigHeight=sizeDIB.cx;
		pScaleRollupDlg->m_nOrigWidth=sizeDIB.cy;

		pScaleRollupDlg->m_nZoomLevel=GetZoomLevel();
		pScaleRollupDlg->ShowControls();
	
		// notify roll-up to change values
		pScaleRollupDlg->RUpdateData(FALSE);
	}
}

// next 3 functions 
// use to display 256 and higher images when
// current palette is 8-bit color or less
BOOL CDIBManagerView::OnQueryNewPalette() 
{
	return DoRealizePalette(TRUE,TRUE)>0 ? TRUE : FALSE;
}

void CDIBManagerView::OnPaletteChanged(CWnd* pFocusWnd)
{
    if(pFocusWnd!=this)
	{
		DoRealizePalette(TRUE,FALSE);
    }
}

UINT CDIBManagerView::DoRealizePalette(BOOL bRedraw, BOOL bForeground)
{
	UINT nCount=0;
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	// applicable only when current palette is 8-bit or less
	if(pApp->m_nColors<=8)
	{
		CDIBManagerDoc* pDoc=GetDocument();
		// retrieve image palette
		CPalette* pPalette=pDoc->GetDIBPalette();
		if(pPalette!=NULL)
		{
			CClientDC dc(this);
			CPalette* pOldPalette=dc.SelectPalette(pPalette,!bForeground);
			nCount=dc.RealizePalette();
			if(nCount>0)
			{
				// if image pallete is selected then
				// redraw image if needed
				if(bRedraw)
				{
					Invalidate();
				}
				dc.SelectPalette(pOldPalette,!bForeground);
			}
		}
    }

	return nCount;
}


void CDIBManagerView::OnViewImageInfo() 
{
	// TODO: Add your command handler code here
	CImageInfoDlg dlgInfo;
	dlgInfo.pDoc=GetDocument();
	dlgInfo.DoModal();
}

void CDIBManagerView::OnViewResampleImage() 
{
	// TODO: Add your command handler code here
	CDIBManagerDoc* pDoc=GetDocument();

	CResampleImageDlg dlgResample;

	// we provide convertion only from 24-bit image to 
	// 8-bit image by means of dithering
	dlgResample.m_bCanConvert=pDoc->m_dib.GetNumBitsPerPixel()==24 ? TRUE : FALSE;
	// we can resize only 24 and 8 bit DIB images
	dlgResample.m_bCanResize=pDoc->m_dib.GetNumBitsPerPixel()==24 || 
		pDoc->m_dib.GetNumBitsPerPixel()==8 ? TRUE : FALSE;
	dlgResample.m_nCurrentZoomLevel=GetZoomLevel();

	dlgResample.m_bConvertTo=FALSE;
	dlgResample.m_bMatchZoomLevel=FALSE;
	dlgResample.m_bMaintainRatio=TRUE;

	CSize sizeDIB=pDoc->m_dib.GetSize();
	dlgResample.m_sHeightOrig.Format(_T("%u"),sizeDIB.cy);
	dlgResample.m_sWidthOrig.Format(_T("%u"),sizeDIB.cx);
	dlgResample.m_nWidthPixels=sizeDIB.cx;
	dlgResample.m_nHeightPixels=sizeDIB.cy;
	dlgResample.m_nOrigWidth=sizeDIB.cx;
	dlgResample.m_nOrigHeight=sizeDIB.cy;

	dlgResample.m_nWidthPercents=100;
	dlgResample.m_nHeightPercents=100;

	if(dlgResample.DoModal()==IDOK)
	{
		BOOL bChanged=FALSE;
		if(dlgResample.m_bCanConvert && dlgResample.m_bConvertTo)
		{
			// try to dither the image
			if(!pDoc->m_dib.HalfToneDitherDIB())
			{
				AfxMessageBox(_T("Cannot convert image!"));
			}
			else
			{
				bChanged=TRUE;
			}
		}
		if(dlgResample.m_bCanResize &&(sizeDIB.cx!=(int)dlgResample.m_nWidthPixels || 
			sizeDIB.cy!=(int)dlgResample.m_nHeightPixels))
		{
			// try to resize
			if(!pDoc->m_dib.ResizeDIB(dlgResample.m_nWidthPixels,
				dlgResample.m_nHeightPixels))
			{
				AfxMessageBox(_T("Cannot resize image!"));
			}
			else
			{
				bChanged=TRUE;
			}
		}
		if(bChanged)
		{
			// if we changed image we have to mark it as dirty,
			pDoc->SetModifiedFlag(TRUE);
			// set new ScrollSize of view window
			CRect rectDIB=CRect(0,0,dlgResample.m_nWidthPixels,
				dlgResample.m_nHeightPixels);
			SetDeviceScrollSizesRelative(MM_TEXT,rectDIB);
			// redraw image
			Invalidate();
		}
	}
}

BOOL CDIBManagerView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(IsSmoothScrolling())
	{
		//
		// First handle left/right scroll messages. If scrolling by page,
		// scroll m_nPageSlices times rather than 1. If scrolling by line,
		// scroll m_nLineSlices times.
		//
		BYTE nCode=LOBYTE(nScrollCode);

		if((nCode==SB_PAGELEFT) ||(nCode==SB_PAGERIGHT) ||
			(nCode==SB_LINELEFT) ||(nCode==SB_LINERIGHT)) 
		{
			int nCount=0;
			int nInc=0;
			int nFinalInc=0;
			int nLineCode=0;

			switch(nCode) 
			{
			case SB_PAGELEFT:
				{
					nLineCode=SB_LINELEFT;
					nInc=m_pageDev.cx/m_nPageSlices;
					nFinalInc=m_pageDev.cx%m_nPageSlices;
					nCount=m_nPageSlices;
					break;
				}
			case SB_PAGERIGHT:
				{
					nLineCode=SB_LINERIGHT;
					nInc=m_pageDev.cx/m_nPageSlices;
					nFinalInc=m_pageDev.cx%m_nPageSlices;
					nCount=m_nPageSlices;
					break;
				}

			case SB_LINELEFT:
				{
					nLineCode=SB_LINELEFT;
					nInc=m_lineDev.cx/m_nLineSlices;
					nFinalInc=m_lineDev.cx%m_nLineSlices;
					nCount=m_nLineSlices;
					break;
				}

			case SB_LINERIGHT:
				{
					nLineCode=SB_LINERIGHT;
					nInc=m_lineDev.cx/m_nLineSlices;
					nFinalInc=m_lineDev.cx%m_nLineSlices;
					nCount=m_nLineSlices;
					break;
				}
			}

			int nOldLineSize=m_lineDev.cx;
			BOOL bResult=FALSE;
			DWORD dwTime=0;

			while(nCount--) 
			{
				DWORD dwCurrentTime=::GetCurrentTime();
				DWORD dwElapsedTime=dwCurrentTime-dwTime;
				if(dwElapsedTime<m_dwWaitingTime)
				{
					::Sleep(m_dwWaitingTime-dwElapsedTime);
				}
				dwTime=dwCurrentTime;

				m_lineDev.cx=nInc;
				BOOL bScrolled=COXZoomView::OnScroll(MAKEWORD(nLineCode,-1),nPos);
				m_lineDev.cx=nOldLineSize;

				if(!bScrolled)
					return bResult;

				bResult=TRUE;
			}

			if(nFinalInc) 
			{
				m_lineDev.cx=nFinalInc;
				if(!COXZoomView::OnScroll(MAKEWORD(nLineCode,-1),nPos))
					bResult=TRUE;
				m_lineDev.cx=nOldLineSize;
			}
			return bResult;
		}

		//
		// Next handle up/down scroll messages. If scrolling by page,
		// scroll m_nPageSlices times rather than 1. If scrolling by line,
		// scroll m_nLineSlices times.
		//
		nCode=HIBYTE(nScrollCode);

		if((nCode==SB_PAGEUP) ||(nCode==SB_PAGEDOWN) ||
			(nCode==SB_LINEUP) ||(nCode==SB_LINEDOWN)) 
		{
			int nCount=0;
			int nInc=0;
			int nFinalInc=0;
			int nLineCode=0;

			switch(nCode) 
			{
			case SB_PAGEUP:
				{
					nLineCode=SB_LINEUP;
					nInc=m_pageDev.cy/m_nPageSlices;
					nFinalInc=m_pageDev.cy%m_nPageSlices;
					nCount=m_nPageSlices;
					break;
				}

			case SB_PAGEDOWN:
				{
					nLineCode=SB_LINEDOWN;
					nInc=m_pageDev.cy/m_nPageSlices;
					nFinalInc=m_pageDev.cy%m_nPageSlices;
					nCount=m_nPageSlices;
					break;
				}

			case SB_LINEUP:
				{
					nLineCode=SB_LINEUP;
					nInc=m_lineDev.cy/m_nLineSlices;
					nFinalInc=m_lineDev.cy%m_nLineSlices;
					nCount=m_nLineSlices;
					break;
				}

			case SB_LINEDOWN:
				{
					nLineCode=SB_LINEDOWN;
					nInc=m_lineDev.cy/m_nLineSlices;
					nFinalInc=m_lineDev.cy%m_nLineSlices;
					nCount=m_nLineSlices;
					break;
				}
			}

			int nOldLineSize=m_lineDev.cy;
			BOOL bResult=FALSE;
			DWORD dwTime=0;

			while(nCount--) 
			{
				DWORD dwCurrentTime=::GetCurrentTime();
				DWORD dwElapsedTime=dwCurrentTime-dwTime;
				if(dwElapsedTime<m_dwWaitingTime)
				{
					::Sleep(m_dwWaitingTime-dwElapsedTime);
				}
				dwTime=dwCurrentTime;

				m_lineDev.cy=nInc;
				BOOL bScrolled=COXZoomView::OnScroll(MAKEWORD(-1,nLineCode),nPos);
				m_lineDev.cy=nOldLineSize;

				if(!bScrolled)
					return bResult;

				bResult=TRUE;
			}

			if(nFinalInc) 
			{
				m_lineDev.cy=nFinalInc;
				if(!COXZoomView::OnScroll(MAKEWORD(-1,nLineCode),nPos))
					bResult=TRUE;
				m_lineDev.cy=nOldLineSize;
			}
			return bResult;
		}
	}
	//
	// If we make it to here, the scroll message wasn't handled above.
	// Call the base class's OnScroll function and let it do the work.
	//
	return COXZoomView::OnScroll(nScrollCode, nPos, bDoScroll);
}
