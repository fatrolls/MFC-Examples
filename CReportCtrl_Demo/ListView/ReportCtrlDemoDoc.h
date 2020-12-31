// ReportCtrlDemoDoc.h : interface of the CReportCtrlDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTCTRLDEMODOC_H__637580BB_ACE1_4064_90B4_E434AF3A23D5__INCLUDED_)
#define AFX_REPORTCTRLDEMODOC_H__637580BB_ACE1_4064_90B4_E434AF3A23D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CReportCtrlDemoDoc : public CDocument
{
protected: // create from serialization only
	CReportCtrlDemoDoc();
	DECLARE_DYNCREATE(CReportCtrlDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCtrlDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportCtrlDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReportCtrlDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCTRLDEMODOC_H__637580BB_ACE1_4064_90B4_E434AF3A23D5__INCLUDED_)
