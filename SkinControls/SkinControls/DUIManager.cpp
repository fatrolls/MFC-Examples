

#include "stdafx.h"
#include "DUIManager.h"
#include "DUIControl.h"
#include "Conv.h"
#include "tinyxml/tinyxml.h"

CDUIManager::CDUIManager()
{
	m_pOwnerWnd = NULL;
	m_pHoverControl = NULL;
	m_pClickControl = NULL;

	m_ControlsNameMap.InitHashTable(101);
}

CDUIManager::CDUIManager(CWnd* pOwnerWnd)
{
	m_pOwnerWnd = pOwnerWnd;
}

CDUIManager::~CDUIManager()
{
	RemoveAllGroups();
	RemoveAllControls();
	m_pOwnerWnd = NULL;
	m_pHoverControl = NULL;
	m_pClickControl = NULL;
}

// 设置窗口
void CDUIManager::SetOwnerWnd(CWnd* pOwnerWnd)
{
	ASSERT(pOwnerWnd != NULL && pOwnerWnd->GetSafeHwnd() != NULL);
	m_pOwnerWnd = pOwnerWnd;
}

void CDUIManager::SetWndSize(int nWidth, int nHeight)
{
	m_szWindow.cx = nWidth;
	m_szWindow.cy = nHeight;
}

const CSize& CDUIManager::GetWndSize() const
{
	return m_szWindow;
}

CWnd* CDUIManager::GetOwnerWnd() const
{
	return m_pOwnerWnd;
}

void CDUIManager::SetFont(CFont* pFont)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		pControl->SetFont(pFont);
	}
}

// 更新皮肤
bool CDUIManager::UpdateSkinInfo(LPCTSTR lpszXML, LPCTSTR lpszWindow)
{
	ASSERT(lpszXML && lpszWindow);
	if (lpszXML == NULL || lpszWindow == NULL) return false;

	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(CT2A(lpszXML), TIXML_ENCODING_UTF8))
		return false;

	const TiXmlElement* pXmlSkin = xmlDoc.FirstChildElement("skin");
	if (!pXmlSkin)
		return false;

	const TiXmlElement* pXmlWindow = NULL;
	for (pXmlWindow = pXmlSkin->FirstChildElement(); pXmlWindow; pXmlWindow = pXmlWindow->NextSiblingElement())
	{
		if (strcmp(pXmlWindow->Value(), CT2U8(lpszWindow)) == 0)
		{
			const TiXmlElement* pXmlChild = NULL;
			const TiXmlAttribute* pXmlChildAttri = NULL;
			CDUIControl* pControl = NULL;
			CDUIControl* pControlTemp = NULL;
			int nID;
			for (pXmlChild = pXmlWindow->FirstChildElement(); pXmlChild; pXmlChild = pXmlChild->NextSiblingElement())
			{
				pXmlChild->Attribute("id", &nID);
				pControl = GetControlFromID(nID);
				if (pControl)
				{
					if (strcmp(pXmlChild->Value(), "Label") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUILabel")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "Button") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUIButton")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "CheckBox") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUICheckBox")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "RadioBox") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUIRadioBox")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "Slider") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUISlider")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "Progress") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUIProgress")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "GroupBox") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUIGroupBox")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "TabButton") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUITabButton")) == 0) pControlTemp = pControl;
					else if (strcmp(pXmlChild->Value(), "ImageControl") == 0 && lstrcmp(pControl->GetClass(), TEXT("DUIImageControl")) == 0) pControlTemp = pControl;
					if (pControlTemp)
					{
						pXmlChildAttri = pXmlChild->FirstAttribute();
						while (pXmlChildAttri)
						{
							pControlTemp->UpdateSkinInfo(CU82T(pXmlChildAttri->Name()), CU82T(pXmlChildAttri->Value()));
							pXmlChildAttri = pXmlChildAttri->Next();
						}
						pControlTemp->UpdateControl();
						pControlTemp = NULL;
					}
				}
			}
			return true;
		}
	}

	return false;
}

// 添加控件
void CDUIManager::AddControl(CDUIControl* pControl)
{
	CDUIControl* pControlTemp = GetControlFromID(pControl->GetID());
	if (pControlTemp == NULL) m_arrControls.Add(pControl);

	if (_tcscmp(pControl->GetName(), TEXT("")) != 0)
	{
		pControlTemp = NULL;
		m_ControlsNameMap.Lookup(pControl->GetName(), pControlTemp);
		if (pControlTemp == NULL) m_ControlsNameMap[pControl->GetName()] = pControl;
	}
}

// 得到控件
CDUIControl* CDUIManager::GetControlFromID(const UINT uID)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		if (pControl->GetID() == uID) return pControl;
	}
	return NULL;
}

// 得到控件
CDUIControl* CDUIManager::GetControlFromName(LPCTSTR lpszName)
{
	CDUIControl* pControlTemp = NULL;
	m_ControlsNameMap.Lookup(lpszName, pControlTemp);
	return pControlTemp;
}

bool CDUIManager::ModifyNameHash(CDUIControl* pControl, LPCTSTR lpszOld, LPCTSTR lpszNew)
{
	CDUIControl* pControlTemp = NULL;
	m_ControlsNameMap.Lookup(lpszOld, pControlTemp);
	if (pControlTemp == NULL) m_ControlsNameMap[lpszNew] = pControl;
	else
	{
		if (_tcscmp(lpszNew, TEXT("")) != 0)
		{
			m_ControlsNameMap.RemoveKey(lpszOld);
			m_ControlsNameMap[lpszNew] = pControl;
		}
	}
	return true;
}

