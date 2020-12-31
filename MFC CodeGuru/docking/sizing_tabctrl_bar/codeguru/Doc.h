// Doc.h : Schnittstelle der Klasse CDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOC_H__D9D4DCAB_C324_11D1_91F5_B4375BB20A38__INCLUDED_)
#define AFX_DOC_H__D9D4DCAB_C324_11D1_91F5_B4375BB20A38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CDoc();
	DECLARE_DYNCREATE(CDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_DOC_H__D9D4DCAB_C324_11D1_91F5_B4375BB20A38__INCLUDED_)
