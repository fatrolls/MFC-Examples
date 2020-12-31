#ifndef __TBCTL_H__
#define __TBCTL_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#ifndef __AFXDISP_H__
  #include <afxdisp.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarCtrlEx

class CToolBarCtrlEx : public CToolBarCtrl
{
// Construction
public:
  CToolBarCtrlEx();
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Attributes
public:
  DWORD GetButtonSize() const
  { ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_GETBUTTONSIZE, 0, 0L); }
	CImageList* GetDisabledImageList() const
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_GETDISABLEDIMAGELIST, 0, 0)); }
	CImageList* GetHotImageList() const
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_GETHOTIMAGELIST, 0, 0)); }
	CImageList* GetImageList() const
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_GETIMAGELIST, 0, 0)); }
	DWORD GetStyle() const
  { ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_GETSTYLE, 0, 0L); }
	int GetMaxTextRows() const
  { ASSERT(::IsWindow(m_hWnd)); return (INT) ::SendMessage(m_hWnd, TB_GETTEXTROWS, 0, 0L); }
	BOOL IsButtonHighlighted(int nID) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ISBUTTONHIGHLIGHTED, nID, 0); }
	BOOL SetButtonWidth(int cxMin, int cxMax)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETBUTTONWIDTH, 0, MAKELPARAM(cxMin, cxMax)); }
	CImageList* SetDisabledImageList(CImageList* pImageList)
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_SETDISABLEDIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }
	CImageList* SetHotImageList(CImageList* pImageList)
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_SETHOTIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }
	CImageList* SetImageList(CImageList* pImageList)
  { ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }
	HRESULT GetDropTarget(IDropTarget** ppDropTarget) const;
	BOOL SetIndent(int iIndent)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETINDENT, iIndent, 0L); }
	BOOL SetMaxTextRows(int iMaxRows)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETMAXTEXTROWS, iMaxRows, 0L); }
	void SetStyle(DWORD dwStyle)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETSTYLE, 0, dwStyle); }
	BOOL GetButtonInfo(int nID, TBBUTTONINFO* ptbbi) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_GETBUTTONINFO, nID, (LPARAM)ptbbi); }
	BOOL SetButtonInfo(int nID, TBBUTTONINFO* ptbbi)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETBUTTONINFO, nID, (LPARAM)ptbbi); }
	DWORD SetDrawTextFlags(DWORD dwMask, DWORD dwDTFlags)
  { ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_SETDRAWTEXTFLAGS, dwMask, dwDTFlags); }
	BOOL GetAnchorHighlight() const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_GETANCHORHIGHLIGHT, 0, 0); }
	BOOL SetAnchorHighlight(BOOL fAnchor = TRUE)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETANCHORHIGHLIGHT, fAnchor, 0); }
	int GetHotItem() const
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_GETHOTITEM, 0, 0); }
	int SetHotItem(int nHot)
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_SETHOTITEM, nHot, 0); }
	void GetInsertMark(TBINSERTMARK* ptbim) const
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_GETINSERTMARK, 0, (LPARAM)ptbim); }
	void SetInsertMark(TBINSERTMARK* ptbim)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETINSERTMARK, 0, (LPARAM)ptbim); }
	BOOL GetMaxSize(LPSIZE pSize) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_GETMAXSIZE, 0, (LPARAM)pSize); }
	BOOL InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_INSERTMARKHITTEST, (WPARAM)ppt, (LPARAM)ptbim); }
	DWORD GetExtendedStyle() const
  { ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_GETEXTENDEDSTYLE, 0, 0L); }
	DWORD SetExtendedStyle(DWORD dwExStyle)
  { ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_SETEXTENDEDSTYLE, 0, dwExStyle); }
	COLORREF GetInsertMarkColor() const
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TB_GETINSERTMARKCOLOR, 0, 0); }
	COLORREF SetInsertMarkColor(COLORREF clrNew)
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TB_SETINSERTMARKCOLOR, 0, (LPARAM) clrNew); }

// Operations
public:
	BOOL MapAccelerator(TCHAR chAccel, UINT* pIDBtn)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)pIDBtn); }
	BOOL MarkButton(int nID, BOOL bHighlight = TRUE)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0)); }
	BOOL MoveButton(UINT nOldPos, UINT nNewPos)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_MOVEBUTTON, nOldPos, nNewPos); }
	int HitTest(LPPOINT ppt) const
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_HITTEST, 0, (LPARAM)ppt); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBarCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif //__TBCTL_H__

/////////////////////////////////////////////////////////////////////////////
