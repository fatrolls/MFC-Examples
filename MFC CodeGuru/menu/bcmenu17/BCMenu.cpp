//*************************************************************************
// BCMenu.cpp : implementation file
// Version : 1.7
// Date : February 2, 1998
// Author : Brent Corkum
// 
// Portions of code supplied by:
// Ben Ashley,Girish Bharadwaj,Jean-Edouard Lachand-Robert,
// Robert Edward Caldecott,Kenny Goers,Leonardo Zide,
// Stefan Kuhr
//
// Bug Fixes:
// Stefan Kuhr,Martin Vladic
//
// You are free to use/modify this code but leave this header intact.
//

#include "stdafx.h"        // Standard windows header file
#include "BCMenu.h"        // BCMenu class declaration

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GAP 1
#ifndef OBM_CHECK
#define OBM_CHECK 32760 // from winuser.h
#endif

#if _MFC_VER <0x400
#error This code does not work on Versions of MFC prior to 4.0
#endif

static CPINFO CPInfo;

enum Win32Type{
Win32s,
Windoze95,
WinNT3,
WinNT4orHigher
};


Win32Type IsNewShell()
{
  Win32Type  ShellType;
  DWORD winVer;
  OSVERSIONINFO *osvi;

  winVer=GetVersion();
  if(winVer<0x80000000){/*NT */
    ShellType=WinNT3;
    osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
    if (osvi!=NULL){
      memset(osvi,0,sizeof(OSVERSIONINFO));
      osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
      GetVersionEx(osvi);
      if (osvi->dwMajorVersion>=4L)
        ShellType=WinNT4orHigher;//yup, it is NT 4 or higher!
      free(osvi);
    }
  }
  else if  (LOBYTE(LOWORD(winVer))<4)
    ShellType=Win32s;/*Win32s*/
  else
    ShellType=Windoze95;/*Windoze95*/
  return ShellType;
}

static Win32Type g_Shell=IsNewShell();

void BCMenuData::SetAnsiString(LPCSTR szAnsiString)
{
  ASSERT(szAnsiString);
  int iBufSize=(CPInfo.MaxCharSize==1)?strlen(szAnsiString):_mbstrlen(szAnsiString);
  iBufSize++;//Increment for the terminating NULL 
  wchar_t *szText=new wchar_t[iBufSize];

  VERIFY(MultiByteToWideChar(
    CP_ACP,     // code page 
    MB_PRECOMPOSED,     // character-type options 
    szAnsiString,       // address of string to map 
    -1, // number of characters in string 
    szText,     // address of wide-character buffer 
    iBufSize*sizeof(wchar_t)// size of buffer 
   ));
  ASSERT(wcslen(szText)==strlen(szAnsiString));
  wcscpy(menuText,szText);
  delete[] szText;
}

CString BCMenuData::GetString(void)//returns the menu text in ANSI or UNICODE
//depending on the MFC-Version we are using
{
  CString strText;

#ifdef UNICODE
  strText = menuText;
#else
  int iLen=(wcslen(menuText)+1)*sizeof(wchar_t);
  char *szAnsiString=new char[iLen];
    
  if (*menuText){
    VERIFY(WideCharToMultiByte(
            CP_ACP,     // code page 
            0,  // performance and mapping flags 
            menuText,   // address of wide-character string 
            -1, // number of characters in string 
            szAnsiString,       // address of buffer for new string 
            iLen,       // size of buffer 
            NULL,       // address of default for unmappable characters  
            NULL        // address of flag set when default char. used 
            ));
    strText=szAnsiString;
  }
  else strText.Empty();
  delete[] szAnsiString;
#endif    
return strText;
}


/*
 
===============================================================================
  BCMenu::BCMenu()
  TCMeny::~BCMenu()
  -----------------

  Constructor and Destructor.
 
===============================================================================
*/

BCMenu::BCMenu()
{
  m_iconX = 16;            // Icon sizes default to 16 x 16
  m_iconY = 15;            // ...
  m_selectcheck = -1;
  m_unselectcheck = -1;
  checkmaps=NULL;
  checkmapsshare=FALSE;
  // set the color used for the transparent background in all bitmaps
  m_bitmapBackground=RGB(192,192,192); //gray
  m_bitmapBackgroundFlag=FALSE;
  GetCPInfo(CP_ACP,&CPInfo);
}


BCMenu::~BCMenu()
{
  DestroyMenu();
}

BCMenuData::~BCMenuData()
{
  if(bitmap)delete(bitmap);
}

BOOL BCMenu::IsMenu(CMenu *submenu)
{
  int m;

  int numSubMenus = m_SubMenus.GetUpperBound();
  for(m=0;m<=numSubMenus;++m){
    if(submenu==m_SubMenus[m])return(TRUE);
  }
  return(FALSE);
}

BOOL BCMenu::DestroyMenu()
{
  // Destroy Sub menus:
  int m;
  int numSubMenus = m_SubMenus.GetUpperBound();
  for(m = numSubMenus; m >= 0; m--)delete(m_SubMenus[m]);
  m_SubMenus.RemoveAll();
  // Destroy menu data
  int numItems = m_MenuList.GetUpperBound();
  for(m = 0; m <= numItems; m++)delete(m_MenuList[m]);
  m_MenuList.RemoveAll();
  if(checkmaps&&!checkmapsshare){
    delete checkmaps;
    checkmaps=NULL;
  }
  // Call base-class implementation last:
  return(CMenu::DestroyMenu());
};


///////////////////////////////////////////////////////////////////////////
//
// BCMenu message handlers


/*
==========================================================================
void BCMenu::DrawItem(LPDRAWITEMSTRUCT)
---------------------------------------

Called by the framework when a particular item needs to be drawn.  We
overide this to draw the menu item in a custom-fashion, including icons
and the 3D rectangle bar.
==========================================================================
*/


