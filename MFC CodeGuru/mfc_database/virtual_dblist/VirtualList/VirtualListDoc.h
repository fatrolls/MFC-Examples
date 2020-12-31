// VirtualListDoc.h : interface of the CVirtualListDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUALLISTDOC_H__A1E706A0_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
#define AFX_VIRTUALLISTDOC_H__A1E706A0_5F36_11D1_959E_D1A30ED05A05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CVirtualListDoc : public CDocument
{
protected: // create from serialization only
	CVirtualListDoc();
	DECLARE_DYNCREATE(CVirtualListDoc)
	CDaoRecordset* m_pRecordSet;
	CDaoDatabase*  m_pDataBase;
// Attributes
public:
	CDaoRecordset* GetRecordSet(){return m_pRecordSet;};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVirtualListDoc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual BOOL OnNewDocument();
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVirtualListDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVirtualListDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRTUALLISTDOC_H__A1E706A0_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
