; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MdiSquares.h"
LastPage=0

ClassCount=9
Class1=CMdiSquaresApp
Class2=CSquaresDoc
Class3=CSquaresView
Class4=CMainFrame
Class7=CChildFrame
Class9=CAboutDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDR_MDISQUTYPE
Resource3=IDD_ABOUTBOX

[CLS:CMdiSquaresApp]
Type=0
HeaderFile=MdiSquares.h
ImplementationFile=MdiSquares.cpp
Filter=N

[CLS:CSquaresDoc]
Type=0
HeaderFile=SquaresDoc.h
ImplementationFile=SquaresDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSquaresView]
Type=0
HeaderFile=SquaresView.h
ImplementationFile=SquaresView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


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
HeaderFile=MdiSquares.cpp
ImplementationFile=MdiSquares.cpp
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
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MDISQUTYPE]
Type=1
Class=CSquaresView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_COLOR_RED
Command9=ID_COLOR_YELLOW
Command10=ID_COLOR_GREEN
Command11=ID_COLOR_CYAN
Command12=ID_COLOR_BLUE
Command13=ID_COLOR_WHITE
Command14=ID_WINDOW_NEW
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_APP_ABOUT
CommandCount=18

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

