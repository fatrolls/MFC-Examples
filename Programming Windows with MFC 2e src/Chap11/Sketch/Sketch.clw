; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLine
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Sketch.h"
LastPage=0

ClassCount=6
Class1=CSketchApp
Class2=CSketchDoc
Class3=CSketchView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CLine
Resource2=IDD_ABOUTBOX

[CLS:CSketchApp]
Type=0
HeaderFile=Sketch.h
ImplementationFile=Sketch.cpp
Filter=N

[CLS:CSketchDoc]
Type=0
HeaderFile=SketchDoc.h
ImplementationFile=SketchDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSketchView]
Type=0
HeaderFile=SketchView.h
ImplementationFile=SketchView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CSketchView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Sketch.cpp
ImplementationFile=Sketch.cpp
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
Command7=ID_VIEW_GRID
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_VIEW_GRID
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[CLS:CLine]
Type=0
HeaderFile=Line.h
ImplementationFile=Line.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CLine
VirtualFilter=C

