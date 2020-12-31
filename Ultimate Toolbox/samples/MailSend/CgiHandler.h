// CgiHandler.h : header file
//

/////////////////////////////////////////////////////////////////////////////
//	HTML of the implementation of this sendmail utility
/////////////////////////////////////////////////////////////////////////////
//	<FORM METHOD="POST" ACTION="CGI/CgiToOle.exe/OXSENDMAIL.CGIHANDLER">
//	<INPUT NAME="Profile" TYPE="HIDDEN" VALUE="Kris" ALIGN=left>
//	<INPUT NAME="To" TYPE="HIDDEN" VALUE="Kris" ALIGN=left>
//	<INPUT NAME="Subject" TYPE="HIDDEN" VALUE="Testje" ALIGN=left>
//	<INPUT NAME="Content" TYPE="HIDDEN" VALUE="Fuck You" ALIGN=left>
//	<INPUT NAME="AttCount" TYPE="HIDDEN" VALUE="1" ALIGN=left>
//	<INPUT NAME="Attachment" TYPE="HIDDEN" VALUE="C:\test.bmp" ALIGN=left>
//	<INPUT TYPE="SUBMIT" VALUE="OXSendMail">
//	</FORM>
//
// In stead of CgiToOle.exe you can use IsapiOle.dll in case of an ISAPI compliant HTTP server

#include "OXOwnThreadCmdTarget.h"


/////////////////////////////////////////////////////////////////////////////
// CCgiHandler command target

class CCgiHandler : public COXOwnThreadCmdTarget
{
	DECLARE_DYNCREATE(CCgiHandler)

	CCgiHandler();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCgiHandler)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCgiHandler();

	// Generated message map functions
	//{{AFX_MSG(CCgiHandler)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCgiHandler)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCgiHandler)
	afx_msg void OnGet(LPDISPATCH pCgiObj, LPCTSTR sCommand);
	afx_msg void OnPost(LPDISPATCH pCgiObj, LPCTSTR sInputType, LPCTSTR sInputBuffer);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
