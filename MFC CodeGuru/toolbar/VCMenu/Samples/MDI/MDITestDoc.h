// MDITestDoc.h : interface of the CMDITestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDITESTDOC_H__8765578D_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
#define AFX_MDITESTDOC_H__8765578D_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMDITestDoc : public CDocument
{
protected: // create from serialization only
	CMDITestDoc();
	DECLARE_DYNCREATE(CMDITestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDITestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMDITestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDITestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDITESTDOC_H__8765578D_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
