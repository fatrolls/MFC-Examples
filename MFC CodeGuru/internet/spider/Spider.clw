; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUrlDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Spider.h"
LastPage=0

ClassCount=7
Class1=CSpiderApp
Class2=CSpiderDoc
Class3=CSpiderView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_SPIDERTYPE
Class5=CAboutDlg
Class6=CChildFrame
Class7=CUrlDlg
Resource4=IDD_GETURL

[CLS:CSpiderApp]
Type=0
HeaderFile=Spider.h
ImplementationFile=Spider.cpp
Filter=N

[CLS:CSpiderDoc]
Type=0
HeaderFile=SpiderDoc.h
ImplementationFile=SpiderDoc.cpp
Filter=N

[CLS:CSpiderView]
Type=0
HeaderFile=SpiderView.h
ImplementationFile=SpiderView.cpp
Filter=C
BaseClass=CEditView
VirtualFilter=VWC
LastObject=CSpiderView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=Spider.cpp
ImplementationFile=Spider.cpp
Filter=D

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
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_SPIDERTYPE]
Type=1
Class=CSpiderView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_TOOLS_GETURL
Command16=ID_TOOL_BROKENURLS
Command17=ID_TOOLS_GETHEADER
Command18=ID_TOOLS_SHOWURLS
Command19=ID_TOOLS_EMAILADDRESS
Command20=ID_TOOLS_STRIPHTML
Command21=ID_TOOLS_STRIPTEXT
Command22=ID_TOOLS_KILLTHREAD
Command23=ID_TOOLS_STOP
Command24=ID_TOOLS_LIST
Command25=ID_TOOLS_NOT_FOUND
Command26=ID_VIEW_TOOLBAR
Command27=ID_VIEW_STATUS_BAR
Command28=ID_WINDOW_NEW
Command29=ID_WINDOW_CASCADE
Command30=ID_WINDOW_TILE_HORZ
Command31=ID_WINDOW_ARRANGE
Command32=ID_WINDOWS_CLOSEALL
Command33=ID_APP_ABOUT
CommandCount=33

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_GETURL]
Type=1
Class=CUrlDlg
ControlCount=6
Control1=IDC_URLCOMBO,combobox,1344339970
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CHECKROOT,button,1342242819

[CLS:CUrlDlg]
Type=0
HeaderFile=UrlDlg.h
ImplementationFile=UrlDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECKROOT
VirtualFilter=dWC

