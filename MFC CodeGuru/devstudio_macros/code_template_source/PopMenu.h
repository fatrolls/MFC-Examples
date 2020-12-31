/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   PopMenu.h
//
//  Author   :   Darren Richards (darrenr@gissing-consulting.co.uk)
//
//  Date     :   20th March 98
//
//  Synopsis :   Simple modal popup menu wrapper.
//
////////////////

#ifndef POPMENU_H
#define POPMENU_H

/////////////////////////////////////////////////////////////////////////////
//
//  class CPopupMenu
//
///////////////

class CPopupMenu
{
public:

    CPopupMenu(POINT pt);
    ~CPopupMenu();

    void AddItem(int nId, LPCSTR pszItem);
    void AddSeparator();
    int TrackPopup();

private:
    HMENU m_hMenu;
    POINT m_pt;
    HBITMAP m_hbmpHdg;
};

#endif // POPMENU_H