
#ifdef UILIB_EXPORTS
#define UILIB_API __declspec(dllexport)
#else
#define UILIB_API __declspec(dllimport)
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>

#include "UIBase.h"
#include "UIAnim.h"
#include "UIManager.h"
#include "UIBlue.h"
#include "UIContainer.h"
#include "UIList.h"
#include "UIEdit.h"
#include "UILabel.h"
#include "UITab.h"
#include "UICombo.h"
#include "UITool.h"
#include "UIButton.h"
#include "UIPanel.h"
#include "UIActiveX.h"
#include "UIDecoration.h"

#include "UIMarkup.h"
#include "UIDlgBuilder.h"

