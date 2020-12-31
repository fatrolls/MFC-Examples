// DkToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDkToolBar window
#ifndef	__CDKTOOLBAR__
#define	__CDKTOOLBAR__

class CToolBarInfo
{
public:
	TBBUTTON		 tbButton;		// information regarding the button
	LPCTSTR			 btnText;		// text for the button
};

class CDkToolBar : public CToolBar
{
// Construction
public:
					// default construction
					 CDkToolBar();

					// overridden Create(...) allows initialization of toolbar
					 // information which allows user-customization; allows
					 // specification of registry key which allows toolbar
					 // state persistance
	BOOL			 Create(CWnd *pParentWnd,
						DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
						UINT nID = AFX_IDW_TOOLBAR,
						CToolBarInfo *tbInfo = NULL,
						CString regSubKey = "",
						CString regValue = "",
						HKEY regKey = HKEY_CURRENT_USER);

					// overridden LoadToolBar allows automatic restoration
					 // of toolbar information and calculation of total
					 // button count
	inline BOOL		 LoadToolBar(UINT idResource, BOOL restore = FALSE)
						{
								BOOL		 success;		// indicates success;

							// load the toolbar bitmap
							success = CToolBar::LoadToolBar(idResource);

							// count the buttons
							nButtons = GetToolBarCtrl().GetButtonCount();

							// if we're supposed to restore last setting
							if (restore)
							{
								RestoreState();
							}
							return success;
						}


// Attributes
public:
	virtual BOOL	 PreTranslateMessage(MSG* pMsg);
	void			 SaveState();
	void			 RestoreState();
	int				 NButtons();			// number of buttons on toolbar

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDkToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDkToolBar();

	// Generated message map functions
protected:
	CToolBarInfo	*toolBarInfo;		// table of buttons and text
	int				 nButtons;			// number of buttons on toolbar
	CSize			 defBtnSize;		// default button size
	CSize			 defImgSize;		// default image size
	CSize			 txtBtnSize;		// size of buttons with text
	BOOL			 iconsAndText;		// indicates if text is shown under icons
	HKEY			 registryKey;		// key where toolbar information is kept
	CString			 registrySubKey;	// key where toolbar information is kept
	CString			 registryValue;		// value where toolbar information is kept

	//{{AFX_MSG(CDkToolBar)
	afx_msg void OnPopupCustomize();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnToolBarQueryDelete(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarQueryInsert(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarChange(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarBeginDrag(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarEndDrag(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarBeginAdjust(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarCustomHelp(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarEndAdjust(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarGetButtonInfo(NMHDR *notify, LRESULT *result);
	afx_msg void OnToolBarReset(NMHDR *notify, LRESULT *result);
	afx_msg void OnContextMenu(CWnd*, CPoint point);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
