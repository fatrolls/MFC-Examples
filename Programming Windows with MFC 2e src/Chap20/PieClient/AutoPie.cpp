// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "autopie.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAutoPie properties

LPDISPATCH CAutoPie::GetChart()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return result;
}

void CAutoPie::SetChart(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

LPDISPATCH CAutoPie::GetWindow()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return result;
}

void CAutoPie::SetWindow(LPDISPATCH propVal)
{
	SetProperty(0x2, VT_DISPATCH, propVal);
}

LPDISPATCH CAutoPie::GetToolbar()
{
	LPDISPATCH result;
	GetProperty(0x3, VT_DISPATCH, (void*)&result);
	return result;
}

void CAutoPie::SetToolbar(LPDISPATCH propVal)
{
	SetProperty(0x3, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPie operations

void CAutoPie::Quit()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoChart properties

/////////////////////////////////////////////////////////////////////////////
// CAutoChart operations

BOOL CAutoChart::Save(LPCTSTR pszPath)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		pszPath);
	return result;
}

long CAutoChart::GetRevenue(short nQuarter)
{
	long result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		nQuarter);
	return result;
}

void CAutoChart::SetRevenue(short nQuarter, long nNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nQuarter, nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoWindow properties

BOOL CAutoWindow::GetVisible()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CAutoWindow::SetVisible(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoWindow operations

void CAutoWindow::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CAutoToolbar properties

BOOL CAutoToolbar::GetVisible()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CAutoToolbar::SetVisible(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoToolbar operations
