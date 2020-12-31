// splashView.h : Schnittstelle der Klasse CSplashView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLASHVIEW_H__00D0679C_E8B9_11D1_A474_006097E3E7B0__INCLUDED_)
#define AFX_SPLASHVIEW_H__00D0679C_E8B9_11D1_A474_006097E3E7B0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSplashView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CSplashView();
	DECLARE_DYNCREATE(CSplashView)

// Attribute
public:
	CSplashDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSplashView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CSplashView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CSplashView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in splashView.cpp
inline CSplashDoc* CSplashView::GetDocument()
   { return (CSplashDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_SPLASHVIEW_H__00D0679C_E8B9_11D1_A474_006097E3E7B0__INCLUDED_)