void BCMenu::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
  ASSERT(lpDIS != NULL);
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CRect rect;
  UINT state = (((BCMenuData*)(lpDIS->itemData))->nFlags);
  if(state & MF_SEPARATOR){
    rect.CopyRect(&lpDIS->rcItem);
    rect.top+=rect.Height()>>1;
    pDC->DrawEdge(&rect,EDGE_ETCHED,BF_TOP);
  }
  else{
    CRect rect2;
    BOOL standardflag=FALSE,selectedflag=FALSE,disableflag=FALSE;
    BOOL checkflag=FALSE;
    CBitmap bitmapstandard;
    CDC dcDisplayMemory;
    COLORREF crText = GetSysColor(COLOR_MENUTEXT);
    COLORREF m_clrBack=GetSysColor(COLOR_MENU);
    CBrush m_brBackground,m_brSelect;
    CPen m_penBack;
    int x0,y0,dy;
    int nIconNormal=-1,xoffset=-1;
    CImageList *bitmap=NULL;
    CFont m_fontMenu;
    LOGFONT m_lf;

    // set some colors and the font
    m_penBack.CreatePen (PS_SOLID,0,GetSysColor(COLOR_MENU));
    m_brBackground.CreateSolidBrush(GetSysColor(COLOR_MENU));
    m_brSelect.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
    ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
    NONCLIENTMETRICS nm;
    nm.cbSize = sizeof (NONCLIENTMETRICS);
    VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
    m_lf =  nm.lfMenuFont;
    m_fontMenu.CreateFontIndirect (&m_lf);

    // draw the colored rectangle portion
  
    rect.CopyRect(&lpDIS->rcItem);
    rect2=rect;
 
    // draw the up/down/focused/disabled state

    UINT action = lpDIS->itemAction;
    UINT state = lpDIS->itemState;
    CString strText;
    LOGFONT lf;
    lf = m_lf;

    CFont dispFont;
    CFont *pFont;
      
    if(lpDIS->itemData != NULL){
      nIconNormal = (((BCMenuData*)(lpDIS->itemData))->menuIconNormal);
      xoffset = (((BCMenuData*)(lpDIS->itemData))->xoffset);
      bitmap = (((BCMenuData*)(lpDIS->itemData))->bitmap);
      strText = ((BCMenuData*) (lpDIS->itemData))->GetString();
    
      if(state&ODS_CHECKED && nIconNormal<0){
        if(state&ODS_SELECTED && m_selectcheck>0)checkflag=TRUE;
        else if(m_unselectcheck>0) checkflag=TRUE;
      }
      else if(nIconNormal != -1){
        standardflag=TRUE;
        if(state&ODS_SELECTED && !(state&ODS_GRAYED))selectedflag=TRUE;
        else if(state&ODS_GRAYED) disableflag=TRUE;
      }
    }
    else{
      strText.Empty();
    }

    if(state&ODS_SELECTED){ // draw the down edges

      CPen *pOldPen = pDC->SelectObject (&m_penBack);

      // You need only Text highlight and thats what you get
     
      if(checkflag||standardflag||selectedflag||disableflag||state&ODS_CHECKED)
        rect2.SetRect(rect.left+m_iconX+4+GAP,rect.top,rect.right,rect.bottom);
      pDC->FillRect (rect2,&m_brSelect);

      pDC->SelectObject (pOldPen);
      if((HFONT)dispFont != NULL)dispFont.DeleteObject ();
      dispFont.CreateFontIndirect (&lf);
      crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
    }
    else {
      CPen *pOldPen = pDC->SelectObject (&m_penBack);
      pDC->FillRect (rect,&m_brBackground);
      pDC->SelectObject (pOldPen);

      // draw the up edges

      pDC->Draw3dRect (rect,m_clrBack,m_clrBack);
      if ((HFONT)dispFont != NULL) dispFont.DeleteObject ();
      dispFont.CreateFontIndirect (&lf); //Normal
    }

    // draw the text if there is any
    //We have to paint the text only if the image is nonexistant

    dy = (rect.Height()-4-m_iconY)/2;
    dy = dy<0 ? 0 : dy;

    if(checkflag||standardflag||selectedflag||disableflag){
      rect2.SetRect(rect.left+1,rect.top+1+dy,rect.left+m_iconX+3,
                    rect.top+m_iconY+3+dy);
      pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
      if(checkflag && checkmaps){
        pDC->FillRect (rect2,&m_brBackground);
        rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                      rect.top+m_iconY+4+dy);
        pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
        CPoint ptImage(rect.left+2,rect.top+2+dy);
       
        if(state&ODS_SELECTED)checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
        else checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
      }
      else if(disableflag){
        if(!selectedflag){
          bitmapstandard.LoadBitmap(nIconNormal);
          rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                        rect.top+m_iconY+4+dy);
          pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
          DitherBlt(lpDIS->hDC,rect.left+2,rect.top+2+dy,m_iconX,m_iconY,
                (HBITMAP)(bitmapstandard),xoffset*m_iconX,0);
          bitmapstandard.DeleteObject();
        }
      }
      else if(selectedflag){
        pDC->FillRect (rect2,&m_brBackground);
        rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                      rect.top+m_iconY+4+dy);
        if (Windoze95==g_Shell || WinNT4orHigher==g_Shell){
          if(state&ODS_CHECKED)
            pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),
                            GetSysColor(COLOR_3DHILIGHT));
          else
            pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DHILIGHT),
                            GetSysColor(COLOR_3DSHADOW));
        }
        CPoint ptImage(rect.left+2,rect.top+2+dy);
        if(bitmap)bitmap->Draw(pDC,xoffset,ptImage,ILD_TRANSPARENT);
      }
      else{
        if(state&ODS_CHECKED){
          CBrush brush;
          COLORREF col =GetSysColor(COLOR_3DLIGHT);
          brush.CreateSolidBrush(col);
          pDC->FillRect(rect2,&brush);
          brush.DeleteObject();
          rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                        rect.top+m_iconY+4+dy);
          if (Windoze95==g_Shell || WinNT4orHigher==g_Shell)
            pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),
                            GetSysColor(COLOR_3DHILIGHT));
        }
        else{
          pDC->FillRect (rect2,&m_brBackground);
          rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                        rect.top+m_iconY+4+dy);
          pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
        }
        CPoint ptImage(rect.left+2,rect.top+2+dy);
        if(bitmap)bitmap->Draw(pDC,xoffset,ptImage,ILD_TRANSPARENT);
      }
    }

    if(nIconNormal<0 && state&ODS_CHECKED && !checkflag){
      rect2.SetRect(rect.left+1,rect.top+2+dy,rect.left+m_iconX+1,
                    rect.top+m_iconY+2+dy);
      CMenuItemInfo info;
      info.fMask = MIIM_CHECKMARKS;
      GetMenuItemInfo((HMENU)lpDIS->hwndItem,lpDIS->itemID,
                      MF_BYCOMMAND, &info);
      if(state&ODS_CHECKED || info.hbmpUnchecked) {
        Draw3DCheckmark(pDC, rect2, state&ODS_SELECTED,
                        state&ODS_CHECKED ? info.hbmpChecked :
                        info.hbmpUnchecked);
      }
    }

    //This is needed always so that we can have the space for check marks

    x0=rect.left;y0=rect.top;
    rect.left = rect.left + m_iconX + 8 + GAP; 

    if(!strText.IsEmpty()){

      CRect rectt(rect.left,rect.top-1,rect.right,rect.bottom-1);

      //   Find tabs

      CString leftStr,rightStr;
      leftStr.Empty();rightStr.Empty();
      int tablocr=strText.ReverseFind(_T('\t'));
      if(tablocr!=-1){
        rightStr=strText.Mid(tablocr+1);
        leftStr=strText.Left(strText.Find(_T('\t')));
        rectt.right-=m_iconX;
      }
      else leftStr=strText;

      int iOldMode = pDC->GetBkMode();
      pDC->SetBkMode( TRANSPARENT);

      // Draw the text in the correct colour:

      UINT nFormat  = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;
      if(!(lpDIS->itemState & ODS_GRAYED)){
        pDC->SetTextColor(crText);
        pDC->DrawText (leftStr,rectt,nFormat);
        if(tablocr!=-1) pDC->DrawText (rightStr,rectt,nFormatr);
      }
      else{

        // Draw the disabled text
        if(!(state & ODS_SELECTED)){
          RECT offset = *rectt;
          offset.left+=1;
          offset.right+=1;
          offset.top+=1;
          offset.bottom+=1;
          pDC->SetTextColor(GetSysColor(COLOR_BTNHILIGHT));
          pDC->DrawText(leftStr,&offset, nFormat);
          if(tablocr!=-1) pDC->DrawText (rightStr,&offset,nFormatr);
          pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1) pDC->DrawText (rightStr,rectt,nFormatr);
        }
        else{
        // And the standard Grey text:
          pDC->SetTextColor(m_clrBack);
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1) pDC->DrawText (rightStr,rectt,nFormatr);
        }
      }
      pFont = pDC->SelectObject (&dispFont);
      pDC->SetBkMode( iOldMode );
      pDC->SelectObject (pFont); //set it to the old font
    }

    m_penBack.DeleteObject();
    m_brBackground.DeleteObject();
    m_fontMenu.DeleteObject();
    m_brSelect.DeleteObject();
    dispFont.DeleteObject ();
  }
}