// 移除控件
void CDUIManager::RemoveControl(const UINT uID)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		if (pControl->GetID() == uID)
		{
			RemoveControl(pControl->GetName());
			delete pControl;
			pControl = NULL;
			m_arrControls.RemoveAt(i);
			break;
		}
	}
}

void CDUIManager::RemoveControl(LPCTSTR lpszName)
{
	CDUIControl* pControlTemp = NULL;
	m_ControlsNameMap.Lookup(lpszName, pControlTemp);
	if (pControlTemp != NULL)
	{
		RemoveControl(pControlTemp->GetID());
		m_ControlsNameMap.RemoveKey(lpszName);
	}
}

void CDUIManager::RemoveAllControls()
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		delete pControl;
		pControl = NULL;
	}

	m_arrControls.RemoveAll();
	m_ControlsNameMap.RemoveAll();
}

bool CDUIManager::AddGroup(WORD wGroupID, CDUIControl* pControl)
{
	CPtrArray* pGroupArray = NULL;
	if(m_GroupsMap.Lookup(wGroupID, pGroupArray) == TRUE)
	{
		for(INT_PTR i = 0; i < pGroupArray->GetCount(); ++i)
		{
			if(pGroupArray->GetAt(i) == pControl)
			{
				return false;
			}
		}
		pGroupArray->Add(pControl);
	}
	else
	{
		pGroupArray = new CPtrArray;
		pGroupArray->Add(pControl);
		m_GroupsMap[wGroupID] = pGroupArray;
	}
	return true;
}

CPtrArray* CDUIManager::GetGroup(WORD wGroupID)
{
	CPtrArray* pGroupArray = NULL;
	m_GroupsMap.Lookup(wGroupID, pGroupArray);
	return pGroupArray;
}

void CDUIManager::RemoveGroup(WORD wGroupID, CDUIControl* pControl)
{
	CPtrArray* pGroupArray = NULL;
	if(m_GroupsMap.Lookup(wGroupID, pGroupArray) == TRUE)
	{
		for(INT_PTR i = 0; i < pGroupArray->GetCount(); ++i)
		{
			if(pGroupArray->GetAt(i) == pControl)
			{
				pGroupArray->RemoveAt(i);
				break;
			}
		}
		if(pGroupArray->GetCount() == 0)
		{
			SafeDelete(pGroupArray);
			m_GroupsMap.RemoveKey(wGroupID);
		}
	}
}

void CDUIManager::RemoveAllGroups()
{
	WORD wGroup = 0;
	CPtrArray* pGroupArray = NULL;
	POSITION Position = m_GroupsMap.GetStartPosition();
	while (Position != NULL)
	{
		m_GroupsMap.GetNextAssoc(Position, wGroup, pGroupArray);
		SafeDelete(pGroupArray);
	}
	m_GroupsMap.RemoveAll();
}

// 绘画控件
void CDUIManager::PaintControls(CDC* pDC)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		pControl->DoPaint(pDC);
	}
}

// 鼠标离开消息
void CDUIManager::OnMouseLeave()
{
	if (m_pHoverControl != NULL)
	{
		m_pHoverControl->OnMouseLeave();
		m_pHoverControl = NULL;
	}

	if (m_pClickControl != NULL)
	{
		m_pClickControl->OnMouseLeave();
		m_pClickControl = NULL;
	}
}

void CDUIManager::OnMouseMove(const CPoint& point)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		if (pControl->OnMouseMove(point))
		{
			if (m_pHoverControl != pControl)
			{
				if (m_pHoverControl) m_pHoverControl->OnMouseLeave();
				m_pHoverControl = pControl;
			}
			return;
		}
	}

	if (m_pHoverControl != NULL)
	{
		m_pHoverControl->OnMouseLeave();
		m_pHoverControl = NULL;
	}
}

bool CDUIManager::OnLButtonDown(const CPoint& point)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		if (pControl->OnLButtonDown(point))
		{
			m_pClickControl = pControl;
			return true;
		}
	}

	m_pClickControl = NULL;
	return false;
}

void CDUIManager::OnLButtonUp(const CPoint& point)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		if (pControl->OnLButtonUp(point))
		{
			if (pControl == m_pClickControl)
			{
				pControl->OnClick();
			}
			else if (m_pClickControl != NULL)
			{
				m_pClickControl->OnLButtonUp(point);
			}
			break;
		}
	}

	if (m_pClickControl != NULL)
	{
		m_pClickControl->OnMouseLeave();
		m_pClickControl = NULL;
	}
}

void CDUIManager::OnRButtonDown(const CPoint& point)
{

}

void CDUIManager::OnRButtonUp(const CPoint& point)
{

}

bool CDUIManager::OnMouseCursor(const CPoint& point)
{
	for (INT_PTR i = 0; i < m_arrControls.GetCount(); ++i)
	{
		CDUIControl* pControl = m_arrControls[i];
		if (pControl->OnMouseCursor(point))
		{
			return lstrcmp(TEXT("DUILabel"), pControl->GetClass()) == 0 ? true : false;
		}
	}

	return false;
}








