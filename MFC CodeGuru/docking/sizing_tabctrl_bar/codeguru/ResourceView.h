#ifndef AFX_RESOURCEVIEW_H__84F28FA5_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_
#define AFX_RESOURCEVIEW_H__84F28FA5_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_

// ResourceView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CResourceView 

class CResourceView : public CTreeView
{
protected:
	CResourceView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CResourceView)

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CResourceView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CResourceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CResourceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_RESOURCEVIEW_H__84F28FA5_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_
