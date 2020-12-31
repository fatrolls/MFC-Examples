#if !defined(AFX_GLENABLEDVIEW_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
#define AFX_GLENABLEDVIEW_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CGLEnabledView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Global type definitions
	enum InfoField {VENDOR,RENDERER,VERSION,ACCELERATION,EXTENSIONS};
	enum ColorsNumber{INDEXED,THOUSANDS,MILLIONS,MILLIONS_WITH_TRANSPARENCY};
	enum ZAccuracy{NORMAL,ACCURATE};

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView view

class CGLEnabledView : public CView
{
protected:
	CGLEnabledView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGLEnabledView)

// Attributes
public:

// Operations
public:
// Display lists functions
// NOTE: between BeginDispList and EndDispList should be present OpenGL calls only (see documentation for which are allowed and how are them treated)
	void DrawDispLists();	// executes all the display lists
	void BeginDispList();	// creates a new display list and opens a display list definition
	void EndDispList();		// closes a display list definition
// Information retrieval function
	const CString GetInformation(InfoField type);
// Mouse cursor function
	void SetMouseCursor(HCURSOR mcursor=NULL);
// Attribute retrieval function
	double GetAspectRatio() {return m_dAspectRatio;};
// Overridables
	virtual void OnCreateGL(); // use to set bg color, activate z-buffer, and other global settings
	virtual void OnSizeGL(int cx, int cy); // use to adapt the viewport to the window
	virtual void OnDrawGL(); // use to issue drawing functions
	virtual void VideoMode(ColorsNumber &c,ZAccuracy &z,BOOL &dbuf); // use to specify some video mode parameters

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLEnabledView)
	private:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGLEnabledView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLEnabledView)
	private:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnDestroy();
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
// member variables
	private:
	BOOL m_ExternDispListCall;
	BOOL m_InsideDispList;
	int m_DispListVector[20];
/* An interface to OGL tessellation routines is under development
	GLUtesselator* m_tesselator;
//*/
	HCURSOR m_hMouseCursor;
	CPalette m_CurrentPalette;
	CPalette* m_pOldPalette;
	CRect m_ClientRect;
	double m_dAspectRatio;
	CDC* m_pCDC;
	HGLRC m_hRC;
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void CreateRGBPalette();
	BOOL bSetupPixelFormat();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLENABLEDVIEW_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
