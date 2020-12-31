/*
Module : DATENTRY.H
Purpose: implementation to a number of classes to allow data entry of the date/time classes
Created: PJN / DATE/1 / 20-02-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "pushpin.h"
#include "win32sup.h"
#include "dentry.h"
#include "dtimeres.h"




//////////////////////////////////  Macros  ///////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifndef _WINDOWS
#pragma message("This module should be included in builds for Windows only")
#endif


////////////////////////////////// Statics ////////////////////////////////////
#define UWM_DLG_CLOSE  WM_USER + 101
#define MOUSE_MOVE 0xf012


////////////////////////////////// Implementation /////////////////////////////
BEGIN_MESSAGE_MAP(CDTDialog, CDialog)
  //{{AFX_MSG_MAP(CDTDialog)
  ON_WM_LBUTTONDOWN()
  ON_WM_ACTIVATE()
  #ifndef _WIN32
  ON_COMMAND(IDC_PUSHPIN, OnPushPin)
  #endif
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CCDateDlg, CDTDialog)
  //{{AFX_MSG_MAP(CCDateDlg)
  ON_BN_CLICKED(IDC_INVALID, OnInvalid)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CCLTimeOfDayDlg, CDTDialog)
  //{{AFX_MSG_MAP(CCLTimeOfDayDlg)
  ON_BN_CLICKED(IDC_INVALID, OnInvalid)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CCLTimeSpanDlg, CDTDialog)
  //{{AFX_MSG_MAP(CCLTimeSpanDlg)
  ON_BN_CLICKED(IDC_INVALID, OnInvalid)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CCLDateDlg, CDTDialog)
  //{{AFX_MSG_MAP(CCLDateDlg)
  ON_BN_CLICKED(IDC_INVALID, OnInvalid)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CDateButton, CButton)
  //{{AFX_MSG_MAP(CDateButton)
#ifdef _WIN32  
  ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
#else                                 
  ON_MESSAGE(UWM_BN_CLICKED, OnMyReflectedClicked)  
#endif  
  ON_MESSAGE(UWM_DLG_CLOSE, OnDlgClose)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CDateTimeControl, CStatic)
  //{{AFX_MSG_MAP(CDateTimeControl)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CDateControl, CDateTimeControl)
  //{{AFX_MSG_MAP(CDateControl)
  ON_MESSAGE(UWM_BN_CLICKED, OnEditClick)
  ON_MESSAGE(UWM_DLG_CLOSE, OnDlgClose)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CLTimeSpanControl, CDateTimeControl)
  //{{AFX_MSG_MAP(CLTimeSpanControl)
  ON_MESSAGE(UWM_BN_CLICKED, OnEditClick)
  ON_MESSAGE(UWM_DLG_CLOSE, OnDlgClose)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CLTimeOfDayControl, CDateTimeControl)
  //{{AFX_MSG_MAP(CLTimeOfDayControl)
  ON_MESSAGE(UWM_BN_CLICKED, OnEditClick)
  ON_MESSAGE(UWM_DLG_CLOSE, OnDlgClose)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CLDateControl, CDateTimeControl)
  //{{AFX_MSG_MAP(CLDateControl)
  ON_MESSAGE(UWM_BN_CLICKED, OnEditClick)
  ON_MESSAGE(UWM_DLG_CLOSE, OnDlgClose)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CDTDialog::CDTDialog()
{
  m_pParentWnd = NULL;
  m_dwFlags = 0;
  m_bSafeToClose = TRUE;
}

CDTDialog::CDTDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd) :
     CDialog(lpszTemplateName, pParentWnd)
{
  m_pParentWnd = pParentWnd;
  m_dwFlags = 0;
  m_bSafeToClose = TRUE;
}

CDTDialog::CDTDialog(UINT nIDTemplate, CWnd* pParentWnd) : 
     CDialog(nIDTemplate, pParentWnd)
{
  m_pParentWnd = pParentWnd;
  m_dwFlags = 0;
  m_bSafeToClose = TRUE;
}


void CDTDialog::OnLButtonDown(UINT /*nFlags*/, CPoint point) 
{
  if (!(m_dwFlags & DT_NODRAG))
  {
    ClientToScreen(&point);
    SendMessage(WM_LBUTTONUP, 0, MAKELONG(point.x, point.y));
    SendMessage(WM_SYSCOMMAND, MOUSE_MOVE, MAKELONG(point.x, point.y));
  }
}


BOOL CDTDialog::OnInitDialog() 
{
  BOOL rval = CDialog::OnInitDialog();

  //adjust the position to concide with the parent button
  ASSERT(m_pParentWnd != NULL);

  CRect ParentRect;
  m_pParentWnd->GetWindowRect(ParentRect);
  int y = ParentRect.bottom+3;
  int nMaxY = GetSystemMetrics(SM_CYFULLSCREEN);
  CRect ThisRect;
  GetWindowRect(ThisRect);
  if (y+ThisRect.bottom-ThisRect.top >= nMaxY)
    y = (ParentRect.top - 3 - ThisRect.bottom + ThisRect.top);
  int x = ParentRect.right-ThisRect.right+ThisRect.left;
  if (x < 1)
    x = 1;
  SetWindowPos(NULL, x, y, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

  //create the push pin button
  if (m_dwFlags & DT_PUSHPIN)
  {                     
    //ensure that bitmaps loads from dtime as 16 bit MFC will
    //not look in extension dlls when loading a bitmap
    #ifndef _WIN32
      #ifdef _DEBUG
        HINSTANCE hDtimeDLL = GetModuleHandle("DT10016D.DLL");
      #else
        HINSTANCE hDtimeDLL = GetModuleHandle("DT10016.DLL");
      #endif
      HINSTANCE hOldResourceHandle = AfxGetResourceHandle();
      AfxSetResourceHandle(hDtimeDLL);
    #endif    
  
    m_btnPushPin.AutoLoad(IDC_PUSHPIN, this);               
                                                          
    #ifndef _WIN32                                                      
      AfxSetResourceHandle(hOldResourceHandle);
    #endif

    //add the tooltip for the push pin
    #ifdef _WIN32
      m_TipPushPin.Create(this);
      m_TipPushPin.Activate(TRUE);
      m_TipPushPin.AddTool(GetDlgItem(IDC_PUSHPIN), IDS_TT_PUSHPIN);
    #endif
  }

  return rval;
}


void CDTDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
  CDialog::OnActivate(nState, pWndOther, bMinimized);

  //DT_PUSHPIN & DT_CLOSEONDEACTIVE are mutually exclusive
  if (m_dwFlags & DT_PUSHPIN)
    ASSERT(!(m_dwFlags & DT_CLOSEONDEACTIVE));
  if (m_dwFlags & DT_CLOSEONDEACTIVE)
    ASSERT(!(m_dwFlags & DT_PUSHPIN));
  
  if ((m_dwFlags & DT_MODELESS) && m_bSafeToClose && (nState == WA_INACTIVE))
  {
    if ((m_dwFlags & DT_CLOSEONDEACTIVE) || (m_dwFlags & DT_PUSHPIN && !m_btnPushPin.IsPinned()))
      OnCancel();
  }
}


