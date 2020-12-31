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

#ifndef __SPLITPLOT_H_122333444455555__
#define __SPLITPLOT_H_122333444455555__

// enumutation of split modes
enum
{
	kSplitNot=0,
	kSplitNM=1,
	kSplit3L1R2=2,
	kSplit3L2R1=3,
	kSplit3T1B2=4,
	kSplit3T2B1=5,

	kSplitModeCount
};


// This templated class
template <class CXYPlotImplT>
class CSplitPlot
{
private:
	class CXYIT: public CXYPlotImplT, public CXYHandler<CXYIT>{};
public:
	CSplitPlot();
	virtual ~CSplitPlot();

	void	SetDefaults();
	void	CopySettings(CSplitPlot *plot);

public:
	int		m_nSplitMode;
	int		m_nRows;
	int		m_nCols;

	vector<CXYIT *>	m_vpPlots;
	vector<int> m_vnRowSpliter, m_vnColSpliter;
	vector<int> m_vnRowOffset, m_vnColOffset;

	bool	m_bDragMode;
	
public:
	inline	bool	IsDragMode() { return m_bDragMode; }
	inline	void	SetDragMode( bool drag ) { m_bDragMode = drag; }
	inline	int		GetSplitMode(){ return m_nSplitMode; }
	inline	int		GetRows(){ return m_nRows; }
	inline	int		GetCols(){ return m_nCols; }
	int				GetPlotsCount(int mode, int nRows, int nCols);
	int				GetPlotsCount();
	int				GetDataSetCount();
	CXYPlotImplT	*GetPlot(int nIndex);

private:
	RECT		m_rctLastClientRect;
protected:
	void		InitSpliters(RECT clientRect);

public:
	void		DeleteAll();
	void		ResizePlots(int mode, int nRows, int nCols);

	int			AddCurve( double *pX, double *pY, int nLen, int nIndex );
public:
	bool		HitRowSpliter(POINT point, int &index);
	bool		HitColSpliter(POINT point, int &index);
	void		CalcColOffsets();
	void		CalcRowOffsets();
	void		UseColOffsets();
	void		UseRowOffsets();

