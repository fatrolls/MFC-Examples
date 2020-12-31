This sample application is part of the Ultimate Toolbox library.
In the first place it serves as a demonstration of how to implement some of the classes in our library.
Classes:
	+ COXSendMail
	+ COXMapi framework (14 classes)
	+ COXThreadEngine
	+ COXOwnThreadCmdTarget
(for documentation on these classes, check the manual or our website: www.dundas.com)

This application is an OLE automation server which implement two OLE objects:
	+ OXSENDMAIL.MESSAGE
	+ OXSENDMAIL.CGIHANDLER

It allows you to send a mail message via a MAPI compliant mail system (even from within NT services).

Dispatch interface of the OXSENDMAIL.MESSAGE object
Properties:
	From			string
	To			string
	Subject			string
	Content			string
	AttachmentCount		integer
	LastError		long

Methods:
	BOOL AddAttachment ( path ) 	path is string
	string GetAttachment ( index ) 	index is integer
	RemoveAttachment ( index )
	BOOL Send ()

Visual Basic sample of the implementation of this ole object:

	Dim msg As Object
	Dim bResult As Boolean
   
	Set msg = CreateObject("OXSENDMAIL.MESSAGE")
	msg.Profile = "John"
	msg.Password = ""
	msg.To = "John Doe"
	msg.Subject = "Test"
	msg.Content = "This is the content body"
	bResult = msg.AddAttachment("c:\test.bmp")
	bResult = msg.Send()


HTML interface via the CgiToOle.exe or IsapiOle.dll utility:

<FORM METHOD="POST" ACTION="CGI/CgiToOle.exe/OXSENDMAIL.CGIHANDLER">
<INPUT NAME="Profile" TYPE="HIDDEN" VALUE="John" ALIGN=left>
<INPUT NAME="To" TYPE="HIDDEN" VALUE="John Doe" ALIGN=left>
<INPUT NAME="Subject" TYPE="HIDDEN" VALUE="Test" ALIGN=left>
<INPUT NAME="Content" TYPE="HIDDEN" VALUE="This is the content body" ALIGN=left>
<INPUT NAME="AttCount" TYPE="HIDDEN" VALUE="1" ALIGN=left>
<INPUT NAME="Attachment" TYPE="HIDDEN" VALUE="C:\test.bmp" ALIGN=left>
<INPUT TYPE="SUBMIT" VALUE="OXSendMail">
</FORM>


Info:

HTTP:  www.theUltimateToolbox.com


