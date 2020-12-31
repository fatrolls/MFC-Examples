
#ifndef DUI_DLGBUILDER_H_
#define DUI_DLGBUILDER_H_
#pragma once

#include "SkinControlsDefine.h"

class CDUIManager;
class SKIN_CONTROLS_EXPORT CDUIDialogBuilder
{
public:
   bool Create(LPCTSTR lpszXML, LPCTSTR lpszWindow, CDUIManager* pDUIManager);

private:
   CDUIManager* m_pDUIManager;
};


#endif // DUI_DLGBUILDER_H_

