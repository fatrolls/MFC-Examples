//*******************************************************************************************************/
//* FileName:		clPlot.cpp
//*
//* Contents:		Implementation of clPlot, axis, legend, serie and timeaxis
//*
//* NOTE 1:			Only a minimum of parameter validation is implemented to save time since this plot is 
//*					time critical.
//*
//* NOTE 2:			All functionality is not fully implemented.
//*
//* Author:			Jan Vidar Berger
//*******************************************************************************************************/
//* 12.feb.98	Jan Vidar Berger	Implemented flicker free drawing. Thanks to John Kim for providing 
//*									the MemDC and to Keith Rule, the author of CMemDC.
//*******************************************************************************************************/

#include "stdafx.h"
#include "clPlot.h"
#include "MemDC.h"

#include "malloc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long	clPlot::m_lMaxDataPrSerie;	// max allowed data pr. serie.
long	clPlot::m_lMaxDataTotal;	// max allowed data total.

//*******************************************************************************************************/
//* time axis threshold. contains grid and label intervals to be used within specified
//* seconds pr. pixels thresholds. The array is terminated by a 'bIAmInUse'=FALSE.
//*******************************************************************************************************/
struct{
	BOOL	bIAmInUse;					// indicate valid entry, last=FALSE
	long	lgridinterval;				// grid line interval in seconds
	long	llabelinterval;				// time label interval in seconds
	long	lmodethreshold;				// mode threshold in seconds pr. pixel
}gridsetting[]={
	TRUE, 1, 4,	0,						// 0: pr. second

	FALSE, 1, 1,0,						// last entry in table
};

//*******************************************************************************************************/
//* Function:		serie::serie
//*******************************************************************************************************/
serie::serie()
{
	m_bIAmInUse		= FALSE;
	m_color			= RGB(0,0,0);
	m_iLineStyle	= PS_SOLID;
	m_bRightAxisAlign	= FALSE;
	m_lNoValues		= 0;
	m_lbegin		= 0;
	m_lend			= 0;
	m_pvalues		= NULL;

}

//*******************************************************************************************************/
//* Function:		serie::~serie
//*******************************************************************************************************/
serie::~serie()
{
	if(m_pvalues !=NULL)
		free(m_pvalues);
}

//*******************************************************************************************************/
//* Function:		serie::AddPoint
//*
//* Description:	AddPoint add new data to the end of a data serie. It will simply append the data,
//*					update the list index and get out. 
//*
//*					This function will also call realloc or malloc to re-size or create the plot array as
//*					needed.
//*
//*					The nice thing about circular lists is that they are multi thread enabled as is. You
//*					must however implement a syncronization mechanism if more than one thread is supposed
//*					to enter data into the plot.
//*
//* Parameters:		valuetime		Time (x value).
//*					y				y value
//*
//* Return Value:	-none-
//*
//* Author:			Jan Vidar Berger
//*******************************************************************************************************/
void serie::AddPoint(CTime &valuetime , double &y)
{
	if(m_lNoValues > 0)
		m_pvalues = (value*)realloc(m_pvalues, (m_lNoValues+1)*sizeof(value));
	else
		m_pvalues = (value*)malloc((m_lNoValues+1)*sizeof(value));

	m_pvalues[m_lend].ValueTime = valuetime;
	m_pvalues[m_lend].dValue	= y;
	m_lNoValues++;
	m_lend++;
	if(m_lend >= clPlot::m_lMaxDataPrSerie)
		m_lend=0;
	if(m_lbegin == m_lend){
		m_lbegin++;
		if(m_lbegin >= clPlot::m_lMaxDataPrSerie)
			m_lbegin=0;
	}
}

//*******************************************************************************************************/
//* Function:		serie::Reset
//*
//* Description:	Reset the serie. Remove data and reset indexes and pointers.
//*
//* Parameters:		-none-
//*
//* Return Value:	-none-
//*
//* Author:			Jan Vidar Berger
//*******************************************************************************************************/
void serie::Reset()
{
	m_lNoValues=0;

	if(m_pvalues !=NULL)
		free(m_pvalues);

	m_pvalues = NULL;

	m_lbegin		= 0;
	m_lend			= 0;
}

