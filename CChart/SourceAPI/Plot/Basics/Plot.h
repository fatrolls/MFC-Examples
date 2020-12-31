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

#ifndef __PLOT_H_122333444455555__
#define __PLOT_H_122333444455555__

#define DEFAULT_WHITE_BACKGROUND 1

#include <string>
#include <vector>
using namespace std;
#include <math.h>
#include "ColorTable.h"
#include "MyConst.h"

class CLegend;
class CAxis;
//class CPlotData;

const int kMaxAxes = 8;

enum
{
	kPopupError = -1,
	kPopupNoAction = -2,
	kPopupUpdate = -3
};

enum
{
	kBrushNull=0,
	kBrushSolid=1,
	kBrushHatch=2,
	kBrushPattern=3,
		
	kBrushTypeCount
};

// class CPlot is a basement class
class CPlot// : public COrigin
{
public:
	CPlot();
	virtual ~CPlot();

	void		SetDefaults();
	void		CopySettings(const CPlot *plot);

	void		DeleteAll();

private:
	// Variables
	RECT		m_rctLastClientRect;

protected:
	bool		m_bUseMajorHGrids;
	bool		m_bUseMajorVGrids;
	bool		m_bUseMinorHGrids;
	bool		m_bUseMinorVGrids;
	COLORREF	m_crMajorGridColor, m_crMinorGridColor;
	int			m_nMajorGridLineSize, m_nMinorGridLineSize;
	int			m_nMajorGridLineStyle, m_nMinorGridLineStyle;

	CAxis		*m_pAxes[kMaxAxes];
	int			m_nAxisCount;
	
	string		m_strTitle;
	LOGFONT		m_lfTitleFont;
	COLORREF	m_crTitleColor;
	
	COLORREF	m_crBorderColor;
	int			m_nBorderSize, m_nBorderStyle;

	bool		m_bEraseBkgnd;
	int			m_nBkgndBrushType;
	COLORREF	m_crBkgndColor;
	int			m_nBkgndHatchStyle;
	HBITMAP		m_hBkgndPattern;
	bool		m_bGradientBkgnd;
	bool		m_bGradientHorizontal;
	COLORREF	m_crGradientColor1,m_crGradientColor2;

	bool		m_bUseDataRegionBrush;
	int			m_nDataRegionBrushType;
	COLORREF	m_crDataRegionColor;
	int			m_nDataRegionHatchStyle;
	HBITMAP		m_hDataRegionPattern;

	int			m_nMarginLeft,m_nMarginRight,m_nMarginTop,m_nMarginBottom;
	
	bool		m_bEqualXYRange,m_bEqualXYAxis;
	
	string		m_strSubtitle;
	LOGFONT		m_lfSubtitleFont;
	COLORREF	m_crSubtitleColor;
	bool		m_bSubtitleShow;
	SIZE		m_sizeSubtitleOffset;

	bool		m_bLightDataRegion;
	bool		m_bLightTitle;
	COLORREF	m_crLightColor;
	int			m_nLightLineSize;
	int			m_nLightLineStyle;

	CLegend		*m_pLegend;
	bool		m_bUseLegend;

public:
	inline	bool		IsUseMajorHGrids(){return m_bUseMajorHGrids;}
	inline	void		SetUseMajorHGrids(bool bUse){m_bUseMajorHGrids=bUse;}
	inline	bool		IsUseMajorVGrids(){return m_bUseMajorVGrids;}
	inline	void		SetUseMajorVGrids(bool bUse){m_bUseMajorVGrids=bUse;}
	inline	bool		IsUseMinorHGrids(){return m_bUseMinorHGrids;}
	inline	void		SetUseMinorHGrids(bool bUse){m_bUseMinorHGrids=bUse;}
	inline	bool		IsUseMinorVGrids(){return m_bUseMinorVGrids;}
	inline	void		SetUseMinorVGrids(bool bUse){m_bUseMinorVGrids=bUse;}

	inline string&		GetTitle( void ) { return m_strTitle; }
	inline void			SetTitle( string title ) { m_strTitle = title; }
	inline COLORREF		GetTitleColor( void ) { return m_crTitleColor; }
	inline void			SetTitleColor( COLORREF color ) { m_crTitleColor = color; }
	inline LOGFONT&		GetTitleFont() { return m_lfTitleFont; }
	inline void			SetTitleFont( LOGFONT font ) { m_lfTitleFont = font; }

