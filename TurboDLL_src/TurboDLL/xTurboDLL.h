#ifndef __TURBO_DLL__
#define __TURBO_DLL__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _AFXDLL
	#pragma message("*** XXXXXXXXXXXXXXXXXXXXXXXXXXXX ***")
	#pragma message("*** Must Using MFC in Shared DLL ***")
	#pragma message("*** XXXXXXXXXXXXXXXXXXXXXXXXXXXX ***")
	#error No MFC
#endif

#include <afxtempl.h>

#ifdef _DEBUG
	#pragma comment(lib,"..\\lib\\Debug\\TurboDLLD.lib") 
	#pragma message("Automatically linking with TurboDLLD.lib ( Debug Version )") 
#else
	#pragma comment(lib,"..\\lib\\Release\\TurboDLL.lib") 
	#pragma message("Automatically linking with TurboDLL.lib ( Release Version )") 
#endif

#include "TreeListColumnInfo.h"
#include "TreeListItem.h"
#include "TreeListHeaderCtrl.h"
#include "TreeListTipCtrl.h"
#include "TreeListStaticCtrl.h"
#include "TreeListEditCtrl.h"
#include "TreeListComboCtrl.h"
#include "TreeListCtrl.h"

#endif  //TURBO_DLL__