BOOL CDTDialog::PreTranslateMessage(MSG* pMsg) 
{
  //give the tooltip a chance to handle the message
  if (m_dwFlags & DT_PUSHPIN)
  {
    #ifdef _WIN32
      m_TipPushPin.RelayEvent(pMsg);
    #endif  
  }
  return CDialog::PreTranslateMessage(pMsg);
}


void CDTDialog::OnOK()
{
  if (m_dwFlags & DT_MODELESS)
  {
    m_bSafeToClose = FALSE; //to avoid deactivating the window due to a message
                            //that could be displayed during UpdateData
    if (!UpdateData(TRUE))
    {
      TRACE0("UpdateData failed during dialog termination.\n");
      // the UpdateData routine will set focus to correct item
      m_bSafeToClose = TRUE;
      return;
    }

    m_bSafeToClose = TRUE;
    m_pParentWnd->PostMessage(UWM_DLG_CLOSE, 1);
    DestroyWindow();
  }  
  else if (m_dwFlags & DT_MODAL)
    CDialog::OnOK();
}


void CDTDialog::OnCancel()
{
  if (m_dwFlags & DT_MODELESS)
  {
    m_pParentWnd->PostMessage(UWM_DLG_CLOSE, 0);
    DestroyWindow();
  }
  else if (m_dwFlags & DT_MODAL)
    CDialog::OnCancel();
}                                  


#ifndef _WIN32
void CDTDialog::OnPushPin()
{
  m_btnPushPin.OnClicked();
}             
#endif


CCDateDlg::CCDateDlg()
{
  m_nDay = 0;
  m_lYear = 0;
  m_bInValid = FALSE;
  m_nDay = 1;
  m_lYear = CDate::CurrentYear();
  m_nMonth = 1;
}


CCDateDlg::CCDateDlg(CWnd* pParent, DWORD dwFlags)
  : CDTDialog(IDD_CDATE_WITHOUT_PIN, pParent)
{
  //DT_PUSHPIN & DT_CLOSEONDEACTIVE should be used with DT_MODELESS only
  if (dwFlags & DT_PUSHPIN)
    ASSERT(dwFlags & DT_MODELESS);
  if (dwFlags & DT_CLOSEONDEACTIVE)
    ASSERT(dwFlags & DT_MODELESS);

  //{{AFX_DATA_INIT(CCDateDlg)
  m_nDay = 0;
  m_lYear = 0;
  m_bInValid = FALSE;
  //}}AFX_DATA_INIT
  m_nDay = 1;
  m_lYear = CDate::CurrentYear();
  m_nMonth = 1;
  m_dwFlags = dwFlags;
}


BOOL CCDateDlg::Create(CWnd* pParent, DWORD dwFlags)
{
  //should only be created modeless when DT_MODELESS flag is used
  ASSERT(dwFlags & DT_MODELESS);

  m_dwFlags = dwFlags;
  m_pParentWnd = pParent;

  UINT nIDTemplate = IDD_CDATE_WITHOUT_PIN;
  if (dwFlags & DT_PUSHPIN)
    nIDTemplate = IDD_CDATE;

  return CDTDialog::Create(nIDTemplate, pParent);
}


void CCDateDlg::DoDataExchange(CDataExchange* pDX)
{
  CDTDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CCDateDlg)
  DDX_Check(pDX, IDC_INVALID, m_bInValid);
  //}}AFX_DATA_MAP
  
  if (!pDX->m_bSaveAndValidate || (pDX->m_bSaveAndValidate && !m_bInValid))
  {
    DDX_Control(pDX, IDC_MONTH, m_ctrlMonth);
    #ifdef _WIN32
      DDX_Control(pDX, IDC_UPDOWN_YEAR, m_ctrlSpinYear);
      DDX_Control(pDX, IDC_UPDOWN_DAY, m_ctrlSpinDay);
    #endif
    DDX_Control(pDX, IDC_INVALID, m_ctrlInvalid);
    DDX_Text(pDX, IDC_YEAR, m_lYear);
    DDX_Text(pDX, IDC_DAY, m_nDay);
  }

  if (pDX->m_bSaveAndValidate)
    m_nMonth = m_ctrlMonth.GetCurSel() + 1;
  else
  {
    OnInvalid();
    m_ctrlMonth.SetCurSel(m_nMonth-1);
  }

  DDV_MinMaxUInt(pDX, m_nDay, 1, (UINT) CDate::DaysInMonth((WORD) m_nMonth, CDate::IsLeap(m_lYear)));
}


BOOL CCDateDlg::OnInitDialog() 
{
  //Add the month strings
  CComboBox* pMonthCombo = (CComboBox*) GetDlgItem(IDC_MONTH);
  for (WORD i=1; i<13; i++)
    pMonthCombo->AddString(CDate::GetFullStringMonth(i));

  //Call up to the parent
  BOOL rval = CDTDialog::OnInitDialog();

  #ifdef _WIN32
    m_ctrlSpinYear.SetRange(UD_MINVAL, UD_MAXVAL);
    m_ctrlSpinDay.SetRange(1, 31);
  #endif

  //disable the invalid check box if required
  if (m_dwFlags & DT_ONLYVALID)
    m_ctrlInvalid.EnableWindow(FALSE);

  return rval;
}


void CCDateDlg::OnInvalid() 
{
  BOOL bEnable = !m_ctrlInvalid.GetCheck();
  GetDlgItem(IDC_DAY_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MONTH_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_YEAR_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_DAY)->EnableWindow(bEnable);
  GetDlgItem(IDC_MONTH)->EnableWindow(bEnable);
  GetDlgItem(IDC_YEAR)->EnableWindow(bEnable);
  m_ctrlMonth.EnableWindow(bEnable);
  #ifdef _WIN32
    m_ctrlSpinYear.EnableWindow(bEnable);
    m_ctrlSpinDay.EnableWindow(bEnable);
  #endif
}


void CCDateDlg::SetValue(const CDate& value)
{
  m_bInValid = !value.IsValid();
  if (!m_bInValid)
  {
    m_nDay = value.GetDay();
    m_nMonth = value.GetMonth();
    m_lYear = value.GetYear();
  }
}


CDate CCDateDlg::GetValue()
{
  CDate rVal;
  if (!m_bInValid)
  {
    #ifdef _DEBUG
    BOOL bOldDoAsserts = CDate::SetDoConstructorAsserts(FALSE);
    #endif
    rVal = CDate(m_lYear, (WORD) m_nMonth, (WORD) m_nDay);
    #ifdef _DEBUG
    CDate::SetDoConstructorAsserts(bOldDoAsserts);
    #endif
  }

  return rVal;
}


