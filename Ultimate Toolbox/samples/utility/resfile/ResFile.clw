; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CResFileApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resfile.h"
LastPage=0

ClassCount=6
Class1=CChildFrame
Class2=CDlgResEdit
Class3=CMainFrame
Class4=CResFileApp
Class5=CResLibDoc
Class6=CResLibView

ResourceCount=3
Resource1=IDR_RESLIBTYPE
Resource2=IDR_MAINFRAME
Resource3=IDD_RES_EDIT

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CDlgResEdit]
Type=0
BaseClass=CDialog
HeaderFile=DlgResEdit.h
ImplementationFile=DlgResEdit.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CResFileApp]
Type=0
BaseClass=CWinApp
HeaderFile=ResFile.h
ImplementationFile=ResFile.cpp
Filter=N
VirtualFilter=AC
LastObject=CResFileApp

[CLS:CResLibDoc]
Type=0
BaseClass=CDocument
HeaderFile=ResLibDoc.h
ImplementationFile=ResLibDoc.cpp

[CLS:CResLibView]
Type=0
BaseClass=CTreeView
HeaderFile=ResLibView.h
ImplementationFile=ResLibView.cpp

[DLG:IDD_RES_EDIT]
Type=1
Class=CDlgResEdit
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_DUMP,edit,1353779204
Control3=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_RESLIBTYPE]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_SAVE
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_WINDOW_NEW
Command7=ID_WINDOW_CASCADE
Command8=ID_WINDOW_TILE_HORZ
Command9=ID_WINDOW_ARRANGE
Command10=ID_APP_ABOUT
CommandCount=10

