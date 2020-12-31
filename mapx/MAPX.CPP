#include "stdafx.h"
#include <afxconv.h>
#include "mapx.h"

/////////////////////////////////////////////////////////////////////////////
// CMapX

#ifdef CWND_MAPX
IMPLEMENT_DYNCREATE(CMapX, CWnd)
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapX properties

CString CMapX::GetDataSetGeoField()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapX::SetDataSetGeoField(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CMapX::GetVersion()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

OLE_HANDLE CMapX::GetHWnd()
{
	OLE_HANDLE result;
	GetProperty(DISPID_HWND, VT_I4, (void*)&result);
	return result;
}

CMapXAnnotations CMapX::GetAnnotations()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return CMapXAnnotations(result);
}

CMapXLayers CMapX::GetLayers()
{
	LPDISPATCH result;
	GetProperty(0x5, VT_DISPATCH, (void*)&result);
	return CMapXLayers(result);
}

BOOL CMapX::GetAutoRedraw()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetAutoRedraw(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

double CMapX::GetZoom()
{
	double result;
	GetProperty(0x7, VT_R8, (void*)&result);
	return result;
}

void CMapX::SetZoom(double propVal)
{
	SetProperty(0x7, VT_R8, propVal);
}

double CMapX::GetCenterX()
{
	double result;
	GetProperty(0x8, VT_R8, (void*)&result);
	return result;
}

void CMapX::SetCenterX(double propVal)
{
	SetProperty(0x8, VT_R8, propVal);
}

double CMapX::GetCenterY()
{
	double result;
	GetProperty(0x9, VT_R8, (void*)&result);
	return result;
}

void CMapX::SetCenterY(double propVal)
{
	SetProperty(0x9, VT_R8, propVal);
}

CString CMapX::GetGeoSet()
{
	CString result;
	GetProperty(0xa, VT_BSTR, (void*)&result);
	return result;
}

void CMapX::SetGeoSet(LPCTSTR propVal)
{
	SetProperty(0xa, VT_BSTR, propVal);
}

double CMapX::GetGeoSetWidth()
{
	double result;
	GetProperty(0xb, VT_R8, (void*)&result);
	return result;
}

double CMapX::GetMapPaperHeight()
{
	double result;
	GetProperty(0xc, VT_R8, (void*)&result);
	return result;
}

double CMapX::GetMapPaperWidth()
{
	double result;
	GetProperty(0xd, VT_R8, (void*)&result);
	return result;
}

short CMapX::GetMaxSearchTime()
{
	short result;
	GetProperty(0xe, VT_I2, (void*)&result);
	return result;
}

void CMapX::SetMaxSearchTime(short propVal)
{
	SetProperty(0xe, VT_I2, propVal);
}

long CMapX::GetPaperUnit()
{
	long result;
	GetProperty(0xf, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetPaperUnit(long propVal)
{
	SetProperty(0xf, VT_I4, propVal);
}

BOOL CMapX::GetPreferCompactLegends()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetPreferCompactLegends(BOOL propVal)
{
	SetProperty(0x10, VT_BOOL, propVal);
}

CMapXStyle CMapX::GetDefaultStyle()
{
	LPDISPATCH result;
	GetProperty(0x11, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapX::SetDefaultStyle(LPDISPATCH propVal)
{
	SetProperty(0x11, VT_DISPATCH, propVal);
}

CString CMapX::GetGeoDictionary()
{
	CString result;
	GetProperty(0x12, VT_BSTR, (void*)&result);
	return result;
}

void CMapX::SetGeoDictionary(LPCTSTR propVal)
{
	SetProperty(0x12, VT_BSTR, propVal);
}

long CMapX::GetDataSetTheme()
{
	long result;
	GetProperty(0x13, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetDataSetTheme(long propVal)
{
	SetProperty(0x13, VT_I4, propVal);
}

long CMapX::GetCurrentTool()
{
	long result;
	GetProperty(0x14, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetCurrentTool(long propVal)
{
	SetProperty(0x14, VT_I4, propVal);
}

long CMapX::GetMousePointer()
{
	long result;
	GetProperty(0x15, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetMousePointer(long propVal)
{
	SetProperty(0x15, VT_I4, propVal);
}

CMapXDatasets CMapX::GetDatasets()
{
	LPDISPATCH result;
	GetProperty(0x16, VT_DISPATCH, (void*)&result);
	return CMapXDatasets(result);
}

CMapXTitle CMapX::GetTitle()
{
	LPDISPATCH result;
	GetProperty(0x17, VT_DISPATCH, (void*)&result);
	return CMapXTitle(result);
}

CString CMapX::GetTitleText()
{
	CString result;
	GetProperty(0x18, VT_BSTR, (void*)&result);
	return result;
}

void CMapX::SetTitleText(LPCTSTR propVal)
{
	SetProperty(0x18, VT_BSTR, propVal);
}

long CMapX::GetMapUnit()
{
	long result;
	GetProperty(0x19, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetMapUnit(long propVal)
{
	SetProperty(0x19, VT_I4, propVal);
}

double CMapX::GetRotation()
{
	double result;
	GetProperty(0x1a, VT_R8, (void*)&result);
	return result;
}

void CMapX::SetRotation(double propVal)
{
	SetProperty(0x1a, VT_R8, propVal);
}

CMapXGeosets CMapX::GetGeosets()
{
	LPDISPATCH result;
	GetProperty(0x1b, VT_DISPATCH, (void*)&result);
	return CMapXGeosets(result);
}

long CMapX::GetAreaUnit()
{
	long result;
	GetProperty(0x1c, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetAreaUnit(long propVal)
{
	SetProperty(0x1c, VT_I4, propVal);
}

CMapXRectangle CMapX::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x1d, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

void CMapX::SetBounds(LPDISPATCH propVal)
{
	SetProperty(0x1d, VT_DISPATCH, propVal);
}

CMapXCoordSys CMapX::GetDisplayCoordSys()
{
	LPDISPATCH result;
	GetProperty(0x1e, VT_DISPATCH, (void*)&result);
	return CMapXCoordSys(result);
}

void CMapX::SetDisplayCoordSys(LPDISPATCH propVal)
{
	SetProperty(0x1e, VT_DISPATCH, propVal);
}

CMapXCoordSys CMapX::GetNumericCoordSys()
{
	LPDISPATCH result;
	GetProperty(0x1f, VT_DISPATCH, (void*)&result);
	return CMapXCoordSys(result);
}

void CMapX::SetNumericCoordSys(LPDISPATCH propVal)
{
	SetProperty(0x1f, VT_DISPATCH, propVal);
}

BOOL CMapX::GetExportSelection()
{
	BOOL result;
	GetProperty(0x20, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetExportSelection(BOOL propVal)
{
	SetProperty(0x20, VT_BOOL, propVal);
}

CMapXStyle CMapX::GetSelectionStyle()
{
	LPDISPATCH result;
	GetProperty(0x21, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapX::SetSelectionStyle(LPDISPATCH propVal)
{
	SetProperty(0x21, VT_DISPATCH, propVal);
}

CMapXFeatureFactory CMapX::GetFeatureFactory()
{
	LPDISPATCH result;
	GetProperty(0x31, VT_DISPATCH, (void*)&result);
	return CMapXFeatureFactory(result);
}

long CMapX::GetDefaultConversionResolution()
{
	long result;
	GetProperty(0x32, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetDefaultConversionResolution(long propVal)
{
	SetProperty(0x32, VT_I4, propVal);
}

OLE_COLOR CMapX::GetBackColor()
{
	OLE_COLOR result;
	GetProperty(DISPID_BACKCOLOR, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetBackColor(OLE_COLOR propVal)
{
	SetProperty(DISPID_BACKCOLOR, VT_I4, propVal);
}

long CMapX::GetMousewheelSupport()
{
	long result;
	GetProperty(0x33, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetMousewheelSupport(long propVal)
{
	SetProperty(0x33, VT_I4, propVal);
}

BOOL CMapX::GetMatchNumericFields()
{
	BOOL result;
	GetProperty(0x34, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetMatchNumericFields(BOOL propVal)
{
	SetProperty(0x34, VT_BOOL, propVal);
}
	
double CMapX::GetMapScreenWidth()
{
	double result;
	GetProperty(0x35, VT_R8, (void*)&result);
	return result;
}

double CMapX::GetMapScreenHeight()
{
	double result;
	GetProperty(0x36, VT_R8, (void*)&result);
	return result;
}

long CMapX::GetRedrawInterval()
{
 	long result;
	GetProperty(0x37, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetRedrawInterval(long propVal)
{
	SetProperty(0x37, VT_I4, propVal);
}

CString CMapX::GetSearchPath()
{
	CString result;
	GetProperty(0x38, VT_BSTR, (void*)&result);
	return result;
}

void CMapX::SetSearchPath(LPCTSTR propVal)
{
	SetProperty(0x38, VT_BSTR, propVal);
}

short CMapX::GetMatchThreshold()
{
 	short result;
	GetProperty(0x39, VT_I2, (void*)&result);
	return result;
}

void CMapX::SetMatchThreshold(short propVal)
{
	SetProperty(0x39, VT_I2, propVal);
}

BOOL CMapX::GetWaitCursorEnabled()
{
 	BOOL result;
	GetProperty(0x3a, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetWaitCursorEnabled(BOOL propVal)
{
	SetProperty(0x3a, VT_BOOL, propVal);
}

BOOL CMapX::GetPanAnimationLayer()
{
 	BOOL result;
	GetProperty(0x3c, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetPanAnimationLayer(BOOL propVal)
{
	SetProperty(0x3c, VT_BOOL, propVal);
}

long CMapX::GetInfotipPopupDelay()
{
	long result;
	GetProperty(0x3d, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetInfotipPopupDelay(long propVal)
{
	SetProperty(0x3d, VT_I4, propVal);
}

CString CMapX::GetMouseIcon()
{
	CString result;
	GetProperty(0x3e, VT_BSTR, (void*)&result);
	return result;
}

void CMapX::SetMouseIcon(LPCTSTR propVal)
{
	SetProperty(0x3e, VT_BSTR, propVal);
}

BOOL CMapX::GetInfotipSupport()
{
 	BOOL result;
	GetProperty(0x3f, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetInfotipSupport(BOOL propVal)
{
	SetProperty(0x3f, VT_BOOL, propVal);
}

short CMapX::GetFeatureEditMode()
{
	short result;
	GetProperty(0x41, VT_I2, (void*)&result);
	return result;
}

void CMapX::SetFeatureEditMode(short propVal)
{
	SetProperty(0x41, VT_I2, propVal);
}

BOOL CMapX::GetReuseEquivalentOnRestore()
{
 	BOOL result;
	GetProperty(0x45, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetReuseEquivalentOnRestore(BOOL b)
{
	SetProperty(0x45, VT_BOOL, b);
}


long CMapX::GetCheckEscapeKeyInterval()
{
	long result;
	GetProperty(0x43, VT_I4, (void*)&result);
	return result;
}

void CMapX::SetCheckEscapeKeyInterval(long propVal)
{
	SetProperty(0x43, VT_I4, propVal);
}

BOOL CMapX::GetSnapToNodeSupport()
{
	BOOL result;
	GetProperty(0x46, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetSnapToNodeSupport(BOOL b)
{
	SetProperty(0x46, VT_BOOL, b);
}

short CMapX::GetSnapTolerance()
{
	short result;
	GetProperty(0x47, VT_I2, (void*)&result);
	return result;
}

void CMapX::SetSnapTolerance(short propVal)
{
	SetProperty(0x47, VT_I2, propVal);
}

BOOL CMapX::GetDynamicSelectionSupport()
{
	BOOL result;
	GetProperty(0x48, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetDynamicSelectionSupport(BOOL b)
{
	SetProperty(0x48, VT_BOOL, b);
}

BOOL CMapX::GetLabelsAreEditable()
{
	BOOL result;
	GetProperty(0x4C, VT_BOOL, (void*)&result);
	return result;
}

void CMapX::SetLabelsAreEditable(BOOL b)
{
	SetProperty(0x4C, VT_BOOL, b);
}

/////////////////////////////////////////////////////////////////////////////
// CMapX operations

void CMapX::ConvertCoord(float* ScreenX, float* ScreenY, double* MapX, double* MapY, short Direction)
{
	static BYTE parms[] =
		VTS_PR4 VTS_PR4 VTS_PR8 VTS_PR8 VTS_I2;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ScreenX, ScreenY, MapX, MapY, Direction);
}

void CMapX::ZoomTo(double Zoom, double X, double Y)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Zoom, X, Y);
}

void CMapX::CreateCustomTool(
	short ToolNumber, 
	short Type, 
	const VARIANT& Cursor, 
	const VARIANT& ShiftCursor, 
	const VARIANT& CtrlCursor, 
	const VARIANT& bInfoTips)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ToolNumber, Type, &Cursor, &CtrlCursor, &ShiftCursor, &bInfoTips);
}

double CMapX::Distance(double X1, double Y1, double X2, double Y2)
{
	double result;
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		X1, Y1, X2, Y2);
	return result;
}

void CMapX::Refresh()
{
	InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapX::PrintMap(long hDC, long X, long Y, long W, long H)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, X, Y, W, H);
}

void CMapX::ExportMap(LPCTSTR Destination, short Format, const VARIANT& Width, const VARIANT& Height)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Destination, Format, &Width, &Height);
}

void CMapX::PropertyPage()
{
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapX::ConvertCoordV(VARIANT* ScreenX, VARIANT* ScreenY, VARIANT* MapX, VARIANT* MapY, short Direction)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_I2;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ScreenX, ScreenY, MapX, MapY, Direction);
}

void CMapX::SetSize(long Width, long Height)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Width, Height);
}

BOOL CMapX::IsPointVisible(double X, double Y)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		X, Y);
	return result;
}

BOOL CMapX::ClipLine(double* X1, double* Y1, double* X2, double* Y2)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		X1, Y1, X2, Y2);
	return result;
}

BOOL CMapX::ClipLineV(VARIANT* X1, VARIANT* Y1, VARIANT* X2, VARIANT* Y2)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		X1, Y1, X2, Y2);
	return result;
}

void CMapX::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


void CMapX::SaveMapAsGeoset(LPCTSTR Name, LPCTSTR Filespec)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		Name, Filespec);
}

LPDISPATCH CMapX::GetDispatch(BOOL bAddRef)
{
#ifdef CWND_MAPX
	LPUNKNOWN pUnk = GetControlUnknown();
#else
	LPUNKNOWN pUnk = m_lpDispatch;
#endif
	LPDISPATCH pDispatch;

	if ((pUnk != NULL) &&	SUCCEEDED(pUnk->QueryInterface(IID_IDispatch, (LPVOID*)&pDispatch))) {
		ASSERT(pDispatch != NULL);
		if (!bAddRef) {
			pDispatch->Release();
		}
		return pDispatch;
	}
	return NULL;
}

void CMapX::Pan(float ScreenX, float ScreenY)
{
	static BYTE parms[] =
		VTS_R4 VTS_R4;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ScreenX, ScreenY);
}

CString CMapX::MilitaryGridReferenceFromPoint(const VARIANT& X, const VARIANT& Y)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x49, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&X, &Y);
	return result;
}

BOOL CMapX::MilitaryGridReferenceToPoint(LPCTSTR strMilGridRef, double* X, double* Y)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PR8 VTS_PR8;
	InvokeHelper(0x4a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		strMilGridRef, X, Y);
	return result;
}

BOOL CMapX::MilitaryGridReferenceToPointV(LPCTSTR strMilGridRef, VARIANT* X, VARIANT* Y)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x4b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		strMilGridRef, X, Y);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXDatasets properties

LPENUMVARIANT CMapXDatasets::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXDatasets::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

BOOL CMapXDatasets::GetBuildSourceRows()
{
 	BOOL result;
	GetProperty(0x7, VT_BOOL, &result);
	return result;
}

void CMapXDatasets::SetBuildSourceRows(BOOL b)
{
	SetProperty(0x7, VT_BOOL, b);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXDatasets operations

CMapXDataset CMapXDatasets::Add(long Type, const VARIANT& SourceData, const VARIANT& Name, const VARIANT& GeoField, const VARIANT& SecondaryGeoField, const VARIANT& BindLayer, const VARIANT& Fields, const VARIANT& Dynamic)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, &SourceData, &Name, &GeoField, &SecondaryGeoField, &BindLayer, &Fields, &Dynamic);
	return CMapXDataset(result);
}

CMapXDataset CMapXDatasets::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXDataset(result);
}

void CMapXDatasets::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

CMapXDataset CMapXDatasets::Restore(LPCTSTR Name, const VARIANT& SourceData)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &SourceData);
	return CMapXDataset(result);
}

void CMapXDatasets::RemoveAll()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLayers properties

LPENUMVARIANT CMapXLayers::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXLayers::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

CMapXRectangle CMapXLayers::GetClippedBounds()
{
	LPDISPATCH result;
	GetProperty(0x10, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLayers operations

void CMapXLayers::ClearSelection()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CMapXLayers::Move(short From, short To)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		From, To);
	return result;
}

CMapXLayer CMapXLayers::Add(const VARIANT& LayerInfo, const VARIANT& Position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&LayerInfo, &Position);
	return CMapXLayer(result);
}

void CMapXLayers::AddGeoSetLayers(LPCTSTR GeoSetName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 GeoSetName);
}

CMapXLayer CMapXLayers::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXLayer(result);
}

void CMapXLayers::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

CMapXLayer CMapXLayers::AddUserDrawLayer(LPCTSTR Name, short Position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I2;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, Position);
	return CMapXLayer(result);
}

CMapXLayer CMapXLayers::GetAnimationLayer()
{
	LPDISPATCH result;
	GetProperty(0x9, VT_DISPATCH, (void*)&result);
	return CMapXLayer(result);
}

void CMapXLayers::SetAnimationLayer(LPDISPATCH propVal)
{
	SetProperty(0x9, VT_DISPATCH, propVal);
}

CMapXRectangle CMapXLayers::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0xc, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

CMapXLayer CMapXLayers::CreateLayer(LPCTSTR Name, const VARIANT& Filespec, const VARIANT& Position, const VARIANT& KeyLength, const VARIANT& CoordSys)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &Filespec, &Position, &KeyLength, &CoordSys);
	return CMapXLayer(result);
}

BOOL CMapXLayers::LayersDlg(const VARIANT& HelpFile, const VARIANT& HelpID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&HelpFile, &HelpID);
	return result;
}

CMapXLayer CMapXLayers::AddServerLayer(LPCTSTR Name, LPCTSTR ConnectString, LPCTSTR Query, const VARIANT& Position, const VARIANT& Options)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, ConnectString, Query, &Position, &Options);
	return CMapXLayer(result);
}

void CMapXLayers::RemoveAll()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


CMapXLayer CMapXLayers::GetInsertionLayer()
{
	LPDISPATCH pDispatch;
	GetProperty(0xf, VT_DISPATCH, (void*)&pDispatch);
	return CMapXLayer(pDispatch);
}

void CMapXLayers::SetInsertionLayer(LPDISPATCH propVal)
{
	SetProperty(0xf, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLayer properties

CString CMapXLayer::GetName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXLayer::SetName(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

BOOL CMapXLayer::GetVisible()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetVisible(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL CMapXLayer::GetSelectable()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetSelectable(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

CString CMapXLayer::GetFilespec()
{
	CString result;
	GetProperty(0x4, VT_BSTR, (void*)&result);
	return result;
}

CMapXLabelProperties CMapXLayer::GetLabelProperties()
{
	LPDISPATCH result;
	GetProperty(0x5, VT_DISPATCH, (void*)&result);
	return CMapXLabelProperties(result);
}

BOOL CMapXLayer::GetAutoLabel()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetAutoLabel(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

BOOL CMapXLayer::GetZoomLayer()
{
	BOOL result;
	GetProperty(0x7, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetZoomLayer(BOOL propVal)
{
	SetProperty(0x7, VT_BOOL, propVal);
}

BOOL CMapXLayer::GetOverrideStyle()
{
	BOOL result;
	GetProperty(0x8, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetOverrideStyle(BOOL propVal)
{
	SetProperty(0x8, VT_BOOL, propVal);
}

CMapXStyle CMapXLayer::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x9, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXLayer::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x9, VT_DISPATCH, propVal);
}

double CMapXLayer::GetZoomMin()
{
	double result;
	GetProperty(0xa, VT_R8, (void*)&result);
	return result;
}

void CMapXLayer::SetZoomMin(double propVal)
{
	SetProperty(0xa, VT_R8, propVal);
}

double CMapXLayer::GetZoomMax()
{
	double result;
	GetProperty(0xb, VT_R8, (void*)&result);
	return result;
}

void CMapXLayer::SetZoomMax(double propVal)
{
	SetProperty(0xb, VT_R8, propVal);
}

CMapXSelection CMapXLayer::GetSelection()
{
	LPDISPATCH result;
	GetProperty(0xc, VT_DISPATCH, (void*)&result);
	return CMapXSelection(result);
}

short CMapXLayer::GetPredominantFeatureType()
{
	short result;
	GetProperty(0xd, VT_I2, (void*)&result);
	return result;
}

CMapXLayerFind CMapXLayer::GetFind()
{
	LPDISPATCH result;
	GetProperty(0xe, VT_DISPATCH, (void*)&result);
	return CMapXLayerFind(result);
}

short CMapXLayer::GetType()
{
	short result;
	GetProperty(0xf, VT_I2, (void*)&result);
	return result;
}

CString CMapXLayer::GetKeyField()
{
	CString result;
	GetProperty(0x10, VT_BSTR, (void*)&result);
	return result;
}

void CMapXLayer::SetKeyField(LPCTSTR propVal)
{
	SetProperty(0x10, VT_BSTR, propVal);
}

CMapXCoordSys CMapXLayer::GetCoordSys()
{
	LPDISPATCH result;
	GetProperty(0x11, VT_DISPATCH, (void*)&result);
	return CMapXCoordSys(result);
}

CMapXRectangle CMapXLayer::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x20, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

BOOL CMapXLayer::GetDrawLabelsAfter()
{
	BOOL result;
	GetProperty(0x25, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetDrawLabelsAfter(BOOL propVal)
{
	SetProperty(0x25, VT_BOOL, propVal);
}

CMapXDatasets CMapXLayer::GetDatasets()
{
	LPDISPATCH result;
	GetProperty(0x27, VT_DISPATCH, (void*)&result);
	return CMapXDatasets(result);
}

BOOL CMapXLayer::GetShowNodes()
{
	BOOL result;
	GetProperty(0x2b, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetShowNodes(BOOL propVal)
{
	SetProperty(0x2b, VT_BOOL, propVal);
}

BOOL CMapXLayer::GetShowCentroids()
{
	BOOL result;
	GetProperty(0x2c, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetShowCentroids(BOOL propVal)
{
	SetProperty(0x2c, VT_BOOL, propVal);
}

BOOL CMapXLayer::GetShowLineDirection()
{
	BOOL result;
	GetProperty(0x2d, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetShowLineDirection(BOOL propVal)
{
	SetProperty(0x2d, VT_BOOL, propVal);
}

BOOL CMapXLayer::GetEditable()
{
	BOOL result;
	GetProperty(0x2e, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayer::SetEditable(BOOL propVal)
{
	SetProperty(0x2e, VT_BOOL, propVal);
}

CMapXRectangle CMapXLayer::GetClippedBounds()
{
	LPDISPATCH result;
	GetProperty(0x31, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

CMapXLabels CMapXLayer::GetLabels()
{
	LPDISPATCH result;
	GetProperty(0x37, VT_DISPATCH, (void*)&result);
	return CMapXLabels(result);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXLayer operations

void CMapXLayer::LabelAtPoint(double X, double Y)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 X, Y);
}

void CMapXLayer::ClearCustomLabels()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CMapXFeature CMapXLayer::AddFeature(LPDISPATCH Source, const VARIANT& RowValues)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Source, &RowValues);
	return CMapXFeature(result);
}

void CMapXLayer::UpdateFeature(
	const VARIANT& Target, 
	const VARIANT& Source,
	const VARIANT& RowValues)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Target, &Source, &RowValues);
}

void CMapXLayer::DeleteFeature(const VARIANT& Target)
{
	static BYTE parms[] =	VTS_VARIANT;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Target);
}

void CMapXLayer::Invalidate(const VARIANT& InvalidRect)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &InvalidRect);
}

CMapXFeatures CMapXLayer::SearchWithinDistance(LPDISPATCH Source, double Distance, short Units, short SearchType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_R8 VTS_I2 VTS_I2;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Source, Distance, Units, SearchType);
	return CMapXFeatures(result);
}

CMapXFeatures CMapXLayer::SearchWithinRectangle(LPDISPATCH Rectangle, short SearchType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I2;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Rectangle, SearchType);
	return CMapXFeatures(result);
}

CMapXFeatures CMapXLayer::AllFeatures()
{
	LPDISPATCH result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXFeatures(result);
}

CMapXFeatures CMapXLayer::NoFeatures()
{
	LPDISPATCH result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXFeatures(result);
}

CMapXBoundsConstraint CMapXLayer::CreateBoundsConstraint()
{
	LPDISPATCH result;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXBoundsConstraint(result);
}

CMapXFeaturesConstraint CMapXLayer::CreateFeaturesConstraint()
{
	LPDISPATCH result;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXFeaturesConstraint(result);
}

CMapXAllFeaturesConstraint CMapXLayer::CreateAllFeaturesConstraint()
{
	LPDISPATCH result;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXAllFeaturesConstraint(result);
}

CMapXFeatures CMapXLayer::SearchWithinFeature(LPDISPATCH Feature, short SearchType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I2;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Feature, SearchType);
	return CMapXFeatures(result);
}

CMapXFeatures CMapXLayer::SearchAtPoint(LPDISPATCH Point, short SearchResultFlags)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I2;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Point, SearchResultFlags);
	return CMapXFeatures(result);
}

void CMapXLayer::DrillDownRemoveFeatures(LPCTSTR Level, const VARIANT& FeatureKeys)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Level, &FeatureKeys);
}

void CMapXLayer::DrillDownAddFeatures(LPCTSTR Level, const VARIANT& FeatureKeys)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Level, &FeatureKeys);
}

CMapXFeatures CMapXLayer::GetDrilldownFeaturesByID(LPCTSTR Level, const VARIANT& FeatureKeys)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms,
		 Level, &FeatureKeys);
	return CMapXFeatures(result);
}

void CMapXLayer::DrilldownReset(LPCTSTR Level)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Level);
}

CMapXFeature CMapXLayer::GetFeatureByID(long FeatureID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FeatureID);
	return CMapXFeature(result);
}

void CMapXLayer::Refresh()
{
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CMapXLayer::FeatureIDFromFeatureName(LPCTSTR Name)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, &result, parms, Name);
	return result;
}

CMapXFeatures CMapXLayer::Search(LPCTSTR strWhere, const VARIANT& Variables)
{
	LPDISPATCH result;
	static BYTE parms[] = VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms, strWhere, &Variables);
	return CMapXFeatures(result);
}

BOOL CMapXLayer::SupportsPack(long PackType)
{
	BOOL bRetVal;
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_BOOL, (void*)&bRetVal, parms, PackType);
	return bRetVal;
}

