// MFCXRebarCtrl.h : header file
//

////////////////////////////////////////////////////////////////
// CMFCXRebarCtrl 1997 Microsoft Systems Journal. ( originally CCoolBar )
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// CMFCXRebarCtrl implements coolbars for MFC.
//
#ifndef MFCXREBARCTRL__H
#define MFCXREBARCTRL__H

#ifndef MFCX_PROJ
#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

class CLASS_EXPORT CMFCXRebarCtrl : public CControlBar
{
	DECLARE_DYNAMIC(CMFCXRebarCtrl)

public:
    CMFCXRebarCtrl();
    virtual ~CMFCXRebarCtrl();

// Message wrappers
public:
	BOOL GetBarInfo(LPREBARINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_GETBARINFO, 0, (LPARAM)lp); }
	BOOL SetBarInfo(LPREBARINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_SETBARINFO, 0, (LPARAM)lp); }
	BOOL GetBandInfo(int iBand, LPREBARBANDINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_GETBANDINFO, iBand, (LPARAM)lp); }
	BOOL SetBandInfo(int iBand, LPREBARBANDINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_SETBANDINFO, iBand, (LPARAM)lp); }
	BOOL InsertBand(int iWhere, LPREBARBANDINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_INSERTBAND, (WPARAM)iWhere, (LPARAM)lp); }
	BOOL DeleteBand(int nWhich)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_INSERTBAND, (WPARAM)nWhich); }
	int GetBandCount()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(RB_GETBANDCOUNT); }
	int GetRowCount()
		{ ASSERT(::IsWindow(m_hWnd));
	     return (int)SendMessage(RB_GETROWCOUNT); }
	int GetRowHeight(int nWhich)
		{ ASSERT(::IsWindow(m_hWnd));
	     return (int)SendMessage(RB_GETROWHEIGHT, (WPARAM)nWhich); }

	BOOL Create(CWnd* pParentWnd, DWORD dwStyle, DWORD dwAfxBarStyle = CBRS_ALIGN_TOP, UINT nID = AFX_IDW_TOOLBAR);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMFCXRebarCtrl)
    public:
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual void OnHeightChanged(const CRect& rcNew);
	virtual BOOL OnCreateBands() = 0; // return -1 if failed
    //}}AFX_VIRTUAL

// Generated message map functions
protected:
    //{{AFX_MSG(CMFCXRebarCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnHeightChange(NMHDR* pNMHDR, LRESULT* pRes);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

//////////////////
// Programmer-friendly REBARINFO initializes itself
//
class CLASS_EXPORT CMFCXRebarInfo : public REBARINFO {
public:
	CMFCXRebarInfo() {
		memset(this, 0, sizeof(REBARINFO));
		cbSize = sizeof(REBARINFO);
	}
};

//////////////////
// Programmer-friendly REBARBANDINFO initializes itself
//
class CLASS_EXPORT CMFCXRebarBandInfo : public REBARBANDINFO {
public:
	CMFCXRebarBandInfo() {
		memset(this, 0, sizeof(REBARBANDINFO));
		cbSize = sizeof(REBARBANDINFO);

		// *** Kirk Stowell
		fMask   = RBBIM_STYLE|RBBIM_CHILD|RBBIM_CHILDSIZE|RBBIM_BACKGROUND|RBBIM_COLORS;
		fStyle  = RBBS_FIXEDBMP;
		clrFore = GetSysColor(COLOR_BTNTEXT);
		clrBack	= GetSysColor(COLOR_BTNFACE);
	}
};

#endif
