// resviewerView.cpp : implementation of the CResviewerView class
//

#include "stdafx.h"
#include "resviewer.h"
#include "resviewerDoc.h"
#include "resviewerView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//LRESULT RsrcDefDlgProc( HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam)
//{ 
// 
//
//
//	switch (Msg)
//	{
//
//		case WM_CREATE:
//			break;
//		case WM_CLOSE:
//			EndDialog(hDlg,FALSE);
//			break;
//		
//	}
	
//	return FALSE;

//}
 

/////////////////////////////////////////////////////////////////////////////
// CResviewerView

IMPLEMENT_DYNCREATE(CResviewerView, CView)

BEGIN_MESSAGE_MAP(CResviewerView, CView)
	//{{AFX_MSG_MAP(CResviewerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResviewerView construction/destruction

CResviewerView::CResviewerView()
{
	// TODO: add construction code here
	m_lpDlgTmplt = NULL;
	m_dialogRsrcWnd = NULL;
	m_mydlg = NULL;

}

CResviewerView::~CResviewerView()
{
	if (m_mydlg != NULL)
		delete m_mydlg;

}

BOOL CResviewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CResviewerView drawing

void CResviewerView::OnDraw(CDC* pDC)
{
	// onupdate allread set the resource values
	// so here we find out the resource type 
	// and use the persrcinst to get acces to the 
	// resource data. the Bitmaps are converted to DIB's
	// and Bitblt 'ed to the screen. icons and cursors are 
	// are in the proper format so just Create them from the 
	// raw data. 


	LPBITMAPINFO lpBMI;
	LPBITMAPINFOHEADER lpBMIH;
	CResviewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	PERsrcTbl* RsrcTbl = pDoc->GetPERsrc();
	
	if (!RsrcTbl)
	{
		return;
	}



	PERsrcType *RsrcType = RsrcTbl->GetResourceTypeById((WORD)m_dwRsrcType);
	if (!RsrcType)
	{
		return;
	}

	PERsrcInst *RsrcInst;

	if (m_dwRsrcID)  // got resource ID number?
	{
		RsrcInst = 
			RsrcType->GetResourceInstById((WORD)m_dwRsrcID);
		if (!RsrcInst)
		{
			return;
		}
	}
	else  // got resource name instead
	{
		RsrcInst = 
			RsrcType->GetResourceInstByName(m_szRsrcName);
		if (!RsrcInst)
		{
			return;
		}
	}


	

	if (m_dwRsrcType == (WORD)RT_BITMAP)
	{
		lpBMI = (LPBITMAPINFO)RsrcInst->GetData();
		lpBMIH = (LPBITMAPINFOHEADER)lpBMI;
		INT iNumColors;
		if (lpBMIH->biBitCount <= 8)
			iNumColors = (1 << lpBMIH->biBitCount);
		else
			iNumColors = 0;

		LPTSTR bmp = (LPTSTR)lpBMIH + 
							 lpBMIH->biSize + 
							 (iNumColors * sizeof(RGBQUAD));
		
		HBITMAP dibBM = CreateDIBitmap(pDC->m_hDC,
										lpBMIH,
										CBM_INIT,
										bmp,
										lpBMI,
										DIB_RGB_COLORS);

		
		CPoint size(lpBMIH->biWidth,lpBMIH->biHeight);
		pDC->DPtoLP(&size);
		CPoint org(0,0);
		pDC->DPtoLP(&org);

		CRect rect;
		GetClientRect(&rect);
		pDC->DPtoLP(&rect);
		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);
		CBitmap myBM;
		CBitmap *BM;
		BM = myBM.FromHandle(dibBM);
		CBitmap* pOldBM = dcMem.SelectObject(BM);
		dcMem.SetMapMode(pDC->GetMapMode());

		//TRACE("RsrcID=%i\n",m_dwRsrcID);
		//TRACE("Sizex=%i\n",size.x);
		//TRACE("Sizey=%i\n",size.y);
		//TRACE("NumColor=%i\n",iNumColors);
		//TRACE("Height=%i\n",lpBMIH->biHeight);
		//TRACE("Width=%i\n",lpBMIH->biWidth);
		//TRACE("Compression=%i\n",lpBMIH->biCompression);
		
		pDC->BitBlt(0,0,size.x,size.y,
					&dcMem,org.x,org.y,
					SRCCOPY);
		dcMem.SelectObject(pOldBM);
//		TRACE("made it\n",DIBBM);
	}


	if (m_dwRsrcType == (WORD)RT_ICON)
	{
		HICON icon;
		
		
		lpBMIH = (LPBITMAPINFOHEADER)RsrcInst->GetData();
		DWORD IconSize = RsrcInst->Size();
		
		icon = CreateIconFromResourceEx((PBYTE)lpBMIH,
							IconSize,
							TRUE,
							0x00030000,
							lpBMIH->biWidth,
							lpBMIH->biHeight/2,
							0);
		//LR_DEFAULTCOLOR);

							
		if (icon)
		{
			DrawIconEx( pDC->m_hDC,0,0,icon,
							lpBMIH->biWidth,
							lpBMIH->biHeight/2,0,NULL,
							DI_NORMAL);
				
			//pDC->DrawIcon(0,0,icon);
		}

	}

	if (m_dwRsrcType == (WORD)RT_CURSOR)
	{
		HICON icon;
		
				
		lpBMIH = (LPBITMAPINFOHEADER)RsrcInst->GetData();
		lpBMI = (LPBITMAPINFO)lpBMIH;
		
		DWORD IconSize = RsrcInst->Size();
		
		icon = CreateIconFromResourceEx((PBYTE)lpBMIH,
							IconSize,
							FALSE,
							0x00030000,
							lpBMIH->biWidth,
							lpBMIH->biHeight,
							LR_DEFAULTCOLOR);
		//LR_DEFAULTCOLOR);

							
		if (icon)
		{
			pDC->DrawIcon(0,0,icon);
		}

	}

	//if (m_dwRsrcType == (WORD)RT_DIALOG)
	//{

	//	DLGTEMPLATE *lpDlg;
	//	DLGTEMPLATEEX *lpDlgx;

	//	lpDlg = (DLGTEMPLATE*)RsrcInst->GetData();
	//	lpDlgx = (DLGTEMPLATEEX*)RsrcInst->GetData();
		
	//	DWORD dwDlgSize = RsrcInst->Size();
		//dwDlgSize = dwDlgSize;
	//}

	delete RsrcType;
	delete RsrcInst;
	return;


	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CResviewerView printing

