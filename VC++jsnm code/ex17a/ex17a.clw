; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStudentView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex17a.h"
LastPage=0

ClassCount=6
Class1=CEx17aApp
Class2=CStudentDoc
Class3=CStudentView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_EX17ATYPE
Resource3=IDD_STUDENT
Class5=CAboutDlg
Class6=CChildFrame
Resource7=IDR_MAINFRAME

[CLS:CEx17aApp]
Type=0
HeaderFile=ex17a.h
ImplementationFile=ex17a.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CEx17aApp

[CLS:CStudentDoc]
Type=0
HeaderFile=StuDoc.h
ImplementationFile=StuDoc.cpp
Filter=N

[CLS:CStudentView]
Type=0
HeaderFile=StuView.h
ImplementationFile=StuView.cpp
Filter=D
LastObject=ID_STUDENT_NEXT
BaseClass=CFormView
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
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ex17a.cpp
ImplementationFile=ex17a.cpp
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
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_STUDENT_HOME
Command5=ID_STUDENT_PREV
Command6=ID_STUDENT_NEXT
Command7=ID_STUDENT_END
Command8=ID_STUDENT_DEL
Command9=ID_STUDENT_INS
Command10=ID_FILE_PRINT
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_EX17ATYPE]
Type=1
Class=CStudentView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_CLEAR_ALL
Command9=ID_STUDENT_HOME
Command10=ID_STUDENT_PREV
Command11=ID_STUDENT_NEXT
Command12=ID_STUDENT_END
Command13=ID_STUDENT_DEL
Command14=ID_STUDENT_INS
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

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

[DLG:IDD_STUDENT]
Type=1
Class=CStudentView
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_GRADE,edit,1350631552
Control6=IDC_CLEAR,button,1342242816

