; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CToolBarEx
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "flatbar.h"
LastPage=0

ClassCount=8
Class1=CChildFrame
Class2=CFlatBarApp
Class3=CAboutDlg
Class4=CFlatBarDoc
Class5=CFlatBarView
Class6=CMainFrame
Class7=CToolBarEx

ResourceCount=7
Resource1=IDR_CHILDFRAME
Resource2=IDR_UTILITIES
Resource3=IDR_FLATBATYPE
Resource4=IDD_ABOUTBOX
Resource5=IDD_DemoPage
Resource6=IDD_ToolBarsPage
Class8=CDemoPage
Resource7=IDR_MAINFRAME

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
VirtualFilter=mfWC

[CLS:CFlatBarApp]
Type=0
BaseClass=CWinApp
HeaderFile=FlatBar.h
ImplementationFile=FlatBar.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=FlatBar.cpp
ImplementationFile=FlatBar.cpp
LastObject=CAboutDlg

[CLS:CFlatBarDoc]
Type=0
BaseClass=CDocument
HeaderFile=FlatBarDoc.h
ImplementationFile=FlatBarDoc.cpp

[CLS:CFlatBarView]
Type=0
BaseClass=CView
HeaderFile=FlatBarView.h
ImplementationFile=FlatBarView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CToolBarEx]
Type=0
BaseClass=CToolBar
HeaderFile=ToolBarEx.h
ImplementationFile=ToolBarEx.cpp
LastObject=CToolBarEx
Filter=W

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_ToggleCase
Command8=ID_FILE_PRINT
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_VIEW_FLATBAR
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_FLATBATYPE]
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
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_VIEW_FLATBAR
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME]
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

[TB:IDR_CHILDFRAME]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_REDO
Command3=ID_FindForward
Command4=ID_FindBackward
Command5=ID_ToggleWord
Command6=ID_ToggleCase
Command7=ID_ToggleRegexp
CommandCount=7

[TB:IDR_UTILITIES]
Type=1
Class=?
Command1=ID_BUTTON32790
Command2=ID_BUTTON32791
Command3=ID_BUTTON32792
Command4=ID_BUTTON32793
Command5=ID_ReplaceButton
Command6=ID_BUTTON32794
Command7=ID_BUTTON32795
Command8=ID_BUTTON32796
CommandCount=8

[DLG:IDD_ToolBarsPage]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ToolBarList,listbox,1352728835
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_DemoPage]
Type=1
Class=CDemoPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CDemoPage]
Type=0
HeaderFile=DemoPage.h
ImplementationFile=DemoPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CDemoPage

