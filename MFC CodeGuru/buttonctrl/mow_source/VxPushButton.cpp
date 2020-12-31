/////////////////////////////////////////////////////////////////////////=
// VxPushButton.cpp : implementation file

//#include "VxMenu.h"

#include "hello.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CVxPushButton

BEGIN_MESSAGE_MAP(CVxPushButton, CButton)
//{{AFX_MSG_MAP(CVxPushButton)
ON_WM_CTLCOLOR_REFLECT()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_TIMER()
ON_CONTROL_REFLECT(BN_CLICKED, uiPushBtnCB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CVxPushButton::CVxPushButton()
{
	m_clrText =  GetSysColor (COLOR_BTNTEXT);
	m_clrBack = GetSysColor (COLOR_BTNFACE);
	m_brBackground.CreateSolidBrush (m_clrBack);
	m_crText = m_clrText;
	m_bLBtnDown = FALSE;
	m_idCursor = 0;
	m_idBitmap = 0;
	m_uniqueID = 0;

	m_font.CreateFont(20,0,0,0,700,0,0,0,
				ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE,
				"arial" );


}

CVxPushButton::~CVxPushButton()
{
	if ((HBRUSH) m_brBackground != NULL)
		m_brBackground.DeleteObject ();
}



/////////////////////////////////////////////////////////////////////////=
////
// CVxPushButton message handlers

// What this function does is it adds a unique SOL id to 
// the button object. This unique ID is different for each
// push button.
// This function was written primarily to keep the 
// code structure similarity between MOTIF and NT
		
void CVxPushButton::AddCallbackID(int Idx)
{
	m_uniqueID = Idx;
}

void CVxPushButton::uiPushBtnCB()
{

	char s[64];

	sprintf(s,"BUTTON ID : %d", this->GetDlgCtrlID()); 
	// m_uniqueID also holds the same value as this->GetDlgCtrlID()
	// i.e. if i have done a good job of calling AddCallbackID function
	// for each pushbutton
	
	MessageBox( s, "From uiPushBtnCB...");

	// Now lets hide the drop down window
	CVxOptPopup *pWnd = (CVxOptPopup *)this->GetParent();
	ASSERT(pWnd);

	CVxOptPicker *comboBoxWnd = pWnd->m_pParent;
	ASSERT(comboBoxWnd);

	CString str;
	this->GetWindowText(str);

	comboBoxWnd->m_CurText   = str ;
	comboBoxWnd->m_CurBitmap = this->m_idBitmap ;
	comboBoxWnd->m_CurButton = (CWnd *)this ;

	//comboBoxWnd->m_pCurButton = this ; // this->GetWindowText(comboBoxWnd->m_pCurButton);

	comboBoxWnd->m_PopupWndVisible	= 0 ;
	pWnd->ShowWindow(SW_HIDE);

}


HBRUSH CVxPushButton::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO: Change any attributes of the DC here
	// TODO: Return a non-NULL brush if the parent's handler 
	// should not be called

	return NULL;
}

void CVxPushButton::OnMouseMove(UINT nFlags, CPoint point)
{
	//Here I will set a timer and see if the current cursor 
	//is within our boundaries if
	// not kill the timer and remove the current highlighting
	SetTimer (1,55,NULL);
	CButton::OnMouseMove(nFlags, point);
}


void CVxPushButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown= TRUE;
	CButton::OnLButtonDown(nFlags, point);
}

void CVxPushButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown= FALSE;
	//Take out the cursor
	CButton::OnLButtonUp(nFlags, point);
}

void CVxPushButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS != NULL);

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rect;
	HBITMAP hBitmap =NULL;

    // draw the colored rectangle portion
	rect.CopyRect(&lpDIS->rcItem);

    // draw the up/down/focused/disabled state

	UINT state = lpDIS->itemState;
    if ( (state & ODS_SELECTED) )
    {
       // draw the down edges
	
		CBrush *pOldBrush = pDC->SelectObject(&m_brBackground);
		pDC->RoundRect(rect.left, rect.top, rect.Width(), rect.Height(), 2, 2);
		pDC->SelectObject(pOldBrush);

		if (m_idBitmap)
			hBitmap = (HBITMAP) LoadImage (AfxGetInstanceHandle(),
											MAKEINTRESOURCE (m_idBitmap), 
											IMAGE_BITMAP,0,0,
				//LR_DEFAULTCOLOR|LR_LOADTRANSPARENT);
				LR_DEFAULTCOLOR|LR_LOADTRANSPARENT);

	
		//pDC->Draw3dRect (rect,GetSysColor (COLOR_BTNSHADOW),
		//						GetSysColor(COLOR_HIGHLIGHT));

		pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
		rect.InflateRect(-2,-2);
		pDC->FillSolidRect (rect,m_clrBack); //m_clrBack);

    }
    else
    {
	
		CBrush *pOldBrush = pDC->SelectObject(&m_brBackground);
		pDC->RoundRect(rect.left, rect.top, rect.Width(), rect.Height(), 2, 2);
		pDC->SelectObject(pOldBrush);
		if (m_idBitmap)
			hBitmap = 	(HBITMAP) LoadImage (AfxGetInstanceHandle(),
						MAKEINTRESOURCE (m_idBitmap),
						// Here if you take out DEFAULTCOLOR and put mono
						// chrome then the bitmap will be black and white
						//IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);//LR_MONOCHROME);
						
						// LR_LOADMAP3DCOLORS with TRANSPARENT will make
						// the backgroud of the bitmap to be COLOR_3DFACE
						IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
        // draw the up edges
		//pDC->Draw3dRect (rect,m_clrBack,m_clrBack);
		
		pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
		rect.InflateRect(-2,-2);
		pDC->FillSolidRect (rect,m_clrBack); //m_clrBack);

    }

    // draw the text if there is any
	//We have to paint the text only if the image is nonexistant
	CString strText;
	GetWindowText(strText);
	if ( !strText.IsEmpty())
	{
		LOGFONT lf;
		ZeroMemory ((PVOID) &lf,sizeof (LOGFONT));
		CFont * pFont = &m_font ; //GetFont();
	
		CFont dispFont;
	
		pFont->GetLogFont (&lf);
	
		if ((state & ODS_SELECTED))
		{
			lf.lfWeight = FW_EXTRABOLD;
			dispFont.CreateFontIndirect (&lf);
			pFont = pDC->SelectObject (&dispFont);
		
			//While selected move the text a bit
			rect.top +=2;
			rect.left +=2;
			rect.right -=2;
			rect.bottom -=2;
		
		}
	
		int         iOldMode = pDC->GetBkMode();
		COLORREF    crOldText = pDC->GetTextColor();
	
		pDC->SetBkMode( TRANSPARENT );
		pDC->SetTextColor( m_crText );
	
		if (state & ODS_FOCUS )
		{
			if (!(state & ODS_SELECTED))
			{
				lf.lfUnderline = FALSE ; //TRUE;
				lf.lfWeight = FW_LIGHT;
				dispFont.CreateFontIndirect (&lf);
				pFont = pDC->SelectObject (&dispFont);
				if (m_idBitmap)
					hBitmap =(HBITMAP) LoadImage (AfxGetInstanceHandle(),
										MAKEINTRESOURCE (m_idBitmap),
										IMAGE_BITMAP,0,0,
						LR_DEFAULTCOLOR |LR_LOADTRANSPARENT);
						//LR_DEFAULTCOLOR|LR_LOADMAPCOLORS|LR_LOADTRANSPARENT);

			}
		}

		if (state & ODS_DISABLED)
		{
			CBrush grayBrush;
			grayBrush.CreateSolidBrush (GetSysColor (COLOR_GRAYTEXT));
			//pDC->GrayString = (&grayBrush,NULL,(LPARAM)((LPCSTR)strText),
			//						-1, rect.left, rect.top,rect.Width(),
			//						rect.Height());
			pDC->GrayString(&grayBrush,NULL,(LPARAM)((LPCSTR)strText),
									-1, rect.left, rect.top,rect.Width(),
									rect.Height());
		}
		else
		{
			if (!hBitmap)
				pDC->DrawText(strText, rect, /*DT_LEFT*/ DT_CENTER | DT_VCENTER | DT_SINGLELINE );
			else
			{
				CDC memdc;
				CBitmap bmp;
				CBitmap *poldbmp;
				bmp.Attach (hBitmap);
				BITMAP bitmap;
				bmp.GetBitmap (&bitmap);

				memdc.CreateCompatibleDC( pDC );
				// Select the bitmap into the DC
				poldbmp = memdc.SelectObject( &bmp);
				// Copy (BitBlt) bitmap from memory DC to screen DC
		
				// I want it to look like a proper button hence
				pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
				rect.InflateRect(-2,-2);

				pDC -> StretchBlt( rect.left, rect.top,
										 rect.right-rect.left, 
										 rect.bottom -rect.top, &memdc, 0,0,
										 bitmap.bmWidth,bitmap.bmHeight,SRCCOPY );
				//pDC -> BitBlt( rect.left, rect.top,
				//						 rect.right-rect.left, 
				//						 rect.bottom -rect.top, &memdc, 0,0,
				//						 SRCCOPY );

				memdc.SelectObject( poldbmp );
				bmp.Detach ();
			}
		
		}
	
		pDC->SetBkMode( iOldMode );
		pDC->SetTextColor( crOldText );
	
		pDC->SelectObject (pFont); //set it to the old font
		dispFont.DeleteObject ();
	}


	if ( (state & ODS_DISABLED) )
    {
        //AST - how should we indicate this???
    }
}


