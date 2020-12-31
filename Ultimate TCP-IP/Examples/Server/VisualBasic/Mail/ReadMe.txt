***********************************************************************
Ultimate TCP/IP MailServ Server ActiveX Control 3.0 - Demo Program
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- ability to add, remove and update Local names.
	
	- ability to add, remove or update DNS entries.
 
	- numerous methods to return or set current user information 
	  (e.g. User_GetAddress, User_GetCount, User_GetPassword, etc.).
	
***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls 
	  and the Dundas History and MailServ 3.0 controls.  It does not
	  use any VB 6 specific functions or procedures. 

***********************************************************************

How to Use This Demo

	1) first set the root path of the mail server.

	2) load the Administrator form and add at least one DNS entry (alternate
           server), one Local dns entry (DNS name identifying the local 
           machine) and add a user (you can use the username and password
           supplied here later with the Mail Client Demo program).  This 
           sets up a mail account which will be used by the Mail Client 
           demo to log onto your server. Please note that if no user 
           information has been entered then the demo will output the 
           following "Failed to load system information".  This will 
           occur until you enter at least one user account.  

	3) use the Ultimate TCP/IP Mail Client Control Demo and enter the 
	   local loopback of 127.0.0.1 for the smtp and pop3 host names.  
	   Enter the username and password which was set-up in MailServ's 
	   Administrator form.
	
	4) use the client mail control to send and receive mail, etc.  

	5) notice that the mail operations are logged to the History control 
	   in the MailServ's main window.  The logging occurs in the 
	   MailServ_OnStatus() event.	

	6) please note there is no Stop() method with this control.  This 
	   is because of the overall complexity of the control (it uses 
	   multiple ports, protocols, etc.)  It is possible to wrap a Stop
	   method but at this time it was not considered feasible. 	

	7) use the tooltiptext. 