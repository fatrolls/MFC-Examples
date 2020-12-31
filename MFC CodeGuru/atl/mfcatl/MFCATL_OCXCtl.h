#if !defined(AFX_MFCATL_OCXCTL_H__A9EE6E92_5F04_11D1_934C_E4CFDA000000__INCLUDED_)
#define AFX_MFCATL_OCXCTL_H__A9EE6E92_5F04_11D1_934C_E4CFDA000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MFCATL_OCXCtl.h : Declaration of the CMFCATL_OCXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXCtrl : See MFCATL_OCXCtl.cpp for implementation.

class CMFCATL_OCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMFCATL_OCXCtrl)

// Constructor
public:
	CMFCATL_OCXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCATL_OCXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CMFCATL_OCXCtrl();

	DECLARE_OLECREATE_EX(CMFCATL_OCXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMFCATL_OCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMFCATL_OCXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMFCATL_OCXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMFCATL_OCXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMFCATL_OCXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMFCATL_OCXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMFCATL_OCXCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCATL_OCXCTL_H__A9EE6E92_5F04_11D1_934C_E4CFDA000000__INCLUDED)
