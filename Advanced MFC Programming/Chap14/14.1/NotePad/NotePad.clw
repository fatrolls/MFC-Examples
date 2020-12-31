; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNotePadView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NotePad.h"
LastPage=0

ClassCount=5
Class1=CNotePadApp
Class2=CNotePadDoc
Class3=CNotePadView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME

[CLS:CNotePadApp]
Type=0
HeaderFile=NotePad.h
ImplementationFile=NotePad.cpp
Filter=N

[CLS:CNotePadDoc]
Type=0
HeaderFile=NPDoc.h
ImplementationFile=NPDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CNotePadDoc

[CLS:CNotePadView]
Type=0
HeaderFile=NPView.h
ImplementationFile=NPView.cpp
Filter=C
LastObject=ID_SEARCH_FINDREPLACE
BaseClass=CEditView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_SEARCH_FINDREPLACE



[CLS:CAboutDlg]
Type=0
HeaderFile=NotePad.cpp
ImplementationFile=NotePad.cpp
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
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_DELETE
Command15=ID_EDIT_SELECTALL
Command16=ID_EDIT_TIMEDATE
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_SEARCH_FIND
Command20=ID_SEARCH_REPLACE
Command21=ID_SEARCH_FINDNEXT
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

