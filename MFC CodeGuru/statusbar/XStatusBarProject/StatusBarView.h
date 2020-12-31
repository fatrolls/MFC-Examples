#if !defined(AFX_STATUSBARVIEW_H__DC9D02AC_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_)
#define AFX_STATUSBARVIEW_H__DC9D02AC_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CStatusBarView : public CView
{
protected:
	CStatusBarView();
	DECLARE_DYNCREATE(CStatusBarView)

// Attribute
public:
	CStatusBarDoc* GetDocument();

// Operationen
public:

// Überladungen
	//{{AFX_VIRTUAL(CStatusBarView)
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
	virtual ~CStatusBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CStatusBarView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in StatusBarView.cpp
inline CStatusBarDoc* CStatusBarView::GetDocument()
   { return (CStatusBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_STATUSBARVIEW_H__DC9D02AC_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_)
