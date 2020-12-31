/*
Module : MessageBoxX.CPP
Purpose: Implementation for a MFC wrapper class for the MessageBox API
Created: PJN / 18-04-2003
History: PJN / 24-04-2006 1. Updated copyright details.
                          2. UpdateCaptionDueToTimer method has been renamed to UpdateUIDueToTimer
                          3. Now includes support for including a check box on the MessageBox. To achieve this
                          simply call SetCheckBox with the text to show on the check box and its initial 
                          checked state prior to calling DoModal to show the message box. Then when DoModal
                          returns simple call GetCheckBoxState to determine whether the check box was ticked
                          or not.
                          4. Now includes support for right aligning buttons instead of the default for the 
                          MessageBox API which is to have the buttons centered. The support for checkboxes
                          and right aligned buttons is inspired by the GSMessageBox article at 
                          http://www.gipsysoft.com/messagebox/.
                          5. Both SetTimeout and SetDisabledButton methods now include a "bModifyCaptionDuringCountdown"
                          which determines if they should cause the MessageBox caption to be modified during their
                          timer countdowns
                          6. Updated the sample app to allow most of the functionality of the code to be optionally
                          tested.
                          7. SetTimeout method now includes a bResetTimeoutOnUserActivity parameter.
                          8. Addition of GetCurrentTimerCaption() and GetCurrentDisabledCaption() virtual methods
                          which allow the timeout and disabled captions to be easily customized at runtime.
                          9. Fixed a number of compiler warnings when the code is compiled using /Wp64
         PJN / 02-07-2006 1. Code now uses newer C++ style casts instead of C style casts.
                          2. Class now allows you to put HTML text into the message box. This is provided by the 
                          QHTM HTML control provided at http://www.gipsysoft.com/qhtm/. You may need to purchase a 
                          license (depending on the type of application you are developing) as well as follow their 
                          instructions on deploying it if you want this functionality with CMessageBoxX. This functionality 
                          by default is not included in CMessageBoxX and is only available when you define the 
                          preprocessor macro "CMESSAGEBOXX_HTML_SUPPORT".
.                         3. Implemented support for selectable text
                          4. Button captions can now be modified via SetModifiedButtonCaption.
                          5. Added user defined animated text support.
                          6. Added user defined animated caption support.
         PJN / 05-11-2006 1. Minor update to stdafx.h of sample app to avoid compiler warnings in VC 2005.
                          2. Code now uses QHTM const for the class name
         PJN / 11-08-2007 1. Updated copyright details.
                          2. Check box text control is now clipped to the width of the main text control if its calculated 
                          width will exceed the message box client area. This was done following a report from Kyle Alons 
                          that this text can get clipped on Vista when you pick a longish piece of text as the check box 
                          text. You should ensure you pick a shortish piece of text to avoid this problem as well as test 
                          all your message boxes on all the operating systems you will be supporting your application on.
                          3. Addition of a CMESSAGEBOXX_EXT_CLASS to allow the code to be more easily added to an 
                          extension dll.
         PJN / 11-07-2008 1. Updated copyright details.
                          2. Updated sample app to clean compile on VC 2008
                          3. Removed VC 6 style classwizard comments from the code.
                          4. The code has now been updated to support VC 2005 or later only. 
                          5. Code now compiles cleanly using Code Analysis (/analyze)
                          6. Code now uses newer C++ style casts instead of C style casts.
                          7. Updated sample app to demonstrate support for user icons
                          8. Class now correctly handles the manifest contexts which the MessageBox API's can have
                          when you are using Common Control v6 or later
                             
Copyright (c) 2003 - 2008 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


//////////////// Includes ////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MessageBoxX.h"
#ifndef __AFXPRIV_H__
#pragma message("To avoid this message, please put afxpriv.h in your pre compiled header (normally stdafx.h)")
#include <afxpriv.h>
#endif
#ifdef CMESSAGEBOXX_HTML_SUPPORT
#ifndef QHTM_H
#include <qhtm.h> //If you get a compilation error on this line, then you need to download, install and possible purchase a license for QHTM (http://www.gipsysoft.com/qhtm/)
#endif
#endif


//////////////// Macros / Defines ////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef MB_CANCELTRYCONTINUE
#define MB_CANCELTRYCONTINUE 0x00000006L
#endif

const UINT MESSAGEBOXX_HTML_ID = 100;
const UINT MESSAGEBOXX_EDIT_ID = 101;
const UINT_PTR MESSAGEBOXX_ANIMATED_TEXT_TIMER = 2;
const UINT_PTR MESSAGEBOXX_ANIMATED_CAPTION_TIMER = 3;
const UINT_PTR MESSAGEBOXX_TIMEOUT_DISABLED_TIMER = 4;


//////////////// Implementation //////////////////////////////////////

//Simple class to allow access to CWinApp::m_dwPromptContext
class CMessageBoxPublicWinApp : public CWinApp
{
public:
  DWORD* GetPromptContextAddress() { return &m_dwPromptContext; };
};

CMessageBoxX::CMessageBoxX()
{
  Initialize();
}

CMessageBoxX::CMessageBoxX(LPCTSTR lpszText, LPCTSTR lpszCaption, UINT nType, CWnd* pParent, UINT nIDHelp)
{
  SetText(lpszText, nIDHelp);
  SetCaption(lpszCaption);
  SetType(nType);
  SetParent(pParent);
  Initialize();
}

CMessageBoxX::CMessageBoxX(UINT nIDResource, LPCTSTR lpszCaption, UINT nType, CWnd* pParent, UINT nIDHelp)
{
	SetText(nIDResource, nIDHelp);
  SetCaption(lpszCaption);
  SetType(nType);
  SetParent(pParent);
  Initialize();
}

void CMessageBoxX::Initialize()
{
  m_dwTextAnimationInterval = 0;
  m_pAnimatedTexts = NULL;
  m_bAnimatedTextLoop = FALSE;
  m_nCurrentAnimatedTextIndex = 0;
  m_dwCaptionAnimationInterval = 0;
  m_pAnimatedCaptions = 0;
  m_bAnimatedCaptionLoop = FALSE;
  m_nCurrentAnimatedCaptionIndex = 0;
  m_pszIcon = NULL;
  m_hIconInstance = 0;
  m_nTimerTimeout = 0;
  m_nTimerButtonId = 0;
  m_nTimerCountdown = 0;
  m_nDisabledTimeout = 0;
  m_nDisabledButtonId = 0;
  m_nDisabledCountdown = 0;
  m_nTimeoutDisabledButtonTimerID = 0;
  m_nAnimatedTextTimerID = 0;
  m_nAnimatedCaptionTimerID = 0;
  m_bCheckBox = FALSE;
  m_bCheckBoxState = FALSE;
  m_bRightAlignButtons = FALSE;
  m_bModifyCaptionForTimerCountdown = TRUE;
  m_bModifyCaptionForDisabledCountdown = TRUE;
  m_bResetTimeoutOnUserActivity = FALSE;
  m_bSelectableText = FALSE;
#ifdef CMESSAGEBOXX_HTML_SUPPORT
  m_bHTML = FALSE;
#endif
}

CString CMessageBoxX::GetCurrentTimerCaption()
{
  //What will be the return value from this function
  CString sCaption;

  if (m_nTimerTimeout && (m_nTimerCountdown <= 10) && m_bModifyCaptionForTimerCountdown)
  {
    //By default we modify the caption with a countdown if there is less than 10 seconds to go before the timeout
    CString sSeconds;
    sSeconds.Format(_T("%d"), m_nTimerCountdown);

    CString sNewCaption;
    AfxFormatString2(sCaption, IDS_MESSAGEBOXX_TIMEOUT_CAPTION, m_sCaption, sSeconds);
  }
  else
    sCaption = m_sCaption; //No change required

  return sCaption;
}

CString CMessageBoxX::GetCurrentDisabledCaption()
{
  //What will be the return value from this function
  CString sCaption;

  if (m_nDisabledTimeout && m_bModifyCaptionForDisabledCountdown)
  {
    //By default we always modify the caption if we have a disabled button (derived classes of course are free
    //to modify this behaviour)
    CString sSeconds;
    sSeconds.Format(_T("%d"), m_nDisabledCountdown);

    AfxFormatString2(sCaption, IDS_MESSAGEBOXX_DISABLED_TIMEOUT_CAPTION, m_sCaption, sSeconds);
  }
  else
    sCaption = m_sCaption; //No Change required

  return sCaption;
}

BEGIN_MESSAGE_MAP(CMessageBoxX, CWnd)
  ON_WM_CREATE()
	ON_WM_TIMER()
  ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

int CMessageBoxX::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  //Unhook window creation
	AfxUnhookWindowCreate();

  //let the base class do its thing
	return CWnd::OnCreate(lpCreateStruct);
}

void CMessageBoxX::SetCaption(LPCTSTR lpszCaption)
{
  if (lpszCaption)
    m_sCaption = lpszCaption;
  else
  {
    ASSERT(AfxGetApp());
    m_sCaption = AfxGetApp()->m_pszAppName;
  }
}

void CMessageBoxX::SetCaption(UINT nIDResource)
{
	if (!m_sCaption.LoadString(nIDResource))
	{
		TRACE(_T("CMessageBoxX::SetCaption, Error: failed to load message box caption string 0x%04x.\n"),	nIDResource);
		ASSERT(FALSE);
	}
}

void CMessageBoxX::SetCaption(UINT nIDResource, LPCTSTR lpsz1)
{
  AfxFormatString1(m_sCaption, nIDResource, lpsz1);
}

void CMessageBoxX::SetCaption(UINT nIDResource, LPCTSTR lpsz1, LPCTSTR lpsz2)
{
  AfxFormatString2(m_sCaption, nIDResource, lpsz1, lpsz2);
}

void CMessageBoxX::SetText(LPCTSTR lpszText, UINT nIDHelp)
{
  m_sText = lpszText;
  m_nHelpIDPrompt = nIDHelp;
}

void CMessageBoxX::SetText(UINT nIDResource, UINT nIDHelp)
{
	if (!m_sText.LoadString(nIDResource))
	{
		TRACE(_T("CMessageBoxX::SetText, Error: failed to load message box prompt string 0x%04x.\n"), nIDResource);
		ASSERT(FALSE);
	}

  if (nIDHelp == static_cast<UINT>(-1))
    m_nHelpIDPrompt = nIDResource;
  else
    m_nHelpIDPrompt = nIDHelp;
}

void CMessageBoxX::SetText(UINT nIDResource, LPCTSTR lpsz1, UINT nIDHelp)
{
  AfxFormatString1(m_sText, nIDResource, lpsz1);

  if (nIDHelp == static_cast<UINT>(-1))
    m_nHelpIDPrompt = nIDResource;
  else
    m_nHelpIDPrompt = nIDHelp;
}

void CMessageBoxX::SetText(UINT nIDResource, LPCTSTR lpsz1, LPCTSTR lpsz2, UINT nIDHelp)
{
  AfxFormatString2(m_sText, nIDResource, lpsz1, lpsz2);

  if (nIDHelp == static_cast<UINT>(-1))
    m_nHelpIDPrompt = nIDResource;
  else
    m_nHelpIDPrompt = nIDHelp;
}

#ifdef CMESSAGEBOXX_HTML_SUPPORT
void CMessageBoxX::SetHTMLText(UINT nIDResource)
{
	if (!m_sHTMLText.LoadString(nIDResource))
	{
		TRACE(_T("CMessageBoxX::SetHTMLText, Error: failed to load message box prompt string 0x%04x.\n"), nIDResource);
		ASSERT(FALSE);
	}
}

void CMessageBoxX::SetHTMLText(UINT nIDResource, LPCTSTR lpsz1)
{
  AfxFormatString1(m_sHTMLText, nIDResource, lpsz1);
}

void CMessageBoxX::SetHTMLText(UINT nIDResource, LPCTSTR lpsz1, LPCTSTR lpsz2)
{
  AfxFormatString2(m_sHTMLText, nIDResource, lpsz1, lpsz2);
}
#endif

void CMessageBoxX::SetUserIcon(UINT nIDResource, HINSTANCE hInstance)
{
  //Pass the buck to the other function
  SetUserIcon(MAKEINTRESOURCE(nIDResource), hInstance);
}

void CMessageBoxX::SetSelectableText(BOOL bSelectableText) 
{ 
  m_bSelectableText = bSelectableText; 

#ifdef CMESSAGEBOXX_HTML_SUPPORT
  //Turning on HTML, means turning off selectable text
  if (m_bSelectableText)
    m_bHTML = FALSE;
#endif
}

#ifdef CMESSAGEBOXX_HTML_SUPPORT
void CMessageBoxX::SetHTML(BOOL bHTML) 
{ 
  m_bHTML = bHTML; 

  //Turning on HTML, means turning off selectable text
  if (m_bHTML)
    m_bSelectableText = FALSE;
}
#endif

void CMessageBoxX::SetModifiedButtonCaption(int nButtonIndex, LPCTSTR pszNewCaption)
{
  //Validate our parameters
  AFXASSUME(nButtonIndex >= 0 && nButtonIndex < sizeof(m_sModifiedButtonCaptions)/sizeof(CString));

  //Hive the value away
  m_sModifiedButtonCaptions[nButtonIndex] = pszNewCaption;
}

CString CMessageBoxX::GetModifiedButtonCaption(int nButtonIndex)
{
  //Validate our parameters
  AFXASSUME(nButtonIndex >= 0 && nButtonIndex < sizeof(m_sModifiedButtonCaptions)/sizeof(CString));

  return m_sModifiedButtonCaptions[nButtonIndex];
}

void CMessageBoxX::SetAnimatedText(DWORD dwAnimationInterval, const CStringArray* pTexts, BOOL bLoop)
{
  m_dwTextAnimationInterval = dwAnimationInterval;
  m_pAnimatedTexts = pTexts;
  m_bAnimatedTextLoop = bLoop;

  m_nCurrentAnimatedTextIndex = 0; //Reset the index value
  if (pTexts) //Set the initial text to the first item in the array
  {
    SetText(pTexts->GetAt(0)); 
  #ifdef CMESSAGEBOXX_HTML_SUPPORT
    SetHTMLText(m_sText); //Also update the HTML for consistency
  #endif
  }
}

void CMessageBoxX::SetAnimatedCaption(DWORD dwAnimationInterval, const CStringArray* pCaptions, BOOL bLoop)
{
  m_dwCaptionAnimationInterval = dwAnimationInterval;
  m_pAnimatedCaptions = pCaptions;
  m_bAnimatedCaptionLoop = bLoop;
  m_nCurrentAnimatedCaptionIndex = 0; //Reset the index value
  if (pCaptions) //Set the initial caption to the first item in the array
    SetCaption(pCaptions->GetAt(0)); 
}

void CMessageBoxX::SetUserIcon(LPCTSTR lpszResourceName, HINSTANCE hInstance)
{
  m_pszIcon = lpszResourceName;
  m_hIconInstance = hInstance;
  m_nType |= MB_USERICON;
}

void CMessageBoxX::SetParent(CWnd* pParent)
{
  if (pParent)
    m_hParentWnd = pParent->GetSafeHwnd();
  else
    m_hParentWnd = NULL;
}

void CMessageBoxX::SetParent(HWND hParent)
{
  m_hParentWnd = hParent;
}

void CMessageBoxX::SetType(UINT nType)
{
  m_nType = nType;
}

void CMessageBoxX::SetTimeout(int nTimeout, int nTimeoutButtonId, BOOL bModifyCaptionDuringCountdown, BOOL bResetTimeoutOnUserActivity)
{
  m_nTimerTimeout = nTimeout;
  m_nTimerButtonId = nTimeoutButtonId;
  m_nTimerCountdown = m_nTimerTimeout;
  m_bModifyCaptionForTimerCountdown = bModifyCaptionDuringCountdown;
  m_bResetTimeoutOnUserActivity = bResetTimeoutOnUserActivity;
}

void CMessageBoxX::SetDisabledButton(int nTimeout, int nDisabledButtonId, BOOL bModifyCaptionDuringCountdown)
{
  m_nDisabledTimeout = nTimeout;
  m_nDisabledButtonId = nDisabledButtonId;
  m_nDisabledCountdown = nTimeout;
  m_bModifyCaptionForDisabledCountdown = bModifyCaptionDuringCountdown;
}

CSize CMessageBoxX::GetCheckBoxSize(CFont* pFont)
{
  //We need a device context to calculate the required size of the check box
  CDC* pDC = GetDC();

  //Get the size of the text
  CFont* pOldFont = pDC->SelectObject(pFont);
  CSize size = pDC->GetTextExtent(m_sCheckBoxText);
  pDC->SelectObject(pOldFont);

  //Add in the size of a check box plus some vertical space for a border above and below
  size.cx += GetSystemMetrics(SM_CXMENUCHECK) + 5;
  size.cy = max(size.cy, GetSystemMetrics(SM_CXMENUCHECK));
  
  ReleaseDC(pDC);

  return size;
}

void CMessageBoxX::SetCheckBox(BOOL bChecked, LPCTSTR lpszText)
{
  m_bCheckBox = TRUE;
  m_bCheckBoxState = bChecked;
  m_sCheckBoxText = lpszText;
}

void CMessageBoxX::SetRightAlignButtons(BOOL bRightAlign)
{
  m_bRightAlignButtons = bRightAlign;
}

CWnd* CMessageBoxX::FindTextControl()
{
	//Find the static control which houses the MessageBox text
	CWnd* pWndStatic = GetWindow(GW_CHILD);
	while (pWndStatic)
	{
		int nID = pWndStatic->GetDlgCtrlID();
		if (nID >= 0xFFFF)
			return pWndStatic;
		pWndStatic = pWndStatic->GetWindow(GW_HWNDNEXT);
	}

	return NULL;
}

CWnd* CMessageBoxX::FindOurTextControl()
{
#ifdef CMESSAGEBOXX_HTML_SUPPORT
  if (IsWindow(m_wndQHTM.GetSafeHwnd()))
    return &m_wndQHTM;
  else if (IsWindow(m_wndSelectableText.GetSafeHwnd()))
#else
  if (IsWindow(m_wndSelectableText.GetSafeHwnd()))
#endif
    return &m_wndSelectableText;
  else
    return FindTextControl();
}

CWnd* CMessageBoxX::GetFirstButton()
{
  //Find the first button on the message box
  static TCHAR* szButtonClass = _T("BUTTON");
  static TCHAR szTest[]      = _T("      "); //7 tchar's allocated buffer to hold the classname "BUTTON"

  CWnd* pChildWnd = GetWindow(GW_CHILD);
  while (pChildWnd)
  {
    if (GetClassName(pChildWnd->GetSafeHwnd(), szTest, sizeof(szTest)/sizeof(TCHAR)))
    {
      if (_tcsnicmp(szTest, szButtonClass, (sizeof(szTest)/sizeof(TCHAR)) - 1) == 0)
        return pChildWnd;
    }  

    pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
  }

  return NULL;
}

CRect CMessageBoxX::GetRightMostButtonRect()
{
  //What will be the return value from this function
  CRect rectButton;

  //Find the first most button
  static TCHAR* szButtonClass = _T("BUTTON");
  static TCHAR szTest[]      = _T("      "); //7 tchar's allocated buffer to hold the classname "BUTTON"

  CWnd* pChildWnd = GetWindow(GW_CHILD);
  int nRightMostXValue = INT_MIN;
  while (pChildWnd)
  {
    if (GetClassName(pChildWnd->GetSafeHwnd(), szTest, sizeof(szTest)/sizeof(TCHAR)))
    {
      if (_tcsnicmp(szTest, szButtonClass, (sizeof(szTest)/sizeof(TCHAR)) - 1) == 0)
      {
        CRect rectThisButton;
        pChildWnd->GetWindowRect(rectThisButton);
        if (rectThisButton.right > nRightMostXValue)
          rectButton = rectThisButton;
      }
    }  

    pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
  }

  return rectButton;
}

void CMessageBoxX::RightAlignButtons()
{
  //Get the right most button position
  CRect rectRightButton = GetRightMostButtonRect();

  //Work out how much we need to move each button to get them right aligned
  CRect rectDialogUnits(0, 0, 7, 0);
  MapDialogRect(GetSafeHwnd(), &rectDialogUnits);
  CRect rectWindow;
  GetWindowRect(&rectWindow);
  int nDeltaX = rectWindow.right - rectDialogUnits.Width() - rectRightButton.right;
  if (nDeltaX)
  {
    //Now move all the buttons on the message box to get them right aligned
    CWnd* pChildWnd = GetWindow(GW_CHILD);
    static TCHAR* szButtonClass = _T("BUTTON");
    static TCHAR szTest[]      = _T("      "); //7 tchar's allocated buffer to hold the classname "BUTTON"
    while (pChildWnd)
    {
      if (GetClassName(pChildWnd->GetSafeHwnd(), szTest, sizeof(szTest)/sizeof(TCHAR)))
      {
        if (_tcsnicmp(szTest, szButtonClass, (sizeof(szTest)/sizeof(TCHAR)) - 1) == 0)
        {
          //Aha we have found a button, move it over horizontally!
          CRect rectButton;
          pChildWnd->GetWindowRect(&rectButton);
          ScreenToClient(&rectButton);
          rectButton.OffsetRect(nDeltaX, 0);
          pChildWnd->SetWindowPos(NULL, rectButton.left, rectButton.top, 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
        }
      }  

      pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
    }
  }
}

void CMessageBoxX::CreateCheckBox()
{
  //Get the size of the check box to create
  CFont* pFont = GetFont();
  CSize sizeCheckBox = GetCheckBoxSize(pFont);

  //Determine the position of the check box (in the process increasing the height of 
  //the message box to accommodate it)
  CWnd* pTextControl = FindOurTextControl();
  AFXASSUME(pTextControl);
  CRect rectStatic;
  pTextControl->GetWindowRect(&rectStatic);
  ScreenToClient(&rectStatic);
  CPoint pt(rectStatic.left, rectStatic.bottom);
  CRect rectDialogUnits(0, 0, 0, 6);
  MapDialogRect(GetSafeHwnd(), &rectDialogUnits);
  int nCheckBoxDeltaY = rectDialogUnits.Height();
  pt.y += nCheckBoxDeltaY;
  CRect rectCheckBox(pt.x, pt.y, pt.x + sizeCheckBox.cx, pt.y + sizeCheckBox.cy);
  
  //Clip the check box to the text if necessary
  if (rectCheckBox.right > rectStatic.right)
    rectCheckBox.right = rectStatic.right;

  //Get the position of the first button to see if we need to move the buttons
  //down to accommodate the new checkbox
  CWnd* pButton = GetFirstButton();
  AFXASSUME(pButton);
  CRect rectButton;
  pButton->GetWindowRect(&rectButton);
  ScreenToClient(&rectButton);

  //See if we need to move all the buttons down a bit
  if (rectButton.top < rectCheckBox.bottom + nCheckBoxDeltaY)
  {
    //First we need to increase the height of the message box by the extra height
    int nExtraHeight = rectCheckBox.bottom + nCheckBoxDeltaY - rectButton.top;
    CRect rectWindow;
    GetWindowRect(&rectWindow);  
    rectWindow.bottom += nExtraHeight;

    SetWindowPos(NULL, rectWindow.left, rectWindow.top, rectWindow.Width(), rectWindow.Height(), SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
    GetWindowRect(&rectWindow);

    //Now move all the buttons on the message box down by the extra height
    CWnd* pChildWnd = GetWindow(GW_CHILD);
    static TCHAR* szButtonClass = _T("BUTTON");
    static TCHAR szTest[]      = _T("      "); //7 tchar's allocated buffer to hold the classname "BUTTON"
    while (pChildWnd)
    {
      if (GetClassName(pChildWnd->GetSafeHwnd(), szTest, sizeof(szTest)/sizeof(TCHAR)))
      {
        if (_tcsnicmp(szTest, szButtonClass, (sizeof(szTest)/sizeof(TCHAR)) - 1) == 0)
        {
          //Aha we have found a button, move it down a bit!
          pChildWnd->GetWindowRect(&rectButton);
          ScreenToClient(&rectButton);
          rectButton.OffsetRect(0, nExtraHeight);
          pChildWnd->SetWindowPos(NULL, rectButton.left, rectButton.top, 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
        }
      }  

      pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
    }
  }

  //Finally, create the check box
  m_wndCheckBox.Create(m_sCheckBoxText, WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, rectCheckBox, this, 0); 
  m_wndCheckBox.SetFont(pFont);
  if (m_bCheckBoxState)
    m_wndCheckBox.SetCheck(1);
}

void CMessageBoxX::FixUpPositionsToSuitQHTM(const CRect& rectText)
{
  //Work out the logical location of the top of the buttons (allowing room for the possibly expanded QHTM text control)
  CRect rectDialogUnits(0, 0, 0, 6);
  MapDialogRect(GetSafeHwnd(), &rectDialogUnits);
  int nRequiredTopOfButton = rectText.bottom + rectDialogUnits.Height();

  //Get the position of the first button to see if we need to move the buttons
  //down to accommodate the new checkbox
  CWnd* pButton = GetFirstButton();
  AFXASSUME(pButton);
  CRect rectButton;
  pButton->GetWindowRect(&rectButton);
  ScreenToClient(&rectButton);

  //See if we need to move all the buttons down a bit
  if (rectButton.top < nRequiredTopOfButton)
  {
    //First we need to increase the height of the message box by the extra height
    int nExtraHeight = nRequiredTopOfButton - rectButton.top;
    CRect rectWindow;
    GetWindowRect(&rectWindow);  
    rectWindow.bottom += nExtraHeight;

    SetWindowPos(NULL, rectWindow.left, rectWindow.top, rectWindow.Width(), rectWindow.Height(), SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
    GetWindowRect(&rectWindow);

    //Now move all the buttons on the message box down by the extra height
    CWnd* pChildWnd = GetWindow(GW_CHILD);
    static TCHAR* szButtonClass = _T("BUTTON");
    static TCHAR szTest[]      = _T("      "); //7 tchar's allocated buffer to hold the classname "BUTTON"
    while (pChildWnd)
    {
      if (GetClassName(pChildWnd->GetSafeHwnd(), szTest, sizeof(szTest)/sizeof(TCHAR)))
      {
        if (_tcsnicmp(szTest, szButtonClass, (sizeof(szTest)/sizeof(TCHAR)) - 1) == 0)
        {
          //Aha we have found a button, move it down a bit!
          pChildWnd->GetWindowRect(&rectButton);
          ScreenToClient(&rectButton);
          rectButton.OffsetRect(0, nExtraHeight);
          pChildWnd->SetWindowPos(NULL, rectButton.left, rectButton.top, 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
        }
      }  

      pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
    }
  }
}

void CMessageBoxX::ModifyButtonCaptions()
{
  //Iterate thro all the button controls, the order in which they are returned here corresponds to the index in the "m_sModifiedButtonCaptions" array
  CWnd* pChildWnd = GetWindow(GW_CHILD);
  static TCHAR* szButtonClass = _T("BUTTON");
  static TCHAR szTest[]      = _T("      "); //7 tchar's allocated buffer to hold the classname "BUTTON"
  int nCurrentButtonIndex = 0;
  while (pChildWnd)
  {
    if (GetClassName(pChildWnd->GetSafeHwnd(), szTest, sizeof(szTest)/sizeof(TCHAR)))
    {
      //Have we found a button?
      if (_tcsnicmp(szTest, szButtonClass, (sizeof(szTest)/sizeof(TCHAR)) - 1) == 0)
      {
        ASSERT(nCurrentButtonIndex < sizeof(m_sModifiedButtonCaptions)/sizeof(CString));

        //Yes, then modify its caption if required
        if (m_sModifiedButtonCaptions[nCurrentButtonIndex].GetLength())
          pChildWnd->SetWindowText(m_sModifiedButtonCaptions[nCurrentButtonIndex]);

        //Increment the button index counter
        ++nCurrentButtonIndex;
      }
    }  

    pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
  }
}

LRESULT CMessageBoxX::OnInitDialog(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
  //Call the default window proc
  LRESULT lRet = Default();

  //install the timer and disable the button if necessary
  if (m_nTimerTimeout || m_nDisabledTimeout)
  {
    //Install a timer if we need to timeout or a disabled button
    InstallTimeoutDisabledTimeout();

    //Do we need to disable the relevent button
    if (m_nDisabledTimeout)
    {
      CWnd* pWnd = GetDlgItem(m_nDisabledButtonId);
      AFXASSUME(pWnd);
      pWnd->EnableWindow(FALSE);
    }
  }

  //Should we do text animation?
  if (m_dwTextAnimationInterval)
    InstallAnimatedTextTimer();

  //Should we do caption animation?
  if (m_dwCaptionAnimationInterval)
    InstallAnimatedCaptionTimer();

  //Update the button captions
  ModifyButtonCaptions();

  //Right align the buttons if necessary
  if (m_bRightAlignButtons)
    RightAlignButtons();

  //Should we create the text as selectable
  if (m_bSelectableText)
  {
    //Hide the message text
    CWnd* pWndText = FindTextControl();
    AFXASSUME(pWndText);
    pWndText->ShowWindow(SW_HIDE);

    //And in its place create the edit control
    CRect rectText;
    pWndText->GetWindowRect(&rectText);
    ScreenToClient(&rectText);

    //Create the control
    rectText.InflateRect(2,0,2,0); //We need this extra space on the left and right because the edit control uses an internal horizontal margin 
                                   //of a few pixels for the drawing of its text
    VERIFY(m_wndSelectableText.Create(ES_READONLY | ES_AUTOHSCROLL | ES_MULTILINE | WS_VISIBLE | WS_CHILD, rectText, this, MESSAGEBOXX_EDIT_ID));

    //Set its text and font
    CString sEditText(m_sText);
    sEditText.Replace(_T("\r\n"), _T("MSGBOXX_EOL"));
    sEditText.Replace(_T("\n"), _T("\r\n"));
    sEditText.Replace(_T("MSGBOXX_EOL"), _T("\r\n"));
    m_wndSelectableText.SetWindowText(sEditText);
    m_wndSelectableText.SetFont(GetFont());
  }

#ifdef CMESSAGEBOXX_HTML_SUPPORT
  //Hook up QHML if we are doing HTML
  if (m_bHTML)
  {
    //Hide the message text
    CWnd* pWndText = FindTextControl();
    AFXASSUME(pWndText);
    pWndText->ShowWindow(SW_HIDE);
    //Also update its text to the HTML so that screen readers etc will pick up the HTML text and not the layout test
    pWndText->SetWindowText(m_sHTMLText);

    //And in its place create the QHTM control
    CRect rectText;
    pWndText->GetWindowRect(&rectText);
    ScreenToClient(&rectText);

    //determine how high we need to make the HTML control
    CDC* pDC = GetDC();
    int nHeight = QHTM_PrintGetHTMLHeight(pDC->GetSafeHdc(), m_sHTMLText, rectText.Width(), QHTM_ZOOM_DEFAULT);
    rectText.bottom = rectText.top + nHeight;

    //Create QHTM control
    VERIFY(m_wndQHTM.Create(QHTM_CLASSNAME, m_sHTMLText, WS_VISIBLE | WS_CHILD, rectText, this, MESSAGEBOXX_HTML_ID)); //If this function call fails, more that likely you forget to call QHTM_Initialize as part of your startup code

    //Release the DC we have been using  
    ReleaseDC(pDC);

    //Nove fix up the positions of the buttons (and the message box size) to suit the QHTM control
    FixUpPositionsToSuitQHTM(rectText);
  }
#endif

  //Add the check box if necessary (Note it is important that we
  //create the checkbox after the right align code above so as
  //that code does not include the checkbox in its calculation logic!
  if (m_bCheckBox)
    CreateCheckBox();

  //Call the C++ virtual OnInitDone implementation
  OnInitDone();

  return lRet;
}

BOOL CMessageBoxX::OnInitDone()
{
  //Derived classes may want to do something more interesting
  return TRUE;
}

BOOL CMessageBoxX::InstallAnimatedTextTimer()
{
  //validate our parameters
  ASSERT(m_nAnimatedTextTimerID == 0);

  //Install the timeout / disabled button timer
  m_nAnimatedTextTimerID = SetTimer(MESSAGEBOXX_ANIMATED_TEXT_TIMER, m_dwTextAnimationInterval, NULL);

  return (m_nAnimatedTextTimerID != 0);
}

BOOL CMessageBoxX::InstallAnimatedCaptionTimer()
{
  //validate our parameters
  ASSERT(m_nAnimatedCaptionTimerID == 0);

  //Install the timeout / disabled button timer
  m_nAnimatedCaptionTimerID = SetTimer(MESSAGEBOXX_ANIMATED_CAPTION_TIMER, m_dwCaptionAnimationInterval, NULL);

  return (m_nAnimatedCaptionTimerID != 0);
}

BOOL CMessageBoxX::InstallTimeoutDisabledTimeout()
{
  //Validate our parameters
  ASSERT(m_nTimeoutDisabledButtonTimerID == 0);

  //Install the timeout / disabled button timer
  m_nTimeoutDisabledButtonTimerID = SetTimer(MESSAGEBOXX_TIMEOUT_DISABLED_TIMER, 1000, NULL);

  return (m_nTimeoutDisabledButtonTimerID != 0);
}

void CMessageBoxX::OnTimer(UINT_PTR nIDEvent) 
{
  //Is it our timer?
  if (nIDEvent == m_nTimeoutDisabledButtonTimerID)
    DoTimeoutDisabledButtonUpdate();
  else if (nIDEvent == m_nAnimatedTextTimerID)
    DoAnimatedTextUpdate();
  else if (nIDEvent == m_nAnimatedCaptionTimerID)
    DoAnimatedCaptionUpdate();
  else	
  {
    //No!, then just let the base class do its thing
	  CWnd::OnTimer(nIDEvent);
  }
}

void CMessageBoxX::DoTimeoutDisabledButtonUpdate()
{
  //Decrement the relevent counters
  if (m_nTimerTimeout)
    --m_nTimerCountdown;
  if (m_nDisabledTimeout)
    --m_nDisabledCountdown;

  //Should we re-enable the relevent button
  if (m_nDisabledTimeout && (m_nDisabledCountdown == 0)) 
  {
    CWnd* pWnd = GetDlgItem(m_nDisabledButtonId);
    AFXASSUME(pWnd);
    pWnd->EnableWindow(TRUE);

    //Reset the caption (if we do not have a timeout currently changing it)
    BOOL bUpdateCaption = (m_bModifyCaptionForDisabledCountdown && ((m_nTimerTimeout && (m_nTimerCountdown > 10)) || (!m_nTimerTimeout)));
    if (bUpdateCaption)
      SetWindowText(m_sCaption);

    //Reset the disabled variables
    m_nDisabledTimeout = 0;
    m_nDisabledButtonId = 0;

    //Kill the timer (if we do not have a auto close pending)
    if (m_nTimerTimeout == 0)
    {
      KillTimer(m_nTimeoutDisabledButtonTimerID);
      m_nTimeoutDisabledButtonTimerID = 0;
    }
  }

  //Should we do the timeout?
  if (m_nTimerTimeout && (m_nTimerCountdown == 0))
  {
    //Kill the timer (since we are about to close!)
    KillTimer(m_nTimeoutDisabledButtonTimerID);
    m_nTimeoutDisabledButtonTimerID = 0;

    //Force the message box to close
    CWnd* pButton = GetDlgItem(m_nTimerButtonId);
    AFXASSUME(pButton);
    PostMessage(WM_COMMAND, MAKEWORD(m_nTimerButtonId, BN_CLICKED), reinterpret_cast<LPARAM>(pButton->GetSafeHwnd())); 

    //Reset the timer variables
    m_nTimerTimeout = 0;
    m_nTimerButtonId = 0;
  }
  else
  {
    //We didn't re enable a button and we didn't auto close the dialog, so see if we need to update the caption
    CString sNewCaption(GetCurrentTimerCaption());
    if (sNewCaption != m_sCaption)
      SetWindowText(sNewCaption);
    else
    {
      sNewCaption = GetCurrentDisabledCaption();
      if (sNewCaption != m_sCaption)
        SetWindowText(sNewCaption);
    }
  }
}

void CMessageBoxX::DoAnimatedTextUpdate()
{
  //Validate our parameters
  AFXASSUME(m_pAnimatedTexts);

  INT_PTR nSize = m_pAnimatedTexts->GetSize();
  ++m_nCurrentAnimatedTextIndex;

  //Have we come to the end of the animation array?
  BOOL bDoUpdate = FALSE;
  if (m_nCurrentAnimatedTextIndex == nSize)
  {
    if (m_bAnimatedTextLoop)
    {
      m_nCurrentAnimatedTextIndex = 0;
      bDoUpdate = TRUE;
    }
    else
    {
      //Kill the timer since we have no need for it anymore  
      KillTimer(m_nAnimatedTextTimerID);
      m_nAnimatedTextTimerID = 0;
    }
  }
  else
    bDoUpdate = TRUE;

  if (bDoUpdate)
  {
    //Lets update the text
    CWnd* pWndText = FindOurTextControl();
    AFXASSUME(pWndText);
    pWndText->SetWindowText(m_pAnimatedTexts->GetAt(m_nCurrentAnimatedTextIndex));
  }
}

void CMessageBoxX::DoAnimatedCaptionUpdate()
{
  //Validate our parameters
  AFXASSUME(m_pAnimatedCaptions);

  INT_PTR nSize = m_pAnimatedCaptions->GetSize();
  ++m_nCurrentAnimatedCaptionIndex;

  //Have we come to the end of the animation array?
  BOOL bDoUpdate = FALSE;
  if (m_nCurrentAnimatedCaptionIndex == nSize)
  {
    if (m_bAnimatedCaptionLoop)
    {
      m_nCurrentAnimatedCaptionIndex = 0;
      bDoUpdate = TRUE;
    }
    else
    {
      //Kill the timer since we have no need for it anymore  
      KillTimer(m_nAnimatedCaptionTimerID);
      m_nAnimatedCaptionTimerID = 0;
    }
  }
  else
    bDoUpdate = TRUE;

  if (bDoUpdate)
  {
    //Lets update the caption
    SetWindowText(m_pAnimatedCaptions->GetAt(m_nCurrentAnimatedCaptionIndex));
  }
}

INT_PTR CMessageBoxX::DoModal()
{
  //Get the CWinApp* pointer
  CMessageBoxPublicWinApp* pApp = static_cast<CMessageBoxPublicWinApp*>(AfxGetApp());

	//disable windows for modal dialog
	if (pApp)
	  pApp->DoEnableModeless(FALSE);
	HWND hWndTop;
	HWND hWnd = CWnd::GetSafeOwner_(NULL, &hWndTop);

	//re-enable the parent window, so that focus is restored 
	//correctly when the dialog is dismissed.
	if (hWnd != hWndTop)
		::EnableWindow(hWnd, TRUE);

	//set help context if possible
	DWORD* pdwContext = NULL;

  //Note we only use WM_HELPPROMPTADDR if the window belongs to the current process
	DWORD dwWndPid = 0;
	GetWindowThreadProcessId(hWnd, &dwWndPid);
	if (hWnd != NULL && dwWndPid == GetCurrentProcessId())
	{
		//use app-level context or frame level context
		LRESULT lResult = ::SendMessage(hWnd, WM_HELPPROMPTADDR, 0, 0);
		if (lResult != 0)
			pdwContext = reinterpret_cast<DWORD*>(lResult);
	}
	//for backward compatibility use app context if possible
	if (pdwContext == NULL && pApp != NULL)
		pdwContext = pApp->GetPromptContextAddress();

	DWORD dwOldPromptContext = 0;
	if (pdwContext != NULL)
	{
		//save old prompt context for restoration later
		dwOldPromptContext = *pdwContext;
		if (m_nHelpIDPrompt != 0)
			*pdwContext = HID_BASE_PROMPT + m_nHelpIDPrompt;
	}

	//determine icon based on type specified
	if ((m_nType & MB_ICONMASK) == 0)
	{
		switch (m_nType & MB_TYPEMASK)
		{
		  case MB_OK: //deliberate fallthrough
		  case MB_OKCANCEL:
		  {
			  m_nType |= MB_ICONEXCLAMATION;
			  break;
      }
		  case MB_YESNO: //deliberate fallthrough
		  case MB_YESNOCANCEL:
		  {
			  m_nType |= MB_ICONQUESTION;
			  break;
      }
		  case MB_ABORTRETRYIGNORE: //deliberate fallthrough
		  case MB_RETRYCANCEL:
		  {
			  //No default icon for these types, since they are rarely used.
			  //The caller should specify the icon.
			  break;
		  }
		}
	}

#ifdef _DEBUG
	if ((m_nType & MB_ICONMASK) == 0)
		TRACE(_T("CMessageBoxX::DoModal, Warning: no icon specified for message box.\n"));
#endif

  //Hook the creation of the MessageBox
	AfxHookWindowCreate(this);

  //Display the message box
  INT_PTR nResult;
  if (m_nType & MB_USERICON)
  {
    MSGBOXPARAMS params;
    params.cbSize = sizeof(params);
    params.hwndOwner = hWnd;
    params.hInstance = m_hIconInstance;
    params.lpszText = m_sText;
    params.lpszCaption = m_sCaption;
    params.dwStyle = m_nType;
    params.lpszIcon = m_pszIcon;
    params.dwContextHelpId = 0; //We always use WM_HELP
    params.lpfnMsgBoxCallback = NULL;
    params.dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
    nResult = ::AfxCtxMessageBoxIndirect(&params);
  }
  else
    nResult = ::AfxCtxMessageBox(hWnd, m_sText, m_sCaption, m_nType);

	//restore prompt context if possible
	if (pdwContext != NULL)
		*pdwContext = dwOldPromptContext;

	//re-enable windows
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
	if (pApp)
	  pApp->DoEnableModeless(TRUE);

	return nResult;
}

LRESULT CMessageBoxX::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  //What will be the return value
  LRESULT lResult;

  //Prevent button click notifications from the disabled button if we are using a disabled button and it is outstanding
  if ((message == WM_COMMAND) && (m_nDisabledTimeout != 0) && (HIWORD(wParam) == BN_CLICKED) && (LOWORD(wParam) == m_nDisabledButtonId))
    lResult = 0;
  else
  {
    //Pass the buck to the default implementation
    lResult = CWnd::DefWindowProc(message, wParam, lParam);

    //Reset the timer if the timer is active and we are configred to reset on user activity
    if (m_nTimerTimeout && m_bResetTimeoutOnUserActivity && ((message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) || ((message >= WM_KEYFIRST) && (message <= WM_KEYLAST))))
    {
      //reset the caption if it is modified
      if (m_bModifyCaptionForTimerCountdown && (m_nTimerCountdown <= 10))
        SetWindowText(m_sCaption);
    
      //And most importantly reset the coundown timer value
      m_nTimerCountdown = m_nTimerTimeout;
    }
  }

  return lResult;
}

void CMessageBoxX::OnDestroy() 
{
  //Get the current check box state if we have one
  if (m_bCheckBox)
    m_bCheckBoxState = (m_wndCheckBox.GetCheck() != 0);

  //Kill the animations timers
  if (m_nAnimatedTextTimerID != 0)
  {
    KillTimer(m_nAnimatedTextTimerID);
    m_nAnimatedTextTimerID = 0;  
  }
  if (m_nAnimatedCaptionTimerID != 0)
  {
    KillTimer(m_nAnimatedCaptionTimerID);
    m_nAnimatedCaptionTimerID = 0;  
  }
  
  //Let the base class do its thing	
	CWnd::OnDestroy();
}
