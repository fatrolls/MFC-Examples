#ifndef AFX_SINUSFRAME_H__41258CBF_8436_11D1_9C04_084D65000000__INCLUDED_
#define AFX_SINUSFRAME_H__41258CBF_8436_11D1_9C04_084D65000000__INCLUDED_

// SinusFrame.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CSinusFrame 

class CSinusFrame : public CStatic
{
// Konstruktion
public:
	CSinusFrame();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSinusFrame)
	//}}AFX_VIRTUAL

// Implementierung
public:
	void SetSinusSpeed(int n);
	void SetFont(CFont* pFont);
	void Stop();
	void Start();
	void SetText(LPCTSTR lpszText);
	virtual ~CSinusFrame();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CSinusFrame)
	afx_msg void OnFontChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void Cleanup();
	void DoCharBlit();
	void Scroll();
	TCHAR GetNextChar();
	void DoSinScroll();
	int GetNextSinusOffset();
	double GetNextSinValue();
	void Initialize();

	int m_nSinusSpeed;
	int m_nSinusOffset;
	int m_nSinusPos;
	int m_nCharWidth;
	int m_nCharHeight;
	int m_nPixLeft;
	int m_nTextPos;

	double m_dSinusTable[720];
	
	UINT m_nTimer;
	
	static void CALLBACK AFX_EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
	
	bool m_bRunning;
	bool m_bInitialized;

	CFont*	m_pFont;
	CBitmap* m_pBMSinus;
	CBitmap* m_pBMScroll;
	CDC*		m_pDCScroll;
	CDC*		m_pDCSinus;
	CRect		m_rcScroll;
	CRect		m_rcClient;
	CString	m_strText;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_SINUSFRAME_H__41258CBF_8436_11D1_9C04_084D65000000__INCLUDED_