void CMapXLayer::Pack(long PackType)
{
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PackType);
}

void CMapXLayer::BeginAccess(long BeginAccessType)
{
	static BYTE parms[] = VTS_I2;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, BeginAccessType);
}

void CMapXLayer::EndAccess(const VARIANT& EndAccessType)
{
	static BYTE parms[] = VTS_VARIANT;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &EndAccessType);
}

CMapXFeature CMapXLayer::GetFeatureByKey(LPCTSTR FeatureKey)
{
	LPDISPATCH result;
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_DISPATCH, (void *)&result, parms, FeatureKey);
	return CMapXFeature(result);
}

CString CMapXLayer::FeatureKeyFromFeatureName(LPCTSTR strKeyValue)
{
	CString result;
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void *)&result, parms, strKeyValue);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXField properties

long CMapXField::GetType()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

CString CMapXField::GetName()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

long CMapXField::GetAggregationFunction()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

short CMapXField::GetWidth()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

short CMapXField::GetPrecision()
{
	short result;
	GetProperty(0x5, VT_I2, (void*)&result);
	return result;
}

short CMapXField::GetDecimals()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}

BOOL CMapXField::GetIndexed()
{
	BOOL result;
	GetProperty(0x7, VT_BOOL, (void*)&result);
	return result;
}

long CMapXField::GetTypeEx()
{
	long result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXField operations


/////////////////////////////////////////////////////////////////////////////
// CMapXDataset properties

CString CMapXDataset::GetName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXDataset::SetName(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

long CMapXDataset::GetRowCount()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

CMapXFields CMapXDataset::GetFields()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return CMapXFields(result);
}

CMapXThemes CMapXDataset::GetThemes()
{
	LPDISPATCH result;
	GetProperty(0x4, VT_DISPATCH, (void*)&result);
	return CMapXThemes(result);
}

long CMapXDataset::GetGeoField()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

long CMapXDataset::GetSecondaryGeoField()
{
	long result;
	GetProperty(0x6, VT_I4, (void*)&result);
	return result;
}

CMapXLayer CMapXDataset::GetLayer()
{
	LPDISPATCH result;
	GetProperty(0x7, VT_DISPATCH, (void*)&result);
	return CMapXLayer(result);
}

short CMapXDataset::GetType()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}

