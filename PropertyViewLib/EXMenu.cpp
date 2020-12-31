// EXMenu.cpp : implementation file
//

#include "stdafx.h"
#include "EXMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EXMenu

IMPLEMENT_DYNCREATE(EXMenu, CMenu)

EXMenu::EXMenu()
{
}

EXMenu::~EXMenu()
{
	std::vector<EXMenu *>::iterator It;
	for(It = m_vMenues.begin();It != m_vMenues.end();It++)
	{
		delete (*It);
	}
}

/*
void EXMenu::AddMenuItem(int nStringId, int nMenuId)
{
	CString str;
	str.LoadString(nStringId);
	AppendMenu( MF_ENABLED , nMenuId , str);
}
*/

void EXMenu::AddSeparator()
{
	AppendMenu( MF_SEPARATOR );
}

void EXMenu::AddCommand( const char* pText , int nID , bool bChecked )
{
	UINT nFlags = MF_ENABLED;

	if( bChecked )
	{
		nFlags |= MF_CHECKED;
	}

	AppendMenu( nFlags , nID , pText );
}

void EXMenu::AddCommand( int nStringId , int nID , bool bChecked )
{
	CString str;
	str.LoadString(nStringId);
	AddCommand( str , nID , bChecked );
}

/*
void EXMenu::AddPopupMenuItem(UINT nID)
{
	EXMenu *pMenu = new EXMenu;
	
	CString str;
	UINT hSub;
	pMenu->CreatePopupMenu();
	str.LoadString(IDS_BROWSE);
	pMenu->AppendMenu( MF_ENABLED , nID , str);
	hSub = (UINT)pMenu->GetSafeHmenu();
	str.LoadString(nID);
	
	if( AppendMenu( MF_POPUP , hSub ,str) == 0)
	{
		// Append failed
		delete pMenu;
	}
	else
		m_vMenues.push_back(pMenu);
}
*/

void EXMenu::AttachPopupMenu(UINT nStringID, EXMenu *pMenu)
{
	CString str;
	str.LoadString(nStringID);
	UINT hSub = (UINT)pMenu->GetSafeHmenu();
	if( AppendMenu( MF_POPUP , hSub ,str) == 0)
	{
		// Append failed
		delete pMenu;
	}
	else
		m_vMenues.push_back(pMenu);
}

EXMenu* EXMenu::AddMenu( UINT nStringID )
{
	EXMenu* pMenu = new EXMenu;
	pMenu->CreateMenu();
	AttachPopupMenu( nStringID , pMenu );
	return pMenu;
}