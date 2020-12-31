// $$root$$.h : main header file for the $$ROOT$$ application
//

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$:
// See $$root$$.cpp for the implementation of this class
//

class $$APP_CLASS$$ : public $$APP_BASE_CLASS$$
{
public:
	$$APP_CLASS$$();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$APP_CLASS$$)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG($$APP_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
$$ENDIF
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
