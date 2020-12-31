; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMenuDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Menu.h"
LastPage=0

ClassCount=5
Class1=CMenuApp
Class2=CMenuDoc
Class3=CMenuView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MENU_POPUP
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX

[CLS:CMenuApp]
Type=0
HeaderFile=Menu.h
ImplementationFile=Menu.cpp
Filter=N

[CLS:CMenuDoc]
Type=0
HeaderFile=MenuDoc.h
ImplementationFile=MenuDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_EDIT_DELETEDYNAMICMENU

[CLS:CMenuView]
Type=0
HeaderFile=MenuView.h
ImplementationFile=MenuView.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=Menu.cpp
ImplementationFile=Menu.cpp
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
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_INSERTDYNAMICMENU
Command12=ID_EDIT_DELETEDYNAMICMENU
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MENU_POPUP]
Type=1
Command1=ID__POPUPITEM1
Command2=ID__POPUPITEM2
Command3=ID__POPUPITEM3
Command4=ID__POPUPITEM4
CommandCount=4

