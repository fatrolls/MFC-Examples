; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStyleBar
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyWord.h"
LastPage=0

ClassCount=6
Class1=CMyWordApp
Class2=CMyWordDoc
Class3=CMyWordView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_CNTR_INPLACE
Resource2=IDR_STYLE_BAR
Resource3=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CStyleBar
Resource4=IDD_ABOUTBOX

[CLS:CMyWordApp]
Type=0
HeaderFile=MyWord.h
ImplementationFile=MyWord.cpp
Filter=N

[CLS:CMyWordDoc]
Type=0
HeaderFile=MyWordDoc.h
ImplementationFile=MyWordDoc.cpp
Filter=N

[CLS:CMyWordView]
Type=0
HeaderFile=MyWordView.h
ImplementationFile=MyWordView.cpp
Filter=C
BaseClass=CRichEditView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=MyWord.cpp
ImplementationFile=MyWord.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_PASTE_SPECIAL
Command12=ID_EDIT_SELECT_ALL
Command13=ID_EDIT_FIND
Command14=ID_EDIT_REPEAT
Command15=ID_EDIT_REPLACE
Command16=ID_OLE_INSERT_NEW
Command17=ID_OLE_EDIT_LINKS
Command18=ID_OLE_EDIT_PROPERTIES
Command19=ID_OLE_VERB_FIRST
Command20=ID_VIEW_TOOLBAR
Command21=IDW_STYLE_BAR
Command22=ID_VIEW_STATUS_BAR
Command23=ID_APP_ABOUT
CommandCount=23

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=CMyWordView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_SELECT_ALL
Command2=ID_CHAR_BOLD
Command3=ID_EDIT_COPY
Command4=ID_EDIT_FIND
Command5=ID_EDIT_REPLACE
Command6=ID_CHAR_ITALIC
Command7=ID_FILE_NEW
Command8=ID_FILE_OPEN
Command9=ID_FILE_SAVE
Command10=ID_CHAR_UNDERLINE
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_CANCEL_EDIT_CNTR
Command15=ID_EDIT_REPEAT
Command16=ID_NEXT_PANE
Command17=ID_PREV_PANE
Command18=ID_EDIT_COPY
Command19=ID_EDIT_PASTE
Command20=ID_OLE_EDIT_PROPERTIES
Command21=ID_EDIT_CUT
Command22=ID_EDIT_UNDO
CommandCount=22

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=CMyWordView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_NEXT_PANE
Command5=ID_PREV_PANE
Command6=ID_CANCEL_EDIT_CNTR
CommandCount=6

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
CommandCount=7

[TB:IDR_STYLE_BAR]
Type=1
Class=?
Command1=ID_CHAR_BOLD
Command2=ID_CHAR_ITALIC
Command3=ID_CHAR_UNDERLINE
Command4=ID_PARA_LEFT
Command5=ID_PARA_CENTER
Command6=ID_PARA_RIGHT
Command7=ID_DUMMY1
Command8=ID_DUMMY2
CommandCount=8

[CLS:CStyleBar]
Type=0
HeaderFile=StyleBar.h
ImplementationFile=StyleBar.cpp
BaseClass=CToolBar
Filter=W
LastObject=CStyleBar

