// SinusDlg.h : Header-Datei
//

#if !defined(AFX_SINUSDLG_H__41258CB7_8436_11D1_9C04_084D65000000__INCLUDED_)
#define AFX_SINUSDLG_H__41258CB7_8436_11D1_9C04_084D65000000__INCLUDED_

#include "sinusframe.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSinusDlg Dialogfeld

class CSinusDlg : public CDialog
{
// Konstruktion
public:
	CSinusDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSinusDlg)
	enum { IDD = IDD_SINUS_DIALOG };
	CSliderCtrl	m_ctrlSpeed;
	CSinusFrame	m_ctrlSinus;
	CString	m_strText;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSinusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CSinusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeTextEdit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBtnSetFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_SINUSDLG_H__41258CB7_8436_11D1_9C04_084D65000000__INCLUDED_)
