///////////////////////////////////////////////////////////////////
//  Module  : PANEL3DP.CPP
//
//  Purpose : Implementation of the CPanel3dPropPage property 
//            page class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-10-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "panel3d.h"
#include "panel3dp.h"
#include "panel3dc.h"

IMPLEMENT_DYNCREATE(CPanel3dPropPage, COlePropertyPage)

///////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPanel3dPropPage, 
   "PANEL3D.Panel3dPropPage.1",
	0x4d85cc84, 0xd9c6, 0x11cf, 0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 
   0, 0)

///////////////////////////////////////////////////////////////////
// CPanel3dPropPage::CPanel3dPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPanel3dPropPage

BOOL CPanel3dPropPage::CPanel3dPropPageFactory::UpdateRegistry(
   BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(
         AfxGetInstanceHandle(), m_clsid, IDS_PANEL3D_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

///////////////////////////////////////////////////////////////////
// CPanel3dPropPage::CPanel3dPropPage - Constructor

CPanel3dPropPage::CPanel3dPropPage() :
	COlePropertyPage(IDD, IDS_PANEL3D_PPG_CAPTION)
{
	// Init class members
   m_bevelWidth    = 0;
	m_Caption       = _T("");
   m_textAlignment = CPanel3dCtrl::taCenter;
	m_drawText3d    = FALSE;
	m_drawBorder    = FALSE;
	m_bevelStyle    = CPanel3dCtrl::bsInset;
}

///////////////////////////////////////////////////////////////////
// CPanel3dPropPage::DoDataExchange - 
// Moves data between page and properties

void CPanel3dPropPage::DoDataExchange(CDataExchange* pDX)
{
	// Bevel Width
   DDP_Text(pDX, IDC_EDIT_BEVELWIDTH, m_bevelWidth,
      _T("BevelWidth"));
	DDX_Text(pDX, IDC_EDIT_BEVELWIDTH, m_bevelWidth);
	DDV_MinMaxInt(pDX, m_bevelWidth, 0, 20);
	
   // Caption
   DDP_Text(pDX, IDC_EDIT_CAPTION, m_Caption, _T("Caption"));
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_Caption);
	DDV_MaxChars(pDX, m_Caption, 25);
	
   // Text Alignment
   DDP_CBIndex(pDX, IDC_CBTEXTALIGN, m_textAlignment, 
      _T("TextAlignment"));
	DDX_CBIndex(pDX, IDC_CBTEXTALIGN, m_textAlignment);
	
   // "3D" Text
   DDP_Check(pDX, IDC_CHK3D, m_drawText3d, _T("DrawText3d") );
	DDX_Check(pDX, IDC_CHK3D, m_drawText3d);
	
   // Border
   DDP_Check(pDX, IDC_CHKDRAWBORDER, m_drawBorder, 
      _T("DrawBorder"));
	DDX_Check(pDX, IDC_CHKDRAWBORDER, m_drawBorder);
	
   // Bevel Style
   DDP_Radio(pDX, IDC_RADIONONE, m_bevelStyle, _T("BevelStyle"));
	DDX_Radio(pDX, IDC_RADIONONE, m_bevelStyle);

	// Finish the transfer of property values
   DDP_PostProcessing(pDX);
}

///////////////////////////////////////////////////////////////////
