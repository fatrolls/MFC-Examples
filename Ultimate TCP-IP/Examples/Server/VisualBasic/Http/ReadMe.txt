***********************************************************************
Ultimate TCP/IP HttpServ Server ActiveX Control 3.0 - Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- the Port property combined with the Start () and Stop() methods 
	  makes getting up and running easy painless.

	- many enumerations to work with like Enum HttpCommand, 
	  HttpServErrorCodes. 

	- rich set of events (OnCanAccept(), OnStatus(),  OnMaxConnect(),
	  etc.).

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls 
	  except for the Dundas' MailServ and History controls.  No VB
	  6 specific code is present in the program.

***********************************************************************

How to Use This Demo

	1) make sure you are online.
	
	2) use the Start and Stop buttons to enable the server.

	3) you may set a new current server root path via the Set Path 
	   button. Have an .htm file like index.htm in the server root 
	   directory.

	4) use any browser or the Dundas HttpClient Control to log onto
	   the http server using the localloopback IP.  For example, start
	   Internet Explorer and in the url text box type 
	   "http://127.0.0.1/index.htm".
  
	5) use the tooltiptext.

	  