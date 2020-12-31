// EPropCtrl.h: interface for the EPropCtrl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef EXDFGHTTKJILFFDDADMBVNCCBDFJKTTLRETKWWTWTKWVVNVNWJWQOL
#define EXDFGHTTKJILFFDDADMBVNCCBDFJKTTLRETKWWTWTKWVVNVNWJWQOL

#include <afxcmn.h>
#include "EPropListCtrl.h"
#include "ECommentPane.h"

class EPropCtrl : public CWnd
{

	DECLARE_MESSAGE_MAP();
	DECLARE_DYNCREATE(EPropCtrl);

private:

	bool m_bCommentPaneEnabled;
	int m_nTabHeight;

	EPropListCtrl m_PropListCtrl;
	ECommentPane m_CommentPane;
	CTabCtrl m_TabCtrl;
	CRect m_CommentSplitterRect;

	CImageList m_ImageList;

//	CPoint m_MouseDownPosition;
//	int m_nMouseDownHeight;
	int m_nCommentPaneHeight;


protected:

	void RefreshTabCtrl();

public:

	EPropCtrl();
	virtual ~EPropCtrl();

	// Create for use in a dialog. Parse parent window, and the id of the childwindow to "take over"
	void Create( CWnd* pParent , int nDestinationCWndID );

	// Create the control at rect position
	void Create( CWnd* pParent , int nDestinationCWndID, const CRect& rect , IPropertyChangeListener* pListener = NULL );

	void SetImageList( int nBitmapID , int nIconWidth , COLORREF nTransparentColor );

	// This refreshes the propertylist, that is if the host has changed
	// its number of properties of if a unit has changed. This is inface
	// same as SetPropertyHost(thesameagain)
	void RefreshHostList();

	// The host is the object that has its properties shown in the
	// control. Inherit your property-enabled object from IPropertyHost
	// and implement the simple interface
	void SetPropertyHost( IPropertyHost* pHost );

	// This tells the control who to notify (others than the propertyhost
	// itself ofcause) when a property changes. The property view sets
	// itself, so that it can update all views on a property change.
	void SetPropertyChangeListener( IPropertyChangeListener* pListener );

	// Call this if parent size changes (OnSize() would be a good
	// place, maybe) this reorganizes the control to fit new size
	void Resize( const CRect& Rect );

	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown( UINT nFlags , CPoint PointCP );
	afx_msg void OnMouseMove( UINT nFlags , CPoint PointCP );
	afx_msg void OnLButtonUp( UINT nFlags , CPoint PointCP );

	void ChildSizeChanged();

	//
	// this
	//

	void EnableAutoSizeKeyColumn(bool bEnable=true)		{ m_PropListCtrl.EnableAutoSizeKeyColumn(bEnable); }
	void EnableCommentPane( bool bEnable );
	void SetCommentPaneHeight( int nHeight );

	void SetActiveTab(int n);
};

#endif
