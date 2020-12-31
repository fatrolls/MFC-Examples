// ex27aDoc.h : interface of the CEx27aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27ADOC_H__1EAAB6C5_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX27ADOC_H__1EAAB6C5_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx27aSrvrItem;

class CEx27aDoc : public COleServerDoc
{
public:
	CString m_strText;
protected: // create from serialization only
	CEx27aDoc();
	DECLARE_DYNCREATE(CEx27aDoc)

// Attributes
public:
	CEx27aSrvrItem* GetEmbeddedItem()
		{ return (CEx27aSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27aDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx27aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27aDoc)
	afx_msg void OnModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27ADOC_H__1EAAB6C5_6011_11D0_848F_00400526305B__INCLUDED_)
