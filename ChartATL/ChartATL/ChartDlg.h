// ChartDlg.h : Declaration of the CChartDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>


// CChartDlg
/* Sundar Code Begins here */
#define VER_LINE_GAP			2
#define NO_OF_GRAPH				4
#define	GRAPH_GAP				6
#define NO_OF_BAR_PARTS			4
#define CENTER_VAL				2.5
#define LINE_GAP_LEN			3
#define BUF_LEN					20
#define VER_MAX_MOV				20
#define GRAPH_HEADER_LOC		20
#define NO_OF_POINTS			25

struct Health_Graph
{
	long	RxBytes;
	long	TxBytes;
};
/* Code Ends */

class CChartDlg : 
	public CDialogImpl<CChartDlg>
{
public:

	//Chart Background Properties
	INT m_VLineStyle;
	INT m_HLineStyle;
	COLORREF	m_VLineColor;
	COLORREF	m_HLineColor;
	COLORREF	m_BackColor;

	//Chart Forground Properties
	COLORREF	m_ChartColor_1;
	COLORREF	m_ChartColor_2;
	INT		m_ChartFillStyle_1;
	INT		m_ChartFillStyle_2;

	//Chart Values
	UINT m_ChartRefreshSpeed, _LastRefreshSpeed;
	UINT m_RxValue, m_TxValue;
	UINT MaxRx, MaxTx;
	LONG64 TotalRxBytes, TotalTxBytes;
	struct Health_Graph GraphInfo[NO_OF_POINTS];

public:
	CChartDlg()
	{
		//m_bWindowOnly = TRUE;
		m_VLineStyle = m_HLineStyle = PS_SOLID;
		m_VLineColor = m_HLineColor = ::GetSysColor(COLOR_WINDOW);
		m_BackColor = ::GetSysColor(COLOR_WINDOW);

		//Chart Forground Properties
		m_ChartColor_1 = ::GetSysColor(COLOR_WINDOWTEXT);
		m_ChartColor_2 = ::GetSysColor(COLOR_WINDOWTEXT);
		m_ChartFillStyle_1 = m_ChartFillStyle_2 = PS_SOLID;

		//Chart Values
		m_RxValue = m_TxValue = 0;
		MaxRx = MaxTx = 0;
		_LastRefreshSpeed = m_ChartRefreshSpeed = 300;
		

		for(int i = 0; i < NO_OF_POINTS; i++)
		{
			GraphInfo[i].RxBytes = 0;
			GraphInfo[i].TxBytes = 0;
		}
	}

	~CChartDlg()
	{
	}

	enum { IDD = IDD_CHARTDLG };

BEGIN_MSG_MAP(CChartDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
//		bHandled = TRUE;

		m_uTimerID = (UINT) SetTimer(1, m_ChartRefreshSpeed, NULL);

		return 1;  // Let the system set the focus
	}
public:
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
public:
	UINT	m_uTimerID;
	RECT	Rect;
	HDC		hdc;
public : 
	VOID RedrawChart(HDC hdc, RECT Rect);		
	VOID DrawChartBackground(HDC hdc, RECT Rect);
};