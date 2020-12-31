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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is a templated class 

#ifndef __SPLITPLOTIMPL_H_122333444455555__
#define __SPLITPLOTIMPL_H_122333444455555__

#include "../../Basics/XYHandler.h"
#include "../../Basics/XYPlotImpl.h"
#include "SplitPlot.h"

// This templated class
template <typename CXYPlotImplT>
class CSplitPlotImpl : public CSplitPlot<CXYPlotImplT>, public CPlotImpl
{
public:
	CSplitPlotImpl();
	virtual ~CSplitPlotImpl();

	RECT	GetPlotRect(RECT clientRect,int nIndex);

	void	OnDraw( HWND hWnd );
	void	OnDraw( HDC hDC, RECT destRect );

	int		GetPlotIndex( POINT point );

	// CPlotImpl is a pure virtual class, so the following functions should be defined
	virtual CAxis	*NewAxis(){ return 0; }
	virtual CLegend	*NewLegend(){ return 0; }
	virtual	bool	IsEmpty(){ return GetDataSetCount()<=0; }
	virtual void	GetPlotRange( double *xRange, double *yRange ){}

	//add the following function since m_rctLastClientRect have inherited twice
	RECT			GetLastClientRect(){return CSplitPlot<CXYPlotImplT>::GetLastClientRect();}
	void			SetLastClientRect(RECT rt){CSplitPlot<CXYPlotImplT>::SetLastClientRect(rt);}
protected:
	void	EraseBkgnd( HDC hDC, RECT destRect );

public:
	POINT	m_ptOrigin,m_ptCurr;
	int		m_nPositionOrigin;
	int		m_nSpliterIndex;
	bool	m_bDragRowSpliter, m_bDragColSpliter;
};

template <typename SplitPlotImplT>
class CSplitHandler : public CHandler<SplitPlotImplT>
{
public:
	bool	OnMouseDown( HWND hWnd, POINT point );
	bool	OnMouseUp( HWND hWnd, POINT point );
	bool	OnMouseDblClk( HWND hWnd, POINT point );
	bool	OnMouseMove( HWND hWnd, POINT point );
	bool	OnContextMenu( HMENU hMenu, HWND hWnd, POINT point );
	
