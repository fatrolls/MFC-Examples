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

#ifndef __XYPLOT_H_122333444455555__
#define __XYPLOT_H_122333444455555__

#include "Plot.h"
#include "PlotData.h"

// Plot type
enum
{
	kXYPlotScatter = 0,
	kXYPlotConnect = 1,
	kXYPlotStepHV = 2,
	kXYPlotStepVH = 3,
	kXYPlotStepHVH = 4,
	kXYPlotStepVHV = 5,
	kXYPlotBezier = 6,
	
	kPlotTypeCount
};

// Marker type
enum
{
	kXYMarkerNone = 0,
	kXYMarkerCircle = 1,
	kXYMarkerSquareUpright = 2,
	kXYMarkerSquareOblique = 3,
	kXYMarkerTriangleLeft = 4,
	kXYMarkerTriangleRight = 5,
	kXYMarkerTriangleUp = 6,
	kXYMarkerTriangleDown = 7,
	kXYMarkerX = 8,
	kXYMarkerDot = 9,
	
	kMarkerTypeCount
};

// Method of set colors
enum
{
	kSetColorFromTable=0,
	kSetColorFromTwoColor=1,
	
	kSetColorModeCount
};

// how to show dataset infomation
enum
{
	kShowDataSetInfoNot=0,
	kShowDataSetInfoEveryN=1,
	kShowDataSetInfoTotalN=2,
	
	kShowDataSetInfoModeCount
};

enum
{
	kDataFillClosed=0,
	kDataFillFromBottomAxis=1,
	kDataFillFromTopAxis=2,
	kDataFillFromLeftAxis=3,
	kDataFillFromRightAxis=4,

	kDataFillModeCount
};

typedef struct stXYDataInfo
{
	CPlotData<DataPoint2D>	*pDataSet;
	int			nDataID;

	int			nPlotType; // see above enum

	COLORREF	crDataColor;
	COLORREF	crPlotColor; // An RGB value
	bool		bAutoColor; // Let the program choose color

	int			nMarkerType;	// how to mark data values (see enum)
	int			nMarkerSize;
	int			nMarkerFrequency;
	bool		bMarkerFill;
	double		fXDataMin;
	double		fXDataMax;
	double		fYDataMin;
	double		fYDataMax;
	bool		bDataRangesSet;

	int			nDataLineSize;
	int			nPlotLineSize;

	int			nDataLineStyle;
	int			nPlotLineStyle;
	bool		bAutoLineStyle;

	int			nDataFillMode;
	bool		bDataFill;
	int			nDataFillBrushType;
	COLORREF	crDataFillColor;
	int			nDataFillHatchStyle;
	HBITMAP		hDataFillPattern;

	SIZE		sizeTitleOffset;
	double		fScale;
	bool		bDragMode;

	bool		bDataShow;
	bool		bSelected;
	bool		bLighted;

	bool		bSpecialFlag;
	
}XYDataInfo;
typedef std::vector<XYDataInfo> vXYDataInfo;

// class CPlot is a basement class
class CXYPlot
{
public:
	CXYPlot();
	virtual ~CXYPlot();

	void				SetDefaults( int index );
	void				SetDefaults( );
	void				CopySettings( const CXYPlot *plot );
	void				CopyAll( const CXYPlot *plot );

	bool				DeleteData( int dataID );
	void				DeleteAllData( void );
	void				DeleteAll( void );

	bool				SetDataModified( int dataID );
protected:
	vXYDataInfo			m_vXYDataInfo;
	int					m_nCurDataID;

	bool				m_bMultiSelect;
	
	int					m_nShowDataSetInfoMode;
	int					m_nShowDataSetInfoNum;
	int					m_nShowDataSetInfoDataPointStep;
	
	bool				m_bKeepFormer;

	bool				m_bAutoDataColor;
	int					m_nModeOfSetColors;
	COLORREF			m_crLineColor1,m_crLineColor2;
	
	bool				m_bAutoLineStyle;

public:
	int					AddCurve( double *pX, double *pY, int nLen );
	int					AddCurve( MyVData2D vData,int plottype = kXYPlotConnect,COLORREF color = RGB(0,0,0),int markertype = kXYMarkerCircle,int markerfreq = 0){ return AddDataSet(vData, plottype, color, markertype, markerfreq); }
	int					AddDataSet( MyVData2D vData,int plottype, COLORREF color, int markertype, int markerfreq );

public:
	vXYDataInfo			&GetXYDataInfo() { return m_vXYDataInfo; }

