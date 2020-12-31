// SkinCtrlMgr.h: interface for the CSkinCtrlMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINCTRLMGR_H__5045517A_7B51_4A99_ABA9_6307094A1B4F__INCLUDED_)
#define AFX_SKINCTRLMGR_H__5045517A_7B51_4A99_ABA9_6307094A1B4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "skinglobals.h"
#include "..\shared\hookmgr.h"

class CSkinCtrl;
class CSkinIniGlobalsFile;
class ISkinCtrlRender;

// interface for receiving callbacks during the skinning process
class INewSkinCtrl
{
public:
	// return TRUE if you want CSkinCtrl to use pSkinCtrl (which can be NULL to prevent skinning)
	// return FALSE to have CSkinCtrl skin using its built-in classes
	virtual BOOL NewSkinCtrl(const HWND hCtrl, CSkinCtrl*& pSkinCtrl) { return FALSE; }
};

class CSkinCtrlMgr : protected CHookMgr<CSkinCtrlMgr>
{
	friend class CHookMgr<CSkinCtrlMgr>;
	friend class CSkinCtrl;

public:
	virtual ~CSkinCtrlMgr();

	static BOOL Initialize(BOOL bHotCtrls = TRUE, INewSkinCtrl* pCallback = NULL);
	static void Reset();
	static void Release();

	static void EnableSkinDraw(BOOL bEnable = TRUE);
	static void EnableHotCtrls();
	static void DisableHotCtrls();
	static void RedrawAll();
	static void SetRenderer(ISkinCtrlRender* pRenderer);

	static void SetColor(int nColor, COLORREF color);
	static BOOL SetControlBitmap(int nItem, CBitmap bitmap[IM_LAST], COLORREF crMask = -1);
	static BOOL SetControlBitmap(int nItem, UINT uIDBitmap[IM_LAST], COLORREF crMask = -1);

#ifndef NO_SKIN_INI
	static BOOL LoadSkin(const CSkinIniGlobalsFile* pIniFile);
	static void UnloadSkin();
#endif

	static BOOL ModifyStyle(HWND hCtrl, DWORD dwStylesToRemove, DWORD dwStylesToAdd);
	static BOOL ModifyStyle(CWnd* pParent, UINT uCtrlID, DWORD dwStylesToRemove, DWORD dwStylesToAdd);

protected:
	BOOL m_bHotCtrls;
	int m_nHotTimer;
	CPoint m_ptMouse;
	CSkinCtrl* m_pHotCtrl;
	CMap<HWND, HWND, CSkinCtrl*, CSkinCtrl*&> m_mapCtrls;
	BOOL m_bClosing;
	BOOL m_bSkinning;
	CSkinGlobals m_skGlobals;
	INewSkinCtrl* m_pCallback;

protected:
	static CSkinCtrlMgr& Instance() { return CHookMgr<CSkinCtrlMgr>::GetInstance(); }

	CSkinCtrlMgr();
	BOOL InitHooks();

	CSkinCtrl* NewSkinCtrl(const CString& sClass, DWORD dwStyle);
	CSkinCtrl* GetSkinCtrl(HWND hCtrl);
	void SkinAllChildren(HWND hCtrl);

	// for checking hot status
	static void CALLBACK TimerHotProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	static HWND RealChildFromPoint(CPoint ptHitTest);

	BOOL IsHot(LPRECT pRect); // screen coords
	void UpdateCursorPos() { ::GetCursorPos(&m_ptMouse); }
	void GetCursorPos(LPPOINT pCursor); // in window coords

	// for safety - see implementation for details
	void DoNotify(HWND hCtrl, UINT uNotify, UINT uID, CWnd* pChild);
	LRESULT DoNotify(HWND hCtrl, NMHDR* pNMHDR);

	void ReleaseAll();
	void DebugMapContents();
	void DeleteMap();
	BOOL Unskin(HWND hCtrl);

	BOOL Skin(HWND hCtrl);
	BOOL IsSkinned(HWND hCtrl) { return GetSkinCtrl(hCtrl) != NULL; }

	LRESULT DoCustomDraw(HWND hCtrl, NMHDR* pNMHDR);
	LRESULT DoNotifyReflect(HWND hCtrl, NMHDR* pNMHDR, LRESULT lrParent);
	void DoNotifyReflect(HWND hCtrl, UINT uNotify, LRESULT lrParent);
	HBRUSH DoCtlColor(HWND hCtrl, CDC* pDC);
	void DoScroll(HWND hCtrl, UINT nSBCode, UINT nPos, BOOL bHorz);
	BOOL DoDrawItem(HWND hCtrl, LPDRAWITEMSTRUCT lpDIS);

	virtual void OnCallWndProc(const MSG& msg);
	void EnableHotCtrls(BOOL bEnable);
};

#endif // !defined(AFX_SKINCTRLMGR_H__5045517A_7B51_4A99_ABA9_6307094A1B4F__INCLUDED_)
