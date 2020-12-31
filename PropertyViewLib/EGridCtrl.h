
#ifndef EGRIDCTRL_H
#define EGRIDCTRL_H

#include <list>
#include "EPropWnd.h"
#include "IRowList.h"
#include "EPropList.h"

class IGridRow;
class IGridModel;

class EGridCtrl : public EPropWnd /*, public IRowList*/
{

	DECLARE_MESSAGE_MAP();
	DECLARE_DYNCREATE(EGridCtrl);

protected:

	//{{AFX_MSG(EGridCtrl)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint pos );
	afx_msg void OnMenuItemSelected(UINT nID);
	//}}AFX_MSG
	afx_msg void OnPropertyChanged( WPARAM wp , LPARAM lp );
	afx_msg void OnAddGridRow     ( WPARAM wp , LPARAM lp );

public:

	virtual BOOL PreTranslateMessage( MSG* pMsg );

public:

	class Column
	{
	public:
		CString m_sName;
		int     m_nLeft;
		int     m_nWidth;
		int     m_nSortState;	//0=unknown, 1=up, 2=down
		Column( CString sName )
		{
			m_nWidth = 0;
			m_sName  = sName;
			m_nSortState = 0;
		}
		void EnsureWidth( int nWidth )
		{
			if( nWidth > m_nWidth )
			{
				m_nWidth = nWidth;
			}
		}
	};

	class Row : public EPropList
	{
	public:
		IGridRow* m_pRowHost;
		int m_nTop;
		int m_nHeight;
		Row( IGridRow* pRowHost )
		{
			m_pRowHost = pRowHost;
			m_nTop     =  0;
			m_nHeight  = 10;
		}
	};

protected:

	IGridModel* m_pGridModel;
	std::list<Row*>    m_vRows;
	std::list<Column*> m_vCols;

	EProperty** m_ppPropertyMap;

	int m_nColumnSeperatorWidth;

//	bool    m_bMouseOverVerticalGridEdge;
	CPoint  m_ButtonDownPoint;
	int     m_nButtonDownWidth;
//	Column* m_pButtonDownColumn;

	CPoint  m_ViewportOrg;

	CPoint  m_SeletectPropertyIndex;

	CPoint  m_MouseDownCP;

	Column* m_pDragColumn;
	bool    m_bWasDoubleClick;

protected:

	void Clear();
	Column* GetColumnAtIndex( int nColumn );
	Column* GetColumn( int x , bool bRightEdge=false );
	Column* GetColumn( CString sName , bool bCreateIfNotFound , int nNewColumnWidth );
	int     CalculateColumnWidth( int nColumn , bool bIncludeHeader );

	Row* GetRow( int y );
	EProperty* GetProperty( CPoint point , int &nCol , int& nRow );
	EProperty* GetProperty( int nCol , int nRow );
	void BuildPropertyMap();

	int GetHeaderRowHeight();
	int GetRowHeight( EPropList* pRow , CDC* pDC );
	void RefreshColumnLefts( int nOffset );
	void RefreshRowTops( int nOffset );
	void StepPropertySelection( int nStepx , int nStepy );

//	void UpdateColumnList( Row* pNewRow );


public:

	//
	//
	//

	EGridCtrl();
	~EGridCtrl();
//	void SetGridModel( IGridModel* pModel );

	virtual void DoPaint( CDC* pDC );
	
public:

	//
	// IRowList
	//

	virtual void AddRow( IGridRow* pRow );

	//
	// EPropWnd
	//
	virtual CSize GetScrollPageSize();

};

#endif
