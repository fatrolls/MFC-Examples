// CgiHandler.cpp : implementation file
//

#include "stdafx.h"
#include "CgiHandler.h"
#include "CgiToOleDrv.h"
#include "MailEngine.h"
#include "XString.h"

#define MR_PROFILE		_T("Profile")
#define MR_PASSWORD		_T("Password")
#define MR_TO			_T("To")
#define MR_SUBJECT		_T("Subject")
#define MR_CONTENT		_T("Content")
#define MR_ATTCOUNT		_T("AttCount")
#define MR_ATTACHMENT	_T("Attachment")


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCgiHandler

IMPLEMENT_DYNCREATE(CCgiHandler, COXOwnThreadCmdTarget)

CCgiHandler::CCgiHandler()
{
	EnableAutomation();
	EnableOwnThread();	
	
	AfxOleLockApp();
}

CCgiHandler::~CCgiHandler()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CCgiHandler::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	COXOwnThreadCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CCgiHandler, COXOwnThreadCmdTarget)
	//{{AFX_MSG_MAP(CCgiHandler)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCgiHandler, COXOwnThreadCmdTarget)
	//{{AFX_DISPATCH_MAP(CCgiHandler)
	DISP_FUNCTION(CCgiHandler, "OnGet", OnGet, VT_EMPTY, VTS_DISPATCH VTS_BSTR)
	DISP_FUNCTION(CCgiHandler, "OnPost", OnPost, VT_EMPTY, VTS_DISPATCH VTS_BSTR VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICgiHandler to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {48452B96-D40F-11CF-AA2E-00AA00489A36}
static const IID IID_ICgiHandler =
{ 0x48452b96, 0xd40f, 0x11cf, { 0xaa, 0x2e, 0x0, 0xaa, 0x0, 0x48, 0x9a, 0x36 } };

BEGIN_INTERFACE_MAP(CCgiHandler, CCmdTarget)
	INTERFACE_PART(CCgiHandler, IID_ICgiHandler, Dispatch)
END_INTERFACE_MAP()

// {48452B97-D40F-11CF-AA2E-00AA00489A36}
IMPLEMENT_OLECREATE(CCgiHandler, "OXSENDMAIL.CGIHANDLER", 0x48452b97, 0xd40f, 0x11cf, 0xaa, 0x2e, 0x0, 0xaa, 0x0, 0x48, 0x9a, 0x36)

/////////////////////////////////////////////////////////////////////////////
// CCgiHandler message handlers

#include "MailEngine.h"

void CCgiHandler::OnGet(LPDISPATCH pCgiObj, LPCTSTR sCommand) 
{
	UNUSED(sCommand);
	CCgiDispatchDrv cgiObj;

	cgiObj.AttachDispatch(pCgiObj, FALSE);
	cgiObj.SetOutput(_T("<HTML>\n<BODY>\n"));
	cgiObj.SetOutput(_T("<H2>CGI Get Method is not supported !!</H2>\n"));
	cgiObj.SetOutput(_T("</BODY>\n</HTML>\n"));
}


void CCgiHandler::OnPost(LPDISPATCH pCgiObj, LPCTSTR sInputType, LPCTSTR sInputBuffer) 
{
	UNUSED(sInputType);
	UNUSED(sInputBuffer);

	CCgiDispatchDrv	cgiObj;
	CString			sProfile;
	CString			sPassword;
	CString			sTo;
	CString			sSubject;
	CString			sContent;
	COXString		sAttCount;
	int				nAttCount;
	CStringArray	sAttachments;
	short			nLastError;
	CString			sOutputString;
	COleVariant		sInputPar;

	cgiObj.AttachDispatch(pCgiObj, FALSE);

	sInputPar = MR_PROFILE;
	sProfile = cgiObj.GetInput(sInputPar);
	sInputPar = MR_PASSWORD;
	sPassword = cgiObj.GetInput(sInputPar);
	sInputPar = MR_TO;
	sTo = cgiObj.GetInput(sInputPar);
	sInputPar = MR_SUBJECT;
	sSubject = cgiObj.GetInput(sInputPar);
	sInputPar = MR_CONTENT;
	sContent = cgiObj.GetInput(sInputPar);
	sInputPar = MR_ATTCOUNT;
	sAttCount = cgiObj.GetInput(sInputPar);
	nAttCount = sAttCount.GetInt();
	sInputPar = MR_ATTACHMENT;
	for (int i=0 ; i<nAttCount ; i++)
		sAttachments.Add(cgiObj.GetInput(sInputPar));

    cgiObj.SetOutput(_T("<HTML><BODY>"));
   
	BOOL bResult = theMailEngine.Send(
						sProfile,
						sPassword,
						sTo,
						sSubject,
						sContent,
						sAttachments,
						nLastError);

	if (bResult)
	{
		sOutputString.Format(_T("<P><H2>Mail sent successfully !!</H2></P>\n"));
	}
	else
	{
		sOutputString.Format(_T("<P><H2>Mail failed !!</H2></P>\n"));
	}
	cgiObj.SetOutput(sOutputString);
	
    cgiObj.SetOutput(_T("</BODY></HTML>"));
}
