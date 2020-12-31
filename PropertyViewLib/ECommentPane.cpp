// ECommentPane.cpp: implementation of the ECommentPane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ECommentPane.h"
#include "hoverbutton.h"
#include "EPropCtrl.h"
#include "EPropWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


IMPLEMENT_DYNCREATE(ECommentPane, CWnd)

BEGIN_MESSAGE_MAP( ECommentPane , CWnd )
	//{{AFX_MSG_MAP(ECommentPane)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


ECommentPane::ECommentPane()
{
	m_pCommentHost = NULL;
	m_pPropWnd = NULL;
}

ECommentPane::~ECommentPane()
{
}

void ECommentPane::SetCommentHost( ICommentHost* pCommentHost )
{
	m_pCommentHost = pCommentHost;
}

void ECommentPane::OnPaint()
{
	CRect   cr;
	GetClientRect(&cr);

	CPaintDC PaintDC(this);
	CDC* pDC = &PaintDC;

	//
	//
	//

//----------------
// flicker
//----------------
	CDC* pParsedDC = pDC;
	CDC     MemDC;
	CBitmap MemBM;
	MemBM.CreateCompatibleBitmap(pParsedDC,cr.Width(),cr.Height());
	MemDC.CreateCompatibleDC(pParsedDC);
	MemDC.SelectObject(&MemBM);
	pDC = &MemDC;
//----------------

	CRect r = cr;

	CFont f;

	pDC->SetBkColor(RGB(255,255,255));

	CRect rlef = r;
	CRect rrig = r;

	rlef.right = 17;
	rrig.left  = rlef.right;

	pDC->FillSolidRect( r , ::GetSysColor(COLOR_3DFACE  ));

	m_pPropWnd->DrawFrame( pDC , r , true , m_pPropWnd->GetColorPaneKey() );

	rrig.DeflateRect(2,2);
	r.DeflateRect(5,3);

	CRect TextAreaRect = r;

	//
	//
	//

	CString sTitle = "-";
	CString sNoComments = "-";

	//
	//
	//

	int nWeight = FW_MEDIUM;	//m_bMinimized ? FW_BOLD : FW_MEDIUM;

	f.CreateFont(13,0,0,0,nWeight,0,0,0,0,0,0,0,0,"tahoma");
	pDC->SelectObject(&f);



	if( m_pCommentHost!=NULL )
	{
		CString sName;
		CString s = m_pCommentHost->GetCurrentComment( sName );

		UINT nFlags = DT_LEFT | DT_WORDBREAK;

		if( s.GetLength()==0 )
		{
			s = sNoComments;
			nFlags = DT_SINGLELINE | DT_CENTER | DT_VCENTER;
		}
		else
		{
			while( true )
			{
				CRect TrimmedTextRect = TextAreaRect;

				pDC->DrawText( s , TrimmedTextRect , DT_WORDBREAK | DT_CALCRECT );

				if( TrimmedTextRect.Height() <= TextAreaRect.Height() )
				{
					break;
				}

				if( s.GetLength() <= 4 )
				{
					s = "...";
					break;
				}

				s = s.Left( s.GetLength()-4 );
				s += "...";
			}

		}

		pDC->DrawText( s , TextAreaRect , nFlags );
	}

//--------------------------
// flicker
//--------------------------
	MemDC.SetViewportOrg(0,0);
	pParsedDC->BitBlt( 0 , 0 , cr.Width() , cr.Height() , &MemDC , 0 , 0 , SRCCOPY );
//--------------------------


}

int ECommentPane::GetHeight( int nColumnWidth )
{
	int nHeight = 13*3 + 6;	//text + edge, defaults to 3 text lines

//------------
//calculate height of text for a given column width
//------------
//	CRect r(0,0,nWidth,0);
//	if( m_pCommentHost!=NULL )
//	{
//		CString sName;
//		CString s = m_pCommentHost->GetCurrentComment( sName );
//
//		CFont f;
//		f.CreateFont(13,0,0,0,FW_NORMAL,0,0,0,0,0,0,0,0,"tahoma");
//
//		CDC dc;
//		dc.CreateCompatibleDC(NULL);
//		dc.SelectObject(&f);
//
//		dc.DrawText( s , &r , DT_CALCRECT | DT_WORDBREAK );
//	}
//	nHeight = r.Height() + 4;
//------------

	return nHeight;
}

void ECommentPane::OnLButtonUp( UINT, CPoint )
{
	EPropCtrl* pParent = (EPropCtrl*)GetParent();
	pParent->SetCommentPaneHeight(0);
}
