********************************************************************
Dundas TCP/IP - Socket Client ActiveX Control 3.0 - Demo Application
********************************************************************

CONTENTS

1)  Features
2)  Compatibility - Visual Basic versions
3)  How to Use the Demo

********************************************************************

FEATURES
	
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

********************************************************************

COMPATIBILITY	

This demo was written using Visual Basic 6. No VB 6 specific
functions were used.

********************************************************************

HOW TO USE THE DEMO

	1) this demo needs two instances of the application running 
	   at the same time.  If both instances are on the same machine
	   then you can send and receive data immediately. 	

	2) start one instance of this demo and then start the second instance.
	   If they are running on different machines you will need to change the Remote
	   IP Addresses at both instances, as well as changing the default ports used.  The Remote
	   IP address at one instance should be the same as the Local IP address at the
	   other instance, and vice versa.  In the same manner the Local port at one
	   instance should match the Remote port setting at the other instance, and vice
	   versa.      
	
  	3) you can enter text into either instance's "Data to be sent:" textbox, and
           the entered text will appear in the other instance's "Retrieved Data" textbox.
	   Note that you can click on the "Send Data" button or you can press the <Enter>
	   key to send your data to the other instance.  

	4) note that we automatically create the sockets for you when each instance of
	   the demo is instantiated.

	5) use the tooltip text.  
	