	inline string&		GetSubtitle( void ) { return m_strSubtitle; }
	inline void			SetSubtitle( string title ) { m_strSubtitle = title; }
	inline bool			IsSubtitleShow( void ) { return m_bSubtitleShow; }
	inline void			SetSubtitleShow( bool show ) { m_bSubtitleShow = show; }
	inline SIZE			GetSubtitleOffset( void ) { return m_sizeSubtitleOffset; }
	inline void			SetSubtitleOffset( SIZE offset ) { m_sizeSubtitleOffset=offset; }
	inline COLORREF		GetSubtitleColor( void ) { return m_crSubtitleColor; }
	inline void			SetSubtitleColor( COLORREF color ) { m_crSubtitleColor = color; }
	inline LOGFONT		&GetSubtitleFont() { return m_lfSubtitleFont; }
	inline void			SetSubtitleFont( LOGFONT font ) { m_lfSubtitleFont = font; }

	inline int			GetMajorGridLineSize( void ) { return m_nMajorGridLineSize; }
	inline void			SetMajorGridLineSize( int lineSize ) { if( lineSize > 0 ) m_nMajorGridLineSize = lineSize; }
	inline int			GetMinorGridLineSize( void ) { return m_nMinorGridLineSize; }
	inline void			SetMinorGridLineSize( int lineSize ) { if( lineSize > 0 ) m_nMinorGridLineSize = lineSize; }
	inline int			GetMajorGridLineStyle( void ) { return m_nMajorGridLineStyle; }
	inline void			SetMajorGridLineStyle( int lineStyle ) { m_nMajorGridLineStyle = lineStyle; }
	inline int			GetMinorGridLineStyle( void ) { return m_nMinorGridLineStyle; }
	inline void			SetMinorGridLineStyle( int lineStyle ) { m_nMinorGridLineStyle = lineStyle; }
	inline COLORREF		GetMajorGridColor( void ) { return m_crMajorGridColor; }
	inline void			SetMajorGridColor( COLORREF color ) { m_crMajorGridColor = color; }
	inline COLORREF		GetMinorGridColor( void ) { return m_crMinorGridColor; }
	inline void			SetMinorGridColor( COLORREF color ) { m_crMinorGridColor = color; }

	inline int			GetBkgndBrushType( void ){ return m_nBkgndBrushType; }
	inline void			SetBkgndBrushType( int type ){ m_nBkgndBrushType = type; }
	inline int			GetBkgndHatchStyle( void ){ return m_nBkgndHatchStyle; }
	inline void			SetBkgndHatchStyle( int style ){ m_nBkgndHatchStyle = style; }
	inline HBITMAP		GetBkgndPattern( void ){ return m_hBkgndPattern; }
	inline void			SetBkgndPattern( HBITMAP pattern ){ m_hBkgndPattern = pattern; }
	inline	COLORREF	GetBkgndColor( void ) { return m_crBkgndColor; }
	inline void			SetBkgndColor( COLORREF color ) { m_crBkgndColor = color; }
	inline	COLORREF	GetBorderColor( void ) { return m_crBorderColor; }
	inline void			SetBorderColor( COLORREF color ) { m_crBorderColor = color; }
	inline	int			GetBorderSize( void ) { return m_nBorderSize; }
	inline void			SetBorderStyle( int style ) { m_nBorderStyle = style; }
	inline	int			GetBorderStyle( void ) { return m_nBorderStyle; }
	inline void			SetBorderSize( int size ) { m_nBorderSize = size; }
	inline	bool		IsEraseBkgnd( void ) { return m_bEraseBkgnd; }
	inline void			SetEraseBkgnd( bool how ) { m_bEraseBkgnd = how; }

	inline int			GetMarginLeft(){ return m_nMarginLeft; }
	inline void			SetMarginLeft(int margin){ m_nMarginLeft = margin; }
	inline int			GetMarginRight(){ return m_nMarginRight; }
	inline void			SetMarginRight(int margin){ m_nMarginRight = margin; }
	inline int			GetMarginTop(){ return m_nMarginTop; }
	inline void			SetMarginTop(int margin){ m_nMarginTop = margin; }
	inline int			GetMarginBottom(){ return m_nMarginBottom; }
	inline void			SetMarginBottom(int margin){ m_nMarginBottom = margin; }

	inline bool			IsEqualXYRange(){ return m_bEqualXYRange; }
	inline void			SetEqualXYRange( bool equal ){ m_bEqualXYRange=equal; }
	inline bool			IsEqualXYAxis(){ return m_bEqualXYAxis; }
	inline void			SetEqualXYAxis( bool equal ){ m_bEqualXYAxis=equal; }

