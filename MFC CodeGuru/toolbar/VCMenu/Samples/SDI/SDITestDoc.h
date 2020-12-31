// SDITestDoc.h : interface of the CSDITestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDITESTDOC_H__876557A2_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
#define AFX_SDITESTDOC_H__876557A2_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSDITestDoc : public CDocument
{
protected: // create from serialization only
	CSDITestDoc();
	DECLARE_DYNCREATE(CSDITestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDITestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDITestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDITestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDITESTDOC_H__876557A2_D5DC_11D1_B0FA_00A0C94457BF__INCLUDED_)
