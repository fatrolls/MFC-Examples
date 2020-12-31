// View.h : Schnittstelle der Klasse CDocView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__D9D4DCAD_C324_11D1_91F5_B4375BB20A38__INCLUDED_)
#define AFX_VIEW_H__D9D4DCAD_C324_11D1_91F5_B4375BB20A38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDocView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CDocView();
	DECLARE_DYNCREATE(CDocView)

// Attribute
public:
	CDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDocView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDocView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDocView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in View.cpp
inline CDoc* CDocView::GetDocument()
   { return (CDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_VIEW_H__D9D4DCAD_C324_11D1_91F5_B4375BB20A38__INCLUDED_)
