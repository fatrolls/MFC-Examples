#if !defined(AFX_SPECTRUMGRAPH_H__D00FAB3B_95DC_433A_B106_D507409E1A0F__INCLUDED_)
#define AFX_SPECTRUMGRAPH_H__D00FAB3B_95DC_433A_B106_D507409E1A0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpectrumGraph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrequencyGraph window
enum FrequencyGraphType{ FG_MICRO_EQ, FG_EQ_CHANNEL, FG_SPECTRUM, FG_OSCILLOSCOPE, FG_PEAK, FG_PEAK2, FG_PIXELGRAM };

class CFrequencyGraph : public CWnd
{
// Construction
public:
	CFrequencyGraph();
	
	void SetNumberOfSteps(WORD nSteps) { m_wSteps = nSteps; m_nStepFactor = (int)((m_nLength/m_wSteps)+0.5);}
	void SetLowColor(COLORREF clrLow) { m_clrLow = clrLow; }
	void SetMediumColor(COLORREF clrMedium) { m_clrMedium = clrMedium;	}
	void SetHighColor(COLORREF clrHigh) { m_clrHigh = clrHigh; }
	void SetMediumLevel(int nLevel) { m_nMediumLevel = nLevel; }
	void SetHighLevel(int nLevel) { m_nHighLevel = nLevel; }
	void SetGrid(BOOL bGridOn=TRUE) { m_bGrid = bGridOn; }
	
	WORD GetNumberOfSteps() { return m_wSteps; }
	COLORREF GetLowColor() { return m_clrLow; }
	COLORREF GetMediumColor() { return m_clrMedium; }
	COLORREF GetHighColor() { return m_clrHigh; }
	int GetMediumLevel() { return m_nMediumLevel; }
	int GetHighLevel() { return m_nHighLevel; }
	BOOL GetGrid() { return m_bGrid; }
	void SetYRange(int nMin, int nMax)
	{
		m_nMinValue=nMin;
		m_nMaxValue=nMax;
	}
	void SetLogScale(BOOL bUseLogScale) { m_bLogScale = bUseLogScale; }
	FrequencyGraphType GetGraphType() { return m_graphType; }
	void SetGraphType(FrequencyGraphType gType) { m_graphType = gType; }

	void Update(int nNumber, double* dArray);//Takes Intensity after FFT is performed on Wave Data
protected:
	int m_nLength;
	double *m_dArray;
	int m_nMinValue;
	int m_nMaxValue;
	int m_nHighLevel;
	int m_nMediumLevel;
	WORD m_wSteps;
	int m_nStepFactor;
	COLORREF m_clrLow;
	COLORREF m_clrMedium;
	COLORREF m_clrHigh;
	BOOL m_bGrid;
	BOOL m_bLogScale;
	FrequencyGraphType m_graphType;
	void Point(HDC hDC, int x, int y, COLORREF color);
	BOOL Line(HDC hDC, int x1, int y1, int x2, int y2);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrequencyGraph)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFrequencyGraph();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFrequencyGraph)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMGRAPH_H__D00FAB3B_95DC_433A_B106_D507409E1A0F__INCLUDED_)
