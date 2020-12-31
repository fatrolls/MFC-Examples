***********************************************************************
Ultimate TCP/IP  Nntp Client ActiveX Control 3.0 - Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- our Nntp control exposes over 60 properties, methods and events.
	
	- trap for errors using the 30 members of the NntpErrorCodes 
	  enumeration (e.g. ecPASSFailed, ecFileWriteFailed, etc.).

	- ability to toggle between synchronous and synchronous mode with
	  the BlockingMode property.

	- check for new newsgroups with CheckForNewNewsGroups().

	- output the progress of posting an article with 
	  OnSendArticleProgress(BytesReceived, BytesTotlal).

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls 
	  and the Dundas Nntp 3.0 control.  It does not use any VB 6 
	  specific functions or procedures. 

***********************************************************************

How to Use This Demo

	1) enter a valid Nntp hostname and connect to the server (default
	   hostname is msnews.microsoft.com).

	2) click on the News Groups button to populate the lower text box
	   with the news groups available on the server.  Enter or 
	   paste a newsgroup into the NewsGroup text box. 
 
	3) retrieve a listing of available articles lists, select one and 
	   then enter or paste the article number to be retrieved in the 
           Article textbox and then click on the Articles button.

	4) use the tooltiptext.

	