CCLTimeOfDayDlg::CCLTimeOfDayDlg()
{
  m_nHour = 0;
  m_nMinute = 0;
  m_nSecond = 0;
  m_nMilliSecond = 0;
  m_bInValid = FALSE;
}


CCLTimeOfDayDlg::CCLTimeOfDayDlg(CWnd* pParent, DWORD dwFlags)
  : CDTDialog(IDD_CLTIMEOFDAY_WITHOUT_PIN, pParent)
{
  //DT_PUSHPIN & DT_CLOSEONDEACTIVE should be used with DT_MODELESS only
  if (dwFlags & DT_PUSHPIN)
    ASSERT(dwFlags & DT_MODELESS);
  if (dwFlags & DT_CLOSEONDEACTIVE)
    ASSERT(dwFlags & DT_MODELESS);

  //{{AFX_DATA_INIT(CCLTimeOfDayDlg)
  m_nHour = 0;
  m_nMinute = 0;
  m_nSecond = 0;
  m_nMilliSecond = 0;
  m_bInValid = FALSE;
  //}}AFX_DATA_INIT
  m_dwFlags = dwFlags;
}


BOOL CCLTimeOfDayDlg::Create(CWnd* pParent, DWORD dwFlags)
{
  //should only be created modeless when DT_MODELESS flag is used
  ASSERT(dwFlags & DT_MODELESS);

  m_pParentWnd = pParent;
  m_dwFlags = dwFlags;

  UINT nIDTemplate = IDD_CLTIMEOFDAY_WITHOUT_PIN;
  if (dwFlags & DT_PUSHPIN)
    nIDTemplate = IDD_CLTIMEOFDAY;

  return CDTDialog::Create(nIDTemplate, pParent);
}


void CCLTimeOfDayDlg::DoDataExchange(CDataExchange* pDX)
{
  CDTDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CCLTimeOfDayDlg)
  #ifdef _WIN32
    DDX_Control(pDX, IDC_UPDOWN_HOUR, m_ctrlSpinHour);
    DDX_Control(pDX, IDC_UPDOWN_MINUTE, m_ctrlSpinMinute);
    DDX_Control(pDX, IDC_UPDOWN_SECOND, m_ctrlSpinSecond);
    DDX_Control(pDX, IDC_UPDOWN_MILLISECOND, m_ctrlSpinMilliSecond);
  #endif
  DDX_Control(pDX, IDC_INVALID, m_ctrlInvalid);
  DDX_Check(pDX, IDC_INVALID, m_bInValid);
  //}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate || (pDX->m_bSaveAndValidate && !m_bInValid))
  {
    DDX_Text(pDX, IDC_HOUR, m_nHour);
    DDV_MinMaxUInt(pDX, m_nHour, 0, 23);
    DDX_Text(pDX, IDC_MINUTE, m_nMinute);
    DDV_MinMaxUInt(pDX, m_nMinute, 0, 59);
    DDX_Text(pDX, IDC_SECOND, m_nSecond);
    DDV_MinMaxUInt(pDX, m_nSecond, 0, 59);
    DDX_Text(pDX, IDC_MILLISECOND, m_nMilliSecond);
    DDV_MinMaxUInt(pDX, m_nMilliSecond, 0, 999);  
  }

  if (!pDX->m_bSaveAndValidate)
    OnInvalid();
}


BOOL CCLTimeOfDayDlg::OnInitDialog() 
{
  BOOL rval = CDTDialog::OnInitDialog();
  #ifdef _WIN32
    m_ctrlSpinHour.SetRange(0, 23);
    m_ctrlSpinMinute.SetRange(0, 59);
    m_ctrlSpinSecond.SetRange(0, 59);
    m_ctrlSpinMilliSecond.SetRange(0, 999);
  #endif

  //disable the invalid check box if required
  if (m_dwFlags & DT_ONLYVALID)
    m_ctrlInvalid.EnableWindow(FALSE);

  //disable the millisecond edit if required
  if (m_dwFlags & DT_NOMILLISECOND)
  {
    GetDlgItem(IDC_MILLISECOND)->EnableWindow(FALSE);
    #ifdef _WIN32
      m_ctrlSpinMilliSecond.EnableWindow(FALSE);
    #endif  
    GetDlgItem(IDC_MILLISECOND_PRMPT)->EnableWindow(FALSE);
  }

  return rval;
}


void CCLTimeOfDayDlg::OnInvalid() 
{
  BOOL bEnable = !m_ctrlInvalid.GetCheck();
  GetDlgItem(IDC_HOUR_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MINUTE_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_SECOND_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MILLISECOND_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_HOUR)->EnableWindow(bEnable);
  GetDlgItem(IDC_MINUTE)->EnableWindow(bEnable);
  GetDlgItem(IDC_SECOND)->EnableWindow(bEnable);
  GetDlgItem(IDC_MILLISECOND)->EnableWindow(bEnable);
  #ifdef _WIN32
    m_ctrlSpinHour.EnableWindow(bEnable);
    m_ctrlSpinMinute.EnableWindow(bEnable);
    m_ctrlSpinSecond.EnableWindow(bEnable);
    m_ctrlSpinMilliSecond.EnableWindow(bEnable);
  #endif
}


void CCLTimeOfDayDlg::SetValue(const CLTimeOfDay& value)
{
  m_bInValid = !value.IsValid();
  if (!m_bInValid)
  {
    m_nHour = value.GetHour();
    m_nMinute = value.GetMinute();
    m_nSecond = value.GetSecond();
    m_nMilliSecond = value.GetMilliSecond();
  }
}


CLTimeOfDay CCLTimeOfDayDlg::GetValue()
{
  CLTimeOfDay rVal;
  if (!m_bInValid)
  {
    #ifdef _DEBUG
    BOOL bOldDoAsserts = CLTimeOfDay::SetDoConstructorAsserts(FALSE);
    #endif
    rVal = CLTimeOfDay((WORD) m_nHour, (WORD) m_nMinute, (WORD) m_nSecond, (WORD) m_nMilliSecond);
    #ifdef _DEBUG
    CLTimeOfDay::SetDoConstructorAsserts(bOldDoAsserts);
    #endif
  }

  return rVal;
}


CCLTimeSpanDlg::CCLTimeSpanDlg()
{
  m_lDay = 0;
  m_nHour = 0;
  m_nMinute = 0;
  m_nSecond = 0;
  m_nMilliSecond = 0;
  m_bInValid = FALSE;
}


CCLTimeSpanDlg::CCLTimeSpanDlg(CWnd* pParent, DWORD dwFlags)
  : CDTDialog(IDD_CLTIMESPAN_WITHOUT_PIN, pParent)
{
  //DT_PUSHPIN & DT_CLOSEONDEACTIVE should be used with DT_MODELESS only
  if (dwFlags & DT_PUSHPIN)
    ASSERT(dwFlags & DT_MODELESS);
  if (dwFlags & DT_CLOSEONDEACTIVE)
    ASSERT(dwFlags & DT_MODELESS);

  //{{AFX_DATA_INIT(CCLTimeOfDayDlg)
  m_lDay = 0;
  m_nHour = 0;
  m_nMinute = 0;
  m_nSecond = 0;
  m_nMilliSecond = 0;
  m_bInValid = FALSE;
  //}}AFX_DATA_INIT
  m_dwFlags = dwFlags;
}


