///////////////////////////////////////////////////////////////////
//  Module  : JIGGLERP.CPP
//
//  Purpose : Implementation of the CJigglerPropPage property 
//            page class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-27-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Jiggler.h"
#include "JigglerP.h"

IMPLEMENT_DYNCREATE(CJigglerPropPage, COlePropertyPage)

///////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJigglerPropPage, COlePropertyPage)
   //{{AFX_MSG_MAP(CJigglerPropPage)
   // NOTE - ClassWizard will add and remove message map entries
   //    DO NOT EDIT what you see in these blocks of generated code !
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJigglerPropPage, "JIGGLER.JigglerPropPage.1",
   0x5cd2fc84, 0xe7bd, 0x11cf, 0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0, 0)


///////////////////////////////////////////////////////////////////
// CJigglerPropPage::CJigglerPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CJigglerPropPage

BOOL CJigglerPropPage::CJigglerPropPageFactory::UpdateRegistry(BOOL bRegister)
{
   if (bRegister)
      return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
         m_clsid, IDS_JIGGLER_PPG);
   else
      return AfxOleUnregisterClass(m_clsid, NULL);
}


///////////////////////////////////////////////////////////////////
// CJigglerPropPage::CJigglerPropPage - Constructor

CJigglerPropPage::CJigglerPropPage() :
   COlePropertyPage(IDD, IDS_JIGGLER_PPG_CAPTION)
{
   //{{AFX_DATA_INIT(CJigglerPropPage)
   m_Caption = _T("");
   m_nInterval = 100;
   //}}AFX_DATA_INIT
}

///////////////////////////////////////////////////////////////////
// CJigglerPropPage::DoDataExchange - Moves data between page 
//  and properties

void CJigglerPropPage::DoDataExchange(CDataExchange* pDX)
{
   //{{AFX_DATA_MAP(CJigglerPropPage)
   DDP_Text(pDX, IDC_EDIT_CAPTION, m_Caption, _T("Caption") );
   DDX_Text(pDX, IDC_EDIT_CAPTION, m_Caption);
   DDV_MaxChars(pDX, m_Caption, 50);
   DDP_Text(pDX, IDC_EDIT_INTERVAL, m_nInterval, _T("Interval") );
   DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInterval);
   DDV_MinMaxInt(pDX, m_nInterval, 10, 1000);
   //}}AFX_DATA_MAP
   DDP_PostProcessing(pDX);
}

///////////////////////////////////////////////////////////////////

