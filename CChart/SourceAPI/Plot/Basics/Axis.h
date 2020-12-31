/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2011 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */

#ifndef __AXIS_H_122333444455555__
#define __AXIS_H_122333444455555__

#include "Plot.h"
//#include "Origin.h"

// Axis locations
enum
{
	kLocationLeft = 0,
	kLocationBottom,
	kLocationRight,
	kLocationTop,
	kLocationCenterVL,
	kLocationCenterVR,
	kLocationCenterHB,
	kLocationCenterHT,

	kLocationTDX,
	kLocationTDY,
	kLocationTDZ,

	kLocationCount
};

// Axis title position
enum
{
	kTitlePositionNormal = 0,
	kTitlePositionLower,
	kTitlePositionUpper,

	kTitlePositionCount
};
// Tick position
enum
{
	kTickPositionNone = 0,
	kTickPositionInner,
	kTickPositionOuter,
	kTickPositionBoth,

	kTickPositionCount
};

class CAxis
{
public:
	CAxis();
	virtual ~CAxis();

protected:
	int			m_nTickCount;	// number of tick marks
	int			m_nMinorTickCount;	// number of minor ticks

	int			m_nTickLength, m_nMinorTickLength;	// length of tick marks (logical units)
	int			m_nTickPosition, m_nMinorTickPosition;	// position of the ticks
	int			m_nTickSize, m_nMinorTickSize; // thickness of the ticks
	COLORREF	m_crTickColor, m_crMinorTickColor; // color of the ticks
	int			m_nAxisSize;		// Size of the line
	int			m_nLineStyle;		// style of the line;
	double		m_Range[2];		// range of the axis
	bool		m_bVisible;		// is axis visible?
	string		m_strTitle;		// axis title
	int			m_nLocation;		// location of axis (left, bottom, top, etc.)
	LOGFONT		m_lfTitleFont;	// font to use for title
	LOGFONT		m_lfLabelFont;	// font to use for axis labels
	COLORREF	m_crAxisColor;		// color to use for axis and font
	COLORREF	m_crTitleColor;	// color to use for title
	bool		m_bRangeSet;		// has the range been set?
	
	bool		m_bAutoMajorTick;
	bool		m_bAutoMinorTick;
	bool		m_bShowMajorTicks;
	bool		m_bShowMinorTicks;

	bool		m_bShowTickLabel;
	COLORREF	m_crTickLabelColor;
	int			m_nMarginHorizontal,m_nMarginVertical;

	bool		m_bSameColor;

	bool		m_bCurrent;

	int			m_nTitlePosition;
	SIZE		m_sizeTitleOffset;
	SIZE		m_sizeLabelOffset;

	bool		m_bReplaceLabel;
	vector<string>	m_vstrAlternateLabels;
	string		m_strLabelSuffix;

public:

	void		SetDefaults( void );
	void		CopySettings( CAxis *axis );

public:
	// some inline functions
	inline int		GetTickCount( void ) { return m_nTickCount; }
	inline void		SetTickCount( int tickCount ) { m_nTickCount = tickCount; }
	inline int		GetMinorTickCount( void ) { return m_nMinorTickCount; }
	inline void		SetMinorTickCount( int tickCount ) { m_nMinorTickCount = tickCount; }
	inline int		GetTickLength( void ) { return m_nTickLength; }
	inline void		SetTickLength( int length ) { m_nTickLength=length; }
	inline int		GetMinorTickLength( void ) { return m_nMinorTickLength; }
	inline void		SetMinorTickLength( int length ) { m_nMinorTickLength=length; }
	inline int		GetTickPosition( void ) { return m_nTickPosition; }
	inline void		SetTickPosition( int position ) { m_nTickPosition=position; }
	inline int		GetMinorTickPosition( void ) { return m_nMinorTickPosition; }
	inline void		SetMinorTickPosition( int position ) { m_nMinorTickPosition=position; }
	inline int		GetTickSize( void ) { return m_nTickSize; }
	inline void		SetTickSize( int Size ) { m_nTickSize=Size; }
	inline int		GetMinorTickSize( void ) { return m_nMinorTickSize; }
	inline void		SetMinorTickSize( int size ) { m_nMinorTickSize=size; }
	inline COLORREF	GetTickColor( void ) { return m_crTickColor; }
	inline void		SetTickColor( COLORREF color ) { m_crTickColor=color; }
	inline COLORREF	GetMinorTickColor( void ) { return m_crMinorTickColor; }
	inline void		SetMinorTickColor( COLORREF color ) { m_crMinorTickColor=color; }
	inline bool		IsAutoMajorTick( void ) { return m_bAutoMajorTick; }//actual calculation implemented in XYChart.cpp
	inline void		SetAutoMajorTick( bool at ) { m_bAutoMajorTick=at; }
	inline bool		IsAutoMinorTick( void ) { return m_bAutoMinorTick; }
	inline void		SetAutoMinorTick( bool amt ) { m_bAutoMinorTick=amt; }
	inline bool		IsShowMajorTicks() { return m_bShowMajorTicks; }
	inline void		SetShowMajorTicks( bool show ) { m_bShowMajorTicks=show; }
	inline bool		IsShowMinorTicks() { return m_bShowMinorTicks; }
	inline void		SetShowMinorTicks( bool show ) { m_bShowMinorTicks=show; }

