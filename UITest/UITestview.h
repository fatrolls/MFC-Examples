// UITestView.h : interface of the CUITestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UITESTVIEW_H__92FE6CB2_C318_45C9_90F5_F01EC28E5FF6__INCLUDED_)
#define AFX_UITESTVIEW_H__92FE6CB2_C318_45C9_90F5_F01EC28E5FF6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _MAP_
#include <sstream>
#else // _MAP_
#endif

typedef CWinTraits<WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|
	WS_VSCROLL|ES_MULTILINE|ES_NOHIDESEL, WS_EX_CLIENTEDGE> CUITestViewTraits;

class CUITestView : 
	public CWindowImpl<CUITestView, CEdit, CUITestViewTraits>, 
	public CEditCommands<CUITestView>
{
public:
	CUITestView() : m_pUIStyle(NULL), m_pUIText(NULL), m_pUIParts(NULL) {}

	void SetUI(wtlx::CStyle* pUIStyle, wtlx::CText* pUIText, wtlx::CParts* pUIParts) { 
		m_pUIStyle = pUIStyle; 
		m_pUIText = pUIText; 
		m_pUIParts = pUIParts;
	}

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	DECLARE_WND_SUPERCLASS(NULL, CEdit::GetWndClassName())
	BEGIN_MSG_MAP(CUITestView)
		MESSAGE_HANDLER(WM_SETUI, OnSetUI)
		COMMAND_ID_HANDLER(ID_EDIT_CLEAR, OnEditClear)
		COMMAND_ID_HANDLER(ID_EDIT_CLEAR_ALL, OnEditClearAll)
		COMMAND_ID_HANDLER(ID_EDIT_COPY, OnEditCopy)
		COMMAND_ID_HANDLER(ID_EDIT_CUT, OnEditCut)
		COMMAND_ID_HANDLER(ID_EDIT_PASTE, OnEditPaste)
		COMMAND_ID_HANDLER(ID_EDIT_SELECT_ALL, OnEditSelectAll)
		COMMAND_ID_HANDLER(ID_EDIT_UNDO, OnEditUndo)
		MESSAGE_RANGE_HANDLER(WM_KEYFIRST, WM_KEYLAST, UpdateUI)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, UpdateUI)
		MESSAGE_HANDLER(WM_LBUTTONUP, UpdateUI)
		
	END_MSG_MAP()

	LRESULT OnSetUI(UINT, WPARAM, LPARAM, BOOL&) {
		_ASSERT(m_pUIStyle && m_pUIText && m_pUIParts);

		static INT parts[] = { 300, 400, -1 };
		m_pUIParts->UISetParts(parts);

		m_pUIStyle->UISetVisible(ATL_IDW_BAND2, true);
		m_pUIStyle->UISetEnable(ID_FILE_SAVE, true);
		m_pUIStyle->UISetEnable(ID_FILE_SAVE_AS, true);
		_UpdateUI();
		return 0L;
	}
	LRESULT UpdateUI(UINT, WPARAM, LPARAM, BOOL& bHandled)
	{
		bHandled = FALSE;
		_UpdateUI();
		return 0;
	}
	LRESULT OnEditClear(WORD, WORD, HWND, BOOL&)
	{
		Clear();
		_UpdateUI();
		return 0;
	}
	LRESULT OnEditClearAll(WORD, WORD, HWND, BOOL&)
	{
		SetSel(0, -1);
		Clear();
		_UpdateUI();
		return 0;
	}
	LRESULT OnEditCopy(WORD, WORD, HWND, BOOL&)
	{
		Copy();
		_UpdateUI();
		return 0;
	}
	LRESULT OnEditCut(WORD, WORD, HWND, BOOL&)
	{
		Cut();
		_UpdateUI();
		return 0;
	}
	LRESULT OnEditPaste(WORD, WORD, HWND, BOOL&)
	{
		Paste();
		_UpdateUI();
		return 0;
	}
	LRESULT OnEditSelectAll(WORD, WORD, HWND, BOOL&)
	{
		SetSel(0, -1);
		_UpdateUI();
		return 0;
	}
	LRESULT OnEditUndo(WORD, WORD, HWND, BOOL&)
	{
		Undo();
		_UpdateUI();
		return 0;
	}

private:
	void _UpdateUI() {
		m_pUIStyle->UISetEnable(ID_EDIT_CUT, CanCut() != FALSE);
		m_pUIStyle->UISetEnable(ID_EDIT_COPY, CanCopy() != FALSE);
		m_pUIStyle->UISetEnable(ID_EDIT_PASTE, CanPaste() != FALSE);
		m_pUIStyle->UISetEnable(ID_EDIT_CLEAR, CanClear() != FALSE);
		m_pUIStyle->UISetEnable(ID_EDIT_UNDO, CanUndo() != FALSE);
		m_pUIStyle->UISetEnable(ID_EDIT_SELECT_ALL, CanSelectAll() != FALSE);

#ifdef _MAP_
		typedef std::basic_string<TCHAR> tsring;
		m_pUIText->UIAddLocalText(1, tsring(), GetModify() ? _T("Modified") : tsring());

		// BUG: That stuff has memory leaks!
		//std::basic_ostringstream<TCHAR> stream;
		//stream << _T("Text length is ") << GetWindowTextLength() << _T(" characters.");
		//m_pUIText->UISetText(0, stream.str());
#else // _MAP_
		CString str;
		str.Format(_T("Text length is %d characters."), GetWindowTextLength());
		m_pUIText->UISetText(0, str);
		m_pUIText->UIAddLocalText(1, CString(), GetModify() ? _T("Modified") : CString());
#endif // _MAP_
	}

	BOOL CanPaste() {
		OpenClipboard();
		UINT uFmt = EnumClipboardFormats(NULL);
		while(uFmt && uFmt != CF_TEXT)
			uFmt = EnumClipboardFormats(uFmt);
		CloseClipboard();
		return uFmt;
	}

private:
	wtlx::CStyle* m_pUIStyle;
	wtlx::CText* m_pUIText;
	wtlx::CParts* m_pUIParts;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UITESTVIEW_H__92FE6CB2_C318_45C9_90F5_F01EC28E5FF6__INCLUDED_)
