// SpectrumWnd.cpp : implementation file
//

#include "stdafx.h"
#include "colorselector.h"
#include "SpectrumWnd.h"

#include <math.h>	// needed to compute color difference in HLS space

#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////
//
// This class paints a spectrum of colors all having a constant luminance
// value, while varying the luminance and saturation values.

// The spectrum fills the entire window, except for a thin one-pixel border
// that surrounds it and is painted in the COLOR_BTNFACE color.  The border 
// allows display of an outlined tiny rectangle to signify which color is 
// closest to a target color

// The constant luminance value is stored in m_iLum
// The target color is m_crTargetColor
// Both are assumed to have been set by an outside source

// If the user drags or clicks in the window, the position of the outline
// is changed, and the window sends its parent a private message whose value
// is UWM_SPECTRUMWINDOWEVENT and which must be defined in the project
// somewhere (such as NameOfApp.h).  The WPARAM of the message has a value
// of SWE_NEWFOCUSCOLOR.  In response, the parent should set the new target
// color (i.e., m_crTargetColor) and/or the luminance (i.e., m_iLum) and then
// invalidate this window or otherwise cause it to re-paint itself.  To assist
// the parent in deciding how to set the target color, the window stores
// the value of the clicked-on color in m_crCurrentFocusColor


const int CSpectrumWnd::m_cbCells = 24;


/////////////////////////////////////////////////////////////////////////////
// CSpectrumWnd

CSpectrumWnd::CSpectrumWnd()
{
	m_iLum = 0;
	m_bIsDragging = FALSE;
	
	// allocate memory to store the RGB values of each tiny
	// rectangle in the spectrum's window
	
	m_crArray = new COLORREF[m_cbCells*m_cbCells];
}

CSpectrumWnd::~CSpectrumWnd()
{
	delete[] m_crArray;
}


BEGIN_MESSAGE_MAP(CSpectrumWnd, CWnd)
//{{AFX_MSG_MAP(CSpectrumWnd)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSpectrumWnd message handlers


int CSpectrumWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// adjust size of client rectangle to a nice multiple of
	// the number of cells being displayed

	// adjust rect to be a multiple of the number of cells contained in the CSpectrum,
	// plus 2 pixels (to allow for outside-the-square drawing of the selection outline)
	
	CRect rc;
	GetClientRect( &rc );

	int ccx, ccy;
	ccx = (rc.Width()+m_cbCells/2)/m_cbCells;	// allow for modest expansion of window's size
	ccy = (rc.Height()+m_cbCells/2)/m_cbCells;
	
	rc.right = ccx*m_cbCells + 2;
	rc.bottom = ccy*m_cbCells + 2;

	this->SetWindowPos( NULL, 0, 0, rc.Width(), rc.Height(),
		SWP_NOMOVE | SWP_NOZORDER );


	return 0;
}


void CSpectrumWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rc;
	GetClientRect( &rc );
	
	// our window is framed by a 1-pixel wide blank border, to accommodate
	// the outside-the-box sized focus outline for the current color
	// so we need to erase one pixel wide in the border, or else we
	// will leave remnants of the outline
	
	CBrush brGray( ::GetSysColor( COLOR_BTNFACE ) );
	dc.FrameRect( &rc, &brGray );
	
	int dx = rc.Width()/m_cbCells;
	int dy = rc.Height()/m_cbCells;
	
	int hue, lum, sat;
