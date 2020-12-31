// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1AC4ACBE_3750_4EED_AA26_576A93DDF940__INCLUDED_)
#define AFX_STDAFX_H__1AC4ACBE_3750_4EED_AA26_576A93DDF940__INCLUDED_

// Change these values to use different versions
#define WINVER		0x0400
#define _WIN32_IE	0x0500
#define _RICHEDIT_VER	0x0100


#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <AtlCtrls.h>
#include <wingdi.h>


#define chSTR(x)    #x
#define chSTR2(x)   chSTR(x)
#define chMSG(desc) message(__FILE__ "("chSTR2(__LINE__) "):" #desc)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1AC4ACBE_3750_4EED_AA26_576A93DDF940__INCLUDED_)
