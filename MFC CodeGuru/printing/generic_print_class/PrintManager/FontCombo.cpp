// FontCombo.cpp : implementation file
//

#include "stdafx.h"
#include "PrintManager.h"
#include "FontCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_INITFONTS	(WM_USER + 123)

/////////////////////////////////////////////////////////////////////////////
// CFontCombo

CFontCombo::CFontCombo()
{
	m_enStyle = FONTS;
	m_clrHilight = GetSysColor (COLOR_HIGHLIGHT);
	m_clrNormalText = GetSysColor (COLOR_WINDOWTEXT);
	m_clrHilightText = GetSysColor (COLOR_HIGHLIGHTTEXT);
	m_clrBkgnd = GetSysColor (COLOR_WINDOW);
	m_bInitOver = FALSE;
}

CFontCombo::CFontCombo(STYLE enStyle)
{
	m_enStyle = enStyle;
	m_clrHilight = GetSysColor (COLOR_HIGHLIGHT);
	m_clrNormalText = GetSysColor (COLOR_WINDOWTEXT);
	m_clrHilightText = GetSysColor (COLOR_HIGHLIGHTTEXT);
	m_clrBkgnd = GetSysColor (COLOR_WINDOW);
	m_bInitOver =FALSE;
}

CFontCombo::~CFontCombo()
{
}


BEGIN_MESSAGE_MAP(CFontCombo, CComboBox)
	//{{AFX_MSG_MAP(CFontCombo)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_INITFONTS,OnInitFonts)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontCombo message handlers


void CFontCombo::OnDestroy() 
{
	if (m_enStyle == FONTS)
	{
		int nCount;
		nCount = GetCount ();
		for (int i = 0; i < nCount; i++)
		{
			delete ((LOGFONT*)GetItemData (i)); //delete the LOGFONTS actually created..
		}
	}
	// TODO: Add your message handler code here
	CComboBox::OnDestroy();
}

int CFontCombo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (m_enStyle == FONTS)
	{
		PostMessage (WM_INITFONTS,0,0);
	}
	return 0;
}

void CFontCombo::DrawFont(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rect;
	TRACE0 ("In Draw Font\n");

	// draw the colored rectangle portion
	rect.CopyRect(&lpDIS->rcItem);
	pDC->SetBkMode( TRANSPARENT );

	if (lpDIS->itemState & ODS_SELECTED)
	{
		pDC->FillSolidRect (rect,m_clrHilight);
		pDC->SetTextColor (m_clrHilightText);
	}
	else
	{
		pDC->FillSolidRect (rect,m_clrBkgnd);
		pDC->SetTextColor (m_clrNormalText);
	}

	if ((int)(lpDIS->itemID) < 0) // Well its negetive so no need to draw text
	{
	}
	else
	{
		CString strText;
		GetLBText (lpDIS->itemID,strText);
		CFont newFont;
		CFont *pOldFont;
		((LOGFONT*)lpDIS->itemData)->lfHeight = 90; //9 point size
		((LOGFONT*)lpDIS->itemData)->lfWidth = 0;
		newFont.CreatePointFontIndirect ((LOGFONT*)lpDIS->itemData);
		pOldFont = pDC->SelectObject (&newFont);
		pDC->DrawText(strText, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject (pOldFont);
		newFont.DeleteObject ();
	}
}

void CFontCombo::InitFonts ()
{
	CDC *pDC = GetDC ();
	ResetContent (); //Delete whatever is there
	EnumFonts (pDC->GetSafeHdc(),NULL,(FONTENUMPROC) EnumFontProc,(LPARAM)this);//Enumerate
	m_bInitOver = TRUE;
}

BOOL CALLBACK CFontCombo::EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData)
{
	if (dwType == TRUETYPE_FONTTYPE && lplf->lfCharSet != SYMBOL_CHARSET) //Add only TTF fellows, If you want you can change it to check for others
	{
		int index = ((CFontCombo *) lpData)->AddString(lplf->lfFaceName);
		TRACE1("FONT: %s\n", lplf->lfFaceName);
		LPLOGFONT lpLF;
		lpLF = new LOGFONT;
		CopyMemory ((PVOID) lpLF,(CONST VOID *) lplf,sizeof (LOGFONT));
		((CFontCombo *) lpData)->SetItemData (index,(DWORD) lpLF);
	}
	return TRUE;
}

long CFontCombo::OnInitFonts (WPARAM, LPARAM)
{
	InitFonts ();
	return 0L;
}

int	CFontCombo::GetSelFont (LOGFONT& lf)
{
	int index = GetCurSel ();
	if (index == LB_ERR)
		return LB_ERR;
	LPLOGFONT lpLF = (LPLOGFONT) GetItemData (index);
	CopyMemory ((PVOID)&lf, (CONST VOID *) lpLF, sizeof (LOGFONT));
	return index; //return the index here.. Maybe the user needs it:-)
}

void CFontCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch (m_enStyle)
	{
	case FONTS:
		DrawFont(lpDrawItemStruct);
		break;
	}	
}

void CFontCombo::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 14;
}
