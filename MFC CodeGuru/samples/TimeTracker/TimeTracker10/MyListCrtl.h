#ifndef AFX_MYLISTCRTL_H__B6119D27_3F56_11D1_94CC_0020187099A1__INCLUDED_
#define AFX_MYLISTCRTL_H__B6119D27_3F56_11D1_94CC_0020187099A1__INCLUDED_

// MyListCrtl.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CMyListCrtl 

class CMyListCrtl : public CListCtrl
{
// Konstruktion
public:
	CMyListCrtl();

// Attribute
public:
	enum EHighlight {HIGHLIGHT_NORMAL, HIGHLIGHT_ALLCOLUMNS, HIGHLIGHT_ROW};

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CMyListCrtl)
	//}}AFX_VIRTUAL

// Implementierung
public:
	BOOL GetSubitemFromPoint(CPoint pt, LPINT pItem, LPINT pSubitem);
	virtual ~CMyListCrtl();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	int m_nHighlight;
	//{{AFX_MSG(CMyListCrtl)
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void RepaintSelectedItems();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MYLISTCRTL_H__B6119D27_3F56_11D1_94CC_0020187099A1__INCLUDED_