	void	Interactive(HWND hWnd, UINT message, POINT point);
	void	Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

template <typename XYPlotImplT>
class CSplitPlotImplI : public CSplitPlotImpl<XYPlotImplT>, public CSplitHandler<CSplitPlotImplI<XYPlotImplT> >
{

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implimentations of CSplitPlotImpl

template <typename CXYPlotImplT>
CSplitPlotImpl<CXYPlotImplT>::CSplitPlotImpl()
{
	m_bDragRowSpliter = false;
	m_bDragColSpliter = false;
}

template <typename CXYPlotImplT>
CSplitPlotImpl<CXYPlotImplT>::~CSplitPlotImpl()
{
}

template <typename CXYPlotImplT>
RECT	CSplitPlotImpl<CXYPlotImplT>::GetPlotRect(RECT clientRect,int nIndex)
{
	int iRow,iCol;
	RECT rect={0,0,0,0};

	switch( m_nSplitMode )
	{
	case kSplitNot:
		rect = clientRect;
		break;
	case kSplitNM:
		iRow = nIndex / m_nCols;
		iCol = nIndex % m_nCols;

		rect.top = m_vnRowSpliter[iRow];
		rect.bottom = m_vnRowSpliter[iRow+1];
		rect.left = m_vnColSpliter[iCol];
		rect.right = m_vnColSpliter[iCol+1];

		break;
	case kSplit3L2R1:
		switch(nIndex)
		{
		case 0:
			{
				RECT rt={m_vnColSpliter[0],m_vnRowSpliter[0],m_vnColSpliter[1],m_vnRowSpliter[1]};
				rect = rt;
			}
			break;
		case 1:
			{
				RECT rt={m_vnColSpliter[0],m_vnRowSpliter[1],m_vnColSpliter[1],m_vnRowSpliter[2]};
				rect = rt;
			}
			break;
		default:
			{
				RECT rt={m_vnColSpliter[1],m_vnRowSpliter[0],m_vnColSpliter[2],m_vnRowSpliter[2]};
				rect = rt;
			}
			break;
		}
		break;
	case kSplit3L1R2:
		switch(nIndex)
		{
		case 0:
			{
				RECT rt={m_vnColSpliter[0],m_vnRowSpliter[0],m_vnColSpliter[1],m_vnRowSpliter[2]};
				rect = rt;
			}
			break;
		case 1:
			{
				RECT rt={m_vnColSpliter[1],m_vnRowSpliter[0],m_vnColSpliter[2],m_vnRowSpliter[1]};
				rect = rt;
			}
			break;
		default:
			{
				RECT rt={m_vnColSpliter[1],m_vnRowSpliter[1],m_vnColSpliter[2],m_vnRowSpliter[2]};
				rect = rt;
			}
			break;
		}
		break;
	case kSplit3T2B1:
		switch(nIndex)
		{
		case 0:
			{
				RECT rt={m_vnColSpliter[0],m_vnRowSpliter[0],m_vnColSpliter[1],m_vnRowSpliter[1]};
				rect = rt;
			}
			break;
		case 1:
			{
				RECT rt={m_vnColSpliter[1],m_vnRowSpliter[0],m_vnColSpliter[2],m_vnRowSpliter[1]};
				rect = rt;
			}
			break;
		default:
			{
				RECT rt={m_vnColSpliter[0],m_vnRowSpliter[1],m_vnColSpliter[2],m_vnRowSpliter[2]};
				rect = rt;
			}
			break;
		}
		break;
	case kSplit3T1B2:
		switch(nIndex)
		{
		case 0:
			{
				RECT rt={m_vnColSpliter[0],m_vnRowSpliter[0],m_vnColSpliter[2],m_vnRowSpliter[1]};
				rect = rt;
			}
			break;
		case 1:
			{
				RECT rt={m_vnColSpliter[0],m_vnRowSpliter[1],m_vnColSpliter[1],m_vnRowSpliter[2]};
				rect = rt;
			}
			break;
		default:
			{
				RECT rt={m_vnColSpliter[1],m_vnRowSpliter[1],m_vnColSpliter[2],m_vnRowSpliter[2]};
				rect = rt;
			}
			break;
		}
		break;
	default:
		rect = clientRect;
		break;
	}
	return rect;
}

template <typename CXYPlotImplT>
int		CSplitPlotImpl<CXYPlotImplT>::GetPlotIndex( POINT point )
{
	int i;

	int iCol,iRow;
	
	for( i=0; i<m_nCols; i++)
	{
		if( point.x >= m_vnColSpliter[i] && point.x < m_vnColSpliter[i+1] )
		{
			iCol = i;
			break;
		}
	}
	for( i=0; i<m_nRows; i++)
	{
		if( point.y >= m_vnRowSpliter[i] && point.y < m_vnRowSpliter[i+1] )
		{
			iRow = i;
			break;
		}
	}

	int idx;
	switch(m_nSplitMode)
	{
	case kSplitNot:
		return 0;
	case kSplitNM:
		return iRow * m_nCols + iCol;
	case kSplit3L2R1://(iR,iC),(0,0)=0,(0,1)=2,(1,0)=1,(1,1)=2
		idx = iRow + 2*iCol;
		if(idx==3)idx=2;
		return idx;
	case kSplit3L1R2://(iR,iC),(0,0)=0,(0,1)=1,(1,0)=0,(1,1)=2
		idx = iRow + iCol;
		if(iRow ==1 && iCol ==0 )idx=0;
		return idx;
	case kSplit3T2B1://(iR,iC),(0,0)=0,(0,1)=1,(1,0)=2,(1,1)=2
		idx = 2*iRow + iCol;
		if(idx==3)idx=2;
		return idx;
	case kSplit3T1B2://(iR,iC),(0,0)=0,(0,1)=0,(1,0)=1,(1,1)=2
		idx = iRow + iCol;
		if(iRow ==0 && iCol ==1 )idx=0;
		return idx;
	default:
		return -1;
	}
}

template <typename CXYPlotImplT>
void	CSplitPlotImpl<CXYPlotImplT>::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);

	OnDraw( hDC, destRect );

	ReleaseDC(hWnd, hDC);
}

template <typename CXYPlotImplT>
void	CSplitPlotImpl<CXYPlotImplT>::OnDraw(HDC hDC, RECT destRect)
{
	InitSpliters(destRect);
	UseColOffsets();
	UseRowOffsets();
	for(int i=0; i<GetPlotsCount(m_nSplitMode, m_nRows, m_nCols); i++)
	{
		m_vpPlots[i]->OnDraw(hDC,GetPlotRect(destRect,i) );
	}
	SetLastClientRect(destRect);
}

template <typename CXYPlotImplT>
void	CSplitPlotImpl<CXYPlotImplT>::EraseBkgnd( HDC hDC, RECT destRect )
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////
//

template <typename SplitPlotImplT>
bool	CSplitHandler<SplitPlotImplT>::OnMouseDown( HWND hWnd, POINT point )
{
	SplitPlotImplT *pT=static_cast<SplitPlotImplT*>(this);

	HDC hDC = GetDC( hWnd );
	SetCapture(hWnd);

	int rowspliter, colspliter;
	bool bcol = pT->HitColSpliter(point, colspliter);
	bool brow = pT->HitRowSpliter(point, rowspliter);
	if( bcol || brow )
	{
		RECT clientRect, clipRect;
		GetClientRect(hWnd, &clientRect);
		clipRect = clientRect;
		if(bcol && colspliter > 0)
		{
			pT->m_bDragColSpliter = true;
			pT->m_bDragRowSpliter = false;
			pT->m_nSpliterIndex = colspliter;
			pT->m_nPositionOrigin = pT->m_vnColSpliter[colspliter];

			clipRect.left = pT->m_vnColSpliter[colspliter-1]+40;
			clipRect.right = pT->m_vnColSpliter[colspliter+1]-40;
			ClientToScreen(hWnd,(LPPOINT)&clipRect);
			ClientToScreen(hWnd,(LPPOINT)&clipRect+1);
			ClipCursor(&clipRect);
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		}
		else if(brow && rowspliter > 0)
		{
			pT->m_bDragColSpliter = false;
			pT->m_bDragRowSpliter = true;
			pT->m_nSpliterIndex = rowspliter;
			pT->m_nPositionOrigin = pT->m_vnRowSpliter[rowspliter];

			clipRect.top = pT->m_vnRowSpliter[rowspliter-1]+40;
			clipRect.bottom = pT->m_vnRowSpliter[rowspliter+1]-40;
			ClientToScreen(hWnd,(LPPOINT)&clipRect);
			ClientToScreen(hWnd,(LPPOINT)&clipRect+1);
			ClipCursor(&clipRect);
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
		}
		pT->m_ptOrigin = pT->m_ptCurr = point;
		
		ReleaseDC(hWnd, hDC);
		return true;
	}
	ReleaseDC(hWnd, hDC);

	int idx = pT->GetPlotIndex( point );
	if( idx < 0 ) return false;
	return pT->m_vpPlots[idx]->OnMouseDown(hWnd, point);
}

