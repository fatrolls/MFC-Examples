// RoundSliderCtrlDemoDlg.h : Header-Datei
//

#if !defined(_ROUNDSLIDERCTRLDEMODLG_H_)
#define _ROUNDSLIDERCTRLDEMODLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RoundSliderCtrl.h"
#include "FrequencyCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CRoundSliderCtrlDemoDlg Dialogfeld

class CRoundSliderCtrlDemoDlg : public CDialog
{
// Konstruktion
public:
	CRoundSliderCtrlDemoDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CRoundSliderCtrlDemoDlg)
	enum { IDD = IDD_ROUNDSLIDERCTRLDEMO_DIALOG };
	CRoundSliderCtrl	m_rscSlider1;
	CFrequencyCtrl		m_rscSlider2;
	int		m_rscSlider2Val;
	int		m_rscSlider1Val;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CRoundSliderCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CRoundSliderCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(_ROUNDSLIDERCTRLDEMODLG_H_)
