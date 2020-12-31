#if !defined(AFX_STATUSBARDOC_H__DC9D02AA_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_)
#define AFX_STATUSBARDOC_H__DC9D02AA_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CStatusBarDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CStatusBarDoc();
	DECLARE_DYNCREATE(CStatusBarDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CStatusBarDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CStatusBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CStatusBarDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_STATUSBARDOC_H__DC9D02AA_E3E9_11D1_B6E6_08005AD2C08F__INCLUDED_)