//*******************************************************************************************************/
//*******************************************************************************************************/
clPlot::clPlot()
{
	m_ctlBkColor		= RGB(255,255,255);
	m_plotBkColor		= RGB(255,255,255);
	m_legendBkColor		= RGB(255,255,255);
	m_gridColor			= RGB(127,127,127);
	m_bctlBorder		= TRUE;
	m_bplotBorder		= TRUE;
	m_blegendBorder		= TRUE;
	m_bPrimaryLegend	= FALSE;
	m_bSecondaryLegend	= FALSE;
	m_bAxisLY			= TRUE;
	m_bAxisRY			= TRUE;
	m_bAxisBX			= TRUE;
	m_bAutoScrollX		= FALSE;
	m_bSimMode			= FALSE;

	m_lMaxDataPrSerie	= 10000;
	m_lMaxDataTotal		= 100000;
	m_dNoData			= 0.0;

	m_dzoom				= 1.0;
	
	lArraySize			= 1000;			// only points with differebt x,y will be put into the array

	pLineArray			= new CPoint[lArraySize];
	SetBXRange(CTime::GetCurrentTime()-CTimeSpan(60),CTime::GetCurrentTime());

	m_logFont.lfHeight			= -13;
	m_logFont.lfWidth			= 0;
	m_logFont.lfEscapement		= 0;
	m_logFont.lfOrientation		= 0;
	m_logFont.lfWeight			= 400;
	m_logFont.lfItalic			= FALSE;
	m_logFont.lfUnderline		= FALSE;
	m_logFont.lfStrikeOut		= FALSE;
	m_logFont.lfCharSet			= ANSI_CHARSET;
	m_logFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_logFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_logFont.lfQuality			= PROOF_QUALITY;
	m_logFont.lfPitchAndFamily	= DEFAULT_PITCH;
	strcpy(m_logFont.lfFaceName,"Ariel");

	m_zoomFont.lfHeight			= -13;
	m_zoomFont.lfWidth			= 0;
	m_zoomFont.lfEscapement		= 0;
	m_zoomFont.lfOrientation		= 0;
	m_zoomFont.lfWeight			= 400;
	m_zoomFont.lfItalic			= FALSE;
	m_zoomFont.lfUnderline		= FALSE;
	m_zoomFont.lfStrikeOut		= FALSE;
	m_zoomFont.lfCharSet			= ANSI_CHARSET;
	m_zoomFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_zoomFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_zoomFont.lfQuality			= PROOF_QUALITY;
	m_zoomFont.lfPitchAndFamily	= DEFAULT_PITCH;
	strcpy(m_zoomFont.lfFaceName,"Ariel");

	m_font.CreateFontIndirect(&m_zoomFont);
}

//*******************************************************************************************************/
//*******************************************************************************************************/
clPlot::~clPlot()
{
	delete [] pLineArray;
}


//*******************************************************************************************************/
//*******************************************************************************************************/
BEGIN_MESSAGE_MAP(clPlot, CWnd)
	//{{AFX_MSG_MAP(clPlot)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*******************************************************************************************************/
//*******************************************************************************************************/
BOOL clPlot::Create(DWORD dwstyle, CRect &rect, CWnd *pParent, UINT id)
{
	DWORD style = dwstyle & (~WS_BORDER);
	if(dwstyle & WS_BORDER)
		m_bctlBorder=TRUE;
	else
		m_bctlBorder=FALSE;

	if(!CWnd::Create(NULL, "", style, rect, pParent, id, NULL))
		return FALSE;

	
	m_ctlRect = rect;
	pParent->ClientToScreen(m_ctlRect);
	ScreenToClient(m_ctlRect);

	ComputeRects(TRUE);
	return TRUE;
}

