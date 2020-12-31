***********************************************************************
Ultimate TCP/IP Socket Client ActiveX Control 3.0 - Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- numerous protocols supported, as listed in the SocketProtocol 
	  enumeration (Protocol_ICMP, Protocol_IGMP, Protocol_IDP, 
	  etc.).
	
	- trap for errors using the 30 members of the SocketErrorCodes 
	  enumeration (e.g. ecCreateSocketFailed, ecInvalidAddressFormat,
	  etc.).

	- toggle between synchronous, asynchronous modes via the 
	  BlockingMode property.	

	- connect using ICMP or TCP protocols.

	- over 70 methods, properties and events exposed.

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls, 
	  the Dundas Socket 3.0 control, as well as the Animation control 
	  shipped with Microsoft Windows Common Controls-2 5.0 (SP2). 
	  It does not use any VB 6 specific functions or procedures. 

***********************************************************************

How to Use This Demo

	1) this demo performs a finger operation on the specified address.
	   The Connect() function is called and the data is obtained from 
	   the OnReadLine(), OnSend() events. 

	2) please note that the Socket control functions at a lower level
	   than the Finger control.  Unlike the the Finger Control the 
	   Socket Control is not limited to finger or traceroute 
	   operations.	

	3) use the tooltiptext.

	