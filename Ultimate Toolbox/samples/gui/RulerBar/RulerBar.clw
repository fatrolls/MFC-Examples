; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRulerBarView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RulerBar.h"
LastPage=0

ClassCount=6
Class1=CRulerBarApp
Class2=CRulerBarDoc
Class3=CRulerBarView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CChildFrame
Resource2=IDR_TEXTTYPE
Class6=CCustomizeRulersDlg
Resource3=IDD_DIALOG_RULERS

[CLS:CRulerBarApp]
Type=0
HeaderFile=RulerBar.h
ImplementationFile=RulerBar.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CRulerBarApp

[CLS:CRulerBarDoc]
Type=0
HeaderFile=RulerBarDoc.h
ImplementationFile=RulerBarDoc.cpp
Filter=N

[CLS:CRulerBarView]
Type=0
HeaderFile=RulerBarView.h
ImplementationFile=RulerBarView.cpp
Filter=C
BaseClass=CEditView
VirtualFilter=VWC
LastObject=CRulerBarView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


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
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_TEXTTYPE]
Type=1
Class=CRulerBarView
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
Command17=ID_VIEW_CUSTOMIZE_RULERS
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
CommandCount=22

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

[DLG:IDD_DIALOG_RULERS]
Type=1
Class=CCustomizeRulersDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_HORZ,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_UNIT,combobox,1344339971
Control6=IDC_CHECK_VERT,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_SIZE,edit,1350631552

[CLS:CCustomizeRulersDlg]
Type=0
HeaderFile=CustomizeRulersDlg.h
ImplementationFile=CustomizeRulersDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCustomizeRulersDlg

