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

#ifndef __PIEPLOT_H_122333444455555__
#define __PIEPLOT_H_122333444455555__

class	CPiePlot
{
public:
	CPiePlot();
	virtual ~CPiePlot();

	void	SetDefaults();
	void	CopySettings(CPiePlot *plot);

public:
	int		m_nMaxPies;
	double	m_fScale;
	int		m_nLineSize;
	int		m_nLineStyle;
	COLORREF	m_crLineColor;
	bool	m_bCircleMode;
	SIZE	m_sizeOffset;
	bool	m_bDragMode;
	
	LOGFONT	m_lfPieTitleFont;
	bool	m_bShowPieTitle;
	double	m_fStartAngle;
	bool	m_bClockWise;

	bool	m_bShadowing;
	int		m_nShadowHalfLength;
	double	m_fShadowAngle;
	COLORREF	m_crShadowColor;

public:
	inline	int		GetMaxPies() { return m_nMaxPies; }
	inline	void	SetMaxPies( int num ) { m_nMaxPies = num; }
	inline	double	GetScale() { return m_fScale; }
	inline	void	SetScale(double scale) { m_fScale = scale; }

	inline	int		GetLineSize() { return m_nLineSize; }
	inline	void	SetLineSize(int size){ m_nLineSize = size; }
	inline	int		GetLineStyle() { return m_nLineStyle; }
	inline	void	SetLineStyle(int style) { m_nLineStyle = style; }
	inline	bool	IsCircleMode() { return m_bCircleMode; }
	inline	void	SetCircleMode(bool circle) { m_bCircleMode = circle; }
	inline	COLORREF	GetLineColor() { return m_crLineColor; }
	inline	void		SetLineColor( COLORREF color ) { m_crLineColor = color; }
	inline	bool	IsShowPieTitle() { return m_bShowPieTitle; }
	inline	void	SetShowPieTitle( bool show ) { m_bShowPieTitle = show; }
	inline	double	GetStartAngle() { return m_fStartAngle; }
	inline	void	SetStartAngle(double angle) { m_fStartAngle = angle; }
	inline	bool	IsClockWise() { return m_bClockWise; }
	inline	void	SetClockWise(bool clockwise) { m_bClockWise = clockwise; }

	inline	bool	IsShadowing() { return m_bShadowing; }
	inline	void	SetShadowing(bool shadow) { m_bShadowing = shadow; }
	inline	int		GetShadowHalfLength() { return m_nShadowHalfLength; }
	inline	void	SetShadowHalfLength(int len){ m_nShadowHalfLength = len; }
	inline	double	GetShadowAngle() { return m_fShadowAngle; }
	inline	void	SetShadowAngle(double angle) { m_fShadowAngle = angle; }
	inline	COLORREF	GetShadowColor() { return m_crShadowColor; }
	inline	void		SetShadowAngle(COLORREF color) { m_crShadowColor = color; }
	inline	SIZE	GetOffset() { return m_sizeOffset; }
	inline	void	SetOffset(SIZE offset) { m_sizeOffset = offset; }
	inline	bool	IsDragMode() { return m_bDragMode; }
	inline	void	SetDragMode(bool drag) { m_bDragMode = drag; }
};

#endif