#if !defined(AFX_MAINFRM_H__8639B386_4321_11D0_9C97_00A0C90A632C__INCLUDED_)
#define AFX_MAINFRM_H__8639B386_4321_11D0_9C97_00A0C90A632C__INCLUDED_
///////////////////////////////////////////////////////////
//
//
// MainFrm.h : interface of the CMainFrame class
//
//
///////////////////////////////////////////////////////////
//
// Includes and forward references.1
//
#include "tantype.h" 

interface ITangramModel ;
interface ITangramVisual ;
interface ITangramWorld ;

///////////////////////////////////////////////////////////
//
// CMainFrame window
//
class CMainFrame : public CFrameWnd
{
public: 
	CMainFrame();
	//DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	static CString s_strClassName ;

	// Interface pointer to World.
	ITangramWorld* m_pWorld ;

	// Model List
	typedef CTypedPtrList< CPtrList, ITangramModel* > CModelList ;
	CModelList m_ModelList ;

	// Selection
	ITangramVisual* m_pSelectedVisual ;
	TangramSize2d m_sizedDiff;

// Helper functions
public:
	// Used to register window class and create window.
	BOOL Create() ;	
	
	// Initializes the components.
	BOOL Initialize(int cx, int cy);

	// Function for handling mouse button down messages.
	void DoButtonDown(UINT nWhichButton, CPoint point) ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8639B386_4321_11D0_9C97_00A0C90A632C__INCLUDED_)
