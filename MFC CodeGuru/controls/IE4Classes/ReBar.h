#ifndef __RBAR_H__
#define __RBAR_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#ifndef __AFXDISP_H__
  #include <afxdisp.h>
#endif

#include "ControlBarEx.h"

#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
                                    // lParam = lpszOther (or NULL)
#define WM_POPMESSAGESTRING 0x0375

#define AFX_IDW_REBAR 0xEEEE

/////////////////////////////////////////////////////////////////////////////

  class CReBarCtrl;

/////////////////////////////////////////////////////////////////////////////
// CReBar

class CReBar : public CControlBarEx
{
  DECLARE_DYNAMIC(CReBar)

// Construction
public:
  CReBar();
  BOOL Create(CWnd* pParentWnd, DWORD dwCtrlStyle = RBS_BANDBORDERS,
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP,
    UINT nID = AFX_IDW_REBAR);

// Attributes
public:
  // for direct access to the underlying common control
  CReBarCtrl& GetReBarCtrl() const
  { return *(CReBarCtrl*)this; }

  // Operations
public:
  BOOL AddBar(CWnd* pBar, LPCTSTR pszText = NULL, CBitmap* pbmp = NULL,
    DWORD dwStyle = RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP);
  BOOL AddBar(CWnd* pBar, COLORREF clrFore, COLORREF clrBack,
    LPCTSTR pszText = NULL, DWORD dwStyle = RBBS_GRIPPERALWAYS);

// Implementation
  virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
  virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
  virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
  virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
#ifdef _DEBUG
  void EnableDocking(DWORD dwDockStyle);
#endif

protected:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  BOOL _AddBar(CWnd* pBar, REBARBANDINFO* pRBBI);

  //{{AFX_MSG(CReBar)
  afx_msg BOOL OnNcCreate(LPCREATESTRUCT);
  afx_msg void OnPaint();
  afx_msg void OnHeightChange(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnNcPaint();
  afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg LRESULT OnShowBand(WPARAM wParam, LPARAM lParam);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif //__RBAR_H__

/////////////////////////////////////////////////////////////////////////////

