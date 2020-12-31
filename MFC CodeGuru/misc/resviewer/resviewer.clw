; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CResviewerView
LastTemplate=CTreeView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resviewer.h"
LastPage=0

ClassCount=6
Class1=CResviewerApp
Class2=CResviewerDoc
Class3=CResviewerView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CResourceTree
Resource2=IDR_MAINFRAME

[CLS:CResviewerApp]
Type=0
HeaderFile=resviewer.h
ImplementationFile=resviewer.cpp
Filter=N
LastObject=CResviewerApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CResviewerDoc]
Type=0
HeaderFile=resviewerDoc.h
ImplementationFile=resviewerDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CResviewerDoc

[CLS:CResviewerView]
Type=0
HeaderFile=resviewerView.h
ImplementationFile=resviewerView.cpp
Filter=C
LastObject=CResviewerView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=resviewer.cpp
ImplementationFile=resviewer.cpp
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
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

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

[CLS:CResourceTree]
Type=0
HeaderFile=ResourceTree.h
ImplementationFile=ResourceTree.cpp
BaseClass=CTreeView
Filter=C
LastObject=CResourceTree
VirtualFilter=VWC

