========================================================================
       ColorEdit
========================================================================
Copyright (c) 1996-1997, Keith Rule

You may freely use or modify this code provided this copyright is 
included in all derived versions.

This application partially implements a editor that allows elements of 
the displayed file to be highlighted. Real-time changes to the text file
cause a worker-thread to update the color information. 

It uses the following classes found at http://www.codeguru.com
	
	CUndo		- Undo/Redo for CDocument derived classes
	CMemDC		- Double buffering class for drawing
	CSplash255Wnd	- 256 color splash screen support
	CToolBarEx	- Flat toolbar support
	CRegExp		- Regular Expression matching
	CStringEx	- Extended CString

In addition it defines the class:

	CColorString	- CString plus rule based color encoding

This application is far from done. Here is my current To Do list.

1) Modify the color update routines so the color info isn't lost for all
   characters following a change.
2) Allow dragging during a selection to scroll.

Feel free to make changes and improvements. However I would like to be
the clearing house for the changes. Please send any changes you would like
to become part of the release to: keithr@europa.com.

Nov 8, 1997 - Keith Rule

