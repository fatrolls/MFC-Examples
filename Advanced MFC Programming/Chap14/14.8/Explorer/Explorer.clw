; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDirView
LastTemplate=CTreeView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Explorer.h"
LastPage=0

ClassCount=6
Class1=CExplorerApp
Class2=CExplorerDoc
Class3=CExplorerView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CDirView
Resource2=IDR_MAINFRAME

[CLS:CExplorerApp]
Type=0
HeaderFile=Explorer.h
ImplementationFile=Explorer.cpp
Filter=N

[CLS:CExplorerDoc]
Type=0
HeaderFile=Doc.h
ImplementationFile=Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CExplorerDoc

[CLS:CExplorerView]
Type=0
HeaderFile=View.h
ImplementationFile=View.cpp
Filter=C
LastObject=CExplorerView
BaseClass=CListView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=Explorer.cpp
ImplementationFile=Explorer.cpp
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
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_WINDOW_SPLIT
Command16=ID_VIEW_LARGEICONS
Command17=ID_VIEW_SMALLICONS
Command18=ID_VIEW_LIST
Command19=ID_VIEW_DETAILS
Command20=ID_APP_ABOUT
CommandCount=20

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

[CLS:CDirView]
Type=0
HeaderFile=DirView.h
ImplementationFile=DirView.cpp
BaseClass=CTreeView
Filter=C
VirtualFilter=VWC
LastObject=CDirView

