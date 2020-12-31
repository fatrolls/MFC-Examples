/*
Module : DENTRY.H
Purpose: Defines the interface to a number of classes to allow data entry of 
         the date/time classes
Created: PJN / DATE/1 / 20-02-1996
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

#ifndef __DENTRY_H__


////////////////////////////////// Macros /////////////////////////////////////

#define __DENTRY_H__


////////////////////////////////// Consts /////////////////////////////////////

//flags used to control how the drop down dialogs are displayed

const DWORD DT_ONLYVALID        = 0x0001;   //only allows valid data to be entered
const DWORD DT_NOMILLISECOND    = 0x0002;   //do not show the millisecond field
const DWORD DT_NODRAG           = 0x0004;   //do not allow dialog dragging
const DWORD DT_CLOSEONDEACTIVE  = 0x0008;   //close the drop down dialog when it losses focus, needs DT_MODELESS
const DWORD DT_PUSHPIN          = 0x0010;   //Displays a push pin in the drop down dialog, needs DT_MODELESS
const DWORD DT_MODAL            = 0x0020;   //Creates the drop down dialog as modal
const DWORD DT_MODELESS         = 0x0040;   //Creates the drop down dialog as modeless

////////////// Id of the edit button created at run time //////////////////////
#define DTIME_EDIT_CONTROL_ID 1000                                                   
#define UWM_BN_CLICKED WM_USER + 100


////////////////////////////////// Includes ///////////////////////////////////
#include "stdafx.h"
#include "datetime.h"


////////////////////////////// classes ////////////////////////////////////////
class CDTDialog : public CDialog
{
public:
  CDTDialog();
  CDTDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
  CDTDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
  
protected:
  //{{AFX_DATA(CDTDialog)
  //}}AFX_DATA

  virtual void OnOK();
  virtual void OnCancel();

  //{{AFX_VIRTUAL(CDTDialog)
  public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CDTDialog)
  virtual BOOL OnInitDialog();
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
  #ifndef _WIN32
    afx_msg void OnPushPin();
  #endif
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

  CWnd* m_pParentWnd;
  DWORD m_dwFlags;
  BOOL m_bSafeToClose;
  CPushPinButton m_btnPushPin;
#ifdef _WIN32  
  CToolTipCtrl m_TipPushPin;
#endif  
};


class CCDateDlg : public CDTDialog
{
public:
//Constructors / Destructors
  CCDateDlg();
  CCDateDlg(CWnd* pParent, DWORD dwFlags);
  BOOL Create(CWnd* pParent, DWORD dwFlags);

//Accessors / Mutators
  void SetValue(const CDate& value);
  CDate GetValue();
  
protected:
  //{{AFX_DATA(CCDateDlg)
  CComboBox m_ctrlMonth;
#ifdef _WIN32  
  CSpinButtonCtrl m_ctrlSpinYear;
  CSpinButtonCtrl m_ctrlSpinDay;
#endif  
  CButton m_ctrlInvalid;
  UINT  m_nDay;
  long  m_lYear;
  BOOL  m_bInValid;
  //}}AFX_DATA
  UINT m_nMonth;

  //{{AFX_VIRTUAL(CCDateDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CCDateDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnInvalid();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


class CCLTimeOfDayDlg : public CDTDialog
{
public:
//Constructors / Destructors
  CCLTimeOfDayDlg();
  CCLTimeOfDayDlg(CWnd* pParent, DWORD dwFlags);
  BOOL Create(CWnd* pParent, DWORD dwFlags);

//Accessors / Mutators
  void SetValue(const CLTimeOfDay& value);
  CLTimeOfDay GetValue();

protected:
  //{{AFX_DATA(CCLTimeOfDayDlg)
#ifdef _WIN32  
  CSpinButtonCtrl m_ctrlSpinHour;
  CSpinButtonCtrl m_ctrlSpinMinute;
  CSpinButtonCtrl m_ctrlSpinSecond;
  CSpinButtonCtrl m_ctrlSpinMilliSecond;
#endif  
  CButton m_ctrlInvalid;
  UINT  m_nHour;
  UINT  m_nMinute;
  UINT  m_nSecond;
  UINT  m_nMilliSecond;
  BOOL  m_bInValid;
  //}}AFX_DATA

  //{{AFX_VIRTUAL(CCLTimeOfDayDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CCLTimeOfDayDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnInvalid();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


class CCLTimeSpanDlg : public CDTDialog
{
public:
//Constructors / Destructors
  CCLTimeSpanDlg();
  CCLTimeSpanDlg(CWnd* pParent, DWORD dwFlags);
  BOOL Create(CWnd* pParent, DWORD dwFlags);

//Accessors / Mutators
  void SetValue(const CLTimeSpan& value);
  CLTimeSpan GetValue();
  
protected:
  //{{AFX_DATA(CCLTimeSpanDlg)
#ifdef _WIN32  
  CSpinButtonCtrl m_ctrlSpinDay;
  CSpinButtonCtrl m_ctrlSpinHour;
  CSpinButtonCtrl m_ctrlSpinMinute;
  CSpinButtonCtrl m_ctrlSpinSecond;
  CSpinButtonCtrl m_ctrlSpinMilliSecond;
#endif  
  CButton m_ctrlInvalid;
  long  m_lDay;
  UINT  m_nHour;
  UINT  m_nMinute;
  UINT  m_nSecond;
  UINT  m_nMilliSecond;
  BOOL  m_bInValid;
  //}}AFX_DATA

  //{{AFX_VIRTUAL(CCLTimeSpanDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CCLTimeSpanDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnInvalid();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


class CCLDateDlg : public CDTDialog
{
public:
//Constructors / Destructors
  CCLDateDlg();
  CCLDateDlg(CWnd* pParent, DWORD dwFlags);
  BOOL Create(CWnd* pParent, DWORD dwFlags);

//Accessors / Mutators
  void SetValue(const CLDate& value);
  CLDate GetValue();
  
protected:
  //{{AFX_DATA(CCLDateDlg)
  CComboBox m_ctrlTimeFrame;
#ifdef _WIN32  
  CSpinButtonCtrl m_ctrlSpinHour;
  CSpinButtonCtrl m_ctrlSpinMinute;
  CSpinButtonCtrl m_ctrlSpinSecond;
  CSpinButtonCtrl m_ctrlSpinMilliSecond;
  CSpinButtonCtrl m_ctrlSpinYear;
  CSpinButtonCtrl m_ctrlSpinDay;
#endif  
  CButton m_ctrlInvalid;
  CComboBox m_ctrlMonth;
  UINT  m_nHour;
  UINT  m_nMinute;
  UINT  m_nSecond;
  UINT  m_nMilliSecond;
  UINT  m_nDay;
  long  m_lYear;
  BOOL  m_bInValid;
  //}}AFX_DATA
  UINT m_nMonth;
  UINT m_nTimeFrame;

  //{{AFX_VIRTUAL(CCLDateDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CCLDateDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnInvalid();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


class CDateButton : public CButton
{
public:
  CDateButton();
  virtual ~CDateButton();

  void SetBuddy(CWnd* pBuddy);


protected:
  //{{AFX_VIRTUAL(CDateButton)
  public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CDateButton)
  afx_msg void OnClicked();
  afx_msg LRESULT OnMyReflectedClicked(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDlgClose(WPARAM, LPARAM);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  CWnd* m_pBuddy;
  BOOL m_bFirstCall;
#ifdef _WIN32  
  CToolTipCtrl m_ToolTip;
#endif  
};


class AFX_EXT_CLASS CDateTimeControl : public CStatic
{
public:
  CDateTimeControl();
  virtual ~CDateTimeControl();

  BOOL SubclassEdit(UINT iCtlID, CWnd* pParentWnd);
  BOOL SubclassEdit(HWND hEdit);
  void SetFlags(DWORD dwFlags) { m_dwFlags = dwFlags; };

protected:
  //{{AFX_VIRTUAL(CDateTimeControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CDateTimeControl)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  BOOL AddEditButton();

  BOOL m_bSubclassed;
  CDateButton m_Edit;
  DWORD m_dwFlags;
};


class AFX_EXT_CLASS CDateControl : public CDateTimeControl
{
public:
//Constructors / Destructors
  EXPORT16 CDateControl();
  virtual EXPORT16 ~CDateControl();

//Accessors / Mutators
  void EXPORT16 SetValue(const CDate& value);
  void EXPORT16 GetValue(CDate& value) { value = m_Value; };
  
protected:
  //{{AFX_VIRTUAL(CDateControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CDateControl)
  afx_msg LRESULT OnEditClick(WPARAM, LPARAM);
  afx_msg LRESULT OnDlgClose(WPARAM, LPARAM);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  CDate m_Value;
  CCDateDlg* m_pDlg; //used to display modeless drop - down dialog
};


class AFX_EXT_CLASS CLTimeSpanControl : public CDateTimeControl
{
public:
//Constructors / Destructors
  EXPORT16 CLTimeSpanControl();
  virtual EXPORT16 ~CLTimeSpanControl();

//Accessors / Mutators
  void EXPORT16 SetValue(const CLTimeSpan& value);
  void EXPORT16 GetValue(CLTimeSpan& value) { value = m_Value; };

protected:
  //{{AFX_VIRTUAL(CLTimeSpanControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CLTimeSpanControl)
  afx_msg LRESULT OnEditClick(WPARAM, LPARAM);
  afx_msg LRESULT OnDlgClose(WPARAM, LPARAM);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  CLTimeSpan m_Value;
  CCLTimeSpanDlg* m_pDlg; //used to display modeless drop - down dialog
};


class AFX_EXT_CLASS CLTimeOfDayControl : public CDateTimeControl
{
public:
//Constructors / Destructors
  EXPORT16 CLTimeOfDayControl();
  virtual EXPORT16 ~CLTimeOfDayControl();

//Accessors / Mutators
  void EXPORT16 SetValue(const CLTimeOfDay& value);
  void EXPORT16 GetValue(CLTimeOfDay& value) { value = m_Value; };

protected:
  //{{AFX_VIRTUAL(CCLTimeOfDayControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CLTimeOfDayControl)
  afx_msg LRESULT OnEditClick(WPARAM, LPARAM);
  afx_msg LRESULT OnDlgClose(WPARAM, LPARAM);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  CLTimeOfDay m_Value;
  CCLTimeOfDayDlg* m_pDlg; //used to display modeless drop - down dialog
};


class AFX_EXT_CLASS CLDateControl : public CDateTimeControl
{
public:
//Constructors / Destructors
  EXPORT16 CLDateControl();
  virtual EXPORT16 ~CLDateControl();

//Accessors / Mutators
  void EXPORT16 SetValue(const CLDate& value);
  void EXPORT16 GetValue(CLDate& value) { value = m_Value; };

protected:
  //{{AFX_VIRTUAL(CLDateControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CLDateControl)
  afx_msg LRESULT OnEditClick(WPARAM, LPARAM);
  afx_msg LRESULT OnDlgClose(WPARAM, LPARAM);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  CLDate m_Value;
  CCLDateDlg* m_pDlg; //used to display modeless drop - down dialog
};


//MFC Data exchange routines

void AFX_EXT_API EXPORT16 DDX_CDateControl(CDataExchange* pDX, int nIDC, CDateControl& rCDateControl, DWORD dwFlags);
void AFX_EXT_API EXPORT16 DDX_CLTimeSpanControl(CDataExchange* pDX, int nIDC, CLTimeSpanControl& rCLTimeSpanControl, DWORD dwFlags);
void AFX_EXT_API EXPORT16 DDX_CLTimeOfDayControl(CDataExchange* pDX, int nIDC, CLTimeOfDayControl& rCLTimeOfDayControl, DWORD dwFlags);
void AFX_EXT_API EXPORT16 DDX_CLDateControl(CDataExchange* pDX, int nIDC, CLDateControl& rCLDateControl, DWORD dwFlags);

void AFX_EXT_API EXPORT16 DDX_CDate(CDataExchange* pDX, CDateControl& rCDateControl, CDate& value);
void AFX_EXT_API EXPORT16 DDV_MinMaxCDate(CDataExchange* pDX, CDate& value, CDate& minVal, CDate& maxVal);
void AFX_EXT_API EXPORT16 DDV_GreaterThanCDate(CDataExchange* pDX, CDate& value, CDate& minVal);
void AFX_EXT_API EXPORT16 DDV_LessThanCDate(CDataExchange* pDX, CDate& value, CDate& maxVal);

void AFX_EXT_API EXPORT16 DDX_CLTimeSpan(CDataExchange* pDX, CLTimeSpanControl& rCLTimeSpanControl, CLTimeSpan& value);
void AFX_EXT_API EXPORT16 DDV_MinMaxCLTimeSpan(CDataExchange* pDX, CLTimeSpan& value, CLTimeSpan& minVal, CLTimeSpan& maxVal);
void AFX_EXT_API EXPORT16 DDV_GreaterThanCLTimeSpan(CDataExchange* pDX, CLTimeSpan& value, CLTimeSpan& minVal);
void AFX_EXT_API EXPORT16 DDV_LessThanCLTimeSpan(CDataExchange* pDX, CLTimeSpan& value, CLTimeSpan& maxVal);

void AFX_EXT_API EXPORT16 DDX_CLTimeOfDay(CDataExchange* pDX, CLTimeOfDayControl& rCLTimeOfDayControl, CLTimeOfDay& value);
void AFX_EXT_API EXPORT16 DDV_MinMaxCLTimeOfDay(CDataExchange* pDX, CLTimeOfDay& value, CLTimeOfDay& minVal, CLTimeOfDay& maxVal);
void AFX_EXT_API EXPORT16 DDV_GreaterThanCLTimeOfDay(CDataExchange* pDX, CLTimeOfDay& value, CLTimeOfDay& minVal);
void AFX_EXT_API EXPORT16 DDV_LessThanCLTimeOfDay(CDataExchange* pDX, CLTimeOfDay& value, CLTimeOfDay& maxVal);

void AFX_EXT_API EXPORT16 DDX_CLDate(CDataExchange* pDX, CLDateControl& rCLDateControl, CLDate& value);
void AFX_EXT_API EXPORT16 DDV_MinMaxCLDate(CDataExchange* pDX, CLDate& value, CLDate& minVal, CLDate& maxVal);
void AFX_EXT_API EXPORT16 DDV_GreaterThanCLDate(CDataExchange* pDX, CLDate& value, CLDate& minVal);
void AFX_EXT_API EXPORT16 DDV_LessThanCLDate(CDataExchange* pDX, CLDate& value, CLDate& maxVal);


#endif //__DENTRY_H__




                                        
