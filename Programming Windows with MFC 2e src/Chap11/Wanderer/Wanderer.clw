; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wanderer.h"
LastPage=0

ClassCount=6
Class1=CDriveView
Class2=CFileView
Class3=CMainFrame
Class4=CWandererApp
Class5=CAboutDlg
Class6=CWandererDoc

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX

[CLS:CDriveView]
Type=0
BaseClass=CTreeView
HeaderFile=DriveView.h
ImplementationFile=DriveView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CFileView]
Type=0
BaseClass=CListView
HeaderFile=FileView.h
ImplementationFile=FileView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CWandererApp]
Type=0
BaseClass=CWinApp
HeaderFile=Wanderer.h
ImplementationFile=Wanderer.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Wanderer.cpp
ImplementationFile=Wanderer.cpp
LastObject=CAboutDlg

[CLS:CWandererDoc]
Type=0
BaseClass=CDocument
HeaderFile=WandererDoc.h
ImplementationFile=WandererDoc.cpp

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
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_LARGE_ICONS
Command3=ID_VIEW_SMALL_ICONS
Command4=ID_VIEW_LIST
Command5=ID_VIEW_DETAILS
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

