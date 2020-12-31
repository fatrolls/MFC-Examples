#ifndef AFX_DLGZEITEN_H__D0B3EC46_4B0F_11D1_94CD_0020187099A1__INCLUDED_
#define AFX_DLGZEITEN_H__D0B3EC46_4B0F_11D1_94CD_0020187099A1__INCLUDED_

// DlgZeiten.h : Header-Datei
//
#include "MyListCrtl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgZeiten 

class CDlgZeiten : public CDialog
{
// Konstruktion
public:
	CDlgZeiten(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgZeiten)
	enum { IDD = IDD_DLGLISTE };
	CComboBox	m_ProjektListe;
	CMyListCrtl	m_Liste;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgZeiten)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgZeiten)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokProjekte();
	afx_msg void OnNeu();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FillComboBox();
	BOOL FillListView(CString &Datei);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGZEITEN_H__D0B3EC46_4B0F_11D1_94CD_0020187099A1__INCLUDED_
