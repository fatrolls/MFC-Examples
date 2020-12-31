; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PopupBar.h"
LastPage=0

ClassCount=5
Class1=CPopupBarApp
Class2=CPopupBarDoc
Class3=CPopupBarView
Class4=CMainFrame

ResourceCount=16
Resource1=IDD_ABOUTBOX
Resource2=IDR_SQUARETYPE
Resource3=IDR_SUARETYPE
Resource7=IDR_SQUARETYPE (English (U.S.))
Resource8=IDR_TOOLBAR_FILE (English (U.S.))
Resource9=IDR_MAINFRAME (English (U.S.))
Resource10=IDR_TOOLBAR_WINDOW
Resource11=IDR_TOOLBAR_FILE
Resource12=IDR_TOOLBAR_CUSTOMIZE (English (Canada))
Resource13=IDR_TOOLBAR_WINDOW (English (Canada))
Resource14=IDR_MAINFRAME
Class5=CChildFrame
Resource15=IDR_TOOLBAR_CUSTOMIZE
Resource16=IDD_DIALOG1

[CLS:CPopupBarApp]
Type=0
HeaderFile=PopupBar.h
ImplementationFile=PopupBar.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CPopupBarApp

[CLS:CPopupBarDoc]
Type=0
HeaderFile=PopupBarDoc.h
ImplementationFile=PopupBarDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPopupBarDoc

[CLS:CPopupBarView]
Type=0
HeaderFile=PopupBarView.h
ImplementationFile=PopupBarView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CPopupBarView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=ID_WINDOW_MODAL


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_TOOLBAR_FILE
Command6=ID_TOOLBAR_WINDOW
Command7=ID_TOOLBAR_CUSTOMIZE
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

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

[MNU:IDR_SUARETYPE]
Type=1
Class=CPopupBarView
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
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:IDR_SQUARETYPE (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_TOOLBAR_FILE
Command9=ID_TOOLBAR_WINDOW
Command10=ID_TOOLBAR_CUSTOMIZE
Command11=ID_VIEW_STATUS_BAR
Command12=ID_WINDOW_NEW
Command13=ID_WINDOW_CASCADE
Command14=ID_WINDOW_TILE_HORZ
Command15=ID_WINDOW_ARRANGE
Command16=ID_APP_ABOUT
CommandCount=16

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_TOOLBAR_FILE
Command6=ID_TOOLBAR_WINDOW
Command7=ID_TOOLBAR_CUSTOMIZE
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
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

[TB:IDR_TOOLBAR_WINDOW]
Type=1
Command1=ID_WINDOW_NEW
Command2=ID_WINDOW_CASCADE
Command3=ID_WINDOW_TILE_HORZ
Command4=ID_WINDOW_ARRANGE
CommandCount=4

[TB:IDR_TOOLBAR_FILE (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_APP_ABOUT
CommandCount=6

[TB:IDR_TOOLBAR_CUSTOMIZE]
Type=1
Command1=ID_CUSTOMIZE_TEXT_COLOR
Command2=ID_CUSTOMIZE_FILL_COLOR
Command3=ID_CUSTOMIZE_BORDER_COLOR
Command4=ID_CUSTOMIZE_BORDER_STYLE
Command5=ID_CUSTOMIZE_LINE_STYLE
Command6=ID_CUSTOMIZE_DASH_STYLE
CommandCount=6

[TB:IDR_TOOLBAR_CUSTOMIZE (English (Canada))]
Type=1
Class=?
Command1=ID_CUSTOMIZE_TEXT_COLOR
Command2=ID_CUSTOMIZE_FILL_COLOR
Command3=ID_CUSTOMIZE_BORDER_COLOR
Command4=ID_CUSTOMIZE_BORDER_STYLE
Command5=ID_CUSTOMIZE_LINE_STYLE
Command6=ID_CUSTOMIZE_DASH_STYLE
CommandCount=6

[TB:IDR_TOOLBAR_FILE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_APP_ABOUT
CommandCount=6

[TB:IDR_TOOLBAR_WINDOW (English (Canada))]
Type=1
Class=?
Command1=ID_WINDOW_NEW
Command2=ID_WINDOW_CASCADE
Command3=ID_WINDOW_TILE_HORZ
Command4=ID_WINDOW_ARRANGE
CommandCount=4

[MNU:IDR_SQUARETYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_TOOLBAR_FILE
Command9=ID_TOOLBAR_WINDOW
Command10=ID_TOOLBAR_CUSTOMIZE
Command11=ID_VIEW_STATUS_BAR
Command12=ID_WINDOW_NEW
Command13=ID_WINDOW_CASCADE
Command14=ID_WINDOW_TILE_HORZ
Command15=ID_WINDOW_ARRANGE
Command16=ID_WINDOW_MODAL
Command17=ID_APP_ABOUT
CommandCount=17

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

