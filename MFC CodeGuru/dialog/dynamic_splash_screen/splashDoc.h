// splashDoc.h : Schnittstelle der Klasse CSplashDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLASHDOC_H__00D0679A_E8B9_11D1_A474_006097E3E7B0__INCLUDED_)
#define AFX_SPLASHDOC_H__00D0679A_E8B9_11D1_A474_006097E3E7B0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSplashDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CSplashDoc();
	DECLARE_DYNCREATE(CSplashDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CSplashDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CSplashDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CSplashDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_SPLASHDOC_H__00D0679A_E8B9_11D1_A474_006097E3E7B0__INCLUDED_)