void CVxPushButton::OnTimer(UINT nIDEvent)
{
	POINT pt;
	static BOOL pPainted = FALSE;

	GetCursorPos(&pt);
	CRect rect;
	GetWindowRect (rect);
	
	if (m_bLBtnDown)
	{
		KillTimer (1);
		//Take the cursor out if the man has pressed de button
		if (m_idCursor)
		{
			::SetCursor (AfxGetApp () -> LoadStandardCursor (IDC_ARROW));
		}

		if (pPainted)
			InvalidateRect (NULL);

		pPainted = FALSE;
		return;
	}

	if (!rect.PtInRect (pt))
	{
		KillTimer (1);
		//Take out the cursor if the thing is out
		if (m_idCursor)
		{
			::SetCursor (AfxGetApp () -> LoadStandardCursor (IDC_ARROW));
		}

		if (pPainted)
			InvalidateRect (NULL);
		pPainted = FALSE;
		return;
	}
	else
	{

		if (pPainted)
			return;
		else
			pPainted = TRUE;

		//Here we need to put the cursor in for the settings
		if (m_idCursor)
		{
			HCURSOR hCursor = AfxGetApp () -> LoadCursor (m_idCursor);
			::SetCursor (hCursor);
		}


		CDC *pDC = GetDC ();

		if (!m_idBitmap)
		{
			LOGFONT lf;
			ZeroMemory ((PVOID) &lf,sizeof (LOGFONT));
			CFont * pFont = &m_font ; //GetFont();
		
			CFont dispFont;
			pFont->GetLogFont (&lf);
			lf.lfUnderline = FALSE; //TRUE;
			lf.lfWeight = FW_BOLD;
		
			int         iOldMode = pDC->GetBkMode();
			COLORREF    crOldText = pDC->GetTextColor();
		
			dispFont.CreateFontIndirect (&lf);
		
			pDC->SetBkMode( TRANSPARENT );
			pDC->SetTextColor( m_crText);
		
			pDC -> SelectObject (dispFont);
		
			CString strText;
			GetWindowText (strText);
		
			CRect rect;
			GetClientRect (rect);
			

			//rect.InflateRect(-3,-3);
			pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
		
			rect.InflateRect(-2,-2);
			pDC->FillSolidRect (rect,RGB(235,235,235)); //m_clrBack);

			pDC->DrawText(strText, rect, /* DT_LEFT */ DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		
			pDC->SetBkMode( iOldMode );
			pDC->SetTextColor( crOldText );
		
			pDC->SelectObject (pFont); //set it to the old font
			dispFont.DeleteObject ();
		}
		else
		{
			HBITMAP hBitmap =(HBITMAP) LoadImage (AfxGetInstanceHandle(),
									MAKEINTRESOURCE (m_idBitmap), IMAGE_BITMAP,
						0,0,LR_DEFAULTCOLOR|LR_LOADTRANSPARENT );
						//0,0,LR_DEFAULTCOLOR|LR_LOADMAPCOLORS|LR_LOADTRANSPARENT);
		
			GetClientRect (rect);
			CDC memdc;
			CBitmap bmp;
			CBitmap *poldbmp;
			bmp.Attach (hBitmap);
			BITMAP bitmap;
			bmp.GetBitmap (&bitmap);
			memdc.CreateCompatibleDC( pDC );
			// Select the bitmap into the DC
			poldbmp = (CBitmap *) memdc.SelectObject( &bmp );
			// Copy (BitBlt) bitmap from memory DC to screen DC

			// I want it to look like a proper button hence
			pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);
			rect.InflateRect(-2,-2);

			pDC -> StretchBlt( rect.left,rect.top,
								    rect.right-rect.left, 
									 rect.bottom -rect.top, &memdc,0,0,
									bitmap.bmWidth,bitmap.bmHeight, SRCCOPY );
			memdc.SelectObject( poldbmp );

		}
		ReleaseDC (pDC);
	}

	CButton::OnTimer(nIDEvent);
}

void CVxPushButton::SetBkgndColor (COLORREF rgb)
{
	m_clrBack = rgb;
	if ((HBRUSH)m_brBackground != NULL)
		m_brBackground.DeleteObject();
	m_brBackground.CreateSolidBrush (m_clrBack);
}

void CVxPushButton::SetTextColor (COLORREF rgb)
{
	m_clrText = rgb;
	m_crText = m_clrText;
}


void CVxPushButton::SetCursor(UINT idCursor)
{
	m_idCursor = idCursor;
}

void CVxPushButton::SetBitmap2 (UINT idBmp)
{
	m_idBitmap = idBmp;
}

UINT CVxPushButton::GetBitmap2()
{

	return m_idBitmap;

}
