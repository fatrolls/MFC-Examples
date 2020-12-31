// FoldersBar.cpp : implementation file
//

#include "stdafx.h"
#include "skinsdemo.h"
#include "FoldersBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT IDC_FOLDERTREE = 1000;

/////////////////////////////////////////////////////////////////////////////
// CFoldersBar

CFoldersBar::CFoldersBar()
{
}

CFoldersBar::~CFoldersBar()
{
}


BEGIN_MESSAGE_MAP(CFoldersBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(CFoldersBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFoldersBar message handlers

int CFoldersBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetClientBorder(TRUE);
	if (!m_FolderTree.Create(WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_LINESATROOT |
		TVS_HASBUTTONS | TVS_EDITLABELS | TVS_SHOWSELALWAYS, CRect(0,0,0,0), this,
		IDC_FOLDERTREE))
	{
		return -1;
	}

	m_FolderTree.InitializeTree();
	
	return 0;
}

void CFoldersBar::OnSize(UINT nType, int cx, int cy) 
{
	COXSizeControlBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rectClient;
	GetClientRect(rectClient);
	m_FolderTree.MoveWindow(rectClient);	
}