	//inline int			GetCurDataID() { return m_nCurDataID; }
	//inline void			SetCurDataID( int id ) { m_nCurDataID = id; }

	inline bool			IsMultiSelect(){return m_bMultiSelect;}
	inline void			SetMultiSelect(bool bSel){m_bMultiSelect=bSel;}
	inline void			SetShowDataSetInfoMode(int mode){m_nShowDataSetInfoMode=mode;}
	inline int			GetShowDataSetInfoMode(){return m_nShowDataSetInfoMode;}
	inline void			SetShowDataSetInfoNum(int num){m_nShowDataSetInfoNum=num;}
	inline int			GetShowDataSetInfoNum(){return m_nShowDataSetInfoNum;}
	inline void			SetShowDataSetInfoDataPointStep(int step){m_nShowDataSetInfoDataPointStep=step;}
	inline int			GetShowDataSetInfoDataPointStep(){return m_nShowDataSetInfoDataPointStep;}
	inline bool			IsKeepFormer() { return m_bKeepFormer;}
	inline void			SetKeepFormer( bool keep ) { m_bKeepFormer=keep; }

	inline bool			IsAutoLineStyle(){return m_bAutoLineStyle;}
	inline void			SetAutoLineStyle(bool bAuto){m_bAutoLineStyle=bAuto;}
	inline bool			IsAutoDataColor(){return m_bAutoDataColor;}
	inline void			SetAutoDataColor(bool bAuto){m_bAutoDataColor=bAuto;}
	inline int			GetModeOfSetColors(){return m_nModeOfSetColors;}
	inline void			SetModeOfSetColors(int mode){m_nModeOfSetColors=mode;};
	inline COLORREF		GetLineColor1(){return m_crLineColor1;}
	inline void			SetLineColor1(COLORREF color){m_crLineColor1=color;}
	inline COLORREF		GetLineColor2(){return m_crLineColor2;}
	inline void			SetLineColor2(COLORREF color){m_crLineColor2=color;}

public:
	inline void			SetDataColor( int dataID, COLORREF color ){int i = GetIndex(dataID); if( i < 0 ) return; else m_vXYDataInfo[i].crDataColor=color;}
	inline COLORREF		GetDataColor( int dataID ) { int i = GetIndex(dataID); if( i < 0 ) return RGB( 0, 0, 0); else return m_vXYDataInfo[i].crDataColor; }
	inline void			SetPlotColor( int dataID, COLORREF color ){int i = GetIndex(dataID); if( i < 0 ) return; else m_vXYDataInfo[i].crPlotColor=color;}
	inline COLORREF		GetPlotColor( int dataID ) { int i = GetIndex(dataID); if( i < 0 ) return RGB( 0, 0, 0); else return m_vXYDataInfo[i].crPlotColor; }
	inline void			SetAutoColor( int dataID, bool bAuto){int i = GetIndex(dataID); if( i < 0 ) return; else m_vXYDataInfo[i].bAutoColor=bAuto;}
	inline bool			IsAutoColor( int dataID ) {int i = GetIndex(dataID); if( i < 0 ) return false; else return m_vXYDataInfo[i].bAutoColor;}
	inline void			SetMarkerType( int dataID, int type ){int index = GetIndex( dataID );if( index < 0 ) return;m_vXYDataInfo[index].nMarkerType = type;}
	inline int			GetMarkerType( int dataID ) { int i = GetIndex(dataID); if( i < 0 ) return -1; else return m_vXYDataInfo[i].nMarkerType; }
	inline void			SetMarkerSize( int dataID, int size ){int index = GetIndex( dataID );if( index < 0 ) return;m_vXYDataInfo[index].nMarkerSize = size;}
	inline int			GetMarkerSize( int dataID )  { int i = GetIndex(dataID); if( i < 0 ) return -1; else return m_vXYDataInfo[i].nMarkerSize; }
	inline void			SetMarkerFillState( int dataID, bool how ){	int	index = GetIndex( dataID );	if( index < 0 ) return;	m_vXYDataInfo[index].bMarkerFill = how;}
	inline bool			GetMarkerFillState( int dataID ) { int i = GetIndex(dataID); if( i < 0 ) return false; else return m_vXYDataInfo[i].bMarkerFill; }
   
