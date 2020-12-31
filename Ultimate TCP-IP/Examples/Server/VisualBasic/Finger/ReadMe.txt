***********************************************************************
Ultimate TCP/IP FingerServ Server ActiveX Control 3.0 - Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- easy to initialize with properties such as MaxConnections,
	  Port, Path. 
	
	- Start() and Stop() procedures make connecting a snap.

	- numerous events to respond to such as OnMaxConnect(), 
	  OnConnect(), OnStatus().  Use the OnStatus() event to respond
	  to changes in connection status (e.g. a disconnect).

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls 
	  and the Dundas Socket and History controls 3.0.  It does not
	  use any VB 6 specific functions or procedures. 

***********************************************************************

How to Use This Demo

	1) first set the root path of the finger server and then start
	   the server.  You will need a finger textfile in the directory
	   which you set as the working directory.  

	2) use the finger.exe command from the console (NT users) and
	   connect to the server (you may alternatively use the 
	   Ultimate TCP/IP Finger Client Control).  Log onto the finger
	   server by using the following syntax at the client:
	   [fingertextfile]@fingerserver.com.

	3) status changes (e.g. new connections, etc.) are logged to the 
	   bottom text box.  When the maximum number of connections has
	   been reached a warning is displayed in the text box. 