/*
==========================================================================
void BCMenu::MeasureItem(LPMEASUREITEMSTRUCT)
---------------------------------------------

Called by the framework when it wants to know what the width and height
of our item will be.  To accomplish this we provide the width of the
icon plus the width of the menu text, and then the height of the icon.
 
==========================================================================
*/

void BCMenu::MeasureItem( LPMEASUREITEMSTRUCT lpMIS )
{
  UINT state = (((BCMenuData*)(lpMIS->itemData))->nFlags);
  if(state & MF_SEPARATOR){
    lpMIS->itemWidth = 0;
    lpMIS->itemHeight = GetSystemMetrics(SM_CYMENU)>>1;
  }
  else{
    CFont m_fontMenu;
    LOGFONT m_lf;
    ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
    NONCLIENTMETRICS nm;
    nm.cbSize = sizeof (NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
           nm.cbSize,&nm,0)); 
    m_lf =  nm.lfMenuFont;
    m_fontMenu.CreateFontIndirect (&m_lf);

    // Obtain the width of the text:
    CWnd *pWnd = AfxGetMainWnd();            // Get main window
    CDC *pDC = pWnd->GetDC();              // Get device context
    CFont* pFont;    // Select menu font in...
    
    if (Windoze95==g_Shell || WinNT4orHigher==g_Shell)
        pFont = pDC->SelectObject (&m_fontMenu);// Select menu font in...
        
    //Get pointer to text SK
    wchar_t *lpstrText = ((BCMenuData*)(lpMIS->itemData))->menuText;
    
    SIZE size;

    if (Win32s!=g_Shell)
      VERIFY(::GetTextExtentPoint32W(pDC->m_hDC,lpstrText,
             wcslen(lpstrText),&size)); //SK should also work on 95
#ifndef UNICODE //can't be UNICODE for Win32s
    else{//it's Win32suckx
      RECT rect;
      rect.left=rect.top=0;
      size.cy=DrawText(pDC->m_hDC,(LPCTSTR)lpstrText,
                       wcslen(lpstrText),&rect,
                       DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
      //+3 makes at least three pixels space to the menu border
      size.cx=rect.right-rect.left+3;
      size.cx += 3*(size.cx/wcslen(lpstrText));
    }
#endif    

    CSize t = CSize(size);
    if(Windoze95==g_Shell || WinNT4orHigher==g_Shell)
      pDC->SelectObject (pFont);  // Select old font in
    AfxGetApp()->m_pMainWnd->ReleaseDC (pDC); // Release the DC

    // Set width and height:

    lpMIS->itemWidth = m_iconX + t.cx + m_iconX + GAP;
    int temp = GetSystemMetrics(SM_CYMENU);
    lpMIS->itemHeight = temp>m_iconY+4 ? temp : m_iconY+4;
    m_fontMenu.DeleteObject();
  }
}

void BCMenu::SetIconSize (int width, int height)
{
  m_iconX = width;
  m_iconY = height;
}

BOOL BCMenu::AppendODMenuA(LPCSTR lpstrText,UINT nFlags,UINT nID,
                           int nIconNormal)
{
  ASSERT(lpstrText);
  int iBufSize=(CPInfo.MaxCharSize==1)?strlen(lpstrText):
                _mbstrlen(lpstrText);
  iBufSize++;//Increment for the terminating NULL 
  wchar_t *szText=new wchar_t[iBufSize];

  VERIFY(MultiByteToWideChar(
    CP_ACP,     // code page 
    MB_PRECOMPOSED,     // character-type options 
    lpstrText,  // address of string to map 
    -1, // number of characters in string 
    szText,     // address of wide-character buffer 
    iBufSize*sizeof(wchar_t)// size of buffer 
   ));
  BOOL bRetVal=AppendODMenuW(szText,nFlags,nID,nIconNormal);
  delete[] szText;
  return bRetVal;
}


