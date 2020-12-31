#if !defined(AFX_VNMDICLIENT_H__FC9EC8F2_8175_11D1_A16B_000000000000__INCLUDED_)
#define AFX_VNMDICLIENT_H__FC9EC8F2_8175_11D1_A16B_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMdiClient : public CWnd
{
	DECLARE_DYNCREATE(CMdiClient)

// Construction
public:
	CMdiClient();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdiClient)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetBitmap(UINT nID);
	BOOL SetBitmap(LPCSTR szFilename);
	COLORREF SetBackColor(COLORREF nBackColor);
	virtual ~CMdiClient();
	void Tile(BOOL b){m_bTile = b;}

	// Generated message map functions
protected:
	//{{AFX_MSG(CMdiClient)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	HANDLE ReadDIBFile(HANDLE hFile);

private:
	COLORREF			m_nBackColor;
	HPALETTE			m_hPal;           // Our DIB's palette
	HBITMAP				m_hBitmap;
	LONG				m_width;
	LONG				m_height;
	BOOL				m_bTile;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VNMDICLIENT_H__FC9EC8F2_8175_11D1_A16B_000000000000__INCLUDED_)
