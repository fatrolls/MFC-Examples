// ==========================================================================
// 					Class Implementation : CHelloScript
// ==========================================================================

// Source file : helloscp.cpp

// Source : Dundas Software
// 
// This sample implements a simple write back script.  This type of script
// requires that the onGet and onPost functions be defined.  These are the
// only functions that needed to be defined for this script.                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "helloscp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWinApp theApp;     // dummy app



CHelloScript::CHelloScript()
	{
	}


CHelloScript::~CHelloScript()
	{
	}

// This function is only so that you will see something when you debug
// this demo from within DevStudio or on a command line.
void CHelloScript::OnRunCommandLine(int argc, char** argv)
	{

    _tprintf(_T("This program is designed to be run from the HTTP Service\n"));
    _tprintf(_T("Running it from the command line does nothing interesting\n"));

	int index = 1;
	while(index < argc)
		{
		_tprintf(_T("Command line Parameter %d : %s\n"), index, argv[index]);
		index++;
		}

	}
// This member function is used whenever the client makes a request
// for information from the server.

// This is virtual function which must be defined in any derived class
// One must override these functions because each implementation 
// will be different.  
void CHelloScript::OnGet(LPCTSTR pszParam)
	{	
	UNREFERENCED_PARAMETER(pszParam);

	// Tell the client that it will be receiving HTML formatted text
	_tprintf(_T("Content-type: text/HTML\n"));
	_tprintf(_T("\n<HTML><BODY background=\"../../dundas.gif\">"));
    
    LPCTSTR pszAction = GetPathInfo();
    if (_tcsicmp(pszAction, _T("/report")) == 0)
		{
		// When called by a get this script will return information
		// about the server, client and connection.
		// These functions can be used internally for processing of 
		
		_tprintf(_T("<P>GetPathInfo() = %s</P>\n"), GetPathInfo());
		_tprintf(_T("<P>GetScriptName() = %s</P>\n"), GetScriptName());
		_tprintf(_T("<P>GetRemoteAddress() = %s</P>\n"), GetRemoteAddress());
		_tprintf(_T("<P>GetServerName() = %s</P>\n"), GetServerName());
		_tprintf(_T("<P>GetServerProtocol() = %s</P>\n"), GetServerProtocol());
		_tprintf(_T("<P>GetServerSoftware() = %s</P>\n"), GetServerSoftware());
		_tprintf(_T("<P>GetServerPort() = %i</P>\n"), GetServerPort());
		_tprintf(_T("<P>GetClientInfo(ACCEPT) = %s</P>\n"), GetClientInfo(_T("ACCEPT")));
		_tprintf(_T("<P>GetClientInfo(USER_AGENT) = %s</P>\n"), GetClientInfo(_T("USER_AGENT")));
		_tprintf(_T("<P>GetClientInfo(REFERER) = %s</P>\n"), GetClientInfo(_T("REFERER")));
		_tprintf(_T("<center><img src=\"../../contact.bmp\"></center>"));
		}
	else
		{
    	_tprintf(_T("This is not a valid parameter :\n"));
		_tprintf(_T("<P> %s\n"), pszAction);
		}

	_tprintf(_T("</BODY>\n</HTML>\n"));
	}

void CHelloScript::OnPost(LPCTSTR pszType, LPCTSTR pszData)
	{
	// The client needs to know what type of file it is receiving
	// This statement tells it that.
	// _tprintf is used to simply print the text to the stdout port. 
	_tprintf(_T("Content-type: text/HTML\n\n"));
    _tprintf(_T("<HTML><BODY background=\"../dundas.gif\">"));

    if (_tcscmp(pszType, _T("application/x-www-form-urlencoded")) != 0)
	    {
	    _tprintf(_T("This is not a valid Post parameter\n"));
		_tprintf(_T("</BODY>\n</HTML>\n"));
		return;
    	}

	LPTSTR pszResult = NULL;

	// CGI converts certain characters like spaces, slashes into other
	// characters. They need to be returned to their initial characters.
	// The UUDecode function takes care of this.
	UUDecode(pszData, pszResult);


    // Check for the required fields.  If they do not exist then
	// write back an error message to the client
    CString sSubject, sDescription, sFileName, sEMail;
    if (!Extract(sSubject, pszResult, 0, _T("Subject")) ||
        !Extract(sDescription, pszResult, 1, _T("Descr")) ||
        !Extract(sFileName, pszResult, 2, _T("Filename")) ||
        !Extract(sEMail, pszResult, 3, _T("MailAddr")))
	    {
        _tprintf(_T("Data is corrupt, please try again\n"));
		_tprintf(_T("</BODY>\n</HTML>\n"));
        return;
    	}
	// The following if statements test the required fields for 
	// information.  If they are empty then an error message is 
	// written back to the client.
    if (sFileName.IsEmpty())
    	{	
        _tprintf(_T("The Filename is empty, please try again\n"));
        _tprintf(_T("<P> <A HREF=\"/cgidemo.htm\">Try again</A>\n"));
		_tprintf(_T("</BODY>\n</HTML>\n"));

		if (pszResult != NULL)
			delete[] pszResult;

        return;
    	}

    if (sEMail.IsEmpty())
    	{	
        _tprintf(_T("Your Mail address is empty, please try again\n"));
        _tprintf(_T("<P> <A HREF=\"/cgidemo.htm\">Try again</A>\n"));
		_tprintf(_T("</BODY>\n</HTML>\n"));

		if (pszResult != NULL)
			delete[] pszResult;
        
		return;
    	}

    		
	if (pszResult != NULL)
		delete[] pszResult;

	// The following _tprintf calls send a message back to the client.
	// If the source of the document is viewed in the cients browser
	// it does not appear to be layed out nicely.  However it is readable.
	// The printing of new line (\n) on its own causes the document to be 
	// restarted.
    _tprintf(_T("<P>Your message has been received\n"));
	_tprintf(_T("<P>Hello %s\n"), sEMail);
	_tprintf(_T("<P>The subject you entered is '%s'\n"), sSubject);
    _tprintf(_T("<P>The description you entered is '%s'\n"), sDescription);
	_tprintf(_T("<P>And here is the filename you entered '%s'\n"), sFileName);
    _tprintf(_T("<P> <A HREF=\"/default.htm\">Back to Home Page</A>\n"));
	_tprintf(_T("<P> <strong>This is just a demonstration of a write back script.<strong><br>"));
	_tprintf(_T("<center><img src=\"../contact.bmp\"></center>"));
	_tprintf(_T("<P></BODY>\n</HTML>\n"));
	}

int main(int argc, char *argv[])
	{
  
    CHelloScript script;
	
    return script.DoMain(argc, argv);
	}