BOOL CMapXDataset::GetReadOnly()
{
	BOOL result;
	GetProperty(0xc, VT_BOOL, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXDataset operations

void CMapXDataset::Refresh()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT CMapXDataset::GetValue(const VARIANT& Row, const VARIANT& Column)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Row, &Column);
	return result;
}

CMapXSourceRows CMapXDataset::GetSourceRows(const VARIANT& Row)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Row);
	return CMapXSourceRows(result);
}

CMapXRowValues CMapXDataset::GetRowValues(const VARIANT& Row)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Row);
	return CMapXRowValues(result);
}

CMapXField CMapXDataset::AddField(LPCTSTR Name, LPCTSTR Expression)
{
	LPDISPATCH result;
	static BYTE parms[] =	VTS_BSTR VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Name, Expression);
	return CMapXField(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXThemes properties

LPENUMVARIANT CMapXThemes::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXThemes::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXThemes operations

CMapXTheme CMapXThemes::Add(const VARIANT& Type, const VARIANT& Field, const VARIANT& Name, const VARIANT& ComputeTheme)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Type, &Field, &Name, &ComputeTheme);
	return CMapXTheme(result);
}

CMapXTheme CMapXThemes::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXTheme(result);
}

void CMapXThemes::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

void CMapXThemes::RemoveAll()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXTheme properties

BOOL CMapXTheme::GetVisible()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CMapXTheme::SetVisible(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

short CMapXTheme::GetType()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}

CMapXThemeProperties CMapXTheme::GetProperties()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return CMapXThemeProperties(result);
}

CMapXLegend CMapXTheme::GetLegend()
{
	LPDISPATCH result;
	GetProperty(0x4, VT_DISPATCH, (void*)&result);
	return CMapXLegend(result);
}

BOOL CMapXTheme::GetAutoRecompute()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

void CMapXTheme::SetAutoRecompute(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}

CString CMapXTheme::GetName()
{
	CString result;
	GetProperty(0x6, VT_BSTR, (void*)&result);
	return result;
}

void CMapXTheme::SetName(LPCTSTR propVal)
{
	SetProperty(0x6, VT_BSTR, propVal);
}

CMapXThemeProperties CMapXTheme::GetThemeProperties()
{
	LPDISPATCH result;
	GetProperty(0x7, VT_DISPATCH, (void*)&result);
	return CMapXThemeProperties(result);
}

CMapXLayer CMapXTheme::GetLayer()
{
	LPDISPATCH result;
	GetProperty(0x9, VT_DISPATCH, (void*)&result);
	return CMapXLayer(result);
}

CMapXFields CMapXTheme::GetFields()
{
	LPDISPATCH result;
	GetProperty(0xa, VT_DISPATCH, (void*)&result);
	return CMapXFields(result);
}

double CMapXTheme::GetDataMin()
{
	double result;
	GetProperty(0xb, VT_R8, (void*)&result);
	return result;
}

void CMapXTheme::SetDataMin(double propVal)
{
	SetProperty(0xb, VT_R8, propVal);
}

double CMapXTheme::GetDataMax()
{
	double result;
	GetProperty(0xc, VT_R8, (void*)&result);
	return result;
}

void CMapXTheme::SetDataMax(double propVal)
{
	SetProperty(0xc, VT_R8, propVal);
}

BOOL CMapXTheme::GetComputeTheme()
{
	BOOL result;
	GetProperty(0xd, VT_BOOL, (void*)&result);
	return result;
}

void CMapXTheme::SetComputeTheme(BOOL propVal)
{
	SetProperty(0xd, VT_BOOL, propVal);
}

