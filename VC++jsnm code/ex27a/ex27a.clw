; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex27a.h"
LastPage=0

ClassCount=7
Class1=CEx27aApp
Class2=CAboutDlg
Class3=CEx27aDoc
Class4=CEx27aView
Class5=CInPlaceFrame
Class6=CMainFrame
Class7=CTextDialog

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDR_SRVR_INPLACE
Resource3=IDR_SRVR_EMBEDDED
Resource4=IDD_ABOUTBOX
Resource5=IDD_DIALOG1

[CLS:CEx27aApp]
Type=0
BaseClass=CWinApp
HeaderFile=ex27a.h
ImplementationFile=ex27a.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ex27a.cpp
ImplementationFile=ex27a.cpp
LastObject=CAboutDlg

[CLS:CEx27aDoc]
Type=0
BaseClass=COleServerDoc
HeaderFile=ex27adoc.h
ImplementationFile=ex27adoc.cpp

[CLS:CEx27aView]
Type=0
BaseClass=CView
HeaderFile=ex27aview.h
ImplementationFile=ex27aview.cpp

[CLS:CInPlaceFrame]
Type=0
BaseClass=COleIPFrameWnd
HeaderFile=IPFRAME.H
ImplementationFile=Ipframe.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MAINFRM.H
ImplementationFile=Mainfrm.cpp

[CLS:CTextDialog]
Type=0
BaseClass=CDialog
HeaderFile=Textdialog.h
ImplementationFile=Textdialog.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG1]
Type=1
Class=CTextDialog
ControlCount=3
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_SRVR_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_SRVR_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_VIEW_TOOLBAR
Command6=ID_MODIFY
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_SRVR_EMBEDDED]
Type=1
Class=?
Command1=ID_FILE_UPDATE
Command2=ID_FILE_PRINT
Command3=ID_FILE_PRINT_PREVIEW
Command4=ID_FILE_PRINT_SETUP
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_MODIFY
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_SRVR_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_CANCEL_EDIT_SRVR
CommandCount=9

[ACL:IDR_SRVR_EMBEDDED]
Type=1
Class=?
Command1=ID_FILE_UPDATE
Command2=ID_FILE_PRINT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
CommandCount=12

