
#include "StdAfx.h"
#include "DUIRadioBox.h"
#include "DUIManager.h"

CDUIRadioBox::CDUIRadioBox()
{
	m_wGroup = 0;
}

CDUIRadioBox::~CDUIRadioBox()
{
}

LPCTSTR CDUIRadioBox::GetClass() const
{
	return TEXT("DUIRadioBox");
}

void CDUIRadioBox::SetCheck(bool bCheck, bool bRedraw)
{
	if(m_bCheck == bCheck) return;
	m_bCheck = bCheck;

	if(m_pDUIManager != NULL)
	{
		if(m_bCheck)
		{
			CPtrArray* pGroupArray = m_pDUIManager->GetGroup(m_wGroup);
			if (pGroupArray)
			{
				for(INT_PTR i = 0; i < pGroupArray->GetCount(); ++i)
				{
					CDUIRadioBox* pControl = static_cast<CDUIRadioBox*>(pGroupArray->GetAt(i));
					if(pControl != this)
					{
						pControl->SetCheck(false, bRedraw);
					}
				}
			}
		}
	}

	if (bRedraw) UpdateControl();
}

void CDUIRadioBox::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("group")) == 0) SetGroup((WORD)_tcstoul(lpszValue, NULL, 10));
	else CDUICheckBox::SetAttribute(lpszName, lpszValue);
}


void CDUIRadioBox::OnClick()
{
	if (m_pDUIManager == NULL) return;
	CWnd* pOwnerWnd = m_pDUIManager->GetOwnerWnd();
	if (pOwnerWnd == NULL || pOwnerWnd->GetSafeHwnd() == NULL) return;
	pOwnerWnd->SendMessage(WM_DUI_MESSAGE, GetID(), (LPARAM)this);
	SetCheck(true, true);
}

void CDUIRadioBox::SetGroup(WORD wGroup)
{
	if (m_wGroup == wGroup) return;
	else
	{
		if (m_pDUIManager != NULL)
		{
			m_pDUIManager->RemoveGroup(m_wGroup, this);
		}
		m_wGroup = wGroup;
	}

	if (m_pDUIManager != NULL)
	{
		m_pDUIManager->AddGroup(m_wGroup, this);
	}
}