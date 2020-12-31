
#ifndef DUI_MANAGER_H_
#define DUI_MANAGER_H_
#pragma once

#include "SkinControlsDefine.h"

#include <afxtempl.h>

#define WM_DUI_MESSAGE				(WM_USER + 9430)			// 控件消息

class CDUIControl;

class SKIN_CONTROLS_EXPORT CDUIManager
{
public:
	CDUIManager();
	CDUIManager(CWnd* pOwnerWnd);
	~CDUIManager();

	// 功能函数
public:
	// 设置窗口
	void SetOwnerWnd(CWnd* pOwnerWnd);
	// 如果窗口大小改变 而且控件设置了从右到左或从下到上 必须在OnSize里调用这个函数
	void SetWndSize(int nWidth, int nHeight);
	const CSize& GetWndSize() const;
	CWnd* GetOwnerWnd() const;
	void SetFont(CFont* pFont);
	// 更新皮肤
	bool UpdateSkinInfo(LPCTSTR lpszXML, LPCTSTR lpszWindow);
	// 添加控件
	void AddControl(CDUIControl* pControl);
	// 得到控件
	CDUIControl* GetControlFromID(const UINT uID);
	// 得到控件
	CDUIControl* GetControlFromName(LPCTSTR lpszName);
	bool ModifyNameHash(CDUIControl* pControl, LPCTSTR lpszOld, LPCTSTR lpszNew);
	// 移除控件
	void RemoveControl(const UINT uID);
	void RemoveControl(LPCTSTR lpszName);
	void RemoveAllControls();
	// 组设置
	bool AddGroup(WORD wGroupID, CDUIControl* pControl);
	CPtrArray* GetGroup(WORD wGroupID);
	void RemoveGroup(WORD wGroupID, CDUIControl* pControl);
	void RemoveAllGroups();
	// 绘画控件
	void PaintControls(CDC* pDC);
	// 操作相关
	void OnMouseMove(const CPoint& point);
	void OnMouseLeave();
	bool OnLButtonDown(const CPoint& point);
	void OnLButtonUp(const CPoint& point);
	void OnRButtonDown(const CPoint& point);
	void OnRButtonUp(const CPoint& point);
	bool OnMouseCursor(const CPoint& point);

private:
	CArray<CDUIControl*> m_arrControls;
	CMap<CString, LPCTSTR, CDUIControl*, CDUIControl*> m_ControlsNameMap; // 控件表
	CMap<WORD, WORD, CPtrArray*, CPtrArray*> m_GroupsMap;
	CWnd* m_pOwnerWnd;
	CDUIControl* m_pHoverControl;
	CDUIControl* m_pClickControl;
	CSize m_szWindow;
};

#endif // DUI_MANAGER_H_


