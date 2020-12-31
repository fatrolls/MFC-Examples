; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileExplorerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "fileexplorer.h"
LastPage=0

ClassCount=7
Class1=CFileExplorerApp
Class2=CAboutDlg
Class3=CFileExplorerDoc
Class4=CFileExplorerView
Class5=CLeftView
Class6=CMainFrame
Class7=COXShellObjectList

ResourceCount=2
Resource1=IDR_VIEWTYPE
Resource2=IDR_MAINFRAME

[CLS:CFileExplorerApp]
Type=0
BaseClass=CWinApp
HeaderFile=FileExplorer.h
ImplementationFile=FileExplorer.cpp
Filter=N
VirtualFilter=AC
LastObject=CFileExplorerApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=FileExplorer.cpp
ImplementationFile=FileExplorer.cpp
LastObject=CAboutDlg

[CLS:CFileExplorerDoc]
Type=0
BaseClass=CDocument
HeaderFile=FileExplorerDoc.h
ImplementationFile=FileExplorerDoc.cpp

[CLS:CFileExplorerView]
Type=0
BaseClass=CView
HeaderFile=FileExplorerView.h
ImplementationFile=FileExplorerView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CFileExplorerView

[CLS:CLeftView]
Type=0
BaseClass=CView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CLeftView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:COXShellObjectList]
Type=0
BaseClass=CListCtrl
HeaderFile=OXShellObjectList.h
ImplementationFile=OXShellObjectList.cpp

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_VIEW_LARGEICON
Command2=ID_VIEW_SMALLICON
Command3=ID_VIEW_LIST
Command4=ID_VIEW_DETAILS
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_VIEWTYPE]
Type=1
Class=?
Command1=ID_VIEW_LARGEICON
Command2=ID_VIEW_SMALLICON
Command3=ID_VIEW_LIST
Command4=ID_VIEW_DETAILS
CommandCount=4

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

