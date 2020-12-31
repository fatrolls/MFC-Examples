***********************************************************************
Ultimate TCP/IP Mail Client ActiveX Control 3.0 - Demo Application
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- the Mail 3.0 Control utilizes the Pop3 and Smtp protocols.

	- mark messages for deletion and have the option to undo deletions 
	  if connection has not been terminated.

	- ability to toggle asynchronous and synchronous operations on
	  and off with the BlockingMode property.

	- use properties such as LineRead to obtain returned data when in 
	  synchronous mode.  Use the numerous events to retrieve data when 
	  using asynchronous mode.

	- the OnSendMail() and OnSaveMsg() events indicate the progress 
	  of the currently running mail operations .
        
        - use the Dundas Message Control 3.0 to parse/examine one message
          at a time.  Used in conjunction with the Mail control, the Message
	  control fully supports MIME/UUENCODE encoding. 

***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls, 
	  the Dundas Message Control 3.0 and the Dundas Mail Control 3.0. 
	  It does not use any VB 6 specific functions or procedures. 

***********************************************************************

How to Use This Demo

	1) to send mail connect to a smtp server, enter a file attach-
	   ment pathname and press Send.

	2) to receive mail connect to a Pop3 server.  The total number of
	   messages will be displayed.  Decode will load the Decode form 
	   which displays message particulars and also lets you decode 
	   attachments. Enter the message number you wish to view in the
	   Current Message textbox. 
	  
	3) Get Message retrieves the message and saves it to a temproary 
	   file (c:\temp\1.txt, c:\temp\2.txt, etc.).
	
	4) mark and unmark messages at the server for deletion via the 
	   Delete Msg, Reset Delete buttons.

	5) use the tooltiptext.

	6) please note that messages which were saved to disk during an 
           earlier session will be overwritten, since the new session will
           save the new messages as "1.txt, 2.txt, etc., the same file names 
           used in the last session.  A more robust application would need to
           determine new filenames which haven't already been used. 

	7) NOTE: If you retrieve a message which was sent with Outlook Express
	   the number of file attachments indicated by this demo will be one
           more than the actual number of attachments for the message.  This 
           is due to the way Outlook Express encodes the message body, the body
           being counted as an attachment by this demo.  This extraneous attachment
           may be trapped by examining the attachment name (which will be
           a zero length string) and the attachment type (which will be "text/html").     