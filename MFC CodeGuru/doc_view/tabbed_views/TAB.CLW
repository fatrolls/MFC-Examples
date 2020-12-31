; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTabWnd
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tab.h"
LastPage=0

ClassCount=7
Class1=CTabApp
Class2=CTabDoc
Class3=CTabView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_TABTYPE
Class5=CAboutDlg
Class6=CChildFrame
Class7=CTabWnd
Resource3=IDR_MAINFRAME

[CLS:CTabApp]
Type=0
HeaderFile=Tab.h
ImplementationFile=Tab.cpp
Filter=N
LastObject=CTabApp

[CLS:CTabDoc]
Type=0
HeaderFile=TabDoc.h
ImplementationFile=TabDoc.cpp
Filter=N

[CLS:CTabView]
Type=0
HeaderFile=TabView.h
ImplementationFile=TabView.cpp
Filter=C
LastObject=CTabView
BaseClass=CListView
VirtualFilter=VWC

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
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame

[CLS:CAboutDlg]
Type=0
HeaderFile=Tab.cpp
ImplementationFile=Tab.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
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
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_TABTYPE]
Type=1
Class=CTabView
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
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

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

[CLS:CTabWnd]
Type=0
HeaderFile=\Sealite\include\tabwnd.h
ImplementationFile=tabwnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CTabWnd

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_SAVE
Command2=ID_PARENT
Command3=ID_VIEW_LARGEICONS
Command4=ID_VIEW_DETAILS
Command5=ID_FOLDER_ADD
Command6=ID_FOLDER_REMOVE
Command7=ID_FOLDER_ADDTOCD
CommandCount=7

