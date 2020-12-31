#ifndef TITLED_MENU_H
#define TITLED_MENU_H

void AddMenuTitle(CMenu* popup, LPCSTR title);
void AddMenuTitle(CMenu* popup);
void MeasurePopupMenuTitle(LPMEASUREITEMSTRUCT mi, LPCSTR menuTitle);
void DrawPopupMenuTitle(LPDRAWITEMSTRUCT di, LPCSTR menuTitle);

#endif

