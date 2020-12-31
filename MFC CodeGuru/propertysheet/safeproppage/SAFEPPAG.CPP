/*
Name:           SAFEPPAG.CPP

Author:         AdaMcPetr (petr.adamek@antek.cz) & Petr Novotny (petr.novotny@antek.cz)

Description:    see header.

Revision:       May 20 1998     -       created
*/
#include <afxwin.h>

#include "safeppag.h"

  CSafePropertyPage::CSafePropertyPage (
        UINT nIDTemplate,
        UINT nIDCaption
                                       ) : CPropertyPage (nIDTemplate, nIDCaption)
    {
      SetPageTemplate (MAKEINTRESOURCE (nIDTemplate));
    }
  
  CSafePropertyPage::CSafePropertyPage (
        LPCTSTR lpszTemplateName,
        UINT nIDCaption
                                       ) : CPropertyPage (lpszTemplateName, nIDCaption)
    {
      SetPageTemplate (lpszTemplateName);
    }

void
  CSafePropertyPage::SetPageTemplate (
        LPCTSTR lpszTemplateName
                                     )
    {
      m_Template.Load (lpszTemplateName);

      m_psp.pResource = (LPCDLGTEMPLATE)m_Template.m_hTemplate;

      m_psp.dwFlags |= PSP_DLGINDIRECT;
    }

IMPLEMENT_DYNAMIC (CSafePropertyPage, CPropertyPage);

