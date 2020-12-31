#ifndef __TBAR_H__
#define __TBAR_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#ifndef __AFXDISP_H__
  #include <afxdisp.h>
#endif

#include "ControlBarEx.h"

/////////////////////////////////////////////////////////////////////////////

class CToolBarCtrlEx;

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx

class CToolBarEx : public CControlBarEx
{
  DECLARE_DYNAMIC(CToolBarEx)

// Construction
public:
  CToolBarEx();
  BOOL Create(CWnd* pParentWnd,
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
    UINT nID = AFX_IDW_TOOLBAR);
  BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
    CRect rcBorders = CRect(0, 0, 0, 0),
    UINT nID = AFX_IDW_TOOLBAR);

  void SetSizes(SIZE sizeButton, SIZE sizeImage);
    // button size should be bigger than image
  void SetHeight(int cyHeight);
    // call after SetSizes, height overrides bitmap size
  BOOL LoadToolBar(LPCTSTR lpszResourceName);
  BOOL LoadToolBar(UINT nIDResource)
  { return LoadToolBar(MAKEINTRESOURCE(nIDResource)); }
  BOOL LoadBitmap(LPCTSTR lpszResourceName);
  BOOL LoadBitmap(UINT nIDResource)
  { return LoadBitmap(MAKEINTRESOURCE(nIDResource)); }
  BOOL SetBitmap(HBITMAP hbmImageWell);
  BOOL SetButtons(const UINT* lpIDArray, int nIDCount);
    // lpIDArray can be NULL to allocate empty buttons

// Attributes
public:
  // standard control bar things
  int CommandToIndex(UINT nIDFind) const;
  UINT GetItemID(int nIndex) const;
  virtual void GetItemRect(int nIndex, LPRECT lpRect) const;
  UINT GetButtonStyle(int nIndex) const;
  void SetButtonStyle(int nIndex, UINT nStyle);

  // for changing button info
  void GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const;
  void SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage);
  BOOL SetButtonText(int nIndex, LPCTSTR lpszText);
  CString GetButtonText(int nIndex) const;
  void GetButtonText(int nIndex, CString& rString) const;

  // for direct access to the underlying common control
  CToolBarCtrl& GetToolBarCtrl() const
  { return *(CToolBarCtrl*)this; }

// Implementation
public:
  virtual ~CToolBarEx();
  virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
  virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
  virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
  virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
  void SetOwner(CWnd* pOwnerWnd);
  BOOL AddReplaceBitmap(HBITMAP hbmImageWell);
  virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  HRSRC m_hRsrcImageWell; // handle to loaded resource for image well
  HINSTANCE m_hInstImageWell; // instance handle to load image well from
  HBITMAP m_hbmImageWell; // contains color mapped button images
  BOOL m_bDelayedButtonLayout; // used to manage when button layout should be done

  CSize m_sizeImage;  // current image size
  CSize m_sizeButton; // current button size

  CMapStringToPtr* m_pStringMap;  // used as CMapStringToUInt

  // implementation helpers
  void _GetButton(int nIndex, TBBUTTON* pButton) const;
  void _SetButton(int nIndex, TBBUTTON* pButton);
  CSize CalcLayout(DWORD nMode, int nLength = -1);
  CSize CalcSize(TBBUTTON* pData, int nCount);
  int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);
  void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);
  void Layout(); // called for for delayed button layout

  //{{AFX_MSG(CToolBarEx)
  afx_msg UINT OnNcHitTest(CPoint);
  afx_msg void OnNcPaint();
  afx_msg void OnPaint();
  afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);
  afx_msg void OnWindowPosChanging(LPWINDOWPOS);
  afx_msg void OnSysColorChange();
  afx_msg LRESULT OnSetButtonSize(WPARAM, LPARAM);
  afx_msg LRESULT OnSetBitmapSize(WPARAM, LPARAM);
  afx_msg BOOL OnNcCreate(LPCREATESTRUCT);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

  LRESULT OnSetSizeHelper(CSize& size, LPARAM lParam);
};

// Styles for toolbar buttons
#define TBBS_BUTTON     MAKELONG(TBSTYLE_BUTTON, 0) // this entry is button
#define TBBS_SEPARATOR  MAKELONG(TBSTYLE_SEP, 0)    // this entry is a separator
#define TBBS_CHECKBOX   MAKELONG(TBSTYLE_CHECK, 0)  // this is an auto check button
#define TBBS_GROUP      MAKELONG(TBSTYLE_GROUP, 0)  // marks the start of a group
#define TBBS_CHECKGROUP (TBBS_GROUP|TBBS_CHECKBOX)  // normal use of TBBS_GROUP
#define TBBS_DROPDOWN   MAKELONG(TBSTYLE_DROPDOWN, 0) // drop down style
#define TBBS_AUTOSIZE   MAKELONG(TBSTYLE_AUTOSIZE, 0) // autocalc button width
#define TBBS_NOPREFIX   MAKELONG(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button

// styles for display states
#define TBBS_CHECKED    MAKELONG(0, TBSTATE_CHECKED)    // button is checked/down
#define TBBS_PRESSED    MAKELONG(0, TBSTATE_PRESSED)    // button is being depressed
#define TBBS_DISABLED   MAKELONG(0, TBSTATE_ENABLED)    // button is disabled
#define TBBS_INDETERMINATE  MAKELONG(0, TBSTATE_INDETERMINATE)  // third state
#define TBBS_HIDDEN     MAKELONG(0, TBSTATE_HIDDEN) // button is hidden
#define TBBS_WRAPPED    MAKELONG(0, TBSTATE_WRAP)   // button is wrapped at this point
#define TBBS_ELLIPSES   MAKELONG(0, TBSTATE_ELIPSES)
#define TBBS_MARKED     MAKELONG(0, TBSTATE_MARKED)

#endif //__TBCTL_H__

/////////////////////////////////////////////////////////////////////////////