BOOL CCLTimeSpanDlg::Create(CWnd* pParent, DWORD dwFlags)
{
  //should only be created modeless when DT_MODELESS flag is used
  ASSERT(dwFlags & DT_MODELESS);

  m_pParentWnd = pParent;
  m_dwFlags = dwFlags;

  UINT nIDTemplate = IDD_CLTIMESPAN_WITHOUT_PIN;
  if (dwFlags & DT_PUSHPIN)
    nIDTemplate = IDD_CLTIMESPAN;

  return CDTDialog::Create(nIDTemplate, pParent);
}


void CCLTimeSpanDlg::DoDataExchange(CDataExchange* pDX)
{
  CDTDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CCLTimeSpanDlg)
  #ifdef _WIN32
    DDX_Control(pDX, IDC_UPDOWN_DAY3, m_ctrlSpinDay);
    DDX_Control(pDX, IDC_UPDOWN_HOUR3, m_ctrlSpinHour);
    DDX_Control(pDX, IDC_UPDOWN_MINUTE3, m_ctrlSpinMinute);
    DDX_Control(pDX, IDC_UPDOWN_SECOND3, m_ctrlSpinSecond);
    DDX_Control(pDX, IDC_UPDOWN_MILLISECOND3, m_ctrlSpinMilliSecond);
  #endif
  DDX_Control(pDX, IDC_INVALID, m_ctrlInvalid);
  DDX_Check(pDX, IDC_INVALID, m_bInValid);
  //}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate || (pDX->m_bSaveAndValidate && !m_bInValid))
  {
    DDX_Text(pDX, IDC_DAY, m_lDay);
    DDX_Text(pDX, IDC_HOUR, m_nHour);
    DDV_MinMaxUInt(pDX, m_nHour, 0, 23);
    DDX_Text(pDX, IDC_MINUTE, m_nMinute);
    DDV_MinMaxUInt(pDX, m_nMinute, 0, 59);
    DDX_Text(pDX, IDC_SECOND, m_nSecond);
    DDV_MinMaxUInt(pDX, m_nSecond, 0, 59);
    DDX_Text(pDX, IDC_MILLISECOND, m_nMilliSecond);
    DDV_MinMaxUInt(pDX, m_nMilliSecond, 0, 999);  
  }
  
  if (!pDX->m_bSaveAndValidate)
    OnInvalid();
}


BOOL CCLTimeSpanDlg::OnInitDialog() 
{
  BOOL rval = CDTDialog::OnInitDialog();
  #ifdef _WIN32
    m_ctrlSpinDay.SetRange(UD_MINVAL, UD_MAXVAL);
    m_ctrlSpinHour.SetRange(0, 23);
    m_ctrlSpinMinute.SetRange(0, 59);
    m_ctrlSpinSecond.SetRange(0, 59);
    m_ctrlSpinMilliSecond.SetRange(0, 999);
  #endif

  //disable the invalid check box if required
  if (m_dwFlags & DT_ONLYVALID)
    m_ctrlInvalid.EnableWindow(FALSE);

  //disable the millisecond edit if required
  if (m_dwFlags & DT_NOMILLISECOND)
  {
    GetDlgItem(IDC_MILLISECOND)->EnableWindow(FALSE);
    #ifdef _WIN32
      m_ctrlSpinMilliSecond.EnableWindow(FALSE);
    #endif
    GetDlgItem(IDC_MILLISECOND_PRMPT)->EnableWindow(FALSE);
  }

  return rval;
}


void CCLTimeSpanDlg::OnInvalid() 
{
  BOOL bEnable = !m_ctrlInvalid.GetCheck();
  GetDlgItem(IDC_DAY_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_HOUR_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MINUTE_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_SECOND_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MILLISECOND_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_DAY)->EnableWindow(bEnable);
  GetDlgItem(IDC_HOUR)->EnableWindow(bEnable);
  GetDlgItem(IDC_MINUTE)->EnableWindow(bEnable);
  GetDlgItem(IDC_SECOND)->EnableWindow(bEnable);
  GetDlgItem(IDC_MILLISECOND)->EnableWindow(bEnable);
  #ifdef _WIN32
    m_ctrlSpinDay.EnableWindow(bEnable);
    m_ctrlSpinHour.EnableWindow(bEnable);
    m_ctrlSpinMinute.EnableWindow(bEnable);
    m_ctrlSpinSecond.EnableWindow(bEnable);
    m_ctrlSpinMilliSecond.EnableWindow(bEnable);
  #endif
}


void CCLTimeSpanDlg::SetValue(const CLTimeSpan& value)
{
  m_bInValid = !value.IsValid();
  if (!m_bInValid)
  {
    m_lDay = value.GetTotalDays();
    m_nHour = value.GetHours();
    m_nMinute = value.GetMinutes();
    m_nSecond = value.GetSeconds();
    m_nMilliSecond = value.GetMilliSeconds();
  }
}


CLTimeSpan CCLTimeSpanDlg::GetValue()
{
  CLTimeSpan rVal;
  if (!m_bInValid)
  {
    #ifdef _DEBUG
    BOOL bOldDoAsserts = CLTimeSpan::SetDoConstructorAsserts(FALSE);
    #endif
    rVal = CLTimeSpan(m_lDay, (WORD) m_nHour, (WORD) m_nMinute, (WORD) m_nSecond, (WORD) m_nMilliSecond);
    #ifdef _DEBUG
    CLTimeSpan::SetDoConstructorAsserts(bOldDoAsserts);
    #endif
  }

  return rVal;
}


CCLDateDlg::CCLDateDlg()
{
  m_nHour = 0;
  m_nMinute = 0;
  m_nSecond = 0;
  m_nMilliSecond = 0;
  m_bInValid = FALSE;
  m_nDay = 1;
  m_lYear = CDate::CurrentYear();
  m_nMonth = 1;
  m_nTimeFrame = 0;
}


CCLDateDlg::CCLDateDlg(CWnd* pParent, DWORD dwFlags)
  : CDTDialog(IDD_CLDATE_WITHOUT_PIN, pParent)
{
  //DT_PUSHPIN & DT_CLOSEONDEACTIVE should be used with DT_MODELESS only
  if (dwFlags & DT_PUSHPIN)
    ASSERT(dwFlags & DT_MODELESS);
  if (dwFlags & DT_CLOSEONDEACTIVE)
    ASSERT(dwFlags & DT_MODELESS);

  //{{AFX_DATA_INIT(CCLDateDlg)
  m_nHour = 0;
  m_nMinute = 0;
  m_nSecond = 0;
  m_nMilliSecond = 0;
  m_nDay = 0;
  m_lYear = 0;
  m_bInValid = FALSE;
  //}}AFX_DATA_INIT
  m_nDay = 1;
  m_lYear = CDate::CurrentYear();
  m_nMonth = 1;
  m_nTimeFrame = 0;
  m_dwFlags = dwFlags;
}


