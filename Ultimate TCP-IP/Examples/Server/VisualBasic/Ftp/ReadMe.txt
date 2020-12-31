***********************************************************************
Ultimate TCP/IP FtpServ Server ActiveX Control 3.0 - Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- easy to initialize with properties such as Path, Port, 
	  WelcomeMsg and MaxConnections.
	
	- Start() and Stop() procedures make connecting a snap.

	- nine events to respond to such as OnMaxConnect(), 
	  OnConnect(), OnStatus().  Use the OnStatus() event to respond
	  to changes in connection status (e.g. a disconnect, connect).
	
	- the OnCheckPassword() event enables you to check the given 
	  user name and password to see if the client is allowed onto 
	  the FTP server.

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls 
	  and the Dundas FtpServ and History controls 3.0.  It does not
	  use any VB 6 specific functions or procedures. 

***********************************************************************

How to Use This Demo

	1) first set the root path of the ftp server and then start
	   the server.  

	2) use the Ultimate TCP/IP Ftp Client Control Demo and log on 
	   using local loopback IP of 127.0.0.1.  

	3) Using the client ftp control list directories, change 
	   directories, etc.  Status changes (e.g. directory  listings,
	   etc.) are logged to the underlying history control. 

	4) use the tooltiptext. 