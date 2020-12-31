/*
Name:           SAFEPPAG.H

Author:         AdaMcPetr (petr.adamek@antek.cz) & Petr Novotny (petr.novotny@antek.cz)

Description:    Fix of problem described at KB Article ID: Q158552.
                Use CSafePropertyPage class instead of CPropertyPage class.
                The fix uses CDialogTemplate class to create copy of resource
                template in R/W memory.

Revision:       May 20 1998     -       created
*/
#ifndef _SAFEPPAG_H_

#define _SAFEPPAG_H_

#include <afxext.h>
#include <afxpriv.h>

class CSafePropertyPage : public CPropertyPage
  {
public:
    CSafePropertyPage (
        UINT,
        UINT = 0
                      );
  
    CSafePropertyPage (
        LPCTSTR,
        UINT = 0
                      );

private:
    CDialogTemplate m_Template;

    void
      SetPageTemplate (
        LPCTSTR
                      );

DECLARE_DYNAMIC (CSafePropertyPage);
  };

#endif