BOOL CCLDateDlg::Create(CWnd* pParent, DWORD dwFlags)
{
  //should only be created modeless when DT_MODELESS flag is used
  ASSERT(dwFlags & DT_MODELESS);

  m_pParentWnd = pParent;
  m_dwFlags = dwFlags;

  UINT nIDTemplate = IDD_CLDATE_WITHOUT_PIN;
  if (dwFlags & DT_PUSHPIN)
    nIDTemplate = IDD_CLDATE;

  return CDTDialog::Create(nIDTemplate, pParent);
}


void CCLDateDlg::DoDataExchange(CDataExchange* pDX)
{
  CDTDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CCLDateDlg)
  DDX_Control(pDX, IDC_TIMEFRAME, m_ctrlTimeFrame);
  #ifdef _WIN32
    DDX_Control(pDX, IDC_UPDOWN_HOUR2, m_ctrlSpinHour);
    DDX_Control(pDX, IDC_UPDOWN_MINUTE2, m_ctrlSpinMinute);
    DDX_Control(pDX, IDC_UPDOWN_SECOND2, m_ctrlSpinSecond);
    DDX_Control(pDX, IDC_UPDOWN_MILLISECOND2, m_ctrlSpinMilliSecond);
    DDX_Control(pDX, IDC_UPDOWN_YEAR2, m_ctrlSpinYear);
    DDX_Control(pDX, IDC_UPDOWN_DAY2, m_ctrlSpinDay);  
  #endif
  DDX_Control(pDX, IDC_INVALID, m_ctrlInvalid);
  DDX_Control(pDX, IDC_MONTH, m_ctrlMonth);
  DDX_Check(pDX, IDC_INVALID, m_bInValid);
  //}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate || (pDX->m_bSaveAndValidate && !m_bInValid))
  {
    DDX_Text(pDX, IDC_HOUR, m_nHour);
    DDV_MinMaxUInt(pDX, m_nHour, 0, 23);
    DDX_Text(pDX, IDC_MINUTE, m_nMinute);
    DDV_MinMaxUInt(pDX, m_nMinute, 0, 59);
    DDX_Text(pDX, IDC_SECOND, m_nSecond);
    DDV_MinMaxUInt(pDX, m_nSecond, 0, 59);
    DDX_Text(pDX, IDC_MILLISECOND, m_nMilliSecond);
    DDV_MinMaxUInt(pDX, m_nMilliSecond, 0, 999);  
    DDX_Text(pDX, IDC_YEAR, m_lYear);
    DDX_Text(pDX, IDC_DAY, m_nDay);
  }

  if (pDX->m_bSaveAndValidate)
  {
    m_nMonth = m_ctrlMonth.GetCurSel() + 1;
    m_nTimeFrame = m_ctrlTimeFrame.GetCurSel();
  }
  else
  {
    m_ctrlMonth.SetCurSel(m_nMonth-1);
    m_ctrlTimeFrame.SetCurSel(m_nTimeFrame);
    OnInvalid();
  }

  DDV_MinMaxUInt(pDX, m_nDay, 1, (UINT) CDate::DaysInMonth((WORD) m_nMonth, CDate::IsLeap(m_lYear)));
}


BOOL CCLDateDlg::OnInitDialog() 
{
  //Add the month strings
  CComboBox* pMonthCombo = (CComboBox*) GetDlgItem(IDC_MONTH);
  for (WORD i=1; i<13; i++)
    pMonthCombo->AddString(CDate::GetFullStringMonth(i));

  //Add the time frame strings (ordering is important)
  CString sTimeFrame;
  CComboBox* pTimeFrameCombo = (CComboBox*) GetDlgItem(IDC_TIMEFRAME);
  if (!sTimeFrame.LoadString(IDS_UTC))
    ASSERT(FALSE);
  pTimeFrameCombo->AddString(sTimeFrame);

  if (!sTimeFrame.LoadString(IDS_ET))
    ASSERT(FALSE);
  pTimeFrameCombo->AddString(sTimeFrame);

  if (!sTimeFrame.LoadString(IDS_LOCAL))
    ASSERT(FALSE);
  pTimeFrameCombo->AddString(sTimeFrame);

  //Call up to the parent
  BOOL rval = CDTDialog::OnInitDialog();

  #ifdef _WIN32
    m_ctrlSpinHour.SetRange(0, 23);
    m_ctrlSpinMinute.SetRange(0, 59);
    m_ctrlSpinSecond.SetRange(0, 59);
    m_ctrlSpinMilliSecond.SetRange(0, 999);
    m_ctrlSpinYear.SetRange(UD_MINVAL, UD_MAXVAL);
    m_ctrlSpinDay.SetRange(1, 31);
  #endif

  //disable the invalid check box if required
  if (m_dwFlags & DT_ONLYVALID)
    m_ctrlInvalid.EnableWindow(FALSE);

  //disable the millisecond edit if required
  if (m_dwFlags & DT_NOMILLISECOND)
  {
    GetDlgItem(IDC_MILLISECOND)->EnableWindow(FALSE);
    #ifdef _WIN32
      m_ctrlSpinMilliSecond.EnableWindow(FALSE);
    #endif  
    GetDlgItem(IDC_MILLISECOND_PRMPT)->EnableWindow(FALSE);
  }

  return rval;
}


void CCLDateDlg::OnInvalid() 
{
  BOOL bEnable = !m_ctrlInvalid.GetCheck();
  GetDlgItem(IDC_DAY_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MONTH_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_YEAR_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_HOUR_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MINUTE_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_SECOND_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_MILLISECOND_PRMPT)->EnableWindow(bEnable);
  GetDlgItem(IDC_DAY)->EnableWindow(bEnable);
  GetDlgItem(IDC_MONTH)->EnableWindow(bEnable);
  GetDlgItem(IDC_YEAR)->EnableWindow(bEnable);
  GetDlgItem(IDC_HOUR)->EnableWindow(bEnable);
  GetDlgItem(IDC_MINUTE)->EnableWindow(bEnable);
  GetDlgItem(IDC_SECOND)->EnableWindow(bEnable);
  GetDlgItem(IDC_MILLISECOND)->EnableWindow(bEnable);
  GetDlgItem(IDC_TIMEFRAME_PRMPT)->EnableWindow(bEnable);
  m_ctrlMonth.EnableWindow(bEnable);
  #ifdef _WIN32
    m_ctrlSpinYear.EnableWindow(bEnable);
    m_ctrlSpinDay.EnableWindow(bEnable);
    m_ctrlSpinHour.EnableWindow(bEnable);
    m_ctrlSpinMinute.EnableWindow(bEnable);
    m_ctrlSpinSecond.EnableWindow(bEnable);
    m_ctrlSpinMilliSecond.EnableWindow(bEnable);
  #endif
  m_ctrlTimeFrame.EnableWindow(bEnable);
}