BOOL BCMenu::AppendODMenuW(wchar_t *lpstrText,UINT nFlags,UINT nID,
                           int nIconNormal)
{
  // Add the MF_OWNERDRAW flag if not specified:
  ASSERT(lpstrText);
  if(!nID)nFlags=MF_SEPARATOR|MF_OWNERDRAW;
  else if(!(nFlags & MF_OWNERDRAW))nFlags |= MF_OWNERDRAW;

  BCMenuData *mdata = new BCMenuData;
  m_MenuList.Add(mdata);
  wcscpy(mdata->menuText, lpstrText);
  
  int iBufSize=wcslen(lpstrText)+1;
  char *szTemp=new char[iBufSize*sizeof(wchar_t)];

  if (*lpstrText){
    VERIFY(WideCharToMultiByte(
            CP_ACP,     // code page 
            0,  // performance and mapping flags 
            lpstrText,  // address of wide-character string 
            -1, // number of characters in string 
            szTemp,     // address of buffer for new string 
            iBufSize*sizeof(wchar_t),   // size of buffer 
            NULL,       // address of default for unmappable characters  
            NULL        // address of flag set when default char. used 
            ));
  }
  else  szTemp[0]=0x00;
    
  delete[] szTemp;  
  
  mdata->menuIconNormal = nIconNormal;
  mdata->xoffset=-1;
  if(nIconNormal>=0){
    mdata->xoffset=0;
    LoadFromToolBar(nID,nIconNormal,mdata->xoffset);
    if(mdata->bitmap)mdata->bitmap->DeleteImageList();
    else mdata->bitmap=new(CImageList);
    mdata->bitmap->Create(m_iconX,m_iconY,TRUE,1,1);
    AddBitmapToImageList(mdata->bitmap,nIconNormal);
  }
  mdata->nFlags = nFlags;
  mdata->nID = nID;
  return(CMenu::AppendMenu(nFlags, nID, (LPCTSTR)mdata));
}


BOOL BCMenu::ModifyODMenuA(const char * lpstrText,UINT nID,int nIconNormal)
{
  BOOL bRetVal;
  wchar_t *szText=NULL;
  if (lpstrText){
    int iBufSize=(CPInfo.MaxCharSize==1)?strlen(lpstrText):
                 _mbstrlen(lpstrText);
    iBufSize++;//Increment for the terminating NULL 
    szText=new wchar_t[iBufSize];

    VERIFY(MultiByteToWideChar(
        CP_ACP, // code page 
        MB_PRECOMPOSED, // character-type options 
        lpstrText,      // address of string to map 
        -1,     // number of characters in string 
        szText, // address of wide-character buffer 
        iBufSize*sizeof(wchar_t)// size of buffer 
    ));
  }
  bRetVal=ModifyODMenuW(szText,nID,nIconNormal);

  delete[] szText;
  return bRetVal;
}

BOOL BCMenu::ModifyODMenuW(wchar_t *lpstrText,UINT nID,int nIconNormal)
{
  int nLoc;
  BCMenuData *mdata;

  // Find the old BCMenuData structure:
  BCMenu *psubmenu = FindMenuOption(nID,nLoc);
  if(psubmenu && nLoc>=0)mdata = psubmenu->m_MenuList[nLoc];
  else{
  // Create a new BCMenuData structure:
    mdata = new BCMenuData;
    m_MenuList.Add(mdata);
  }
  ASSERT(mdata);
  if(lpstrText)
    wcscpy(mdata->menuText, lpstrText);
  mdata->menuIconNormal = nIconNormal;
  mdata->xoffset=-1;
  if(nIconNormal>=0){
    mdata->xoffset=0;
    LoadFromToolBar(nID,nIconNormal,mdata->xoffset);
    if(mdata->bitmap)mdata->bitmap->DeleteImageList();
    else mdata->bitmap=new(CImageList);
    mdata->bitmap->Create(m_iconX,m_iconY,TRUE,1,1);
    AddBitmapToImageList(mdata->bitmap,nIconNormal);
  }
  mdata->nFlags = MF_BYCOMMAND | MF_OWNERDRAW;
  mdata->nID = nID;
  return (CMenu::ModifyMenu(nID,mdata->nFlags,nID,(LPCTSTR)mdata));
}


BOOL BCMenu::ModifyODMenuA(const char *lpstrText,const char *OptionText,
                           int nIconNormal)
{
  BOOL bRetVal;
  wchar_t *szText=NULL;
  wchar_t *szOptionText=NULL;
  int iBufSize;
  if(lpstrText){
   
    iBufSize=(CPInfo.MaxCharSize==1)?strlen(lpstrText):
             _mbstrlen(lpstrText);
    iBufSize++;//Increment for the terminating NULL 
    szText=new wchar_t[iBufSize];

    VERIFY(MultiByteToWideChar(
        CP_ACP, // code page 
        MB_PRECOMPOSED, // character-type options 
        lpstrText,      // address of string to map 
        -1,     // number of characters in string 
        szText, // address of wide-character buffer 
        iBufSize*sizeof(wchar_t)// size of buffer 
    ));
  }

  if(OptionText){
    iBufSize=(CPInfo.MaxCharSize==1)?strlen(OptionText):
             _mbstrlen(OptionText);
    iBufSize++;//Increment for the terminating NULL 
    szOptionText=new wchar_t[iBufSize];

    VERIFY(MultiByteToWideChar(
        CP_ACP, // code page 
        MB_PRECOMPOSED, // character-type options 
        OptionText,     // address of string to map 
        -1,     // number of characters in string 
        szOptionText,   // address of wide-character buffer 
        iBufSize*sizeof(wchar_t)// size of buffer 
        ));
  }


  bRetVal=ModifyODMenuW(szText,szOptionText,nIconNormal);
  delete[] szText;
  delete[] szOptionText;
  return bRetVal;
}


BOOL BCMenu::ModifyODMenuW(wchar_t *lpstrText,wchar_t *OptionText,
                           int nIconNormal)
{
  BCMenuData *mdata;

  // Find the old BCMenuData structure:
  mdata=FindMenuOption(OptionText);
  if(mdata){
    if(lpstrText)wcscpy(mdata->menuText, lpstrText);
    mdata->menuIconNormal = nIconNormal;
    mdata->xoffset=-1;
    if(nIconNormal>=0){
      mdata->xoffset=0;
      if(mdata->bitmap)mdata->bitmap->DeleteImageList();
      else mdata->bitmap=new(CImageList);
      mdata->bitmap->Create(m_iconX,m_iconY,TRUE,1,1);
      AddBitmapToImageList(mdata->bitmap,nIconNormal);
    }
    return(TRUE);
  }
  return(FALSE);
}

