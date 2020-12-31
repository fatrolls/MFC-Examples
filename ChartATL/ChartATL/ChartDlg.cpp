// ChartDlg.cpp : Implementation of CChartDlg

#include "stdafx.h"
#include "ChartDlg.h"


// CChartDlg
VOID CChartDlg::RedrawChart(HDC hdc, RECT Rect)
{
	// TODO: Add your implementation code here
    HFONT  hOldFont, hNewFont;
    HPEN   hOldPen, hNewPen;
	
	LOGBRUSH lbrush;     
 	HBRUSH hOldBrush, hNewBrush;	
	
    LOGPEN   lpen;          
    LOGFONT  lfont;          

    POINT penpoint;           

	char Buf[20];
	int XAxisValues ;
	int ModVal;
	int iLoop, Index, Check_Index;
	float XPlotDiff, YPlotDiff;
	int XInt, YInt;

	XAxisValues = Index = Check_Index = 0;

    XInt = (Rect.right - Rect.left)/GRAPH_GAP;
	YInt = (Rect.bottom - Rect.top)/GRAPH_GAP;

	// Check for valid data...
	if(m_RxValue < 0 || m_RxValue > 9999)
		m_RxValue = 0;
	if(m_TxValue < 0 || m_TxValue > 9999)
		m_TxValue = 0;

	// Update the Max Bytes that has send / Received through the socket.
	if(m_RxValue > MaxRx)
		MaxRx = m_RxValue;
	if(m_TxValue > MaxTx)
		MaxTx = m_TxValue;

	if(MaxTx <= 0 && MaxRx <= 0)
		MaxTx = 100;
	// Assign the x axis difference values. Get six intervals values for x axis.
	if(MaxTx > MaxRx)
		XAxisValues = MaxTx / GRAPH_GAP;
	else
		XAxisValues = MaxRx / GRAPH_GAP;
	
	// Round off the xaxis values for draw graph
	ModVal = (int) XAxisValues % 10;
	ModVal = 10 - ModVal;
	if(ModVal != 10)
		XAxisValues += ModVal;

	// Set the font to display the x - axis values.
	lfont.lfHeight		=	-9;
	lfont.lfWeight		=	FW_THIN;
	lfont.lfWidth		=	0;
	lfont.lfEscapement	=	0;
	lfont.lfOrientation =	0;
	lfont.lfUnderline	=	FALSE;
	lfont.lfStrikeOut   =	FALSE;
	lfont.lfItalic		=	FALSE;
    lfont.lfCharSet		= DEFAULT_CHARSET;
    lfont.lfOutPrecision= OUT_TT_PRECIS;
    lfont.lfPitchAndFamily   = VARIABLE_PITCH | FF_DONTCARE;
    lfont.lfQuality          = PROOF_QUALITY;
    lfont.lfClipPrecision    = CLIP_DEFAULT_PRECIS;
	strcpy_s((char *) lfont.lfFaceName, sizeof(lfont.lfFaceName), (const char *) _T("Times New Roman"));
	
	hNewFont = CreateFontIndirect(&lfont);
	hOldFont = (HFONT) SelectObject(hdc, hNewFont);

	SetTextColor(hdc, RGB( 255, 255, 255));
	SetTextAlign(hdc, TA_LEFT | TA_BASELINE);
	// Display the x axis values
	Index = GRAPH_GAP;
	SetBkColor(hdc, RGB(000, 80, 40));
	for (iLoop = Rect.top; iLoop < Rect.bottom ; iLoop += YInt)
	{
		memset(Buf, 0x00, sizeof(Buf));
		sprintf_s(Buf, sizeof(Buf), "%ld", (XAxisValues * Index));
		if(Index == 0)
			TextOutA(hdc, (Rect.right - GRAPH_HEADER_LOC)+1, iLoop, Buf, (int) strlen(Buf));
		else
			TextOutA(hdc, (Rect.right - GRAPH_HEADER_LOC)+1, iLoop + 8, Buf, (int) strlen(Buf));
		Index --;
	}
	if(Index == 0)
		TextOut(hdc, (Rect.right - GRAPH_HEADER_LOC)+1, Rect.bottom, _T("0"), (int) strlen("0"));

	// Format the bytes structure.
	for(iLoop = NO_OF_POINTS; iLoop > 0; iLoop--)
	{
		GraphInfo[iLoop-1].RxBytes	=	GraphInfo[iLoop-2].RxBytes;
		GraphInfo[iLoop-1].TxBytes	=	GraphInfo[iLoop-2].TxBytes;
	}
	// Move the current value into the structure
	if(m_RxValue < 0 || m_RxValue > 32767)
		m_RxValue = 0;
	if(m_TxValue < 0 || m_TxValue > 32767)
		m_TxValue = 0;

	GraphInfo[0].RxBytes	=	m_RxValue;
	GraphInfo[0].TxBytes	=	m_TxValue;

	//Get Plot Pos Difference
	XPlotDiff = (float) XInt * GRAPH_GAP;
	XPlotDiff /= NO_OF_POINTS;
	XPlotDiff++;

	YPlotDiff = (float) Rect.bottom - (Rect.top);
	YPlotDiff /=  (XAxisValues*GRAPH_GAP);

	//Change pen color to DRAK GREEN
    penpoint.x           = (long)NULL;
    penpoint.y           = (long)NULL;

	lpen.lopnColor = m_ChartColor_1;
    lpen.lopnStyle = m_ChartFillStyle_1;
    lpen.lopnWidth = penpoint;
	
	hNewPen   = CreatePenIndirect(&lpen);    
	hOldPen   = (HPEN) SelectObject( hdc, hNewPen);

	//Change the brush color
    lbrush.lbStyle     = m_ChartFillStyle_1;
    lbrush.lbColor     = m_ChartColor_1;
    lbrush.lbHatch     = 0;

	// Select New Brush DC.
    hNewBrush   = CreateBrushIndirect(&lbrush);
    hOldBrush	 = (HBRUSH) SelectObject( hdc, hNewBrush);

	TotalRxBytes = TotalTxBytes = 0;
	//Plot Rx Bytes information on the graph
	Check_Index = 0;
	for (iLoop = NO_OF_POINTS; iLoop > 0; iLoop --)
	{
		if((Rect.left+Check_Index+XPlotDiff) > (Rect.right - GRAPH_HEADER_LOC))
			break;		
		if(((Rect.top + (YInt * GRAPH_GAP)) - (GraphInfo[iLoop-1].RxBytes * YPlotDiff)) < (GRAPH_HEADER_LOC + Rect.top ) )
		{
			Rectangle(hdc, (int)((Rect.left+Check_Index)), (int)(Rect.top), (int)(Rect.left+Check_Index+(XPlotDiff/2)), Rect.bottom); 
		}
		else if(((Rect.top + (YInt * GRAPH_GAP)) - (GraphInfo[iLoop].RxBytes * YPlotDiff)) > Rect.bottom )
		{
			Rectangle(hdc, (int)(Rect.left+Check_Index), Rect.bottom, (int)(Rect.left+Check_Index+10), Rect.bottom);
		}
		else
		{
			Rectangle(hdc, (int)((Rect.left+Check_Index)), (int) ((Rect.top + (YInt * GRAPH_GAP)) - (GraphInfo[iLoop-1].RxBytes * YPlotDiff)), 
				(int)(Rect.left+Check_Index+(XPlotDiff/2))  , (int) Rect.bottom );
		}
		Check_Index += (int) XPlotDiff;
		TotalRxBytes += GraphInfo[iLoop].RxBytes;
	}

	//Change pen color to DRAK GREEN
	lpen.lopnColor = m_ChartColor_2;
    lpen.lopnStyle = m_ChartFillStyle_2;
    lpen.lopnWidth = penpoint;
	hNewPen   = CreatePenIndirect(&lpen);    
	hOldPen   = (HPEN) SelectObject( hdc, hNewPen);
 
	//Change the brush color
    lbrush.lbStyle     = m_ChartFillStyle_2;
    lbrush.lbColor     = m_ChartColor_2;
    lbrush.lbHatch     = 0;

	// Select New Brush DC.
    hNewBrush   = CreateBrushIndirect(&lbrush);
    hOldBrush	 = (HBRUSH) SelectObject( hdc, hNewBrush);

	//Plot Tx Bytes information on the graph
	Check_Index = 0;
	for (iLoop = NO_OF_POINTS; iLoop > 0 ; iLoop --)
	{
		if((Rect.left+Check_Index+XPlotDiff) > (Rect.right - GRAPH_HEADER_LOC))
			break;
		if(((Rect.top + (YInt * GRAPH_GAP)) - (GraphInfo[iLoop-1].TxBytes * YPlotDiff)) < (GRAPH_HEADER_LOC + Rect.top ) )
		{
			Rectangle(hdc, (int)((Rect.left+Check_Index+(XPlotDiff/2))), (int)(Rect.top), (int)(Rect.left+Check_Index+XPlotDiff), Rect.bottom); 
		}
		else if(((Rect.top + (YInt * GRAPH_GAP)) - (GraphInfo[iLoop].TxBytes * YPlotDiff)) > Rect.bottom )
		{
			Rectangle(hdc, (int)(Rect.left+Check_Index), Rect.bottom, (int)(Rect.left+Check_Index), Rect.bottom);
		}
		else
		{			
			Rectangle(hdc, (int)((Rect.left+Check_Index+(XPlotDiff/2))), (int) ((Rect.top + (YInt * GRAPH_GAP)) - (GraphInfo[iLoop-1].TxBytes * YPlotDiff)),
				(int)(Rect.left+Check_Index+XPlotDiff), (int) (Rect.bottom));
		}
		Check_Index += (int) XPlotDiff;
		TotalTxBytes += GraphInfo[iLoop].TxBytes;
	}
	SelectObject(hdc, hOldPen);
    DeleteObject(hNewPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hNewBrush);
}

