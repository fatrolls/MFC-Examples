; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMSDIWinApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Msdi.h"
LastPage=0

ClassCount=11
Class1=CMsdiApp
Class2=CMsdiDoc
Class3=CMsdiView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MSDITYPE
Class5=CAboutDlg
Class6=CChildFrame
Class7=COutView
Resource4=IDD_MSDI_FORM
Resource5=IDR_OUTTYPE
Class8=CMSDIWinApp
Class9=CMSDIFrame
Class10=CGrafView
Class11=CViewFrame

[CLS:CMsdiApp]
Type=0
HeaderFile=Msdi.h
ImplementationFile=Msdi.cpp
Filter=N

[CLS:CMsdiDoc]
Type=0
HeaderFile=MsdiDoc.h
ImplementationFile=MsdiDoc.cpp
Filter=N

[CLS:CMsdiView]
Type=0
HeaderFile=MsdiView.h
ImplementationFile=MsdiView.cpp
Filter=C
LastObject=CMsdiView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=Msdi.cpp
ImplementationFile=Msdi.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_OUTPUT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

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
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_MSDITYPE]
Type=1
Class=CMsdiView
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
Command15=ID_VIEW_VIEW2
Command16=ID_VIEW_OUTPUT
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_APP_ABOUT
CommandCount=23

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

[DLG:IDD_MSDI_FORM]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[MNU:IDR_OUTTYPE]
Type=1
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
Command15=ID_OUTPUT_TEXT
Command16=ID_OUTPUT_ERASE
Command17=ID_VIEW_OUTPUT
Command18=ID_VIEW_VIEW2
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_WINDOW_CASCADE
Command22=ID_WINDOW_TILE_HORZ
Command23=ID_WINDOW_ARRANGE
Command24=ID_APP_ABOUT
CommandCount=24

[CLS:COutView]
Type=0
HeaderFile=outview.h
ImplementationFile=outview.cpp
BaseClass=CEditView
LastObject=COutView
Filter=C
VirtualFilter=VWC

[CLS:CMSDIWinApp]
Type=0
HeaderFile=msdiapp.h
ImplementationFile=msdiapp.cpp
BaseClass=CWinApp
LastObject=CMSDIWinApp

[CLS:CMSDIFrame]
Type=0
HeaderFile=msdifrm.h
ImplementationFile=msdifrm.cpp
BaseClass=CMDIChildWnd
LastObject=CMSDIFrame

[CLS:CGrafView]
Type=0
HeaderFile=grafview.h
ImplementationFile=grafview.cpp
BaseClass=CView
LastObject=CGrafView

[CLS:CViewFrame]
Type=0
HeaderFile=viewfrm.h
ImplementationFile=viewfrm.cpp
BaseClass=CMDIChildWnd
LastObject=CViewFrame