//*******************************************************************************************************/
//* Function        : clPlot::ComputeRects
//*
//* Description	    : Compute rects used for internal possitioning of different objects. This function is 
//*					  called when the plot is created or sized.
//*
//* Return type	    : void 
//*
//* Parameter(s)    : bInitialization		indicate wherever parameters that can be changed abu the user
//*											also should be computed.
//*
//* Author          : Jan Vidar Berger
//*******************************************************************************************************/
void clPlot::ComputeRects(BOOL bInitialization)
{
	// adjust the client rect for borders

	//GetClientRect(m_ctlRect);
	CClientDC dc(this);
	int w = 0;
	int n=0;
	CSize z=dc.GetTextExtent(CString("A"));
//	m_TextHeight = z.cy;

	m_dzoom = ((double)m_ctlRect.Height()/(double)z.cy) / 25.0;

	m_zoomFont.lfWidth = (int)(m_logFont.lfWidth * m_dzoom);
	m_zoomFont.lfHeight = (int)(m_logFont.lfHeight * m_dzoom);
	m_font.Detach();
	m_font.CreateFontIndirect(&m_zoomFont);
	CFont *oFont = dc.SelectObject(&m_font);
//	SetFont(&m_font);
	z=dc.GetTextExtent(CString("A"));
	m_TextHeight = z.cy;
	if(m_bctlBorder){
		m_clientRect.left = m_ctlRect.left+2;
		m_clientRect.right = m_ctlRect.right-2;
		m_clientRect.top = m_ctlRect.top+2;
		m_clientRect.bottom = m_ctlRect.bottom-2;
	}else{
		m_clientRect = m_ctlRect;
	}

	if(bInitialization)
	{
		m_iMtop = m_iMbottom = m_clientRect.Height()/10;
		m_iMleft = m_iMright = m_clientRect.Width()/10;
	}

	// compute plot rect.
	m_plotRect.left = m_clientRect.left + m_iMleft;
	m_plotRect.right = m_clientRect.right - m_iMright;
	m_plotRect.top = m_clientRect.top + m_iMtop;
	m_plotRect.bottom = m_clientRect.bottom - m_iMbottom;

	// compute default legend possition

	if(bInitialization)
	{
		m_legendRect.left = m_plotRect.left + (m_iMleft/5);
		m_legendRect.right = m_plotRect.left + (m_plotRect.Width()/5);
		m_legendRect.top = m_plotRect.top - (m_iMtop/2);
		m_legendRect.bottom = m_plotRect.top + (m_iMtop);
		int w = 0;
		int n=0;
		for(int x = 0; x< MAXLEGENDS;x++){
			if(m_primarylegends[x].m_bIAmInUse){
				n++;
				z=dc.GetTextExtent(CString(m_primarylegends[x].m_szTitle));
				if(z.cx > w )
					w=z.cx;
//				m_TextHeight = z.cy;
			}
		}

		m_legendRect.right = m_legendRect.left + 40 + w;
		m_legendRect.bottom = m_legendRect.top + 10 + (m_TextHeight*n);
	}

	// compute left axis area
	m_axisLYRect.left = m_clientRect.left + (m_iMleft/5);
	m_axisLYRect.right = m_plotRect.left;
	m_axisLYRect.top = m_plotRect.top;
	m_axisLYRect.bottom = m_plotRect.bottom;

	// compute right axis area
	m_axisRYRect.left =  m_plotRect.left;
	m_axisRYRect.right = m_clientRect.right - (m_iMright/5);
	m_axisRYRect.top = m_plotRect.top;
	m_axisRYRect.bottom = m_plotRect.bottom;

	// compute bottom axis area
	m_axisBXRect.left = m_plotRect.left;
	m_axisBXRect.right = m_plotRect.right;
	m_axisBXRect.top = m_plotRect.bottom;
	m_axisBXRect.bottom = m_clientRect.bottom - (m_iMbottom/5);

//	if(bInitialization)
//	{
		m_timeaxis.m_dSecondsPrPixel = ((double)(m_timeaxis.m_maxtime.GetTime() - m_timeaxis.m_mintime.GetTime())) / (double)m_plotRect.Width();
		m_leftaxis.m_dValuePrPixel   = ((double)(m_leftaxis.maxrange- m_leftaxis.minrange) / (double)m_plotRect.Height());
		m_rightaxis.m_dValuePrPixel   = ((double)(m_rightaxis.maxrange- m_rightaxis.minrange) / (double)m_plotRect.Height());
//	}
	dc.SelectObject(oFont);
}

//*******************************************************************************************************/
//* Function:		clPlot::OnPaint
//*
//* Description:	This function will create a memory image, call Draw to draw the plot on it, and when
//*					copy the image into memory.
//*
//*					This is fast and provides flicker free plot update.
//*
//* Author:			Jan Vidar Berger
//*******************************************************************************************************/
void clPlot::OnPaint() 
{
        CPaintDC dc(this); // device context for painting
        CMemDC  pdc(&dc);  // non flickering painting

        Draw(&pdc);
		
		// Do not call CWnd::OnPaint() for painting messages
}

