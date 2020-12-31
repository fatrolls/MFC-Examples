
#pragma once

#include "resource.h"

class CFTPexampleApp : public CWinApp
{
public:
   CFTPexampleApp();

   public:
   virtual BOOL InitInstance();

   DECLARE_MESSAGE_MAP()
};

extern CFTPexampleApp theApp;
