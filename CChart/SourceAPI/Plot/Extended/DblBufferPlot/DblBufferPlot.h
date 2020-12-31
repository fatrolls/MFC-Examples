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

#ifndef __DBLBUFFERPLOT_H_122333444455555__
#define __DBLBUFFERPLOT_H_122333444455555__

#include "../../Basics/XYPlotImpl.h"

// class CPlot is a basement class
class CDblBufferPlot
{
public:
	CDblBufferPlot();
	virtual ~CDblBufferPlot();

	void				SetDefaults( );
	void				CopySettings( const CDblBufferPlot *plot );

protected:
	HWND				m_hWnd;
	bool				m_bUpdate;

	//virtual window parameters
	HDC m_hMemDC;
	int m_maxX,m_maxY;

protected:
	void				CreateVirtualWindow();
	void				ReleaseVirtualWindow();

public:
	inline bool			IsUpdate(){return m_bUpdate;}
	inline void			SetUpdate(bool update){m_bUpdate = update;}
};

#endif