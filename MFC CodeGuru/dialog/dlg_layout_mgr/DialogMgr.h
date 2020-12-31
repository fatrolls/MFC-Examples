/////////////////////////////////////////////////////////////////////////////
// CDialogMgr
//
// COPYRIGHT: (c) 1998 ET-Soft - all rights reserved -
//
// A class for smart layouting of Dialogs (inspired by GridBagLayout from 
// Java(tm)
//
// USAGE: See DialogMgr.html
//
// AUTHOR: Erwin Tratar <info@et-soft.de>
//
// COMMENTS: You may use and modify this code freely as long (1) this copyright 
// notice remains unmodified (2) you submit all changes to the original
// author and (3) give credits to the author in your Documentation / AboutBox
//
// LEGAL: THIS SOFTWARE COMES WITH ABSOLUTLY NO WARRANTY NEITHER EXPRESSED NOR
// IMPLIED. USE IT AT YOUR OWN RISK. IN NO WAY SHALL THE AUTHER BE LIABLE FOR
// ANY HARM DONE.

#if !defined(AFX_DIALOGMGR_H__56FCA0C2_E00B_11D1_801B_4854E82A1622__INCLUDED_)
#define AFX_DIALOGMGR_H__56FCA0C2_E00B_11D1_801B_4854E82A1622__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogMgr.h : header file
//

#include <afxtempl.h>

/**
 * Control if the Icon is automatically set to IDR_MAINFRAME
 */
#define _AUTO_SET_ICON

/**
 * Use this helper in your derived class as usually
 *
 * example: [MyDerivedClass.cpp]
 *
 * IMPLEMENT_LAYOUT(CMyDerivedClass);
 * 
 * CMyDerivedClass::CMyDerivedClass()
 * {
 * ...
 *
 * FUNCTION: Connects the layout mechanism to your class
 */
#define IMPLEMENT_LAYOUT(className)				\
void className##::Layout(CRect& rcClient)		\
{												\
	if(rcClient.Height() && rcClient.Width()  && m_pRootPane)	\
		m_pRootPane->resizeTo(rcClient);		\
}
 

/**
 * Use this helper in your derived class as usually
 *
 * example: [MyDerivedClass.cpp]
 *
 * IMPLEMENT_LAYOUT(CMyDerivedClass);
 * 
 * CMyDerivedClass::CMyDerivedClass()
 * {
 * ...
 *
 * FUNCTION: Connects the layout mechanism to your class
 */
#define DECLARE_LAYOUT()				\
virtual void Layout(CRect& rcClient);


/**
 * This is the default border size between the panes. You
 * may override it in CPane constructor, but it is the
 * fixed border around the root pane
 */
const int nDefaultBorder = 5;


/**
 * Base class for the Layout function. Derive your own class
 * from this or derive it from CDialog and modify _all_
 * references to CDialog to CDialogMgr
 */
class CDialogMgr : public CDialog
{
public:
	
	/**
	 * This is the base class for all kind of panes. 
	 */
	class CPaneBase {
	public:
		enum {
			GREEDY				= 0,		// Will eat up as much as it can
			ABSOLUTE_HORZ		= 1 << 0,	// Horizontal size is absolute
			RELATIVE_HORZ		= 1 << 1,	// Horizontal size in percent
			ABSOLUTE_VERT		= 1 << 2,	// Vertical size is absolute
			RELATIVE_VERT		= 1 << 3,	// Vertical size in percent
			NORESIZE			= ABSOLUTE_HORZ | ABSOLUTE_VERT,
		};


		/**
		 * Informs the caller how much of the given space this pane would
		 * like to receive in horizontal direction
		 */
		virtual int		getConstrainHorz(int sizeParent) = 0;


		/**
		 * Informs the caller how much of the given space this pane would
		 * like to receive in vertical direction
		 */
		virtual int		getConstrainVert(int sizeParent) = 0;

		/**
		 * Informs the caller how much of the given space this pane
		 * minimally need. This would be an absolute Value if 
		 * the mode contains ABSOLUTE_HORZ, else 0
		 */
		virtual int		getMinConstrainHorz() = 0;

