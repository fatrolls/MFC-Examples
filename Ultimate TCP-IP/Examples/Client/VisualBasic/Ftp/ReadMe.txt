********************************************************************
Dundas Software - FTP Client ActiveX Control 3.0 - Demo Application
********************************************************************


1)  General Information
2)  Features
2)  Compatibility - Visual Basic versions
3)  How to Use the Demo


********************************************************************

GENERAL INFORMATION

	The Ultimate TCP/IP FTP Client Control 3.0 is a robust component that 
allows developers to quickly add ftp capabilities to their client-side applications.  

********************************************************************

FEATURES
	
	- numerous directory/file methods (e.g. RemoveDir, RenameFile, etc.).
	- events which inform user of the number of bytes uploaded/downloaded.  
	- ability to resume a file transfer that was previously aborted.
	- ability to toggle between synchronous and asynchronous modes.
	- cancellation of an asynchronous ftp operation.

********************************************************************

COMPATIBILITY	

	This demo was written using Visual Basic 6. No VB 6 specific
functions were used but the common dialog control is version 6.0, which 
may not be present on systems using VB 5.

********************************************************************

HOW TO USE THE DEMO

	1) Enter a valid Ftp address and connect to the server. 
	
	2) Retrieve a directory listing by clicking on List Dir.  To change 
           directories paste the new directory from the bottom textbox into
           the Directory textbox and click on Change Dir.  Then retrieve a directory
           listing again.  To move up the directory tree use the CdUp button. 
	
	3) For a download enter the name of the file to be downloaded in the Remote
	   Filename textbox and click on GetFile.  Then use the Save As common dialog
           to choose a local filename and the directory the file is to be saved in.
           To upload to the server enter the filename it is to be saved as in the Remote
           Filename textbox.  Then click on Send File.  Use the Open common dialog 
           to choose the file to be uploaded. 
	
	4) To perform a custom command operation enter the name of the command in the 
           Quote textbox and then click on the Quote button.
	
        4) The results of the operation will be indicated in the textbox at the bottom
	   of the form.
	
	5) Utilize the tooltiptext for additional information.

