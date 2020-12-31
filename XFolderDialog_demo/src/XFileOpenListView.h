// XFileOpenListView.h  Version 1.0
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// This software is released into the public domain.  You are free to use
// it in any way you like, except that you may not sell this source code.
//
// This software is provided "as is" with no expressed or implied warranty.
// I accept no liability for any damage or loss of business that this
// software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XFILEOPENLISTVIEW_H
#define XFILEOPENLISTVIEW_H

#define XLVM_XP_DO_NOT_PERSIST			(-1)
#define XLVM_XP_UNDEFINED				0
#define XLVM_XP_ICONS					0x7029
#define XLVM_XP_LIST					0x702B
#define XLVM_XP_DETAILS					0x702C
#define XLVM_XP_THUMBNAILS				0x702D
#define XLVM_XP_TILES					0x702E

#define XLVM_VISTA_DO_NOT_PERSIST		(-1)
#define XLVM_VISTA_UNDEFINED			0
#define XLVM_VISTA_DETAILS				0x704B
#define XLVM_VISTA_TILES				0x704C
#define XLVM_VISTA_EXTRA_LARGE_ICONS	0x704D
#define XLVM_VISTA_MEDIUM_ICONS			0x704E
#define XLVM_VISTA_LARGE_ICONS			0x704F
#define XLVM_VISTA_SMALL_ICONS			0x7050
#define XLVM_VISTA_LIST					0x7051

///////////////////////////////////////////////////////////////////////////////
// This class is used to subclass the "SHELLDLL_DefView" window in the file
// open dialog.
//
class CXFileOpenListView : public CWnd
{
public:
	CXFileOpenListView(CWnd * pDlg = NULL) : m_lastViewMode(0), m_pDialog(pDlg) {}
	void Init(CWnd * pWnd) { m_pDialog = pWnd; }
	~CXFileOpenListView() {}

	CWnd *	m_pDialog;
	DWORD	m_lastViewMode;
	BOOL	m_bRedraw;

	int  GetViewMode();
	BOOL SetViewMode(int cmd);

protected:
	int GetVistaViewMode(long lView, CListCtrl * plc);
	int GetXpViewMode(long lView, CListCtrl * plc);

	virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif //XFILEOPENLISTVIEW_H
