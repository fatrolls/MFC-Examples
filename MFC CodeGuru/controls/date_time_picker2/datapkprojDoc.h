// datapkprojDoc.h : interface of the CDatapkprojDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAPKPROJDOC_H__D7484F4F_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
#define AFX_DATAPKPROJDOC_H__D7484F4F_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDatapkprojDoc : public CDocument
{
protected: // create from serialization only
	CDatapkprojDoc();
	DECLARE_DYNCREATE(CDatapkprojDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatapkprojDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDatapkprojDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDatapkprojDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAPKPROJDOC_H__D7484F4F_4B8C_11D1_B233_0020AFF9CEA6__INCLUDED_)
