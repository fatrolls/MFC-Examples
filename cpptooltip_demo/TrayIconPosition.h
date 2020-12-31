// TrayIconPosition.h: interface for the CTrayIconPosition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAYICONPOSITION_H__9FD8A5A1_419F_11D7_B751_00304F20BD3B__INCLUDED_)
#define AFX_TRAYICONPOSITION_H__9FD8A5A1_419F_11D7_B751_00304F20BD3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTrayIconPosition  
{
public:
	void Invalidate();
	typedef enum Precision {Default=0,Low,Medium,High};
	
	void RestoreTrayIcon(HICON icon);
	void SetPrecisionTimeOuts(int iLowSec, int iMedSec, int iHighSec);
	BOOL GetTrayIconPosition(CPoint& point, Precision prPrec = Default);

	void InitializePositionTracking(HWND hwndOfIconOwner, int iIconID);
	void SetDefaultPrecision(Precision newPrecision) { m_prDefaultPrecision = newPrecision; };
	Precision GetDefaultPrecision(void) { return m_prDefaultPrecision; };

	CTrayIconPosition();
	virtual ~CTrayIconPosition();

protected:
	HICON		m_hIconTemp;
	CRect		m_rtRectangleOfTheTray;
	Precision	m_prDefaultPrecision;
	CTime		m_tLastUpdate;
	CPoint		m_ptPosition;
	int			m_iTrayIconID;
	HWND		m_hWndOfIconOwner;
	int			m_iPrecisions[3];  //This is table of time outs in seconds of low,med and high precision modes.
	OSVERSIONINFO m_osVer;

	BOOL FindOutPositionOfIcon(HICON icon);
	BOOL CheckIfColorIsBlackOrNearBlack(COLORREF crColor);
	CRect GetTrayWndRect();
	static BOOL CALLBACK FindTrayWnd(HWND hwnd, LPARAM lParam);
};

#endif // !defined(AFX_TRAYICONPOSITION_H__9FD8A5A1_419F_11D7_B751_00304F20BD3B__INCLUDED_)
