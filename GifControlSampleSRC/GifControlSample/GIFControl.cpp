#include"stdafx.h"
#include"GIFControl.h"

//MSG MAP
BEGIN_MESSAGE_MAP(CGIFControl,CStatic)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//
CGIFControl::CGIFControl()
{
	m_pImage = NULL;
	m_pDimensionIDs = NULL;
	m_pItem = NULL;

	m_bBorderEnable = FALSE;
	m_bTrackOnce = FALSE;

	//
	m_bIsPlaying = FALSE;

	//
	m_hHandCursor = ::LoadCursor(NULL,MAKEINTRESOURCE(IDC_HAND));
}

CGIFControl::~CGIFControl()
{
	if(m_pDimensionIDs)
	{
		delete[] m_pDimensionIDs;
	}

	if(m_pItem)
	{
		free(m_pItem);
	}

	if(m_pImage)
	{
		delete m_pImage;
	}
}

BOOL CGIFControl::OnEraseBkgnd(CDC* pDC)
{
	return CStatic::OnEraseBkgnd(pDC);
}

void CGIFControl::SetBorderRound(Color& c,int iLineWidth)
{
	m_cBorder = c;
	m_iBorderLineWidth = iLineWidth;

	CRect rcClient;
	GetClientRect(&rcClient);
	ClientToScreen(&rcClient);

	//扩大
	rcClient.left -= m_iBorderLineWidth;
	rcClient.top -= m_iBorderLineWidth;
	rcClient.right += m_iBorderLineWidth;
	rcClient.bottom += m_iBorderLineWidth;

	//改变控件的大小
	SetWindowPos(CWnd::FromHandle(HWND_BOTTOM),rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height(),SWP_NOZORDER);
}

//
void CGIFControl::DrawBorder(Graphics& g)
{
	if(!m_bBorderEnable)
	{
		return;
	}

	CRect rcClient;
	GetClientRect(&rcClient);

	//准备绘制
	Rect rcDraw(rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height());

	SolidBrush bs(m_cBorder);
	g.FillRectangle(&bs,rcDraw);
}

void CGIFControl::EnableBorder(BOOL bEnable)
{
	m_bBorderEnable = bEnable;
}

void CGIFControl::OnLButtonDown(UINT nFlags,CPoint point)
{
	if(m_URL.IsEmpty())
	{
		return;
	}

	::ShellExecute(NULL,_T("Open"),_T("IEXPLORE"),m_URL,NULL,SW_SHOW);
}

void CGIFControl::OnMouseMove(UINT nFlags,CPoint point)
{
	if(!m_bTrackOnce)
	{
		TRACKMOUSEEVENT	csTME;

		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE;
		csTME.hwndTrack = m_hWnd;
		::_TrackMouseEvent(&csTME);

		m_bTrackOnce = TRUE;
	}

	//如果有URL，则显示Hand图标
	if(m_URL.IsEmpty())
	{
		return ;
	}

	//Save Old
	m_hOldCursor = ::GetCursor();
	
	//Set New
	//每个消息都设置，会不会有问题啊
	::SetCursor(m_hHandCursor);
}

void CGIFControl::PreSubclassWindow()
{
	ModifyStyle(0, SS_OWNERDRAW | SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

LRESULT CGIFControl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTrackOnce = FALSE;
	::SetCursor(m_hOldCursor);

	return TRUE;
}

BOOL CGIFControl::Create(CRect& rc,CWnd* parent ,UINT nID)
{
	BOOL bResult = CStatic::Create(NULL , WS_CHILD | SS_OWNERDRAW | WS_VISIBLE | SS_NOTIFY , rc , parent , nID);

	return bResult;
}

void CGIFControl::Load(LPCTSTR sFileName)
{
	//DEBUG HINT HERE
	//PLEASE MAKE SURE FILEPATH RIGHT!
	m_pImage = Image::FromFile(sFileName);
	
	UINT count = m_pImage->GetFrameDimensionsCount();
	m_pDimensionIDs =new GUID[count];
	m_pImage->GetFrameDimensionsList(m_pDimensionIDs, count);
	
	WCHAR strGuid[39];
	StringFromGUID2(m_pDimensionIDs[0], strGuid, 39);
	m_FrameCount = m_pImage->GetFrameCount(&m_pDimensionIDs[0]);

	//PropertyTagFrameDelay是GDI+中预定义的一个GIG属性ID值，表示标签帧数据的延迟时间
	UINT TotalBuffer = m_pImage->GetPropertyItemSize(PropertyTagFrameDelay);
	m_pItem = (PropertyItem*)malloc(TotalBuffer);
	m_pImage->GetPropertyItem(PropertyTagFrameDelay,TotalBuffer,m_pItem);
}

void CGIFControl::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);

	GUID Guid = FrameDimensionTime;
	m_pImage->SelectActiveFrame(&Guid,m_iCurrentFrame);

	SetTimer(1,((UINT*)m_pItem[0].value)[m_iCurrentFrame] * 10,NULL);

	m_iCurrentFrame = (++ m_iCurrentFrame) % m_FrameCount;
	Invalidate(FALSE);
}

void CGIFControl::Play()
{
	if(m_bIsPlaying == TRUE)
	{
		return;
	}

	m_iCurrentFrame = 0;
	GUID Guid = FrameDimensionTime;
	m_pImage->SelectActiveFrame(&Guid,m_iCurrentFrame);

	SetTimer(1,((UINT*)m_pItem[0].value)[m_iCurrentFrame]  * 10,NULL);

	++ m_iCurrentFrame;
	Invalidate(FALSE);

	//
	m_bIsPlaying = TRUE;
}

void CGIFControl::Stop()
{
	if(m_bIsPlaying == FALSE)
	{
		return;
	}

	//
	KillTimer(1);

	//
	m_bIsPlaying = FALSE;
}

void CGIFControl::SetURL(LPCTSTR sURL)
{
	m_URL = sURL;
}

void CGIFControl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics g(lpDrawItemStruct->hDC);

	DrawBorder(g);

	CRect rcClient;
	GetClientRect(&rcClient);

	if(m_bBorderEnable)
	{
		rcClient.DeflateRect(m_iBorderLineWidth,m_iBorderLineWidth,m_iBorderLineWidth,m_iBorderLineWidth);
	}

	g.DrawImage(m_pImage,rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height());
}