//*******************************************************************************************************/
//* FileName        : clPlot.h
//*
//* Description	    : Real Time Plot for MFC
//*
//* Contents:		: axis		y (x) axis info.
//*					  timeaxis	time axis info
//*					  legend	legend info.
//*					  serie		data serie info & array
//*					  clPlot	The plot itself.
//*
//* Author          : Jan Vidar Berger
//*******************************************************************************************************/
#if !defined(AFX_DQPLOT_H__0D536D37_5CF1_11D1_AED1_0060973A08A4__INCLUDED_)
#define AFX_DQPLOT_H__0D536D37_5CF1_11D1_AED1_0060973A08A4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// clPlot.h : header file
//
#define MAXLEGENDS	10
#define MAXSERIES	50

//*******************************************************************************************************/
//* simple data value struct. used in dynamic array
//*******************************************************************************************************/
typedef struct _value{
	double	dValue;
	CTime	ValueTime;
}value;

//*******************************************************************************************************/
//* non-time axis. used for left and right y axis. might be used for x as well.
//*******************************************************************************************************/
class  AFX_EXT_CLASS axis
{
public:
	CString szTitle;
	double	minrange;
	double	maxrange;

	double	m_dValuePrPixel;

	axis()
	{
		szTitle	= "Title";
		minrange	= 0.0;
		maxrange	= 2000.0;

		m_dValuePrPixel = 1;
	};
};

//*******************************************************************************************************/
//* time axis
//*******************************************************************************************************/
class  AFX_EXT_CLASS timeaxis
{
public:
	CString		m_szTitle;		// time axis title;
	CTime		m_mintime;		// min time
	CTime		m_maxtime;		// max time
	int			m_iTimeMode;	// axis grid and legend interval index

	double		m_dSecondsPrPixel;

	timeaxis()
	{
		m_szTitle = "Time";
		m_mintime = 0;
		m_maxtime = 600;
		m_iTimeMode=0;
		m_dSecondsPrPixel=1;
	}
};

//*******************************************************************************************************/
//* legend
//*******************************************************************************************************/
class  AFX_EXT_CLASS legend
{
public:
	BOOL		m_bIAmInUse;
	COLORREF	m_color;		// legend color code
	int			m_istyle;
	CString		m_szTitle;		// legend title

	legend(){
		m_bIAmInUse = FALSE;
		m_color		= 0;
		m_istyle	= PS_SOLID;
		m_szTitle	= "";
	}
};

//*******************************************************************************************************/
//* data serie
//*******************************************************************************************************/
class  AFX_EXT_CLASS serie
{
public:
	BOOL		m_bIAmInUse;
	COLORREF	m_color;		// serie line color
	int			m_iLineStyle;	// line style
	BOOL		m_bRightAxisAlign; // align to right axis
	value	*	m_pvalues;		// value array
	long		m_lNoValues;	// no values (used for array size)
	long		m_lbegin;		// list begin
	long		m_lend;			// list end
//	CPen		m_pen;			// pre-calculated pen (for speed)

	serie();
	~serie();

	void AddPoint(CTime &valuetime, double &y);
	void Reset();
};

//*******************************************************************************************************/
//* Class           : clPlot
//*
//* Base Class      : public CWnd
//*
//* Description     : Plot Component.
//*
//*					  This is a standard plot and can be used for any application.
//*
//*						1. A special 'autoscroll'mode exist for real time plots.
//*						2. Only a minimum of features are implemented.
//*						3. Series and legends are separated and must be set up individually.
//*						4. A set of defines (see top of file) are used to set the max array sizes.
//*						5. Only time are supported as x-axis.
//*						6. A large range of pre-calculated values are used for maximum speed.
//*
//* Author          : Jan Vidar Berger
//*******************************************************************************************************/
class AFX_EXT_CLASS clPlot : public CWnd
{
// Construction
public:
	clPlot();
	virtual ~clPlot();

// Attributes
public:

