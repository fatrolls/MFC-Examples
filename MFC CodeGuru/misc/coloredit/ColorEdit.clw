; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CColorEditView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ColorEdit.h"
ODLFile=ColorEdit.odl
LastPage=0

ClassCount=7
Class1=CColorEditApp
Class2=CColorEditDoc
Class3=CColorEditView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDR_CEDITTYPE
Resource3=IDD_SEARCH
Class5=CAboutDlg
Class6=CChildFrame
Class7=CSearch
Resource4=IDD_ABOUTBOX

[CLS:CColorEditApp]
Type=0
HeaderFile=ColorEdit.h
ImplementationFile=ColorEdit.cpp
Filter=N

[CLS:CColorEditDoc]
Type=0
HeaderFile=ColorEditDoc.h
ImplementationFile=ColorEditDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CColorEditView]
Type=0
HeaderFile=ColorEditView.h
ImplementationFile=ColorEditView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_EDIT_PASTE

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

[CLS:CAboutDlg]
Type=0
HeaderFile=ColorEdit.cpp
ImplementationFile=ColorEdit.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_STATIC_SCROLL,static,1342308352
Control4=IDC_STATIC,static,1342308352

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

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_REDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_FIND
Command10=ID_FILE_PRINT
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_CEDITTYPE]
Type=1
Class=CColorEditView
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
Command12=ID_EDIT_REDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_FIND
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_WINDOW_SPLIT
Command24=ID_APP_ABOUT
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_REDO
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_SEARCH]
Type=1
Class=CSearch
ControlCount=8
Control1=IDCANCEL,button,1342242816
Control2=IDC_SEARCH_STRING,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_REPLACE_STRING,edit,1350631552
Control6=IDC_FIND_NEXT,button,1342242816
Control7=IDC_REPLACE,button,1342242816
Control8=IDC_REPLACE_ALL,button,1342242816

[CLS:CSearch]
Type=0
HeaderFile=Search.h
ImplementationFile=Search.cpp
BaseClass=CDialog
Filter=D
LastObject=CSearch

