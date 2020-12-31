#if ! defined( __TOGSPLITTERWND_H__ )
#define __TOGSPLITTERWND_H__

#if _MSC_VER >= 1000
	#pragma once
#endif // _MSC_VER >= 1000

/*
** Author: Guy Gascoigne - Piggford
** Internet: guy@wyrdrune.com
**
** You can use this source in any way you like as long as you don't try to sell it.
**
** Any attempt to sell this in source code form must have the permission
** of the original author. You can produce commercial executables with
** this source, but you may not sell it.
**
** Copyright, 1994-98 Guy Gascoigne - Piggford
**
*/

class CTogSplitterWnd : public CSplitterWnd
{
public:
	CTogSplitterWnd::CTogSplitterWnd();
	BOOL CreateStatic( CWnd* pParentWnd, int nRows, int nCols );
	void Toggle();
	BOOL BarIsHorizontal() const { return m_nCols < m_nRows; }
	void UpdateSizes( CSize & sz1, CSize & sz2 );
};

#endif //__TOGSPLITTERWND_H__
