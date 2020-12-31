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

#ifndef __OSCILLOPLOT_H_122333444455555__
#define __OSCILLOPLOT_H_122333444455555__

#include "../../Basics/XYPlotImpl.h"

// class CPlot is a basement class
class COscilloPlot
{
public:
	COscilloPlot();
	virtual ~COscilloPlot();

	void				SetDefaults( );
	void				CopySettings( const COscilloPlot *plot );

protected:
	bool				m_bShowVCursor,m_bShowHCursor;
	double				m_fCursorX,m_fCursorY;
	bool				m_bHoldCursorToCurve;
	int					m_nIndexToHoldCursor;
	int					m_nCursorSize, m_nCursorStyle;
	COLORREF			m_crCursorColor;
	bool				m_bEnableXZoneSel,m_bEnableYZoneSel;
	double				m_fXZoneSelLower,m_fXZoneSelUpper;
	double				m_fYZoneSelLower,m_fYZoneSelUpper;
	COLORREF			m_crZoneSelColor;
public:
	inline bool			IsShowHCursor() { return m_bShowHCursor; }
	inline void			SetShowHCursor( bool show ) { m_bShowHCursor=show; }
	inline bool			IsShowVCursor() { return m_bShowVCursor; }
	inline void			SetShowVCursor( bool show ) { m_bShowVCursor=show; }
	inline void			SetShowCursor( bool show ) { m_bShowHCursor=show; m_bShowVCursor=show; }
	inline bool			IsHoldCursorToCurve() { return m_bHoldCursorToCurve; }
	inline void			SetHoldCursorToCurve( bool hold ){ m_bHoldCursorToCurve = hold; }
	inline double		GetCursorX() { return m_fCursorX; }
	inline void			SetCursorX( double cursor ) { m_fCursorX = cursor; }
	inline double		GetCursorY() { return m_fCursorY; }
	inline void			SetCursorY( double cursor ) { m_fCursorY = cursor; }
	inline void			GetCursor( double *val ) { val[0]=m_fCursorX; val[1]=m_fCursorY; }
	inline void			SetCursor( double *val ) { m_fCursorX=val[0]; m_fCursorY=val[1]; }
	inline int			GetIndexToHoldCursor() { return m_nIndexToHoldCursor; }
	inline void			SetIndexToHoldCursor( int index) { m_nIndexToHoldCursor=index; }
	inline int			GetCursorSize(){return m_nCursorSize;}
	inline void			SetCursorSize(int size){m_nCursorSize = size;}
	inline int			GetCursorStyle(){return m_nCursorStyle;}
	inline void			SetCursorStyle(int style){m_nCursorStyle =style; }
	inline COLORREF		GetCursorColor() { return m_crCursorColor; }
	inline void			SetCursorColor( COLORREF color ) { m_crCursorColor = color; }

	inline bool			IsEnableXZoneSel() { return m_bEnableXZoneSel; }
	inline void			SetEnableXZoneSel( bool enable ) { m_bEnableXZoneSel=enable; }
	inline bool			IsEnableYZoneSel() { return m_bEnableYZoneSel; }
	inline void			SetEnableYZoneSel( bool enable ) { m_bEnableYZoneSel=enable; }
	inline double		GetXZoneSelLower() { return m_fXZoneSelLower; }
	inline void			SetXZoneSelLower( double lower) { m_fXZoneSelLower=lower; }
	inline double		GetXZoneSelUpper() { return m_fXZoneSelUpper; }
	inline void			SetXZoneSelUpper( double upper) { m_fXZoneSelUpper=upper; }
	inline double		GetYZoneSelLower() { return m_fYZoneSelLower; }
	inline void			SetYZoneSelLower( double lower) { m_fYZoneSelLower=lower; }
	inline double		GetYZoneSelUpper() { return m_fYZoneSelUpper; }
	inline void			SetYZoneSelUpper( double upper) { m_fYZoneSelUpper=upper; }
	inline COLORREF		GetZoneSelColor() { return m_crZoneSelColor; }
	inline void			SetZoneSelColor( COLORREF color) { m_crZoneSelColor=color; }
};

#endif