	inline void			SetPlotType( int dataID, int type ){int index = GetIndex( dataID );if( index < 0 ) return;m_vXYDataInfo[index].nPlotType = type;}
	inline int			GetPlotType( int dataID )   { int i = GetIndex(dataID); if( i < 0 ) return -1; else return m_vXYDataInfo[i].nPlotType; }
	inline void			SetMarkerFrequency( int dataID, int freq ){int index = GetIndex( dataID );if( index < 0 ) return;m_vXYDataInfo[index].nMarkerFrequency = freq;}
	inline int			GetMarkerFrequency( int dataID ) { int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].nMarkerFrequency; }
	inline int			GetDataLineSize( int dataID ) { int i = GetIndex( dataID ); if( i < 0 ) return 1; else return m_vXYDataInfo[i].nDataLineSize; }
	inline void			SetDataLineSize( int dataID, int lineSize ) { int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].nDataLineSize = lineSize; }
	inline int			GetPlotLineSize( int dataID ) { int i = GetIndex( dataID ); if( i < 0 ) return 1; else return m_vXYDataInfo[i].nPlotLineSize; }
	inline void			SetPlotLineSize( int dataID, int lineSize ) { int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].nPlotLineSize = lineSize; }
	inline int			GetDataLineStyle( int dataID ) { int i = GetIndex( dataID ); if( i < 0 ) return 1; else return m_vXYDataInfo[i].nDataLineStyle; }
	inline void			SetDataLineStyle( int dataID, int lineStyle ) { int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].nDataLineStyle = lineStyle; }
	inline int			GetPlotLineStyle( int dataID ) { int i = GetIndex( dataID ); if( i < 0 ) return 1; else return m_vXYDataInfo[i].nPlotLineStyle; }
	inline void			SetPlotLineStyle( int dataID, int lineStyle ) { int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].nPlotLineStyle = lineStyle; }
	inline bool			IsAutoLineStyle( int dataID ) { int i = GetIndex( dataID ); if( i < 0 ) return false; else return m_vXYDataInfo[i].bAutoLineStyle; }
	inline void			SetAutoLineStyle( int dataID, bool bAuto ) { int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].bAutoLineStyle = bAuto; };
	inline bool			IsDataShow( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].bDataShow; }
	inline void			SetDataShow( int dataID, bool bShow ) { int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].bDataShow = bShow; };
	inline bool			IsSelected( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].bSelected; }
	inline void			SetSelected( int dataID, bool bSel ) { int i = GetIndex( dataID ); if( i < 0 ) return; else {if(!m_bMultiSelect && bSel)SelectAllDataSets(false);m_vXYDataInfo[i].bSelected = bSel;} };
	inline bool			IsLighted( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].bLighted; }
	inline void			SetLighted( int dataID, bool bLight ){UnlightAllDataSets();int i = GetIndex( dataID );if( i < 0 ) return;else m_vXYDataInfo[i].bLighted = bLight;}

	inline bool			GetSpecialFlag( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return false; else return m_vXYDataInfo[i].bSpecialFlag; }
	inline void			SetSpecialFlag( int dataID, bool bFlag ) { int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].bSpecialFlag = bFlag; }
	inline bool			GetSpecialFlag(){for(int i=0;i<GetDataSetCount();i++)if(GetSpecialFlag(GetDataID(i)))return true;return false;}
	inline bool			GetSpecialFlagNot(){for(int i=0;i<GetDataSetCount();i++)if(!GetSpecialFlag(GetDataID(i)))return true;return false;}
	inline void			SetSpecialFlag(bool bFlag){for(int i=0;i<GetDataSetCount();i++)SetSpecialFlag(GetDataID(i),bFlag);}
	
	inline int			GetDataFillMode( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].nDataFillMode; }
	inline void			SetDataFillMode( int dataID, int mode ){ int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].nDataFillMode = mode; }
	inline bool			IsDataFill( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].bDataFill; }
	inline void			SetDataFill( int dataID, bool bFill ){ int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].bDataFill = bFill; }
	inline int			GetDataFillBrushType( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].nDataFillBrushType; }
	inline void			SetDataFillBrushType( int dataID, int type ){ int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].nDataFillBrushType = type; }
	inline COLORREF		GetDataFillColor( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return 0; else return m_vXYDataInfo[i].crDataFillColor; }
	inline void			SetDataFillColor( int dataID, COLORREF color ){ int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].crDataFillColor = color; }
	inline int			GetDataFillHatchStyle( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return -1; else return m_vXYDataInfo[i].nDataFillHatchStyle; }
	inline void			SetDataFillHatchStyle( int dataID, int style ){ int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].nDataFillHatchStyle = style; }
	inline HBITMAP		GetDataFillPattern( int dataID ){ int i = GetIndex(dataID); if( i < 0 ) return NULL; else return m_vXYDataInfo[i].hDataFillPattern; }
	inline void			SetDataFillPattern( int dataID, HBITMAP pattern ){ int i = GetIndex( dataID ); if( i < 0 ) return; else m_vXYDataInfo[i].hDataFillPattern = pattern; }

	inline	SIZE		GetPieTitleOffset(int which){ if(which >=0 && which < GetDataSetCount() )return m_vXYDataInfo[which].sizeTitleOffset; else {SIZE size = {0,0}; return size;} }
	inline	void		SetPieTitleOffset(int which, SIZE offset){ if(which >=0 && which < GetDataSetCount() )m_vXYDataInfo[which].sizeTitleOffset = offset; else return; }
	inline	double		GetPieScale(int which){ if(which >=0 && which < GetDataSetCount() )return m_vXYDataInfo[which].fScale; else return 0; }
	inline	void		SetPieScale(int which, double scale){ if(which >=0 && which < GetDataSetCount() ){ if(scale < 0.0 || scale >1.0)scale = 1.0; m_vXYDataInfo[which].fScale = scale;} else return; }

	inline	bool		DelDataSetSel(){for(int i=0;i<GetDataSetCount();i++){if(m_vXYDataInfo[i].bSelected)if(!DeleteData(GetDataID(i)))return false;}return true;}
	inline	bool		HideDataSetSel(){for(int i=0;i<GetDataSetCount();i++)if(IsSelected(GetDataID(i)))SetDataShow(GetDataID(i),false);return true;}
	inline	void		SelectAllDataSets(bool bSel){for(int i=0;i<GetDataSetCount();i++)m_vXYDataInfo[i].bSelected=bSel;}
	inline	bool		IsSelected(){for(int i=0;i<GetDataSetCount();i++)if(m_vXYDataInfo[i].bSelected)return true;return false;}
	inline	bool		IsLighted(){for(int i=0;i<GetDataSetCount();i++)if(m_vXYDataInfo[i].bLighted)return true;return false;}
	inline	void		UnlightAllDataSets(){for(int i=0;i<GetDataSetCount();i++)m_vXYDataInfo[i].bLighted=false;}
	inline	int			GetIDofLighted(){for(int i=0;i<GetDataSetCount();i++)if(m_vXYDataInfo[i].bLighted)return GetDataID(i);return -1;}
	inline	bool		IsAnyHiden(){for(int i=0;i<GetDataSetCount();i++)if(!m_vXYDataInfo[i].bDataShow)return true;return false;}
	inline	void		ShowAllDataSets(){for(int i=0;i<GetDataSetCount();i++)SetDataShow(GetDataID(i),true);}
	
	virtual inline int	GetDataSetCount( void ) const{ return m_vXYDataInfo.size(); }// virtual for LayeredLegend
	virtual inline int	GetDataSetLevels() const {return GetDataSetCount();}

