#ifndef __MAPX_H__
#define __MAPX_H__

#ifdef UNDER_CE
#define HELP_FINDER       0x000b
#endif

#pragma warning( disable: 4100)

// event dispids
#define MAPX_DISPID_SELECTION_CHANGED 0x1
#define MAPX_DISPID_RESOLVEDATABIND 0x2
#define MAPX_DISPID_TOOLUSED 0x3
#define MAPX_DISPID_REQUESTDATA 0x4
#define MAPX_DISPID_DATAMISMATCH 0x5
#define MAPX_DISPID_MAPVIEWCHANGED 0x6
#define MAPX_DISPID_ANNOTATIONADDED 0x7
#define MAPX_DISPID_ANNOTATIONCHANGED 0x8
#define MAPX_DISPID_THEMEMODIFYREQUESTED 0x9
#define MAPX_DISPID_DRAWUSERLAYER 0x0a
#define MAPX_DISPID_POLYTOOLUSED 0x0b
#define MAPX_DISPID_MOUSEWHEEL 0x0c
#define MAPX_DISPID_MAPINITIALIZED 0x0d
#define MAPX_DISPID_RESOLVEDATABINDEX 0xe
#define MAPX_DISPID_MAPDRAW 0xf
#define MAPX_DISPID_ADDFEATURETOOLUSED 0x10
#define MAPX_DISPID_LABELCHANGED			 0x11

// dispatch id definitions for ole stock events are
// defined in <olectl.h>
// they are included here for reference
//#define DISPID_CLICK                    (-600)
//#define DISPID_DBLCLICK                 (-601)
//#define DISPID_KEYDOWN                  (-602)
//#define DISPID_KEYPRESS                 (-603)
//#define DISPID_KEYUP                    (-604)
//#define DISPID_MOUSEDOWN                (-605)
//#define DISPID_MOUSEMOVE                (-606)
//#define DISPID_MOUSEUP                  (-607)
//#define DISPID_ERROREVENT               (-608)



// enum definitions to match typelib

enum ToolConstants
{
	miArrowTool = 1000,
	miPanTool = 1001,
	miCenterTool = 1002,
	miZoomInTool = 1003,
	miZoomOutTool = 1004,
	miSymbolTool = 1005,
	miTextTool = 1006,
	miSelectTool = 1007,
	miRadiusSelectTool = 1008,
	miRectSelectTool = 1009,
	miPolygonSelectTool = 1010,
	miLabelTool = 1011,
	miAddLineTool = 1012,
	miAddPolylineTool = 1013,
	miAddRegionTool = 1014,
	miAddPointTool = 1015
};

/* Synchronize this with mimoapp.odl! */
enum CursorConstants
{
	miDefaultCursor = 0,
	miArrowCursor = 1,
	miCrossCursor = 2,
	miIBeamCursor = 3,
	miIconCursor = 4,
	miSizeCursor = 5,
	miSizeNESWCursor = 6,
	miSizeNSCursor = 7,
	miSizeNWSECursor = 8,
	miSizeEWCursor = 9,
	miUpArrowCursor = 10,
	miHourglassCursor = 11,
	miNoDropCursor = 12,
	miArrowHourglassCursor = 13,
	miArrowQuestionCursor = 14,
	miSizeAllCursor = 15,
	miArrowToolCursor = 16,
	miPanCursor = 17,
	miCenterCursor = 18,
	miZoomInCursor = 19,
	miZoomOutCursor = 20,
	miSymbolCursor = 21,
	miTextCursor = 22,
	miSelectCursor = 23,
	miRadiusSelectCursor = 24,
	miRectSelectCursor = 25,
	miRegionSelectCursor = 26,
	miInfoCursor = 27,
	miSelectPlusCursor = 28,
	miSelectRadiusPlusCursor = 29,
	miSelectRectPlusCursor = 30,
	miSelectRegionPlusCursor = 31,
	miSelectMinusCursor = 32,
	miSelectRadiusMinusCursor = 33,
	miSelectRectMinusCursor = 34,
	miSelectRegionMinusCursor = 35,
	miLabelCursor = 36,
	miDrilldownExpandCursor = 37,
	miDrilldownContractCursor = 38,
	miInfoCursorOld = 39,
	miCustomCursor = 40
};


enum MapUnitConstants
{
	miUnitMile = 0,
	miUnitKilometer = 1,
	miUnitInch = 2,
	miUnitFoot = 3,
	miUnitYard = 4,
	miUnitMillimeter = 5,
	miUnitCentimeter = 6,
	miUnitMeter = 7,
	miUnitSurveyFoot = 8,
	miUnitNauticalMile = 9,
	miUnitTwip = 10,
	miUnitPoint = 11,
	miUnitPica = 12,
	miUnitDegree = 13,
	miUnitLink = 30,
	miUnitChain = 31,
	miUnitRod = 32
};

enum PaperUnitConstants
{
	miPaperUnitMile = 0,
	miPaperUnitKilometer = 1,
	miPaperUnitInch = 2,
	miPaperUnitFoot = 3,
	miPaperUnitYard = 4,
	miPaperUnitMillimeter = 5,
	miPaperUnitCentimeter = 6,
	miPaperUnitMeter = 7,
	miPaperUnitSurveyFoot = 8,
	miPaperUnitNauticalMile = 9,
	miPaperUnitTwip = 10,
	miPaperUnitPoint = 11,
	miPaperUnitPica = 12,
	miPaperUnitDegree = 13,
	miPaperUnitLink = 30,
	miPaperUnitChain = 31,
	miPaperUnitRod = 32
};

enum SelectionTypeConstants
{
	miSelectionNew = 0,
	miSelectionAppend = 1,
	miSelectionRemove = 2
};

enum ConversionConstants
{
	miMapToScreen = 0,
	miScreenToMap = 1
};

enum DotSizeConstants
{
	miDotSizeSmall = 0,
	miDotSizeLarge = 1
};

enum DistribMethodConstants
{
	miCustomRanges = 0,
	miEqualCountPerRange = 1,
	miEqualRangeSize = 2,
	miNaturalBreak = 3,
	miStandardDeviation = 4
};

enum PenStyleConstants
{
	miPenNone = 0,
	miPenSolid = 1
};

enum FieldTypeConstants
{
	miTypeString = 0,
	miTypeNumeric = 1,
	miTypeDate = 2,
	miTypeInteger = 3,
	miTypeSmallInt = 4,
	miTypeFloat = 5,
	miTypeLogical = 6
};

enum AggregationFunctionConstants
{
	miAggregationSum = 0,
	miAggregationAverage = 1,
	miAggregationCount = 2,
	miAggregationIndividual = 4,
	miAggregationAuto = 5
};

enum FillPatternConstants
{
	miPatternNoFill = 0,
	miPatternHollow = 1,
	miPatternSolid = 2,
	miPatternHorizontal = 3,
	miPatternVertical = 4,
	miPatternFDiag = 5,
	miPatternFilBDiag = 6,
	miPatternCross = 7,
	miPatternDiagCross = 8
};

enum ThemeTypeConstants
{
	miThemeRanged = 0,
	miThemeBarChart = 1,
	miThemePieChart = 2,
	miThemeGradSymbol = 3,
	miThemeDotDensity = 4,
	miThemeIndividualValue = 5,
	miThemeAuto = 6,
	miThemeLabelRanged = 7,
	miThemeLabelIndividualValue = 8,
	miThemeNone = 9,
};

enum AnnotationTypeConstants
{
	miSymbolAnnotation = 1,
	miTextAnnotation = 6,
};

enum ToolTypeConstants
{
	miToolTypePoint = 0,
	miToolTypeLine = 1,
	miToolTypeCircle = 2,
	miToolTypeMarquee = 3,
	miToolTypePoly = 4,
	miToolTypePolygon = 5
};

enum PolyToolFlagConstants
{
	miPolyToolBegin = 0,
	miPolyToolEnd = 1,
	miPolyToolEndEscaped = 2,
	miPolyToolInProgress = 3
};

enum DatasetTypeConstants
{
	miDataSetDAO = 1,
	miDataSetODBC = 2,
	miDataSetUnbound = 3,
	miDataSetGlobalHandle = 4,
	miDataSetOLEData = 5,
	miDataSetLayer = 6,
	miDataSetNotesView = 7,
	miDataSetNotesQuery = 8,
	miDataSetSafeArray = 9,
	//miDataSetOEO = 10,
	miDataSetDelphi = 1010,
	miDataSetDelphi4 = 1011,
	miDataSetDelphi5 = 1012,
	miDataSetDelphi6 = 1013,
	miDataSetADO = 12,
	miDataSetRDO = 13,
	miDataSetXML = 14,
	miDataSetOCI = 15
};

enum AnnotationChangedTypeConstants
{
	miAddAnnotation = 0,
	miDeleteAnnotation = 1,
	miSelectAnnotation = 2,
	miEditAnnotation = 3
};

enum ResolveDataBindConstants
{
	miChooseField = 0,
	miChooseLayer = 1,
	miChooseGeoSet = 2
};

enum SpreadByConstants
{
	miSpreadByNone = 0,
	miSpreadByColor = 1,
	miSpreadBySize = 2
};

enum BindLayerTypeConstants
{
	miBindLayerTypeNormal = 0,
	miBindLayerTypeXY = 1,
	miBindLayerTypePointRef = 2
};

enum ExportFormatConstants
{
	miFormatWMF = 0,
	miFormatBMP = 1,
	miFormatGIF = 2,
	miFormatJPEG = 3,
	miFormatTIF = 4,
	miFormatPNG = 5,
	miFormatPSD = 6
};

enum FeatureTypeConstants
{
	miFeatureTypeRegion = 0,
	miFeatureTypeLine = 1,
	miFeatureTypeSymbol = 2,
	miFeatureTypeMixed = 3,
	miFeatureTypeUnknown = 4,
	miFeatureTypeText = 5,
	miFeatureTypeNull = 6,
	miFeatureTypeMultipoint = 7,
	miFeatureTypeCollection = 8
};

enum LineTypeConstants
{
	miLineTypeNone = 0,
	miLineTypeSimple = 1,
	miLineTypeArrow = 2
};

enum PositionConstants
{
	miPositionCC = 0,
	miPositionTL = 1,
	miPositionTC = 2,
	miPositionTR = 3,
	miPositionCL = 4,
	miPositionCR = 5,
	miPositionBL = 6,
	miPositionBC = 7,
	miPositionBR = 8
};

enum SearchTypeConstants
{
	miSearchTypeCentroidWithin = 0,
	miSearchTypePartiallyWithin = 1,
	miSearchTypeEntirelyWithin = 2
};

enum LayerTypeConstants
{
	miLayerTypeNormal = 0,
	miLayerTypeRaster = 2,
	miLayerTypeSeamless = 4,
	miLayerTypeUnknown = 5,
	miLayerTypeUserDraw = 6,
	miLayerTypeDrilldown = 7,
};

enum AreaUnitConstants
{
	miUnitSquareMile = 14,
	miUnitSquareKilometer = 15,
	miUnitSquareInch = 16,
	miUnitSquareFoot = 17,
	miUnitSquareYard = 18,
	miUnitSquareMillimeter = 19,
	miUnitSquareCentimeter = 20,
	miUnitSquareMeter = 21,
	miUnitSquareSurveyFoot = 22,
	miUnitSquareNauticalMile = 23,
	miUnitSquareTwip = 24,
	miUnitSquarePoint = 25,
	miUnitSquarePica = 26,
	miUnitSquareDegree = 27,
	miUnitAcre = 28,
	miUnitHectare = 29,
	miUnitSquareLink = 33,
	miUnitSquareChain = 34,
	miUnitSquareRod = 35,
	miUnitPerch = 36,
	miUnitRood = 37
};

enum CircleTypeConstants
{
	miCircleTypeScreen= 0,
	miCircleTypeMap = 1,
};

enum CoordSysTypeConstants
{
	miNonEarth = 0,
	miLongLat = 1,
	miCylindricalEqualArea = 2,
	miLambertConformalConic = 3,
	miLambertAzimuthalEqualArea = 4,
	miAzimuthalEquidistant = 5,
	miEquidistantConic = 6,
	miHotineObliqueMercator = 7,
	miTransverseMercator = 8,
	miAlbersEqualAreaConic = 9,
	miMercator = 10,
	miMillerCylindrical = 11,
	miRobinson = 12,
	miMollweide = 13,
	miEckertIV = 14,
	miEckertVI = 15,
	miSinusoidal = 16,
	miGall = 17,
	miNewZealandMapGrid = 18,
	miLambertConformalConicBelgium = 19,
	miStereographic = 20,
	miTransverseMercatorDenmarkS34J = 21,
	miTransverseMercatorDenmarkS34S = 22,
	miTransverseMercatorDenmarkS45B = 23,
	miTransverseMercatorFinland = 24,
	miSwissObliqueMercator = 25,
	miMercatorStdParallel = 26,
	miPolyconic = 27,
	miAzimuthalEquidistantOblique = 28,
	miLambertAzimuthalEqualAreaOblique = 29,
	miCassiniSoldner = 30,
	miDblStereographic = 31
};

enum SymbolTypeConstants
{
	miSymbolTypeTrueTypeFont = 0,
	miSymbolTypeBitmap = 1,
	miSymbolTypeVector = 2
};

