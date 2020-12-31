; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CScrngrabView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "scrngrab.h"
LastPage=0

ClassCount=5
Class1=CChildFrame
Class2=CMainFrame
Class3=CScrngrabApp
Class4=CScrngrabDoc
Class5=CScrngrabView

ResourceCount=3
Resource1=IDR_SCRNGRTYPE
Resource2=IDR_MAINFRAME
Resource3=IDD_SCRNGRAB_FORM

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CMainFrame]
Type=0
BaseClass=COXMainFrame
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CScrngrabApp]
Type=0
BaseClass=CWinApp
HeaderFile=scrngrab.h
ImplementationFile=scrngrab.cpp
Filter=N
VirtualFilter=AC
LastObject=CScrngrabApp

[CLS:CScrngrabDoc]
Type=0
BaseClass=CDocument
HeaderFile=scrngrabDoc.h
ImplementationFile=scrngrabDoc.cpp

[CLS:CScrngrabView]
Type=0
BaseClass=CFormView
HeaderFile=scrngrabView.h
ImplementationFile=scrngrabView.cpp
Filter=D
VirtualFilter=VWC
LastObject=IDC_STATICIMAGE

[DLG:IDD_SCRNGRAB_FORM]
Type=1
Class=CScrngrabView
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CAPT_BUTTON,button,1342373888
Control3=IDC_STATICIMAGE,static,1342177284
Control4=IDC_CAPT_BUTTON_ENTIRE,button,1342373888
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_STATUS_BAR
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_SCRNGRTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_VIEW_STATUS_BAR
Command5=ID_WINDOW_NEW
Command6=ID_WINDOW_CASCADE
Command7=ID_WINDOW_TILE_HORZ
Command8=ID_WINDOW_ARRANGE
Command9=ID_APP_ABOUT
CommandCount=9

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