BOOL clPlot::OnEraseBkgnd(CDC* pDC) 
{
		return FALSE;
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::Draw(CDC * dc)
{
	CFont *oFont = dc->SelectObject(&m_font);
	DrawBasic(dc);
	DrawGrid(dc);
	DrawPlot(dc);
	DrawLegend(dc);
	dc->SelectObject(oFont);
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::DrawBasic(CDC * dc)
{
	CBrush brushctlBkColor(m_ctlBkColor);
	dc->FillRect(m_ctlRect,&brushctlBkColor);
	if(m_bctlBorder)
	{
		dc->DrawEdge(m_ctlRect,BDR_SUNKENINNER|BDR_SUNKENOUTER, BF_RECT); 
	}
	dc->Rectangle(m_plotRect);
	DrawLegendShadow(dc);
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::DrawPlot(CDC * dc)
{
	for(int s=0;s<MAXSERIES;s++)
	{
		if(m_series[s].m_bIAmInUse)
		{
			DrawSerie(dc, s);
		}
	}
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::DrawSerie(CDC *dc,int s)
{
	BOOL bMore=TRUE;
	BOOL bDraw;
	CPoint p;
	int ly;
	// lets get some serie parameters now and save the time of indexing during the loop
	long y = m_series[s].m_lbegin;
	long m = m_series[s].m_lend;
	long a = m_series[s].m_lNoValues;
	BOOL bRightAxis = m_series[s].m_bRightAxisAlign;
	CPen pen(m_series[s].m_iLineStyle, 1, m_series[s].m_color);
	CPen *old = dc->SelectObject(&pen);
	while(bMore){
		bDraw=FALSE;
		bMore=FALSE;
		ly=0;
		while(y != m && !bDraw){
			if(m_series[s].m_pvalues[y].dValue == m_dNoData)
			{
				bDraw = TRUE;
				bMore = TRUE;
			}else{
//				Scaling. We do scaling inline to save some time
				time_t valuetime = m_series[s].m_pvalues[y].ValueTime.GetTime();
				p.x = (int)(m_plotRect.left + ((valuetime-m_timeaxis.m_mintime.GetTime())/m_timeaxis.m_dSecondsPrPixel));
				
				if(bRightAxis){
					p.y = (int)(m_plotRect.bottom - ((m_series[s].m_pvalues[y].dValue-m_rightaxis.minrange)/m_rightaxis.m_dValuePrPixel));
				}else{
					p.y = (int)(m_plotRect.bottom - ((m_series[s].m_pvalues[y].dValue-m_leftaxis.minrange)/m_leftaxis.m_dValuePrPixel));
				}

				if((ly == 0 || p.x != pLineArray[ly].x || p.y != pLineArray[ly].y)
					&& (p.x >= m_plotRect.left && p.x <= m_plotRect.right))
				{
					pLineArray[ly].x = p.x;
					pLineArray[ly].y = p.y;
					ly++;
				}
			}
			y++;
			if(y > a)	// wrap list index ?
				y=0;
		}
		if(ly > 0){
			dc->Polyline(pLineArray, ly);
		}
	}
	dc->SelectObject(old);
}

//*******************************************************************************************************/
//*
//*******************************************************************************************************/
void clPlot::DrawGrid(CDC * dc)
{
	DrawXAxisGrid(dc);
	DrawYAxisGrid(dc);
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::DrawYAxisGrid(CDC * dc)
{
	double yGrid = m_leftaxis.minrange;
	double delta = 25.0 + (long)(((m_leftaxis.m_dValuePrPixel)))*25;
	if((long)delta%50 != 0 && delta > 20.0)
		delta +=25;
	double d10 = delta / 5.0;
	// todo: delta switch
	long diff = ((long)yGrid)%((long)delta);
	yGrid = yGrid - diff;
	CPen *old, pen(PS_SOLID, 1, m_gridColor);
	CPen stick(PS_SOLID,0,RGB(0,0,0));
	CPen mline(PS_SOLID,0,RGB(192,192,192));

	for( long sy = (long)((long)(m_leftaxis.minrange) - diff); sy < m_leftaxis.maxrange; sy+=(long)d10)
	{
		int off=3;
		if((long)sy%(long)delta == 0){
			off=5;
		}
		if(sy > m_leftaxis.minrange){
			int y = (int)(m_plotRect.bottom - ((sy-m_leftaxis.minrange)/m_leftaxis.m_dValuePrPixel));
			old = dc->SelectObject(&stick); 
			dc->MoveTo(CPoint(m_plotRect.left,y));
			dc->LineTo(CPoint(m_plotRect.left-off,y));
			dc->MoveTo(CPoint(m_plotRect.right,y));
			dc->LineTo(CPoint(m_plotRect.right+off,y));
			dc->SelectObject(old);

			old = dc->SelectObject(&mline);
			dc->MoveTo(CPoint(m_plotRect.left+1,y));
			dc->LineTo(CPoint(m_plotRect.right-1,y));
			dc->SelectObject(old);
		}
	}

	old = dc->SelectObject(&pen);
	while(yGrid <= m_leftaxis.maxrange)
	{
		double yy = m_plotRect.bottom - ((yGrid-m_leftaxis.minrange)/m_leftaxis.m_dValuePrPixel);
		int y = (int)yy;
		if(yGrid > m_leftaxis.minrange && yGrid<m_leftaxis.maxrange){
			dc->MoveTo(CPoint(m_plotRect.left+1,y));
			dc->LineTo(CPoint(m_plotRect.right-1,y));
		}

		char b[100];
		sprintf(b, "%.0f", yGrid);
		dc->DrawText(b, CRect(m_clientRect.left, y-m_TextHeight/2,m_plotRect.left-5,y+m_TextHeight/2), DT_RIGHT|DT_BOTTOM);

		double yr = (m_plotRect.bottom - yy) * m_rightaxis.m_dValuePrPixel + m_rightaxis.minrange;
		sprintf(b, "%.0f", yr);
		dc->DrawText(b, CRect(m_plotRect.right+5, y-m_TextHeight/2,m_clientRect.right,y+m_TextHeight/2), DT_LEFT|DT_BOTTOM);

		yGrid += delta;
	}
	dc->SelectObject(old);
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::DrawXAxisGrid(CDC * dc)
{
	long yGrid = m_timeaxis.m_mintime.GetTime();
	long delta = (long)(10.0 + (long)(((m_timeaxis.m_dSecondsPrPixel)))*10);
	long d10 = (long)(delta / 10.0);
	// todo: delta switch
	long diff = ((long)yGrid)%((long)delta);
	yGrid = yGrid - diff;
	CPen *old, pen(PS_SOLID, 1, m_gridColor);
	CPen stick(PS_SOLID,0,RGB(0,0,0));
	CPen mline(PS_SOLID,0,RGB(192,192,192));

	for( long sx = m_timeaxis.m_mintime.GetTime() - diff; sx < m_timeaxis.m_maxtime.GetTime(); sx+=d10)
	{
		int off=3;
		if((long)sx%(long)delta == 0){
			off=5;
		}
		if(sx > m_timeaxis.m_mintime.GetTime()){
			int x = (int)(m_plotRect.left + ((sx-m_timeaxis.m_mintime.GetTime())/m_timeaxis.m_dSecondsPrPixel));
//			int x = m_plotRect.right - ((sx-m_timeaxis.m_mintime.GetTime())/m_timeaxis.m_lSecondsPrPixel);
			old = dc->SelectObject(&stick); 
			dc->MoveTo(CPoint(x,m_plotRect.bottom));
			dc->LineTo(CPoint(x+off,m_plotRect.bottom));
			dc->SelectObject(old);

			old = dc->SelectObject(&mline);
			dc->MoveTo(CPoint(x,m_plotRect.bottom-1));
			dc->LineTo(CPoint(x,m_plotRect.top+1));
			dc->SelectObject(old);
		}
	}

	old = dc->SelectObject(&pen);
	while(yGrid <= m_timeaxis.m_maxtime.GetTime())
	{
		int x = (int)(m_plotRect.left + ((yGrid-m_timeaxis.m_mintime.GetTime())/m_timeaxis.m_dSecondsPrPixel));

		if(yGrid > m_timeaxis.m_mintime.GetTime() && yGrid<m_timeaxis.m_maxtime.GetTime()){
			dc->MoveTo(CPoint(x,m_plotRect.bottom-1));
			dc->LineTo(CPoint(x,m_plotRect.top+1));
		}

//		char b[100];
//		sprintf(b, "%.0f", yGrid);
//		dc->DrawText(b, CRect(m_clientRect.left, y-m_TextHeight/2,m_plotRect.left-5,y+m_TextHeight/2), DT_RIGHT|DT_BOTTOM);

		yGrid += delta;
	}
	dc->SelectObject(old);
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::DrawLegendShadow(CDC * dc)
{
	if(m_blegendBorder){
		CPen pen(PS_SOLID, 1, RGB(127,127,127));
		CPen *oPen = dc->SelectObject(&pen);
		CBrush *oBrush , brush(RGB(127,127,127));
		oBrush = dc->SelectObject(&brush);
		dc->Rectangle(CRect(m_legendRect.left+5,m_legendRect.top+5,m_legendRect.right+5, m_legendRect.bottom+5));
		dc->SelectObject(oBrush);
		dc->SelectObject(oPen);
	}
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::DrawLegend(CDC * dc)
{
	if(m_blegendBorder){
		CPen pen(PS_SOLID, 1, RGB(0,0,0));
		CPen *oPen = dc->SelectObject(&pen);
		CBrush *oBrush , brush(m_legendBkColor);
		oBrush = dc->SelectObject(&brush);
		dc->Rectangle(m_legendRect);
		dc->SelectObject(oBrush);
		dc->SelectObject(oPen);
	}
	int y = m_legendRect.top + 5;
	int dx = m_legendRect.left + (2*m_TextHeight);
	int mh = m_TextHeight/2;
	for(int x = 0; x< MAXLEGENDS;x++){
		if(m_primarylegends[x].m_bIAmInUse){
			CRect lRect(	dx + 5, y, m_legendRect.right - 5, y + m_TextHeight);
			CPen pen(m_primarylegends[x].m_istyle, 1, m_primarylegends[x].m_color);
			CPen *oPen = dc->SelectObject(&pen);
			dc->MoveTo(CPoint(m_legendRect.left+5, y + mh));
			dc->LineTo(CPoint(dx, y+mh));
			dc->SelectObject(oPen);

			dc->DrawText(m_primarylegends[x].m_szTitle, lRect, DT_LEFT);
			y+=m_TextHeight+1;
		}
	}
}

//*******************************************************************************************************/
//* Function:		clPlot::AddPoint
//*******************************************************************************************************/
BOOL clPlot::AddPoint(int serie, CTime &valuetime, double &value)
{
	if(m_series[serie].m_lNoValues < m_lMaxDataPrSerie){
		m_series[serie].AddPoint(valuetime, value);
		if(m_bAutoScrollX && valuetime > m_timeaxis.m_maxtime){
			time_t span = m_timeaxis.m_maxtime.GetTime() - m_timeaxis.m_mintime.GetTime();
			time_t mintime = valuetime.GetTime() - span;

			SetBXRange(CTime(mintime), valuetime);
		}
		return TRUE;
	}
	return FALSE;
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetBXRange(CTime &fromtime, CTime &totime, BOOL bMove)
{
	m_timeaxis.m_mintime = fromtime;
	m_timeaxis.m_maxtime = totime;
	if(!bMove){
		m_timeaxis.m_dSecondsPrPixel = ((double)(m_timeaxis.m_maxtime.GetTime() - m_timeaxis.m_mintime.GetTime()+1)) / (double)m_plotRect.Width();
	}
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetLYRange(double &minrange, double &maxrange)
{
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetRYRange(double &minrange, double &maxrange)
{
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetBXTitle(const char *title)
{
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetLYTitle(const char *title)
{
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetRYTitle(const char *title)
{
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::Reset()
{
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetSerie(int s, int style, COLORREF color, double minrange, double maxrange, const char *szTitle, BOOL Rightalign)
{
	m_series[s].m_bIAmInUse = TRUE;
	m_series[s].m_color = color;
	m_series[s].m_iLineStyle = style;
	m_series[s].m_bRightAxisAlign = Rightalign;
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::MoveWindow(CRect & Rect)
{
	m_ctlRect = Rect;
	GetParent()->ClientToScreen(m_ctlRect);
	ScreenToClient(m_ctlRect);
	ComputeRects(TRUE);
	CWnd::MoveWindow(Rect);
}

//*******************************************************************************************************/
//*******************************************************************************************************/
void clPlot::SetLegend(int l, int style, COLORREF color, const char *text)
{
	m_primarylegends[l].m_bIAmInUse	= TRUE;
	m_primarylegends[l].m_color		= color;
	m_primarylegends[l].m_istyle		= style;
	m_primarylegends[l].m_szTitle		= text;
	CClientDC dc(this);
	CFont *oFont = dc.SelectObject(&m_font);
	int w = 0;
	int n=0;
	for(int x = 0; x< MAXLEGENDS;x++){
		if(m_primarylegends[x].m_bIAmInUse){
			n++;
			CSize z=dc.GetTextExtent(CString(m_primarylegends[x].m_szTitle));
			if(z.cx > w )
				w=z.cx;
//			m_TextHeight = z.cy;
		}
	}

	m_legendRect.right = m_legendRect.left + 10+(2*m_TextHeight) + w;
	m_legendRect.bottom = m_legendRect.top + 10 + (m_TextHeight*n);
	dc.SelectObject(oFont);
}
