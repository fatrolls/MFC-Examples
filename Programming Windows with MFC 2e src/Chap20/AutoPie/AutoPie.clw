; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAutoPieDoc
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AutoPie.h"
ODLFile=AutoPie.odl
LastPage=0

ClassCount=8
Class1=CAutoPieApp
Class2=CAutoPieDoc
Class3=CAutoPieView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CAutoChart
Class7=CAutoWindow
Class8=CAutoToolbar
Resource2=IDD_ABOUTBOX

[CLS:CAutoPieApp]
Type=0
HeaderFile=AutoPie.h
ImplementationFile=AutoPie.cpp
Filter=N

[CLS:CAutoPieDoc]
Type=0
HeaderFile=AutoPieDoc.h
ImplementationFile=AutoPieDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CAutoPieView]
Type=0
HeaderFile=AutoPieView.h
ImplementationFile=AutoPieView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=AutoPie.cpp
ImplementationFile=AutoPie.cpp
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
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

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

[CLS:CAutoChart]
Type=0
HeaderFile=AutoChart.h
ImplementationFile=AutoChart.cpp
BaseClass=CCmdTarget
Filter=N
VirtualFilter=C

[CLS:CAutoWindow]
Type=0
HeaderFile=AutoWindow.h
ImplementationFile=AutoWindow.cpp
BaseClass=CCmdTarget
Filter=N
VirtualFilter=C

[CLS:CAutoToolbar]
Type=0
HeaderFile=AutoToolbar.h
ImplementationFile=AutoToolbar.cpp
BaseClass=CCmdTarget
Filter=N
VirtualFilter=C