BCMenuData *BCMenu::NewODMenu(UINT pos,UINT nFlags,UINT nID,CString string)
{
  BCMenuData *mdata;

  mdata = new BCMenuData;
  mdata->menuIconNormal = -1;
  mdata->xoffset=-1;
  #ifdef UNICODE
  wcscpy(mdata->menuText,string);//SK
  #else
  mdata->SetAnsiString(string);
  #endif
  mdata->nFlags = nFlags;
  mdata->nID = nID;
  
  
  if (nFlags&MF_OWNERDRAW){
    ASSERT(!(nFlags&MF_STRING));
    ModifyMenu(pos,nFlags,nID,(LPCTSTR)mdata);
  }
  else if (nFlags&MF_STRING){
    ASSERT(!(nFlags&MF_OWNERDRAW));
    ModifyMenu(pos,nFlags,nID,mdata->GetString());
  }
  else{
    ASSERT(nFlags&MF_SEPARATOR);
    ModifyMenu(pos,nFlags,nID);
  }

  return(mdata);
};

BOOL BCMenu::LoadToolbars(const UINT *arID,int n)
{
  ASSERT(arID);
  BOOL bRet=TRUE;
  for(int i=0;i<n;++i)
    bRet |= LoadToolbar(arID[i]);
  return(bRet);
}

BOOL BCMenu::LoadToolbar(UINT nToolBar)
{
  UINT nID;
  BOOL returnflag=FALSE;
  CToolBar bar;

  bar.Create(AfxGetMainWnd());
  if(bar.LoadToolBar(nToolBar)){
    for(int i=0;i<bar.GetCount();++i){
      nID = bar.GetItemID(i); 
      if(nID && GetMenuState(nID, MF_BYCOMMAND)
        !=0xFFFFFFFF)ModifyODMenu(NULL,nID,nToolBar);
    }
    returnflag=TRUE;
  }
  return(returnflag);
}

BOOL BCMenu::LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset)
{
  int xset,offset;
  UINT nStyle;
  BOOL returnflag=FALSE;
  CToolBar bar;

  bar.Create(AfxGetMainWnd());
  if(bar.LoadToolBar(nToolBar)){
    offset=bar.CommandToIndex(nID);
    if(offset>=0){
      bar.GetButtonInfo(offset,nID,nStyle,xset);
      if(xset>0)xoffset=xset;
      returnflag=TRUE;
    }
  }
  return(returnflag);
}

BCMenu *BCMenu::FindMenuOption(int nId,int& nLoc)
{
  int i;
  BCMenu *psubmenu,*pgoodmenu;

  for(i=0;i<(int)(GetMenuItemCount());++i){
#ifdef _CPPRTTI 
    psubmenu=dynamic_cast<BCMenu *>(GetSubMenu(i));
#else
    psubmenu=(BCMenu *)GetSubMenu(i);
#endif
    if(psubmenu){
      pgoodmenu=psubmenu->FindMenuOption(nId,nLoc);
      if(pgoodmenu)return(pgoodmenu);
    }
    else if(nId==(int)GetMenuItemID(i)){
      nLoc=i;
      return(this);
    }
  }
  nLoc = -1;
  return(NULL);
}

BCMenuData *BCMenu::FindMenuOption(wchar_t *lpstrText)
{
  int i;
  BCMenu *psubmenu;
  BCMenuData *pmenulist;

  for(i=0;i<(int)(GetMenuItemCount());++i){
#ifdef _CPPRTTI 
    psubmenu=dynamic_cast<BCMenu *>(GetSubMenu(i));
#else
    psubmenu=(BCMenu *)GetSubMenu(i);
#endif
    if(psubmenu){
      pmenulist=psubmenu->FindMenuOption(lpstrText);
      if(pmenulist)return(pmenulist);
    }
    else{
      for(i=0;i<=m_MenuList.GetUpperBound();++i){     
        if(!wcscmp(lpstrText,m_MenuList[i]->menuText))
          return(m_MenuList[i]);
      }
    }
  }
  return(NULL);
}


BOOL BCMenu::LoadMenu(int nResource)
{
  return(BCMenu::LoadMenu(MAKEINTRESOURCE(nResource)));
};

