#if !defined(AFX_SOURCEOBJ_H__B77C2985_56DD_11CF_B355_00104B08CC22__INCLUDED_)
#define AFX_SOURCEOBJ_H__B77C2985_56DD_11CF_B355_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SourceObj.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSourceObj command target

class CSourceObj : public CCmdTarget
{
	DECLARE_DYNCREATE(CSourceObj)

	CSourceObj();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSourceObj)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	DECLARE_MESSAGE_MAP()
// Implementation
protected:
	virtual ~CSourceObj();

	// Generated message map functions
	//{{AFX_MSG(CSourceObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_OLECREATE(CSourceObj)    // Class factory and guid
	DECLARE_INTERFACE_MAP()
	// Connection point for interface IEventSet
	BEGIN_CONNECTION_PART(CSourceObj, EventSetConnPt)
		virtual REFIID GetIID();
	END_CONNECTION_PART(EventSetConnPt)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSourceObj)
	afx_msg long GetMyProperty();
	afx_msg void SetMyProperty(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_CONNECTION_MAP()

	// event handler
	void FirePropChanged (long nInt);
private:
	long mProperty;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOURCEOBJ_H__B77C2985_56DD_11CF_B355_00104B08CC22__INCLUDED_)
