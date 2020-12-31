#ifndef NETWORK_TREE_CTRL_H
#define NETWORK_TREE_CTRL_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NetworkTreeCtrl.h : header file
//

#ifndef COLOR_TREE_CTRL_H
	#include "ColorTreeCtrl.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetworkTreeCtrl window

class CNetworkTreeCtrl : public CColorTreeCtrl
{
// Construction
public:
	CNetworkTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNetworkTreeCtrl();


	void Refresh();
	
	// Generated message map functions
protected:
	void WNetEnum(LPNETRESOURCE lpNetResource,DWORD dwDeep,CTreeCursor &node);

	
	//{{AFX_MSG(CNetworkTreeCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 
