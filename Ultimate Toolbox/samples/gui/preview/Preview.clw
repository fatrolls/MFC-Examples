; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COXFileDialog
LastTemplate=CFileDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "preview.h"
LastPage=0

ClassCount=6
Class1=CChildFrame
Class2=CMainFrame
Class3=CPreviewApp
Class4=CPreviewDoc
Class5=CMyPreviewView

ResourceCount=2
Resource1=IDR_PREVTYPE
Resource2=IDR_MAINFRAME
Class6=COXFileDialog

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

[CLS:CPreviewApp]
Type=0
BaseClass=COXWinApp
HeaderFile=Preview.h
ImplementationFile=Preview.cpp
Filter=N
VirtualFilter=AC
LastObject=CPreviewApp

[CLS:CPreviewDoc]
Type=0
BaseClass=CDocument
HeaderFile=PreviewDoc.h
ImplementationFile=PreviewDoc.cpp

[CLS:CMyPreviewView]
Type=0
BaseClass=CView
HeaderFile=PreviewView.h
ImplementationFile=PreviewView.cpp

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_APP_EXIT
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_PREVTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_APP_EXIT
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

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

[CLS:COXFileDialog]
Type=0
HeaderFile=OXFileDialog.h
ImplementationFile=OXFileDialog.cpp
BaseClass=CFileDialog
Filter=D

