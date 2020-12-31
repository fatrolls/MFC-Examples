#if !defined(AFX_PEAKMETERCTRL_H__1A889652_9CAB_11D5_9075_000086436E72__INCLUDED_)
#define AFX_PEAKMETERCTRL_H__1A889652_9CAB_11D5_9075_000086436E72__INCLUDED_
#pragma warning(push)
#pragma warning(disable:4995)
#include <vector>
#pragma warning(pop)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PeakMeterCtrl.h : header file
//

#define HORZ_DEFAULT	8
#define VERT_DEFAULT	8
#define BAND_DEFAULT	8
#define LEDS_DEFAULT	8
#define BAND_PERCENT	10	// 10% of Max Range (Auto Decrease)
#define GRID_INCREASEBY	15	// Increase Grid color based on Background color
#define FALL_INCREASEBY 60	// Increase Falloff color based on Background
#define DELAY_10MS		10
#define DEFAULT_SPEED	10

// Peak Meter Control styles
#define PMS_HORIZONTAL	0x0000	// Horizontal band
#define PMS_VERTICAL	0x0001	// Vertical band


// Peak Meter data
struct PeakMeterData {
public:
	int  nValue;
	int  nFalloff;
	int  nPeak;
	PeakMeterData() :
	nValue(0), nFalloff(0), nPeak(0)
	{
	}
	
	~PeakMeterData() { }
	PeakMeterData& Copy(const PeakMeterData& pm);
	PeakMeterData& operator=(const PeakMeterData& pm) { return Copy( pm ); }
	bool	IsEqual(const PeakMeterData& pm);
	bool	IsGreater(const PeakMeterData& pm);
	bool	IsLower(const PeakMeterData& pm);
	bool	operator==(const PeakMeterData& pm) { return IsEqual( pm ); }
	bool	operator!=(const PeakMeterData& pm) { return !IsEqual( pm ); }
	bool	operator<(const PeakMeterData& pm)  { return IsLower( pm ); }
	bool	operator>(const PeakMeterData& pm)  { return IsGreater( pm ); }
	bool	operator<=(const PeakMeterData& pm) { return !IsGreater( pm ); }
	bool	operator>=(const PeakMeterData& pm) { return !IsLower( pm ); }
};


typedef std::vector<PeakMeterData> Vector_MeterData;

/////////////////////////////////////////////////////////////////////////////
// CPeakMeterCtrl window

class CPeakMeterCtrl : public CWnd
{
// Construction
public:
	CPeakMeterCtrl();

// Attributes
public:
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	void SetMeterStyle(int meterStyle);
	void SetBackgroundColor(COLORREF colorBgnd);
	void SetMeterBands(int nNumBands, int nLedBands);
	void SetBandsColor(COLORREF colorNormal, COLORREF colorMedium, COLORREF colorHigh);
	void SetFalloffDelay(int nSpeed);
	void SetFalloffEffect(bool bFalloffEffect);
	bool GetFalloffEffect() const;
	void ShowGrid(bool bShowGrid);
	bool IsGridVisible() const;
	void SetRangeValue(int nMin, int nMed, int nMax);
	void GetRangeValue(int* lpiMin, int* lpiMed, int* lpiMax) const;
	bool SetData(const int ArrayValue[], int nOffset, int nSize);
	void Refresh();
	bool IsStarted() const;
	bool Start(UINT uDelay);
	bool Stop();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPeakMeterCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPeakMeterCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPeakMeterCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void ResetControl();
	void InitData();
	void DrawVertBand(CDC* pDC, CRect& rcClient);
	void DrawHorzBand(CDC* pDC, CRect& rcClient);

	// Peak Meter animation
	virtual void DoTimerProcessing(UINT uID);

	int		 m_meterStyle;		// Meter Style
	COLORREF m_clrBackground;	// Control background color
	COLORREF m_clrNormal;		// Normal-range value band color
	COLORREF m_clrMedium;		// Medium-range value band color
	COLORREF m_clrHigh;			// High-range value band color
	int		 m_nMinValue;		// Minimum value
	int		 m_nMedValue;		// Medium value
	int		 m_nMaxValue;		// Maximum value
	int		 m_nNumBands;		// number of bands
	int		 m_nLedBands;		// number of leds per band
	int		 m_nSpeed;			// Falloff Speed
	bool	 m_bShowGrid;		// Show Tick grid
	bool	 m_bShowFalloff;	// Show Falloff
	UINT	 m_uTimerID;		// timer identifier
	UINT	 m_nDelay;			// Saved delay value
	Vector_MeterData	m_MeterData;
private:
	static void CALLBACK PeakTimerProc(UINT uID, UINT uMsg, DWORD_PTR dwUser, DWORD dw1, DWORD dw2);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEAKMETERCTRL_H__1A889652_9CAB_11D5_9075_000086436E72__INCLUDED_)