public:
	string				GetDataTitle( int dataID );
	void				SetDataTitle( int dataID, string title );

	int					GetDataID( int index) const
	{
		if(index<0 || index>=GetDataSetCount())return -1;
		else return m_vXYDataInfo[index].nDataID;
	};
	int					GetIndex( int dataID ) const;

	virtual CPlotData<DataPoint2D>	*GetAbsoluteDataSet( int which );// virtual for LayeredLegend
	virtual string					GetAbsoluteDataTitle( int which );
	CPlotData<DataPoint2D>			*GetDataSet( int dataID );

	const MyVData2D		&GetData( int dataID ) const;
	const MyVData2D		&GetAbsoluteData( int which ) const;

	void				GetDataRange( int dataID );
	void				GetDataRanges();
	void				GetDataRanges(double xRange[2], double yRange[2]);

public:
	bool				WriteToFile( string pathName );
	bool				WriteToFile( int which, string pathName );
	bool				ReadFromFile( string pathName );
	bool				ReadFromFile( int which, string pathName );

protected:
	void				SetPlotColors();
	void				SetPlotLineStyles();
	void				SetPlotLineSizes();

	int					GetLineWidth(int linewidth, bool bLighted, bool bSelected);
	COLORREF			GetLineColor(COLORREF linecolor, bool bLighted, bool bSelected);

private:
	int					AddData( MyVData2D vData );
	int					SetData( int dataID, MyVData2D vData );
};

#endif