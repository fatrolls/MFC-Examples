#ifndef NGTOOLBAR__H
#define NGTOOLBAR__H

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#ifdef _DEBUG
#pragma comment(lib,"ngtlb10d.lib")
#pragma message("Automatically linking with ngtlb10d.dll")
#else
#pragma comment(lib,"ngtlb10r.lib")
#pragma message("Automatically linking with ngtlb10r.dll")
#endif

#ifndef TBSTYLE_TRANSPARENT
// Old commctrl.h compatibility
#define TBSTYLE_TRANSPARENT     0x8000 
#endif

#include <NGenericToolBar.h>
#include <NGenericMenu.h>
#include <NMDIMenuFrameWnd.h>
#include <NSDIMenuFrameWnd.h>
#include <NMDIClient.h>

#ifdef AUTO_SUBCLASS
// Automatically use new classes
#define CMDIFrameWnd CNMDIMenuFrameWnd
#define CFrameWnd CNSDIMenuFrameWnd
#define CToolBar CNGenericToolBar
#endif

#endif