		/**
		 * Informs the caller how much of the given space this pane
		 * minimally need. This would be an absolute Value if 
		 * the mode contains ABSOLUTE_VERT, else 0
		 */
		virtual int		getMinConstrainVert() = 0;

		/**
		 * This will do the actual resize operation after the
		 * caller computed a new area for this pane
		 */
		virtual bool	resizeTo(CRect& rcNewArea) = 0;

		/**
		 * Virtual destructor needed in Container operations
		 */
		virtual ~CPaneBase() {};

		/**
		 * Returs the Resize Mode of this pane
		 */
		DWORD	modeResize() { return m_modeResize; };

	protected:
		/**
		 * How this Item will be resized, a combination of the flags above
		 */
		DWORD	m_modeResize;
	};


	/**
	 * CPaneItem represents a single control
	 */
	class CPaneItem : public CPaneBase {
	public:
		/**
		 * Creates a new CPaneItem from an Control. If sizeX or sizeY are 0
		 * and modeResize is ABSOLUTE will copy the current dimensions of
		 * the control to m_sizeX/Y. So the appearance does not change
		 * from the Dialog Editor
		 */
		CPaneItem( CWnd* pWnd, DWORD modeResize = GREEDY, int sizeX=0, int sizeY=0);

		/**
		 * If your control is not mapped you can name it by its ChildID. Pass
		 * the pMgr to receive the CWnd* of nID. 
		 * The rest as stated above
		 */
		CPaneItem( UINT nID, CDialogMgr* pMgr, DWORD modeResize = GREEDY, int sizeX=0, int sizeY=0);

		/**
		 * see CPaneBase
		 */
		virtual int getConstrainHorz(int sizeParent);
		virtual int getConstrainVert(int sizeParent);
		virtual int getMinConstrainHorz();
		virtual int getMinConstrainVert();
		virtual bool resizeTo(CRect& rcNewArea);

	private:

		/**
		 * The horizontal size of the control (see m_modeResize)
		 */
		int				m_sizeX;

		/**
		 * The vertical size of the control (see m_modeResize)
		 */
		int				m_sizeY;

		/**
		 * Child Control pointer
		 */
		CWnd*			m_pCtrl;
	};


	/**
	 * This class encapsulates a Subpane (and indeed the root Pane too)
	 * it is a container of CPaneBase* which it will recursivly resize
	 */
	class CPane : public CPaneBase {
	public:
		enum layOrientation {
			HORIZONTAL,
			VERTICAL
		};

		/**
		 * Tell the pane in which direction it is positioned. A HORIZONTAL pane
		 * arranges it's subpanes from left to right, a VERTICAL from top to bottom
		 */
		CPane( layOrientation orientation, int sizeBorder = nDefaultBorder, int sizeExtraBorder = 0 );

		/**
		 * Add a SubPane to the pane, appending at the end. You may specify the resize
		 * mode for both directions. If you add modes for the secondary direction
		 * (i.e. *_VERT for a HORIZONTAL pane) then sizeSecondary is used as it's
		 * size. If you do not specify sizeSecondary and the mode is ABSOLUTE_VERT
		 * it will be computed as the maximum Height of all SubPanes (the same is
		 * true for VERTICAL panes and subpanes with *_HORZ)
		 */
		bool addItem( CPane* pSubpane, DWORD modeResize, int sizeSecondary = 0);

		/**
		 * Add an item to the pane, appending at the end. You may specify the resize
		 * mode for both directions. If you add modes for the secondary direction
		 * (i.e. *_VERT for a HORIZONTAL pane) then sizeSecondary is used as it's
		 * size. If you do not specify sizeSecondary and the mode is ABSOLUTE_VERT
		 * it will be computed as the maximum Height of all SubPanes (the same is
		 * true for VERTICAL panes and subpanes with *_HORZ)
		 */
		bool addItem( CPaneBase* pItem );

		virtual int		getConstrainHorz(int sizeParent);
		virtual int		getConstrainVert(int sizeParent);
		virtual int		getMinConstrainHorz();
		virtual int		getMinConstrainVert();
		virtual bool	resizeTo(CRect& rcNewArea);