BOOL BCMenu::LoadMenu(LPCTSTR lpszResourceName)
{
  TRACE(_T(
    "IMPORTANT:Use BCMenu::DestroyMenu to destroy Loaded Menu's\n"));
  ASSERT_VALID(this);
  ASSERT(lpszResourceName != NULL);

  // Find the Menu Resource:
  HINSTANCE m_hInst = AfxFindResourceHandle(lpszResourceName,RT_MENU);
  HRSRC hRsrc = ::FindResource(m_hInst,lpszResourceName,RT_MENU);
  if(hRsrc == NULL)return FALSE;

  // Get size of resource:

  DWORD dwSize = SizeofResource(NULL, hRsrc);

  // Load the Menu Resource:

  HGLOBAL hGlobal = LoadResource(m_hInst, hRsrc);
  if(hGlobal == NULL)return FALSE;

  // Attempt to create us as a menu...

  if(!CMenu::CreateMenu())return FALSE;

  // Get Item template Header, and calculate offset of MENUITEMTEMPLATES

  MENUITEMTEMPLATEHEADER *pTpHdr=
    (MENUITEMTEMPLATEHEADER*)LockResource(hGlobal);
  BYTE* pTp=(BYTE*)pTpHdr + 
    (sizeof(MENUITEMTEMPLATEHEADER) + pTpHdr->offset);


  // Variables needed during processing of Menu Item Templates:

  int j=0;
  BCMenuData*  pData = NULL;              // New OD Menu Item Data
  WORD    dwFlags = 0;              // Flags of the Menu Item
  WORD    dwID  = 0;              // ID of the Menu Item
  UINT    uFlags;                  // Actual Flags.
  wchar_t *szCaption=NULL;
  int      nLen   = 0;                // Length of caption
  CTypedPtrArray<CPtrArray, BCMenu*>  m_Stack;    // Popup menu stack
  CArray<BOOL,BOOL>  m_StackEnd;    // Popup menu stack
  m_Stack.Add(this);                  // Add it to this...
  m_StackEnd.Add(FALSE);

  do{
    // Obtain Flags and (if necessary), the ID...
    memcpy(&dwFlags, pTp, sizeof(WORD));pTp+=sizeof(WORD);// Obtain Flags
    if(!(dwFlags & MF_POPUP)){
      memcpy(&dwID, pTp, sizeof(WORD)); // Obtain ID
      pTp+=sizeof(WORD);
    }
    else dwID = 0;

    uFlags = (UINT)dwFlags; // Remove MF_END from the flags that will
    if(uFlags & MF_END) // be passed to the Append(OD)Menu functions.
      uFlags -= MF_END;

    // Obtain Caption (and length)

    nLen = 0;
    char *ch = (char*)pTp;
    szCaption=new wchar_t[wcslen((wchar_t *)pTp)+1];
    wcscpy(szCaption,(wchar_t *)pTp);
    pTp=&pTp[(wcslen((wchar_t *)pTp)+1)*sizeof(wchar_t)];//modified SK
    
    // Handle popup menus first....

    //WideCharToMultiByte
    if(dwFlags & MF_POPUP){
      if(dwFlags & MF_END)m_StackEnd.SetAt(m_Stack.GetUpperBound(),TRUE);
      BCMenu* pSubMenu = new BCMenu;
      pSubMenu->m_unselectcheck=m_unselectcheck;
      pSubMenu->m_selectcheck=m_selectcheck;
      pSubMenu->checkmaps=checkmaps;
      pSubMenu->checkmapsshare=TRUE;
      pSubMenu->CreatePopupMenu();

      // Append it to the top of the stack:

      m_Stack[m_Stack.GetUpperBound()]->AppendODMenuW(szCaption,uFlags,
        (UINT)pSubMenu->m_hMenu, -1);
      m_Stack.Add(pSubMenu);
      m_StackEnd.Add(FALSE);
      m_SubMenus.Add(pSubMenu);
    }
    else {
      m_Stack[m_Stack.GetUpperBound()]->AppendODMenuW(szCaption, uFlags,
        dwID, -1);
      if(dwFlags & MF_END)m_StackEnd.SetAt(m_Stack.GetUpperBound(),TRUE);
      j = m_Stack.GetUpperBound();
      while(j>=0 && m_StackEnd.GetAt(j)){
        m_Stack[m_Stack.GetUpperBound()]->InsertSpaces();
        m_Stack.RemoveAt(j);
        m_StackEnd.RemoveAt(j);
        --j;
      }
    }

    delete[] szCaption;
  }while(m_Stack.GetUpperBound() != -1);

  for(int i=0;i<(int)GetMenuItemCount();++i){
    CString str=m_MenuList[i]->GetString();

    if(GetSubMenu(i)){
      m_MenuList[i]->nFlags=MF_POPUP|MF_BYPOSITION;
      ModifyMenu(i,MF_POPUP|MF_BYPOSITION,
        (UINT)GetSubMenu(i)->m_hMenu,str);
    }
    else{
      m_MenuList[i]->nFlags=MF_STRING|MF_BYPOSITION;
      ModifyMenu(i,MF_STRING|MF_BYPOSITION,m_MenuList[i]->nID,str);
    }
  }
  
  return(TRUE);
}

void BCMenu::InsertSpaces(void)
{
  int i,j,numitems,maxlength;
  CString string,newstring;
  CSize t;
  CFont m_fontMenu;
  LOGFONT m_lf;

  ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
  NONCLIENTMETRICS nm;
  nm.cbSize = sizeof (NONCLIENTMETRICS);
  VERIFY (SystemParametersInfo (SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
  m_lf =  nm.lfMenuFont;
  m_fontMenu.CreateFontIndirect (&m_lf);

  CWnd *pWnd = AfxGetMainWnd();  
  CDC *pDC = pWnd->GetDC();
  CFont* pFont = pDC->SelectObject (&m_fontMenu);
  
  numitems=GetMenuItemCount();
  maxlength = -1;
  for(i=0;i<numitems;++i){
    string=m_MenuList[i]->GetString();
    j=string.Find((char)9);
    newstring.Empty();
    if(j!=-1)newstring.Left(j);
    else newstring=string;
    newstring+=" ";
    LPCTSTR lpstrText = (LPCTSTR)newstring;
    t=pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
    if(t.cx>maxlength)maxlength = t.cx;
  }
  for(i=0;i<numitems;++i){
    string=m_MenuList[i]->GetString();

    j=string.Find((char)9);
    if(j!=-1){
      newstring.Empty();
      newstring=string.Left(j);
      LPCTSTR lpstrText = (LPCTSTR)(newstring);
      t=pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
      while(t.cx<maxlength){
        newstring+=' ';
        LPCTSTR lpstrText = (LPCTSTR)(newstring);
        t=pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
      }
      newstring+=string.Mid(j);
#ifdef UNICODE      
      wcscpy(m_MenuList[i]->menuText,newstring);
#else
      m_MenuList[i]->SetAnsiString(newstring);
#endif
    }
  }
  pDC->SelectObject (pFont);              // Select old font in
  AfxGetApp()->m_pMainWnd->ReleaseDC (pDC);      // Release the DC
  m_fontMenu.DeleteObject();
}

void BCMenu::LoadCheckmarkBitmap(int unselect, int select)
{
  if(unselect>=0 && select>=0){
    m_selectcheck=select;
    m_unselectcheck=unselect;
    if(checkmaps)checkmaps->DeleteImageList();
    else checkmaps=new(CImageList);
    checkmaps->Create(m_iconX,m_iconY,TRUE,2,1);
    AddBitmapToImageList(checkmaps,unselect);
    AddBitmapToImageList(checkmaps,select);
  }
}

BOOL BCMenu::GetMenuText(UINT id, CString& string)
{
  BOOL returnflag=FALSE;

  UINT numMenuItems = m_MenuList.GetUpperBound();
  if(id<=numMenuItems){
    string=m_MenuList[id]->GetString();
    returnflag=TRUE;
  }
  return(returnflag);
}

void BCMenu::DrawRadioDot(CDC *pDC,int x,int y,COLORREF color)
{
  CRect rcDot(x,y,x+6,y+6);
  CBrush brush;
  CPen pen;
  brush.CreateSolidBrush(color);
  pen.CreatePen(PS_SOLID,0,color);
  pDC->SelectObject(&brush);
  pDC->SelectObject(&pen);
  pDC->Ellipse(&rcDot);
  pen.DeleteObject();
  brush.DeleteObject();
}

void BCMenu::DrawCheckMark(CDC* pDC,int x,int y,COLORREF color)
{
  pDC->SetPixel(x,y+2,color);
  pDC->SetPixel(x,y+3,color);
  pDC->SetPixel(x,y+4,color);

  pDC->SetPixel(x+1,y+3,color);
  pDC->SetPixel(x+1,y+4,color);
  pDC->SetPixel(x+1,y+5,color);

  pDC->SetPixel(x+2,y+4,color);
  pDC->SetPixel(x+2,y+5,color);
  pDC->SetPixel(x+2,y+6,color);

  pDC->SetPixel(x+3,y+3,color);
  pDC->SetPixel(x+3,y+4,color);
  pDC->SetPixel(x+3,y+5,color);

  pDC->SetPixel(x+4,y+2,color);
  pDC->SetPixel(x+4,y+3,color);
  pDC->SetPixel(x+4,y+4,color);

  pDC->SetPixel(x+5,y+1,color);
  pDC->SetPixel(x+5,y+2,color);
  pDC->SetPixel(x+5,y+3,color);

  pDC->SetPixel(x+6,y,color);
  pDC->SetPixel(x+6,y+1,color);
  pDC->SetPixel(x+6,y+2,color);
}

BCMenuData *BCMenu::FindMenuList(UINT nID)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i){
    if(m_MenuList[i]->nID==nID && !m_MenuList[i]->syncflag){
      m_MenuList[i]->syncflag=1;
      return(m_MenuList[i]);
    }
  }
  return(NULL);
}

