; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBarDialog
LastTemplate=CToolBarCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DB.h"
LastPage=0

ClassCount=7
Class1=CDBApp
Class2=CDBDoc
Class3=CDBView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource3=IDD_DIALOG
Class6=CBarDialog
Class7=CDlgToolBar

[CLS:CDBApp]
Type=0
HeaderFile=DB.h
ImplementationFile=DB.cpp
Filter=N

[CLS:CDBDoc]
Type=0
HeaderFile=DBDoc.h
ImplementationFile=DBDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CDBDoc

[CLS:CDBView]
Type=0
HeaderFile=DBView.h
ImplementationFile=DBView.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=DB.cpp
ImplementationFile=DB.cpp
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
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_DIALOG_BARDIALOG
Command17=ID_APP_ABOUT
CommandCount=17

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

[DLG:IDD_DIALOG]
Type=1
Class=CBarDialog
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CBarDialog]
Type=0
HeaderFile=BarDlg.h
ImplementationFile=BarDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CBarDialog
VirtualFilter=dWC

[TB:IDD_DIALOG]
Type=1
Class=?
Command1=ID_BUTTON_YELLOW
Command2=ID_BUTTON_GREEN
Command3=ID_BUTTON_RED
Command4=ID_BUTTON_BLUE
CommandCount=4

[CLS:CDlgToolBar]
Type=0
HeaderFile=ToolBar.h
ImplementationFile=ToolBar.cpp
BaseClass=CToolBar
Filter=D
LastObject=CDlgToolBar

