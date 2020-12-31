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

#ifndef __LEGEND_H_122333444455555__
#define __LEGEND_H_122333444455555__

class CPlot;

class CLegend
{
protected:
	CPlot				*m_pPlot;
	SIZE				m_sizeOffset;
	int					m_nMaxNumOfLegend;
	COLORREF			m_crBorderColor;
	COLORREF			m_crBkgndColor;
	int					m_nBorderLineSize;
	int					m_nBorderLineStyle;
	int					m_nLineLength;
	bool				m_bTransparent;
	int					m_nMarginSize;
	int					m_nDragMarginSize;

	bool				m_bConfined;

	bool				m_bCurrent;

	LOGFONT				m_lfFont;

	bool				m_bDragMode;
	POINT				m_ptOrigin,m_ptCurr;
	SIZE				m_sizeOffsetOrigin;
	
	bool				m_bColorRect;

public:
	CLegend();
	virtual ~CLegend();

	void			SetDefaults();
	void			CopySettings(const CLegend *legend);
public:
	virtual	void	OnDraw( HDC hDC, RECT plotRect) = 0;

	inline SIZE		GetOffset(){return m_sizeOffset;}
	inline void		SetOffset(SIZE offset){m_sizeOffset = offset;}
	inline int		GetMaxNumOfLegend(){return m_nMaxNumOfLegend;}
	inline void		SetMaxNumOfLegend(int num){if(num >= 0)m_nMaxNumOfLegend = num;}
	inline COLORREF	GetBorderColor(){return m_crBorderColor;}
	inline void		SetBorderColor(COLORREF color){m_crBorderColor = color;}
	inline COLORREF	GetBkgndColor(){return m_crBkgndColor;}
	inline void		SetBkgndColor(COLORREF color){m_crBkgndColor = color;}
	inline int		GetBorderLineSize(){return m_nBorderLineSize;}
	inline void		SetBorderLizeSize(int size){if(size>0)m_nBorderLineSize = size;}
	inline int		GetBorderLineStyle(){return m_nBorderLineStyle;}
	inline void		SetBorderLizeStyle(int style){m_nBorderLineStyle = style;}
	inline bool		IsTransparent(){return m_bTransparent;}
	inline void		SetTransparent(bool transparent){m_bTransparent = transparent;}
	inline bool		IsDragMode(){return m_bDragMode;}
	inline void		SetDragMode(bool drag,POINT pointStart){m_bDragMode = drag;m_ptOrigin = pointStart;m_ptCurr = pointStart;m_sizeOffsetOrigin = m_sizeOffset;}
	inline POINT	GetCurrentPoint(){return m_ptCurr;}
	inline void		SetCurrentPoint(POINT point){m_ptCurr = point;}
	inline int		GetMarginSize(){return m_nMarginSize;}
	inline void		SetMarginSize(int size){m_nMarginSize = size; }
	inline int		GetDragMarginSize(){return m_nDragMarginSize;}
	inline void		SetDragMarginSize(int size){m_nDragMarginSize = size; }
	inline bool		IsConfined(){return m_bConfined;}
	inline void		SetConfined(bool confine){m_bConfined = confine;}
	inline bool		IsColorRect(){return m_bColorRect;}
	inline void		SetColorRect(bool cr){m_bColorRect = cr;}

	inline LOGFONT	&GetFont() { return m_lfFont; }
	inline void		SetFont(LOGFONT font) { m_lfFont = font;}
	inline void		SetFontHeight(int height){if(height>0)m_lfFont.lfHeight = height;}

	inline bool		IsCurrent(){return m_bCurrent;}
	inline void		SetCurrent(bool cur){m_bCurrent = cur;}

};

#endif