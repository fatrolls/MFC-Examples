//=================================================================
//
//  class: CHistory
//  File:  History.cpp
//
//  Purpose:
//		Provide output to custom control and file logging 
//      for status messages.
//      
// ===================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#include "stdafx.h"
#include "UTHistory.h"
#include "History.h"
#include "AboutDlg.h"

static const FONTDESC _fontdesc =
      {sizeof(FONTDESC), OLESTR("times new roman"), FONTSIZE( 14 ),
      FW_BOLD, ANSI_CHARSET, TRUE, FALSE, FALSE };


/////////////////////////////////////////////////////////////////////////////
// CHistory
/////////////////////////////////////////////////////////////////////////////

/*********************************************
CHistory
    Constructor
Params
    none
Return
	none
**********************************************/
CHistory::CHistory() : 
		m_ctlContainedWnd(_T(""), this, 1),
		m_bEnableLog(FALSE),					// Disable file log
		m_pIFont(NULL)							// Initialize IFont interface
{	
	// Run only in windowed mode
	m_bWindowOnly = TRUE;

	// Initialize text & back colors
	m_clrForeColor = m_ctlHistory.GetTextColor();
	m_clrBackColor = m_ctlHistory.GetBackColor(); 
}

/*********************************************
~CHistory
    Destructor
Params
    none
Return
	none
**********************************************/
CHistory::~CHistory()
{
}

/***************************************************
InterfaceSupportsErrorInfo
	Checks if specified interface supports error
	information.
Params
    riid	- inteface id
Return
	S_OK	- support error info
	S_FALSE - don't support error info
****************************************************/
STDMETHODIMP CHistory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IHistory,
	};
	for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

/***************************************************
PreTranslateAccelerator
****************************************************/
BOOL CHistory::PreTranslateAccelerator(LPMSG pMsg, HRESULT& hRet)
{
	if(pMsg->message == WM_KEYDOWN && 
		(pMsg->wParam == VK_LEFT || 
		pMsg->wParam == VK_RIGHT ||
		pMsg->wParam == VK_UP ||
		pMsg->wParam == VK_DOWN))
	{
		hRet = S_FALSE;
		return TRUE;
	}
	//TODO: Add your additional accelerator handling code here
	return FALSE;
}

/***************************************************
OnSetFocus
****************************************************/
LRESULT CHistory::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = CComControl<CHistory>::OnSetFocus(uMsg, wParam, lParam, bHandled);
	if (m_bInPlaceActive)
	{
		DoVerbUIActivate(&m_rcPos,  NULL);
		if(!IsChild(::GetFocus()))
			::SetFocus(m_ctlHistory.m_hWnd);
	}
	return lRes;
}

/***************************************************
OnCreate
****************************************************/
LRESULT CHistory::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rc;
	GetWindowRect(&rc);
	rc.right -= rc.left;
	rc.bottom -= rc.top;
	rc.top = rc.left = 0;

	// Create history window
	m_ctlHistory.CreateHistoryWindow(m_hWnd, 0x50a00000, rc);
	m_ctlContainedWnd.SubclassWindow(m_ctlHistory.m_hWnd);
	
	// In the design mode add one line of text
	BOOL	bUserMode;
	GetAmbientUserMode(bUserMode);
	if(bUserMode == FALSE)
		m_ctlHistory.AddLine("Line of Text", 0xFFFFFFFF, 0xFFFFFFFF, FALSE);

	return 0;
}

