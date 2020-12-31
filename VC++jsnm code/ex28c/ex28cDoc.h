// ex28cDoc.h : interface of the CEx28cDoc class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_EX28CDOC_H__6FE9FA8D_957D_11D0_AAA2_444553540000__INCLUDED_)
#define AFX_EX28CDOC_H__6FE9FA8D_957D_11D0_AAA2_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx28cDoc : public CDocument
{
protected: // create from serialization only
	CEx28cDoc();
	DECLARE_DYNCREATE(CEx28cDoc)

// Attributes
public:
	CEx28cSet* m_pEx28cSet;
	CDatabase m_database;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28cDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28CDOC_H__6FE9FA8D_957D_11D0_AAA2_444553540000__INCLUDED_)
