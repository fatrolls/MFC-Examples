#ifndef __CNTBAR_H__
#define __CNTBAR_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#ifndef __AFXIMPL_H__
  #include <afximpl.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlBarEx

#define CBRS_GRIPPER        0x00800000L

class CControlBarEx : public CControlBar
{
  DECLARE_DYNAMIC(CControlBarEx)
// Construction
protected:
  CControlBarEx()
  { }

// Attributes
  // getting and setting border space
  void SetBorders(LPCRECT lpRect)
  { SetBorders(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom); }
  void SetBorders(int cxLeft = 0, int cyTop = 0, int cxRight = 0, int cyBottom = 0);
  CRect GetBorders() const;

// Implementation
public:
  virtual ~CControlBarEx()
  { }

	virtual void DoPaint(CDC* pDC);
  void DrawGripper(CDC* pDC, const CRect& rect);

  // implementation helpers
  virtual LRESULT WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
  void CalcInsideRect(CRect& rect, BOOL bHorz) const; // adjusts borders etc
  void EraseNonClient();

  //{{AFX_MSG(CControlBarEx)
  afx_msg void OnPaint();
  afx_msg void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif //__CNTBAR_H__

/////////////////////////////////////////////////////////////////////////////

