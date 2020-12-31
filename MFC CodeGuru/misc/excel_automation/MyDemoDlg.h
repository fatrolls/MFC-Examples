// MyDemoDlg.h : Header-Datei
//

#if !defined(AFX_MYDEMODLG_H__44414C44_A85E_11D1_9BB6_00C0D109A731__INCLUDED_)
#define AFX_MYDEMODLG_H__44414C44_A85E_11D1_9BB6_00C0D109A731__INCLUDED_

#include <afxmt.h>

#include "xl5en32.h"	// Hinzugefügt von ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDemoDlg Dialogfeld

class CMyDemoDlg : public CDialog
{
// Konstruktion
public:
	CMyDemoDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CMyDemoDlg)
	enum { IDD = IDD_MYDEMO_DIALOG };
		// HINWEIS: der Klassenassistent fügt an dieser Stelle Datenelemente (Members) ein
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMyDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CMyDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Application m_Excel;
	bool m_bExcelStarted;
	void DoExcelConversion(CString File);
	bool CloseExcel();
	bool OpenExcel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_MYDEMODLG_H__44414C44_A85E_11D1_9BB6_00C0D109A731__INCLUDED_)
