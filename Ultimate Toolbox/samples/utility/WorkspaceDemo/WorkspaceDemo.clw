; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWorkspaceDemoApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "workspacedemo.h"
LastPage=0

ClassCount=11
Class1=CChildFrame
Class2=CMainFrame
Class3=CSplitChildFrame
Class4=CWorkspaceDemoApp
Class5=CWorkspaceDlg
Class6=CWorkspaceGraphDoc
Class7=CWorkspaceGraphPropView
Class8=CWorkspaceGraphView
Class9=CWorkspaceLengthView
Class10=CWorkspaceTextDoc
Class11=CWorkspaceTextView

ResourceCount=9
Resource1=IDD_GRAPH_FORM (Dutch (Belgium))
Resource2=IDD_LENGTH_FORM (Dutch (Belgium))
Resource3=IDD_WORKSPACE_DLG (Dutch (Belgium))
Resource4=IDR_SECOND_TOOLBAR (Dutch (Belgium))
Resource5=IDR_GRAPHTYPE (Dutch (Belgium))
Resource6=IDR_WORKSPTYPE (Dutch (Belgium))
Resource7=IDR_LENGTHTYPE (Dutch (Belgium))
Resource8=IDR_MAINFRAME (Dutch (Belgium))
Resource9=IDD_GRAPHPROP_FORM (Dutch (Belgium))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CSplitChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=SplitChildFrm.h
ImplementationFile=SplitChildFrm.cpp

[CLS:CWorkspaceDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=WorkspaceDemo.h
ImplementationFile=WorkspaceDemo.cpp
Filter=N
VirtualFilter=AC
LastObject=CWorkspaceDemoApp

[CLS:CWorkspaceDlg]
Type=0
BaseClass=CDialog
HeaderFile=WorkspaceDlg.h
ImplementationFile=WorkspaceDlg.cpp

[CLS:CWorkspaceGraphDoc]
Type=0
BaseClass=CDocument
HeaderFile=WorkspaceGraphDoc.h
ImplementationFile=WorkspaceGraphDoc.cpp

[CLS:CWorkspaceGraphPropView]
Type=0
BaseClass=CFormView
HeaderFile=WorkspaceGraphPropView.h
ImplementationFile=WorkspaceGraphPropView.cpp

[CLS:CWorkspaceGraphView]
Type=0
BaseClass=CFormView
HeaderFile=WorkspaceGraphView.h
ImplementationFile=WorkspaceGraphView.cpp

[CLS:CWorkspaceLengthView]
Type=0
BaseClass=CFormView
HeaderFile=WorkspaceLengthView.h
ImplementationFile=WorkspaceLengthView.cpp

[CLS:CWorkspaceTextDoc]
Type=0
BaseClass=CDocument
HeaderFile=WorkspaceTextDoc.h
ImplementationFile=WorkspaceTextDoc.cpp

[CLS:CWorkspaceTextView]
Type=0
BaseClass=CEditView
HeaderFile=WorkspaceTextView.h
ImplementationFile=WorkspaceTextView.cpp

[DLG:IDD_WORKSPACE_DLG]
Type=1
Class=CWorkspaceDlg

[DLG:IDD_GRAPHPROP_FORM]
Type=1
Class=CWorkspaceGraphPropView

[DLG:IDD_GRAPH_FORM]
Type=1
Class=CWorkspaceGraphView

[DLG:IDD_LENGTH_FORM]
Type=1
Class=CWorkspaceLengthView

[DLG:IDD_GRAPH_FORM (Dutch (Belgium))]
Type=1
Class=?
ControlCount=1
Control1=IDC_GROUP,button,1342177287

[DLG:IDD_GRAPHPROP_FORM (Dutch (Belgium))]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COLOR,edit,1350633600
Control3=IDC_COLOR_BROWSE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SIDES,edit,1350633600
Control6=IDC_SIDES_SPIN,msctls_updown32,1342177334

[TB:IDR_MAINFRAME (Dutch (Belgium))]
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

[TB:IDR_SECOND_TOOLBAR (Dutch (Belgium))]
Type=1
Class=?
Command1=ID_CIRCLE
Command2=ID_SQUARE
CommandCount=2

[MNU:IDR_MAINFRAME (Dutch (Belgium))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_TOOLS_WORKSPACES
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_WORKSPTYPE (Dutch (Belgium))]
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
Command17=ID_TOOLS_WORKSPACES
Command18=ID_WINDOW_NEWTEXTWINDOW
Command19=ID_WINDOW_NEWLENGTHWINDOW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_WINDOW_CLOSEALL
Command24=ID_APP_ABOUT
CommandCount=24

[MNU:IDR_LENGTHTYPE (Dutch (Belgium))]
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
Command17=ID_TOOLS_WORKSPACES
Command18=ID_WINDOW_NEWTEXTWINDOW
Command19=ID_WINDOW_NEWLENGTHWINDOW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_WINDOW_CLOSEALL
Command24=ID_APP_ABOUT
CommandCount=24

[MNU:IDR_GRAPHTYPE (Dutch (Belgium))]
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
Command17=ID_TOOLS_WORKSPACES
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_WINDOW_CLOSEALL
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME (Dutch (Belgium))]
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

[DLG:IDD_WORKSPACE_DLG (Dutch (Belgium))]
Type=1
Class=?
ControlCount=8
Control1=IDCANCEL,button,1342242816
Control2=IDC_REGISTRY_TYPE,button,1342308361
Control3=IDC_FILE_TYPE,button,1342177289
Control4=IDC_FILE_PATH,edit,1350762624
Control5=IDC_BROWSE,button,1342242816
Control6=IDC_LOAD,button,1342242816
Control7=IDC_STORE,button,1342242816
Control8=IDC_REGISTRY,edit,1350631552

[DLG:IDD_LENGTH_FORM (Dutch (Belgium))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LENGTH,edit,1350633600
Control3=IDC_LENGTH_SPIN,msctls_updown32,1342177334