VOID CChartDlg::DrawChartBackground(HDC hdc, RECT Rect)
{
	// TODO: Add your implementation code here
	// Variable declaration

	HBRUSH hOldBrush, hNewBrush;
    HPEN   hOldPen, hNewPen;
	
	int XInt, YInt;
	int iLoop, Index;
	static int IncYAxis = 0;

	hNewPen = CreatePen(BS_SOLID, 0, m_BackColor);;
	if(hNewPen)
		hOldPen = (HPEN) SelectObject(hdc,(HPEN)hNewPen);

	// Select New Brush DC.
	hNewBrush = CreateSolidBrush(m_BackColor);
	hOldBrush = (HBRUSH) SelectObject(hdc, (HBRUSH) hNewBrush);

	// Calculate the diff value for x and y axis.
    XInt = (Rect.right - Rect.left)/GRAPH_GAP;
	YInt = (Rect.bottom - Rect.top)/GRAPH_GAP;

	// Draw the Box
	BOOL b = Rectangle(hdc, Rect.left, Rect.top , Rect.right - GRAPH_HEADER_LOC, Rect.bottom);

	// Select New Brush DC.
	hNewBrush = CreateSolidBrush(RGB(000, 80, 40));
	hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
//    FillRect(hDC, &Rect, hNewBrush);
	// Draw the Box
	Rectangle(hdc, Rect.right - GRAPH_HEADER_LOC, Rect.top , Rect.right, Rect.bottom);

	
	//Change pen color for Verticle Line
	hNewPen = CreatePen(m_VLineStyle, 0, m_VLineColor);;
	if(hNewPen)
		hOldPen = (HPEN) SelectObject(hdc,(HPEN)hNewPen);

	// Move the Background of the graph
	IncYAxis += VER_LINE_GAP;
	if(IncYAxis > XInt)
		IncYAxis  = 0;
	//Draw Y Axis . Vertical Line
	for (iLoop = (Rect.right - GRAPH_HEADER_LOC); (iLoop - IncYAxis) > Rect.left ; iLoop -= XInt)
	{

		MoveToEx(hdc, iLoop - IncYAxis, Rect.top, NULL); 
		LineTo(hdc, iLoop - IncYAxis, Rect.top + (YInt * GRAPH_GAP));
	}

	//Change pen color for Horizontal Line
	hNewPen = CreatePen(m_HLineStyle, 0, m_HLineColor);;
	if(hNewPen)
		hOldPen = (HPEN) SelectObject(hdc,(HPEN)hNewPen);

	//Draw X Axis . Horizontal Line
	Index = GRAPH_GAP;
	for (iLoop = Rect.top; iLoop <= Rect.bottom ; iLoop += YInt)
	{
		MoveToEx(hdc, Rect.left, iLoop, NULL); 
		LineTo(hdc, Rect.right - GRAPH_HEADER_LOC, iLoop);
		Index --;
	}
	if(Index == 0)
	{
		MoveToEx(hdc, Rect.left, Rect.bottom, NULL); 
		LineTo(hdc, Rect.right - GRAPH_HEADER_LOC, Rect.bottom);
	}

	SelectObject(hdc, hOldPen);
    DeleteObject(hNewPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hNewBrush);
}


LRESULT CChartDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseDC(hdc);
	KillTimer(m_uTimerID);

	return 0;
}

LRESULT CChartDlg::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	hdc = GetDC();
	GetClientRect(&Rect);
	DrawChartBackground(hdc, Rect);
	RedrawChart(hdc, Rect);

	if(_LastRefreshSpeed != m_ChartRefreshSpeed)
	{
		KillTimer(m_uTimerID);
		m_uTimerID = (UINT) SetTimer(1, m_ChartRefreshSpeed, NULL);
		_LastRefreshSpeed = m_ChartRefreshSpeed;
	}

	return 0;
}


LRESULT CChartDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(&ps);

	EndPaint(&ps);

	return 0;
}