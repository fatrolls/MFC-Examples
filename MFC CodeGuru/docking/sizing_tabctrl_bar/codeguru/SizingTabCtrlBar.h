#ifndef AFX_SIZINGTABCTRLBAR_H__3804CCE3_C325_11D1_91F5_B4375BB20A38__INCLUDED_
#define AFX_SIZINGTABCTRLBAR_H__3804CCE3_C325_11D1_91F5_B4375BB20A38__INCLUDED_

// SizingTabCtrlBar.h : Header-Datei
//
#include <afxtempl.h>
#include "sizecbar.h"

typedef struct
{
	CWnd *pWnd;
	char szLabel[32];
}TCB_ITEM;

/////////////////////////////////////////////////////////////////////////////
// Fenster CSizingTabCtrlBar 

class CSizingTabCtrlBar : public CSizingControlBar
{
// Konstruktion
public:
	CSizingTabCtrlBar();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	void SetActiveView(int nNewTab);
	void SetActiveView(CRuntimeClass *pViewClass);
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSizingTabCtrlBar)
	//}}AFX_VIRTUAL

// Implementierung
public:
	CView* GetActiveView();
	CView* GetView(int nView);
	CView* GetView(CRuntimeClass *pViewClass);
	BOOL AddView(LPCTSTR lpszLabel, CRuntimeClass *pViewClass, CCreateContext *pContext = NULL);
	void RemoveView(int nView);
	CTabCtrl m_tabctrl;
	virtual ~CSizingTabCtrlBar();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int m_nActiveTab;
	CView* m_pActiveView;
	CList <TCB_ITEM *,TCB_ITEM *> m_views;
	CImageList m_images;
	//{{AFX_MSG(CSizingTabCtrlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult) ;
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_SIZINGTABCTRLBAR_H__3804CCE3_C325_11D1_91F5_B4375BB20A38__INCLUDED_