long CMapXTheme::GetThemedFeatureType()
{
	long result;
	GetProperty(0xe, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXTheme operations

BOOL CMapXTheme::ThemeDlg(const VARIANT& HelpFile, const VARIANT& HelpID)
{
	BOOL bRetVal;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&bRetVal, parms,
		&HelpFile, &HelpID);
	return bRetVal;
}


/////////////////////////////////////////////////////////////////////////////
// CMapXLegend properties

BOOL CMapXLegend::GetCompact()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLegend::SetCompact(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

BOOL CMapXLegend::GetVisible()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLegend::SetVisible(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

CMapXStyle CMapXLegend::GetTitleStyle()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXLegend::SetTitleStyle(LPDISPATCH propVal)
{
	SetProperty(0x3, VT_DISPATCH, propVal);
}

CMapXStyle CMapXLegend::GetSubTitleStyle()
{
	LPDISPATCH result;
	GetProperty(0x4, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXLegend::SetSubTitleStyle(LPDISPATCH propVal)
{
	SetProperty(0x4, VT_DISPATCH, propVal);
}

CMapXStyle CMapXLegend::GetCompactTitleStyle()
{
	LPDISPATCH result;
	GetProperty(0x5, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXLegend::SetCompactTitleStyle(LPDISPATCH propVal)
{
	SetProperty(0x5, VT_DISPATCH, propVal);
}

CMapXStyle CMapXLegend::GetBodyTextStyle()
{
	LPDISPATCH result;
	GetProperty(0x6, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXLegend::SetBodyTextStyle(LPDISPATCH propVal)
{
	SetProperty(0x6, VT_DISPATCH, propVal);
}

CMapXLegendTexts CMapXLegend::GetLegendTexts()
{
	LPDISPATCH result;
	GetProperty(0x7, VT_DISPATCH, (void*)&result);
	return CMapXLegendTexts(result);
}

BOOL CMapXLegend::GetCurrencyFormat()
{
	BOOL result;
	GetProperty(0x8, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLegend::SetCurrencyFormat(BOOL propVal)
{
	SetProperty(0x8, VT_BOOL, propVal);
}

CString CMapXLegend::GetTitle()
{
	CString result;
	GetProperty(0x9, VT_BSTR, (void*)&result);
	return result;
}

void CMapXLegend::SetTitle(LPCTSTR propVal)
{
	SetProperty(0x9, VT_BSTR, propVal);
}

CString CMapXLegend::GetSubTitle()
{
	CString result;
	GetProperty(0xa, VT_BSTR, (void*)&result);
	return result;
}

void CMapXLegend::SetSubTitle(LPCTSTR propVal)
{
	SetProperty(0xa, VT_BSTR, propVal);
}

CString CMapXLegend::GetCompactTitle()
{
	CString result;
	GetProperty(0xb, VT_BSTR, (void*)&result);
	return result;
}

void CMapXLegend::SetCompactTitle(LPCTSTR propVal)
{
	SetProperty(0xb, VT_BSTR, propVal);
}

double CMapXLegend::GetLeft()
{
	double result;
	GetProperty(0xc, VT_R8, (void*)&result);
	return result;
}

void CMapXLegend::SetLeft(double propVal)
{
	SetProperty(0xc, VT_R8, propVal);
}

double CMapXLegend::GetTop()
{
	double result;
	GetProperty(0xd, VT_R8, (void*)&result);
	return result;
}

void CMapXLegend::SetTop(double propVal)
{
	SetProperty(0xd, VT_R8, propVal);
}

double CMapXLegend::GetWidth()
{
	double result;
	GetProperty(0xe, VT_R8, (void*)&result);
	return result;
}

double CMapXLegend::GetHeight()
{
	double result;
	GetProperty(0xf, VT_R8, (void*)&result);
	return result;
}

BOOL CMapXLegend::GetShowEmptyRanges()
{
	BOOL result;
	GetProperty(0x11, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLegend::SetShowEmptyRanges(BOOL propVal)
{
	SetProperty(0x11, VT_BOOL, propVal);
}

BOOL CMapXLegend::GetShowCount()
{
	BOOL result;
	GetProperty(0x13, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLegend::SetShowCount(BOOL propVal)
{
	SetProperty(0x13, VT_BOOL, propVal);
}

double CMapXLegend::GetPaperHeight()
{
	double result;
	GetProperty(0x15, VT_R8, (void*)&result);
	return result;
}

double CMapXLegend::GetPaperWidth()
{
	double result;
	GetProperty(0x16, VT_R8, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLegend operations

BOOL CMapXLegend::LegendDlg(const VARIANT& HelpFile, const VARIANT& HelpID)
{
	BOOL bRetVal;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&bRetVal, parms,
		&HelpFile, &HelpID);
	return(bRetVal);
}

void CMapXLegend::ExportLegend(LPCTSTR Destination, short Format)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I2;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Destination, Format);
}

void CMapXLegend::PrintLegend(long hDC, long X, long Y, long W, long H)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, X, Y, W, H);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXAnnotations properties

LPENUMVARIANT CMapXAnnotations::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

BOOL CMapXAnnotations::GetEditable()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CMapXAnnotations::SetEditable(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

long CMapXAnnotations::GetCount()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXAnnotations operations

CMapXAnnotation CMapXAnnotations::AddSymbol(double X, double Y)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		X, Y);
	return CMapXAnnotation(result);
}

CMapXAnnotation CMapXAnnotations::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXAnnotation(result);
}

void CMapXAnnotations::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

CMapXAnnotation CMapXAnnotations::AddText(LPCTSTR Text, double X, double Y, const VARIANT& Position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_R8 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Text, X, Y, &Position);
	return CMapXAnnotation(result);
}

void CMapXAnnotations::RemoveAll()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CMapXAnnotation CMapXAnnotations::ActiveAnnotation()
{
	LPDISPATCH result;
	GetProperty(0x8, VT_DISPATCH, (void*)&result);
	return CMapXAnnotation(result);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXThemeProperties properties

short CMapXThemeProperties::GetDistMethod()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetDistMethod(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}

short CMapXThemeProperties::GetNumRanges()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetNumRanges(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}

CMapXRangeCategories CMapXThemeProperties::GetRangeCategories()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return CMapXRangeCategories(result);
}

short CMapXThemeProperties::GetDotSize()
{
	short result;
	GetProperty(0x5, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetDotSize(short propVal)
{
	SetProperty(0x5, VT_I2, propVal);
}

BOOL CMapXThemeProperties::GetGraduated()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetGraduated(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

CMapXMultivarCategories CMapXThemeProperties::GetMultivarCategories()
{
	LPDISPATCH result;
	GetProperty(0x7, VT_DISPATCH, (void*)&result);
	return CMapXMultivarCategories(result);
}

BOOL CMapXThemeProperties::GetIndependent()
{
	BOOL result;
	GetProperty(0x8, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetIndependent(BOOL propVal)
{
	SetProperty(0x8, VT_BOOL, propVal);
}

CMapXIndividualValueCategories CMapXThemeProperties::GetIndividualValueCategories()
{
	LPDISPATCH result;
	GetProperty(0x4, VT_DISPATCH, (void*)&result);
	return CMapXIndividualValueCategories(result);
}

double CMapXThemeProperties::GetValuePerDot()
{
	double result;
	GetProperty(0x9, VT_R8, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetValuePerDot(double propVal)
{
	SetProperty(0x9, VT_R8, propVal);
}

double CMapXThemeProperties::GetDataValue()
{
	double result;
	GetProperty(0xa, VT_R8, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetDataValue(double propVal)
{
	SetProperty(0xa, VT_R8, propVal);
}

double CMapXThemeProperties::GetSize()
{
	double result;
	GetProperty(0xb, VT_R8, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetSize(double propVal)
{
	SetProperty(0xb, VT_R8, propVal);
}

double CMapXThemeProperties::GetWidth()
{
	double result;
	GetProperty(0xc, VT_R8, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetWidth(double propVal)
{
	SetProperty(0xc, VT_R8, propVal);
}

CMapXStyle CMapXThemeProperties::GetSymbolStyle()
{
	LPDISPATCH result;
	GetProperty(0xd, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXThemeProperties::SetSymbolStyle(LPDISPATCH propVal)
{
	SetProperty(0xd, VT_DISPATCH, propVal);
}

short CMapXThemeProperties::GetSpreadBy()
{
	short result;
	GetProperty(0xe, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetSpreadBy(short propVal)
{
	SetProperty(0xe, VT_I2, propVal);
}

BOOL CMapXThemeProperties::GetAllowEmptyRanges()
{
	BOOL result;
	GetProperty(0xf, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetAllowEmptyRanges(BOOL propVal)
{
	SetProperty(0xf, VT_BOOL, propVal);
}

unsigned long CMapXThemeProperties::GetDotColor()
{
	unsigned long result;
	GetProperty(0x10, VT_I4, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetDotColor(unsigned long propVal)
{
	SetProperty(0x10, VT_I4, propVal);
}

BOOL CMapXThemeProperties::GetPieClockwise()
{
	BOOL result;
	GetProperty(0x11, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetPieClockwise(BOOL propVal)
{
	SetProperty(0x11, VT_BOOL, propVal);
}

BOOL CMapXThemeProperties::GetPieHalfPies()
{
	BOOL result;
	GetProperty(0x12, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetPieHalfPies(BOOL propVal)
{
	SetProperty(0x12, VT_BOOL, propVal);
}

short CMapXThemeProperties::GetPieStartAngle()
{
	short result;
	GetProperty(0x13, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetPieStartAngle(short propVal)
{
	SetProperty(0x13, VT_I2, propVal);
}

BOOL CMapXThemeProperties::GetBarStacked()
{
	BOOL result;
	GetProperty(0x14, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetBarStacked(BOOL propVal)
{
	SetProperty(0x14, VT_BOOL, propVal);
}

CMapXStyle CMapXThemeProperties::GetNegativeSymbolStyle()
{
	LPDISPATCH result;
	GetProperty(0x15, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXThemeProperties::SetNegativeSymbolStyle(LPDISPATCH propVal)
{
	SetProperty(0x15, VT_DISPATCH, propVal);
}

BOOL CMapXThemeProperties::GetShowNegativeValues()
{
	BOOL result;
	GetProperty(0x16, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetShowNegativeValues(BOOL propVal)
{
	SetProperty(0x16, VT_BOOL, propVal);
}

short CMapXThemeProperties::GetGraduateSizeBy()
{
	short result;
	GetProperty(0x17, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetGraduateSizeBy(short propVal)
{
	SetProperty(0x17, VT_I2, propVal);
}

CMapXStyle CMapXThemeProperties::GetBorderStyle()
{
	LPDISPATCH result;
	GetProperty(0x18, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXThemeProperties::SetBorderStyle(LPDISPATCH propVal)
{
	SetProperty(0x18, VT_DISPATCH, propVal);
}

double CMapXThemeProperties::GetBarWidth()
{
	double result;
	GetProperty(0x19, VT_R8, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetBarWidth(double propVal)
{
	SetProperty(0x19, VT_R8, propVal);
}

BOOL CMapXThemeProperties::GetBarIndependentScale()
{
	BOOL result;
	GetProperty(0x1a, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetBarIndependentScale(BOOL propVal)
{
	SetProperty(0x1a, VT_BOOL, propVal);
}

CMapXStyle CMapXThemeProperties::GetPositiveSymbolStyle()
{
	LPDISPATCH result;
	GetProperty(0x1b, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXThemeProperties::SetPositiveSymbolStyle(LPDISPATCH propVal)
{
	SetProperty(0x1b, VT_DISPATCH, propVal);
}

CMapXStyle CMapXThemeProperties::GetBarFrameStyle()
{
	LPDISPATCH result;
	GetProperty(0x1c, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXThemeProperties::SetBarFrameStyle(LPDISPATCH propVal)
{
	SetProperty(0x1c, VT_DISPATCH, propVal);
}

BOOL CMapXThemeProperties::GetPieGraduated()
{
	BOOL result;
	GetProperty(0x1d, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetPieGraduated(BOOL propVal)
{
	SetProperty(0x1d, VT_BOOL, propVal);
}

BOOL CMapXThemeProperties::GetBarGraduatedStack()
{
	BOOL result;
	GetProperty(0x1e, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetBarGraduatedStack(BOOL propVal)
{
	SetProperty(0x1e, VT_BOOL, propVal);
}

short CMapXThemeProperties::GetApplyAttribute()
{
	short result;
	GetProperty(0x1f, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetApplyAttribute(short propVal)
{
	SetProperty(0x1f, VT_I2, propVal);
}

BOOL CMapXThemeProperties::GetRoundRanges()
{
	BOOL result;
	GetProperty(0x20, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetRoundRanges(BOOL propVal)
{
	SetProperty(0x20, VT_BOOL, propVal);
}

double CMapXThemeProperties::GetRoundBy()
{
	double result;
	GetProperty(0x21, VT_R8, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetRoundBy(double propVal)
{
	SetProperty(0x21, VT_R8, propVal);
}

short CMapXThemeProperties::GetColorMethod()
{
	short result;
	GetProperty(0x22, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetColorMethod(short propVal)
{
	SetProperty(0x22, VT_I2, propVal);
}

BOOL CMapXThemeProperties::GetInflectRanges()
{
	BOOL result;
	GetProperty(0x23, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetInflectRanges(BOOL propVal)
{
	SetProperty(0x23, VT_BOOL, propVal);
}

short CMapXThemeProperties::GetInflectionRange()
{
	short result;
	GetProperty(0x24, VT_I2, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetInflectionRange(short propVal)
{
	SetProperty(0x24, VT_I2, propVal);
}

unsigned long CMapXThemeProperties::GetInflectionColor()
{
	unsigned long result;
	GetProperty(0x25, VT_I4, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetInflectionColor(unsigned long propVal)
{
	SetProperty(0x25, VT_I4, propVal);
}

BOOL CMapXThemeProperties::GetBarFramed()
{
	BOOL result;
	GetProperty(0x26, VT_BOOL, (void*)&result);
	return result;
}

void CMapXThemeProperties::SetBarFramed(BOOL propVal)
{
	SetProperty(0x26, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXThemeProperties operations


/////////////////////////////////////////////////////////////////////////////
// CMapXSelection properties

LPENUMVARIANT CMapXSelection::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXSelection::GetCount()
{
	long result;
	GetProperty(0x10001, VT_I4, (void*)&result);
	return result;
}

CMapXRectangle CMapXSelection::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x10008, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXSelection operations

CMapXFeature CMapXSelection::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXFeature(result);
}

CMapXFeatures CMapXSelection::Clone()
{
	LPDISPATCH result;
	InvokeHelper(0x10003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXFeatures(result);
}

void CMapXSelection::Add(LPDISPATCH Source)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10004, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Source);
}

void CMapXSelection::Common(LPDISPATCH Source)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Source);
}

void CMapXSelection::Remove(const VARIANT& Source)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source);
}

void CMapXSelection::Replace(LPDISPATCH Source)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Source);
}

void CMapXSelection::AddByID(const VARIANT& FeatureID)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FeatureID);
}

void CMapXSelection::RemoveByID(const VARIANT& FeatureID)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FeatureID);
}

void CMapXSelection::SelectByRegion(LPDISPATCH Layer, const VARIANT& FeatureID, short Flag)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT VTS_I2;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Layer, &FeatureID, Flag);
}

void CMapXSelection::ClearSelection()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapXSelection::SelectByPoint(double X, double Y, short SelectFlag, short SearchResultFlags)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_I2 VTS_I2;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 X, Y, SelectFlag, SearchResultFlags);
}

void CMapXSelection::SelectByRadius(double X, double Y, double radius, short Flag)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8 VTS_I2;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 X, Y, radius, Flag);
}

void CMapXSelection::SelectByRectangle(double X1, double Y1, double X2, double Y2, short Flag)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I2;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 X1, Y1, X2, Y2, Flag);
}

BOOL CMapXSelection::SelectAll(short Flag)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Flag);
	return result;
}

void CMapXSelection::SelectByID(const VARIANT& FeatureID, short Flag)
{
	static BYTE parms[] =	
		VTS_VARIANT VTS_I2;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FeatureID, Flag);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXFeature properties

long CMapXFeature::GetFeatureID()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

short CMapXFeature::GetType()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}

void CMapXFeature::SetType(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}

double CMapXFeature::GetLength()
{
	double result;
	GetProperty(0x3, VT_R8, (void*)&result);
	return result;
}

double CMapXFeature::GetCenterX()
{
	double result;
	GetProperty(0x4, VT_R8, (void*)&result);
	return result;
}

double CMapXFeature::GetCenterY()
{
	double result;
	GetProperty(0x5, VT_R8, (void*)&result);
	return result;
}

CMapXStyle CMapXFeature::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x6, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXFeature::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x6, VT_DISPATCH, propVal);
}

CMapXRectangle CMapXFeature::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x7, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

CString CMapXFeature::GetCaption()
{
	CString result;
	GetProperty(0x8, VT_BSTR, (void*)&result);
	return result;
}

void CMapXFeature::SetCaption(LPCTSTR propVal)
{
	SetProperty(0x8, VT_BSTR, propVal);
}

CMapXParts CMapXFeature::GetParts()
{
	LPDISPATCH result;
	GetProperty(0x9, VT_DISPATCH, (void*)&result);
	return CMapXParts(result);
}

double CMapXFeature::GetArea()
{
	double result;
	GetProperty(0xa, VT_R8, (void*)&result);
	return result;
}

CMapXLayer CMapXFeature::GetLayer()
{
	LPDISPATCH result;
	GetProperty(0xb, VT_DISPATCH, (void*)&result);
	return CMapXLayer(result);
}

CMapXPoint CMapXFeature::GetPoint()
{
	LPDISPATCH result;
	GetProperty(0xc, VT_DISPATCH, (void*)&result);
	return CMapXPoint(result);
}

void CMapXFeature::SetPoint(LPDISPATCH propVal)
{
	SetProperty(0xc, VT_DISPATCH, propVal);
}

CMapXPoint CMapXFeature::GetLabelPoint()
{
	LPDISPATCH result;
	GetProperty(0xd, VT_DISPATCH, (void*)&result);
	return CMapXPoint(result);
}

double CMapXFeature::GetPerimeter()
{
	double result;
	GetProperty(0xe, VT_R8, (void*)&result);
	return result;
}

BOOL CMapXFeature::GetSmooth()
{
	BOOL result;
	GetProperty(0xf, VT_BOOL, (void*)&result);
	return result;
}

void CMapXFeature::SetSmooth(BOOL propVal)
{
	SetProperty(0xf, VT_BOOL, propVal);
}

CString CMapXFeature::GetName()
{
	CString result;
	GetProperty(0x10, VT_BSTR, (void*)&result);
	return result;
}

CString CMapXFeature::GetKeyValue()
{
	CString result;
	GetProperty(0x11, VT_BSTR, (void*)&result);
	return result;
}

void CMapXFeature::SetKeyValue(LPCTSTR propVal)
{
	SetProperty(0x11, VT_BSTR, propVal);
}

CString CMapXFeature::GetFeatureKey()
{
	CString result;
	GetProperty(0x17, VT_BSTR, (void*)&result);
	return result;
}

CMapXFeature CMapXFeature::GetRegion()
{
	LPDISPATCH result;
	GetProperty(0x18, VT_DISPATCH, (void*)&result);
	return CMapXFeature(result);
}

void CMapXFeature::SetRegion(LPDISPATCH propVal)
{
	SetProperty(0x18, VT_DISPATCH, propVal);
}

CMapXFeature CMapXFeature::GetPolyline()
{
	LPDISPATCH result;
	GetProperty(0x19, VT_DISPATCH, (void*)&result);
	return CMapXFeature(result);
}

void CMapXFeature::SetPolyline(LPDISPATCH propVal)
{
	SetProperty(0x19, VT_DISPATCH, propVal);
}

CMapXFeature CMapXFeature::GetMultipoint()
{
	LPDISPATCH result;
	GetProperty(0x1A, VT_DISPATCH, (void*)&result);
	return CMapXFeature(result);
}

void CMapXFeature::SetMultipoint(LPDISPATCH propVal)
{
	SetProperty(0x1A, VT_DISPATCH, propVal);
}

BOOL CMapXFeature::GetHasRegion()
{
	BOOL result;
	GetProperty(0x1B, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXFeature::GetHasPolyline()
{
	BOOL result;
	GetProperty(0x1C, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXFeature::GetHasMultipoint()
{
	BOOL result;
	GetProperty(0x1D, VT_BOOL, (void*)&result);
	return result;
}
/////////////////////////////////////////////////////////////////////////////
// CMapXFeature operations

void CMapXFeature::Update(const VARIANT& UpdateFeature, const VARIANT& RowValues)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &UpdateFeature, &RowValues);
}

void CMapXFeature::Offset(double deltaX, double deltaY)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 deltaX, deltaY);
}

void CMapXFeature::Attach(LPDISPATCH Map)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Map);
}

CMapXFeature CMapXFeature::Clone()
{
	LPDISPATCH result;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXFeature(result);
}

VARIANT CMapXFeature::Nodes(const VARIANT& CSys)
{
	VARIANT result;
	static BYTE parms[] =	VTS_VARIANT;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &CSys);
	return result;
}

VARIANT CMapXFeature::GetNodes(const VARIANT& CSys)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&CSys);
	return result;
}

void CMapXFeature::SetNodes(const VARIANT& CSys, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &CSys, &newValue);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFeatureFactory properties

/////////////////////////////////////////////////////////////////////////////
// CMapXFeatureFactory operations

CMapXFeature CMapXFeatureFactory::BufferFeatures(LPDISPATCH Source, double Distance, const VARIANT& Units, const VARIANT& Resolution)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_R8 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Source, Distance, &Units, &Resolution);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CombineFeatures(LPDISPATCH Source1, const VARIANT& Source2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Source1, &Source2);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::IntersectFeatures(LPDISPATCH Source1, const VARIANT& Source2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Source1, &Source2);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::EraseFeature(LPDISPATCH Feature, LPDISPATCH EraserFeature)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Feature, EraserFeature);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateSymbol(const VARIANT& Point, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point, &Style);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateRegion(const VARIANT& Points, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Points, &Style);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateLine(const VARIANT& Points, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Points, &Style);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateText(const VARIANT& Point, const VARIANT& Caption, const VARIANT& Position, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point, &Caption, &Position, &Style);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateArc(LPDISPATCH Point1, LPDISPATCH Point2, const VARIANT& Angle, const VARIANT& Distance, const VARIANT& Resolution, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Point1, Point2, &Angle, &Distance, &Resolution, &Style);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateEllipticalRegion(LPDISPATCH Rectangle, const VARIANT& Angle, const VARIANT& Resolution, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Rectangle, &Angle, &Resolution, &Style);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateCircularRegion(short Type, LPDISPATCH Point, double Distance, const VARIANT& Units, const VARIANT& Resolution, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I2 VTS_DISPATCH VTS_R8 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, Point, Distance, &Units, &Resolution, &Style);
	return CMapXFeature(result);
}

BOOL CMapXFeatureFactory::IntersectionTest(LPDISPATCH Feature1, LPDISPATCH Feature2, const VARIANT& Flag)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Feature1, Feature2, &Flag);
	return result;
}

CMapXPoints CMapXFeatureFactory::IntersectionPoints(LPDISPATCH Feature1, LPDISPATCH Feature2, const VARIANT& Flag)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Feature1, Feature2, &Flag);
	return CMapXPoints(result);
}

CMapXFeature CMapXFeatureFactory::CreateCollectionFeature(const VARIANT& Source1, const VARIANT& Source2, const VARIANT& Source3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Source1, &Source2, &Source3);
	return CMapXFeature(result);
}

CMapXFeature CMapXFeatureFactory::CreateMultipoint(const VARIANT& Points, const VARIANT& Style)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Points, &Style);
	return CMapXFeature(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRangeCategory properties

double CMapXRangeCategory::GetMin()
{
	double result;
	GetProperty(0x1, VT_R8, (void*)&result);
	return result;
}

void CMapXRangeCategory::SetMin(double propVal)
{
	SetProperty(0x1, VT_R8, propVal);
}

double CMapXRangeCategory::GetMax()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

void CMapXRangeCategory::SetMax(double propVal)
{
	SetProperty(0x2, VT_R8, propVal);
}

long CMapXRangeCategory::GetNumItems()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

CMapXStyle CMapXRangeCategory::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x4, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXRangeCategory::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x4, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRangeCategory operations


/////////////////////////////////////////////////////////////////////////////
// CMapXFields properties

LPENUMVARIANT CMapXFields::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXFields::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFields operations

CMapXField CMapXFields::Add(const VARIANT& SourceField, const VARIANT& Name, const VARIANT& AggregationFunction, const VARIANT& Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&SourceField, &Name, &AggregationFunction, &Type);
	return CMapXField(result);
}

CMapXField CMapXFields::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXField(result);
}

void CMapXFields::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

void CMapXFields::RemoveAll()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CMapXField CMapXFields::AddStringField(const VARIANT& Name, const VARIANT& Width, const VARIANT& Indexed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Width, &Indexed);
	return CMapXField(result);
}

CMapXField CMapXFields::AddLogicalField(const VARIANT& Name, const VARIANT& Indexed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Indexed);
	return CMapXField(result);
}

CMapXField CMapXFields::AddIntegerField(const VARIANT& Name, const VARIANT& Indexed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Indexed);
	return CMapXField(result);
}

CMapXField CMapXFields::AddSmallIntField(const VARIANT& Name, const VARIANT& Indexed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Indexed);
	return CMapXField(result);
}

CMapXField CMapXFields::AddNumericField(const VARIANT& Name, const VARIANT& Precision, const VARIANT& Decimals, const VARIANT& Indexed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Precision, &Decimals, &Indexed);
	return CMapXField(result);
}

CMapXField CMapXFields::AddFloatField(const VARIANT& Name, const VARIANT& Indexed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Indexed);
	return CMapXField(result);
}

CMapXField CMapXFields::AddDateField(const VARIANT& Name, const VARIANT& Indexed)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name, &Indexed);
	return CMapXField(result);
}


/////////////////////////////////////////////////////////////////////////////
// COleFont properties

CString COleFont::GetName()
{
	CString result;
	GetProperty(0x0, VT_BSTR, (void*)&result);
	return result;
}

void COleFont::SetName(LPCTSTR propVal)
{
	SetProperty(0x0, VT_BSTR, propVal);
}

CY COleFont::GetSize()
{
	CY result;
	GetProperty(0x2, VT_CY, (void*)&result);
	return result;
}

void COleFont::SetSize(const CY& propVal)
{
	SetProperty(0x2, VT_CY, &propVal);
}

BOOL COleFont::GetBold()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void COleFont::SetBold(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL COleFont::GetItalic()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void COleFont::SetItalic(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

BOOL COleFont::GetUnderline()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

void COleFont::SetUnderline(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}

BOOL COleFont::GetStrikethrough()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void COleFont::SetStrikethrough(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

short COleFont::GetWeight()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}

void COleFont::SetWeight(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}

short COleFont::GetCharset()
{
	short result;
	GetProperty(0x8, VT_I2, (void*)&result);
	return result;
}

void COleFont::SetCharset(short propVal)
{
	SetProperty(0x8, VT_I2, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// COleFont operations

/////////////////////////////////////////////////////////////////////////////
// CMapXStyle properties

short CMapXStyle::GetSymbolCharacter()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolCharacter(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}

unsigned long CMapXStyle::GetLineColor()
{
	unsigned long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetLineColor(unsigned long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

short CMapXStyle::GetLineStyle()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetLineStyle(short propVal)
{
	SetProperty(0x3, VT_I2, propVal);
}

short CMapXStyle::GetLineWidth()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetLineWidth(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

unsigned long CMapXStyle::GetRegionColor()
{
	unsigned long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionColor(unsigned long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}

short CMapXStyle::GetRegionPattern()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionPattern(short propVal)
{
	SetProperty(0x6, VT_I2, propVal);
}

BOOL CMapXStyle::GetRegionTransparent()
{
	BOOL result;
	GetProperty(0x2b, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionTransparent(BOOL propVal)
{
	SetProperty(0x2b, VT_BOOL, propVal);
}

unsigned long CMapXStyle::GetRegionBackColor()
{
	unsigned long result;
	GetProperty(0x7, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionBackColor(unsigned long propVal)
{
	SetProperty(0x7, VT_I4, propVal);
}

short CMapXStyle::GetRegionBorderStyle()
{
	short result;
	GetProperty(0x8, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionBorderStyle(short propVal)
{
	SetProperty(0x8, VT_I2, propVal);
}

unsigned long CMapXStyle::GetRegionBorderColor()
{
	unsigned long result;
	GetProperty(0x9, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionBorderColor(unsigned long propVal)
{
	SetProperty(0x9, VT_I4, propVal);
}

short CMapXStyle::GetRegionBorderWidth()
{
	short result;
	GetProperty(0xa, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionBorderWidth(short propVal)
{
	SetProperty(0xa, VT_I2, propVal);
}

COleFont CMapXStyle::GetTextFont()
{
	LPDISPATCH result;
	GetProperty(0xb, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}

COleFont CMapXStyle::GetSymbolFont()
{
	LPDISPATCH result;
	GetProperty(0xc, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}

unsigned long CMapXStyle::GetTextFontColor()
{
	unsigned long result;
	GetProperty(0xd, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontColor(unsigned long propVal)
{
	SetProperty(0xd, VT_I4, propVal);
}

unsigned long CMapXStyle::GetTextFontBackColor()
{
	unsigned long result;
	GetProperty(0xe, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontBackColor(unsigned long propVal)
{
	SetProperty(0xe, VT_I4, propVal);
}

unsigned long CMapXStyle::GetSymbolFontColor()
{
	unsigned long result;
	GetProperty(0xf, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolFontColor(unsigned long propVal)
{
	SetProperty(0xf, VT_I4, propVal);
}

unsigned long CMapXStyle::GetSymbolFontBackColor()
{
	unsigned long result;
	GetProperty(0x10, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolFontBackColor(unsigned long propVal)
{
	SetProperty(0x10, VT_I4, propVal);
}

BOOL CMapXStyle::GetSymbolFontOpaque()
{
	BOOL result;
	GetProperty(0x11, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolFontOpaque(BOOL propVal)
{
	SetProperty(0x11, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetTextFontOpaque()
{
	BOOL result;
	GetProperty(0x12, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontOpaque(BOOL propVal)
{
	SetProperty(0x12, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetSymbolFontHalo()
{
	BOOL result;
	GetProperty(0x13, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolFontHalo(BOOL propVal)
{
	SetProperty(0x13, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetSymbolFontShadow()
{
	BOOL result;
	GetProperty(0x14, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolFontShadow(BOOL propVal)
{
	SetProperty(0x14, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetTextFontHalo()
{
	BOOL result;
	GetProperty(0x15, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontHalo(BOOL propVal)
{
	SetProperty(0x15, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetTextFontShadow()
{
	BOOL result;
	GetProperty(0x16, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontShadow(BOOL propVal)
{
	SetProperty(0x16, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetTextFontAllCaps()
{
	BOOL result;
	GetProperty(0x17, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontAllCaps(BOOL propVal)
{
	SetProperty(0x17, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetTextFontDblSpace()
{
	BOOL result;
	GetProperty(0x18, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontDblSpace(BOOL propVal)
{
	SetProperty(0x18, VT_BOOL, propVal);
}

BOOL CMapXStyle::GetSymbolBitmapTransparent()
{
	BOOL result;
	GetProperty(0x21, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolBitmapTransparent(BOOL bNewValue)
{
	SetProperty(0x21, VT_BOOL, bNewValue);
}

BOOL CMapXStyle::GetSymbolBitmapOverrideColor()
{
	BOOL result;
	GetProperty(0x22, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolBitmapOverrideColor(BOOL bNewValue)
{
	SetProperty(0x22, VT_BOOL, bNewValue);
}

unsigned long CMapXStyle::GetSymbolBitmapColor()
{
	unsigned long result;
	GetProperty(0x23, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolBitmapColor(unsigned long nNewValue)
{
	SetProperty(0x23, VT_I4, nNewValue);
}

CString CMapXStyle::GetSymbolBitmapName()
{
	CString result;
	GetProperty(0x24, VT_BSTR, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolBitmapName(LPCTSTR lpszNewValue)
{
	SetProperty(0x24, VT_BSTR, lpszNewValue);
}

short CMapXStyle::GetSymbolType()
{
	short result;
	GetProperty(0x25, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolType(short nNewValue)
{
	SetProperty(0x25, VT_I2, nNewValue);
}

long CMapXStyle::GetSymbolBitmapSize()
{
	long result;
	GetProperty(0x26, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolBitmapSize(long nNewValue)
{
	SetProperty(0x26, VT_I4, nNewValue);
}

BOOL CMapXStyle::GetSupportsBitmapSymbols()
{
	BOOL result;
	GetProperty(0x27, VT_BOOL, (void*)&result);
	return result;
}

short CMapXStyle::GetSymbolFontRotation()
{
	short result;
	GetProperty(0x28, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolFontRotation(short nNewValue)
{
	SetProperty(0x28, VT_I2, nNewValue);
}

long CMapXStyle::GetLineStyleCount()
{
	long result;
	GetProperty(0x2a, VT_I4, (void*)&result);
	return result;
}

BOOL CMapXStyle::GetLineInterleaved()
{
	BOOL result;
	GetProperty(0x2c, VT_BOOL, (void*)&result);
	return result;
}

void CMapXStyle::SetLineInterleaved(BOOL bNewValue)
{
	SetProperty(0x2c, VT_BOOL, bNewValue);
}

long CMapXStyle::GetLineWidthUnit()
{
	long result;
	GetProperty(0x2d, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetLineWidthUnit(long nNewValue)
{
	SetProperty(0x2d, VT_I4, nNewValue);
}

long CMapXStyle::GetRegionBorderWidthUnit()
{
	long result;
	GetProperty(0x2e, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetRegionBorderWidthUnit(long nNewValue)
{
	SetProperty(0x2e, VT_I4, nNewValue);
}

BOOL CMapXStyle::GetLineSupportsInterleave()
{
	BOOL result;
	GetProperty(0x2f, VT_BOOL, (void*)&result);
	return result;
}

short CMapXStyle::GetTextFontRotation()
{
	short result;
	GetProperty(0x30, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetTextFontRotation(short propVal)
{
	SetProperty(0x30, VT_I2, propVal);
}

unsigned long CMapXStyle::GetSymbolVectorColor()
{
	unsigned long result;
	GetProperty(0x35, VT_I4, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolVectorColor(unsigned long propVal)
{
	SetProperty(0x35, VT_I4, propVal);
}

short CMapXStyle::GetSymbolVectorSize()
{
	short result;
	GetProperty(0x36, VT_I2, (void*)&result);
	return result;
}

void CMapXStyle::SetSymbolVectorSize(short nNewValue)
{
	SetProperty(0x36, VT_I2, nNewValue);
}

short CMapXStyle::GetMinVectorSymbolCharacter()
{
	short result;
	GetProperty(0x37, VT_I2, (void*)&result);
	return result;
}

short CMapXStyle::GetMaxVectorSymbolCharacter()
{
	short result;
	GetProperty(0x38, VT_I2, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXStyle operations

BOOL CMapXStyle::PickRegion()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CMapXStyle::PickLine()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CMapXStyle::PickText()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CMapXStyle::PickSymbol()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMapXStyle::DrawTextSample(long hDC, LPDISPATCH Rectangle, LPCTSTR SampleText)
{
	static BYTE parms[] =
		VTS_I4 VTS_DISPATCH VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, Rectangle, SampleText);
}

void CMapXStyle::DrawSymbolSample(long hDC, LPDISPATCH Rectangle)
{
	static BYTE parms[] =
		VTS_I4 VTS_DISPATCH;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, Rectangle);
}

void CMapXStyle::DrawRegionSample(long hDC, LPDISPATCH Rectangle)
{
	static BYTE parms[] =
		VTS_I4 VTS_DISPATCH;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, Rectangle);
}

void CMapXStyle::DrawLineSample(long hDC, LPDISPATCH Rectangle)
{
	static BYTE parms[] =
		VTS_I4 VTS_DISPATCH;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, Rectangle);
}

CMapXStyle CMapXStyle::Clone()
{
	LPDISPATCH result;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXStyle(result);
}

void CMapXStyle::ExportSymbolSample(LPCTSTR Destination, short Format, double Width, double Height, const VARIANT& BackgroundColor)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_R8 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Destination, Format, Width, Height, &BackgroundColor);
}

void CMapXStyle::ExportRegionSample(LPCTSTR Destination, short Format, double Width, double Height, const VARIANT& BackgroundColor)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_R8 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Destination, Format, Width, Height, &BackgroundColor);
}

void CMapXStyle::ExportLineSample(LPCTSTR Destination, short Format, double Width, double Height, const VARIANT& BackgroundColor)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_R8 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Destination, Format, Width, Height, &BackgroundColor);
}

void CMapXStyle::ExportTextSample(LPCTSTR Destination, short Format, double Width, double Height, LPCTSTR SampleText, const VARIANT& BackgroundColor)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_R8 VTS_R8 VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Destination, Format, Width, Height, SampleText, &BackgroundColor);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXIndividualValueCategory properties

CMapXStyle CMapXIndividualValueCategory::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXIndividualValueCategory::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

long CMapXIndividualValueCategory::GetNumItems()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

CString CMapXIndividualValueCategory::GetValue()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}

void CMapXIndividualValueCategory::SetValue(LPCTSTR propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXMultivarCategory properties

CMapXStyle CMapXMultivarCategory::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXMultivarCategory::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXMultivarCategory operations


/////////////////////////////////////////////////////////////////////////////
// CMapXSourceRows properties

LPENUMVARIANT CMapXSourceRows::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXSourceRows::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXSourceRows operations

CMapXSourceRow CMapXSourceRows::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXSourceRow(result);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXSourceRow properties

long CMapXSourceRow::GetRow()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXSourceRow operations


/////////////////////////////////////////////////////////////////////////////
// CMapXAnnotation properties

short CMapXAnnotation::GetType()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

CMapXGraphic CMapXAnnotation::GetGraphic()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return CMapXGraphic(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXAnnotation operations


/////////////////////////////////////////////////////////////////////////////
// CMapXText properties
// NOTE: ***OBSOLETE***: Do not use this class use CMapXGraphic instead

CString CMapXText::GetCaption()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXText::SetCaption(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

double CMapXText::GetX()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

void CMapXText::SetX(double propVal)
{
	SetProperty(0x2, VT_R8, propVal);
}

double CMapXText::GetY()
{
	double result;
	GetProperty(0x3, VT_R8, (void*)&result);
	return result;
}

void CMapXText::SetY(double propVal)
{
	SetProperty(0x3, VT_R8, propVal);
}

short CMapXText::GetPosition()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void CMapXText::SetPosition(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

CMapXStyle CMapXText::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x5, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXText::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x5, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXGraphic operations

/////////////////////////////////////////////////////////////////////////////
// CMapXGraphic properties
// Used for both Text and Symbol annotations

CString CMapXGraphic::GetCaption()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXGraphic::SetCaption(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

double CMapXGraphic::GetX()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

void CMapXGraphic::SetX(double propVal)
{
	SetProperty(0x2, VT_R8, propVal);
}

double CMapXGraphic::GetY()
{
	double result;
	GetProperty(0x3, VT_R8, (void*)&result);
	return result;
}

void CMapXGraphic::SetY(double propVal)
{
	SetProperty(0x3, VT_R8, propVal);
}

short CMapXGraphic::GetPosition()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void CMapXGraphic::SetPosition(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

CMapXStyle CMapXGraphic::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x5, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXGraphic::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x5, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXGraphic operations

/////////////////////////////////////////////////////////////////////////////
// CMapXLegendText properties

CString CMapXLegendText::GetText()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXLegendText::SetText(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

BOOL CMapXLegendText::GetVisible()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLegendText::SetVisible(BOOL bNewValue)
{
	SetProperty(0x2, VT_BOOL, bNewValue);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLegendText operations


/////////////////////////////////////////////////////////////////////////////
// CMapXLegendTexts properties

LPENUMVARIANT CMapXLegendTexts::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

BOOL CMapXLegendTexts::GetAutoGenerate()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLegendTexts::SetAutoGenerate(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

long CMapXLegendTexts::GetCount()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

CMapXLegendText CMapXLegendTexts::GetAllOthersText()
{
	LPDISPATCH result;
	GetProperty(0x4, VT_DISPATCH, (void*)&result);
	return CMapXLegendText(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLegendTexts operations

CMapXLegendText CMapXLegendTexts::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXLegendText(result);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXTitle properties

CString CMapXTitle::GetCaption()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXTitle::SetCaption(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CMapXStyle CMapXTitle::GetTextStyle()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXTitle::SetTextStyle(LPDISPATCH propVal)
{
	SetProperty(0x2, VT_DISPATCH, propVal);
}

BOOL CMapXTitle::GetVisible()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void CMapXTitle::SetVisible(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

double CMapXTitle::GetX()
{
	double result;
	GetProperty(0x4, VT_R8, (void*)&result);
	return result;
}

void CMapXTitle::SetX(double propVal)
{
	SetProperty(0x4, VT_R8, propVal);
}

double CMapXTitle::GetY()
{
	double result;
	GetProperty(0x5, VT_R8, (void*)&result);
	return result;
}

void CMapXTitle::SetY(double propVal)
{
	SetProperty(0x5, VT_R8, propVal);
}

BOOL CMapXTitle::GetEditable()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CMapXTitle::SetEditable(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

short CMapXTitle::GetPosition()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}

void CMapXTitle::SetPosition(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}

BOOL CMapXTitle::GetBorder()
{
	BOOL result;
	GetProperty(0x8, VT_BOOL, (void*)&result);
	return result;
}

void CMapXTitle::SetBorder(BOOL propVal)
{
	SetProperty(0x8, VT_BOOL, propVal);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXLabelProperties properties

CMapXStyle CMapXLabelProperties::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXLabelProperties::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

BOOL CMapXLabelProperties::GetVisible()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetVisible(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL CMapXLabelProperties::GetLabelZoom()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetLabelZoom(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

double CMapXLabelProperties::GetLabelZoomMin()
{
	double result;
	GetProperty(0x4, VT_R8, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetLabelZoomMin(double propVal)
{
	SetProperty(0x4, VT_R8, propVal);
}

double CMapXLabelProperties::GetLabelZoomMax()
{
	double result;
	GetProperty(0x5, VT_R8, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetLabelZoomMax(double propVal)
{
	SetProperty(0x5, VT_R8, propVal);
}

short CMapXLabelProperties::GetLineType()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetLineType(short propVal)
{
	SetProperty(0x6, VT_I2, propVal);
}

short CMapXLabelProperties::GetOffset()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetOffset(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}

BOOL CMapXLabelProperties::GetParallel()
{
	BOOL result;
	GetProperty(0x8, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetParallel(BOOL propVal)
{
	SetProperty(0x8, VT_BOOL, propVal);
}

CMapXDataset CMapXLabelProperties::GetDataset()
{
	LPDISPATCH result;
	GetProperty(0x9, VT_DISPATCH, (void*)&result);
	return CMapXDataset(result);
}

void CMapXLabelProperties::SetDataset(LPDISPATCH propVal)
{
	SetProperty(0x9, VT_DISPATCH, propVal);
}

BOOL CMapXLabelProperties::GetDuplicate()
{
	BOOL result;
	GetProperty(0xa, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetDuplicate(BOOL propVal)
{
	SetProperty(0xa, VT_BOOL, propVal);
}

BOOL CMapXLabelProperties::GetOverlap()
{
	BOOL result;
	GetProperty(0xb, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetOverlap(BOOL propVal)
{
	SetProperty(0xb, VT_BOOL, propVal);
}

short CMapXLabelProperties::GetLabelMax()
{
	short result;
	GetProperty(0xc, VT_I2, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetLabelMax(short propVal)
{
	SetProperty(0xc, VT_I2, propVal);
}

CMapXField CMapXLabelProperties::GetDataField()
{
	LPDISPATCH result;
	GetProperty(0xd, VT_DISPATCH, (void*)&result);
	return CMapXField(result);
}

void CMapXLabelProperties::SetDataField(LPDISPATCH propVal)
{
	SetProperty(0xd, VT_DISPATCH, propVal);
}

short CMapXLabelProperties::GetPosition()
{
	short result;
	GetProperty(0xe, VT_I2, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetPosition(short propVal)
{
	SetProperty(0xe, VT_I2, propVal);
}

BOOL CMapXLabelProperties::GetPartialSegments()
{
	BOOL result;
	GetProperty(0xf, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetPartialSegments(BOOL propVal)
{
	SetProperty(0xf, VT_BOOL, propVal);
}

BOOL CMapXLabelProperties::GetLabelPartialObjects()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetLabelPartialObjects(BOOL propVal)
{
	SetProperty(0x10, VT_BOOL, propVal);
}

short CMapXLabelProperties::GetLabelAlong()
{
	short result;
	GetProperty(0x11, VT_I2, (void*)&result);
	return result;
}

void CMapXLabelProperties::SetLabelAlong(short propVal)
{
	SetProperty(0x11, VT_I2, propVal);
}



/////////////////////////////////////////////////////////////////////////////
// CMapXLabelProperties operations


/////////////////////////////////////////////////////////////////////////////
// CMapXBindLayer properties

CString CMapXBindLayer::GetLayerName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXBindLayer::SetLayerName(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

VARIANT CMapXBindLayer::GetRefColumn1()
{
	VARIANT result;
	GetProperty(0x2, VT_VARIANT, (void*)&result);
	return result;
}

void CMapXBindLayer::SetRefColumn1(const VARIANT& propVal)
{
	SetProperty(0x2, VT_VARIANT, &propVal);
}

VARIANT CMapXBindLayer::GetRefColumn2()
{
	VARIANT result;
	GetProperty(0x3, VT_VARIANT, (void*)&result);
	return result;
}

void CMapXBindLayer::SetRefColumn2(const VARIANT& propVal)
{
	SetProperty(0x3, VT_VARIANT, &propVal);
}

short CMapXBindLayer::GetLayerType()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void CMapXBindLayer::SetLayerType(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

CString CMapXBindLayer::GetReferenceLayer()
{
	CString result;
	GetProperty(0x5, VT_BSTR, (void*)&result);
	return result;
}

void CMapXBindLayer::SetReferenceLayer(LPCTSTR propVal)
{
	SetProperty(0x5, VT_BSTR, propVal);
}

CMapXCoordSys CMapXBindLayer::GetCoordSys()
{
	LPDISPATCH result;
	GetProperty(0x6, VT_DISPATCH, (void*)&result);
	return CMapXCoordSys(result);
}

void CMapXBindLayer::SetCoordSys(LPDISPATCH propVal)
{
	SetProperty(0x6, VT_DISPATCH, propVal);
}

CString CMapXBindLayer::GetFilespec()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}

void CMapXBindLayer::SetFilespec(LPCTSTR propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}

short CMapXBindLayer::GetKeyLength()
{
	short result;
	GetProperty(0x8, VT_I2, (void*)&result);
	return result;
}

void CMapXBindLayer::SetKeyLength(short propVal)
{
	SetProperty(0x8, VT_I2, propVal);
}

long CMapXBindLayer::GetReferenceLayerField()
{
	long result;
	GetProperty(0x9, VT_I4, (void*)&result);
	return result;
}

void CMapXBindLayer::SetReferenceLayerField(long propVal)
{
	SetProperty(0x9, VT_I4, propVal);
}

BOOL CMapXBindLayer::GetOverwriteFile()
{
	short result;
	GetProperty(0xA, VT_BOOL, (void*)&result);
	return result;
}

void CMapXBindLayer::SetOverwriteFile(BOOL propVal)
{
	SetProperty(0xA, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXBindLayer operations


/////////////////////////////////////////////////////////////////////////////
// CMapXRangeCategories properties

LPENUMVARIANT CMapXRangeCategories::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXRangeCategories::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

CMapXRangeCategory CMapXRangeCategories::GetAllOthersCategory()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return CMapXRangeCategory(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRangeCategories operations

CMapXRangeCategory CMapXRangeCategories::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXRangeCategory(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXIndividualValueCategories properties

LPENUMVARIANT CMapXIndividualValueCategories::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXIndividualValueCategories::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

CMapXIndividualValueCategory CMapXIndividualValueCategories::GetAllOthersCategory()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return CMapXIndividualValueCategory(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXIndividualValueCategories operations

CMapXIndividualValueCategory CMapXIndividualValueCategories::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXIndividualValueCategory(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXMultivarCategories properties

LPENUMVARIANT CMapXMultivarCategories::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXMultivarCategories::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXThemeCategories operations

CMapXMultivarCategory CMapXMultivarCategories::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXMultivarCategory(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRectangle properties

double CMapXRectangle::GetXMin()
{
	double result;
	GetProperty(0x1, VT_R8, (void*)&result);
	return result;
}

double CMapXRectangle::GetYMin()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

double CMapXRectangle::GetXMax()
{
	double result;
	GetProperty(0x3, VT_R8, (void*)&result);
	return result;
}

double CMapXRectangle::GetYMax()
{
	double result;
	GetProperty(0x4, VT_R8, (void*)&result);
	return result;
}

double CMapXRectangle::GetHeight()
{
	double result;
	GetProperty(0x5, VT_R8, (void*)&result);
	return result;
}

double CMapXRectangle::GetWidth()
{
	double result;
	GetProperty(0x6, VT_R8, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRectangle operations

void CMapXRectangle::Set(double X1, double Y1, double X2, double Y2)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 X1, Y1, X2, Y2);
}

void CMapXRectangle::Offset(double deltaX, double deltaY)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 deltaX, deltaY);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXLayerFind properties

CMapXLayer CMapXLayerFind::GetRefineLayer()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return CMapXLayer(result);
}

void CMapXLayerFind::SetRefineLayer(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

BOOL CMapXLayerFind::GetAbbreviations()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayerFind::SetAbbreviations(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL CMapXLayerFind::GetClosestAddr()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayerFind::SetClosestAddr(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL CMapXLayerFind::GetOtherBoundary()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLayerFind::SetOtherBoundary(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

CMapXField CMapXLayerFind::GetFindField()
{
	LPDISPATCH result;
	GetProperty(0x5, VT_DISPATCH, (void*)&result);
	return CMapXField(result);
}

void CMapXLayerFind::SetFindField(LPDISPATCH propVal)
{
	SetProperty(0x5, VT_DISPATCH, propVal);
}

CMapXField CMapXLayerFind::GetRefineField()
{
	LPDISPATCH result;
	GetProperty(0x6, VT_DISPATCH, (void*)&result);
	return CMapXField(result);
}

void CMapXLayerFind::SetRefineField(LPDISPATCH propVal)
{
	SetProperty(0x6, VT_DISPATCH, propVal);
}

CMapXDataset CMapXLayerFind::GetFindDataset()
{
	LPDISPATCH result;
	GetProperty(0x7, VT_DISPATCH, (void*)&result);
	return CMapXDataset(result);
}

void CMapXLayerFind::SetFindDataset(LPDISPATCH propVal)
{
	SetProperty(0x7, VT_DISPATCH, propVal);
}

CMapXDataset CMapXLayerFind::GetRefineDataset()
{
	LPDISPATCH result;
	GetProperty(0x8, VT_DISPATCH, (void*)&result);
	return CMapXDataset(result);
}

void CMapXLayerFind::SetRefineDataset(LPDISPATCH propVal)
{
	SetProperty(0x8, VT_DISPATCH, propVal);
}

long CMapXLayerFind::GetCloseMatchMax()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}

void CMapXLayerFind::SetCloseMatchMax(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLayerFind operations

CMapXFindFeature CMapXLayerFind::Search(LPCTSTR Address, const VARIANT& RefineBoundary)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Address, &RefineBoundary);
	return CMapXFindFeature(result);
}

CMapXFindResult CMapXLayerFind::SearchEx(LPCTSTR Address, const VARIANT& RefineBoundary)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Address, &RefineBoundary);
	return CMapXFindResult(result);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXFindFeature properties

long CMapXFindFeature::GetFeatureID()
{
	long result;
	GetProperty(0x10001, VT_I4, (void*)&result);
	return result;
}

short CMapXFindFeature::GetType()
{
	short result;
	GetProperty(0x10002, VT_I2, (void*)&result);
	return result;
}

void CMapXFindFeature::SetType(short propVal)
{
	SetProperty(0x10002, VT_I2, propVal);
}

double CMapXFindFeature::GetLength()
{
	double result;
	GetProperty(0x10003, VT_R8, (void*)&result);
	return result;
}

double CMapXFindFeature::GetCenterX()
{
	double result;
	GetProperty(0x10004, VT_R8, (void*)&result);
	return result;
}

double CMapXFindFeature::GetCenterY()
{
	double result;
	GetProperty(0x10005, VT_R8, (void*)&result);
	return result;
}

CMapXStyle CMapXFindFeature::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0x10006, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXFindFeature::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0x10006, VT_DISPATCH, propVal);
}

CMapXRectangle CMapXFindFeature::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x10007, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

CString CMapXFindFeature::GetCaption()
{
	CString result;
	GetProperty(0x10008, VT_BSTR, (void*)&result);
	return result;
}

void CMapXFindFeature::SetCaption(LPCTSTR propVal)
{
	SetProperty(0x10008, VT_BSTR, propVal);
}

CMapXParts CMapXFindFeature::GetParts()
{
	LPDISPATCH result;
	GetProperty(0x10009, VT_DISPATCH, (void*)&result);
	return CMapXParts(result);
}

double CMapXFindFeature::GetArea()
{
	double result;
	GetProperty(0x1000a, VT_R8, (void*)&result);
	return result;
}

CMapXLayer CMapXFindFeature::GetLayer()
{
	LPDISPATCH result;
	GetProperty(0x1000b, VT_DISPATCH, (void*)&result);
	return CMapXLayer(result);
}

CMapXPoint CMapXFindFeature::GetPoint()
{
	LPDISPATCH result;
	GetProperty(0x1000c, VT_DISPATCH, (void*)&result);
	return CMapXPoint(result);
}

void CMapXFindFeature::SetPoint(LPDISPATCH propVal)
{
	SetProperty(0x1000c, VT_DISPATCH, propVal);
}

CMapXPoint CMapXFindFeature::GetLabelPoint()
{
	LPDISPATCH result;
	GetProperty(0x1000d, VT_DISPATCH, (void*)&result);
	return CMapXPoint(result);
}

double CMapXFindFeature::GetPerimeter()
{
	double result;
	GetProperty(0x1000e, VT_R8, (void*)&result);
	return result;
}

BOOL CMapXFindFeature::GetSmooth()
{
	BOOL result;
	GetProperty(0x1000f, VT_BOOL, (void*)&result);
	return result;
}

void CMapXFindFeature::SetSmooth(BOOL propVal)
{
	SetProperty(0x1000f, VT_BOOL, propVal);
}

CString CMapXFindFeature::GetName()
{
	CString result;
	GetProperty(0x10010, VT_BSTR, (void*)&result);
	return result;
}

CString CMapXFindFeature::GetKeyValue()
{
	CString result;
	GetProperty(0x10011, VT_BSTR, (void*)&result);
	return result;
}

void CMapXFindFeature::SetKeyValue(LPCTSTR propVal)
{
	SetProperty(0x10011, VT_BSTR, propVal);
}

CString CMapXFindFeature::GetFeatureKey()
{
	CString result;
	GetProperty(0x10017, VT_BSTR, (void*)&result);
	return result;
}

short CMapXFindFeature::GetFindRC()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFindFeature operations

void CMapXFindFeature::Update(const VARIANT& UpdateFeature, const VARIANT& RowValues)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x10012, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &UpdateFeature, &RowValues);
}

void CMapXFindFeature::Offset(double deltaX, double deltaY)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x10013, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 deltaX, deltaY);
}

void CMapXFindFeature::Attach(LPDISPATCH Map)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x10014, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Map);
}

LPDISPATCH CMapXFindFeature::Clone()
{
	LPDISPATCH result;
	InvokeHelper(0x10015, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT CMapXFindFeature::GetNodes(const VARIANT& CSys)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10016, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&CSys);
	return result;
}

void CMapXFindFeature::SetNodes(const VARIANT& CSys, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x10016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &CSys, &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXFindResult properties

BOOL CMapXFindResult::GetExactMatch()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXFindResult::GetSubstitute()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXFindResult::GetAddressOutOfRange()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXFindResult::GetIntersectionNotFound()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXFindResult::GetMultipleMatches()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXFindResult::GetRefineRegion()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

short CMapXFindResult::GetFindRC()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}

CMapXFindMatches CMapXFindResult::GetMatches()
{
	LPDISPATCH result;
	GetProperty(0x8, VT_DISPATCH, (void*)&result);
	return CMapXFindMatches(result);
}

CMapXFeature CMapXFindResult::GetMatchedFeature()
{
	LPDISPATCH result;
	GetProperty(0x9, VT_DISPATCH, (void*)&result);
	return CMapXFeature(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFindMatches properties

LPENUMVARIANT CMapXFindMatches::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXFindMatches::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFindMatches operations

CMapXFindMatch CMapXFindMatches::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXFindMatch(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFindMatch properties

long CMapXFindMatch::GetFeatureID()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

CString CMapXFindMatch::GetName()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

long CMapXFindMatch::GetScore()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

CString CMapXFindMatch::GetFeatureKey()
{
	CString result;
	GetProperty(0x4, VT_BSTR, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXGeosets properties

LPENUMVARIANT CMapXGeosets::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXGeosets::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXGeosets operations

CMapXGeoset CMapXGeosets::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXGeoset(result);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXGeoset properties

CMapXPoint CMapXGeoset::GetCentroid()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return CMapXPoint(result);
}

CString CMapXGeoset::GetPathName()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

CString CMapXGeoset::GetUserName()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXGeoset operations


/////////////////////////////////////////////////////////////////////////////
// CMapXParts properties

LPENUMVARIANT CMapXParts::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXParts::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXParts operations

CMapXPoints CMapXParts::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXPoints(result);
}

void CMapXParts::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

CMapXPoints CMapXParts::Add(LPDISPATCH Points)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Points);
	return CMapXPoints(result);
}

void CMapXParts::RemoveAll()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXPoints properties

LPENUMVARIANT CMapXPoints::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXPoints::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXPoints operations

CMapXPoint CMapXPoints::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXPoint(result);
}

void CMapXPoints::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

CMapXPoint CMapXPoints::Add(LPDISPATCH Point, const VARIANT& Position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Point, &Position);
	return CMapXPoint(result);
}

CMapXPoint CMapXPoints::AddXY(double X, double Y, const VARIANT& Position)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		X, Y, &Position);
	return CMapXPoint(result);
}

void CMapXPoints::RemoveAll()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapXPoints::GetXY(long Index, double *dX, double *dY)
{
	static BYTE parms[] = 
		VTS_I4 VTS_PR8 VTS_PR8;

	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, dX, dY);
}

double CMapXPoints::X(long Index)
{
	static BYTE parms[] = 
		VTS_I4;
	double dX;

	InvokeHelper(0x9, DISPATCH_METHOD, VT_R8, &dX, parms, Index);

	return dX;
}

double CMapXPoints::Y(long Index)
{
	static BYTE parms[] = 
		VTS_I4;
	double dY;

	InvokeHelper(0xa, DISPATCH_METHOD, VT_R8, &dY, parms, Index);

	return dY;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXPoint properties

double CMapXPoint::GetX()
{
	double result;
	GetProperty(0x1, VT_R8, (void*)&result);
	return result;
}

double CMapXPoint::GetY()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXPoint operations

void CMapXPoint::Set(double X, double Y)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 X, Y);
}

void CMapXPoint::Offset(double deltaX, double deltaY)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 deltaX, deltaY);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXFeatures properties

LPENUMVARIANT CMapXFeatures::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXFeatures::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

CMapXRectangle CMapXFeatures::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x8, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFeatures operations

CMapXFeature CMapXFeatures::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXFeature(result);
}

CMapXFeatures CMapXFeatures::Clone()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXFeatures(result);
}

void CMapXFeatures::Add(LPDISPATCH Source)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Source);
}

void CMapXFeatures::Common(LPDISPATCH Source)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Source);
}

void CMapXFeatures::Remove(const VARIANT& Source)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source);
}

void CMapXFeatures::Replace(LPDISPATCH Source)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Source);
}

void CMapXFeatures::AddByID(const VARIANT& FeatureID)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FeatureID);
}

void CMapXFeatures::RemoveByID(const VARIANT& FeatureID)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FeatureID);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXDatum properties

short CMapXDatum::GetEllipsoid()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

double CMapXDatum::GetShiftX()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetShiftY()
{
	double result;
	GetProperty(0x3, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetShiftZ()
{
	double result;
	GetProperty(0x4, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetRotateX()
{
	double result;
	GetProperty(0x5, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetRotateY()
{
	double result;
	GetProperty(0x6, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetRotateZ()
{
	double result;
	GetProperty(0x7, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetScaleAdjust()
{
	double result;
	GetProperty(0x8, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetPrimeMeridian()
{
	double result;
	GetProperty(0x9, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetSemiMajorAxis()
{
	double result;
	GetProperty(0xa, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetSemiMinorAxis()
{
	double result;
	GetProperty(0xb, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetFlattening()
{
	double result;
	GetProperty(0xc, VT_R8, (void*)&result);
	return result;
}

double CMapXDatum::GetEccentricity()
{
	double result;
	GetProperty(0xd, VT_R8, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXDatum operations

void CMapXDatum::Set(short Ellipsoid, double ShiftX, double ShiftY, double ShiftZ, double RotateX, double RotateY, double RotateZ, double ScaleAdjust, double PrimeMeridian)
{
	static BYTE parms[] =
		VTS_I2 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Ellipsoid, ShiftX, ShiftY, ShiftZ, RotateX, RotateY, RotateZ, ScaleAdjust, PrimeMeridian);
}

void CMapXDatum::SetFromList(short DatumNum)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DatumNum);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXAffineTransform properties

short CMapXAffineTransform::GetUnits()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

double CMapXAffineTransform::GetA()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

double CMapXAffineTransform::GetB()
{
	double result;
	GetProperty(0x3, VT_R8, (void*)&result);
	return result;
}

double CMapXAffineTransform::GetC()
{
	double result;
	GetProperty(0x4, VT_R8, (void*)&result);
	return result;
}

double CMapXAffineTransform::GetD()
{
	double result;
	GetProperty(0x5, VT_R8, (void*)&result);
	return result;
}

double CMapXAffineTransform::GetE()
{
	double result;
	GetProperty(0x6, VT_R8, (void*)&result);
	return result;
}

double CMapXAffineTransform::GetF()
{
	double result;
	GetProperty(0x7, VT_R8, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXAffineTransform operations

void CMapXAffineTransform::Set(short Units, double A, double B, double C, double D, double E, double F)
{
	static BYTE parms[] =
		VTS_I2 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Units, A, B, C, D, E, F);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXCoordSys properties

short CMapXCoordSys::GetType()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

CMapXDatum CMapXCoordSys::GetDatum()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return CMapXDatum(result);
}

short CMapXCoordSys::GetUnits()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}

CMapXRectangle CMapXCoordSys::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x4, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

double CMapXCoordSys::GetOriginLongitude()
{
	double result;
	GetProperty(0x5, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetOriginLatitude()
{
	double result;
	GetProperty(0x6, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetStandardParallelOne()
{
	double result;
	GetProperty(0x7, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetStandardParallelTwo()
{
	double result;
	GetProperty(0x8, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetAzimuth()
{
	double result;
	GetProperty(0x9, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetScaleFactor()
{
	double result;
	GetProperty(0xa, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetFalseEasting()
{
	double result;
	GetProperty(0xb, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetFalseNorthing()
{
	double result;
	GetProperty(0xc, VT_R8, (void*)&result);
	return result;
}

double CMapXCoordSys::GetRange()
{
	double result;
	GetProperty(0xd, VT_R8, (void*)&result);
	return result;
}

CMapXAffineTransform CMapXCoordSys::GetAffineTransform()
{
	LPDISPATCH result;
	GetProperty(0xe, VT_DISPATCH, (void*)&result);
	return CMapXAffineTransform(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXCoordSys operations

void CMapXCoordSys::Set(short Type, const VARIANT& Datum, const VARIANT& Units, const VARIANT& OriginLongitude, const VARIANT& OriginLatitude, const VARIANT& StandardParallelOne, const VARIANT& StandardParallelTwo, const VARIANT& Azimuth, 
		const VARIANT& ScaleFactor, const VARIANT& FalseEasting, const VARIANT& FalseNorthing, const VARIANT& Range, const VARIANT& Bounds, const VARIANT& AffineTransform)
{
	static BYTE parms[] =
		VTS_I2 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Type, &Datum, &Units, &OriginLongitude, &OriginLatitude, &StandardParallelOne, &StandardParallelTwo, &Azimuth, &ScaleFactor, &FalseEasting, &FalseNorthing, &Range, &Bounds, &AffineTransform);
}

BOOL CMapXCoordSys::PickCoordSys(const VARIANT& HelpFile, const VARIANT& HelpID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&HelpFile, &HelpID);
	return result;
}

CMapXCoordSys CMapXCoordSys::Clone()
{
	LPDISPATCH result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXCoordSys(result);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXNotesViewInfo properties

CString CMapXNotesViewInfo::GetServer()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesViewInfo::SetServer(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CMapXNotesViewInfo::GetDatabase()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesViewInfo::SetDatabase(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

CString CMapXNotesViewInfo::GetView()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesViewInfo::SetView(LPCTSTR propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXNotesViewInfo operations


/////////////////////////////////////////////////////////////////////////////
// CMapXNotesQueryInfo properties

CString CMapXNotesQueryInfo::GetServer()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetServer(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CMapXNotesQueryInfo::GetDatabase()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetDatabase(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

CString CMapXNotesQueryInfo::GetQuery()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetQuery(LPCTSTR propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}

CString CMapXNotesQueryInfo::GetBeginDate()
{
	CString result;
	GetProperty(0x4, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetBeginDate(LPCTSTR propVal)
{
	SetProperty(0x4, VT_BSTR, propVal);
}

CString CMapXNotesQueryInfo::GetEndDate()
{
	CString result;
	GetProperty(0x5, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetEndDate(LPCTSTR propVal)
{
	SetProperty(0x5, VT_BSTR, propVal);
}

BOOL CMapXNotesQueryInfo::GetFullTextSearch()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetFullTextSearch(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

CString CMapXNotesQueryInfo::GetDefaultStringValue()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetDefaultStringValue(LPCTSTR propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}

double CMapXNotesQueryInfo::GetDefaultNumericValue()
{
	double result;
	GetProperty(0x8, VT_R8, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetDefaultNumericValue(double propVal)
{
	SetProperty(0x8, VT_R8, propVal);
}

long CMapXNotesQueryInfo::GetMaxNumDocs()
{
	long result;
	GetProperty(0x9, VT_I4, (void*)&result);
	return result;
}

void CMapXNotesQueryInfo::SetMaxNumDocs(long propVal)
{
	SetProperty(0x9, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXNotesQueryInfo operations

/////////////////////////////////////////////////////////////////////////////
// CMapXODBCQueryInfo properties

CString CMapXODBCQueryInfo::GetDataSource()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXODBCQueryInfo::SetDataSource(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CMapXODBCQueryInfo::GetSqlQuery()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CMapXODBCQueryInfo::SetSqlQuery(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

CString CMapXODBCQueryInfo::GetConnectString()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}

void CMapXODBCQueryInfo::SetConnectString(LPCTSTR propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXOCIQueryInfo properties

CString CMapXOCIQueryInfo::GetSqlQuery()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CMapXOCIQueryInfo::SetSqlQuery(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

CString CMapXOCIQueryInfo::GetConnectString()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CMapXOCIQueryInfo::SetConnectString(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXBitmapSymbols properties

LPENUMVARIANT CMapXBitmapSymbols::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXBitmapSymbols::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

CMapXBitmapSymbol CMapXBitmapSymbols::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXBitmapSymbol(result);
}

void CMapXBitmapSymbols::Refresh()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapXBitmapSymbols::Unload()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXBitmapSymbol properties

CString CMapXBitmapSymbol::GetName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXResolveObject properties
CString CMapXResolveObject::GetTableName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

long CMapXResolveObject::GetSourceMatch()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

long CMapXResolveObject::GetTableMatch()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CMapXResolveObjects properties

LPENUMVARIANT CMapXResolveObjects::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXResolveObjects::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXResolveObjects operations

CMapXResolveObject CMapXResolveObjects::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXResolveObject(result);
}


/* MapX Events for Reference

void CMapXEvents::Click()
{
	InvokeHelper(DISPID_CLICK, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapXEvents::DblClick()
{
	InvokeHelper(DISPID_DBLCLICK, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapXEvents::Error(short Number, BSTR* Description, long Scode, LPCTSTR Source, LPCTSTR HelpFile, long HelpContext, BOOL* CancelDisplay)
{
	static BYTE parms[] =
		VTS_I2 VTS_PBSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_PBOOL;
	InvokeHelper(DISPID_ERROREVENT, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Number, Description, Scode, Source, HelpFile, HelpContext, CancelDisplay);
}

void CMapXEvents::KeyDown(short* KeyCode, short Shift)
{
	static BYTE parms[] =
		VTS_PI2 VTS_I2;
	InvokeHelper(DISPID_KEYDOWN, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 KeyCode, Shift);
}

void CMapXEvents::KeyPress(short* KeyAscii)
{
	static BYTE parms[] =
		VTS_PI2;
	InvokeHelper(DISPID_KEYPRESS, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 KeyAscii);
}

void CMapXEvents::KeyUp(short* KeyCode, short Shift)
{
	static BYTE parms[] =
		VTS_PI2 VTS_I2;
	InvokeHelper(DISPID_KEYUP, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 KeyCode, Shift);
}

void CMapXEvents::MouseMove(short* Button, short* Shift, float* X, float* Y)
{
	static BYTE parms[] =
		VTS_PI2 VTS_PI2 VTS_PR4 VTS_PR4;
	InvokeHelper(DISPID_MOUSEMOVE, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Button, Shift, X, Y);
}

void CMapXEvents::MouseDown(short* Button, short* Shift, float* X, float* Y)
{
	static BYTE parms[] =
		VTS_PI2 VTS_PI2 VTS_PR4 VTS_PR4;
	InvokeHelper(DISPID_MOUSEDOWN, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Button, Shift, X, Y);
}

void CMapXEvents::MouseUp(short* Button, short* Shift, float* X, float* Y)
{
	static BYTE parms[] =
		VTS_PI2 VTS_PI2 VTS_PR4 VTS_PR4;
	InvokeHelper(DISPID_MOUSEUP, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Button, Shift, X, Y);
}

void CMapXEvents::SelectionChanged()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapXEvents::ResolveDataBind(short Flag, short NumMatches, const VARIANT& Matches, short* Choice, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_VARIANT VTS_PI2 VTS_PBOOL;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Flag, NumMatches, &Matches, Choice, Cancel);
}

void CMapXEvents::ToolUsed(short ToolNum, double X1, double Y1, double X2, double Y2, double Distance, BOOL Shift, BOOL Ctrl, BOOL* EnableDefault)
{
	static BYTE parms[] =
		VTS_I2 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_BOOL VTS_BOOL VTS_PBOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ToolNum, X1, Y1, X2, Y2, Distance, Shift, Ctrl, EnableDefault);
}

void CMapXEvents::RequestData(LPCTSTR DataSetName, long Row, short Field, VARIANT* Value, BOOL* Done)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I2 VTS_PVARIANT VTS_PBOOL;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DataSetName, Row, Field, Value, Done);
}

void CMapXEvents::DataMismatch(LPCTSTR DataSetName, long Row, BSTR* GeoFieldValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PBSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DataSetName, Row, GeoFieldValue);
}

void CMapXEvents::MapViewChanged()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMapXEvents::AnnotationAdded(LPDISPATCH Annotation)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Annotation);
}

void CMapXEvents::AnnotationChanged(short ChangeType, LPDISPATCH Annotation, BOOL* EnableDefault)
{
	static BYTE parms[] =
		VTS_I2 VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ChangeType, Annotation, EnableDefault);
}

void CMapXEvents::ThemeModifyRequested(LPDISPATCH Theme)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Theme);
}

void CMapXEvents::DrawUserLayer(LPDISPATCH Layer, long hDCOutput, long hDCAttrib, LPDISPATCH RectFull, LPDISPATCH RectInvalid)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4 VTS_I4 VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Layer, hDCOutput, hDCAttrib, RectFull, RectInvalid);
}

void CMapXEvents::PolyToolUsed(short ToolNum, long Flags, LPDISPATCH Points, BOOL bShift, BOOL bCtrl, BOOL* EnableDefault)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4 VTS_DISPATCH VTS_BOOL VTS_BOOL VTS_PBOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ToolNum, Flags, Points, bShift, bCtrl, EnableDefault);
}

void ResolveDataBindEx(short Flag, short NumMatches, const VARIANT& Matches, short* Choice, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_VARIANT VTS_PI2 VTS_PBOOL;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Flag, NumMatches, &Matches, Choice, Cancel);
}

void MapDraw(short Flag)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flag);
}


void AddFeatureToolUsed(short ToolNum, long Flags, IDispatch* Feature, VARIANT_BOOL bShift, VARIANT_BOOL bCtrl, VARIANT_BOOL* EnableDefault)
{
	static BYTE parms[] = 
		VTS_I2 VTS_I4 VTS_DISPATCH VTS_BOOL VTS_BOOL VTS_PBOOL;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
			ChangeType, ChangingLabels, EnableDefault);
}

void LabelChanged(short ChangeType, CMapXLabels* ChangingLabels, BOOL* EnableDefault)
{
	static BYTE parms[] = 
		VTS_I2, VTS_VARIANT, VTS_PBOOL;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
			ChangeType, ChangingLabels, EnableDefault);
}

*/

/////////////////////////////////////////////////////////////////////////////
// CMapXRowValues properties

LPENUMVARIANT CMapXRowValues::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXRowValues::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

BOOL CMapXRowValues::GetReadOnly()
{
	BOOL result;
	GetProperty(0x7, VT_BOOL, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRowValues operations

CMapXRowValue CMapXRowValues::Item(const VARIANT& Index)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		&Index);
	return CMapXRowValue(pDispatch);
}

void CMapXRowValues::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

CMapXRowValue CMapXRowValues::Add(LPDISPATCH RowValue)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		RowValue);
	return CMapXRowValue(pDispatch);
}

void CMapXRowValues::RemoveAll()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CMapXRowValues CMapXRowValues::Clone()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CMapXRowValues(pDispatch);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRowValue properties

BOOL CMapXRowValue::GetReadOnly()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

LPDISPATCH CMapXRowValue::GetDataset()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return result;
}

void CMapXRowValue::SetDataset(LPDISPATCH propVal)
{
	SetProperty(0x2, VT_DISPATCH, propVal);
}

LPDISPATCH CMapXRowValue::GetField()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return result;
}

void CMapXRowValue::SetField(LPDISPATCH propVal)
{
	SetProperty(0x3, VT_DISPATCH, propVal);
}

VARIANT CMapXRowValue::GetValue()
{
	VARIANT result;
	GetProperty(0x4, VT_VARIANT, (void*)&result);
	return result;
}

void CMapXRowValue::SetValue(const VARIANT& propVal)
{
	SetProperty(0x4, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXRowValue operations


/////////////////////////////////////////////////////////////////////////////
// CMapXLayerInfo properties

short CMapXLayerInfo::GetType()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

void CMapXLayerInfo::SetType(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLayerInfo operations

void CMapXLayerInfo::AddParameter(LPCTSTR ParamName, const VARIANT& Param)
{
	static BYTE parms[] =	VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ParamName, &Param);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXVariables properties

LPENUMVARIANT CMapXVariables::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXVariables::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXVariables operations

CMapXVariable CMapXVariables::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXVariable(result);
}

void CMapXVariables::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

CMapXVariable CMapXVariables::Add(LPCTSTR Name, const VARIANT& Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &Value);
	return CMapXVariable(result);
}

void CMapXVariables::RemoveAll()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CMapXVariables CMapXVariables::Clone()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return CMapXVariables(result);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXVariable properties

CString CMapXVariable::GetName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

VARIANT CMapXVariable::GetValue()
{
	VARIANT result;
	GetProperty(0x2, VT_VARIANT, (void*)&result);
	return result;
}

void CMapXVariable::SetValue(const VARIANT& propVal)
{
	SetProperty(0x2, VT_VARIANT, &propVal);
}

CLSID GetClassID(LPCTSTR pszProgramID)
{	
	CLSID clsid;
	USES_CONVERSION;
	HRESULT hr = CLSIDFromProgID(T2COLE(pszProgramID), &clsid);
	if(hr != S_OK)
	{
		AfxThrowOleException(hr);
	}
	return clsid;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXVariable operations

/////////////////////////////////////////////////////////////////////////////
// CMapXBoundsConstraint properties
BOOL CMapXBoundsConstraint::GetEnabled()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

CMapXRectangle CMapXBoundsConstraint::GetBounds()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return CMapXRectangle(result);
}

void CMapXBoundsConstraint::SetBounds(LPDISPATCH propVal)
{
	SetProperty(0x2, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXBoundsConstraint operations
void CMapXBoundsConstraint::Enable()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
void CMapXBoundsConstraint::Disable()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFeaturesConstraint properties
BOOL CMapXFeaturesConstraint::GetEnabled()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

CMapXFeatures CMapXFeaturesConstraint::GetFeatures()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return CMapXFeatures(result);
}

void CMapXFeaturesConstraint::SetFeatures(LPDISPATCH propVal)
{
	SetProperty(0x2, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXFeaturesConstraint operations
void CMapXFeaturesConstraint::Enable()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
void CMapXFeaturesConstraint::Disable()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMapXAllFeaturesConstraint properties
BOOL CMapXAllFeaturesConstraint::GetEnabled()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXAllFeaturesConstraint operations
void CMapXAllFeaturesConstraint::Enable()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
void CMapXAllFeaturesConstraint::Disable()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMapXLabel properties

double CMapXLabel::GetAnchorX()
{
	double result;
	GetProperty(0x1, VT_R8, (void*)&result);
	return result;
}

void CMapXLabel::SetAnchorX(double propVal)
{
	SetProperty(0x1, VT_R8, propVal);
}

double CMapXLabel::GetAnchorY()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

void CMapXLabel::SetAnchorY(double propVal)
{
	SetProperty(0x2, VT_R8, propVal);
}

short CMapXLabel::GetAngle()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}

void CMapXLabel::SetAngle(short propVal)
{
	SetProperty(0x3, VT_I2, propVal);
}

CString CMapXLabel::GetCaption()
{
	CString result;
	GetProperty(0x4, VT_BSTR, (void*)&result);
	return result;
}

void CMapXLabel::SetCaption(LPCTSTR propVal)
{
	SetProperty(0x4, VT_BSTR, propVal);
}

long CMapXLabel::GetLineType()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

void CMapXLabel::SetLineType(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}

BOOL CMapXLabel::GetMultiSegment()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabel::SetMultiSegment(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

long CMapXLabel::GetOffset()
{
	long result;
	GetProperty(0x7, VT_I4, (void*)&result);
	return result;
}

void CMapXLabel::SetOffset(long propVal)
{
	SetProperty(0x7, VT_I4, propVal);
}

short CMapXLabel::GetPosition()
{
	short result;
	GetProperty(0x8, VT_I2, (void*)&result);
	return result;
}

void CMapXLabel::SetPosition(short propVal)
{
	SetProperty(0x8, VT_I2, propVal);
}

BOOL CMapXLabel::GetSelected()
{
	BOOL result;
	GetProperty(0x9, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabel::SetSelected(BOOL propVal)
{
	SetProperty(0x9, VT_BOOL, propVal);
}

LPDISPATCH CMapXLabel::GetStyle()
{
	LPDISPATCH result;
	GetProperty(0xa, VT_DISPATCH, (void*)&result);
	return CMapXStyle(result);
}

void CMapXLabel::SetStyle(LPDISPATCH propVal)
{
	SetProperty(0xa, VT_DISPATCH, propVal);
}

BOOL CMapXLabel::GetVisible()
{
	BOOL result;
	GetProperty(0xb, VT_BOOL, (void*)&result);
	return result;
}

void CMapXLabel::SetVisible(BOOL propVal)
{
	SetProperty(0xb, VT_BOOL, propVal);
}

BOOL CMapXLabel::GetDrawn()
{
	BOOL result;
	GetProperty(0xc, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEdited()
{
	BOOL result;
	GetProperty(0xd, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedAnchor()
{
	BOOL result;
	GetProperty(0xe, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedAngle()
{
	BOOL result;
	GetProperty(0xf, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedCaption()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedLineStyle()
{
	BOOL result;
	GetProperty(0x11, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedLineType()
{
	BOOL result;
	GetProperty(0x12, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedMultiSegment()
{
	BOOL result;
	GetProperty(0x13, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedOffset()
{
	BOOL result;
	GetProperty(0x14, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedPosition()
{
	BOOL result;
	GetProperty(0x15, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedTextStyle()
{
	BOOL result;
	GetProperty(0x16, VT_BOOL, (void*)&result);
	return result;
}

BOOL CMapXLabel::GetEditedVisible()
{
	BOOL result;
	GetProperty(0x17, VT_BOOL, (void*)&result);
	return result;
}

LPDISPATCH CMapXLabel::GetLayer()
{
	LPDISPATCH result;
	GetProperty(0x18, VT_DISPATCH, (void*)&result);
	return CMapXLayer(result);
}

CString CMapXLabel::GetFeatureKey()
{
	CString result;
	GetProperty(0x19, VT_BSTR, (void*)&result);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CMapXLabels properties

LPENUMVARIANT CMapXLabels::GetEnumerator()
{
	LPENUMVARIANT pEnumVariant = 0;
	LPUNKNOWN pUnknown = 0;
	GetProperty(0xfffffffc, VT_UNKNOWN, (void*)&pUnknown);	
	if(pUnknown)
	{
		pUnknown->QueryInterface(IID_IEnumVARIANT, (void**)&pEnumVariant);
		pUnknown->Release();
	}	
	return pEnumVariant;
}

long CMapXLabels::GetCount()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CMapXLabels operations

CMapXLabel CMapXLabels::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return CMapXLabel(result);
}