BOOL CResviewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CResviewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CResviewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CResviewerView diagnostics

#ifdef _DEBUG
void CResviewerView::AssertValid() const
{
	CView::AssertValid();
}

void CResviewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CResviewerDoc* CResviewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CResviewerDoc)));
	return (CResviewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResviewerView message handlers

void CResviewerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	

	// when the doc updates the view we make sure 
	// we have a resource directory if not clear the view
	// then see if a parm was passed from the tree
	// meaning that the tree is requesting an update.
	//
	// if not doing a dialog resource then invalidate the rect
	// to force ondraw to handle the bmp and ico resources.
	//
	// if a dialog then call the dialog routine to diaply it 
	// but bypass the on draw method. be sure to delete any 
	// previous dialog first.


	CResviewerDoc* pDoc = (CResviewerDoc*)GetDocument();
	PERsrcTbl* RsrcTbl = pDoc->GetPERsrc();
	
	if (!RsrcTbl)
	{
		m_dwRsrcID = 0;
		m_dwRsrcType = 0;
		CRect rect;
		GetClientRect(rect);
		InvalidateRect(rect);
		return;
		
	}

	if (lHint != NULL)
	{
		RESINFO *Res;

		Res = (LPRESINFO)lHint;
		m_dwRsrcID = Res->riIDNum;
		m_dwRsrcType = Res->riType;
		strcpy(m_szRsrcName,Res->riIDName);
		
		if (m_mydlg != NULL)
		{
			m_mydlg->EndDialog(0);
			delete m_mydlg;
			m_mydlg = NULL;
		}
		if (m_dwRsrcType == (WORD)RT_DIALOG)
		{
			

			CreateResourceDialog();
			return;
		}

		CRect rect;
		GetClientRect(rect);
		InvalidateRect(rect);
		return;
		
	}
	
}

void CResviewerView::CreateResourceDialog()
{
	// use the rsrcinst to get a point to the dialog template
	// use the dialog template to dynamically create and open 
	// the dialog window.
	//
	//

	CResviewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	PERsrcTbl* RsrcTbl = pDoc->GetPERsrc();
	
	if (!RsrcTbl)
	{
		return;
	}



	PERsrcType *RsrcType = RsrcTbl->GetResourceTypeById((WORD)m_dwRsrcType);
	if (!RsrcType)
	{
		return;
	}

	PERsrcInst *RsrcInst;

	if (m_dwRsrcID)  // got resource ID number?
	{
		RsrcInst = 
			RsrcType->GetResourceInstById((WORD)m_dwRsrcID);
		if (!RsrcInst)
		{
			return;
		}
	}
	else  // got resource name instead
	{
		RsrcInst = 
			RsrcType->GetResourceInstByName(m_szRsrcName);
		if (!RsrcInst)
		{
			return;
		}
	}

	m_mydlg = new CDialog();


	ULONG RsrcSize;
	LPDLGTEMPLATEEX lpDlgEX;
	LPDLGTEMPLATE   lpDlg;

	RsrcSize = (ULONG)RsrcInst->Size();
	//m_lpGHDlgTmplt = GlobalAlloc(0,RsrcSize);
	//m_lpDlgTmplt = GlobalLock(m_lpGHDlgTmplt);

	m_lpDlgTmplt = malloc(RsrcSize);
	memcpy(m_lpDlgTmplt,RsrcInst->GetData(),RsrcSize);

	LPBYTE dlgbytes = (LPBYTE)m_lpDlgTmplt;
	lpDlgEX = (LPDLGTEMPLATEEX)dlgbytes;
	lpDlg = (LPDLGTEMPLATE)dlgbytes;

		
	if ((WORD)dlgbytes+2 == 0xFFFF)
	{  // extended dlg
		lpDlgEX->style |= WS_VISIBLE;
			
	}
	else
	{  // standard dlg;
		lpDlg->style |= WS_VISIBLE;
		
		
	}



	//m_dialogRsrcWnd = CreateDialogIndirect(AfxGetInstanceHandle(),
	//								(LPDLGTEMPLATE)dlgbytes,
	//								AfxGetMainWnd()->m_hWnd,
	//								(DLGPROC)RsrcDefDlgProc);
	BOOL dlgOK;

	dlgOK = m_mydlg->CreateIndirect((LPCDLGTEMPLATE)dlgbytes);

	if (!dlgOK)
	{
		AfxMessageBox("Dialog Cannot be Displayed");
		delete m_mydlg;
		m_mydlg = NULL;
	}
	
	free(m_lpDlgTmplt);
	m_lpDlgTmplt = NULL;

	delete RsrcType;
	delete RsrcInst;

	return;
	//::ShowWindow(m_dialogRsrcWnd,SW_SHOWNORMAL);

}
