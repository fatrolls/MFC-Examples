#include "stdafx.h"
#include "Ini.h"
#include "MainFrm.h"
#include "ToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CToolBarEx::CToolBarEx()
{
}

CToolBarEx::~CToolBarEx()
{
}

BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
	//{{AFX_MSG_MAP(CToolBarEx)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CToolBarEx::OnDestroy() 
{
	CToolBar::OnDestroy();
}

void CToolBarEx::OnClose() 
{

	CToolBar::OnClose();
}
