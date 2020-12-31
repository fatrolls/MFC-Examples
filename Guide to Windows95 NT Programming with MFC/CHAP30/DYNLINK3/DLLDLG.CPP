///////////////////////////////////////////////////////////////////
//  Header  : DLLDLG.CPP
//
//  Purpose : Implementation file for the CDllDialog class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-02-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "dlldlg.h"

///////////////////////////////////////////////////////////////////
// CDllDialog::CDllDialog() - dialog constructor

CDllDialog::CDllDialog(CWnd* pParent /*=NULL*/)
   : CDialog(CDllDialog::IDD, pParent)
{
}

///////////////////////////////////////////////////////////////////
// CDllDialog::DoDataExchange()

void CDllDialog::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
}

///////////////////////////////////////////////////////////////////
// CDllDialog message handlers

BOOL CDllDialog::OnInitDialog() 
{
   // Call inherited method
   CDialog::OnInitDialog();
   
   // Set the dislog text from string table resource data
   CString str;
   str.LoadString(IDS_TEXT1);
   
   CStatic* pText = (CStatic*) GetDlgItem(IDC_TEXT1);
   if (pText)
      pText->SetWindowText((LPCTSTR) str);

   return TRUE;
}

///////////////////////////////////////////////////////////////////
