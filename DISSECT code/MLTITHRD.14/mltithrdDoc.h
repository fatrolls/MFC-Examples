// mltithrdDoc.h : interface of the CMltithrdDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MLTITHRDDOC_H__3C3D7AD0_B569_11D0_968D_444553540000__INCLUDED_)
#define AFX_MLTITHRDDOC_H__3C3D7AD0_B569_11D0_968D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMltithrdDoc : public CDocument
{
protected: // create from serialization only
	CMltithrdDoc();
	DECLARE_DYNCREATE(CMltithrdDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMltithrdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMltithrdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMltithrdDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLTITHRDDOC_H__3C3D7AD0_B569_11D0_968D_444553540000__INCLUDED_)
