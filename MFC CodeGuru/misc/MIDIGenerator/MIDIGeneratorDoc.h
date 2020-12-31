// MIDIGeneratorDoc.h : interface of the CMIDIGeneratorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIGENERATORDOC_H__0892C6DB_841E_11D1_A3FC_000000000000__INCLUDED_)
#define AFX_MIDIGENERATORDOC_H__0892C6DB_841E_11D1_A3FC_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMIDIGeneratorDoc : public CDocument
{
protected: // create from serialization only
	CMIDIGeneratorDoc();
	DECLARE_DYNCREATE(CMIDIGeneratorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIDIGeneratorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMIDIGeneratorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMIDIGeneratorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDIGENERATORDOC_H__0892C6DB_841E_11D1_A3FC_000000000000__INCLUDED_)