	inline int			GetDataRegionBrushType( void ){ return m_nDataRegionBrushType; }
	inline void			SetDataRegionBrushType( int type ){ m_nDataRegionBrushType = type; }
	inline int			GetDataRegionHatchStyle( void ){ return m_nDataRegionHatchStyle; }
	inline void			SetDataRegionHatchStyle( int style ){ m_nDataRegionHatchStyle = style; }
	inline HBITMAP		GetDataRegionPattern( void ){ return m_hDataRegionPattern; }
	inline void			SetDataRegionPattern( HBITMAP pattern ){ m_hDataRegionPattern = pattern; }
	inline COLORREF		GetDataRegionColor( void ) { return m_crDataRegionColor; }
	inline void			SetDataRegionColor( COLORREF color ) { m_crDataRegionColor = color; }
	inline bool			IsUseDataRegionBrush( void ) { return m_bUseDataRegionBrush; }
	inline void			SetUseDataRegionBrush( bool use ) { m_bUseDataRegionBrush = use; }
	inline bool			IsGradientBkgnd( void ) { return m_bGradientBkgnd; }
	inline void			SetGradientBkgnd( bool set) { m_bGradientBkgnd=set; }
	inline bool			IsGradientHorizontal( void ) { return m_bGradientHorizontal; }
	inline void			SetGradientHorizontal( bool hor ){ m_bGradientHorizontal=hor; }
	inline COLORREF		GetGradientColor1( void ) { return m_crGradientColor1; }
	inline void			SetGradientColor1( COLORREF color ) { m_crGradientColor1=color; }
	inline COLORREF		GetGradientColor2( void ) { return m_crGradientColor2; }
	inline void			SetGradientColor2( COLORREF color ) { m_crGradientColor2=color; }

	inline bool			IsLightTitle() { return m_bLightTitle; }
	inline void			SetLightTitle( bool light ) { m_bLightTitle=light; }
	inline bool			IsLightDataRegion() { return m_bLightDataRegion; }
	inline void			SetLightDataRegion( bool light ) { m_bLightDataRegion=light; }
	inline COLORREF		GetLightColor( void ) { return m_crLightColor; }
	inline void			SetLightColor( COLORREF color ) { m_crLightColor = color; }
	inline int			GetLightLineSize( void ) { return m_nLightLineSize; }
	inline void			SetLightLineSize( int size ) { m_nLightLineSize = size; }
	inline int			GetLigntLineStyle(){return m_nLightLineStyle;}
	inline void			SetLightLineStyle(int style){m_nLightLineStyle = style;}
	
	inline bool			IsUseLegend() { return m_bUseLegend; }
	inline void			SetUseLegend(bool use) { m_bUseLegend = use; }
	CLegend				*GetLegend();
	virtual CLegend		*NewLegend()=0;
	void				DeleteLegend();

public:
	inline RECT			GetLastClientRect(){return m_rctLastClientRect;}
	inline void			SetLastClientRect(RECT rt){m_rctLastClientRect=rt;}
	inline int			GetAxisCount( void ){ return m_nAxisCount; }
	CAxis				*GetAxis( int which ) { if( which >= 0 && which < m_nAxisCount ) return m_pAxes[which]; else return NULL; }
	CAxis				*AddAxis( int location );
	virtual CAxis		*NewAxis()=0;
	CAxis				*GetAxisByLocation( int location );
	int					GetAxisIndex( int location );
	void				RejectAxisByLocation(int location);
	void				RejectAxis( int which );// do not delete really, only not use it
	void				RejectAllAxes();
	void				DeleteAllAxes();

	bool				AxisLighted();
	void				UnlightAllAxis();

	void				DeleteUsedHandles();

	virtual void		GetPlotRange( double *xRange, double *yRange )=0;
	void				GetRange( double *xRange, double *yRange );
	void				GetXRange( double *range );
	void				GetYRange( double *range );
	void				SetRange( bool setX, double low, double high );
	void				SetXRange( double low, double high );
	void				SetYRange( double low, double high );
	void				IsAutoRange( bool &haveXRange, bool &haveYRange );
	bool				IsXAutoRange( void );
	bool				IsYAutoRange( void );
	void				SetAutoRange( bool setX );
	void				SetXAutoRange( void );
	void				SetYAutoRange( void );

public:
	virtual	bool		IsEmpty()=0;
public:
	static	bool		m_bNewInteractive;
	static	string		GetVersion(){ return "CChart Version 2.0.0.1"; }
	static	string		GetAuthorInfo(){ return "Baita, PHD, vice professor, living in Mianyang, fan of Mr Fang Zhouzi"; }
};

#endif