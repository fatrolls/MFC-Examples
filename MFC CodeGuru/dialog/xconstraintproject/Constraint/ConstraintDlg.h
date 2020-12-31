/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Adresse:			Joachim.Raidl@iname.com
 * Klasse:			CConstraintDlg
 * JRRC:			%J%
 * Inlines:			-
 *
 ****************************************************************************/

#if !defined(AFX_CONSTRAINTDLG_H__549FCE07_DB80_11D1_B6E6_08005AD2C08F__INCLUDED_)
#define AFX_CONSTRAINTDLG_H__549FCE07_DB80_11D1_B6E6_08005AD2C08F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XConstraint.h"

class CConstraintDlg : public CDialog
{
// Konstruktion
public:
	CConstraintDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CConstraintDlg)
	enum { IDD = IDD_CONSTRAINT_DIALOG };
	int		m_left;
	int		m_bottom;
	int		m_right;
	int		m_top;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CConstraintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON		m_hIcon;
	XConstraint cs;
	CSize		aktSize;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CConstraintDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnConstraint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_CONSTRAINTDLG_H__549FCE07_DB80_11D1_B6E6_08005AD2C08F__INCLUDED_)
