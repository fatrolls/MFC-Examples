; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWidget
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Widget.h"
LastPage=0

ClassCount=6
Class1=CWidgetApp
Class2=CWidgetDoc
Class3=CWidgetView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CWidget
Resource2=IDD_ABOUTBOX

[CLS:CWidgetApp]
Type=0
HeaderFile=Widget.h
ImplementationFile=Widget.cpp
Filter=N

[CLS:CWidgetDoc]
Type=0
HeaderFile=WidgetDoc.h
ImplementationFile=WidgetDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CWidgetView]
Type=0
HeaderFile=WidgetView.h
ImplementationFile=WidgetView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Widget.cpp
ImplementationFile=Widget.cpp
Filter=D
LastObject=CAboutDlg

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
Command11=ID_EDIT_DELETE
Command12=ID_VIEW_STATUS_BAR
Command13=ID_INSERT_REDWIDGET
Command14=ID_INSERT_BLUEWIDGET
Command15=ID_INSERT_YELLOWWIDGET
Command16=ID_APP_ABOUT
CommandCount=16

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