		/**
		 * The destructor takes care of destroying all Subpanes and items
		 */
		virtual ~CPane();

		/**
		 * Access to the orientation of this pane
		 */
		layOrientation	getOrientation() { return m_Orientation; };

	protected:
		/**
		 * The orientation of the pane. Keep in mind that all subpanes
		 * must have the complementary orientation, i.e. a VERTICAL
		 * pane must have all HORIZONTAL SubPanes (or normal Items
		 * of course)
		 */
		layOrientation					m_Orientation;

		/**
		 * This array holds the pointers to the Items/SubPanes
		 */
		CArray<CPaneBase*,CPaneBase*>	m_paneItems;

		/**
		 * The secondary constrain
		 */
		int				m_sizeSecondary;

		/** 
		 * Size of gap between childs
		 */
		int				m_sizeBorder;
		int				m_sizeExtraBorder;
	};


	/**
	 * This class encapsulates a Subpane which is a Tab
	 * it will use calls to AdjustRect to position it's
	 * childs
	 */
	class CPaneTab : public CPane
	{
	public:
		/**
		 * Tell the pane in which direction it is positioned. A HORIZONTAL pane
		 * arranges it's subpanes from left to right, a VERTICAL from top to bottom
		 */
		CPaneTab( CTabCtrl* pTab, layOrientation orientation, int sizeBorder = nDefaultBorder, int sizeExtraBorder = 0 );

		virtual int		getConstrainHorz(int sizeParent);
		virtual int		getConstrainVert(int sizeParent);
		virtual int		getMinConstrainHorz();
		virtual int		getMinConstrainVert();
		virtual bool	resizeTo(CRect& rcNewArea);

	private:
		CTabCtrl* m_pTab;
	};

// Construction
public:
	CDialogMgr(UINT nID, CWnd* pParent = NULL);   // standard constructor

	/**
	 * Loadss the current position and size from the registry using a supplied
	 * key. Will be loaded with AfxGetApp()->WriteProfileXXX(). You may
	 * specify a subfolder (e.g. Load( _T("MyDialog\\Layout") ); ). Will
	 * load the following keys:
	 *
	 * - lpstrRegKey+"SizeX";
	 * - lpstrRegKey+"SizeY";
	 * - lpstrRegKey+"PosX";
	 * - lpstrRegKey+"PosY";
	 *
	 * A good place to call this is in InitDialog() after (!!) the baseclass
	 * call when the controls are already created.
	 */
	bool Load(LPCTSTR lpstrRegKey);

	/**
	 * Store the current position and size to the registry using a supplied
	 * key. Will be stored with AfxGetApp()->WriteProfileXXX(). You may
	 * specify a subfolder (e.g. Save( _T("MyDialog\\Layout") ); ). Will
	 * create the following keys:
	 *
	 * - lpstrRegKey+"SizeX";
	 * - lpstrRegKey+"SizeY";
	 * - lpstrRegKey+"PosX";
	 * - lpstrRegKey+"PosY";
	 *
	 * A good place to call this is DestroyWindow() before (!!) you call the
	 * base implementation
	 */
	bool Save(LPCTSTR lpstrRegKey);


// Dialog Data
	//{{AFX_DATA(CDialogMgr)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMgr)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialogMgr)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
#ifdef _AUTO_SET_ICON
	virtual BOOL OnInitDialog();
#endif
	DECLARE_MESSAGE_MAP()


	/**
	 * Updates the layout after you specify the new
	 * layout
	 */
	void UpdateLayout();

	/**
	 * Does the actual Layout, called from OnSize()
	 * Default implementation does nothing, use
	 * IMPLEMENT_LAYOUT in your derived class (see above)
	 */
	virtual void Layout(CRect& rcClient);

	/**
	 * This holds the root pane. Fill in InitDialog()
	 */
	CPane* m_pRootPane;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMGR_H__56FCA0C2_E00B_11D1_801B_4854E82A1622__INCLUDED_)