enum ColorConstants
{
	miColorBlack = 0,
	miColorRed = 255,
	miColorGreen = 65280,
	miColorBlue = 16711680,
	miColorMagenta = 16711935,
	miColorCyan = 16776960,
	miColorWhite = 16777215,
	miColorLightGray = 12632256,
	miColorDarkGray = 4210752,
	miColorGray = 8421504,
	miColorPaleYellow = 13697023,
	miColorLightYellow = 8454143,
	miColorYellow = 65535,
	miColorLimeGreen = 12639424,
	miColorTeal = 8421440,
	miColorDarkGreen = 16384,
	miColorMaroon = 128,
	miColorPurple = 8388736,
	miColorOrange = 33023,
	miColorKhaki = 7051175,
	miColorOlive = 32896,
	miColorBrown = 4210816,
	miColorNavy = 8404992,
	miColorScrollBars = 0x80000000,
	miColorDesktop = 0x80000001,
	miColorActiveTitleBar = 0x80000002,
	miColorInactiveTitleBar = 0x80000003,
	miColorMenuBar = 0x80000004,
	miColorWindowBackground = 0x80000005,
	miColorWindowFrame = 0x80000006,
	miColorMenuText = 0x80000007,
	miColorWindowText = 0x80000008,
	miColorTitleBarText = 0x80000009,
	miColorActiveBorder = 0x8000000A,
	miColorInactiveBorder = 0x8000000B,
	miColorApplicationWorkspace = 0x8000000C,
	miColorHighlight = 0x8000000D,
	miColorHighlightText = 0x8000000E,
	miColorButtonFace = 0x8000000F,
	miColorButtonShadow = 0x80000010,
	miColorGrayText = 0x80000011,
	miColorButtonText = 0x80000012,
	miColorInactiveCaptionText = 0x80000013,
	miColor3DHighlight = 0x80000014,
	miColor3DDarkShadow = 0x80000015,
	miColor3DLight = 0x80000016,
	miColorInfoText = 0x80000017,
	miColorInfoBackground = 0x80000018,
};

enum IntersectionTestConstants
{
	miIntersectCentroidWithinFeature = 0,
	miIntersectFeature = 1,
	miIntersectEntirelyWithinFeature = 2
};

enum IntersectionPointConstants
{
	miIntersectCrossings = 9,
	miIntersectCommon = 10,
	miIntersectAll = 11
};

enum MousewheelSupportConstants
{
	miNoMousewheelSupport = 1,
	miMousewheelNoAutoScroll = 2,
	miFullMousewheelSupport = 3	
};

enum StyleUnitConstants
{
	miStyleUnitPixel = 0,
	miStyleUnitTenthsOfPoint = 1
};

enum ServerLayerOptions // bit mask for long, must be power of 2
{
	miLayerCacheOn = 0,			// default = Cache on
	miLayerMBRSearchOn = 0,	// default = Search on
	miLayerCacheOff = 1,
	miMBRSearchOff  = 2
};

enum LayerBeginAccessConstants
{
	miAccessRead= 0,
	miAccessReadWrite = 1,
};

enum LayerEndAccessConstants
{
	miAccessEnd= 0,
};

enum LayerPackConstant
{
	miPackGraphics= 0x1,
	miRebuildGraphics= 0x2,
	miPackIndex= 0x4,
	miRebuildIndex= 0x8,
	miPackData= 0x10,
	miPackCompactDB= 0x20,
	miPackAll= 0x15,
};

enum GraduationConstants
{
	miGraduateBySquareRoot = 0,
	miGraduateByConstant = 1,
	miGraduateByLogarithm = 2
};

enum LayerInfoTypeConstants
{
	miLayerInfoTypeTab = 0,
	miLayerInfoTypeUserDraw = 1,
	miLayerInfoTypeRaster = 2,
	miLayerInfoTypeShape = 3,
	miLayerInfoTypeServer = 4,
	miLayerInfoTypeGeodictUserName = 5,
	miLayerInfoTypeTemp = 6,
	miLayerInfoTypeNewTable = 7
};

enum MapDrawConstants
{
	miDrawBegin = 1,
	miDrawEnd = 2
};

enum ColorSpreadingMethodConstants
{
	miColorMethodRGB = 0,
	miColorMethodHSV = 1
};

enum ApplyAttributeConstants
{
	miApplyAttributeAll = 0,
	miApplyAttributeColor = 1,
	miApplyAttributeSize = 2
};

enum ToolFlagConstants
{
	miToolBegin = 0,
	miToolEnd = 1,
	miToolEndEscaped = 2,
	miToolInProgress = 3,
	miToolCompleted = 4
};

enum FeatureEditModeConstants
{
	miEditModeFeature = 1,
	miEditModeNode = 2,
	miMoveDuplicateNodes = 4,
	miDeleteDuplicateNodes = 8,
	miEditModeAddNode = 64
};

enum SearchResultTypeConstants
{
	miSearchResultAll		= 0x0000,
	miSearchResultTopmost	= 0x0001,
	miSearchResultRegion	= 0x0002,
	miSearchResultPoint		= 0x0004,
	miSearchResultLine		= 0x0008,
	miSearchResultText		= 0x0010,
	miSearchResultMultipoint= 0x0020,
	miSearchResultCollection= 0x0040
};

enum LabelAlongConstants
{
	miLabelAlongNone = 0,
	miLabelAlongParallel = 1,
	miLabelAlongMultiSegment = 2
};

enum LabelChangedTypeConstants
{
	miLabelMove = 0,
	miLabelAdd = 1,
	miLabelSelectionChange = 2
};

// forward delcarations
class CMapXAllFeaturesConstraint;
class CMapXAnnotation;
class CMapXAnnotations;
class CMapXBitmapSymbol;
class CMapXBitmapSymbols;
class CMapXBoundsConstraint;
class CMapXCoordSys;
class CMapXDataset;
class CMapXDatasets;
class CMapXFeature;
class CMapXFeatureFactory;
class CMapXFeatures;
class CMapXFeaturesConstraint;
class CMapXField;
class CMapXFields;
class CMapXFindFeature;
class CMapXFindMatch;
class CMapXFindMatches;
class CMapXFindResult;
class CMapXGeoset;
class CMapXGeosets;
class CMapXGraphic;
class CMapXIndividualValueCategories;
class CMapXIndividualValueCategory;
class CMapXLabel;
class CMapXLabels;
class CMapXLabelProperties;
class CMapXLayer;
class CMapXLayerFind;
class CMapXLayerInfo;
class CMapXLayers;
class CMapXLegend;
class CMapXLegendText;
class CMapXLegendTexts;
class CMapXMultivarCategories;
class CMapXMultivarCategory;
class CMapXParts;
class CMapXPoint;
class CMapXPoints;
class CMapXRangeCategories;
class CMapXRangeCategory;
class CMapXRectangle;
class CMapXResolveObject;
class CMapXResolveObjects;
class CMapXRowValue;
class CMapXRowValues;
class CMapXSelection;
class CMapXSourceRow;
class CMapXSourceRows;
class CMapXStyle;
class CMapXTheme;
class CMapXThemeProperties;
class CMapXThemes;
class CMapXTitle;
class CMapXVariable;
class CMapXVariables;
class COptionalVariant;

CLSID GetClassID(LPCTSTR pszProgramID);

// simple class to pass to methods that take
// a variant that we want to mark as optional (not supplied by the method call)
class COptionalVariant: public COleVariant
{
public:
	COptionalVariant() { vt = VT_ERROR; scode = DISP_E_PARAMNOTFOUND; }
};

// another helper class to handle dispatch variants
class COleVariantDispatch: public COleVariant
{
public:
	COleVariantDispatch(LPDISPATCH pdisp)
	{
    vt = VT_DISPATCH;
    pdispVal = pdisp;
		pdispVal->AddRef();
	}
};

// This is the MapX major version being used:
#define MAPX_VERSION _T("5")

// MapX program IDs' prefix:
#if defined(MAPX_MOBILE) || defined(UNDER_CE)
#define MAPX_PROGRAM_ID_PREFIX _T("MapXMobile")
#else
#define MAPX_PROGRAM_ID_PREFIX _T("MapX")
#endif

// to derive CMapX from COleDispatchDriver instead of CWnd,
// comment out the next line
#define CWND_MAPX


/////////////////////////////////////////////////////////////////////////////
// CMapX wrapper class
#ifdef CWND_MAPX

//----------------------------
class CMapX : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMapX)
public:
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

#else

class CMapX : public COleDispatchDriver
{
#endif //of #ifdef CWND_MAPX
public:
	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Map.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

	// default bAddRef is false because you don't need to addref
	// when passing result to Feature.Attach();
	LPDISPATCH GetDispatch(BOOL bAddRef=FALSE);

// Attributes
public:
	CString GetDataSetGeoField();
	void SetDataSetGeoField(LPCTSTR);
	CString GetVersion();
	OLE_HANDLE GetHWnd();
	CMapXAnnotations GetAnnotations();
	CMapXLayers GetLayers();
	BOOL GetAutoRedraw();
	void SetAutoRedraw(BOOL);
	double GetZoom();
	void SetZoom(double);
	double GetCenterX();
	void SetCenterX(double);
	double GetCenterY();
	void SetCenterY(double);
	CString GetGeoSet();
	void SetGeoSet(LPCTSTR);
	double GetGeoSetWidth();
	double GetMapPaperHeight();
	double GetMapPaperWidth();
	short GetMaxSearchTime();
	void SetMaxSearchTime(short);
	long GetPaperUnit();
	void SetPaperUnit(long);
	BOOL GetPreferCompactLegends();
	void SetPreferCompactLegends(BOOL);
	CMapXStyle GetDefaultStyle();
	void SetDefaultStyle(LPDISPATCH);
	CString GetGeoDictionary();
	// this method currently will not work in 'run' mode. which
	// is the only mode MFC Control containers support, so don't bother calling it.
	void SetGeoDictionary(LPCTSTR);

	long GetDataSetTheme();
	void SetDataSetTheme(long);
	long GetCurrentTool();
	void SetCurrentTool(long);
	long GetMousePointer();
	void SetMousePointer(long);
	CMapXDatasets GetDatasets();
	CMapXTitle GetTitle();
	CString GetTitleText();
	void SetTitleText(LPCTSTR);
	long GetMapUnit();
	void SetMapUnit(long);
	double GetRotation();
	void SetRotation(double);
	CMapXGeosets GetGeosets();
	long GetAreaUnit();
	void SetAreaUnit(long);
	CMapXRectangle GetBounds();
	void SetBounds(LPDISPATCH);
	CMapXCoordSys GetDisplayCoordSys();
	void SetDisplayCoordSys(LPDISPATCH);
	CMapXCoordSys GetNumericCoordSys();
	void SetNumericCoordSys(LPDISPATCH);
	BOOL GetExportSelection();
	void SetExportSelection(BOOL);
	CMapXStyle GetSelectionStyle();
	void SetSelectionStyle(LPDISPATCH);
	CMapXFeatureFactory GetFeatureFactory();
	long GetDefaultConversionResolution();
	void SetDefaultConversionResolution(long);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	long GetMousewheelSupport();
	void SetMousewheelSupport(long);
	BOOL GetMatchNumericFields();
	void SetMatchNumericFields(BOOL);
	double GetMapScreenWidth();
	double GetMapScreenHeight();
	long GetRedrawInterval();
	void SetRedrawInterval(long l);
	CString GetSearchPath();
	void SetSearchPath(LPCTSTR propVal);
	short GetMatchThreshold();
	void SetMatchThreshold(short l);
	BOOL GetWaitCursorEnabled();
	void SetWaitCursorEnabled(BOOL b);
	BOOL GetPanAnimationLayer();
	void SetPanAnimationLayer(BOOL b);
	long GetInfotipPopupDelay();
	void SetInfotipPopupDelay(long propVal);
	CString GetMouseIcon();
	void SetMouseIcon(LPCTSTR propVal);
	BOOL GetInfotipSupport();
	void SetInfotipSupport(BOOL b);
	short GetFeatureEditMode();
	void SetFeatureEditMode(short);
	long GetCheckEscapeKeyInterval();
	void SetCheckEscapeKeyInterval(long);
	BOOL GetReuseEquivalentOnRestore();
	void SetReuseEquivalentOnRestore(BOOL b);
	BOOL GetSnapToNodeSupport();
	void SetSnapToNodeSupport(BOOL b);
	short GetSnapTolerance();
	void SetSnapTolerance(short);
	BOOL GetDynamicSelectionSupport();
	void SetDynamicSelectionSupport(BOOL b);
	BOOL GetLabelsAreEditable();
	void SetLabelsAreEditable(BOOL b);


// Operations
public:
	void ConvertCoord(float* ScreenX, float* ScreenY, double* MapX, double* MapY, short Direction);
	void ZoomTo(double Zoom, double X, double Y);
	
	void CreateCustomTool(short ToolNumber, short Type, const VARIANT& Cursor, const VARIANT& ShiftCursor, const VARIANT& CtrlCursor, const VARIANT& bInfoTips);
	void CreateCustomTool(short ToolNumber, short Type, short Cursor)
	{ CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COptionalVariant(), COptionalVariant(), COptionalVariant()); }
	void CreateCustomTool(short ToolNumber, short Type, LPCTSTR Cursor)
	{ CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COptionalVariant(), COptionalVariant(), COptionalVariant()); }
	void CreateCustomTool(short ToolNumber, short Type, short Cursor, bool bInfoTips)
	{
		short sInfoTips = (short) bInfoTips;
		CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COptionalVariant(), COptionalVariant(), COleVariant(sInfoTips));
	}
	void CreateCustomTool(short ToolNumber, short Type, LPCTSTR Cursor, bool bInfoTips)
	{
		short sInfoTips = (short) bInfoTips;
		CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COptionalVariant(), COptionalVariant(), COleVariant(sInfoTips));
	}
	void CreateCustomTool(short ToolNumber, short Type, short Cursor, short ShiftCursor, short CtrlCursor)
	{ CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COleVariant(ShiftCursor), COleVariant(CtrlCursor), COptionalVariant()); }
	void CreateCustomTool(short ToolNumber, short Type, LPCTSTR Cursor, LPCTSTR ShiftCursor, LPCTSTR CtrlCursor)
	{ CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COleVariant(ShiftCursor), COleVariant(CtrlCursor), COptionalVariant()); }
	void CreateCustomTool(short ToolNumber, short Type, short Cursor, short ShiftCursor, short CtrlCursor, bool bInfoTips)
	{
		short sInfoTips = (short) bInfoTips;
		CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COleVariant(ShiftCursor), COleVariant(CtrlCursor), COleVariant(sInfoTips));
	}
	void CreateCustomTool(short ToolNumber, short Type, LPCTSTR Cursor, LPCTSTR ShiftCursor, LPCTSTR CtrlCursor, bool bInfoTips)
	{
		short sInfoTips = (short) bInfoTips;
		CreateCustomTool(ToolNumber, Type, COleVariant(Cursor), COleVariant(ShiftCursor), COleVariant(CtrlCursor), COleVariant(sInfoTips));
	}

	double Distance(double X1, double Y1, double X2, double Y2);
	void Refresh();
	void PrintMap(long hDC, long X, long Y, long W, long H);

	void ExportMap(LPCTSTR Destination, short Format, const VARIANT& Width, const VARIANT& Height);
	void ExportMap(LPCTSTR Destination, short Format)
		{	ExportMap(Destination, Format, COptionalVariant(), COptionalVariant()); }
	void ExportMap(LPCTSTR Destination, short Format, double Width, double Height)
		{	ExportMap(Destination, Format, COleVariant(Width), COleVariant(Height)); }
	
	void PropertyPage();
	void ConvertCoordV(VARIANT* ScreenX, VARIANT* ScreenY, VARIANT* MapX, VARIANT* MapY, short Direction);
	void SetSize(long Width, long Height);
	BOOL IsPointVisible(double X, double Y);
	BOOL ClipLine(double* X1, double* Y1, double* X2, double* Y2);
	BOOL ClipLineV(VARIANT* X1, VARIANT* Y1, VARIANT* X2, VARIANT* Y2);
	void SaveMapAsGeoset(LPCTSTR Name, LPCTSTR Filespec);
	void Pan(float ScreenX, float ScreenY);
	void AboutBox();
	CString MilitaryGridReferenceFromPoint(const VARIANT& X, const VARIANT& Y);
	BOOL MilitaryGridReferenceToPoint(LPCTSTR strMilGridRef, double* X, double* Y);
	BOOL MilitaryGridReferenceToPointV(LPCTSTR strMilGridRef, VARIANT* X, VARIANT* Y);
};

