#if !defined(AFX_CREDITSTATIC_H__4ABD7701_49F5_11D1_9E3C_00A0245800CF__INCLUDED_)
#define AFX_CREDITSTATIC_H__4ABD7701_49F5_11D1_9E3C_00A0245800CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CreditStatic.h : header file
//

#define DISPLAY_SLOW		0
#define DISPLAY_MEDIUM		1
#define DISPLAY_FAST		2

#define BACKGROUND_COLOR        0
#define TOP_LEVEL_TITLE_COLOR	1
#define TOP_LEVEL_GROUP_COLOR   2
#define GROUP_TITLE_COLOR       3
#define NORMAL_TEXT_COLOR	4

#define TOP_LEVEL_TITLE_HEIGHT	0		
#define TOP_LEVEL_GROUP_HEIGHT  1     
#define GROUP_TITLE_HEIGHT    	2     
#define	NORMAL_TEXT_HEIGHT		3

#define TOP_LEVEL_TITLE		0   // '\t'
#define TOP_LEVEL_GROUP         1   // '\n'
#define GROUP_TITLE           	2   // '\r'
#define DISPLAY_BITMAP		3   // '^'

class CCreditStatic : public CStatic
{
protected:
	COLORREF    m_Colors[5];
	int         m_TextHeights[4];
    	TCHAR       m_Escapes[4];
	int         m_DisplaySpeed[3],m_CurrentSpeed;
// 	CRect       m_ScrollRect;		   // rect of Static Text frame
	CStringList m_ArrCredit;
	CString		m_szWork;
	int         m_nCounter;		   // work ints
	POSITION    m_ArrIndex;
	BOOL        m_bFirstTime;
	BOOL        m_bDrawText;
	int         m_nClip,m_ScrollAmount;
	int         m_nCurrentFontHeight;

	CBitmap     m_bmpWork;                  // bitmap holder
	CBitmap		m_BmpMain;                  // bitmap holder

	CSize 		m_size;                     // drawing helpers
	CPoint 		m_pt;
	BOOL 		m_bProcessingBitmap;
	CPalette	m_pal;
	CBitmap		m_bitmap;
	int m_cxBitmap, m_cyBitmap;
	BOOL		m_bFirstTurn;
	int			n_MaxWidth;
	UINT        TimerOn;
// Construction
public:
	CCreditStatic();

// Attributes
public:

// Operations
public:
   BOOL StartScrolling();
   void EndScrolling();
   void SetCredits(LPCTSTR credits, char delimiter = '|');
   void SetCredits(UINT nID, char delimiter = '\n');
   void SetSpeed(UINT index, int speed = 0);
   void SetColor(UINT index, COLORREF col);
   void SetTextHeight(UINT index, int height);
   void SetEscape(UINT index, char escape);
   BOOL SetBkImage(UINT nIDResource);
   BOOL SetBkImage(LPCTSTR lpszResourceName);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreditStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCreditStatic();

	// Generated message map functions
protected:
	void MoveCredit(CDC *pDC, CRect& r, CRect& r2, BOOL bCheck);
	void AddBackGround(CDC* pDC, CRect& m_ScrollRect, CRect& m_ClientRect);
	void DrawCredit(CDC* pDC, CRect& m_ScrollRect);
	//{{AFX_MSG(CCreditStatic)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREDITSTATIC_H__4ABD7701_49F5_11D1_9E3C_00A0245800CF__INCLUDED_)
