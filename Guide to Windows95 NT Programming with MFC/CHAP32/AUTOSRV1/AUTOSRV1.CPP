///////////////////////////////////////////////////////////////////
// Module  : AUTOSRV1.CPP
//
// Purpose : Implementation of the CAutoSrv1App application class.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 07-06-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoSrv1.h"

///////////////////////////////////////////////////////////////////
// CAutoSrv1App::InitInstance()

BOOL CAutoSrv1App::InitInstance()
{
   // Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Register all OLE server (factories) as running.  
      // This enables the OLE libraries to create objects 
      // from other applications...

		COleTemplateServer::RegisterAll();

		// Application was run with /Embedding or /Automation, so  
      // don't show the main window

		return TRUE;
	}

	// When a server application is launched stand-alone, it's 
   // a good idea to update the system registry in case it's
   // been damaged...

	COleObjectFactory::UpdateRegistryAll();

   // Display a message box explaining that this 
   // is only a server app...

   ::MessageBeep(MB_ICONSTOP);
   AfxMessageBox(IDS_RUNMESSAGE, MB_ICONSTOP);

	return FALSE;          
}

///////////////////////////////////////////////////////////////////
// Declare and run the application

CAutoSrv1App MyApp;

///////////////////////////////////////////////////////////////////
