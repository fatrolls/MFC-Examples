// BCGToolbarButton.h: interface for the CBCGToolbarButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARBUTTON_H__E0D2D9D5_C494_11D1_A646_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARBUTTON_H__E0D2D9D5_C494_11D1_A646_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXOLE_H__
#include <afxole.h>
#endif

class CBCGToolBarImages;

class AFX_EXT_CLASS CBCGToolbarButton : public CObject
{
	DECLARE_SERIAL(CBCGToolbarButton)

public:
	CBCGToolbarButton();
	CBCGToolbarButton(UINT uiID, int iImage, LPCTSTR lpszText = NULL, BOOL bUserButton = FALSE);
	virtual ~CBCGToolbarButton();

// Operations:
public:

	//--------------------
	// Drag and drop stuf:
	//--------------------
	static CLIPFORMAT GetClipboardFormat ();
	static CBCGToolbarButton* CreateFromOleData (COleDataObject* pDataObject);
	BOOL PrepareDrag (COleDataSource& srcItem);

// Overrides:
	virtual void CopyFrom (const CBCGToolbarButton& src);
	virtual void Serialize (CArchive& ar);
	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE);
	virtual int OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual BOOL OnClick (CWnd* pWnd)		{	return FALSE;	}
	virtual void OnChangeParentWnd (CWnd* pWndParent) {}
	virtual void OnMove ()						{}
	virtual void OnSize (int iSize)				{}
	virtual HWND GetHwnd ()						{	return NULL;	}
	virtual BOOL CanBeStretched () const		{	return FALSE;	}
	virtual BOOL NotifyCommand (int iNotifyCode){	return FALSE;	}
	virtual void OnAddToCustomizePage ()		{}
	virtual HBRUSH OnCtlColor(CDC* pDC, UINT nCtlColor)
	{
		return NULL;
	}
						
// Attributes:
public:
	BOOL IsDrawText () const
	{
		return m_bText && !m_strText.IsEmpty ();
	}

	BOOL IsDrawImage () const
	{
		return m_bImage && m_bImage >= 0;
	}

	BOOL	m_bUserButton;	// Is user-defined tool button?
	UINT	m_nID;			// Command ID that this button sends
	UINT	m_nStyle;		// TBBS_ styles
	int		m_iImage;		// index into bitmap of this button's picture
	CRect	m_rect;			// Button location
	CString	m_strText;		// Button text (for user-defined buttons only!)
	BOOL	m_bText;		// Draw text label
	BOOL	m_bImage;		// Draw image
	BOOL	m_bWrap;		// Wrap toolbar

	// Run-time properties:
	BOOL	m_bDragFromCollection;	// Button is dragged from collection
	static CLIPFORMAT	m_cFormat;
};

#endif // !defined(AFX_BCGTOOLBARBUTTON_H__E0D2D9D5_C494_11D1_A646_00A0C93A70EC__INCLUDED_)