	inline bool		IsVisible( void ) { return m_bVisible; }
	inline void		SetVisible( bool visible ) { m_bVisible=visible; }

	inline string	GetTitle() { return m_strTitle; }
	inline void		SetTitle( string title ) { m_strTitle = title; }
	inline LOGFONT	&GetTitleFont() { return m_lfTitleFont; }
	inline void		SetTitleFont( LOGFONT font)	{ m_lfTitleFont=font; }
	inline LOGFONT	&GetLabelFont() { return m_lfLabelFont; }
	inline void		SetLabelFont( LOGFONT font)	{ m_lfLabelFont=font; }
	inline COLORREF GetTitleColor( void ) { return m_crTitleColor; }
	inline void		SetTitleColor( COLORREF color ) {m_crTitleColor = color; }
	inline COLORREF	GetTickLabelColor( void ) { return m_crTickLabelColor; }
	inline void		SetTickLabelColor( COLORREF color ) { m_crTickLabelColor=color; }
	inline bool		IsShowTickLabel( void ) { return m_bShowTickLabel; }
	inline void		SetShowTickLabel( bool show ) { m_bShowTickLabel=show; }

	inline COLORREF	GetAxisColor( void ) { return m_crAxisColor; }
	inline void		SetAxisColor( COLORREF color ) { m_crAxisColor = color; }
	inline int		GetAxisSize( void ) { return m_nAxisSize; }
	inline void		SetAxisSize( int size ) { if( size > 0 ) m_nAxisSize = size; }
	inline int		GetLineStyle( void ) { return m_nLineStyle; }
	inline void		SetLineStyle( int style ) { if( style > 0 ) m_nLineStyle = style; }


	inline short	GetLocation( void ) { return m_nLocation; }
	inline void		SetLocation( short location ) { m_nLocation = location; }
	inline bool		IsRangeSet( void ) { return m_bRangeSet; }
	inline void		SetRangeSet( bool set ) { m_bRangeSet=set; }

	inline int		GetTitlePosition( void ) { return m_nTitlePosition; }
	inline void		SetTitlePosition( int pos ) { m_nTitlePosition=pos; m_lfTitleFont.lfHeight*=4; m_lfTitleFont.lfHeight/=5; }
	inline SIZE		GetTitleOffset() { return m_sizeTitleOffset; }
	inline void		SetTitleOffset( SIZE offset ) { m_sizeTitleOffset=offset; }
	inline SIZE		GetLabelOffset() { return m_sizeLabelOffset; }
	inline void		SetLabelOffset( SIZE offset ) { m_sizeLabelOffset=offset; }
	inline bool		IsReplaceLabel() { return m_bReplaceLabel; }
	inline void		SetReplaceLabel( bool replace ) { m_bReplaceLabel = replace; }
	inline string	GetLabelSuffix() { return m_strLabelSuffix; }
	inline void		SetLabelSuffix(string suffix) { m_strLabelSuffix = suffix; }
	
	inline bool		IsCurrent(){return m_bCurrent;}
	inline void		SetCurrent(bool cur){m_bCurrent=cur;}

	inline void		GetRange( double *range ) { memcpy( range, m_Range, 2 * sizeof( double ) ); }
	inline double	GetLowerRange( void ) { return m_Range[0]; }
	inline double	GetUpperRange( void ) { return m_Range[1]; }
	inline void		SetRange( double low, double high ) { m_Range[0] = low; m_Range[1] = high; m_bRangeSet = true; }
	inline void		SetRange( bool set, double low, double high ) { m_Range[0] = low; m_Range[1] = high; m_bRangeSet = set; }

	inline bool		IsSameColor(){return m_bSameColor;}
	inline void		SetSameColor(bool same){m_bSameColor=same;}

	inline vector<string>	&GetAlternateLabels() { return m_vstrAlternateLabels; }

	//void		AddAxisPopupMenus( HMENU menu, int startVal );
	//void		AddNumberOfTicksPopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal, BOOL bAuto );
	//int			InterpretAxisPopupMenuItem( int which );

};

#endif