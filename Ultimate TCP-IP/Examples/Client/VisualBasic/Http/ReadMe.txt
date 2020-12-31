***********************************************************************
Ultimate TCP/IP Http Client ActiveX Control 3.0 - Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- the HTTP 3.0 Control supports uploading and deleting of files
 	  at the server via the Put and DeleteFile functions. 

	- ability to send Custom commands via the CommandLine function. 

	- ability to toggle asynchronous and synchronous operations on
	  and off with the BlockingMode property.

	- connect via proxy (ProxyServer property).  

	- rich set of callback events (OnGet(), OnPut(), etc.)

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls 
	  except for the Dundas Http Control.  No VB 6 specific code is
 	  present in the program.

***********************************************************************

How to Use This Demo

	1) make sure there is a valid url in the URL textbox.
	
	2) click on the HEAD button to send a HEAD statement to the
 	   currently connected server or proxy to retrieve the results.
           This will retrieve header data.

	3) the PUT button sends a PUT statement to the server or proxy.
	   Enter a valid filename in the Filename textbox to specify the
	   file to be sent.

	4) to retrieve the entire web page use the GET button. 	

        5) enter a custom request in the Command textbox and click on the 
           Command button to execute a valid command which is not 
           incorporated by the Http control. To send/receive data with the
           custom command enter a valid filename in the Data textbox.

	5) use the tooltiptext.	
	   
	   