void CCLDateDlg::SetValue(const CLDate& value)
{
  //should be optimised
  m_bInValid = !value.IsValid();
  if (!m_bInValid)
  {
    m_nDay = value.GetCDate().GetDay();
    m_nMonth = value.GetCDate().GetMonth();
    m_lYear = value.GetCDate().GetYear();
    m_nHour = value.GetCLTimeOfDay().GetHour();
    m_nMinute = value.GetCLTimeOfDay().GetMinute();
    m_nSecond = value.GetCLTimeOfDay().GetSecond();
    m_nMilliSecond = value.GetCLTimeOfDay().GetMilliSecond();
    m_nTimeFrame = value.GetTimeFrame();
  }
}


CLDate CCLDateDlg::GetValue()
{
  CLDate rVal;
  if (!m_bInValid)
  {
    #ifdef _DEBUG
    BOOL bOldDoAsserts = CLDate::SetDoConstructorAsserts(FALSE);
    #endif
    rVal = CLDate(m_lYear, (WORD) m_nMonth, (WORD) m_nDay, (WORD) m_nHour, (WORD) m_nMinute,
                 (WORD) m_nSecond, (WORD) m_nMilliSecond, (TimeFrame) m_nTimeFrame);
    #ifdef _DEBUG
    CLDate::SetDoConstructorAsserts(bOldDoAsserts);
    #endif
  }

  return rVal;
}


CDateButton::CDateButton()
{
  m_pBuddy = NULL;
  m_bFirstCall = TRUE;
}


CDateButton::~CDateButton()
{
}


void CDateButton::SetBuddy(CWnd* pBuddy)
{
  m_pBuddy = pBuddy;
}


BOOL CDateButton::PreTranslateMessage(MSG* pMsg) 
{                     
  #ifdef _WIN32
    //create the tooltip
    if (m_bFirstCall)
    {
      m_ToolTip.Create(this);
      m_ToolTip.Activate(TRUE);
      m_ToolTip.AddTool(this, IDS_TT_MODIFY);
      m_bFirstCall = FALSE;
    }
    
    //give the tooltip a chance to handle the message
    m_ToolTip.RelayEvent(pMsg);
  #endif

  return CButton::PreTranslateMessage(pMsg);
}


void CDateButton::OnClicked() 
{
  if (m_pBuddy)
    m_pBuddy->PostMessage(UWM_BN_CLICKED);
  else
    TRACE0("CDateButton: No auto buddy defined\n");
}                        

                     
LRESULT CDateButton::OnMyReflectedClicked(WPARAM /*wParam*/, LPARAM /*lParam*/)
{   
  OnClicked();                                                    
  return 0;
}


LRESULT CDateButton::OnDlgClose(WPARAM wParam, LPARAM lParam) 
{
  LRESULT lresult = 0L;

  if (m_pBuddy)
    lresult = m_pBuddy->PostMessage(UWM_DLG_CLOSE, wParam, lParam);
  else
    TRACE0("CDateButton: No auto buddy defined\n");

  return lresult;
}


CDateTimeControl::CDateTimeControl()
{
  m_bSubclassed = FALSE;
}


CDateTimeControl::~CDateTimeControl()
{
}


BOOL CDateTimeControl::SubclassEdit(UINT iCtlID, CWnd* pParentWnd)
{
  //test our inputs
  ASSERT(this);
  if (!iCtlID || ! pParentWnd)
  {
    ASSERT(FALSE);
    TRACE0("CDateTimeControl::SubclassEdit -- Control iD or parent window class is invalid!\n");
    return FALSE;
  }                
  
  //this can only work if it's on a form view or dialog
  if (pParentWnd->IsKindOf(RUNTIME_CLASS(CFormView)) ||
     pParentWnd->IsKindOf(RUNTIME_CLASS(CDialog)))
  {
    //subclass the control
    if (SubclassDlgItem(iCtlID, pParentWnd))
    {
      m_bSubclassed = TRUE;

      //This control can only be used with a read only edit control
      LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
      if (!(lStyle & ES_READONLY))
      {
        TRACE0("CDateTimeControl::SubclassEdit -- ES_READONLY style should be set for the edit control\n");
        ASSERT(FALSE);
        return FALSE;
      }

      return AddEditButton();
    }
    else
    {
      TRACE0("CDateTimeControl::SubclassEdit -- Could not subclass edit control!\n");
      ASSERT(FALSE);
      return FALSE;
    }
  }
  else    //parent is not of CDialog or CFormView class
  {  
    TRACE0("CDateTimeControl::SubclassEdit -- Parent class is not a CFormView or CDialog!\n");
    return FALSE;
  }  
}


BOOL CDateTimeControl::SubclassEdit(HWND hEdit)
{   
  //test our inputs
  ASSERT(this);
  if (!IsWindow(hEdit))
  {
    ASSERT(FALSE);
    TRACE0("CDateTimeControl::SubclassEdit -- window handle is invalid!\n");
    return FALSE;
  }                
  
  //subclass the control
  if (SubclassWindow(hEdit))
  {
    m_bSubclassed = TRUE;
    
    //This control can only be used with a read only edit control
    LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
    if (!(lStyle & ES_READONLY))
    {
      TRACE0("CDateTimeControl::SubclassEdit -- ES_READONLY style should be set for the edit control\n");
      return FALSE;
    }

    return AddEditButton();
  }
  else
  {
    TRACE0("CDateTimeControl::SubclassEdit -- Could not subclass static control!\n");
    return FALSE;
  }
}


BOOL CDateTimeControl::AddEditButton()
{
  CRect Rect;
  GetWindowRect(Rect);
  GetParent()->ScreenToClient(Rect);
  Rect.left = Rect.right;
  Rect.right = Rect.left + (Rect.Height()*8/10);  //width is 8/10 of height

  //dynamically create the edit control
  CString sEditControlText;
  if (!sEditControlText.LoadString(IDS_EDIT_TEXT))
    ASSERT(FALSE);
  BOOL bSuccess = m_Edit.Create(sEditControlText, WS_VISIBLE | WS_CHILD | WS_GROUP, 
                                Rect, GetParent(), DTIME_EDIT_CONTROL_ID);

  //tell the button to send click notifications to this window
  m_Edit.SetBuddy(this);

  //ensure it is using the same font as the parent
  m_Edit.SetFont(GetParent()->GetFont());

  return bSuccess;
}


CDateControl::CDateControl()
{
  m_pDlg = NULL;
}


CDateControl::~CDateControl()
{
}


