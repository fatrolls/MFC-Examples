#if !defined(AFX_ICMPCOMEVENTS_H__170A9482_F824_11D1_841C_00A0244DBC26__INCLUDED_)
#define AFX_ICMPCOMEVENTS_H__170A9482_F824_11D1_841C_00A0244DBC26__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ICMPComEvents.h : header file
//


class CPingDlg;

/////////////////////////////////////////////////////////////////////////////
// ICMPComEvents command target

class ICMPComEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(ICMPComEvents)

	ICMPComEvents(CPingDlg* pParent = NULL);  // protected constructor used by dynamic creation
	virtual ~ICMPComEvents();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ICMPComEvents)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPingDlg* m_pParent;
	void OnPingMsgEvent(LPCTSTR msg);
	void OnPingDone();
	void OnPingTerminated();


	// Generated message map functions
	//{{AFX_MSG(ICMPComEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()  // ping events
	DECLARE_INTERFACE_MAP()  
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICMPCOMEVENTS_H__170A9482_F824_11D1_841C_00A0244DBC26__INCLUDED_)