template <typename SplitPlotImplT>
bool	CSplitHandler<SplitPlotImplT>::OnMouseUp( HWND hWnd, POINT point )
{
	SplitPlotImplT *pT=static_cast<SplitPlotImplT*>(this);

	if(GetCapture())ReleaseCapture();
	ClipCursor(NULL);

	pT->m_bDragColSpliter = false;
	pT->m_bDragRowSpliter = false;

	int idx = pT->GetPlotIndex( point );
	if( idx < 0 ) return false;
	return pT->m_vpPlots[idx]->OnMouseUp(hWnd, point);
}

template <typename SplitPlotImplT>
bool	CSplitHandler<SplitPlotImplT>::OnMouseDblClk( HWND hWnd, POINT point )
{
	SplitPlotImplT *pT=static_cast<SplitPlotImplT*>(this);
	int idx = pT->GetPlotIndex( point );
	if( idx < 0 ) return false;
	return pT->m_vpPlots[idx]->OnMouseDblClk(hWnd, point);
}

template <typename SplitPlotImplT>
bool	CSplitHandler<SplitPlotImplT>::OnMouseMove( HWND hWnd, POINT point )
{
	SplitPlotImplT *pT=static_cast<SplitPlotImplT*>(this);
	// Drag the edge
	if(pT->m_bDragColSpliter)
	{
		pT->m_ptCurr = point;
		
		int pos = pT->m_nPositionOrigin;
		pos+=(pT->m_ptCurr.x-pT->m_ptOrigin.x);
		pT->m_vnColSpliter[pT->m_nSpliterIndex] = pos;

		pT->CalcColOffsets();
		return true;
	}
	else if(pT->m_bDragRowSpliter)
	{
		pT->m_ptCurr = point;
		
		int pos = pT->m_nPositionOrigin;
		pos+=(pT->m_ptCurr.y-pT->m_ptOrigin.y);
		pT->m_vnRowSpliter[pT->m_nSpliterIndex] = pos;

		pT->CalcRowOffsets();
		return true;
	}

	// SetCursor
	int spliter;
	if( pT->HitColSpliter(point, spliter) )
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
	}
	else if( pT->HitRowSpliter(point, spliter) )
	{
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
	}
	
	// default behaver
	int idx = pT->GetPlotIndex( point );
	if( idx < 0 ) return false;
	return pT->m_vpPlots[idx]->OnMouseMove(hWnd, point);
}

template <typename SplitPlotImplT>
bool	CSplitHandler<SplitPlotImplT>::OnContextMenu( HMENU hMenu, HWND hWnd, POINT point )
{
	SplitPlotImplT *pT=static_cast<SplitPlotImplT*>(this);
	int idx = pT->GetPlotIndex( point );
	if( idx < 0 ) return false;
	return pT->m_vpPlots[idx]->OnContextMenu(hMenu, hWnd, point);
}

template <typename SplitPlotImplT>
void	CSplitHandler<SplitPlotImplT>::Interactive(HWND hWnd, UINT message, POINT point)
{
	SplitPlotImplT *pT=static_cast<SplitPlotImplT*>(this);
	switch(message)
	{
	case WM_LBUTTONDOWN:
		if(OnMouseDown(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_LBUTTONUP:
		if(OnMouseUp(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_LBUTTONDBLCLK:
		if(OnMouseDblClk(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_MOUSEMOVE:
		if(OnMouseMove(hWnd,point))pT->OnDraw(hWnd);
		break;
	case WM_CONTEXTMENU:
		if(OnContextMenu(NULL, hWnd, point))pT->OnDraw(hWnd);
		break;
	case WM_SIZE:
		pT->OnDraw(hWnd);
	case WM_ERASEBKGND:
		return;
	default:
		return;
	}
}

template <typename SplitPlotImplT>
void	CSplitHandler<SplitPlotImplT>::Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SplitPlotImplT *pT=static_cast<SplitPlotImplT*>(this);
	POINT	point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	Interactive(hWnd, message, point);
}

#endif