// EVENT Prototypes
// For dispatch objects passed to events, the event handler should not change the reference count
// ie: do not call release on the object because an ocx does not do an addref before passing the
// object to the event
/*
	void Click();
	void DblClick();
	void Error(short Number, BSTR* Description, long Scode, LPCTSTR Source, LPCTSTR HelpFile, long HelpContext, BOOL* CancelDisplay);
	void KeyDown(short* KeyCode, short Shift);
	void KeyPress(short* KeyAscii);
	void KeyUp(short* KeyCode, short Shift);
	void MouseMove(short Button, short Shift, float X, float Y);
	void MouseDown(short Button, short Shift, float X, float Y);
	void MouseUp(short Button, short Shift, float X, float Y);
	void SelectionChanged();
	void ResolveDataBind(short Flag, short NumMatches, const VARIANT& Matches, short* Choice, BOOL* Cancel);
	void ToolUsed(short ToolNum, double X1, double Y1, double X2, double Y2, double Distance, BOOL Shift, BOOL Ctrl, BOOL* EnableDefault);
	void RequestData(LPCTSTR DataSetName, long Row, short Field, VARIANT* Value, BOOL* Done);
	void DataMismatch(LPCTSTR DataSetName, long Row, BSTR* GeoFieldValue);
	void MapViewChanged();
	void AnnotationAdded(LPDISPATCH Annotation);
	void AnnotationChanged(short ChangeType, LPDISPATCH Annotation, BOOL* EnableDefault);
	void ThemeModifyRequested(LPDISPATCH Theme);
	void DrawUserLayer(LPDISPATCH Layer, long hOutputDC, long hAttributeDC, LPDISPATCH RectFull, LPDISPATCH RectInvalid);
	void PolyToolUsed(short ToolNum, long Flags, LPDISPATCH Points, BOOL bShift, BOOL bCtrl, BOOL FAR* EnableDefault)
	void ResolveDataBindEx(short Flag, short NumMatches, const VARIANT& Matches, short* Choice, BOOL* Cancel);
	void MapDraw(short Flag);
	void AddFeatureToolUsed(short ToolNum, long Flags, IDispatch* Feature, boolean bShift, boolean bCtrl, boolean* EnableDefault);
	void LabelChanged(short ChangeType, CMapXLabels* ChangingLabels, boolean* EnableDefault);
*/

/////////////////////////////////////////////////////////////////////////////
// CMapXSourceRow wrapper class

