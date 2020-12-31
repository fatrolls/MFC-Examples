#include "stdafx.h"
#include "TitledMenu.h"

//// This function adds a title entry to a popup menu//
void AddMenuTitle(CMenu* popup, LPCSTR title)
{
    // insert a separator item at the top
    popup->InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR, 0, title);
    // insert title item
    // note: item is not selectable (disabled) but not grayed
    popup->InsertMenu(0, MF_BYPOSITION | MF_STRING | MF_DISABLED, 0, title);
    SetMenuDefaultItem(popup->m_hMenu, 0, TRUE);
}


//
// This function adds a title entry to a popup menu
//
void AddMenuTitle(CMenu* popup)
{
    // insert a separator item at the top
    popup->InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR, 0, (LPSTR)0);

    // insert an empty owner-draw item at top to serve as the title
    // note: item is not selectable (disabled) but not grayed
    popup->InsertMenu(0, MF_BYPOSITION | MF_OWNERDRAW | MF_STRING | MF_DISABLED, 0, (LPSTR)0);
}

//
// This function creates the bold font for the popup menu's title
//
static HFONT CreatePopupMenuTitleFont()
{
    // start by getting the stock menu font
    HFONT font = (HFONT)GetStockObject(ANSI_VAR_FONT);
    if (font)
    {
        // now, get the complete LOGFONT describing this font
        LOGFONT lf;
        if (GetObject(font, sizeof(LOGFONT), &lf))
        {
            // set the weight to bold
            lf.lfWeight = FW_BOLD;

            // recreate this font with just the weight changed
            font = CreateFontIndirect(&lf);
        }
    }

    // return the new font - Note: Caller now owns this GDI object
    return font;
}

//
// This is a helper function to measure the popup menu's title item
//
void MeasurePopupMenuTitle(LPMEASUREITEMSTRUCT mi, LPCSTR menuTitle)
{
    // create the font we will use for the title
    HFONT font = CreatePopupMenuTitleFont();
    if (font)
    {
        // get the screen dc to use for retrieving size information
        CDC dc;
        dc.Attach(::GetDC(NULL));

        // select the title font
        CFont* old = (CFont*)dc.SelectObject(CFont::FromHandle(font));

        // compute the size of the title
        CSize size = dc.GetTextExtent(menuTitle);

        // deselect the title font
        dc.SelectObject(old);

        // delete the title font
        DeleteObject(font);

        // add in the left margin for the menu item
        size.cx += GetSystemMetrics(SM_CXMENUCHECK)+8;

        // return the width and height
        mi->itemWidth = size.cx;
        mi->itemHeight = size.cy;
    }
}

//
// This is a helper function to draw the popup menu's title item
//
void DrawPopupMenuTitle(LPDRAWITEMSTRUCT di, LPCSTR menuTitle)
{
    // create the font we will use for the title
    HFONT font = CreatePopupMenuTitleFont();
    if (font)
    {
        // create the background menu brush
        HBRUSH bgb = CreateSolidBrush(GetSysColor(COLOR_MENU));

        // fill the rectangle with this brush
        FillRect(di->hDC, &di->rcItem, bgb);

        // delete the brush
        DeleteObject(bgb);

        // set text mode to transparent
        int mode = SetBkMode(di->hDC, TRANSPARENT);

        // set text color to menu text color
        COLORREF color = SetTextColor(di->hDC, GetSysColor(COLOR_MENUTEXT));

        // select this font into the dc
        HFONT old = (HFONT)SelectObject(di->hDC, font);

        // add the menu margin offset
        di->rcItem.left += GetSystemMetrics(SM_CXMENUCHECK)+8;

        // draw the text left aligned and vertically centered
        DrawText(di->hDC, menuTitle, -1, &di->rcItem, DT_SINGLELINE|DT_VCENTER|DT_LEFT);

        // deselect the font
        SelectObject(di->hDC, old);

        // restore the text background mode
        SetBkMode(di->hDC, mode);

        // restore the text color
        SetTextColor(di->hDC, color);
    }
}
