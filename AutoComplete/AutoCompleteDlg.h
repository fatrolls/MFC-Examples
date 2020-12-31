// AutoCompleteDlg.h : Header-Datei
//

#if !defined(AFX_AUTOCOMPLETEDLG_H__C60BD0D7_F940_46D8_B62C_DE7C056CA346__INCLUDED_)
#define AFX_AUTOCOMPLETEDLG_H__C60BD0D7_F940_46D8_B62C_DE7C056CA346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAutoCompleteDlg Dialogfeld

#include "ACEdit.h"
class CAutoCompleteDlg : public CDialog
{
// Konstruktion
public:
	CAutoCompleteDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	~CAutoCompleteDlg();
// Dialogfelddaten
	//{{AFX_DATA(CAutoCompleteDlg)
	enum { IDD = IDD_AUTOCOMPLETE_DIALOG };
	CACEdit	m_VerzEdit5;
	CACEdit	m_VerzEdit4;
	CACEdit	m_VerzEdit3;
	CACEdit	m_VerzEdit2;
	CACEdit	m_VerzEdit;
	CACEdit	m_ACEdit1;
	CACEdit	m_MEditCtrl;
	CACEdit	m_ComboBox2;
	CACEdit	m_ComboBox;
	CACEdit	m_EditCtrl2;
	CListBox	m_ListeBox;
	CACEdit	m_EditCtrl1;
	CString	m_EditText;
	CString	m_Verzeichnis;
	//}}AFX_DATA
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAutoCompleteDlg)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	TCHAR  szDirectory[MAX_PATH+2];
	CACEdit m_ComboEdit;
// Implementierung
protected:
	HICON m_hIcon;
	//CACListCtrl	*m_Liste;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CAutoCompleteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdateEdit1();
	virtual void OnOK();
	afx_msg void OnDirAuswahl();
	//}}AFX_MSG
	afx_msg LONG OnUpdateEdit2(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_AUTOCOMPLETEDLG_H__C60BD0D7_F940_46D8_B62C_DE7C056CA346__INCLUDED_)
