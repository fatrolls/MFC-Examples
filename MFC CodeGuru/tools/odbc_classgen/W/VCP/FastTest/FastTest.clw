; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSlowView
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FastTest.h"
LastPage=0

ClassCount=8
Class1=CFastTestApp
Class2=CFastTestDoc
Class3=CFastTestView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_FASTTETYPE
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CChildFrame
Class7=CSlowView
Resource3=IDD_ABOUTBOX
Class8=CSlowSet

[CLS:CFastTestApp]
Type=0
HeaderFile=FastTest.h
ImplementationFile=FastTest.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_FILE_SLOWVIEW

[CLS:CFastTestDoc]
Type=0
HeaderFile=FastTestDoc.h
ImplementationFile=FastTestDoc.cpp
Filter=N

[CLS:CFastTestView]
Type=0
HeaderFile=FastTestView.h
ImplementationFile=FastTestView.cpp
Filter=C
LastObject=CFastTestView
BaseClass=CListView
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
HeaderFile=FastTest.cpp
ImplementationFile=FastTest.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_FASTTETYPE]
Type=1
Class=CFastTestView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_STATUS_BAR
Command13=ID_WINDOW_NEW
Command14=ID_WINDOW_CASCADE
CommandCount=17
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command15=ID_WINDOW_TILE_HORZ
Command16=ID_WINDOW_ARRANGE
Command17=ID_APP_ABOUT

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

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_FASTVIEW
Command2=ID_FILE_SLOWVIEW
Command3=ID_FILE_CLOSE
Command4=ID_APP_EXIT
Command5=ID_VIEW_STATUS_BAR
Command6=ID_WINDOW_NEW
Command7=ID_WINDOW_CASCADE
Command8=ID_WINDOW_TILE_HORZ
Command9=ID_WINDOW_ARRANGE
Command10=ID_APP_ABOUT
CommandCount=10

[CLS:CSlowView]
Type=0
HeaderFile=SlowView.h
ImplementationFile=SlowView.cpp
BaseClass=CListView
Filter=C
VirtualFilter=VWC
LastObject=CSlowView

[CLS:CSlowSet]
Type=0
HeaderFile=SlowSet.h
ImplementationFile=SlowSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CSlowSet]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[CODE], 12, 8
Column2=[NAME], 12, 30

