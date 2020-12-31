
#include "StdAfx.h"
#include "DUIDlgBuilder.h"
#include "Conv.h"
#include "tinyxml/tinyxml.h"
#include "DUIManager.h"
#include "DUIControl.h"
#include "DUILabel.h"
#include "DUIButton.h"
#include "DUICheckBox.h"
#include "DUIRadioBox.h"
#include "DUIProgress.h"
#include "DUISlider.h"
#include "DUIGroupBox.h"
#include "DUITabButton.h"
#include "DUIImageControl.h"

bool CDUIDialogBuilder::Create(LPCTSTR lpszXML, LPCTSTR lpszWindow, CDUIManager* pDUIManager)
{
	ASSERT(pDUIManager != NULL);
	if (pDUIManager == NULL) return false;
	m_pDUIManager = pDUIManager;

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
			const char* size = pXmlWindow->Attribute("size");
			if (size)
			{
				char* pstr = NULL;
				int cx = strtol(size, &pstr, 10);
				int cy = strtol(pstr + 1, &pstr, 10);
				m_pDUIManager->SetWndSize(cx, cy);
			}

			const TiXmlElement* pXmlChild = NULL;
			const TiXmlAttribute* pXmlChildAttri = NULL;
			CDUIControl* pControl = NULL;
			for (pXmlChild = pXmlWindow->FirstChildElement(); pXmlChild; pXmlChild = pXmlChild->NextSiblingElement())
			{
				if (strcmp(pXmlChild->Value(), "Label") == 0) pControl = new CDUILabel;
				else if (strcmp(pXmlChild->Value(), "Button") == 0) pControl = new CDUIButton;
				else if (strcmp(pXmlChild->Value(), "CheckBox") == 0) pControl = new CDUICheckBox;
				else if (strcmp(pXmlChild->Value(), "RadioBox") == 0) pControl = new CDUIRadioBox;
				else if (strcmp(pXmlChild->Value(), "Slider") == 0) pControl = new CDUISlider;
				else if (strcmp(pXmlChild->Value(), "Progress") == 0) pControl = new CDUIProgress;
				else if (strcmp(pXmlChild->Value(), "GroupBox") == 0) pControl = new CDUIGroupBox;
				else if (strcmp(pXmlChild->Value(), "TabButton") == 0) pControl = new CDUITabButton;
				else if (strcmp(pXmlChild->Value(), "ImageControl") == 0) pControl = new CDUIImageControl;
				if (pControl)
				{
					pControl->SetManager(m_pDUIManager);
					pXmlChildAttri = pXmlChild->FirstAttribute();
					while (pXmlChildAttri)
					{
						pControl->SetAttribute(CU82T(pXmlChildAttri->Name()), CU82T(pXmlChildAttri->Value()));
						pXmlChildAttri = pXmlChildAttri->Next();
					}
					m_pDUIManager->AddControl(pControl);
					pControl = NULL;
				}
#ifdef _DEBUG
				else
				{
					CString str;
					str.Format(TEXT("%s 是无效的控件类型"), CU82T(pXmlChild->Value()));
					AfxMessageBox(str);
				}
#endif
			}

			return true;
		}
	}

	return false;
}

