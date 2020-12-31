; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRoll32App
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "roll32.h"
LastPage=0

ClassCount=6
Class1=CExample
Class2=CMainFrame
Class3=CMaxVirtDialog
Class4=CRoll32App
Class5=CRoll32Doc
Class6=CRoll32View

ResourceCount=4
Resource1=IDR_ROLL32TYPE (Dutch (Belgium))
Resource2=ID_EXAMPLE (Dutch (Belgium))
Resource3=IDR_MAINFRAME (Dutch (Belgium))
Resource4=ID_OVERLOAD_MAX (Dutch (Belgium))

[CLS:CExample]
Type=0
BaseClass=COXRollup
HeaderFile=EXAMPLE.H
ImplementationFile=EXAMPLE.CPP
LastObject=CExample

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=Mainfrm.cpp

[CLS:CMaxVirtDialog]
Type=0
BaseClass=COXRollup
HeaderFile=MAXVIRTD.H
ImplementationFile=MAXVIRTD.CPP

[CLS:CRoll32App]
Type=0
BaseClass=CWinApp
HeaderFile=ROLL32.H
ImplementationFile=Roll32.cpp
Filter=N
VirtualFilter=AC
LastObject=CRoll32App

[CLS:CRoll32Doc]
Type=0
BaseClass=CDocument
HeaderFile=ROLL3DOC.H
ImplementationFile=ROLL3DOC.CPP

[CLS:CRoll32View]
Type=0
BaseClass=CView
HeaderFile=ROLL3VW.H
ImplementationFile=Roll3vw.cpp

[DLG:ID_EXAMPLE]
Type=1
Class=CExample

[DLG:ID_OVERLOAD_MAX]
Type=1
Class=CMaxVirtDialog

[MNU:IDR_MAINFRAME (Dutch (Belgium))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_STATUS_BAR
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_ROLL32TYPE (Dutch (Belgium))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_VIEW_STATUS_BAR
Command5=ID_VIEW_ROLLUPTEST
Command6=ID_WINDOW_NEW
Command7=ID_WINDOW_CASCADE
Command8=ID_WINDOW_TILE_HORZ
Command9=ID_WINDOW_ARRANGE
Command10=ID_APP_ABOUT
CommandCount=10

[DLG:ID_EXAMPLE (Dutch (Belgium))]
Type=1
Class=?
ControlCount=4
Control1=IDC_CAPTION,static,1073741825
Control2=IDC_TEST_EDIT,edit,1350631620
Control3=IDC_BTN_APPLY,button,1342242816
Control4=IDC_STATIC,static,1342308353

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

[DLG:ID_OVERLOAD_MAX (Dutch (Belgium))]
Type=1
Class=?
ControlCount=2
Control1=IDC_CAPTION,static,1073741825
Control2=IDC_STATIC,static,1342308353

