/*
Module : PUSHPIN.H
Purpose: Interface of a push pin button 
         (as seen on X-Windows & property dialogs in VC 4)
Created: PJN / DATE/1 / 04-04-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

#ifndef __PUSHPIN_H__            


////////////////////////////////// Includes ///////////////////////////////////

#include "win32sup.h"



class AFX_EXT_CLASS CPushPinButton : public CBitmapButton
{
public:
  EXPORT16 CPushPinButton();
  virtual EXPORT16 ~CPushPinButton();

  BOOL EXPORT16 IsPinned() { return m_bPinned; };


  //{{AFX_MSG(CPushPinButton)
  afx_msg void OnClicked();
  //}}AFX_MSG

protected:
  //{{AFX_VIRTUAL(CPushPinButton)
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  //}}AFX_VIRTUAL

  DECLARE_MESSAGE_MAP()
  BOOL m_bPinned;
};

#endif //__PUSHPIN_H__