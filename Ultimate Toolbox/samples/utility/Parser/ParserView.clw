; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "parserview.h"
LastPage=0

ClassCount=8
Class1=CChildFrame
Class2=CLeftView
Class3=CMainFrame
Class4=CParseEditView
Class5=CParserViewApp
Class6=CAboutDlg
Class7=CParserViewDoc
Class8=CParserViewView

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDR_PARSERTYPE
Resource3=IDD_ABOUTBOX

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
VirtualFilter=mfWC
LastObject=CChildFrame

[CLS:CLeftView]
Type=0
BaseClass=CTreeView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CParseEditView]
Type=0
BaseClass=CEditView
HeaderFile=ParseEditView.h
ImplementationFile=ParseEditView.cpp

[CLS:CParserViewApp]
Type=0
BaseClass=CWinApp
HeaderFile=ParserView.h
ImplementationFile=ParserView.cpp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ParserView.cpp
ImplementationFile=ParserView.cpp
LastObject=CAboutDlg

[CLS:CParserViewDoc]
Type=0
BaseClass=CDocument
HeaderFile=ParserViewDoc.h
ImplementationFile=ParserViewDoc.cpp

[CLS:CParserViewView]
Type=0
BaseClass=CView
HeaderFile=ParserViewView.h
ImplementationFile=ParserViewView.cpp

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
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_PARSERTYPE]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_WINDOW_NEW
Command5=ID_WINDOW_CASCADE
Command6=ID_WINDOW_TILE_HORZ
Command7=ID_WINDOW_ARRANGE
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_APP_ABOUT
CommandCount=2

[ACL:IDR_MAINFRAME]
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