///	int dr, dg, db;		// delta errors in RGB space (not needed, see below)
	int dclr, dclrmax;	// color difference errors
	int dH, dL, dS;		// deltas in HLS coords
	WORD HH, LL, SS;	// m_crTargetColor in HLS coords
	dclrmax = SHRT_MAX;	// big number
	float dColor = 240.0F/m_cbCells;
	CRect block(0,0,0,0);
	CSize offset(dy, dy);
	COLORREF cr;
	double TwoPiOver240 = 2.0 * 3.1415926 / 240.0;
	
	for ( int nDexY=0; nDexY<m_cbCells; nDexY++ )
	{
		// set the start location of the current drawing rectangle
		// offset by one pixel from window origin to allow drawing of focus outline rect
		
		block = CRect( 1, nDexY*dy+1, dx+1, (nDexY+1)*dy+1 );

		for ( int nDexX=0; nDexX<m_cbCells; nDexX++ )
		{
			hue = (int)dColor*nDexX;
			lum = m_iLum;
			sat = (int)(dColor*((float)nDexY+0.5F));
			
			cr = ::ColorHLSToRGB( hue, lum, sat );
			*(m_crArray+nDexY*m_cbCells+nDexX) = cr;
			dc.FillSolidRect( &block, cr );
			
/*
			// this computation of color difference is done is non-preferred
			// RGB coordinates, and has been replaced by a more perceptual
			// color difference calculation in HLS coordinates, below
			
			dr = GetRValue(m_crTargetColor) - GetRValue(cr);
			dg = GetGValue(m_crTargetColor) - GetGValue(cr);
			db = GetBValue(m_crTargetColor) - GetBValue(cr);
			  
			dclr = (dr*dr)+(dg*dg)+(db*db);
*/
			
			// compute color difference in HLS space (which are cylindrical coords)
			// dc = s1^2 + s2^2 - 2*s1*s2*cos(h1-h2) + (l1-l2)^2
			
			::ColorRGBToHLS( m_crTargetColor, &HH, &LL, &SS );
			
			dH = HH - hue;
			dL = LL - lum;
			dS = SS*SS + sat*sat;
			
			dclr = (int)((double)dS - 2.0*SS*sat*cos( TwoPiOver240*dH ) + (double)dL*dL);
			
			if (dclr<dclrmax)
			{
				dclrmax=dclr;
				m_rcFocusOutline = block;
				m_crCurrentFocusColor = cr;
			}
			
			block.OffsetRect( dx, 0 );
		}
	}
	
	// outline the rectangle that contains the target color
	
	m_rcFocusOutline.InflateRect(1,1);
	
	// if underlying colors are pale, use dark yellow outline for the target
	// otherwise, if underlying colors are dark enough, use a white brush
	
	COLORREF crOutline = ( m_iLum > 210 ) ? RGB( 200, 200, 100 ) : RGB(255,255,255);
	CBrush brush( crOutline );
	dc.FrameRect( &m_rcFocusOutline, &brush );
	
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CSpectrumWnd::SetLum(int iLum)
{
	ASSERT( iLum>=0 );
	m_iLum = iLum;
}


void CSpectrumWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// check if user clicked inside or outside of current focus rectangle
	// if inside, start a drag operation
	// if outside, then re-set the current focus poition
	
	if ( m_rcFocusOutline.PtInRect( point )	)
	{
		m_bIsDragging = TRUE;
		SetCapture();
	}
	else
	{
		// determine which cell user clicked inside (don't forget about one-pixel offset)
		
		CPoint ccp = GetCellCoordinatesFromPoint( point );
		
		// set new focus color and tell parent to re-draw us
		
		m_crCurrentFocusColor = *(m_crArray + ccp.y*m_cbCells + ccp.x);
		GetParent()->SendMessage( UWM_SPECTRUMWINDOWEVENT, (WPARAM)SWE_NEWFOCUSCOLOR, 0L );
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CSpectrumWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	if ( m_bIsDragging && nFlags==MK_LBUTTON )
	{	
		CPoint ccp = GetCellCoordinatesFromPoint( point );
			
		// set new focus color and tell parent to re-draw us
			
		m_crCurrentFocusColor = *(m_crArray + ccp.y*m_cbCells + ccp.x);
		GetParent()->SendMessage( UWM_SPECTRUMWINDOWEVENT, (WPARAM)SWE_NEWFOCUSCOLOR, 0L );
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CSpectrumWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bIsDragging = FALSE;
	ReleaseCapture();
	
	CWnd::OnLButtonUp(nFlags, point);
}


#define RestrictToInclusiveRange( ii, min, max ) ((ii)<(min))?(min):( ((ii)>(max))?(max):(ii) )
CPoint CSpectrumWnd::GetCellCoordinatesFromPoint(CPoint point)
{
	// determine which cell user clicked inside (don't forget about one-pixel offset)
	
	CRect rc;
	GetClientRect( &rc );
	int dx = rc.Width()/m_cbCells;
	int dy = rc.Height()/m_cbCells;
	
	CPoint pt;
	pt.x = (point.x-1)/dx;
	pt.y = (point.y-1)/dy;

	pt.x = RestrictToInclusiveRange( pt.x, 0, m_cbCells-1 );
	pt.y = RestrictToInclusiveRange( pt.y, 0, m_cbCells-1 );

	ASSERT( pt.x + pt.y*m_cbCells < m_cbCells*m_cbCells );	// bounds check
	ASSERT( pt.x + pt.y*m_cbCells >= 0 );
	
	return pt;
}




// static const array of named colors, for the 
// foolish purpose of giving names to colors when copying them to the 
// clipboard
static const struct
{
	char*		name;
	COLORREF	cr;
}
NamedColors[]=
{
		"aliceblue",	(COLORREF)  0x00FFF8F0,
		"antiquewhite",	(COLORREF)  0x00D7EBFA,
		"aqua",			(COLORREF)  0x00FFFF00,
		"aquamarine",	(COLORREF)  0x00D4FF7F,
		"azure",		(COLORREF)  0x00FFFFF0,
		"beige",		(COLORREF)  0x00DCF5F5,
		"bisque",		(COLORREF)  0x00C4E4FF,
		"black",		(COLORREF)  0x00000000,
		"blanchedalmond",	(COLORREF)  0x00CDEBFF,
		"blue",			(COLORREF)  0x00FF0000,
		"blueviolet",	(COLORREF)  0x00E22B8A,
		"brown",		(COLORREF)  0x002A2AA5,
		"burlywood",	(COLORREF)  0x0087B8DE,
		"cadetblue",	(COLORREF)  0x00A09E5F,
		"chartreuse",	(COLORREF)  0x0000FF7F,
		"chocolate",	(COLORREF)  0x001E69D2,
		"coral",		(COLORREF)  0x00507FFF,
		"cornflowerblue",	(COLORREF)  0x00ED9564,
		"cornsilk",		(COLORREF)  0x00DCF8FF,
		"crimson",		(COLORREF)  0x003C14DC,
		"cyan",			(COLORREF)  0x00FFFF00,
		"darkblue",		(COLORREF)  0x008B0000,
		"darkcyan",		(COLORREF)  0x008B8B00,
		"darkgoldenrod",	(COLORREF)  0x000B86B8,
		"darkgray",		(COLORREF)  0x00A9A9A9,
		"darkgreen",	(COLORREF)  0x00006400,
		"darkkhaki",	(COLORREF)  0x006BB7BD,
		"darkmagenta",	(COLORREF)  0x008B008B,
		"darkolivegreen",	(COLORREF)  0x002F6B55,
		"darkorange",	(COLORREF)  0x00008CFF,
		"darkorchid",	(COLORREF)  0x00CC3299,
		"darkred",		(COLORREF)  0x0000008B,
		"darksalmon",	(COLORREF)  0x007A96E9,
		"darkseagreen",	(COLORREF)  0x008BBC8F,
		"darkslateblue",	(COLORREF)  0x008B3D48,
		"darkslategray",	(COLORREF)  0x004F4F2F,
		"darkturquoise",	(COLORREF)  0x00D1CE00,
		"darkviolet",		(COLORREF)  0x00D30094,
		"deeppink",		(COLORREF)  0x009314FF,
		"deepskyblue",	(COLORREF)  0x00FFBF00,
		"dimgray",		(COLORREF)  0x00696969,
		"dodgerblue",	(COLORREF)  0x00FF901E,
		"firebrick",	(COLORREF)  0x002222B2,
		"floralwhite",	(COLORREF)  0x00F0FAFF,
		"forestgreen",	(COLORREF)  0x00228B22,
		"fuchsia",		(COLORREF)  0x00FF00FF,
		"gainsboro",	(COLORREF)  0x00DCDCDC,
		"ghostwhite",	(COLORREF)  0x00FFF8F8,
		"gold",			(COLORREF)  0x0000D7FF,
		"goldenrod",	(COLORREF)  0x0020A5DA,
		"gray",			(COLORREF)  0x00808080,
		"green",		(COLORREF)  0x00008000,
		"greenyellow",	(COLORREF)  0x002FFFAD,
		"honeydew",		(COLORREF)  0x00F0FFF0,
		"hotpink",		(COLORREF)  0x00B469FF,
		"indianred",	(COLORREF)  0x005C5CCD,
		"indigo",		(COLORREF)  0x0082004B,
		"ivory",		(COLORREF)  0x00F0FFFF,
		"khaki",		(COLORREF)  0x008CE6F0,
		"lavender",		(COLORREF)  0x00FAE6E6,
		"lavenderblush",	(COLORREF)  0x00F5F0FF,
		"lawngreen",	(COLORREF)  0x0000FC7C,
		"lemonchiffon",	(COLORREF)  0x00CDFAFF,
		"lightblue",	(COLORREF)  0x00E6D8AD,
		"lightcoral",	(COLORREF)  0x008080F0,
		"lightcyan",	(COLORREF)  0x00FFFFE0,
		"lightgoldenrodyellow",		(COLORREF)  0x00D2FAFA,
		"lightgray",	(COLORREF)  0x00D3D3D3,
		"lightgreen",	(COLORREF)  0x0090EE90,
		"lightpink",	(COLORREF)  0x00C1B6FF,
		"lightsalmon",	(COLORREF)  0x007AA0FF,
		"lightseagreen",	(COLORREF)  0x00AAB220,
		"lightskyblue",		(COLORREF)  0x00FACE87,
		"lightslategray",	(COLORREF)  0x00998877,
		"lightsteelblue",	(COLORREF)  0x00DEC4B0,
		"lightyellow",		(COLORREF)  0x00E0FFFF,
		"lime",			(COLORREF)  0x0000FF00,
		"limegreen",	(COLORREF)  0x0032CD32,
		"linen",		(COLORREF)  0x00E6F0FA,
		"magenta",		(COLORREF)  0x00FF00FF,
		"maroon",		(COLORREF)  0x00000080,
		"mediumaquamarine",	(COLORREF)  0x00AACD66,
		"mediumblue",		(COLORREF)  0x00CD0000,
		"mediumorchid",		(COLORREF)  0x00D355BA,
		"mediumpurple",		(COLORREF)  0x00DB7093,
		"mediumseagreen",	(COLORREF)  0x0071B33C,
		"mediumslateblue",	(COLORREF)  0x00EE687B,
		"mediumspringgreen",	(COLORREF)  0x009AFA00,
		"mediumturquoise",		(COLORREF)  0x00CCD148,
		"mediumvioletred",		(COLORREF)  0x008515C7,
		"midnightblue",		(COLORREF)  0x00701919,
		"mintcream",		(COLORREF)  0x00FAFFF5,
		"mistyrose",	(COLORREF)  0x00E1E4FF,
		"moccasin",		(COLORREF)  0x00B5E4FF,
		"navajowhite",	(COLORREF)  0x00ADDEFF,
		"navy",			(COLORREF)  0x00800000,
		"oldlace",		(COLORREF)  0x00E6F5FD,
		"olive",		(COLORREF)  0x00008080,
		"olivedrab",	(COLORREF)  0x00238E6B,
		"orange",		(COLORREF)  0x0000A5FF,
		"orangered",	(COLORREF)  0x000045FF,
		"orchid",		(COLORREF)  0x00D670DA,
		"palegoldenrod",	(COLORREF)  0x00AAE8EE,
		"palegreen",		(COLORREF)  0x0098FB98,
		"paleturquoise",	(COLORREF)  0x00EEEEAF,
		"palevioletred",	(COLORREF)  0x009370DB,
		"papayawhip",		(COLORREF)  0x00D5EFFF,
		"peachpuff",	(COLORREF)  0x00B9DAFF,
		"peru",			(COLORREF)  0x003F85CD,
		"pink",			(COLORREF)  0x00CBC0FF,
		"plum",			(COLORREF)  0x00DDA0DD,
		"powderblue",	(COLORREF)  0x00E6E0B0,
		"purple",		(COLORREF)  0x00800080,
		"red",			(COLORREF)  0x000000FF,
		"rosybrown",	(COLORREF)  0x008F8FBC,
		"royalblue",	(COLORREF)  0x00E16941,
		"saddlebrown",	(COLORREF)  0x0013458B,
		"salmon",		(COLORREF)  0x007280FA,
		"sandybrown",	(COLORREF)  0x0060A4F4,
		"seagreen",		(COLORREF)  0x00578B2E,
		"seashell",		(COLORREF)  0x00EEF5FF,
		"sienna",		(COLORREF)  0x002D52A0,
		"silver",		(COLORREF)  0x00C0C0C0,
		"skyblue",		(COLORREF)  0x00EBCE87,
		"slateblue",	(COLORREF)  0x00CD5A6A,
		"slategray",	(COLORREF)  0x00908070,
		"snow",			(COLORREF)  0x00FAFAFF,
		"springgreen",	(COLORREF)  0x007FFF00,
		"steelblue",	(COLORREF)  0x00B48246,
		"tan",			(COLORREF)  0x008CB4D2,
		"teal",			(COLORREF)  0x00808000,
		"thistle",		(COLORREF)  0x00D8BFD8,
		"tomato",		(COLORREF)  0x004763FF,
		"turquoise",	(COLORREF)  0x00D0E040,
		"violet",		(COLORREF)  0x00EE82EE,
		"wheat",		(COLORREF)  0x00B3DEF5,
		"white",		(COLORREF)  0x00FFFFFF,
		"whitesmoke",	(COLORREF)  0x00F5F5F5,
		"yellow",		(COLORREF)  0x0000FFFF,
		"yellowgreen",	(COLORREF)  0x0032CD9A 
};

CString CSpectrumWnd::GetNameOfClosestColor(COLORREF cr, COLORREF* crNamed /* = NULL */)
{
	// iterates through list of named colors to find the one with 
	// the smallest error in HLS coordinates
	
	int iMax = sizeof(NamedColors)/sizeof(NamedColors[0]);
	double twoPiOver240 = 2.0F * 3.1415926 / 240.0F;
	
	int dclr, dclrmax;	// delta errors
	int dH, dL, dS;		// deltas in HLS coords
	WORD tHH, tLL, tSS;	// test color in HLS coords
	WORD iHH, iLL, iSS;	// input color in HLS coords
	dclrmax = SHRT_MAX;	// big number
	COLORREF crTest;
	CString strRet;
	strRet.Empty();
	
	::ColorRGBToHLS( cr, &iHH, &iLL, &iSS );
	
	for ( int ii=0; ii<iMax; ii++ )
	{
		crTest = NamedColors[ii].cr;
		::ColorRGBToHLS( crTest, &tHH, &tLL, &tSS );
		
		// compute color difference in HLS space (which are cylindrical coords)
		// dc = s1^2 + s2^2 - 2*s1*s2*cos(h1-h2) + (l1-l2)^2
		
		dH = iHH - tHH;
		dL = iLL - tLL;
		dS = iSS*iSS + tSS*tSS;
		
		dclr = (int)((double)dS - 2.0*iSS*tSS*cos( twoPiOver240*dH ) + (double)dL*dL);
		
		if (dclr<dclrmax)
		{
			dclrmax = dclr;
			strRet = NamedColors[ii].name;
			if ( crNamed )
				*crNamed = crTest;
		}
	}
	
	return strRet;
	
}