void BCMenu::InitializeMenuList(int value)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i)
    m_MenuList[i]->syncflag=value;
}

void BCMenu::DeleteMenuList(void)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i){
    if(!m_MenuList[i]->syncflag){
      delete m_MenuList[i];
    }
  }
}

void BCMenu::SynchronizeMenu(void)
{
  CTypedPtrArray<CPtrArray, BCMenuData*> temp;
  BCMenuData *mdata;
  CString string;
  UINT submenu,nID,state,j;

  InitializeMenuList(0);
  for(j=0;j<GetMenuItemCount();++j){
    mdata=NULL;
    state=GetMenuState(j,MF_BYPOSITION);
    if(state&MF_POPUP){
      submenu=(UINT)GetSubMenu(j)->m_hMenu;
      mdata=FindMenuList(submenu);
      GetMenuString(j,string,MF_BYPOSITION);
      if(!mdata)mdata=NewODMenu(j,
        state|MF_BYPOSITION|MF_POPUP|MF_OWNERDRAW,submenu,string);
      else if(string.GetLength()>0)
#ifdef UNICODE
        wcscpy(mdata->menuText,string);//SK
#else
        mdata->SetAnsiString(string);
#endif
    }
    else if(state&MF_SEPARATOR){
      mdata=FindMenuList(0);
      if(!mdata)mdata=NewODMenu(j,
        state|MF_BYPOSITION|MF_SEPARATOR|MF_OWNERDRAW,0,"");
      else ModifyMenu(j,mdata->nFlags,nID,(LPCTSTR)mdata);
    }
    else{
      nID=GetMenuItemID(j);
      mdata=FindMenuList(nID);
      GetMenuString(j,string,MF_BYPOSITION);
      if(!mdata)mdata=NewODMenu(j,state|MF_BYPOSITION|MF_OWNERDRAW,
        nID,string);
      else{
        mdata->nFlags=state|MF_BYPOSITION|MF_OWNERDRAW;
        if(string.GetLength()>0)
#ifdef UNICODE
            wcscpy(mdata->menuText,string);//SK
#else
            mdata->SetAnsiString(string);
#endif
            
        ModifyMenu(j,mdata->nFlags,nID,(LPCTSTR)mdata);
      }
    }
    if(mdata)temp.Add(mdata);
  }
  DeleteMenuList();
  m_MenuList.RemoveAll();
  m_MenuList.Append(temp);
  temp.RemoveAll(); 
}

void BCMenu::UpdateMenu(CMenu *pmenu)
{
#ifdef _CPPRTTI 
  BCMenu *psubmenu = dynamic_cast<BCMenu *>(pmenu);
#else
  BCMenu *psubmenu = (BCMenu *)pmenu;
#endif
  if(psubmenu)psubmenu->SynchronizeMenu();
}

LRESULT BCMenu::FindKeyboardShortcut(UINT nChar, UINT nFlags,
                                     CMenu *pMenu)
{
#ifdef _CPPRTTI 
  BCMenu *pBCMenu = dynamic_cast<BCMenu *>(pMenu);
#else
  BCMenu *pBCMenu = (BCMenu *)pMenu;
#endif
  if(pBCMenu && nFlags&MF_POPUP){
    CString key('&',2);
    key.SetAt(1,(TCHAR)nChar);
    key.MakeLower();
    CString menutext;
    int menusize = (int)pBCMenu->GetMenuItemCount();
    if(menusize!=(pBCMenu->m_MenuList.GetUpperBound()+1))
      pBCMenu->SynchronizeMenu();
    for(int i=0;i<menusize;++i){
      if(pBCMenu->GetMenuText(i,menutext)){
        menutext.MakeLower();
        if(menutext.Find(key)>=0)return(MAKELRESULT(i,2));
      }
    }
  }
  return(0);
}

