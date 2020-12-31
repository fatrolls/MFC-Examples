***********************************************************************
Dundas TCP/IP - Ping Client ActiveX Control 3.0 Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- implements IP header construction and sends and receives ICMP 
	  messages to perform Ping and Trace-route operations (Ping() 
	  and TraceOut() functions).
	
	- trap for errors using the numerous members of the PingErrorCodes 
	  enumeration (e.g. ecCreateSocketFailed, ecInvalidAddressFormat,
	  etc.).

	- numerous data properties such as DataTimeStamp, DataType, 
	  DataID, etc.

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls 
	  and the Dundas Ping 3.0 control.  It does not use any VB 6
	  specific functions or procedures. 

***********************************************************************

How to Use This Demo

	1) enter a valid address and click on Ping or Traceroute to perform
           the ping or traceroute operation.  The results are displayed in 
           the textbox below.  
 
        2) you may toggle between synchronous and asynchronous mode via 
           the BlockingMode checkbox (check it for synchronous mode).  

	3) perform an optional name lookup for each received packet by
           checking the Do Lookup checkbox.  Note that performing a name lookup
           involves a Dns lookup, so it adds a substantial amount of 
           overhead to the Ping or Traceroute call.

	4) cancel an asynchronous (BlockingMode is false) operation by 
	   clicking the Cancel button.  
            	
	5) use the tooltiptext. 

	