class CMapXSourceRow : public COleDispatchDriver
{
public:
	CMapXSourceRow() {}		// Calls COleDispatchDriver default constructor
	CMapXSourceRow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXSourceRow(const CMapXSourceRow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetRow();

// Operations
public:
};


/////////////////////////////////////////////////////////////////////////////
// CMapXSourceRows wrapper class

class CMapXSourceRows : public COleDispatchDriver
{
public:
	CMapXSourceRows() {}		// Calls COleDispatchDriver default constructor
	CMapXSourceRows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXSourceRows(const CMapXSourceRows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXSourceRow operator[](long Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();

// Operations
public:
	CMapXSourceRow Item(const VARIANT& Index);
	CMapXSourceRow Item(long Index) { return Item(COleVariant(Index)); }
};


/////////////////////////////////////////////////////////////////////////////
// CMapXRowValue wrapper class

class CMapXRowValue : public COleDispatchDriver
{
public:
	CMapXRowValue() {}		// Calls COleDispatchDriver default constructor
	CMapXRowValue(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXRowValue(const CMapXRowValue& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".RowValue.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	BOOL GetReadOnly();
	LPDISPATCH GetDataset();
	void SetDataset(LPDISPATCH);
	LPDISPATCH GetField();
	void SetField(LPDISPATCH);
	VARIANT GetValue();
	void SetValue(const VARIANT&);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXRowValues wrapper class

class CMapXRowValues : public COleDispatchDriver
{
public:
	CMapXRowValues() {}		// Calls COleDispatchDriver default constructor
	CMapXRowValues(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXRowValues(const CMapXRowValues& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".RowValues.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();
	BOOL GetReadOnly();

// Operations
public:
	CMapXRowValue Item(const VARIANT& Index);
	CMapXRowValue	Item(long Index) { return Item(COleVariant(Index)); }
	CMapXRowValue	Item(LPCTSTR Index) { return Item(COleVariant(Index)); }

	void Remove(const VARIANT& Index);
	CMapXRowValue Add(LPDISPATCH RowValue);
	void RemoveAll();
	CMapXRowValues Clone();
};


/////////////////////////////////////////////////////////////////////////////
// CMapXDataset wrapper class

class CMapXDataset : public COleDispatchDriver
{
public:
	CMapXDataset() {}		// Calls COleDispatchDriver default constructor
	CMapXDataset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXDataset(const CMapXDataset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetName();
	void SetName(LPCTSTR);
	long GetRowCount();
	CMapXFields GetFields();
	CMapXThemes GetThemes();
	long GetGeoField();
	long GetSecondaryGeoField();
	CMapXLayer GetLayer();
	short GetType();
	BOOL GetReadOnly();

// Operations
public:
	void Refresh();
	VARIANT GetValue(const VARIANT& Row, const VARIANT& Column);
	VARIANT GetValue(long Row, long Column)
	{ return GetValue(COleVariant(Row), COleVariant(Column)); }
	VARIANT GetValue(long Row, LPCTSTR Column)
	{ return GetValue(COleVariant(Row), COleVariant(Column)); }
	
	CMapXSourceRows GetSourceRows(const VARIANT& Row);
	CMapXSourceRows GetSourceRows(long Row)
	{ return GetSourceRows(COleVariant(Row)); }

	CMapXRowValues GetRowValues(const VARIANT& Row);
	CMapXRowValues GetRowValues(long Row)
	{ return GetRowValues(COleVariant(Row)); }

	CMapXField AddField(LPCTSTR Name, LPCTSTR Expression);
};

/////////////////////////////////////////////////////////////////////////////
// CMapXDatasets wrapper class

class CMapXDatasets : public COleDispatchDriver
{
public:
	CMapXDatasets() {}		// Calls COleDispatchDriver default constructor
	CMapXDatasets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXDatasets(const CMapXDatasets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();
	
	CMapXDataset operator[](long Index) { return Item(Index); }
	CMapXDataset operator[](LPCTSTR Index) { return Item(Index); }

	BOOL GetBuildSourceRows();
	void SetBuildSourceRows(BOOL b);

// Operations
public:
	CMapXDataset Add(long Type, const VARIANT& SourceData, const VARIANT& Name, const VARIANT& GeoField, const VARIANT& SecondaryGeoField, const VARIANT& BindLayer, const VARIANT& Fields, const VARIANT& Dynamic);
	CMapXDataset Add(short Type, const VARIANT& SourceData, LPCTSTR Name=NULL, long GeoField=0)
	{ return Add(	Type, SourceData, COleVariant(Name), COleVariant(GeoField),
					COptionalVariant(), COptionalVariant(), COptionalVariant(), COptionalVariant());
	}
	CMapXDataset Item(const VARIANT& Index);
	CMapXDataset Item(long Index) { return Item(COleVariant(Index)); }
	CMapXDataset Item(LPCTSTR Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void Remove(LPCTSTR Index) { Remove(COleVariant(Index)); }
	CMapXDataset Restore(LPCTSTR Name, const VARIANT& SourceData);
	void RemoveAll();

};

/////////////////////////////////////////////////////////////////////////////
// CMapXLabelProperties wrapper class

class CMapXLabelProperties : public COleDispatchDriver
{
public:
	CMapXLabelProperties() {}		// Calls COleDispatchDriver default constructor
	CMapXLabelProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLabelProperties(const CMapXLabelProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);
	BOOL GetVisible();
	void SetVisible(BOOL);
	BOOL GetLabelZoom();
	void SetLabelZoom(BOOL);
	double GetLabelZoomMin();
	void SetLabelZoomMin(double);
	double GetLabelZoomMax();
	void SetLabelZoomMax(double);
	short GetLineType();
	void SetLineType(short);
	short GetOffset();
	void SetOffset(short);
	BOOL GetParallel();
	void SetParallel(BOOL);
	CMapXDataset GetDataset();
	void SetDataset(LPDISPATCH);
	BOOL GetDuplicate();
	void SetDuplicate(BOOL);
	BOOL GetOverlap();
	void SetOverlap(BOOL);
	short GetLabelMax();
	void SetLabelMax(short);
	CMapXField GetDataField();
	void SetDataField(LPDISPATCH);
	short GetPosition();
	void SetPosition(short);
	BOOL GetPartialSegments();
	void SetPartialSegments(BOOL);
	BOOL GetLabelPartialObjects();
	void SetLabelPartialObjects(BOOL);
	short GetLabelAlong();
	void SetLabelAlong(short);
// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFeature wrapper class

class CMapXFeature : public COleDispatchDriver
{
public:
	CMapXFeature() {}		// Calls COleDispatchDriver default constructor
	CMapXFeature(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFeature(const CMapXFeature& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Feature.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	long GetFeatureID();
	short GetType();
	void SetType(short);
	double GetLength();
	double GetCenterX();
	double GetCenterY();
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);
	CMapXRectangle GetBounds();
	CMapXParts GetParts();
	double GetArea();
	CMapXLayer GetLayer();
	CString GetCaption();
	void SetCaption(LPCTSTR);
	CMapXPoint GetPoint();
	void SetPoint(LPDISPATCH);
	CMapXPoint GetLabelPoint();
	double GetPerimeter();
	BOOL GetSmooth();
	void SetSmooth(BOOL);
	CString GetName();
	CString GetKeyValue();
	void SetKeyValue(LPCTSTR);
	CString GetFeatureKey();
	CMapXFeature GetRegion();
	void SetRegion(LPDISPATCH);
	CMapXFeature GetPolyline();
	void SetPolyline(LPDISPATCH);
	CMapXFeature GetMultipoint();
	void SetMultipoint(LPDISPATCH);
	BOOL GetHasRegion();
	BOOL GetHasPolyline();
	BOOL GetHasMultipoint();

// Operations
public:
	void Update(const VARIANT& UpdateFeature, const VARIANT& RowValues);
	void Update(bool UpdateFeature, LPDISPATCH RowValues)
	{ Update(COleVariant((short)UpdateFeature), COleVariantDispatch(RowValues)); }
	void Update(bool UpdateFeature)
	{
		short sUpdateFeature = (short) UpdateFeature;

		Update(COleVariant(sUpdateFeature), COptionalVariant());
	}
	void Update(LPDISPATCH RowValues)
	{
		Update(COptionalVariant(), COleVariantDispatch(RowValues));
	}
	void Update()
	{ Update(COptionalVariant(), COptionalVariant()); }

	void Offset(double deltaX, double deltaY);
	void Attach(LPDISPATCH Map);
	CMapXFeature Clone();

	VARIANT GetNodes(const VARIANT& CSys);
	VARIANT GetNodes()
	{ return GetNodes(COptionalVariant()); }
	void SetNodes(const VARIANT& CSys, const VARIANT& newValue);

	// Obsolete. You should use GetNodes(CSys) instead:
	VARIANT Nodes(const VARIANT& CSys);
	// Obsolete. You should use GetNodes() instead:
	VARIANT Nodes()
	{ return Nodes(COptionalVariant()); }
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFeatures wrapper class

class CMapXFeatures : public COleDispatchDriver
{
public:
	CMapXFeatures() {}		// Calls COleDispatchDriver default constructor
	CMapXFeatures(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFeatures(const CMapXFeatures& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXFeature operator[](long Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();
	CMapXRectangle GetBounds();

// Operations
public:
	CMapXFeature Item(const VARIANT& Index);
	CMapXFeature Item(long Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Source);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void Remove(LPDISPATCH Source=NULL)
	{ Remove(COleVariantDispatch(Source)); }
	
	CMapXFeatures Clone();

	void AddByID(const VARIANT& FeatureID);
	void AddByID(long FeatureID)
	{ AddByID(COleVariant(FeatureID)); }
	void AddByID(LPCTSTR FeatureID)
	{ AddByID(COleVariant(FeatureID)); }

	void RemoveByID(const VARIANT& FeatureID);
	void RemoveByID(long FeatureID)
	{ RemoveByID(COleVariant(FeatureID)); }
	void RemoveByID(LPCTSTR FeatureID)
	{ RemoveByID(COleVariant(FeatureID)); }
	
	void Add(LPDISPATCH Source);
	void Common(LPDISPATCH Source);
	void Replace(LPDISPATCH Source);
};

/////////////////////////////////////////////////////////////////////////////
// CMapXLayer wrapper class

class CMapXLayer : public COleDispatchDriver
{
public:
	CMapXLayer() {}		// Calls COleDispatchDriver default constructor
	CMapXLayer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLayer(const CMapXLayer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetName();
	void SetName(LPCTSTR);
	BOOL GetVisible();
	void SetVisible(BOOL);
	BOOL GetSelectable();
	void SetSelectable(BOOL);
	CString GetFilespec();
	CMapXLabelProperties GetLabelProperties();
	CMapXLabelProperties GetLabel() { return GetLabelProperties(); }
	BOOL GetAutoLabel();
	void SetAutoLabel(BOOL);
	BOOL GetZoomLayer();
	void SetZoomLayer(BOOL);
	BOOL GetOverrideStyle();
	void SetOverrideStyle(BOOL);
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);
	double GetZoomMin();
	void SetZoomMin(double);
	double GetZoomMax();
	void SetZoomMax(double);
	CMapXSelection GetSelection();
	short GetPredominantFeatureType();
	CMapXLayerFind GetFind();
	short GetType();
	CString GetKeyField();
	void SetKeyField(LPCTSTR);
	CMapXCoordSys GetCoordSys();
	CMapXRectangle GetBounds();
	BOOL GetDrawLabelsAfter();
	void SetDrawLabelsAfter(BOOL);
	CMapXDatasets GetDatasets();
	BOOL GetShowNodes();
	void SetShowNodes(BOOL propVal);
	BOOL GetShowCentroids();
	void SetShowCentroids(BOOL propVal);
	BOOL GetShowLineDirection();
	void SetShowLineDirection(BOOL propVal);
	BOOL GetEditable();
	void SetEditable(BOOL propVal);
	CMapXRectangle GetClippedBounds();
	CMapXLabels GetLabels();

// Operations
public:
	void LabelAtPoint(double X, double Y);
	void ClearCustomLabels();
	
	CMapXFeature AddFeature(LPDISPATCH Source, const VARIANT& RowValues);
	CMapXFeature AddFeature(LPDISPATCH Source)
	{ return AddFeature(Source, COptionalVariant()); }
	CMapXFeature AddFeature(LPDISPATCH Source, LPDISPATCH RowValues)
	{
		return AddFeature(Source, COleVariantDispatch(RowValues));
	}

	void UpdateFeature(const VARIANT& Target, const VARIANT& Source, const VARIANT& RowValues);
	void UpdateFeature(LPDISPATCH Target, LPDISPATCH Source, LPDISPATCH RowValues)
	{
		UpdateFeature(COleVariantDispatch(Target), COleVariantDispatch(Source), COleVariantDispatch(RowValues));
	}
	void UpdateFeature(LPCTSTR Target, LPDISPATCH Source, LPDISPATCH RowValues)
	{
		UpdateFeature(COleVariant(Target), COleVariantDispatch(Source), COleVariantDispatch(RowValues));
	}
	void UpdateFeature(long Target, LPDISPATCH Source, LPDISPATCH RowValues)
	{
		UpdateFeature(COleVariant(Target), COleVariantDispatch(Source), COleVariantDispatch(RowValues));
	}
	void UpdateFeature(LPDISPATCH Target, LPDISPATCH Source)
	{
		UpdateFeature(COleVariantDispatch(Target), COleVariantDispatch(Source), COptionalVariant());
	}
	void UpdateFeature(LPCTSTR Target, LPDISPATCH Source)
	{
		UpdateFeature(COleVariant(Target), COleVariantDispatch(Source), COptionalVariant());
	}
	void UpdateFeature(long Target, LPDISPATCH Source)
	{
		UpdateFeature(COleVariant(Target), COleVariantDispatch(Source), COptionalVariant());
	}
	void UpdateFeature(LPDISPATCH Target)
	{
		UpdateFeature(COleVariantDispatch(Target), COptionalVariant(), COptionalVariant());
	}
	void UpdateFeature(LPCTSTR Target)
	{ UpdateFeature(COleVariant(Target), COptionalVariant(), COptionalVariant()); }
	void UpdateFeature(long Target)
	{ UpdateFeature(COleVariant(Target), COptionalVariant(), COptionalVariant()); }

	void DeleteFeature(const VARIANT& Target);
	void DeleteFeature(LPDISPATCH Target)
	{
		DeleteFeature(COleVariantDispatch(Target));
	}
	void DeleteFeature(LPCTSTR Target)
	{ DeleteFeature(COleVariant(Target)); }
	void DeleteFeature(long Target)
	{ DeleteFeature(COleVariant(Target)); }

	void Invalidate(const VARIANT& InvalidRect);
	void Invalidate() { Invalidate(COptionalVariant()); }
	CMapXFeatures SearchWithinDistance(LPDISPATCH Source, double Distance, short Units, short SearchType);
	CMapXFeatures SearchWithinRectangle(LPDISPATCH Rectangle, short SearchType);
	CMapXFeatures AllFeatures();
	CMapXFeatures NoFeatures();
	CMapXBoundsConstraint CreateBoundsConstraint();
	CMapXFeaturesConstraint CreateFeaturesConstraint();
	CMapXAllFeaturesConstraint CreateAllFeaturesConstraint();
	CMapXFeatures SearchWithinFeature(LPDISPATCH Feature, short SearchType);
	CMapXFeatures SearchAtPoint(LPDISPATCH Point, short SearchResultFlags = miSearchResultAll);
	void DrillDownRemoveFeatures(LPCTSTR Level, const VARIANT& FeatureKeys);
	void DrillDownAddFeatures(LPCTSTR Level, const VARIANT& FeatureKeys);
	CMapXFeatures GetDrilldownFeaturesByID(LPCTSTR Level, const VARIANT& FeatureKeys);
	void DrilldownReset(LPCTSTR Level);
	CMapXFeature GetFeatureByID(long FeatureID);
	void Refresh();
	long FeatureIDFromFeatureName(LPCTSTR Name);

	CMapXFeatures Search(LPCTSTR Where, const VARIANT& Variables);
	CMapXFeatures Search(LPCTSTR Where)
		{ return Search(Where, COptionalVariant()); }
	CMapXFeatures Search(LPCTSTR Where, LPDISPATCH Variables)
		{ return Search(Where, COleVariantDispatch(Variables)); }
	BOOL SupportsPack(long PackType);
	void Pack(long PackType);
	

	void BeginAccess(long BeginAccessType);
	void EndAccess(const VARIANT& EndAccessType);
	void EndAccess()
	{ EndAccess(COptionalVariant()); }

	CMapXFeature GetFeatureByKey(LPCTSTR);
	CString FeatureKeyFromFeatureName(LPCTSTR);
};

class CMapXLayers : public COleDispatchDriver
{
public:
	CMapXLayers() {}		// Calls COleDispatchDriver default constructor
	CMapXLayers(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLayers(const CMapXLayers& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXLayer operator[](long Index) { return Item(Index); }
	CMapXLayer operator[](LPCTSTR Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();
	long GetCount();
	
	CMapXLayer GetAnimationLayer();
	void SetAnimationLayer(LPDISPATCH);
	CMapXRectangle GetBounds();
	CMapXLayer GetInsertionLayer();
	void SetInsertionLayer(LPDISPATCH);
	CMapXRectangle GetClippedBounds();

// Operations
public:
	void ClearSelection();
	BOOL Move(short From, short To);
	CMapXLayer Add(const VARIANT& LayerInfo, const VARIANT& Position);
	CMapXLayer Add(LPDISPATCH LayerInfo)
	{
		return Add(COleVariantDispatch(LayerInfo), COptionalVariant());
	}
	CMapXLayer Add(LPDISPATCH LayerInfo, long Position)
	{
		return Add(COleVariantDispatch(LayerInfo), COleVariant(Position));
	}
	CMapXLayer Add(LPCTSTR Filespec, const VARIANT& Position)
	{ return Add(COleVariant(Filespec), Position); }
	CMapXLayer Add(LPCTSTR Filespec) // for backward compatiblity
	{ return Add(COleVariant(Filespec), COptionalVariant()); }
	CMapXLayer Add(LPCTSTR Filespec, long Position)
	{ return Add(COleVariant(Filespec), COleVariant(Position)); }

	void AddGeoSetLayers(LPCTSTR GeoSetName);
	CMapXLayer Item(const VARIANT& Index);
	CMapXLayer Item(long Index) { return Item(COleVariant(Index)); }
	CMapXLayer Item(LPCTSTR Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void Remove(LPCTSTR Index) { Remove(COleVariant(Index)); }
	CMapXLayer AddUserDrawLayer(LPCTSTR Name, short Position);
	CMapXLayer CreateLayer(LPCTSTR Name, const VARIANT& Filespec, const VARIANT& Position, const VARIANT& KeyLength, const VARIANT& CoordSys);
	CMapXLayer CreateLayer(LPCTSTR Name, LPCTSTR Filespec=NULL, long Position=-1, short KeyLength=32)
		{ return CreateLayer(Name, COleVariant(Filespec), COleVariant(Position), COleVariant(KeyLength), COptionalVariant()); }
	BOOL LayersDlg(const VARIANT& HelpFile, const VARIANT& HelpID);
	BOOL LayersDlg(LPCTSTR HelpFile, UINT HelpID=HELP_FINDER)
		{ return LayersDlg(COleVariant(HelpFile), COleVariant((long)HelpID)); }
	BOOL LayersDlg()
		{ return LayersDlg(COptionalVariant(), COptionalVariant()); }
	CMapXLayer AddServerLayer(LPCTSTR Name, LPCTSTR ConnectString, LPCTSTR Query, const VARIANT& Position, const VARIANT& Options);
	CMapXLayer AddServerLayer(LPCTSTR Name, LPCTSTR ConnectString, LPCTSTR Query, long Position, long Options=0)
		{ return AddServerLayer(Name, ConnectString, Query, COleVariant(Position), COleVariant(Options)); }
	CMapXLayer AddServerLayer(LPCTSTR Name, LPCTSTR ConnectString, LPCTSTR Query)
		{ return AddServerLayer(Name, ConnectString, Query, COptionalVariant(), COptionalVariant()); }
	void RemoveAll();

};
/////////////////////////////////////////////////////////////////////////////
// CMapXField wrapper class

class CMapXField : public COleDispatchDriver
{
public:
	CMapXField() {}		// Calls COleDispatchDriver default constructor
	CMapXField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXField(const CMapXField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetType();
	CString GetName();
	long GetAggregationFunction();
	short GetWidth();
	short GetPrecision();
	short GetDecimals();
	BOOL GetIndexed();
	long GetTypeEx();

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXTheme wrapper class

class CMapXTheme : public COleDispatchDriver
{
public:
	CMapXTheme() {}		// Calls COleDispatchDriver default constructor
	CMapXTheme(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXTheme(const CMapXTheme& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetVisible();
	void SetVisible(BOOL);
	short GetType();
	CMapXThemeProperties GetProperties();
	CMapXLegend GetLegend();
	BOOL GetAutoRecompute();
	void SetAutoRecompute(BOOL);
	CString GetName();
	void SetName(LPCTSTR);
	CMapXThemeProperties GetThemeProperties();
	CMapXLayer GetLayer();
	CMapXFields GetFields();
	double GetDataMin();
	void SetDataMin(double);
	double GetDataMax();
	void SetDataMax(double);
	BOOL GetComputeTheme();
	void SetComputeTheme(BOOL);
	long GetThemedFeatureType();

// Operations
public:
	BOOL ThemeDlg(const VARIANT& HelpFile, const VARIANT& HelpID);
	BOOL ThemeDlg(LPCTSTR HelpFile, UINT HelpID=HELP_FINDER)
		{ return ThemeDlg(COleVariant(HelpFile), COleVariant((long)HelpID)); }
	BOOL ThemeDlg()
		{ return ThemeDlg(COptionalVariant(), COptionalVariant()); }
};

/////////////////////////////////////////////////////////////////////////////
// CMapXThemes wrapper class

class CMapXThemes : public COleDispatchDriver
{
public:
	CMapXThemes() {}		// Calls COleDispatchDriver default constructor
	CMapXThemes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXThemes(const CMapXThemes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXTheme operator[](long Index) { return Item(Index); }
	CMapXTheme operator[](LPCTSTR Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();
	
	long GetCount();

// Operations
public:
	CMapXTheme Add(const VARIANT& Type, const VARIANT& Field, const VARIANT& Name, const VARIANT& ComputeTheme);
	CMapXTheme Add(const VARIANT& Type, const VARIANT& Field, const VARIANT& Name)
		{ return Add(COleVariant(Type), COleVariant(Field), COleVariant(Name), COptionalVariant()); }
	CMapXTheme Add(short Type, long Field, LPCTSTR Name)
		{ return Add(COleVariant(Type), COleVariant(Field), COleVariant(Name), COptionalVariant()); }
	CMapXTheme Add(short Type, LPCTSTR Field, LPCTSTR Name)
		{ return Add(COleVariant(Type), COleVariant(Field), COleVariant(Name), COptionalVariant()); }
	CMapXTheme Add(short Type, long Field)
		{ return Add(COleVariant(Type), COleVariant(Field), COptionalVariant(), COptionalVariant()); }
	CMapXTheme Add(short Type, LPCTSTR Field)
		{ return Add(COleVariant(Type), COleVariant(Field), COptionalVariant(), COptionalVariant()); }
	CMapXTheme Add(short Type=miThemeAuto)
		{ return Add(COleVariant(Type), COptionalVariant(), COptionalVariant(), COptionalVariant()); }
	CMapXTheme Item(const VARIANT& Index);
	CMapXTheme Item(long Index) { return Item(COleVariant(Index)); }
	CMapXTheme Item(LPCTSTR Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void Remove(LPCTSTR Index) { Remove(COleVariant(Index)); }
	void RemoveAll();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXLegend wrapper class

class CMapXLegend : public COleDispatchDriver
{
public:
	CMapXLegend() {}		// Calls COleDispatchDriver default constructor
	CMapXLegend(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLegend(const CMapXLegend& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetCompact();
	void SetCompact(BOOL);
	BOOL GetVisible();
	void SetVisible(BOOL);
	CMapXStyle GetTitleStyle();
	void SetTitleStyle(LPDISPATCH);
	CMapXStyle GetSubTitleStyle();
	void SetSubTitleStyle(LPDISPATCH);
	CMapXStyle GetCompactTitleStyle();
	void SetCompactTitleStyle(LPDISPATCH);
	CMapXStyle GetBodyTextStyle();
	void SetBodyTextStyle(LPDISPATCH);
	CMapXLegendTexts GetLegendTexts();
	BOOL GetCurrencyFormat();
	void SetCurrencyFormat(BOOL);
	CString GetTitle();
	void SetTitle(LPCTSTR);
	CString GetSubTitle();
	void SetSubTitle(LPCTSTR);
	CString GetCompactTitle();
	void SetCompactTitle(LPCTSTR);
	double GetLeft();
	void SetLeft(double);
	double GetTop();
	void SetTop(double);
	double GetWidth();
	double GetHeight();
	BOOL GetShowEmptyRanges();
	void SetShowEmptyRanges(BOOL);
	BOOL GetShowCount();
	void SetShowCount(BOOL propVal);
	double GetPaperHeight();
	double GetPaperWidth();
		
// Operations
public:
	BOOL LegendDlg(const VARIANT& HelpFile, const VARIANT& HelpID);
	BOOL LegendDlg(LPCTSTR HelpFile, UINT HelpID=HELP_FINDER)
		{ return LegendDlg(COleVariant(HelpFile), COleVariant((long)HelpID)); }
	BOOL LegendDlg()
		{ return LegendDlg(COptionalVariant(), COptionalVariant()); }
	void ExportLegend(LPCTSTR Destination, short Format);
	void PrintLegend(long hDC, long X, long Y, long W, long H);
};

/////////////////////////////////////////////////////////////////////////////
// CMapXAnnotation wrapper class

class CMapXAnnotation : public COleDispatchDriver
{
public:
	CMapXAnnotation() {}		// Calls COleDispatchDriver default constructor
	CMapXAnnotation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXAnnotation(const CMapXAnnotation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	short GetType();
	CMapXGraphic GetGraphic();

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXAnnotations wrapper class

class CMapXAnnotations : public COleDispatchDriver
{
public:
	CMapXAnnotations() {}		// Calls COleDispatchDriver default constructor
	CMapXAnnotations(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXAnnotations(const CMapXAnnotations& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXAnnotation operator[](long Index) { return Item(Index); }
	CMapXAnnotation operator[](LPCTSTR Index) { return Item(Index); }

	// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	BOOL GetEditable();
	void SetEditable(BOOL);
	long GetCount();

// Operations
public:
	
	CMapXAnnotation Item(const VARIANT& Index);
	CMapXAnnotation Item(long Index) { return Item(COleVariant(Index)); }
	CMapXAnnotation Item(LPCTSTR Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }

	CMapXAnnotation AddSymbol(double X, double Y);
	CMapXAnnotation AddText(LPCTSTR Text, double X, double Y, const VARIANT& Position);
	CMapXAnnotation AddText(LPCTSTR Text, double X, double Y, short Position)
		{ return AddText(Text, X, Y, COleVariant(Position)); }

	void RemoveAll();
	CMapXAnnotation ActiveAnnotation();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXThemeProps wrapper class

class CMapXThemeProperties : public COleDispatchDriver
{
public:
	CMapXThemeProperties() {}		// Calls COleDispatchDriver default constructor
	CMapXThemeProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXThemeProperties(const CMapXThemeProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	short GetDistMethod();
	void SetDistMethod(short);
	short GetNumRanges();
	void SetNumRanges(short);
	CMapXRangeCategories GetRangeCategories();
	short GetDotSize();
	void SetDotSize(short);
	BOOL GetGraduated();
	void SetGraduated(BOOL);
	CMapXMultivarCategories GetMultivarCategories();
	BOOL GetIndependent();
	void SetIndependent(BOOL);
	CMapXIndividualValueCategories GetIndividualValueCategories();
	double GetValuePerDot();
	void SetValuePerDot(double);
	double GetDataValue();
	void SetDataValue(double);
	double GetSize();
	void SetSize(double);
	double GetWidth();
	void SetWidth(double);
	CMapXStyle GetSymbolStyle();
	void SetSymbolStyle(LPDISPATCH);
	short GetSpreadBy();
	void SetSpreadBy(short);
	BOOL GetAllowEmptyRanges();
	void SetAllowEmptyRanges(BOOL);
	unsigned long GetDotColor();
	void SetDotColor(unsigned long);
	BOOL GetPieClockwise();
	void SetPieClockwise(BOOL);
	BOOL GetPieHalfPies();
	void SetPieHalfPies(BOOL);
	short GetPieStartAngle();
	void SetPieStartAngle(short);
	BOOL GetBarStacked();
	void SetBarStacked(BOOL);
	CMapXStyle GetNegativeSymbolStyle();
	void SetNegativeSymbolStyle(LPDISPATCH);
	BOOL GetShowNegativeValues();
	void SetShowNegativeValues(BOOL);
	short GetGraduateSizeBy();
	void SetGraduateSizeBy(short);
	CMapXStyle GetBorderStyle();
	void SetBorderStyle(LPDISPATCH);
	double GetBarWidth();
	void SetBarWidth(double);
	BOOL GetBarIndependentScale();
	void SetBarIndependentScale(BOOL);
	CMapXStyle GetPositiveSymbolStyle();
	void SetPositiveSymbolStyle(LPDISPATCH);
	CMapXStyle GetBarFrameStyle();
	void SetBarFrameStyle(LPDISPATCH);
	BOOL GetPieGraduated();
	void SetPieGraduated(BOOL);
	BOOL GetBarGraduatedStack();
	void SetBarGraduatedStack(BOOL);
	short GetApplyAttribute();
	void SetApplyAttribute(short);
	BOOL GetRoundRanges();
	void SetRoundRanges(BOOL);
	double GetRoundBy();
	void SetRoundBy(double);
	short GetColorMethod();
	void SetColorMethod(short);
	BOOL GetInflectRanges();
	void SetInflectRanges(BOOL);
	short GetInflectionRange();
	void SetInflectionRange(short);
	unsigned long GetInflectionColor();
	void SetInflectionColor(unsigned long);
	BOOL GetBarFramed();
	void SetBarFramed(BOOL);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXSelection wrapper class

class CMapXSelection : public COleDispatchDriver
{
public:
	CMapXSelection() {}		// Calls COleDispatchDriver default constructor
	CMapXSelection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXSelection(const CMapXSelection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXFeature operator[](long Index) { return Item(Index); }

	// Attributes
public:
	LPENUMVARIANT GetEnumerator();
	long GetCount();
	CMapXRectangle GetBounds();

// Operations
public:
	void SelectByRegion(LPDISPATCH Layer, const VARIANT& FeatureID, short Flag);
	void SelectByRegion(LPDISPATCH Layer, long FeatureID, short Flag)
	{ SelectByRegion(Layer, COleVariant(FeatureID), Flag); }
	void SelectByRegion(LPDISPATCH Layer, LPCTSTR FeatureID, short Flag)
	{ SelectByRegion(Layer, COleVariant(FeatureID), Flag); }

	void ClearSelection();
	void SelectByPoint(double X, double Y, short SelectFlag, short SearchResultFlags = miSearchResultAll);
	void SelectByRadius(double X, double Y, double radius, short Flag);
	void SelectByRectangle(double X1, double Y1, double X2, double Y2, short Flag);
	BOOL SelectAll(short Flag);

	void SelectByID(const VARIANT& FeatureID, short Flag);
	void SelectByID(long FeatureID, short Flag)
	{ SelectByID(COleVariant(FeatureID), Flag); }
	void SelectByID(LPCTSTR FeatureID, short Flag)
	{ SelectByID(COleVariant(FeatureID), Flag); }

	CMapXFeature Item(const VARIANT& Index);
	CMapXFeature Item(long Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Source);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void Remove(LPDISPATCH Source=NULL)
	{ Remove(COleVariantDispatch(Source));}
	
	CMapXFeatures Clone();

	void Add(LPDISPATCH Source);
	void Common(LPDISPATCH Source);
	void Replace(LPDISPATCH Source);

	void AddByID(const VARIANT& FeatureID);
	void RemoveByID(const VARIANT& FeatureID);
};

/////////////////////////////////////////////////////////////////////////////
// CMapXRangeCategory wrapper class

class CMapXRangeCategory : public COleDispatchDriver
{
public:
	CMapXRangeCategory() {}		// Calls COleDispatchDriver default constructor
	CMapXRangeCategory(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXRangeCategory(const CMapXRangeCategory& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	double GetMin();
	void SetMin(double);
	double GetMax();
	void SetMax(double);
	long GetNumItems();
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// CMapXFields wrapper class

class CMapXFields : public COleDispatchDriver
{
public:
	CMapXFields() {}		// Calls COleDispatchDriver default constructor
	CMapXFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFields(const CMapXFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Fields.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

	CMapXField operator[](long Index) { return Item(Index); }
	CMapXField operator[](LPCTSTR Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();

// Operations
public:
	CMapXField Add(const VARIANT& SourceField, const VARIANT& Name, const VARIANT& AggregationFunction, const VARIANT& Type);
	CMapXField Add(LPCTSTR SourceField, LPCTSTR Name=_T(""), short AggregationFunction=miAggregationAuto)
		{ return Add(COleVariant(SourceField), COleVariant(Name), COleVariant(AggregationFunction), COptionalVariant()); }
	CMapXField Add(long SourceField, LPCTSTR Name=_T(""), short AggregationFunction=miAggregationAuto)
		{ return Add(COleVariant(SourceField), COleVariant(Name), COleVariant(AggregationFunction), COptionalVariant()); }
	CMapXField Item(const VARIANT& Index);
	CMapXField Item(long Index) { return Item(COleVariant(Index)); }
	CMapXField Item(LPCTSTR Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void Remove(LPCTSTR Index) { Remove(COleVariant(Index)); }
	void RemoveAll();
	CMapXField AddStringField(const VARIANT& Name, const VARIANT& Width, const VARIANT& Indexed);
	CMapXField AddStringField(const VARIANT& Name, const VARIANT& Width)
	{
		return AddStringField(Name, Width, COptionalVariant());
	}
	CMapXField AddStringField(LPCTSTR Name, long Width, BOOL Indexed = FALSE)
	{
		short sIndexed = (short) Indexed;
		return AddStringField(COleVariant(Name), COleVariant(Width), COleVariant(sIndexed));
	}
	CMapXField AddLogicalField(const VARIANT& Name, const VARIANT& Indexed);
	CMapXField AddLogicalField(const VARIANT& Name)
	{
		return AddLogicalField(Name, COptionalVariant());
	}
	CMapXField AddLogicalField(LPCTSTR Name, BOOL Indexed = FALSE)
	{
		short sIndexed = (short) Indexed;
		return AddLogicalField(COleVariant(Name), COleVariant(sIndexed));
	}
	CMapXField AddIntegerField(const VARIANT& Name, const VARIANT& Indexed);
	CMapXField AddIntegerField(const VARIANT& Name)
	{
		return AddIntegerField(Name, COptionalVariant());
	}
	CMapXField AddIntegerField(LPCTSTR Name, BOOL Indexed = FALSE)
	{
		short sIndexed = (short) Indexed;
		return AddIntegerField(COleVariant(Name), COleVariant(sIndexed));
	}
	CMapXField AddSmallIntField(const VARIANT& Name, const VARIANT& Indexed);
	CMapXField AddSmallIntField(const VARIANT& Name)
	{
		return AddSmallIntField(Name, COptionalVariant());
	}
	CMapXField AddSmallIntField(LPCTSTR Name, BOOL Indexed = FALSE)
	{
		short sIndexed = (short) Indexed;
		return AddSmallIntField(COleVariant(Name), COleVariant(sIndexed));
	}
	CMapXField AddNumericField(const VARIANT& Name, const VARIANT& Precision, const VARIANT& Decimals, const VARIANT& Indexed);
	CMapXField AddNumericField(const VARIANT& Name, const VARIANT& Precision, const VARIANT& Decimals)
	{
		return AddNumericField(Name, Precision, Decimals, COptionalVariant());
	}
	CMapXField AddNumericField(LPCTSTR Name, long Precision, long Decimals, BOOL Indexed = FALSE)
	{
		short sIndexed = (short) Indexed;
		return AddNumericField(COleVariant(Name), COleVariant(Precision), COleVariant(Decimals), COleVariant(sIndexed));
	}
	CMapXField AddFloatField(const VARIANT& Name, const VARIANT& Indexed);
	CMapXField AddFloatField(const VARIANT& Name)
	{
		return AddFloatField(Name, COptionalVariant());
	}
	CMapXField AddFloatField(LPCTSTR Name, BOOL Indexed = FALSE)
	{
		short sIndexed = (short) Indexed;
		return AddFloatField(COleVariant(Name), COleVariant(sIndexed));
	}
	CMapXField AddDateField(const VARIANT& Name, const VARIANT& Indexed);
	CMapXField AddDateField(const VARIANT& Name)
	{
		return AddDateField(Name, COptionalVariant());
	}
	CMapXField AddDateField(LPCTSTR Name, BOOL Indexed = FALSE)
	{
		short sIndexed = (short) Indexed;
		return AddDateField(COleVariant(Name), COleVariant(sIndexed));
	}
};

class COleFont : public COleDispatchDriver
{
public:
	COleFont() {}		// Calls COleDispatchDriver default constructor
	COleFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COleFont(const COleFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetName();
	void SetName(LPCTSTR);
	CY GetSize();
	void SetSize(const CY&);
	BOOL GetBold();
	void SetBold(BOOL);
	BOOL GetItalic();
	void SetItalic(BOOL);
	BOOL GetUnderline();
	void SetUnderline(BOOL);
	BOOL GetStrikethrough();
	void SetStrikethrough(BOOL);
	short GetWeight();
	void SetWeight(short);
	short GetCharset();
	void SetCharset(short);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXStyle wrapper class

class CMapXStyle : public COleDispatchDriver
{
public:
	CMapXStyle() {}		// Calls COleDispatchDriver default constructor
	CMapXStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXStyle(const CMapXStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Style.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	short GetSymbolCharacter();
	void SetSymbolCharacter(short);
	unsigned long GetLineColor();
	void SetLineColor(unsigned long);
	short GetLineStyle();
	void SetLineStyle(short);
	short GetLineWidth();
	void SetLineWidth(short);
	unsigned long GetRegionColor();
	void SetRegionColor(unsigned long);
	short GetRegionPattern();
	void SetRegionPattern(short);
	BOOL GetRegionTransparent();
	void SetRegionTransparent(BOOL);
	unsigned long GetRegionBackColor();
	void SetRegionBackColor(unsigned long);
	short GetRegionBorderStyle();
	void SetRegionBorderStyle(short);
	unsigned long GetRegionBorderColor();
	void SetRegionBorderColor(unsigned long);
	short GetRegionBorderWidth();
	void SetRegionBorderWidth(short);
	COleFont GetTextFont();
	COleFont GetSymbolFont();
	unsigned long GetTextFontColor();
	void SetTextFontColor(unsigned long);
	unsigned long GetTextFontBackColor();
	void SetTextFontBackColor(unsigned long);
	unsigned long GetSymbolFontColor();
	void SetSymbolFontColor(unsigned long);
	unsigned long GetSymbolFontBackColor();
	void SetSymbolFontBackColor(unsigned long);
	BOOL GetSymbolFontOpaque();
	void SetSymbolFontOpaque(BOOL);
	BOOL GetTextFontOpaque();
	void SetTextFontOpaque(BOOL);
	BOOL GetSymbolFontHalo();
	void SetSymbolFontHalo(BOOL);
	BOOL GetSymbolFontShadow();
	void SetSymbolFontShadow(BOOL);
	BOOL GetTextFontHalo();
	void SetTextFontHalo(BOOL);
	BOOL GetTextFontShadow();
	void SetTextFontShadow(BOOL);
	BOOL GetTextFontAllCaps();
	void SetTextFontAllCaps(BOOL);
	BOOL GetTextFontDblSpace();
	void SetTextFontDblSpace(BOOL);
	BOOL GetSymbolBitmapTransparent();
	void SetSymbolBitmapTransparent(BOOL bNewValue);
	BOOL GetSymbolBitmapOverrideColor();
	void SetSymbolBitmapOverrideColor(BOOL bNewValue);
	unsigned long GetSymbolBitmapColor();
	void SetSymbolBitmapColor(unsigned long nNewValue);
	CString GetSymbolBitmapName();
	void SetSymbolBitmapName(LPCTSTR lpszNewValue);
	short GetSymbolType();
	void SetSymbolType(short nNewValue);
	long GetSymbolBitmapSize();
	void SetSymbolBitmapSize(long nNewValue);
	BOOL GetSupportsBitmapSymbols();
	short GetSymbolFontRotation();
	void SetSymbolFontRotation(short nNewValue);
	long GetLineStyleCount();
	BOOL GetLineInterleaved();
	void SetLineInterleaved(BOOL bNewValue);
	long GetLineWidthUnit();
	void SetLineWidthUnit(long nNewValue);
	long GetRegionBorderWidthUnit();
	void SetRegionBorderWidthUnit(long nNewValue);
	BOOL GetLineSupportsInterleave();
	short GetTextFontRotation();
	void SetTextFontRotation(short propVal);
	unsigned long GetSymbolVectorColor();
	void SetSymbolVectorColor(unsigned long);
	short GetSymbolVectorSize();
	void SetSymbolVectorSize(short);
	short GetMinVectorSymbolCharacter();
	short GetMaxVectorSymbolCharacter();

// Operations
public:
	BOOL PickRegion();
	BOOL PickLine();
	BOOL PickText();
	BOOL PickSymbol();
	void DrawTextSample(long hDC, LPDISPATCH Rectangle, LPCTSTR SampleText);
	void DrawSymbolSample(long hDC, LPDISPATCH Rectangle);
	void DrawRegionSample(long hDC, LPDISPATCH Rectangle);
	void DrawLineSample(long hDC, LPDISPATCH Rectangle);
	CMapXStyle Clone();
	void ExportSymbolSample(LPCTSTR Destination, short Format, double Width, double Height, const VARIANT& BackgroundColor);
	void ExportRegionSample(LPCTSTR Destination, short Format, double Width, double Height, const VARIANT& BackgroundColor);
	void ExportLineSample(LPCTSTR Destination, short Format, double Width, double Height, const VARIANT& BackgroundColor);
	void ExportTextSample(LPCTSTR Destination, short Format, double Width, double Height, LPCTSTR SampleText, const VARIANT& BackgroundColor);
};
/////////////////////////////////////////////////////////////////////////////
// CMapXIndividualValueCategory wrapper class

class CMapXIndividualValueCategory : public COleDispatchDriver
{
public:
	CMapXIndividualValueCategory() {}		// Calls COleDispatchDriver default constructor
	CMapXIndividualValueCategory(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXIndividualValueCategory(const CMapXIndividualValueCategory& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);
	long GetNumItems();
	CString GetValue();
	void SetValue(LPCTSTR);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// CMapXMultivarCategory wrapper class

class CMapXMultivarCategory : public COleDispatchDriver
{
public:
	CMapXMultivarCategory() {}		// Calls COleDispatchDriver default constructor
	CMapXMultivarCategory(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXMultivarCategory(const CMapXMultivarCategory& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXText wrapper class (Same as CMapXGraphic)
// Used for both Text and Symbol annotations
// NOTE: ***OBSOLETE***: Do not use this class use CMapXGraphic instead
class CMapXText : public COleDispatchDriver
{
public:
	CMapXText() {}		// Calls COleDispatchDriver default constructor
	CMapXText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXText(const CMapXText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetCaption();
	void SetCaption(LPCTSTR);
	double GetX();
	void SetX(double);
	double GetY();
	void SetY(double);
	short GetPosition();
	void SetPosition(short);
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXGraphic wrapper class (Same as CMapXText)
// Used for both Text and Symbol annotations

class CMapXGraphic : public COleDispatchDriver
{
public:
	CMapXGraphic() {}		// Calls COleDispatchDriver default constructor
	CMapXGraphic(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXGraphic(const CMapXGraphic& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetCaption();
	void SetCaption(LPCTSTR);
	double GetX();
	void SetX(double);
	double GetY();
	void SetY(double);
	short GetPosition();
	void SetPosition(short);
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXLegendText wrapper class

class CMapXLegendText : public COleDispatchDriver
{
public:
	CMapXLegendText() {}		// Calls COleDispatchDriver default constructor
	CMapXLegendText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLegendText(const CMapXLegendText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetText();
	void SetText(LPCTSTR);
 	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// CMapXLegendTexts wrapper class

class CMapXLegendTexts : public COleDispatchDriver
{
public:
	CMapXLegendTexts() {}		// Calls COleDispatchDriver default constructor
	CMapXLegendTexts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLegendTexts(const CMapXLegendTexts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXLegendText operator[](long Index) { return Item(Index); }

	// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	BOOL GetAutoGenerate();
	void SetAutoGenerate(BOOL);
	long GetCount();
	CMapXLegendText GetAllOthersText();

// Operations
public:
	CMapXLegendText Item(const VARIANT& Index);
	CMapXLegendText Item(long Index) { return Item(COleVariant(Index)); }
};
/////////////////////////////////////////////////////////////////////////////
// CMapXTitle wrapper class

class CMapXTitle : public COleDispatchDriver
{
public:
	CMapXTitle() {}		// Calls COleDispatchDriver default constructor
	CMapXTitle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXTitle(const CMapXTitle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetCaption();
	void SetCaption(LPCTSTR);
	CMapXStyle GetTextStyle();
	void SetTextStyle(LPDISPATCH);
	BOOL GetVisible();
	void SetVisible(BOOL);
	double GetX();
	void SetX(double);
	double GetY();
	void SetY(double);
	BOOL GetEditable();
	void SetEditable(BOOL);
	short GetPosition();
	void SetPosition(short);
	BOOL GetBorder();
	void SetBorder(BOOL);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXBindLayer wrapper class

class CMapXBindLayer : public COleDispatchDriver
{
public:
	CMapXBindLayer() {}		// Calls COleDispatchDriver default constructor
	CMapXBindLayer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXBindLayer(const CMapXBindLayer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".BindLayer.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	CString GetLayerName();
	void SetLayerName(LPCTSTR);
	VARIANT GetRefColumn1();
	void SetRefColumn1(const VARIANT&);
	void SetRefColumn1(long Column) { SetRefColumn1(COleVariant(Column)); }
	void SetRefColumn1(LPCTSTR Column) { SetRefColumn1(COleVariant(Column)); }
	VARIANT GetRefColumn2();
	void SetRefColumn2(const VARIANT&);
	void SetRefColumn2(long Column) { SetRefColumn2(COleVariant(Column)); }
	void SetRefColumn2(LPCTSTR Column) { SetRefColumn2(COleVariant(Column)); }
	short GetLayerType();
	void SetLayerType(short);
	CString GetReferenceLayer();
	void SetReferenceLayer(LPCTSTR);
	CMapXCoordSys GetCoordSys();
	void SetCoordSys(LPDISPATCH);
	CString GetFilespec();
	void SetFilespec(LPCTSTR);
	short GetKeyLength();
	void SetKeyLength(short);
	BOOL GetOverwriteFile();
	void SetOverwriteFile(BOOL);
	long GetReferenceLayerField();
	void SetReferenceLayerField(long);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// CMapXMultivarCategories wrapper class

class CMapXMultivarCategories : public COleDispatchDriver
{
public:
	CMapXMultivarCategories() {}		// Calls COleDispatchDriver default constructor
	CMapXMultivarCategories(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXMultivarCategories(const CMapXMultivarCategories& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXMultivarCategory operator[](long Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();
	long GetCount();

// Operations
public:
	CMapXMultivarCategory Item(const VARIANT& Index);
	CMapXMultivarCategory Item(long Index) { return Item(COleVariant(Index)); }
};


/////////////////////////////////////////////////////////////////////////////
// CMapXRangeCategories wrapper class

class CMapXRangeCategories : public COleDispatchDriver
{
public:
	CMapXRangeCategories() {}		// Calls COleDispatchDriver default constructor
	CMapXRangeCategories(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXRangeCategories(const CMapXRangeCategories& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXRangeCategory operator[](long Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();
	CMapXRangeCategory GetAllOthersCategory();

// Operations
public:
	CMapXRangeCategory Item(const VARIANT& Index);
	CMapXRangeCategory Item(long Index) { return Item(COleVariant(Index)); }
};


/////////////////////////////////////////////////////////////////////////////
// CMapXIndividualValueCategories  wrapper class

class CMapXIndividualValueCategories : public COleDispatchDriver
{
public:
	CMapXIndividualValueCategories () {}		// Calls COleDispatchDriver default constructor
	CMapXIndividualValueCategories (LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXIndividualValueCategories (const CMapXIndividualValueCategories & dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXIndividualValueCategory operator[](long Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();
	CMapXIndividualValueCategory GetAllOthersCategory();

// Operations
public:
	CMapXIndividualValueCategory Item(const VARIANT& Index);
	CMapXIndividualValueCategory Item(long Index) { return Item(COleVariant(Index)); }
};


// CMapXRectangle wrapper class

class CMapXRectangle : public COleDispatchDriver
{
public:
	CMapXRectangle() {}		// Calls COleDispatchDriver default constructor
	CMapXRectangle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXRectangle(const CMapXRectangle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Rectangle.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	double GetXMin();
	double GetYMin();
	double GetXMax();
	double GetYMax();
	double GetHeight();
	double GetWidth();

// Operations
public:
	void Set(double X1, double Y1, double X2, double Y2);
	void Offset(double deltaX, double deltaY);
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFindFeature wrapper class

class CMapXFindFeature : public COleDispatchDriver
{
public:
	CMapXFindFeature() {}		// Calls COleDispatchDriver default constructor
	CMapXFindFeature(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFindFeature(const CMapXFindFeature& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetFeatureID();
	short GetType();
	void SetType(short);
	double GetLength();
	double GetCenterX();
	double GetCenterY();
	CMapXStyle GetStyle();
	void SetStyle(LPDISPATCH);
	CMapXRectangle GetBounds();
	CString GetCaption();
	void SetCaption(LPCTSTR);
	CMapXParts GetParts();
	double GetArea();
	CMapXLayer GetLayer();
	CMapXPoint GetPoint();
	void SetPoint(LPDISPATCH);
	CMapXPoint GetLabelPoint();
	double GetPerimeter();
	BOOL GetSmooth();
	void SetSmooth(BOOL);
	CString GetName();
	CString GetKeyValue();
	void SetKeyValue(LPCTSTR);
	CString GetFeatureKey();
	LPDISPATCH GetRegion();
	void SetRegion(LPDISPATCH);
	LPDISPATCH GetPolyline();
	void SetPolyline(LPDISPATCH);
	LPDISPATCH GetMultipoint();
	void SetMultipoint(LPDISPATCH);
	BOOL GetHasRegion();
	BOOL GetHasPolyline();
	BOOL GetHasMultipoint();
	short GetFindRC();

// Operations
public:
	void Update(const VARIANT& UpdateFeature, const VARIANT& RowValues);
	void Update()
	{
		Update(COptionalVariant(), COptionalVariant());
	}
	void Offset(double deltaX, double deltaY);
	void Attach(LPDISPATCH Map);
	LPDISPATCH Clone();
	VARIANT GetNodes(const VARIANT& CSys);
	void SetNodes(const VARIANT& CSys, const VARIANT& newValue);
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFindResult wrapper class

class CMapXFindResult : public COleDispatchDriver
{
public:
	CMapXFindResult() {}		// Calls COleDispatchDriver default constructor
	CMapXFindResult(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFindResult(const CMapXFindResult& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetExactMatch();
	BOOL GetSubstitute();
	BOOL GetAddressOutOfRange();
	BOOL GetIntersectionNotFound();
	BOOL GetMultipleMatches();
	BOOL GetRefineRegion();
	short GetFindRC();
	CMapXFindMatches GetMatches();
	CMapXFeature GetMatchedFeature();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXLayerFind wrapper class

class CMapXLayerFind : public COleDispatchDriver
{
public:
	CMapXLayerFind() {}		// Calls COleDispatchDriver default constructor
	CMapXLayerFind(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLayerFind(const CMapXLayerFind& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CMapXLayer GetRefineLayer();
	void SetRefineLayer(LPDISPATCH);
	BOOL GetAbbreviations();
	void SetAbbreviations(BOOL);
	BOOL GetClosestAddr();
	void SetClosestAddr(BOOL);
	BOOL GetOtherBoundary();
	void SetOtherBoundary(BOOL);
	CMapXField GetFindField();
	void SetFindField(LPDISPATCH);
	CMapXField GetRefineField();
	void SetRefineField(LPDISPATCH);
	CMapXDataset GetFindDataset();
	void SetFindDataset(LPDISPATCH);
	CMapXDataset GetRefineDataset();
	void SetRefineDataset(LPDISPATCH);
	long GetCloseMatchMax();
	void SetCloseMatchMax(long);

// Operations
public:
	CMapXFindFeature Search(LPCTSTR Address, const VARIANT& RefineBoundary);
	CMapXFindFeature Search(LPCTSTR Address, LPCTSTR RefineBoundary)
	{ return Search(Address, COleVariant(RefineBoundary)); }
	CMapXFindFeature Search(LPCTSTR Address)
	{ return Search(Address, COptionalVariant()); }

	CMapXFindResult SearchEx(LPCTSTR Address, const VARIANT& RefineBoundary);
	CMapXFindResult SearchEx(LPCTSTR Address, LPCTSTR RefineBoundary)
	{ return SearchEx(Address, COleVariant(RefineBoundary)); }
	CMapXFindResult SearchEx(LPCTSTR Address)
	{ return SearchEx(Address, COptionalVariant()); }
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFindMatch wrapper class

class CMapXFindMatch : public COleDispatchDriver
{
public:
	CMapXFindMatch() {}		// Calls COleDispatchDriver default constructor
	CMapXFindMatch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFindMatch(const CMapXFindMatch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetFeatureID();
	CString GetName();
	long GetScore();
	CString GetFeatureKey();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFindMatches wrapper class

class CMapXFindMatches : public COleDispatchDriver
{
public:
	CMapXFindMatches() {}		// Calls COleDispatchDriver default constructor
	CMapXFindMatches(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFindMatches(const CMapXFindMatches& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXFindMatch operator[](long Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();

// Operations
public:
	CMapXFindMatch Item(const VARIANT& Index);
	CMapXFindMatch Item(long Index) { return Item(COleVariant(Index)); }

};

/////////////////////////////////////////////////////////////////////////////
// CMapXGeoset wrapper class

class CMapXGeoset : public COleDispatchDriver
{
public:
	CMapXGeoset() {}		// Calls COleDispatchDriver default constructor
	CMapXGeoset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXGeoset(const CMapXGeoset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CMapXPoint GetCentroid();
	CString GetPathName();
	CString GetUserName();

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXGeosets wrapper class

class CMapXGeosets : public COleDispatchDriver
{
public:
	CMapXGeosets() {}		// Calls COleDispatchDriver default constructor
	CMapXGeosets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXGeosets(const CMapXGeosets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXGeoset operator[](long Index) { return Item(Index); }
	CMapXGeoset operator[](LPCTSTR Index) { return Item(Index); }

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();

// Operations
public:
	CMapXGeoset Item(const VARIANT& Index);
	CMapXGeoset Item(long Index) { return Item(COleVariant(Index)); }
	CMapXGeoset Item(LPCTSTR Index) { return Item(COleVariant(Index)); }
};

/////////////////////////////////////////////////////////////////////////////
// CMapXPoint wrapper class

class CMapXPoint : public COleDispatchDriver
{
public:
	CMapXPoint() {}		// Calls COleDispatchDriver default constructor
	CMapXPoint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXPoint(const CMapXPoint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Point.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	double GetX();
	double GetY();

// Operations
public:
	void Set(double X, double Y);
	void Offset(double deltaX, double deltaY);
};

/////////////////////////////////////////////////////////////////////////////
// CMapXPoints wrapper class

class CMapXPoints : public COleDispatchDriver
{
public:
	CMapXPoints() {}		// Calls COleDispatchDriver default constructor
	CMapXPoints(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXPoints(const CMapXPoints& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXPoint operator[](long Index) { return Item(Index); }

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Points.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	LPENUMVARIANT GetEnumerator();
	long GetCount();

// Operations
public:
	CMapXPoint Item(const VARIANT& Index);
	CMapXPoint Item(long Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	CMapXPoint Add(LPDISPATCH Point, const VARIANT& Position);
	CMapXPoint Add(LPDISPATCH Point, short Position) { return Add(Point, COleVariant(Position)); }
	CMapXPoint Add(LPDISPATCH Point) { return Add(Point, COptionalVariant()); }
	CMapXPoint AddXY(double X, double Y, const VARIANT& Position);
	CMapXPoint AddXY(double X, double Y) { return AddXY(X,Y, COptionalVariant()); }
	CMapXPoint AddXY(double X, double Y, short Position) { return AddXY(X,Y, COleVariant(Position)); }
	void RemoveAll();
	void GetXY(long Index, double *dX, double *dY);
	double X(long Index);
	double Y(long Index);

};

/////////////////////////////////////////////////////////////////////////////
// CMapXParts wrapper class

class CMapXParts : public COleDispatchDriver
{
public:
	CMapXParts() {}		// Calls COleDispatchDriver default constructor
	CMapXParts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXParts(const CMapXParts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXPoints operator[](long Index) { return Item(Index); }

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Parts.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();

// Operations
public:
	CMapXPoints Add(LPDISPATCH Points);
	CMapXPoints Add() { return Add(NULL); }
	CMapXPoints Item(const VARIANT& Index);
	CMapXPoints Item(long Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void RemoveAll();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXNotesViewInfo wrapper class

class CMapXNotesViewInfo : public COleDispatchDriver
{
public:
	CMapXNotesViewInfo() {}		// Calls COleDispatchDriver default constructor
	CMapXNotesViewInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXNotesViewInfo(const CMapXNotesViewInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".NotesViewInfo.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	CString GetServer();
	void SetServer(LPCTSTR);
	CString GetDatabase();
	void SetDatabase(LPCTSTR);
	CString GetView();
	void SetView(LPCTSTR);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// CMapXNotesQueryInfo wrapper class

class CMapXNotesQueryInfo : public COleDispatchDriver
{
public:
	CMapXNotesQueryInfo() {}		// Calls COleDispatchDriver default constructor
	CMapXNotesQueryInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXNotesQueryInfo(const CMapXNotesQueryInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".NotesQueryInfo.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	CString GetServer();
	void SetServer(LPCTSTR);
	CString GetDatabase();
	void SetDatabase(LPCTSTR);
	CString GetQuery();
	void SetQuery(LPCTSTR);
	CString GetBeginDate();
	void SetBeginDate(LPCTSTR);
	CString GetEndDate();
	void SetEndDate(LPCTSTR);
	BOOL GetFullTextSearch();
	void SetFullTextSearch(BOOL);
	CString GetDefaultStringValue();
	void SetDefaultStringValue(LPCTSTR);
	double GetDefaultNumericValue();
	void SetDefaultNumericValue(double);
	long GetMaxNumDocs();
	void SetMaxNumDocs(long);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXODBCQueryInfo wrapper class

class CMapXODBCQueryInfo : public COleDispatchDriver
{
public:
	CMapXODBCQueryInfo() {}		// Calls COleDispatchDriver default constructor
	CMapXODBCQueryInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXODBCQueryInfo(const CMapXODBCQueryInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".ODBCQueryInfo.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

	// Attributes
public:
	CString GetDataSource();
	void SetDataSource(LPCTSTR);
	CString GetSqlQuery();
	void SetSqlQuery(LPCTSTR);
	CString GetConnectString();
	void SetConnectString(LPCTSTR);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXOCIQueryInfo wrapper class

class CMapXOCIQueryInfo : public COleDispatchDriver
{
public:
	CMapXOCIQueryInfo() {}		// Calls COleDispatchDriver default constructor
	CMapXOCIQueryInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXOCIQueryInfo(const CMapXOCIQueryInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".OCIQueryInfo.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

	// Attributes
public:
	CString GetSqlQuery();
	void SetSqlQuery(LPCTSTR);
	CString GetConnectString();
	void SetConnectString(LPCTSTR);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXDatum wrapper class

class CMapXDatum : public COleDispatchDriver
{
public:
	CMapXDatum() {}		// Calls COleDispatchDriver default constructor
	CMapXDatum(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXDatum(const CMapXDatum& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Datum.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	short GetEllipsoid();
	double GetShiftX();
	double GetShiftY();
	double GetShiftZ();
	double GetRotateX();
	double GetRotateY();
	double GetRotateZ();
	double GetScaleAdjust();
	double GetPrimeMeridian();
	double GetSemiMajorAxis();
	double GetSemiMinorAxis();
	double GetFlattening();
	double GetEccentricity();

// Operations
public:
	void Set(short Ellipsoid, double ShiftX, double ShiftY, double ShiftZ, double RotateX, double RotateY, double RotateZ, double ScaleAdjust, double PrimeMeridian);
	void SetFromList(short DatumNum);
};
/////////////////////////////////////////////////////////////////////////////
// CMapXAffineTransform wrapper class

class CMapXAffineTransform : public COleDispatchDriver
{
public:
	CMapXAffineTransform() {}		// Calls COleDispatchDriver default constructor
	CMapXAffineTransform(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXAffineTransform(const CMapXAffineTransform& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".AffineTransform.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	short GetUnits();
	double GetA();
	double GetB();
	double GetC();
	double GetD();
	double GetE();
	double GetF();

// Operations
public:
	void Set(short Units, double A, double B, double C, double D, double E, double F);
};
/////////////////////////////////////////////////////////////////////////////
// CMapXCoordSys wrapper class

class CMapXCoordSys : public COleDispatchDriver
{
public:
	CMapXCoordSys() {}		// Calls COleDispatchDriver default constructor
	CMapXCoordSys(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXCoordSys(const CMapXCoordSys& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".CoordSys.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	short GetType();
	CMapXDatum GetDatum();
	short GetUnits();
	CMapXRectangle GetBounds();
	double GetOriginLongitude();
	double GetOriginLatitude();
	double GetStandardParallelOne();
	double GetStandardParallelTwo();
	double GetAzimuth();
	double GetScaleFactor();
	double GetFalseEasting();
	double GetFalseNorthing();
	double GetRange();
	CMapXAffineTransform GetAffineTransform();

// Operations
public:
	void Set(short Type, const VARIANT& Datum, const VARIANT& Units, const VARIANT& OriginLongitude, const VARIANT& OriginLatitude, const VARIANT& StandardParallelOne, const VARIANT& StandardParallelTwo, const VARIANT& Azimuth,
		const VARIANT& ScaleFactor, const VARIANT& FalseEasting, const VARIANT& FalseNorthing, const VARIANT& Range, const VARIANT& Bounds, const VARIANT& AffineTransform);
	
	void Set(short Type, LPDISPATCH Datum, const VARIANT& Units, const VARIANT& OriginLongitude, const VARIANT& OriginLatitude, const VARIANT& StandardParallelOne, const VARIANT& StandardParallelTwo, const VARIANT& Azimuth,
		const VARIANT& ScaleFactor, const VARIANT& FalseEasting, const VARIANT& FalseNorthing, const VARIANT& Range, const VARIANT& Bounds, const VARIANT& AffineTransform)
		{
			Set(Type, COleVariantDispatch(Datum), Units, OriginLongitude, OriginLatitude, StandardParallelOne,
				StandardParallelTwo, Azimuth, ScaleFactor, FalseEasting, FalseNorthing, Range, Bounds,
				AffineTransform);
		}

	void Set(short Type, short Datum, const VARIANT& Units, const VARIANT& OriginLongitude, const VARIANT& OriginLatitude, const VARIANT& StandardParallelOne, const VARIANT& StandardParallelTwo, const VARIANT& Azimuth,
		const VARIANT& ScaleFactor, const VARIANT& FalseEasting, const VARIANT& FalseNorthing, const VARIANT& Range, const VARIANT& Bounds, const VARIANT& AffineTransform)
		{
			Set(Type, COleVariant(Datum), Units, OriginLongitude, OriginLatitude, StandardParallelOne,
				StandardParallelTwo, Azimuth, ScaleFactor, FalseEasting, FalseNorthing, Range, Bounds,
				AffineTransform);
		}

	BOOL PickCoordSys(const VARIANT& HelpFile, const VARIANT& HelpID);
	BOOL PickCoordSys(LPCTSTR HelpFile, UINT HelpID=HELP_FINDER)
		{ return PickCoordSys(COleVariant(HelpFile), COleVariant((long)HelpID)); }
	BOOL PickCoordSys()
		{ return PickCoordSys(COptionalVariant(), COptionalVariant()); }

	CMapXCoordSys Clone();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXBitmapSymbol wrapper class

class CMapXBitmapSymbol : public COleDispatchDriver
{
public:
	CMapXBitmapSymbol() {}		// Calls COleDispatchDriver default constructor
	CMapXBitmapSymbol(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXBitmapSymbol(const CMapXBitmapSymbol& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetName();
};


/////////////////////////////////////////////////////////////////////////////
// CMapXBitmapSymbols wrapper class

class CMapXBitmapSymbols : public COleDispatchDriver
{
public:
	CMapXBitmapSymbols() {}		// Calls COleDispatchDriver default constructor
	CMapXBitmapSymbols(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXBitmapSymbols(const CMapXBitmapSymbols& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".BitmapSymbols.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	LPENUMVARIANT GetEnumerator();
	long GetCount();
	CMapXBitmapSymbol operator[](long Index) { return Item(Index); }

// Operations
public:
	CMapXBitmapSymbol Item(const VARIANT& Index);
	CMapXBitmapSymbol Item(long Index) { return Item(COleVariant(Index)); }
	void Refresh();
	void Unload();


// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFeatureFactory wrapper class

class CMapXFeatureFactory : public COleDispatchDriver
{
public:
	CMapXFeatureFactory() {}		// Calls COleDispatchDriver default constructor
	CMapXFeatureFactory(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFeatureFactory(const CMapXFeatureFactory& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CMapXFeature BufferFeatures(LPDISPATCH Source, double Distance, const VARIANT& Units, const VARIANT& Resolution);
	CMapXFeature BufferFeatures(LPDISPATCH Source, double Distance, short Units, short Resolution)
		{ return BufferFeatures(Source, Distance, COleVariant(Units), COleVariant(Resolution));}
	CMapXFeature BufferFeatures(LPDISPATCH Source, double Distance, short Units)
		{ return BufferFeatures(Source, Distance, COleVariant(Units), COptionalVariant());}

	CMapXFeature CombineFeatures(LPDISPATCH Source1, const VARIANT& Source2);
	CMapXFeature CombineFeatures(LPDISPATCH Source1)
		{ return CombineFeatures(Source1, COptionalVariant()); }

	CMapXFeature IntersectFeatures(LPDISPATCH Source1, const VARIANT& Source2);
	CMapXFeature IntersectFeatures(LPDISPATCH Source1)
		{ return IntersectFeatures(Source1, COptionalVariant()); }

	CMapXFeature EraseFeature(LPDISPATCH Feature, LPDISPATCH EraserFeature);

	CMapXFeature CreateSymbol(const VARIANT& Point, const VARIANT& Style);
	CMapXFeature CreateSymbol(const VARIANT& Point)
		{ return CreateSymbol(Point, COptionalVariant());}
	CMapXFeature CreateSymbol()
		{ return CreateSymbol(COptionalVariant(), COptionalVariant());}

	CMapXFeature CreateRegion(const VARIANT& Points, const VARIANT& Style);
	CMapXFeature CreateRegion(const VARIANT& Points)
		{ return CreateRegion(Points, COptionalVariant());}
	CMapXFeature CreateRegion()
		{ return CreateRegion(COptionalVariant(), COptionalVariant());}

	CMapXFeature CreateLine(const VARIANT& Points, const VARIANT& Style);
	CMapXFeature CreateLine(const VARIANT& Points)
		{ return CreateLine(Points, COptionalVariant());}
	CMapXFeature CreateLine()
		{ return CreateLine(COptionalVariant(), COptionalVariant());}

	CMapXFeature CreateText(const VARIANT& Point, const VARIANT& Caption, const VARIANT& Position, const VARIANT& Style);
	CMapXFeature CreateText(const VARIANT& Point, LPCTSTR Caption, short Position, const VARIANT& Style)
		{ return CreateText(Point, COleVariant(Caption), COleVariant(Position), Style);}
	CMapXFeature CreateText(const VARIANT& Point, LPCTSTR Caption=_T(""), short Position=miPositionTL)
		{ return CreateText(Point, COleVariant(Caption), COleVariant(Position), COptionalVariant());}
	CMapXFeature CreateText(LPCTSTR Caption=_T(""), short Position=miPositionTL)
		{ return CreateText(COptionalVariant(), COleVariant(Caption), COleVariant(Position), COptionalVariant());}

	CMapXFeature CreateArc(LPDISPATCH Point1, LPDISPATCH Point2, const VARIANT& Angle, const VARIANT& Distance, const VARIANT& Resolution, const VARIANT& Style);
	CMapXFeature CreateArc(LPDISPATCH Point1, LPDISPATCH Point2, double Angle, double Distance, short Resolution)
		{ return CreateArc(Point1, Point2, COleVariant(Angle), COleVariant(Distance), COleVariant(Resolution), COptionalVariant());}
	CMapXFeature CreateArc(LPDISPATCH Point1, LPDISPATCH Point2, double Angle=90.0, double Distance=1.0)
		{ return CreateArc(Point1, Point2, COleVariant(Angle), COleVariant(Distance), COptionalVariant(), COptionalVariant());}

	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, const VARIANT& Angle, const VARIANT& Resolution, const VARIANT& Style);
	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, double Angle=0.0)
	{ return CreateEllipticalRegion(Rectangle, COleVariant(Angle), COptionalVariant(), COptionalVariant());}
	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, short Resolution)
	{ return CreateEllipticalRegion(Rectangle, COptionalVariant(), COleVariant(Resolution), COptionalVariant());}
	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, LPDISPATCH Style)
	{
		return CreateEllipticalRegion(Rectangle, COptionalVariant(), COptionalVariant(), COleVariantDispatch(Style));
	}
	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, double Angle, short Resolution)
	{ return CreateEllipticalRegion(Rectangle, COleVariant(Angle), COleVariant(Resolution), COptionalVariant());}
	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, double Angle, LPDISPATCH Style)
	{
		return CreateEllipticalRegion(Rectangle, COleVariant(Angle), COptionalVariant(), COleVariantDispatch(Style));
	}
	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, short Resolution, LPDISPATCH Style)
	{
		return CreateEllipticalRegion(Rectangle, COptionalVariant(), COleVariant(Resolution), COleVariantDispatch(Style));
	}
	CMapXFeature CreateEllipticalRegion(LPDISPATCH Rectangle, double Angle, short Resolution, LPDISPATCH Style)
	{
		return CreateEllipticalRegion(Rectangle, COleVariant(Angle), COleVariant(Resolution), COleVariantDispatch(Style));
	}

	CMapXFeature CreateCircularRegion(short Type, LPDISPATCH Point, double Distance, const VARIANT& Units, const VARIANT& Resolution, const VARIANT& Style);
	CMapXFeature CreateCircularRegion(short Type, LPDISPATCH Point, double Distance, short Units, short Resolution)
		{ return CreateCircularRegion(Type, Point, Distance, COleVariant(Units), COleVariant(Resolution), COptionalVariant());}
	CMapXFeature CreateCircularRegion(short Type, LPDISPATCH Point, double Distance, short Units)
		{ return CreateCircularRegion(Type, Point, Distance, COleVariant(Units), COptionalVariant(), COptionalVariant());}

	BOOL IntersectionTest(LPDISPATCH Feature1, LPDISPATCH Feature2, const VARIANT& Flag);
	BOOL IntersectionTest(LPDISPATCH Feature1, LPDISPATCH Feature2, short Flag=miIntersectFeature)
		{ return IntersectionTest(Feature1, Feature2, COleVariant(Flag)); }

	CMapXPoints IntersectionPoints(LPDISPATCH Feature1, LPDISPATCH Feature2, const VARIANT& Flag);
	CMapXPoints IntersectionPoints(LPDISPATCH Feature1, LPDISPATCH Feature2, short Flag=miIntersectAll)
		{ return IntersectionPoints(Feature1, Feature2, COleVariant(Flag)); }

	CMapXFeature CreateCollectionFeature(const VARIANT& Source1, const VARIANT& Source2, const VARIANT& Source3);
	CMapXFeature CreateCollectionFeature(const VARIANT& Source1, const VARIANT& Source2)
		{ return CreateCollectionFeature(Source1, Source2, COptionalVariant()); }
	CMapXFeature CreateCollectionFeature(const VARIANT& Source1)
		{ return CreateCollectionFeature(Source1, COptionalVariant(), COptionalVariant()); }
	CMapXFeature CreateCollectionFeature()
		{ return CreateCollectionFeature(COptionalVariant(), COptionalVariant(), COptionalVariant()); }

	CMapXFeature CreateMultipoint(const VARIANT& Points, const VARIANT& Style);
	CMapXFeature CreateMultipoint(const VARIANT& Points)
		{ return CreateMultipoint(Points, COptionalVariant());}
	CMapXFeature CreateMultipoint()
		{ return CreateMultipoint(COptionalVariant(), COptionalVariant());}

};

class CMapXResolveObject : public COleDispatchDriver
{
public:
	CMapXResolveObject() {}		// Calls COleDispatchDriver default constructor
	CMapXResolveObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXResolveObject(const CMapXResolveObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}


// Attributes
public:
	CString GetTableName();
	long GetSourceMatch();
	long GetTableMatch();

// Operations
public:
};

class CMapXResolveObjects : public COleDispatchDriver
{
public:
	CMapXResolveObjects() {}		// Calls COleDispatchDriver default constructor
	CMapXResolveObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXResolveObjects(const CMapXResolveObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}


// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();
	CMapXResolveObject operator[](long Index) { return Item(Index); }

// Operations
public:
	CMapXResolveObject Item(const VARIANT& Index);
	CMapXResolveObject Item(long Index) { return Item(COleVariant(Index)); }
};

/////////////////////////////////////////////////////////////////////////////
// CMapXLayerInfo wrapper class

class CMapXLayerInfo : public COleDispatchDriver
{
public:
	CMapXLayerInfo() {}		// Calls COleDispatchDriver default constructor
	CMapXLayerInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLayerInfo(const CMapXRowValue& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".LayerInfo.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	short GetType();
	void SetType(short);

// Operations
public:
	void AddParameter(LPCTSTR ParamName, const VARIANT& Param);
};


/////////////////////////////////////////////////////////////////////////////
// CMapXVariable wrapper class

class CMapXVariable : public COleDispatchDriver
{
public:
	CMapXVariable() {}		// Calls COleDispatchDriver default constructor
	CMapXVariable(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXVariable(const CMapXVariable& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetName();
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	void SetValue(short n)
		{ SetValue(COleVariant(n)); }
	void SetValue(long n)
		{ SetValue(COleVariant(n)); }
	void SetValue(double d)
		{ SetValue(COleVariant(d)); }
	void SetValue(const TCHAR *pszValue)
		{ SetValue(COleVariant(pszValue)); }

// Operations
public:
};


// CMapXVariables wrapper class

class CMapXVariables : public COleDispatchDriver
{
public:
	CMapXVariables() {}		// Calls COleDispatchDriver default constructor
	CMapXVariables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXVariables(const CMapXVariables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	const CLSID& GetClsid() const
	{
		static bool bInitialized = false;
		static CLSID clsid;
		if(!bInitialized)
		{
			clsid = GetClassID(MAPX_PROGRAM_ID_PREFIX _T(".Variables.") MAPX_VERSION);
			bInitialized = true;
		}
		return clsid;
	}

// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();
	CMapXVariable operator[](long Index) { return Item(Index); }
	CMapXVariable operator[](LPCTSTR Index) { return Item(Index); }

// Operations
public:
	CMapXVariable Add(LPCTSTR Name, const VARIANT& Value);
	CMapXVariable Add(LPCTSTR Name, long Value) 
		{ return Add(Name, COleVariant(Value)); }
	CMapXVariable Add(LPCTSTR Name, short Value) 
		{ return Add(Name, COleVariant(Value)); }
	CMapXVariable Add(LPCTSTR Name, double Value) 
		{ return Add(Name, COleVariant(Value)); }
	CMapXVariable Add(LPCTSTR Name, LPCTSTR Value) 
		{ return Add(Name, COleVariant(Value)); }

	
	CMapXVariable Item(const VARIANT& Index);
	CMapXVariable Item(long Index) { return Item(COleVariant(Index)); }
	CMapXVariable Item(LPCTSTR Index) { return Item(COleVariant(Index)); }
	void Remove(const VARIANT& Index);
	void Remove(long Index) { Remove(COleVariant(Index)); }
	void Remove(LPCTSTR Index) { Remove(COleVariant(Index)); }
	void RemoveAll();
	CMapXVariables Clone();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXBoundsConstraint wrapper class

class CMapXBoundsConstraint : public COleDispatchDriver
{
public:
	CMapXBoundsConstraint() {}		// Calls COleDispatchDriver default constructor
	CMapXBoundsConstraint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXBoundsConstraint(const CMapXBoundsConstraint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetEnabled();
	CMapXRectangle GetBounds();
	void SetBounds(LPDISPATCH);

// Operations
public:
	void Enable();
	void Disable();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXFeaturesConstraint wrapper class

class CMapXFeaturesConstraint : public COleDispatchDriver
{
public:
	CMapXFeaturesConstraint() {}		// Calls COleDispatchDriver default constructor
	CMapXFeaturesConstraint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXFeaturesConstraint(const CMapXFeaturesConstraint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetEnabled();
	CMapXFeatures GetFeatures();
	void SetFeatures(LPDISPATCH);

// Operations
public:
	void Enable();
	void Disable();
};

/////////////////////////////////////////////////////////////////////////////
// CMapXAllFeaturesConstraint wrapper class

class CMapXAllFeaturesConstraint : public COleDispatchDriver
{
public:
	CMapXAllFeaturesConstraint() {}		// Calls COleDispatchDriver default constructor
	CMapXAllFeaturesConstraint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXAllFeaturesConstraint(const CMapXAllFeaturesConstraint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetEnabled();

// Operations
public:
	void Enable();
	void Disable();
};


/////////////////////////////////////////////////////////////////////////////
// CMapXLabel wrapper class

class CMapXLabel : public COleDispatchDriver
{
public:
	CMapXLabel() {}		// Calls COleDispatchDriver default constructor
	CMapXLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLabel(const CMapXLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	
// Attributes
public:
	double GetAnchorX();
	void SetAnchorX(double);
	double GetAnchorY();
	void SetAnchorY(double);
	short GetAngle();
	void SetAngle(short);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	long GetLineType();
	void SetLineType(long);
	BOOL GetMultiSegment();
	void SetMultiSegment(BOOL);
	long GetOffset();
	void SetOffset(long);
	short GetPosition();
	void SetPosition(short);
	BOOL GetSelected();
	void SetSelected(BOOL);
	LPDISPATCH GetStyle();
	void SetStyle(LPDISPATCH);
	BOOL GetVisible();
	void SetVisible(BOOL);
	BOOL GetDrawn();
	BOOL GetEdited();
	BOOL GetEditedAnchor();
	BOOL GetEditedAngle();
	BOOL GetEditedCaption();
	BOOL GetEditedLineStyle();
	BOOL GetEditedLineType();
	BOOL GetEditedMultiSegment();
	BOOL GetEditedOffset();
	BOOL GetEditedPosition();
	BOOL GetEditedTextStyle();
	BOOL GetEditedVisible();
	LPDISPATCH GetLayer();
	CString GetFeatureKey();
};


/////////////////////////////////////////////////////////////////////////////
// CMapXLabels wrapper class

class CMapXLabels : public COleDispatchDriver
{
public:
	CMapXLabels() {}		// Calls COleDispatchDriver default constructor
	CMapXLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapXLabels(const CMapXLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CMapXLabel operator[](long Index) { return Item(Index); }

	// Attributes
public:
	LPENUMVARIANT GetEnumerator();

	long GetCount();

// Operations
public:
	CMapXLabel Item(const VARIANT& Index);
	CMapXLabel Item(long Index) { return Item(COleVariant(Index)); }
};

#endif // __MAPX_H__/////////////////////////////////////////////////////////////////////////////

