
#include "stdafx.h"
#include "BitItem.h"
#include "BitSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBitSlider::CBitSlider()
  : m_bAllocFlag(FALSE),
	m_lpActive(NULL),
	m_lpNormal(NULL),
	m_hHand(NULL),
	m_nOffset(0)
{
}

CBitSlider::~CBitSlider()
{
	this->DestroyBackItem();
}

BEGIN_MESSAGE_MAP(CBitSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CBitSlider)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBitSlider::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

BOOL CBitSlider::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	return TRUE;
}

void CBitSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CBitSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{
	this->Invalidate();
	this->UpdateToolTips();
	CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CBitSlider::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDC * pDC = this->GetDC();
	this->DrawSlider(pDC, FALSE);
	this->ReleaseDC(pDC);

	this->UpdateToolTips();

	CSliderCtrl::OnMouseMove(nFlags, point);
}

BOOL CBitSlider::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if( m_hHand != NULL )
	{
		::SetCursor(m_hHand);
		return TRUE;
	}
	return FALSE;
}

void CBitSlider::OnPaint() 
{
	CPaintDC	dc(this);
	this->DrawSlider(&dc, TRUE);
}

void CBitSlider::DrawSlider(CDC * pDC, BOOL bPaint)
{
	if( m_Thumb.m_hWnd != NULL && m_lpNormal != NULL && m_lpActive != NULL )
	{
		CRect		rcRect;
		CRect		rcThumb;

		this->GetClientRect(rcRect);
		this->GetNewThumbRect(rcThumb);
		if( (GetStyle() & TBS_VERT) == TBS_VERT )
		{
			m_lpActive->CopyHoleDC(pDC, 0, 0, rcRect.Width(), bPaint ? rcThumb.bottom : rcThumb.top);
			m_lpNormal->CopyHoleDC(pDC, 0, rcThumb.bottom, rcRect.Width(), rcRect.bottom - rcThumb.bottom, 0, rcThumb.bottom);
		}
		else
		{
			m_lpActive->CopyHoleDC(pDC, 0, 0, bPaint ? rcThumb.right : rcThumb.left, rcRect.Height());
			m_lpNormal->CopyHoleDC(pDC, rcThumb.right, 0, rcRect.right - rcThumb.right, rcRect.Height(), rcThumb.right, 0);
		}
		bPaint ? m_Thumb.MoveWindow(rcThumb) : NULL;
	}
}

void CBitSlider::DestroyBackItem()
{
	if( m_lpActive != NULL && m_bAllocFlag )
	{
		delete m_lpActive;
		m_lpActive = NULL;
	}
	if( m_lpNormal != NULL && m_bAllocFlag )
	{
		delete m_lpNormal;
		m_lpNormal = NULL;
	}
	m_bAllocFlag = FALSE;
}

void CBitSlider::BuildBackItem(UINT nNormalRes, UINT nActiveRes)
{
	this->DestroyBackItem();
	ASSERT( m_lpActive == NULL );
	ASSERT( m_lpNormal == NULL );

	m_lpNormal  = new CBitItem(nNormalRes, 0, 0);
	m_lpActive  = new CBitItem(nActiveRes, 0, 0);
	ASSERT( m_lpActive != NULL );
	ASSERT( m_lpNormal != NULL );

	m_bAllocFlag = TRUE;

	this->SetWindowPos( NULL, 0, 0, m_lpActive->GetImageWidth(),
						m_lpActive->GetImageHeight(), SWP_NOMOVE );
}

void CBitSlider::BuildBackItem(CBitItem * lpNBit, CBitItem * lpABit)
{
	if( this->m_hWnd == NULL || lpNBit == NULL || lpABit == NULL )
		return;

	m_lpNormal	= lpNBit;
	m_lpActive	= lpABit;
	
	this->SetWindowPos( NULL, 0, 0, m_lpActive->GetItemWidth(),
						m_lpActive->GetItemHeight(), SWP_NOMOVE );
}

void CBitSlider::UpdateToolTips()
{
	CString	  strTips;
	strTips.Format("%d%%", this->GetPos());

	m_ctlTips.UpdateTipText(strTips, this);
	m_ctlTips.UpdateTipText(strTips, &m_Thumb);
}

void CBitSlider::BuildThumbItem(UINT nThumbRes, int cx, int cy)
{
	if( m_Thumb.m_hWnd != NULL || nThumbRes <= 0 )
		return;
	m_Thumb.Create(WS_CHILD | WS_VISIBLE, this, 0);
	ASSERT( m_Thumb.m_hWnd != NULL );
	m_Thumb.ReLoadBitItem(nThumbRes, cx, cy);
	m_Thumb.SetNotifyParent(TRUE);

	m_ctlTips.Create(this);
	m_ctlTips.AddTool(this);
	m_ctlTips.AddTool(&m_Thumb);
	m_ctlTips.SetDelayTime(100);

	this->UpdateToolTips();
}

void CBitSlider::BuildThumbItem(CBitItem * lpBit)
{
	if( lpBit == NULL || m_Thumb.m_hWnd != NULL )
		return;
	m_Thumb.Create(WS_CHILD | WS_VISIBLE, this, 0);
	ASSERT( m_Thumb.m_hWnd != NULL );
	m_Thumb.SetBitItem(lpBit);
	m_Thumb.SetNotifyParent(TRUE);

	m_ctlTips.Create(this);
	m_ctlTips.AddTool(this);
	m_ctlTips.AddTool(&m_Thumb);
	m_ctlTips.SetDelayTime(100);

	this->UpdateToolTips();
}

void CBitSlider::GetNewThumbRect(CRect & rcThumb)
{
	CRect	rcRect, rcOld;
	m_Thumb.GetClientRect(rcRect);
	this->GetThumbRect(&rcOld);

	if((GetStyle() & TBS_VERT) == TBS_VERT)		// Vertical slider...
	{
		rcThumb.left	= m_nOffset;
		rcThumb.right	= rcThumb.left + rcRect.Width();
		rcThumb.top		= rcOld.top + (rcRect.Height() - rcOld.Height()) / 2;
		rcThumb.bottom	= rcThumb.top + rcRect.Height();
	}
	else										// Horizon slider...
	{
		rcThumb.top		= m_nOffset;
		rcThumb.bottom	= rcThumb.top + rcRect.Height();
		rcThumb.left	= rcOld.left + (rcRect.Width() - rcOld.Width()) / 2;
		rcThumb.right	= rcThumb.left + rcRect.Width();
	}
}

BOOL CBitSlider::PreTranslateMessage(MSG* pMsg) 
{
	if(  m_ctlTips.m_hWnd != NULL  )
		m_ctlTips.RelayEvent(pMsg);
	
	return CSliderCtrl::PreTranslateMessage(pMsg);
}















