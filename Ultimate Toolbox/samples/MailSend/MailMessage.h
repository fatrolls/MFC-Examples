// MailMessage.h : header file
//



/////////////////////////////////////////////////////////////////////////////
//	Visual Basic sample of the implementation of this ole object
/////////////////////////////////////////////////////////////////////////////
//    Dim msg As Object
//    Dim bResult As Boolean
//    
//    Set msg = CreateObject("OXSENDMAIL.MESSAGE")
//    msg.Profile = "Kris"
//    msg.Password = ""
//    msg.To = "Kris"
//    msg.Subject = "Hello to myself"
//    msg.Content = "Hello and bye bye !!"
//    bResult = msg.AddAttachment("c:\test.bmp")
//    bResult = msg.Send()
//

#include "OXOwnThreadCmdTarget.h"


/////////////////////////////////////////////////////////////////////////////
// CMailMessage command target

class CMailEngine;

class CMailMessage : public COXOwnThreadCmdTarget
{
friend CMailEngine;

DECLARE_DYNCREATE(CMailMessage)

// Data Members
public:

protected:
	CStringArray	m_sAttachments;
	// See the OLE generated dispatch map functions in the function section below

private:

// Member Functions
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailMessage)
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

protected:
	CMailMessage();           // protected constructor used by dynamic creation
	virtual ~CMailMessage();

	// Generated message map functions
	//{{AFX_MSG(CMailMessage)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMailMessage)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMailMessage)
	CString m_sSubject;
	afx_msg void OnSubjectChanged();
	CString m_sContent;
	afx_msg void OnContentChanged();
	short m_nAttachmentCount;
	afx_msg void OnAttachmentCountChanged();
	short m_nLastError;
	afx_msg void OnLastErrorChanged();
	CString m_sTo;
	afx_msg void OnToChanged();
	CString m_sProfile;
	afx_msg void OnProfileChanged();
	CString m_sPassword;
	afx_msg void OnPasswordChanged();
	afx_msg BOOL AddAttachment(LPCTSTR sFilePatch);
	afx_msg BSTR GetAttachment(short nIndex);
	afx_msg BOOL RemoveAttachment(short nIndex);
	afx_msg BOOL Send();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
};

/////////////////////////////////////////////////////////////////////////////