/***************************************************
SetObjectRects
****************************************************/
STDMETHODIMP CHistory::SetObjectRects(LPCRECT prcPos,LPCRECT prcClip)
{
	IOleInPlaceObjectWindowlessImpl<CHistory>::SetObjectRects(prcPos, prcClip);
	int cx, cy;
	cx = prcPos->right - prcPos->left;
	cy = prcPos->bottom - prcPos->top;
	::SetWindowPos(m_ctlHistory.m_hWnd, NULL, 0,
		0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
	return S_OK;
}

/***************************************************
IOleObject_SetClientSite
****************************************************/
STDMETHODIMP CHistory::IOleObject_SetClientSite(LPOLECLIENTSITE pSite)
{
	HRESULT hr = CComControlBase::IOleObject_SetClientSite(pSite);
	// Check to see if the container has an ambient font. If it does,
	// clone it so your user can change the font of the control
	// without changing the ambient font for the container. If there is
	// no ambient font, create your own font object when you hook up a
	// client site.

	if(!m_pFont && pSite) {
		FONTDESC fd = _fontdesc;
		CComPtr<IFont> pAF;
		CComPtr<IFont> pClone;
		if(SUCCEEDED(GetAmbientFont(&pAF))) {
			//clone the font
			if(SUCCEEDED(pAF->Clone(&pClone)))
				pClone->QueryInterface(IID_IFontDisp, (void**)&m_pFont);
			}
		else 
		  OleCreateFontIndirect(&fd,IID_IFontDisp,(void**)&m_pFont);
		}

	return hr;
}

////////////////////////////////////////////////////
//	IHistory interface properties Set/Get functions
////////////////////////////////////////////////////

/***************************************************
put_BackColor
	Puts control back color
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_BackColor(OLE_COLOR newVal)
{
    if (m_clrBackColor == newVal)
        return S_OK;

	if (FireOnRequestEdit(DISPID_BACKCOLOR) == S_FALSE)
		return S_FALSE;

	m_clrBackColor = newVal;                // Save new color

    m_bRequiresSave = TRUE;                 // Set dirty flag
    FireOnChanged(DISPID_BACKCOLOR);		// Notify container of change

	// Set history window back color
	COLORREF	color;
	OleTranslateColor(m_clrBackColor, NULL, &color);
	m_ctlHistory.SetBackColor(color); 
	
	::InvalidateRect(m_ctlHistory.m_hWnd, NULL, TRUE);
    FireViewChange();                       // Request redraw
    SendOnDataChange(NULL);                 // Notify advise sinks of change

	return S_OK;
}

/***************************************************
put_ForeColor
	Puts control text color
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_ForeColor(OLE_COLOR newVal)
{
    if (m_clrForeColor == newVal)
        return S_OK;

	if (FireOnRequestEdit(DISPID_FORECOLOR) == S_FALSE)
		return S_FALSE;

	m_clrForeColor = newVal;                // Save new color

    m_bRequiresSave = TRUE;                 // Set dirty flag
    FireOnChanged(DISPID_FORECOLOR);		// Notify container of change

	// Set history window back color
	COLORREF	color;
	OleTranslateColor(m_clrForeColor, NULL, &color);
	m_ctlHistory.SetTextColor(color); 
	
	::InvalidateRect(m_ctlHistory.m_hWnd, NULL, TRUE);
    FireViewChange();                       // Request redraw
    SendOnDataChange(NULL);                 // Notify advise sinks of change

	return S_OK;
}

/***************************************************
putref_Font
	Puts control font
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::putref_Font(IFontDisp* newVal)
{
	if (FireOnRequestEdit(DISPID_FONT) == S_FALSE)
		return S_FALSE;

	m_pFont = newVal;

	// Set Font
	if(m_pFont) {
		HFONT	hFont;
		CComQIPtr<IFont,&IID_IFont> pFont(m_pFont);

		BSTR		bstrString;
		BOOL		bBold, bItalic, bStrike, bUnderline;
		SHORT		sCharSet, sWeight;
		CY			cySize;

		pFont->get_Name(&bstrString);
		pFont->get_Bold(&bBold);
		pFont->get_Charset(&sCharSet);
		pFont->get_Italic(&bItalic);
		pFont->get_Size(&cySize);
		pFont->get_Strikethrough(&bStrike);
		pFont->get_Underline(&bUnderline);
		pFont->get_Weight(&sWeight);

		double		nPointSize = cySize.Lo/10000.;

		HDC hDC = ::GetDC(NULL);
		hFont = CreateFont(	(int)-((nPointSize * GetDeviceCaps(hDC, LOGPIXELSY)) / 72.),
							0, 0, 0, 
							sWeight, 
							bItalic, 
							bUnderline, 
							bStrike, 
							DEFAULT_CHARSET, 
							0, 
							0, 
							0, 
							DEFAULT_PITCH,
							_bstr_t(bstrString));

		::ReleaseDC(NULL, hDC);

		m_ctlHistory.SetFont(hFont);
		}

	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_FONT);

	::InvalidateRect(m_ctlHistory.m_hWnd, NULL, TRUE);
	FireViewChange();
	SendOnDataChange(NULL);


	return S_OK;
}

/***************************************************
put_Font
	Puts control font
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_Font(IFontDisp* newVal)
{
	if (FireOnRequestEdit(DISPID_FONT) == S_FALSE)
		return S_FALSE;
	m_pFont = newVal;

	// Set Font
	if(m_pFont) {
		CComQIPtr<IFont,&IID_IFont> pFont(m_pFont);
		HFONT	hFont;

		pFont->get_hFont(&hFont);
		m_ctlHistory.SetFont(hFont);
		}

	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_FONT);

	::InvalidateRect(m_ctlHistory.m_hWnd, NULL, TRUE);
	FireViewChange();
	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_LogName
	Gets log file name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHistory::get_LogName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_ctlHistory.GetLogName())))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_LogName
	Puts log file name
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_LogName(BSTR newVal)
{
    if (_bstr_t(m_ctlHistory.GetLogName()) == _bstr_t(newVal))
        return S_OK;

	if (FireOnRequestEdit(DISPID_LOG_NAME) == S_FALSE)
		return S_FALSE;

	m_ctlHistory.SetLogName(_bstr_t(newVal));
	m_bRequiresSave = TRUE;                 // Set dirty flag
	FireOnChanged(DISPID_LOG_NAME);			// Notify container of change

	SendOnDataChange(NULL);                 // Notify advise sinks of change

	return S_OK;
}

/***************************************************
get_EnableLog
	Gets log enabled flag
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHistory::get_EnableLog(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_bEnableLog;
	return S_OK;
}

/***************************************************
put_EnableLog
	Puts log enabled flag
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_EnableLog(VARIANT_BOOL newVal)
{
    if (m_bEnableLog == newVal)
        return S_OK;

	if (FireOnRequestEdit(DISPID_ENABLE_LOG) == S_FALSE)
		return S_FALSE;

	m_bEnableLog = newVal;
    m_bRequiresSave = TRUE;                 // Set dirty flag
	FireOnChanged(DISPID_ENABLE_LOG);		// Notify container of change
    SendOnDataChange(NULL);                 // Notify advise sinks of change
	return S_OK;
}

/***************************************************
get_TimeStampedLog
	Gets log enabled flag
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHistory::get_TimeStampedLog(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_ctlHistory.IsTimeStampedLogEnabled();
	return S_OK;
}

/***************************************************
put_TimeStampedLog
	Puts log enabled flag
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_TimeStampedLog(VARIANT_BOOL newVal)
{
    if (m_ctlHistory.IsTimeStampedLogEnabled() == newVal)
        return S_OK;

	if (FireOnRequestEdit(DISPID_TIME_STAMPED_LOG) == S_FALSE)
		return S_FALSE;

	m_ctlHistory.EnableTimeStampedLog((BOOL)newVal);
    m_bRequiresSave = TRUE;						// Set dirty flag
	FireOnChanged(DISPID_TIME_STAMPED_LOG);		// Notify container of change
    SendOnDataChange(NULL);						// Notify advise sinks of change
	return S_OK;
}

/***************************************************
get_Aligment
	Gets aligment type
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHistory::get_Alignment(AlignmentType *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (AlignmentType)m_ctlHistory.GetAlignment();
	return S_OK;
}

/***************************************************
put_Alignment
	Puts alignment type
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_Alignment(AlignmentType newVal)
{
    if ((AlignmentType)m_ctlHistory.GetAlignment() == newVal)
        return S_OK;

	if (FireOnRequestEdit(DISPID_ALIGNMENT) == S_FALSE)
		return S_FALSE;

	m_ctlHistory.SetAlignment(newVal);

    m_bRequiresSave = TRUE;                 // Set dirty flag
    FireOnChanged(DISPID_ALIGNMENT);		// Notify container of change

	::InvalidateRect(m_ctlHistory.m_hWnd, NULL, TRUE);
    FireViewChange();                       // Request redraw
    SendOnDataChange(NULL);                 // Notify advise sinks of change

	return S_OK;
}

/***************************************************
get_Margin
	Gets margin size
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHistory::get_Margin(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_ctlHistory.GetMargin();
	return S_OK;
}

/***************************************************
put_Margin
	Puts margin size
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_Margin(long newVal)
{
    if (m_ctlHistory.GetMargin() == newVal)
        return S_OK;

	if (FireOnRequestEdit(DISPID_MARGIN) == S_FALSE)
		return S_FALSE;

	m_ctlHistory.SetMargin(newVal);

    m_bRequiresSave = TRUE;                 // Set dirty flag
    FireOnChanged(DISPID_MARGIN);			// Notify container of change

	::InvalidateRect(m_ctlHistory.m_hWnd, NULL, TRUE);
    FireViewChange();                       // Request redraw
    SendOnDataChange(NULL);                 // Notify advise sinks of change

	return S_OK;
}

/***************************************************
get_TimeStampFormat
	Gets time stamp format
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHistory::get_TimeStampFormat(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_ctlHistory.GetTimeStampFormat())))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_TimeStampFormat
	Puts time stamp format
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_TimeStampFormat(BSTR newVal)
{
    if (_bstr_t(m_ctlHistory.GetTimeStampFormat()) == _bstr_t(newVal))
        return S_OK;

	if (FireOnRequestEdit(DISPID_TIME_STAMP_FORMAT) == S_FALSE)
		return S_FALSE;

	m_ctlHistory.SetTimeStampFormat(_bstr_t(newVal));
	m_bRequiresSave = TRUE;							// Set dirty flag
	FireOnChanged(DISPID_TIME_STAMP_FORMAT);		// Notify container of change

	SendOnDataChange(NULL);							// Notify advise sinks of change

	return S_OK;
}

/***************************************************
get_MaxHistoryLength
	Gets max. history length
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHistory::get_MaxHistoryLength(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_ctlHistory.GetHistoryLength();
	return S_OK;
}

/***************************************************
put_MaxHistoryLength
	Puts max. history length
Params
    newVal	- new value of the property
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHistory::put_MaxHistoryLength(long newVal)
{
    if (m_ctlHistory.GetHistoryLength() == newVal)
        return S_OK;

	if (FireOnRequestEdit(DISPID_MAX_HISTORY_LENGTH) == S_FALSE)
		return S_FALSE;

	m_ctlHistory.SetHistoryLength(newVal);

    m_bRequiresSave = TRUE;								// Set dirty flag
    FireOnChanged(DISPID_MAX_HISTORY_LENGTH);			// Notify container of change

	::InvalidateRect(m_ctlHistory.m_hWnd, NULL, TRUE);
    FireViewChange();									// Request redraw
    SendOnDataChange(NULL);								// Notify advise sinks of change

	return S_OK;
}

/***************************************************
AddLine
	Adds a new line to the control.
    If logging is on and the addToLog
    param is TRUE then this line is also
    added to the log file.
Params
    String		- string to add
	[TextColor]	- color of the text
	[BackColor]	- color of the background
    [AddToLog]	- if TRUE then add to the file log, if it is enabled
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CHistory::AddLine(BSTR String, OLE_COLOR TextColor, OLE_COLOR BackColor, BOOL AddToLog)
{
	COLORREF	colorText, colorBack;
	
	if(TextColor == 0xFFFFFFFF)
		colorText = 0xFFFFFFFF;
	else
		OleTranslateColor(TextColor, NULL, &colorText);

	if(BackColor == 0xFFFFFFFF)
		colorBack = 0xFFFFFFFF;
	else
		OleTranslateColor(BackColor, NULL, &colorBack);

	// Enable log
	if(m_bEnableLog != m_ctlHistory.IsLogEnabled() && AddToLog == TRUE)
		m_ctlHistory.EnableLog(m_bEnableLog);

	m_ctlHistory.AddLine(_bstr_t(String), colorText, colorBack, (BOOL)AddToLog);
	return S_OK;
}

/***************************************************
AddStampedLine
	Adds a new line to the control with
    a time stamp added to the beginning
    of the line.
    If logging is on and the addToLog
    param is TRUE then this line is also
    added to the log file.
Params
    String		- string to add
	[TextColor]	- color of the text
	[BackColor]	- color of the background
    [AddToLog]	- if TRUE then add to the file log, if it is enabled
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CHistory::AddStampedLine(BSTR String, OLE_COLOR TextColor, OLE_COLOR BackColor, BOOL AddToLog)
{
	COLORREF	colorText, colorBack;
	
	if(TextColor == 0xFFFFFFFF)
		colorText = 0xFFFFFFFF;
	else
		OleTranslateColor(TextColor, NULL, &colorText);

	if(BackColor == 0xFFFFFFFF)
		colorBack = 0xFFFFFFFF;
	else
		OleTranslateColor(BackColor, NULL, &colorBack);
	
	// Enable log
	if(m_bEnableLog != m_ctlHistory.IsLogEnabled() && AddToLog == TRUE)
		m_ctlHistory.EnableLog(m_bEnableLog);

	m_ctlHistory.AddStampedLine(_bstr_t(String), colorText, colorBack, (BOOL)AddToLog);
	return S_OK;
}

/***************************************************
AppendToLine
	Appends more information to the last 
    line added.
    If logging is on and the addToLog
    param is TRUE then this line is also
    added to the log file.
Params
    String		- string to add
    [AddToLog]	- if TRUE then add to the file log, if it is enabled
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CHistory::AppendToLine(BSTR String, BOOL AddToLog)
{
	m_ctlHistory.AppendToLine(_bstr_t(String), (BOOL)AddToLog);
	return S_OK;
}

/***************************************************
ClearHistory
	Clears all items from the history list
Params
    none
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CHistory::ClearHistory()
{
	m_ctlHistory.ClearHistory();
	return S_OK;
}

/***************************************************
AboutBox
	Display about box
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CHistory::AboutBox()
{
	CAboutDlg	dlg;

	dlg.DoModal();
	return S_OK;
}
