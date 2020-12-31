/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   PopMenu.cpp
//
//  Author   :   Darren Richards (darrenr@gissing-consulting.co.uk)
//
//  Date     :   20th March 98
//
//  Synopsis :   Simple modal popup menu wrapper.
//
////////////////

/////////////////////////////////////////////////////////////////////////////
//
//  includes
//
///////////////

#include "stdafx.h"
#include "resource.h"
#include "PopMenu.h"

/////////////////////////////////////////////////////////////////////////////
//
//  CPopupMenu implementation
//
///////////////

CPopupMenu::CPopupMenu(POINT pt)
{
    m_pt = pt;
    m_hMenu = CreatePopupMenu();
}

CPopupMenu::~CPopupMenu()
{
    DestroyMenu(m_hMenu);
}

void CPopupMenu::AddItem(int nId, LPCSTR pszItem)
{
    MENUITEMINFO mi;

    ZeroMemory(&mi,sizeof(mi));
    mi.cbSize = sizeof(mi);

    mi.fMask        = MIIM_TYPE|MIIM_STATE|MIIM_ID;
    mi.fType        = MFT_STRING;
    mi.fState       = 0;
    mi.dwTypeData   = (char*)pszItem;
    mi.wID          = nId;

    InsertMenuItem(m_hMenu, nId, false, &mi); 
}

void CPopupMenu::AddSeparator()
{
    MENUITEMINFO mi;

    ZeroMemory(&mi,sizeof(mi));
    mi.cbSize = sizeof(mi);

    mi.fMask = MIIM_TYPE|MIIM_ID;
    mi.fType = MFT_SEPARATOR;
    mi.wID   = -1;

    InsertMenuItem(m_hMenu, -1, false, &mi); 
}

int CPopupMenu::TrackPopup()
{
    return TrackPopupMenu(m_hMenu,
                          TPM_RETURNCMD|TPM_LEFTALIGN|TPM_LEFTBUTTON,
                          m_pt.x,
                          m_pt.y,
                          0,
                          GetFocus(),
                          NULL);
}

