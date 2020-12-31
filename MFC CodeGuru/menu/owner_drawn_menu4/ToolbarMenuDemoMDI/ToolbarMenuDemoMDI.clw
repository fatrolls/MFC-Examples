; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSpawnFrameWnd
LastTemplate=CFrameWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ToolbarMenuDemoMDI.h"
LastPage=0

ClassCount=9
Class1=CToolbarMenuDemoMDIApp
Class2=CToolbarMenuDemoMDIDoc
Class3=CToolbarMenuDemoMDIView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_TOOLBATYPE
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDR_SYSTEMBAR
Resource5=IDR_TOOLBATYPE (English (U.S.))
Resource6=IDR_MAINFRAME (English (U.S.))
Class7=CSpawnFrameWnd
Class8=CSpawnMDIChildWnd
Resource7=IDD_ABOUTBOX (English (U.S.))
Class9=CSpawnMDIFrameWnd

[CLS:CToolbarMenuDemoMDIApp]
Type=0
HeaderFile=ToolbarMenuDemoMDI.h
ImplementationFile=ToolbarMenuDemoMDI.cpp
Filter=N

[CLS:CToolbarMenuDemoMDIDoc]
Type=0
HeaderFile=ToolbarMenuDemoMDIDoc.h
ImplementationFile=ToolbarMenuDemoMDIDoc.cpp
Filter=N

[CLS:CToolbarMenuDemoMDIView]
Type=0
HeaderFile=ToolbarMenuDemoMDIView.h
ImplementationFile=ToolbarMenuDemoMDIView.cpp
Filter=W
LastObject=CToolbarMenuDemoMDIView
BaseClass=CEditView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
BaseClass=CSpawnMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=W
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame

[CLS:CAboutDlg]
Type=0
HeaderFile=ToolbarMenuDemoMDI.cpp
ImplementationFile=ToolbarMenuDemoMDI.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

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
CommandCount=8
Command8=ID_APP_ABOUT

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

[MNU:IDR_TOOLBATYPE]
Type=1
Class=CToolbarMenuDemoMDIView
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
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

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
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
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

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_TOOLBATYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_FILE_NEW
Command15=ID_FILE_OPEN
Command16=ID_FILE_CLOSE
Command17=ID_FILE_SAVE
Command18=ID_FILE_SAVE_AS
Command19=ID_FILE_PRINT
Command20=ID_FILE_PRINT_PREVIEW
Command21=ID_FILE_PRINT_SETUP
Command22=ID_APP_EXIT
Command23=ID_VIEW_TOOLBAR
Command24=ID_VIEW_STATUS_BAR
Command25=ID_WINDOW_NEW
Command26=ID_WINDOW_CASCADE
Command27=ID_WINDOW_TILE_HORZ
Command28=ID_WINDOW_ARRANGE
Command29=ID_APP_ABOUT
CommandCount=29

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
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

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_SYSTEMBAR]
Type=1
Class=?
CommandCount=0

[CLS:CSpawnFrameWnd]
Type=0
HeaderFile=SpawnFrameWnd.h
ImplementationFile=SpawnFrameWnd.cpp
BaseClass=CFrameWnd
Filter=W
LastObject=CSpawnFrameWnd
VirtualFilter=fWC

[CLS:CSpawnMDIChildWnd]
Type=0
HeaderFile=SpawnMDIChildWnd.h
ImplementationFile=SpawnMDIChildWnd.cpp
BaseClass=CMDIChildWnd
Filter=W
LastObject=CSpawnMDIChildWnd
VirtualFilter=mfWC

[CLS:CSpawnMDIFrameWnd]
Type=0
HeaderFile=SpawnMDIFrameWnd.h
ImplementationFile=SpawnMDIFrameWnd.cpp
BaseClass=CMDIFrameWnd
Filter=T
LastObject=CSpawnMDIFrameWnd
VirtualFilter=fWC

