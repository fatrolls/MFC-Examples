// MessengerDoc.h : interface of the CMessengerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSENGERDOC_H__3987ADCE_E657_11D1_B802_0060084C3BF4__INCLUDED_)
#define AFX_MESSENGERDOC_H__3987ADCE_E657_11D1_B802_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMessengerDoc : public CDocument
{
protected: // create from serialization only
	CMessengerDoc();
	DECLARE_DYNCREATE(CMessengerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessengerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMessengerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
//	CClientMailslot m_ClientMailslot;
//	CServerMailslot m_ServerMailslot;

	//{{AFX_MSG(CMessengerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSENGERDOC_H__3987ADCE_E657_11D1_B802_0060084C3BF4__INCLUDED_)
