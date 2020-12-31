#ifndef AFX_FILEVIEW_H__84F28FA6_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_
#define AFX_FILEVIEW_H__84F28FA6_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_

// FileView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CFileView 

class CFileView : public CTreeView
{
protected:
	CFileView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CFileView)

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CFileView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CFileView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_FILEVIEW_H__84F28FA6_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_
