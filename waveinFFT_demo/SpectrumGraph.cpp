// SpectrumGraph.cpp : implementation file
//

#include "stdafx.h"
#include "waveInFFT.h"
#include "SpectrumGraph.h"
#include <math.h>
#include "memoryDc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrequencyGraph

CFrequencyGraph::CFrequencyGraph()
{
	m_nLength = 0;
	m_dArray = NULL;
	m_nMinValue = 0;
	m_nMaxValue = 10;
	m_nHighLevel = 80;
	m_nMediumLevel = 60;
	m_wSteps = 16;
	m_nStepFactor = 1;
	m_clrLow = RGB(0,0,255);
	m_clrMedium = RGB(0,255,0);
	m_clrHigh = RGB(255,0,0);
	m_bGrid = TRUE;
	m_bLogScale = FALSE;
	m_graphType = FG_EQ_CHANNEL;
}

CFrequencyGraph::~CFrequencyGraph()
{
	if (m_dArray)
		delete []m_dArray;
}

BEGIN_MESSAGE_MAP(CFrequencyGraph, CWnd)
	//{{AFX_MSG_MAP(CFrequencyGraph)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFrequencyGraph message handlers
void CFrequencyGraph::Point(HDC hDC, int x, int y, COLORREF color)
{
	::SetPixel (hDC, x, y, color);
}
BOOL CFrequencyGraph::Line(HDC hDC, int x1, int y1, int x2, int y2)
{
	::MoveToEx(hDC, x1, y1, 0);
	return ::LineTo(hDC, x2, y2);
}
void CFrequencyGraph::OnPaint()
{
	CRect rct;
	GetClientRect(&rct);
	//Needs to use CMemoryDC or else CMemDC...
	//using either class will get ride of the 
	//flicker problem that otherwise presents itself...
	CPaintDC paintdc(this);
	CMemDC dc(&paintdc,&rct);

// graph
	if (m_nLength == 0)
		return;

	CBrush* pOldBrush = NULL;
	CBrush* pbbr = NULL;
	CBrush* pabr = NULL;
	CBrush br(RGB(0,0,0));
	CBrush bg(RGB(0,65,0));
	CBrush bg1(RGB(0,192,0));
	CBrush bbr(RGB(0,0,255));
	CBrush abr(RGB(0,255,0));

	CPen blk1(PS_SOLID,3,RGB(0,0,0));
	CPen wht(PS_SOLID,1,RGB(192,192,192));
	CPen grn(PS_SOLID,2,RGB(0,128,0));
	CPen grn1(PS_SOLID,2,RGB(0,212,0));
	CPen pen(PS_SOLID,1,RGB(255,255,255));
	CPen bpen(PS_SOLID,1,RGB(0,0,255));
	CPen* pOldPen = NULL;
	CPen* pbOldPen = NULL;

	float div[16]={9,16,33,66,132,282,485, 540,632,987,1283,2732,5820,11640,17123,19123};

	CRect stepRect;
	CRect rc, lr, rr;

	int i, n, x,ctr,py,half,y=0;
	int nBars = m_wSteps;
	int pos=0;
	int xRight = (int)ceil((float)rct.Width() / (float)nBars);
	int nDiv=m_nLength/(nBars);
	int leftzerolevel = (rct.Height()/2-10)/2;
	int rightzerolevel = rct.Height()/2+10+leftzerolevel;
	int StereoY = rct.Height()/2;
	int StereoX = rct.Width()/2;

	double dRangePerStep = (m_nMaxValue-m_nMinValue);
	double timescale = leftzerolevel/dRangePerStep;
	double ts = static_cast<double>(rct.Width())/static_cast<double>(m_nLength);
	double ksum = 0.0;
	double rqsum = 0.0;
	double lqsum = 0.0;
	double left, right, coef, l, r, correlation;
	double peakleft = 0;
	double peakright = 0;
	double StereoScale = static_cast<double>(StereoX)/dRangePerStep;
	double StereoScaleY = static_cast<double>(StereoY)/dRangePerStep;
	double stereoleft = 0;
	double stereoright = 0;
	double* data = m_dArray;

	float alfa = 45.0f*3.1415926535897932384626433832795f/180.0f;
	float hcos = cos(alfa);
	float hsin = sin(alfa);
	
	switch (m_graphType)
	{
	case FG_MICRO_EQ:
		dc.SelectObject(bg);
		dc.SelectObject(blk1);

		dc.Rectangle(rct);

		dc.SelectObject(wht);
		dc.MoveTo(rct.left+1,rct.Height()/2-2);
		dc.LineTo(rct.left+1,rct.top+1);
		dc.LineTo(rct.right-1,rct.top+1);
		dc.SelectObject(grn);
		dc.MoveTo(rct.left+2,rct.Height()/2);
		dc.LineTo(rct.right-2,rct.Height()/2);

		dc.SelectObject(grn1);
		dc.SelectObject(bg1);
		if (m_dArray != NULL)
		{
			x=16;
			for(ctr=1; ctr<m_wSteps; ctr++)
			{
				m_dArray[ctr]=(m_dArray[m_nLength/ctr]/div[ctr])*m_wSteps;
				py=rct.Height()/2-(int)m_dArray[ctr];
				if(py<3) py=3;
				rc.SetRect(x-2,py,x+2,rct.Height()/2);
				dc.Rectangle(rc);
				x=x+33;
			}
		}
	break;
	case FG_SPECTRUM:
	case FG_EQ_CHANNEL:
	{
		dc.FillRect(&rct,&br);

		float scalefactor = 1;
		if (m_nMinValue<0)
		{
			scalefactor = ((float)rct.Height())/((m_nMinValue-m_nMaxValue)+1);
		}
		else
		{
			scalefactor = ((float)rct.Height())/((m_nMaxValue-m_nMinValue)+1);
		}
		if (m_graphType == FG_SPECTRUM)
		{
			//Spectrum Peak View
			// clear background
			Rectangle(dc,0,0,rct.Width(),rct.Height());
			// draw analyser
			float fTmp = 0;
			for (x = 1; x < rct.Width(); x ++)
			{
				fTmp = (float)(x/rct.Width());
				y=(int)(float)log10(fTmp);
				MoveToEx(dc,x,(y*rct.Height()+rct.Height()),NULL);
				float fy=(float)m_dArray[int((double(m_nLength)/double(rct.Width()))*x)];
				//float fsy=((fy*rct.Height()/(float)(m_nMaxValue-m_nMinValue))/(float)scalefactor);
				float fsy=(float)scalefactor*fy;
				//y=(int)(fsy*rct.Height());
				y = (int)fsy;
				//TRACE("FY=%f FSY=%f Y=%d\n",fy, fsy, y);
				LineTo(dc,x,rct.Height()-y);
			}
		}
		else
		{
			dRangePerStep /= GetNumberOfSteps();
			//EQ-Channel View
			for (WORD w = 0; w < nBars; w++)
			{
				stepRect.top = rct.bottom;
				int tot=0,nLargest=0;
				for (int i=pos; i<pos+nDiv; i++)
				{
					//ASSERT_READ(&m_dArray[i],sizeof(double));
					tot=tot+(int)m_dArray[i];
					if (m_dArray[i] > nLargest)
						nLargest = (int)m_dArray[i];
				}
				//17 130 61 130 = 37
				//60 130 61 130 = 127
				//108 130 61 130 = 100
				//17 130 61 230 = 36 / 231 * 130 = 20
				//60 130 61 230 = 127 / 231 * 130 = 71
				//108 130 61 230 = 231 / 231 * 130 = 130
				tot /= (nDiv);
				/*if (m_bLogScale)
				{
					tot = log10((float)tot)/log10(abs((float)m_nMaxValue-m_nMinValue))*rct.Height();
				}
				*/
				if (m_nMaxValue-m_nMinValue < tot)
				{
					tot = rct.Height()/max(abs(m_nMinValue),abs(m_nMaxValue))*tot;
				}
				else
				tot = (int)(scalefactor*tot);
				//tot = (int)(((((float)tot*rct.Height())/((float)(m_nMaxValue-m_nMinValue)))/(float)scalefactor)*rct.Height());
				//tot *= 2;
				//tot = (int)log(tot);
				TRACE("Total=%d Div=%d, Bars=%d dRange=%f Max=%d Min=%d Largest=%d\n",tot,nDiv,nBars,dRangePerStep,m_nMaxValue,m_nMinValue,nLargest);
				{
					stepRect.left = (rct.left+((xRight*(w+1))-xRight));
					stepRect.right = (xRight*(w+1));
					stepRect.bottom = stepRect.top;
					stepRect.top = rct.bottom - int(tot);
					CBrush br1;
					if (tot > m_nHighLevel)
						br1.CreateSolidBrush(GetHighColor());
					else if (tot > m_nMediumLevel)
						br1.CreateSolidBrush(GetMediumColor());
					else
						br1.CreateSolidBrush(GetLowColor());
					dc.FillRect(&stepRect,&br1);
					if (m_bGrid)
						dc.FrameRect(&stepRect,&br);

					stepRect.bottom = stepRect.top;
					stepRect.top = 0;
				}
				pos+=nDiv;
			}
		}
	}
	break;
	case FG_OSCILLOSCOPE:
		pOldBrush = dc.SelectObject(&br);
		pOldPen = dc.SelectObject(&pen);
		dc.Rectangle( 0, 0, rct.Width(), rct.Height() );
		pbOldPen = dc.SelectObject(&bpen);
		dc.MoveTo(0, leftzerolevel);
		for(i=0; i<m_nLength-1; i+=2)
		{
			x=(int)((double)i*ts);
			int y = (int)((double)leftzerolevel - static_cast<double>(m_dArray[i])*timescale);
			dc.LineTo( x ,y );
		}
		dc.MoveTo(0, rightzerolevel);
		for(i=1; i<m_nLength; i+=2)
		{
			x=(int)(i*ts);
			int y = (int)((double)rightzerolevel - static_cast<double>(m_dArray[i])*timescale);
			dc.LineTo( x ,y );
		}
		dc.SelectObject(pbOldPen);
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
	break;
	case FG_PEAK:
		for(i=0; i<m_nLength/2; i++)
		{
			r = static_cast<double>(*data++);
			l = static_cast<double>(*data++);
			ksum += r * l;
			rqsum += r * r;
			lqsum += l * l;
		}
		correlation = ksum / sqrt(lqsum * rqsum);
		dc.FillRect( rct,&br );
		half = rct.Width()/2;
		n = (int)(half+correlation*half);
		if( n+8 >= rct.Width() )
		{
			n = rct.Width()-5;
		}
		rct.left=n-4;
		rct.right=rct.left+8;
		rct.top=5;
		rct.bottom=rct.Height()-5;
		dc.FillRect(rct,&bbr);
	break;
	case FG_PEAK2:
		for(i = 0; i<m_nLength/2; i++)
		{
			left = fabs(static_cast<double>(*data++));
			right = fabs(static_cast<double>(*data++));
			peakleft = left>peakleft?left:peakleft;
			peakright = right>peakright?right:peakright;
		}

		coef = rct.Width()/dRangePerStep;
		lr.left=1;
		lr.right=(LONG)(coef*peakleft);
		lr.top=2;
		lr.bottom=rct.Height()/2-2;

		rr.left=1;
		rr.right=(LONG)(coef*peakright);
		rr.top=rct.Height()/2+2;
		rr.bottom=rct.bottom-2;

		pOldBrush = dc.SelectObject(&br);
		pOldPen = dc.SelectObject(&pen);
		dc.Rectangle( 0, 0, rct.Width(), rct.Height() );
		pbbr = dc.SelectObject(&bbr);
		pabr = dc.SelectObject(&abr);
		dc.FillRect( lr,&bbr );
		dc.FillRect( rr,&abr );
		dc.SelectObject(pabr);
		dc.SelectObject(pbbr);
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
	break;
	case FG_PIXELGRAM:
		pOldBrush = dc.SelectObject(&br);
		pOldPen = dc.SelectObject(&pen);
		dc.Rectangle(0, 0, rct.Width(), rct.Height());
		for(i=0; i<m_nLength/2; i++)
		{
			left=static_cast<double>(*data++);
			right=static_cast<double>(*data++);
			stereoleft = (hcos*left - hsin*right)*2;
			stereoright = (hsin*right + hcos*left)*2;
			dc.SetPixel((int)(StereoX+stereoright*StereoScale),(int)(StereoY+stereoleft*StereoScaleY),RGB(255,255,255));
		}
	break;
	}
	if (pOldPen)
		dc.SelectObject(pOldPen);
	if (pOldBrush)
		dc.SelectObject(pOldBrush);
}

void CFrequencyGraph::Update(int nNumber, double* dArray)
{
	if (m_nLength != nNumber)
	{
		m_nLength = nNumber;
		if (m_dArray)
			delete []m_dArray;
		m_dArray = new double[m_nLength];
	}
	m_nStepFactor = (int)((m_nLength/m_wSteps)+0.5);
	memcpy(m_dArray,dArray,nNumber*sizeof(double));
	Invalidate(FALSE);
}