LRESULT CDateControl::OnEditClick(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
  if (m_dwFlags & DT_MODELESS)
  {
    if (m_pDlg == NULL)
    {
      m_pDlg = new CCDateDlg;
      if (m_pDlg)
      {
        m_pDlg->SetValue(m_Value);
        m_pDlg->Create(&m_Edit, m_dwFlags); 
      }
    } 
    else
      TRACE0("Drop down dialog already visible\n");
  }
  else if (m_dwFlags & DT_MODAL)
  {
    CCDateDlg dlg(&m_Edit, m_dwFlags);
    dlg.SetValue(m_Value);
    if (dlg.DoModal() == IDOK)
    {
      CDate val = dlg.GetValue();
      SetWindowText(val.Format());
      m_Value = val;
    }
  }
  else
    ASSERT(FALSE);  //DT_MODELESS or DT_MODAL must be used

  return 0;
}


LRESULT CDateControl::OnDlgClose(WPARAM wParam, LPARAM /*lParam*/)
{
  if (wParam == 1)
  {
    CDate val = m_pDlg->GetValue();
    SetWindowText(val.Format());
    m_Value = val;
  }

  delete m_pDlg;
  m_pDlg = NULL;

  return 0;
}


void CDateControl::SetValue(const CDate& value)
{
  m_Value = value;
  SetWindowText(m_Value.Format());
}


CLTimeSpanControl::CLTimeSpanControl()
{
  m_pDlg = NULL;
}


CLTimeSpanControl::~CLTimeSpanControl()
{
}


LRESULT CLTimeSpanControl::OnEditClick(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
  if (m_dwFlags & DT_MODELESS)
  {
    if (m_pDlg == NULL)
    {
      m_pDlg = new CCLTimeSpanDlg;
      if (m_pDlg)
      {
        m_pDlg->SetValue(m_Value);
        m_pDlg->Create(&m_Edit, m_dwFlags); 
      }                          
      else
        TRACE0("Drop down dialog already visible\n");
    }
  }
  else if (m_dwFlags & DT_MODAL)
  {
    CCLTimeSpanDlg dlg(&m_Edit, m_dwFlags);
    dlg.SetValue(m_Value);
    if (dlg.DoModal() == IDOK)
    {
      CLTimeSpan val = dlg.GetValue();
      SetWindowText(val.Format());
      m_Value = val;
    }
  }
  else
    ASSERT(FALSE);  //DT_MODELESS or DT_MODAL must be used

  return 0;
}


LRESULT CLTimeSpanControl::OnDlgClose(WPARAM wParam, LPARAM /*lParam*/)
{
  if (wParam == 1)
  {
    CLTimeSpan val = m_pDlg->GetValue();
    SetWindowText(val.Format());
    m_Value = val;
  }

  delete m_pDlg;
  m_pDlg = NULL;

  return 0;
}


void CLTimeSpanControl::SetValue(const CLTimeSpan& value)
{
  m_Value = value;
  SetWindowText(m_Value.Format());
}


CLTimeOfDayControl::CLTimeOfDayControl()
{
  m_pDlg = NULL;
}


CLTimeOfDayControl::~CLTimeOfDayControl()
{
}


LRESULT CLTimeOfDayControl::OnEditClick(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
  if (m_dwFlags & DT_MODELESS)
  {
    if (m_pDlg == NULL)
    {
      m_pDlg = new CCLTimeOfDayDlg;
      if (m_pDlg)
      {
        m_pDlg->SetValue(m_Value);
        m_pDlg->Create(&m_Edit, m_dwFlags); 
      }                           
      else
        TRACE0("Drop down dialog already visible\n");
    }
  }
  else if (m_dwFlags & DT_MODAL)
  {
    CCLTimeOfDayDlg dlg(&m_Edit, m_dwFlags);
    dlg.SetValue(m_Value);
    if (dlg.DoModal() == IDOK)
    {
      CLTimeOfDay val = dlg.GetValue();
      SetWindowText(val.Format());
      m_Value = val;
    }
  }
  else
    ASSERT(FALSE);  //DT_MODELESS or DT_MODAL must be used

  return 0;
}


LRESULT CLTimeOfDayControl::OnDlgClose(WPARAM wParam, LPARAM /*lParam*/)
{
  if (wParam == 1)
  {
    CLTimeOfDay val = m_pDlg->GetValue();
    SetWindowText(val.Format());
    m_Value = val;
  }

  delete m_pDlg;
  m_pDlg = NULL;

  return 0;
}


void CLTimeOfDayControl::SetValue(const CLTimeOfDay& value)
{
  m_Value = value;
  SetWindowText(m_Value.Format());
}


CLDateControl::CLDateControl()
{
  m_pDlg = NULL;
}


CLDateControl::~CLDateControl()
{
}


LRESULT CLDateControl::OnEditClick(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
  if (m_dwFlags & DT_MODELESS)
  {
    if (m_pDlg == NULL)
    {
      m_pDlg = new CCLDateDlg;
      if (m_pDlg)
      {
        m_pDlg->SetValue(m_Value);
        m_pDlg->Create(&m_Edit, m_dwFlags); 
      }                      
      else
        TRACE0("Drop down dialog already visible\n");
    }
  }
  else if (m_dwFlags & DT_MODAL)
  {
    CCLDateDlg dlg(&m_Edit, m_dwFlags);
    dlg.SetValue(m_Value);
    if (dlg.DoModal() == IDOK)
    {
      CLDate val = dlg.GetValue();
      SetWindowText(val.Format());
      m_Value = val;
    }
  }
  else
    ASSERT(FALSE);  //DT_MODELESS or DT_MODAL must be used


  return 0;
}


LRESULT CLDateControl::OnDlgClose(WPARAM wParam, LPARAM /*lParam*/)
{
  if (wParam == 1)
  {
    CLDate val = m_pDlg->GetValue();
    SetWindowText(val.Format());
    m_Value = val;
  }

  delete m_pDlg;
  m_pDlg = NULL;

  return 0;
}


void CLDateControl::SetValue(const CLDate& value)
{
  m_Value = value;
  SetWindowText(m_Value.Format());
}


void DDX_CDateControl(CDataExchange* pDX, int nIDC, CDateControl& rCDateControl, DWORD dwFlags)
{ 
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCDateControl.m_hWnd == NULL)    // not subclassed yet
  {
    if (!rCDateControl.SubclassEdit(hWndCtrl))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
    else
      rCDateControl.SetFlags(dwFlags);
  }
}


void DDX_CLTimeSpanControl(CDataExchange* pDX, int nIDC, CLTimeSpanControl& rCLTimeSpanControl, DWORD dwFlags)
{
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCLTimeSpanControl.m_hWnd == NULL)    // not subclassed yet
  {
    if (!rCLTimeSpanControl.SubclassEdit(hWndCtrl))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
    else
      rCLTimeSpanControl.SetFlags(dwFlags);
  }
}


void DDX_CLTimeOfDayControl(CDataExchange* pDX, int nIDC, CLTimeOfDayControl& rCLTimeOfDayControl, DWORD dwFlags)
{
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCLTimeOfDayControl.m_hWnd == NULL)    // not subclassed yet
  {
    if (!rCLTimeOfDayControl.SubclassEdit(hWndCtrl))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
    else
      rCLTimeOfDayControl.SetFlags(dwFlags);
  }
}


