//
//	Class:		CBkDialogST
//
//	Compiler:	Visual C++
//	Tested on:	Visual C++ 6.0
//
//	Version:	See GetVersionC() or GetVersionI()
//
//	Created:	01/September/2000
//	Updated:	26/July/2002
//
//	Author:		Davide Calabro'		davide_calabro@yahoo.com
//									http://www.softechsoftware.it
//
//	Disclaimer
//	----------
//	THIS SOFTWARE AND THE ACCOMPANYING FILES ARE DISTRIBUTED "AS IS" AND WITHOUT
//	ANY WARRANTIES WHETHER EXPRESSED OR IMPLIED. NO REPONSIBILITIES FOR POSSIBLE
//	DAMAGES OR EVEN FUNCTIONALITY CAN BE TAKEN. THE USER MUST ASSUME THE ENTIRE
//	RISK OF USING THIS SOFTWARE.
//
//	Terms of use
//	------------
//	THIS SOFTWARE IS FREE FOR PERSONAL USE OR FREEWARE APPLICATIONS.
//	IF YOU USE THIS SOFTWARE IN COMMERCIAL OR SHAREWARE APPLICATIONS YOU
//	ARE GENTLY ASKED TO DONATE 1$ (ONE U.S. DOLLAR) TO THE AUTHOR:
//
//		Davide Calabro'
//		P.O. Box 65
//		21019 Somma Lombardo (VA)
//		Italy
//
#ifndef _BKDIALOGST_H_
#define _BKDIALOGST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Return values
#ifndef	BKDLGST_OK
#define	BKDLGST_OK						0
#endif
#ifndef	BKDLGST_INVALIDRESOURCE
#define	BKDLGST_INVALIDRESOURCE			1
#endif
#ifndef	BKDLGST_INVALIDMODE
#define	BKDLGST_INVALIDMODE				2
#endif
#ifndef	BKDLGST_FAILEDREGION
#define	BKDLGST_FAILEDREGION			3
#endif

class CBkDialogST : public CDialog
{
public:
	CBkDialogST(CWnd* pParent = NULL);
	CBkDialogST(UINT uResourceID, CWnd* pParent = NULL);
	CBkDialogST(LPCTSTR pszResourceID, CWnd* pParent = NULL);

	virtual ~CBkDialogST();

	DWORD SetMode(BYTE byMode, BOOL bRepaint = TRUE);

	DWORD SetBitmap(HBITMAP hBitmap, COLORREF crTransColor = -1L);
	DWORD SetBitmap(int nBitmap, COLORREF crTransColor = -1L);

	DWORD ActivateEasyMoveMode(BOOL bActivate);
#ifndef UNDER_CE
	DWORD ShrinkToFit(BOOL bRepaint = TRUE);
#endif

	enum	{
				BKDLGST_MODE_TILE = 0,
				BKDLGST_MODE_CENTER,
				BKDLGST_MODE_STRETCH,
				BKDLGST_MODE_TILETOP,
				BKDLGST_MODE_TILEBOTTOM,
				BKDLGST_MODE_TILELEFT,
				BKDLGST_MODE_TILERIGHT,
				BKDLGST_MODE_TOPLEFT,
				BKDLGST_MODE_TOPRIGHT,
				BKDLGST_MODE_TOPCENTER,
				BKDLGST_MODE_BOTTOMLEFT,
				BKDLGST_MODE_BOTTOMRIGHT,
				BKDLGST_MODE_BOTTOMCENTER,

				BKDLGST_MAX_MODES
			};

	//{{AFX_DATA(CBkDialogST)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBkDialogST)
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CBkDialogST)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnPostEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	static short GetVersionI()		{return 12;}
	static LPCTSTR GetVersionC()	{return (LPCTSTR)_T("1.2");}

private:
	void Init();
	void FreeResources(BOOL bCheckForNULL = TRUE);
#ifndef UNDER_CE
	HRGN ScanRegion(HBITMAP hBitmap, BYTE byTransR, BYTE byTransG, BYTE byTransB);
	LPBYTE Get24BitPixels(HBITMAP hBitmap, LPDWORD lpdwWidth, LPDWORD lpdwHeight);
#endif

	HBITMAP		m_hBitmap;			// Handle to bitmap
#ifndef UNDER_CE
	HRGN		m_hRegion;			// Handle to region
#endif
	DWORD		m_dwWidth;			// Width of bitmap
	DWORD		m_dwHeight;			// Height of bitmap
	BYTE		m_byMode;			// Current drawing bitmap mode
	BOOL		m_bEasyMoveMode;	// Indicates if EasyMove mode must be used

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
