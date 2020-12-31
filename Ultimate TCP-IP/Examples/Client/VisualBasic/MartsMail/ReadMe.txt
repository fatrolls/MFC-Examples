***********************************************************************
Dundas TCP/IP 3.0 - Mail Client ActiveX Control Demonstration
***********************************************************************

Contents

	- General Features
	- Compatibility Issues with VB 5
	- How to Use This Demo

***********************************************************************

General Features
	
	- the Mail 3.0 and Message 3.0 controls use the Pop3 and Smtp 
          protocols.  They also support MIME encoding.

	- mark messages at the server for deletion and have the option 
	  to undo deletions if connection has not been terminated.

	- ability to toggle asynchronous and synchronous operations on
	  and off with the BlockingMode property.  In this demo the main
	  startup window handles the Pop3 operations in synchronous mode.  
	  The Send Mail form (Smtp) utilizes asynchronous mode to send 
	  mail.

	- use properties such as LineRead to obtain returned data when 
	  in synchronous mode (please note that the callback events 
	  still occur).  Use the numerous events (e.g. OnGetMsgNumber)
	  to retrieve data when using asynchronous mode.  Refer to the 	 
	  documentation for more details.

	- OnSendMailProgress() and OnSaveMsgProgress() events indicate 
	  the progress of the currently executing mail operations .

	- You can also retrieve partial messages by using the OpenTop  
	  and ReadTop methods of the Mail control.	
***********************************************************************

Compatibility Issues

	- this was written with VB 6.0.  It utilizes standard controls, 
	  the Dundas Mail control as well as the Dundas Message control.
	  It also uses the Microsoft Common Dialog Control 6.0, the 
	  MSFlexgrid Control 6.0, the MS Rich Textbox Control 6.0 as 
          well as the Toolbar and Statusbar controls from the 
          MS Common Controls 6.0 library.
	  
***********************************************************************

How to Use This Demo


	Receiving Mail:	

	1) Run the program.  The first time the program is run you will 
	   be prompted to enter the Pop3, Smtp server names as well as 
	   username and password information for your email account.  These
	   values are saved to the registry (HKEY_CURRENT_USER\Software\
	   VB and VBA Programs\DundasMailDemo\ServerInfo).
	   These settings may be changed later with the File | Server 
	   Settings... menu item. 
	
	2) An InBox folder is created in the application directory the
	   first time you run the program.  If there are messages saved 
	   in the InBox (done automatically every time you retrieve
	   messages) then they will be displayed in the flexgrid control
	   and will have an icon beside them in the To field if they have not
	   yet been read.

	3) Use the default Timeout settings or reset them (this can be done
	   at run-time from the Options menu).

	4) To retrieve mail click on Messages | Retrieve Messages (it will 
	   connect automatically for you).  

	5) The progress of the messages download will be indicated by the 
	   progress bar.  Once all the messages are downloaded you will be 
	   prompted to delete the messages at the server.  By doing so you
	   will not download the same messages the next time you retrieve 
	   mail.

	6) To save a file attachment double-click in the listbox or use 
	   File | Save Attachment from the menu.
	  
	7) Clipboard operations are initiated from the Edit menu or 
	   right-click in the rich text box.
	
	8) Mark and unmark messages at the server for deletion via the 
	   Messages | Delete/Undelete Messages at Server menu.  Messages 
	   at the server are not actually deleted until the connection 
	   closes, allowing you to rollback the deletion.
	
	9) Downloaded messages saved to the InBox may be deleted via 
	   the Messages | Delete Saved Messages menu item.  
	
	10) You may also print the header and body information from the
	    toolbar Print icon.
	
	11) To download only a portion of the messages use the 
	    Messages | Retrieve Message Tops menu item.


	Sending Mail:	

	8) Click on Reply to reply to a message or use Send New Mail to
	   load the Send Mail form.	

	9) To send a file attachment along with a message use the File -
	   Attach File menu item or click once in the Attachment list box.
	
	10) Once you Send the message you will have the option to Cancel
	    the operation with the same command button.	

	10) Please note that unloading the Send Mail form closes the
	    Smtp connection, while closing the main form closes the
	    Pop3 connection.
	
	11) Use the tooltiptext.