void DDX_CLDateControl(CDataExchange* pDX, int nIDC, CLDateControl& rCLDateControl, DWORD dwFlags)
{
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCLDateControl.m_hWnd == NULL)    // not subclassed yet
  {
    if (!rCLDateControl.SubclassEdit(hWndCtrl))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
    else
      rCLDateControl.SetFlags(dwFlags);
  }
}


void DDX_CDate(CDataExchange* pDX, CDateControl& rCDateStatic, CDate& value)
{
  if (rCDateStatic.m_hWnd != NULL)
  {
    if (pDX->m_bSaveAndValidate)
    {
      rCDateStatic.GetValue(value);
    }
    else
    {
      rCDateStatic.SetValue(value);
    }
  }
}


void DDX_CLTimeSpan(CDataExchange* pDX, CLTimeSpanControl& rCLTimeSpanControl, CLTimeSpan& value)
{
  if (rCLTimeSpanControl.m_hWnd != NULL)
  {
    if (pDX->m_bSaveAndValidate)
    {
      rCLTimeSpanControl.GetValue(value);
    }
    else
    {
      rCLTimeSpanControl.SetValue(value);
    }
  }
}


void DDX_CLTimeOfDay(CDataExchange* pDX, CLTimeOfDayControl& rCLTimeOfDayControl, CLTimeOfDay& value)
{
  if (rCLTimeOfDayControl.m_hWnd != NULL)
  {
    if (pDX->m_bSaveAndValidate)
    {
      rCLTimeOfDayControl.GetValue(value);
    }
    else
    {
      rCLTimeOfDayControl.SetValue(value);
    }
  }
}


void DDX_CLDate(CDataExchange* pDX, CLDateControl& rCLDateControl, CLDate& value)
{
  if (rCLDateControl.m_hWnd != NULL)
  {
    if (pDX->m_bSaveAndValidate)
    {
      rCLDateControl.GetValue(value);
    }
    else
    {
      rCLDateControl.SetValue(value);
    }
  }
}


void DDV_MinMaxCDate(CDataExchange* pDX, CDate& value, CDate& minVal, CDate& maxVal)
{
  ASSERT(value.IsValid() && minVal.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && ((value < minVal) || (value > maxVal)))
  {
    AfxMessageBox(IDS_INVALID_DATE_RANGE, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_DATE_RANGE);
    pDX->Fail();
  }
}


void DDV_GreaterThanCDate(CDataExchange* pDX, CDate& value, CDate& minVal)
{
  ASSERT(value.IsValid() && minVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value < minVal))
  {
    AfxMessageBox(IDS_INVALID_DATE_MIN, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_DATE_MIN);
    pDX->Fail();
  }
}


void DDV_LessThanCDate(CDataExchange* pDX, CDate& value, CDate& maxVal)
{
  ASSERT(value.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value > maxVal))
  {
    AfxMessageBox(IDS_INVALID_DATE_MAX, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_DATE_MAX);
    pDX->Fail();
  }
}


void DDV_MinMaxCLTimeSpan(CDataExchange* pDX, CLTimeSpan& value, CLTimeSpan& minVal, CLTimeSpan& maxVal)
{
  ASSERT(value.IsValid() && minVal.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && ((value < minVal) || (value > maxVal)))
  {
    AfxMessageBox(IDS_INVALID_TIMESPAN_RANGE, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_TIMESPAN_RANGE);
    pDX->Fail();
  }
}


void DDV_GreaterThanCLTimeSpan(CDataExchange* pDX, CLTimeSpan& value, CLTimeSpan& minVal)
{
  ASSERT(value.IsValid() && minVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value < minVal))
  {
    AfxMessageBox(IDS_INVALID_TIMESPAN_MIN, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_TIMESPAN_MIN);
    pDX->Fail();
  }
}


void DDV_LessThanCLTimeSpan(CDataExchange* pDX, CLTimeSpan& value, CLTimeSpan& maxVal)
{
  ASSERT(value.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value > maxVal))
  {
    AfxMessageBox(IDS_INVALID_TIMESPAN_MAX, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_TIMESPAN_MAX);
    pDX->Fail();
  }
}


void DDV_IsValidCLTimeSpan(CDataExchange* pDX, CLTimeSpan& value)
{
  if (pDX->m_bSaveAndValidate && (!value.IsValid()))
  {
    AfxMessageBox(IDS_INVALID_TIMESPAN, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_TIMESPAN);
    pDX->Fail();
  }
}


void DDV_MinMaxCLTimeOfDay(CDataExchange* pDX, CLTimeOfDay& value, CLTimeOfDay& minVal, CLTimeOfDay& maxVal)
{
  ASSERT(value.IsValid() && minVal.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && ((value < minVal) || (value > maxVal)))
  {
    AfxMessageBox(IDS_INVALID_TIMEOFDAY_RANGE, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_TIMEOFDAY_RANGE);
    pDX->Fail();
  }
}


void DDV_GreaterThanCLTimeOfDay(CDataExchange* pDX, CLTimeOfDay& value, CLTimeOfDay& minVal)
{
  ASSERT(value.IsValid() && minVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value < minVal))
  {
    AfxMessageBox(IDS_INVALID_TIMEOFDAY_MIN, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_TIMEOFDAY_MIN);
    pDX->Fail();
  }
}


void DDV_LessThanCLTimeOfDay(CDataExchange* pDX, CLTimeOfDay& value, CLTimeOfDay& maxVal)
{
  ASSERT(value.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value > maxVal))
  {
    AfxMessageBox(IDS_INVALID_TIMEOFDAY_MAX, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_TIMEOFDAY_MAX);
    pDX->Fail();
  }
}


void DDV_MinMaxCLDate(CDataExchange* pDX, CLDate& value, CLDate& minVal, CLDate& maxVal)
{
  ASSERT(value.IsValid() && minVal.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && ((value < minVal) || (value > maxVal)))
  {
    AfxMessageBox(IDS_INVALID_DATE_RANGE, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_DATE_RANGE);
    pDX->Fail();
  }
}


void DDV_GreaterThanCLDate(CDataExchange* pDX, CLDate& value, CLDate& minVal)
{
  ASSERT(value.IsValid() && minVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value < minVal))
  {
    AfxMessageBox(IDS_INVALID_LDATE_MIN, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_LDATE_MIN);
    pDX->Fail();
  }
}


void DDV_LessThanCLDate(CDataExchange* pDX, CLDate& value, CLDate& maxVal)
{
  ASSERT(value.IsValid() && maxVal.IsValid());
  if (pDX->m_bSaveAndValidate && (value > maxVal))
  {
    AfxMessageBox(IDS_INVALID_LDATE_MAX, MB_OK | MB_ICONEXCLAMATION, DT_IDS_INVALID_LDATE_MAX);
    pDX->Fail();
  }
}