	inline RECT	GetLastClientRect(){return m_rctLastClientRect;}
	inline void	SetLastClientRect(RECT rt){m_rctLastClientRect=rt;}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implimentations of CSplitPlot

template <class CXYPlotImplT>
CSplitPlot<CXYPlotImplT>::CSplitPlot()
{

	m_nSplitMode = kSplitNot;
	m_nRows = 1;
	m_nCols = 1;

	SetRectEmpty(&m_rctLastClientRect);

	ResizePlots( m_nSplitMode, m_nRows, m_nCols );
}

template <class CXYPlotImplT>
CSplitPlot<CXYPlotImplT>::~CSplitPlot()
{
	DeleteAll();
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::SetDefaults()
{
	ResizePlots( kSplitNot, 1, 1 );
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::CopySettings(CSplitPlot *plot)
{
	ResizePlots(plot->GetSplitMode(), plot->GetRows(), plot->GetCols());
}

template <class CXYPlotImplT>
int		CSplitPlot<CXYPlotImplT>::GetPlotsCount(int mode, int nRows, int nCols)
{
	switch(mode)
	{
	case kSplitNot:
		return 1;
	case kSplitNM:
		if(nRows<1)nRows=1;
		if(nCols<1)nCols=1;
		return nRows*nCols;
	case kSplit3L1R2:
	case kSplit3L2R1:
	case kSplit3T1B2:
	case kSplit3T2B1:
		return 3;
	default:
		return 1;
	}
}

template <class CXYPlotImplT>
int		CSplitPlot<CXYPlotImplT>::GetPlotsCount()
{
	return GetPlotsCount(m_nSplitMode, m_nRows, m_nCols);
}

template <class CXYPlotImplT>
int		CSplitPlot<CXYPlotImplT>::GetDataSetCount()
{
	int nPlots = GetPlotsCount();
	int counts=0;
	for( int i=0; i<nPlots; i++)
	{
		counts+=m_vpPlots[i]->GetDataSetCount();
	}
	return counts;
}

template <class CXYPlotImplT>
CXYPlotImplT*	CSplitPlot<CXYPlotImplT>::GetPlot(int nIndex)
{
	if(nIndex<0 || nIndex>=GetPlotsCount())return NULL;
	return m_vpPlots[nIndex];
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::InitSpliters(RECT clientRect)
{
	int i;
	for( i=0; i<m_nCols+1; i++)
	{
		m_vnColSpliter[i] = clientRect.left + i * ( clientRect.right - clientRect.left )/m_nCols;
	}
	for( i=0; i<m_nRows+1; i++)
	{
		m_vnRowSpliter[i] = clientRect.top + i * ( clientRect.bottom - clientRect.top )/m_nRows;
	}
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::DeleteAll()
{
	if(m_vpPlots.size()>0)
	{
		for(int i=m_vpPlots.size()-1; i>=0; i--)
		{
			if(m_vpPlots[i])
			{
				delete m_vpPlots[i];
				m_vpPlots[i] = NULL;
			}
			m_vpPlots.pop_back();
		}
	}
}

template <class CXYPlotImplT>
int		CSplitPlot<CXYPlotImplT>::AddCurve( double *pX, double *pY, int nLen, int nIndex )
{
	if(nIndex<0 || nIndex>=GetPlotsCount(m_nSplitMode, m_nRows, m_nCols))
		return -1;
	return m_vpPlots[nIndex]->AddCurve(pX, pY, nLen);
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::ResizePlots(int mode, int nRows, int nCols)
{
	int i;

	if(nRows<=0)nRows=1;
	if(nCols<=0)nCols=1;

	DeleteAll();

	m_vpPlots.resize(GetPlotsCount(mode, nRows, nCols));
	for(i=0; i<GetPlotsCount(mode, nRows, nCols); i++)
	{
		//m_vpPlots[i] = new CXYPlotImplT;
		m_vpPlots[i] = new CXYIT;
		m_vpPlots[i]->AddAxis(kLocationLeft);
		m_vpPlots[i]->AddAxis(kLocationBottom);
		m_vpPlots[i]->SetMarginLeft(2);
		m_vpPlots[i]->SetMarginRight(2);
		m_vpPlots[i]->SetMarginTop(2);
		m_vpPlots[i]->SetMarginBottom(2);
	}
	m_nSplitMode = mode;
	switch(mode)
	{
	case kSplitNot:
		m_nRows =1;
		m_nCols =1;
		break;
	case kSplitNM:
		m_nRows = nRows;
		m_nCols = nCols;
		break;
	case kSplit3L1R2:
	case kSplit3L2R1:
	case kSplit3T1B2:
	case kSplit3T2B1:
		m_nRows = 2;
		m_nCols = 2;
		break;
	default:
		m_nRows = 1;
		m_nCols = 1;
		break;
	}
	m_vnRowSpliter.resize(m_nRows+1);
	m_vnColSpliter.resize(m_nCols+1);
	m_vnRowOffset.resize(m_nRows+1);
	m_vnColOffset.resize(m_nCols+1);
	for( i=0; i<m_nCols+1; i++)
	{
		m_vnColOffset[i] = 0;
	}
	for( i=0; i<m_nRows+1; i++)
	{
		m_vnRowOffset[i] = 0;
	}
}

template <class CXYPlotImplT>
bool		CSplitPlot<CXYPlotImplT>::HitRowSpliter(POINT point, int &index)
{
	for(int i=1; i<m_nRows; i++)
	{
		if( abs(point.y - m_vnRowSpliter[i]) <= 2 )
		{
			index = i;
			return true;
		}
	}
	return false;
}

template <class CXYPlotImplT>
bool		CSplitPlot<CXYPlotImplT>::HitColSpliter(POINT point, int &index)
{
	for(int i=1; i<m_nCols; i++)
	{
		if( abs(point.x - m_vnColSpliter[i]) <= 2 )
		{
			index = i;
			return true;
		}
	}
	return false;
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::CalcColOffsets()
{
	for( int i=1; i<m_nCols; i++ )
	{
		m_vnColOffset[i] = m_vnColSpliter[i] - 
			( m_rctLastClientRect.left + i * ( m_rctLastClientRect.right - m_rctLastClientRect.left )/m_nCols );
	}
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::CalcRowOffsets()
{
	for( int i=1; i<m_nRows; i++ )
	{
		m_vnRowOffset[i] = m_vnRowSpliter[i] - 
			( m_rctLastClientRect.top + i * ( m_rctLastClientRect.bottom - m_rctLastClientRect.top )/m_nRows );
	}
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::UseColOffsets()
{
	for( int i=1; i<m_nCols; i++ )
	{
		m_vnColSpliter[i] += m_vnColOffset[i];
	}
}

template <class CXYPlotImplT>
void	CSplitPlot<CXYPlotImplT>::UseRowOffsets()
{
	for( int i=1; i<m_nRows; i++ )
	{
		m_vnRowSpliter[i] += m_vnRowOffset[i];
	}
}

#endif