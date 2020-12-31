///////////////////////////////////////////////////////////////////
//  Module   : FLIPDLG.CPP
//
//  Purpose  : Implementation of the CAboutDlg and CWallFlipDlg 
//             classes.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-27-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WallFlip.h"
#include "FlipDlg.h"
#include <winreg.h>   // Windows Registry interface header

///////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
   CAboutDlg();

   enum { IDD = IDD_ABOUTBOX };
protected:
   virtual void DoDataExchange(CDataExchange* pDX); 
};

///////////////////////////////////////////////////////////////////
// CAboutDlg::CAboutDlg()

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

///////////////////////////////////////////////////////////////////
// CAboutDlg::DoDataExchange()

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg message map

BEGIN_MESSAGE_MAP(CWallFlipDlg, CDialog)
   ON_WM_SYSCOMMAND()
   ON_BN_CLICKED(IDC_BTNABOUT, OnBtnAboutClick)
   ON_BN_CLICKED(IDC_BTNADD, OnBtnAddClick)
   ON_BN_CLICKED(IDC_BTNREMOVE, OnBtnRemoveClick)
   ON_WM_DESTROY()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::CWallFlipDlg()

CWallFlipDlg::CWallFlipDlg(CWnd* pParent)
   : CDialog(CWallFlipDlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::DoDataExchange()

void CWallFlipDlg::DoDataExchange(CDataExchange* pDX)
{
   // Call inherited method
   CDialog::DoDataExchange(pDX);
   
   DDX_Control(pDX, IDC_BTNREMOVE, m_btnRemove);
   DDX_Control(pDX, IDC_BTNADD, m_btnAdd);
   DDX_Control(pDX, IDC_BTNABOUT, m_btnAbout);
   DDX_Control(pDX, IDC_BITMAPLIST, m_listBitmaps);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::OnInitDialog()

BOOL CWallFlipDlg::OnInitDialog()
{
   // Call inherited method
   CDialog::OnInitDialog();

   // Add "About..." menu item to system menu.
   // IDM_ABOUTBOX must be in the system command range.
   ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
   ASSERT(IDM_ABOUTBOX < 0xF000);

   CMenu* pSysMenu = GetSystemMenu(FALSE);
   CString strAboutMenu;
   strAboutMenu.LoadString(IDS_ABOUTBOX);
   if (!strAboutMenu.IsEmpty())
   {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
   }

   // Set the icon for this dialog
   SetIcon(m_hIcon, TRUE);       // Set big icon
   SetIcon(m_hIcon, FALSE);      // Set small icon
   
   // Get bitmap filenames from registry
   GetRegData();
   
   return TRUE;  
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::OnSysCommand()

void CWallFlipDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
   if ((nID & 0xFFF0) == IDM_ABOUTBOX)
   {
      CAboutDlg dlgAbout;
      dlgAbout.DoModal();
   }
   else
   {
      CDialog::OnSysCommand(nID, lParam);
   }
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::OnBtnAboutClick()

void CWallFlipDlg::OnBtnAboutClick()
{
   // Display the "About" box
   CAboutDlg dlgAbout;
   dlgAbout.DoModal();
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::OnBtnAddClick()

void CWallFlipDlg::OnBtnAddClick() 
{
   // Allow user to select bitmaps
   CFileDialog dlg(TRUE, NULL, NULL, 
      OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT,
      "Bitmaps (*.bmp)|*.bmp");            

   dlg.m_ofn.lpstrTitle = "Select Bitmap File(s)";
      
   if (IDCANCEL == dlg.DoModal())
      return;

   // Add the selected file(s) to the list box
   POSITION pos = dlg.GetStartPosition();

   while (pos)
   {
      CString str = dlg.GetNextPathName(pos);

      // Prevent duplicate strings by searching all items in the
      // list box

      if (LB_ERR == m_listBitmaps.FindString(-1, (LPCTSTR)str))
         m_listBitmaps.AddString((LPCTSTR)str);
   }
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::OnBtnRemoveClick()

void CWallFlipDlg::OnBtnRemoveClick() 
{
   int nCurSel = m_listBitmaps.GetCurSel(); 

   if (nCurSel != LB_ERR)
      m_listBitmaps.DeleteString(nCurSel);

   m_btnRemove.EnableWindow(FALSE);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::SetRegValue() - writes a registry string value

void CWallFlipDlg::SetRegValue(HKEY hKey, 
                               CString strKey, 
                               CString strChildKey, 
                               CString strChildKeyValue)
{
   HKEY   hChildKey = 0;
   DWORD  dwDisposition;

   // Create or open the registry key
   RegCreateKeyEx(hKey,
      (LPCTSTR) strKey, 
      0, 
      NULL, 
      REG_OPTION_NON_VOLATILE,
      KEY_CREATE_SUB_KEY | KEY_ALL_ACCESS, 
      NULL, 
      &hChildKey,
      &dwDisposition
   );   

   // Set the new value for the key
   RegSetValueEx(
      hChildKey,
      (LPCTSTR) strChildKey, 
      0,
      REG_SZ,
      (const BYTE*)(LPCTSTR)strChildKeyValue, 
      (DWORD) strChildKeyValue.GetLength()
   );
   // Close the key
   RegCloseKey(hChildKey);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::SetRegValue() - writes a registry dword value

void CWallFlipDlg::SetRegValue(HKEY hKey, 
                               CString strKey, 
                               CString strChildKey, 
                               DWORD dwChildKeyValue)
{
   HKEY  hChildKey = 0;
   DWORD dwDisposition;

   // Create or open the registry key
   RegCreateKeyEx(hKey,
      (LPCTSTR) strKey, 
      0, 
      NULL, 
      REG_OPTION_NON_VOLATILE,
      KEY_CREATE_SUB_KEY | KEY_ALL_ACCESS, 
      NULL, 
      &hChildKey,
      &dwDisposition
   );   

   // Set the new value for the key
   RegSetValueEx(
      hChildKey,
      (LPCTSTR) strChildKey, 
      0,
      REG_DWORD,
      (const BYTE*) &dwChildKeyValue, 
      sizeof(DWORD)
   );
   RegCloseKey(hChildKey);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::OnDestroy() 

void CWallFlipDlg::OnDestroy() 
{
   // Call inherited method
   CDialog::OnDestroy();

   // Specify the registry location to save info to
   CString strKey = 
      "SOFTWARE\\TikiSoft\\WallFlip\\CurrentVersion";
   
   // Delete any existing keys from this location
   RegDeleteKey(HKEY_CURRENT_USER, strKey);

   // Save bitmap names (if any) to registry
   CWallFlipApp* pApp = (CWallFlipApp*) AfxGetApp();
   for (int i = 0; i < m_listBitmaps.GetCount(); i++)
   {
      CString strChildKey = "Bitmap" + pApp->IntToString(i + 1);
      CString strChildKeyValue;
      m_listBitmaps.GetText(i, strChildKeyValue);

      SetRegValue(HKEY_CURRENT_USER, strKey, strChildKey, 
         strChildKeyValue);
   }
   // Save the number of bitmap filenames stored here
   SetRegValue(HKEY_CURRENT_USER, strKey, "BitmapCount", 
      m_listBitmaps.GetCount());

   // Set the next wallpaper bitmap index
   SetRegValue(HKEY_CURRENT_USER, strKey, "NextBitmap", 0);

   // Set the app to autorun when Windows starts
   strKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
   CString str = GetCommandLine();
   str += " /flip";
   
   SetRegValue(HKEY_LOCAL_MACHINE, strKey, "WallFlip", str);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::OnCommand()

BOOL CWallFlipDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
   // Enable or disable the Remove button, depending on selection
   BOOL bEnable = (m_listBitmaps.GetCurSel() >= 0);
   m_btnRemove.EnableWindow(bEnable);
   
   return CDialog::OnCommand(wParam, lParam);
}

///////////////////////////////////////////////////////////////////
// CWallFlipDlg::GetRegData()

void CWallFlipDlg::GetRegData() 
{
   // Specify the registry location to get data from
   CString strKey = 
      "SOFTWARE\\TikiSoft\\WallFlip\\CurrentVersion";   

   // Open the registry key
   HKEY hResult;
   if (ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, 
       (LPCTSTR) strKey, &hResult)) 
      return;

   // Get the values
   BYTE   cFilenames;
   DWORD  dwCount = sizeof(DWORD);

   if (ERROR_SUCCESS != RegQueryValueEx(hResult, 
      (LPCTSTR) "BitmapCount", 0, 0, 
      &cFilenames, &dwCount))
   {
     RegCloseKey(hResult);    // Close the key
     return;
   }

   // Iterate through the bitmap filenames
   CWallFlipApp* pApp = (CWallFlipApp*) AfxGetApp();
   for (int i = 0; i < cFilenames; i++)
   {
      CString str = "Bitmap" + pApp->IntToString(i + 1);
      BYTE   szBuf[255];
      dwCount = 255;

      RegQueryValueEx(hResult, (LPCTSTR) str,
         0, 0, &szBuf[0], &dwCount);

      // Add the string to the list box
      m_listBitmaps.AddString((LPCTSTR) szBuf);
   }
   // Close the key
   RegCloseKey(hResult);   
}

///////////////////////////////////////////////////////////////////
