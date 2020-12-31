/*
Module : MessageBoxX.H
Purpose: Defines the interface for a MFC wrapper class for the MessageBox API
Created: PJN / 18-04-2003

Copyright (c) 2003 - 2008 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////////// Defines ///////////////////////////////////////

#pragma once

#ifndef __MESSAGEBOXX_H__
#define __MESSAGEBOXX_H__


/////////////////////////////// Includes //////////////////////////////////////

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#pragma message("To avoid this message, you should put afxtempl.h in your pre compiled header (normally stdafx.h)")
#endif


/////////////////////////////// Defines ///////////////////////////////////////

#ifndef CMESSAGEBOXX_EXT_CLASS
#define CMESSAGEBOXX_EXT_CLASS
#endif


/////////////////////////////// Classes ///////////////////////////////////////

class CMESSAGEBOXX_EXT_CLASS CMessageBoxX : public CWnd
{
public: 
//Constructors / Destructors
  CMessageBoxX();
  CMessageBoxX(LPCTSTR lpszText, LPCTSTR lpszCaption = NULL, UINT nType = MB_OK, CWnd* pParent = NULL, UINT nIDHelp = 0);
  CMessageBoxX(UINT nIDResource, LPCTSTR lpszCaption = NULL, UINT nType = MB_OK, CWnd* pParent = NULL, UINT nIDHelp = -1);
//Methods
  INT_PTR DoModal();

//Accessors / Mutators
  void    SetCaption(LPCTSTR lpszCaption);
  void    SetCaption(UINT nIDResource);
  void    SetCaption(UINT nIDResource, LPCTSTR lpsz1);
  void    SetCaption(UINT nIDResource, LPCTSTR lpsz1, LPCTSTR lpsz2);
  void    SetText(LPCTSTR lpszText, UINT nIDHelp = 0);
  void    SetText(UINT nIDResource, UINT nIDHelp = -1);
  void    SetText(UINT nIDResource, LPCTSTR lpsz1, UINT nIDHelp = -1);
  void    SetText(UINT nIDResource, LPCTSTR lpsz1, LPCTSTR lpsz2, UINT nIDHelp = -1);
  void    SetUserIcon(UINT nIDResource, HINSTANCE hInstance = AfxGetResourceHandle());
  void    SetUserIcon(LPCTSTR lpszResourceName, HINSTANCE hInstance = AfxGetResourceHandle());
  void    SetParent(CWnd* pParent);
  void    SetParent(HWND hParent);
  void    SetType(UINT nType);
  void    SetTimeout(int nTimeout, int nTimeoutButtonId = IDCANCEL, BOOL bModifyCaptionDuringCountdown = TRUE, BOOL bResetTimeoutOnUserActivity = FALSE);
  void    SetDisabledButton(int nTimeout, int nDisabledButtonId = IDOK, BOOL bModifyCaptionDuringCountdown = TRUE);
  void    SetCheckBox(BOOL bChecked, LPCTSTR lpszText);
  void    SetCheckBoxState(BOOL bChecked) { m_bCheckBoxState = bChecked; };
  BOOL    GetCheckBoxState() const { return m_bCheckBoxState; };
  void    SetRightAlignButtons(BOOL bRightAlign);
  void    SetSelectableText(BOOL bSelectableText);
  BOOL    GetSelectableText() const { return m_bSelectableText; };
  void    SetModifiedButtonCaption(int nButtonIndex, LPCTSTR pszNewCaption);
  CString GetModifiedButtonCaption(int nButtonIndex);
  void    SetAnimatedText(DWORD dwAnimationInterval, const CStringArray* pTexts, BOOL bLoop);
  void    SetAnimatedCaption(DWORD dwAnimationInterval, const CStringArray* pCaptions, BOOL bLoop);
#ifdef CMESSAGEBOXX_HTML_SUPPORT
  void    SetHTMLText(LPCTSTR pszHTML) { m_sHTMLText = pszHTML; }; //Note the reason why we have a separate SetText and SetHTMLText method is that the normal text is used by the MessageBox
                                                                   //API call to determine the width to use for the text while the HTML text has its own rules about layout. By splitting the
                                                                   //two, you can then for example set the plain text to a specific size of unused characters e.g. for layout purposes and set
                                                                   //the real (HTML) text which is displayed via SetHTMLText
  void    SetHTMLText(UINT nIDResource);
  void    SetHTMLText(UINT nIDResource, LPCTSTR lpsz1);
  void    SetHTMLText(UINT nIDResource, LPCTSTR lpsz1, LPCTSTR lpsz2);
  CString GetHTMLText() const { return m_sHTMLText; };
  void    SetHTML(BOOL bHTML);
  BOOL    GetHTML() const { return m_bHTML; };
#endif

protected:
//Member variables
  CString       m_sCaption;
  CString       m_sText;
  UINT          m_nHelpIDPrompt;
  LPCTSTR       m_pszIcon;
  HINSTANCE     m_hIconInstance;
  HWND          m_hParentWnd;
  UINT          m_nType;
  int           m_nTimerTimeout;
  int           m_nTimerButtonId;
  int           m_nTimerCountdown;
  BOOL          m_bModifyCaptionForTimerCountdown;
  BOOL          m_bResetTimeoutOnUserActivity;
  int           m_nDisabledTimeout;
  int           m_nDisabledButtonId;
  BOOL          m_bModifyCaptionForDisabledCountdown;
  int           m_nDisabledCountdown;
  UINT_PTR      m_nTimeoutDisabledButtonTimerID;
  UINT_PTR      m_nAnimatedTextTimerID;
  UINT_PTR      m_nAnimatedCaptionTimerID;
  DWORD         m_dwTextAnimationInterval;
  const CStringArray* m_pAnimatedTexts;
  BOOL          m_bAnimatedTextLoop;
  INT_PTR       m_nCurrentAnimatedTextIndex;
  DWORD         m_dwCaptionAnimationInterval;
  const CStringArray* m_pAnimatedCaptions;
  BOOL          m_bAnimatedCaptionLoop;
  int           m_nCurrentAnimatedCaptionIndex;
  BOOL          m_bCheckBox;
  BOOL          m_bCheckBoxState;
  CString       m_sCheckBoxText;
  CButton       m_wndCheckBox;     
  BOOL          m_bRightAlignButtons;
  BOOL          m_bSelectableText;
  CEdit         m_wndSelectableText;
#ifdef CMESSAGEBOXX_HTML_SUPPORT
  BOOL          m_bHTML;
  CWnd          m_wndQHTM;
  CString       m_sHTMLText;
#endif          
  CString       m_sModifiedButtonCaptions[4]; //Contains the captions we applied to the modified buttons

//Methods
  virtual BOOL InstallTimeoutDisabledTimeout();
  virtual BOOL InstallAnimatedTextTimer();
  virtual BOOL InstallAnimatedCaptionTimer();
  virtual void DoTimeoutDisabledButtonUpdate();
  virtual void DoAnimatedTextUpdate();
  virtual void DoAnimatedCaptionUpdate();
  virtual CSize GetCheckBoxSize(CFont* pFont);
  virtual void CreateCheckBox();
  virtual void RightAlignButtons();
  virtual void FixUpPositionsToSuitQHTM(const CRect& rectText);
  virtual void ModifyButtonCaptions();
  virtual CString GetCurrentTimerCaption();
  virtual CString GetCurrentDisabledCaption();
  void    Initialize();
  CRect   GetRightMostButtonRect();
  CWnd*   FindTextControl();
  CWnd*   FindOurTextControl();
  CWnd*   GetFirstButton();
  virtual BOOL OnInitDone(); //virtual function similiar to the CFileDialog method of the same name

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

  virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

#endif //__MESSAGEBOXX_H__