void BCMenu::DitherBlt (HDC hdcDest, int nXDest, int nYDest, int nWidth, 
                        int nHeight, HBITMAP hbm, int nXSrc, int nYSrc)
{
  ASSERT(hdcDest && hbm);
  ASSERT(nWidth > 0 && nHeight > 0);
  
  // Create a generic DC for all BitBlts
  HDC hDC = CreateCompatibleDC(hdcDest);
  ASSERT(hDC);
  
  if (hDC)
  {
    // Create a DC for the monochrome DIB section
    HDC bwDC = CreateCompatibleDC(hDC);
    ASSERT(bwDC);
    
    if (bwDC)
    {
      // Create the monochrome DIB section with a black and white palette
      struct {
        BITMAPINFOHEADER bmiHeader; 
        RGBQUAD      bmiColors[2]; 
      } RGBBWBITMAPINFO = {
        
        {    // a BITMAPINFOHEADER
          sizeof(BITMAPINFOHEADER),  // biSize 
            nWidth,         // biWidth; 
            nHeight,        // biHeight; 
            1,            // biPlanes; 
            1,            // biBitCount 
            BI_RGB,         // biCompression; 
            0,            // biSizeImage; 
            0,            // biXPelsPerMeter; 
            0,            // biYPelsPerMeter; 
            0,            // biClrUsed; 
            0            // biClrImportant; 
        },    
        {
          { 0x00, 0x00, 0x00, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }
        } 
      };
      VOID *pbitsBW;
      HBITMAP hbmBW = CreateDIBSection(bwDC,
        (LPBITMAPINFO)&RGBBWBITMAPINFO, DIB_RGB_COLORS, &pbitsBW, NULL, 0);
      ASSERT(hbmBW);
      
      if (hbmBW)
      {
        // Attach the monochrome DIB section and the bitmap to the DCs
        HBITMAP olddib = (HBITMAP)SelectObject(bwDC, hbmBW);
        SelectObject(hDC, hbm);
        
        // BitBlt the bitmap into the monochrome DIB section
        BitBlt(bwDC, 0, 0, nWidth, nHeight, hDC, nXSrc, nYSrc, SRCCOPY);
        
        // Paint the destination rectangle in gray
        FillRect(hdcDest, CRect(nXDest, nYDest, nXDest + nWidth, nYDest +
          nHeight), GetSysColorBrush(COLOR_3DFACE));
        
        // BitBlt the black bits in the monochrome bitmap into COLOR_3DHILIGHT
        // bits in the destination DC
        // The magic ROP comes from the Charles Petzold's book
        HBRUSH hb = CreateSolidBrush(GetSysColor(COLOR_3DHILIGHT));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdcDest, hb);
        BitBlt(hdcDest,nXDest+1,nYDest+1,nWidth,nHeight,bwDC,0,0,0xB8074A);
        
        // BitBlt the black bits in the monochrome bitmap into COLOR_3DSHADOW
        // bits in the destination DC
        hb = CreateSolidBrush(GetSysColor(COLOR_3DSHADOW));
        DeleteObject(SelectObject(hdcDest, hb));
        BitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight,bwDC,0,0,0xB8074A);
        DeleteObject(SelectObject(hdcDest, oldBrush));
        VERIFY(DeleteObject(SelectObject(bwDC, olddib)));
      }
      
      VERIFY(DeleteDC(bwDC));
    }
    
    VERIFY(DeleteDC(hDC));
  }
}

int BCMenu::AddBitmapToImageList(CImageList *bmplist,UINT nResourceID)
{
  int bReturn;

  HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nResourceID),RT_BITMAP);
  HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(nResourceID),RT_BITMAP);
  if(hRsrc){
    HBITMAP hbmp = AfxLoadSysColorBitmap(hInst,hRsrc,FALSE);
    CBitmap bmp;
    bmp.Attach(hbmp);
    if(m_bitmapBackgroundFlag) bReturn=bmplist->Add(&bmp,m_bitmapBackground);
    else bReturn=bmplist->Add(&bmp,GetSysColor(COLOR_3DFACE));
    bmp.Detach();
  }
  else bReturn = -1;
  return(bReturn);
}

void BCMenu::SetBitmapBackground(COLORREF color)
{
  m_bitmapBackground=color;
  m_bitmapBackgroundFlag=TRUE;
}

void BCMenu::UnSetBitmapBackground(void)
{
  m_bitmapBackgroundFlag=FALSE;
}

// Given a toolbar, append all the options from it to this menu
// Passed a ptr to the toolbar object and the toolbar ID
// Author : Robert Edward Caldecott
void BCMenu::AddFromToolBar(CToolBar* pToolBar, int nResourceID)
{
  for (int i = 0; i < pToolBar->GetCount(); i++) {
    UINT nID = pToolBar->GetItemID(i);
    // See if this toolbar option
    // appears as a command on this
    // menu or is a separator
    if (nID == 0 || GetMenuState(nID, MF_BYCOMMAND) == 0xFFFFFFFF)
      continue; // Item doesn't exist
    UINT nStyle;
    int nImage;
    // Get the toolbar button info
    pToolBar->GetButtonInfo(i, nID, nStyle, nImage);
    // OK, we have the command ID of the toolbar
    // option, and the tollbar bitmap offset
    int nLoc;
    BCMenuData* pData;
    BCMenu *pSubMenu = FindMenuOption(nID, nLoc);
    if (pSubMenu && nLoc >= 0)pData = pSubMenu->m_MenuList[nLoc];
    else {
      // Create a new BCMenuData structure
      pData = new BCMenuData;
      m_MenuList.Add(pData);
    }
    // Set some default structure members
    pData->menuIconNormal = nResourceID;
    pData->nID = nID;
    pData->nFlags =  MF_BYCOMMAND | MF_OWNERDRAW;
    pData->xoffset = nImage;
    if (pData->bitmap)pData->bitmap->DeleteImageList();
    else pData->bitmap = new CImageList;
    pData->bitmap->Create(m_iconX, m_iconY, TRUE, 1, 1);
    AddBitmapToImageList(pData->bitmap, nResourceID);
    // Modify our menu
    ModifyMenu(nID,pData->nFlags,nID,(LPCTSTR)pData);
  }
}

BOOL BCMenu::Draw3DCheckmark(CDC *dc, const CRect& rc,
                             BOOL bSelected, HBITMAP hbmCheck)
{
  CRect rcDest = rc;
  CBrush brush;
  COLORREF col=GetSysColor(bSelected?COLOR_MENU:COLOR_3DLIGHT);
  brush.CreateSolidBrush(col);
  dc->FillRect(rcDest,&brush);
  brush.DeleteObject();
  dc->DrawEdge(&rcDest, BDR_SUNKENOUTER, BF_RECT);
  if (!hbmCheck)DrawCheckMark(dc,rc.left+4,rc.top+4,GetSysColor(COLOR_MENUTEXT));
  else DrawRadioDot(dc,rc.left+5,rc.top+4,GetSysColor(COLOR_MENUTEXT));
  return TRUE;
}

//*************************************************************************