	CRect		m_ctlRect;			// control rect
	CRect		m_clientRect;		// ctlRect - borderspace
	CRect		m_plotRect;			// clientRect - margins
	CRect		m_legendRect;		// any rect within clientRect
	CRect		m_axisLYRect;		// Left axisi rect
	CRect		m_axisRYRect;		// right y axis
	CRect		m_axisBXRect;		// bottom x axis

	int			m_iMleft;			// left margin
	int			m_iMright;			// right margin
	int			m_iMtop;			// top margin
	int			m_iMbottom;			// bottom margin

	COLORREF	m_ctlBkColor;		// control background color
	COLORREF	m_plotBkColor;		// plot bacground color
	COLORREF	m_legendBkColor;	// legend background color
	COLORREF	m_gridColor;		// grid line color

	BOOL		m_bctlBorder;		// control border
	BOOL		m_bplotBorder;		// plot border
	BOOL		m_blegendBorder;	// legend border
	BOOL		m_bPrimaryLegend;	// primary legend
	BOOL		m_bSecondaryLegend;	// secondary legend
	BOOL		m_bAxisLY;			// left axis
	BOOL		m_bAxisRY;			// right axis
	BOOL		m_bAxisBX;			// bottom axis
	BOOL		m_bAutoScrollX;		// automatic x range scrolling
	BOOL		m_bSimMode;			// simulate data input

	static long	m_lMaxDataPrSerie;	// max allowed data pr. serie.
	static long	m_lMaxDataTotal;	// max allowed data total.
	double		m_dNoData;			// No Data Value (used for gaps)

	legend		m_primarylegends[MAXLEGENDS];
	legend		m_secondarylegends[MAXLEGENDS];

	serie		m_series[MAXSERIES];

	axis		m_leftaxis;			// left axis
	axis		m_rightaxis;		// right axis
	timeaxis	m_timeaxis;			// bottom axis

	CPoint		*pLineArray;		// pre-calculated when new data are entered into the system
	long		lArraySize;			// current size of pLineArray

	CFont		m_font;
	LOGFONT		m_logFont;
	LOGFONT		m_zoomFont;
	double		m_dzoom;
	int			m_TextHeight;

// Operations
public:
	BOOL		Create(DWORD dwstyle, CRect &rect, CWnd *pParent, UINT id);
	void		MoveWindow(CRect &Rect);

	virtual void Draw(CDC * dc);			// Draw the entire plot
	virtual void DrawBasic(CDC * dc);		// Draw plot basics
	virtual void DrawPlot(CDC * dc);		// Draw the plot series
	virtual void DrawSerie(CDC *dc, int serie);
	virtual void DrawGrid(CDC * dc);		// Draw grids
	virtual void DrawLegendShadow(CDC * dc);// Draw legend shadows
	virtual void DrawLegend(CDC * dc);		// Draw legends

	virtual void DrawYAxisGrid(CDC * dc);
	virtual void DrawXAxisGrid(CDC * dc);

	virtual void ComputeRects(BOOL bInitialize);

	virtual BOOL AddPoint(int serie, CTime &valuetime, double &y);
	virtual void SetBXRange(CTime &fromtime, CTime &totime,BOOL bMove=TRUE);
	virtual void SetLYRange(double &minrange, double &maxrange);
	virtual void SetRYRange(double &minrange, double &maxrange);
	virtual void Reset();

	virtual void SetSerie(int s, int style, COLORREF color, double minrange, double maxrange, const char *szTitle, BOOL Rightalign=FALSE);
	virtual void SetLegend(int l, int style, COLORREF color, const char *text);
	virtual void SetBXTitle(const char *title);
	virtual void SetLYTitle(const char *title);
	virtual void SetRYTitle(const char *title);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(clPlot)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(clPlot)
	afx_msg void OnPaint();
	//}}AFX_MSG
	BOOL clPlot::OnEraseBkgnd(CDC* pDC) ;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DQPLOT_H__0D536D37_5CF1_11D1_AED1_0060973A08A4__INCLUDED_)
