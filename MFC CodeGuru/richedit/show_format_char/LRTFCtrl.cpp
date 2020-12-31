// LRTFCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "FormatRTF.h"
#include "LRTFCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LRichEditCtrl static callbach function for stream I/O 

//------------------------------------------------------------------------------
// EditStreamOutCallback
//
DWORD CALLBACK EditStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
	CString* pstr = (CString *)dwCookie;
	
	(*pstr) = pbBuff;

	return 0;
}

//------------------------------------------------------------------------------
// EditStreamInCallback
// Callback for setting the RTF Text to the ctrl
//
// (this code is from Zafir Anjum (zafir@dsp.com). Check his article for more 
// infos: "Inserting an RTF string using StreamIn" on www.codeguru.com)
//
DWORD CALLBACK EditStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{

	CString* pstr = (CString *)dwCookie;

	if( pstr->GetLength() < cb )
	{
		*pcb = pstr->GetLength();
		memcpy(pbBuff, (LPCSTR)*pstr, *pcb );
		pstr->Empty();
	}
	else
	{
		*pcb = cb;
		memcpy(pbBuff, (LPCSTR)*pstr, *pcb );
		*pstr = pstr->Right( pstr->GetLength() - cb );
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// LRichEditCtrl

LRichEditCtrl::LRichEditCtrl()
{
	m_foFormatChar.CreatePointFont(80, "Symbol");
	m_bDrawFormatChars = FALSE;
}

LRichEditCtrl::~LRichEditCtrl()
{
}


BEGIN_MESSAGE_MAP(LRichEditCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(LRichEditCtrl)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(BM_DRAW_FORMAT_CHAR, OnDrawFormatChars)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LRichEditCtrl message handlers

//------------------------------------------------------------------------------
// OnEraseBkgnd
//
BOOL LRichEditCtrl::OnEraseBkgnd(CDC* pDC) 
{
	PostMessage(BM_DRAW_FORMAT_CHAR);
	return CRichEditCtrl::OnEraseBkgnd(pDC);
}

//------------------------------------------------------------------------------
// ToggleFormatChars
//
void LRichEditCtrl::OnPaint() 
{
	PostMessage(BM_DRAW_FORMAT_CHAR);
	CRichEditCtrl::OnPaint();
}

//------------------------------------------------------------------------------
// OnKeyDown
//
void LRichEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(m_bDrawFormatChars){

		switch(nChar){

			// chars to ignore
			case VK_UP :
			case VK_DOWN :
			case VK_RIGHT :
			case VK_LEFT :
			case VK_CONTROL :
			case VK_SHIFT :
			break;

			default:

				long lStart, lEnd;
				GetSel(lStart, lEnd);

				// if last pos on line draw a empty rect
				if((lStart == lEnd) && (lStart == (LineIndex() + LineLength())) ){
					
					CClientDC dc(this);
					CRect rectClient;
					CRgn rgnRect;

					// limit clipping region to the ctrl
					GetClientRect(&rectClient);
					rgnRect.CreateRectRgnIndirect(&rectClient);
					dc.SelectClipRgn(&rgnRect);

					CPoint ptChar = GetCharPos(lStart);
					CSize sizChar = dc.GetTextExtent("A", 1);
					sizChar.cx++;
					sizChar.cx++;
					CRect rectChar(ptChar, sizChar);

					HideCaret();
					// if you change the background color of the edit you have to set the same background color
					dc.FillSolidRect(&rectChar, RGB(255, 255, 255));
					ShowCaret();
				}

				// redraw the format chars
				PostMessage(BM_DRAW_FORMAT_CHAR);
			break;
		}
	}

	CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

//------------------------------------------------------------------------------
// OnDrawFormatChars
// draws the format chars if m_bDrawFormatChars is on
//
LRESULT LRichEditCtrl::OnDrawFormatChars(WPARAM wParam, LPARAM lParam)
{
	if(!m_bDrawFormatChars)
		return 0L;

	CString strText;
	CPoint ptCharL;
	CPoint ptCharR;
	CClientDC dc(this);
	CRect rectClient;
	CRgn rgnRect;
	CSize sizChar = dc.GetTextExtent("A", 1);
	CFont* pfoOld = dc.SelectObject(&m_foFormatChar);

	// limit clipping region to the ctrl
	GetClientRect(&rectClient);
	rgnRect.CreateRectRgnIndirect(&rectClient);
	dc.SelectClipRgn(&rgnRect);

	HideCaret();

	//-----------------------------------------
	// Draw TAB
	GetWindowText(strText);

	int iLen = LineIndex(GetFirstVisibleLine());
	strText = strText.Mid(iLen);

	int iPos = strText.Find('\t');
	int iAbsPos = iPos + iLen;

	// makt the char green
	dc.SetTextColor(RGB(0, 128, 0));
	
	// if you change the background color of the edit you have to set the same background color
	//dc.SetBkColor(RGB(192, 192, 192));

	// for all '\t'
	while(iPos > -1){

		ptCharL = GetCharPos(iAbsPos);
		ptCharR = GetCharPos(iAbsPos + 1);

		if(rectClient.PtInRect(ptCharL)){

			CRect rectTab(ptCharL, ptCharR);
			rectTab.bottom += sizChar.cy;

			dc.SetTextAlign(TA_CENTER);
			dc.ExtTextOut(ptCharL.x + rectTab.Width() / 2, ptCharL.y, ETO_OPAQUE, rectTab, "®", 1, NULL);
		}

		if(ptCharL.y > rectClient.bottom)
			break;

		strText = strText.Mid(iPos + 1);
		
		iPos = strText.Find('\t');
		iAbsPos += iPos + 1;
	}

	//-----------------------------------------
	// Draw LF
	GetWindowText(strText);

	strText = strText.Mid(iLen);

	iPos = strText.Find('\n');
	iAbsPos = iPos + iLen;

	// for all '\n'
	while(iPos > -1){
		ptCharL = GetCharPos(iAbsPos);

		if(rectClient.PtInRect(ptCharL)){

			dc.SetTextAlign(TA_LEFT);
			dc.ExtTextOut(ptCharL.x - 7, ptCharL.y, ETO_OPAQUE, NULL, "¿", 1, NULL);
		}

		if(ptCharL.y > rectClient.bottom)
			break;

		strText = strText.Mid(iPos + 1);

		iPos = strText.Find('\n');
		iAbsPos += iPos + 1;
	}

	// restore old font
	dc.SelectObject(pfoOld);

	ShowCaret();

	return 0L;
}

//------------------------------------------------------------------------------
// GetRTFText
// reads the RTF Text from the ctrl
//
void LRichEditCtrl::GetRTFText(CString& strText)
{
	EDITSTREAM esText = {(DWORD)&strText, 0, EditStreamOutCallback};

	StreamOut(SF_RTF, esText);
}

//------------------------------------------------------------------------------
// SetRTFText
// sets the RTF Text into the ctrl
//
// (this code is from Zafir Anjum (zafir@dsp.com). Check his article for more 
// infos: "Inserting an RTF string using StreamIn" on www.codeguru.com)
//
void LRichEditCtrl::SetRTFText(const CString& strText)
{
	EDITSTREAM esText = {(DWORD)&strText, 0, EditStreamInCallback};

	StreamIn(SF_RTF, esText);
}

//------------------------------------------------------------------------------
// ToggleFormatChars
//
void LRichEditCtrl::DrawFormatChars(BOOL bDrawFormatChars /* = TRUE */)
{
	m_bDrawFormatChars = bDrawFormatChars;

	if(m_bDrawFormatChars)
		PostMessage(BM_DRAW_FORMAT_CHAR);
	else
		RedrawWindow();
}

//------------------------------------------------------------------------------
// ToggleFormatChars
//
void LRichEditCtrl::ToggleFormatChars()
{
	m_bDrawFormatChars = !m_bDrawFormatChars;

	if(m_bDrawFormatChars)
		PostMessage(BM_DRAW_FORMAT_CHAR);
	else
		RedrawWindow();
}

