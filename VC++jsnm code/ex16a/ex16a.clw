; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStudentView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex16a.h"
LastPage=0

ClassCount=5
Class1=CEx16aApp
Class2=CAboutDlg
Class3=CMainFrame
Class4=CStudentDoc
Class5=CStudentView

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_STUDENT

[CLS:CEx16aApp]
Type=0
BaseClass=CWinApp
HeaderFile=ex16a.h
ImplementationFile=ex16a.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ex16a.cpp
ImplementationFile=ex16a.cpp
LastObject=CAboutDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CStudentDoc]
Type=0
BaseClass=CDocument
HeaderFile=StuDoc.h
ImplementationFile=StuDoc.cpp

[CLS:CStudentView]
Type=0
BaseClass=CFormView
HeaderFile=StuView.h
ImplementationFile=StuView.cpp
Filter=D
VirtualFilter=VWC
LastObject=ID_STUDENT_PREV

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_STUDENT]
Type=1
Class=CStudentView
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_GRADE,edit,1350631552
Control6=IDC_CLEAR,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
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

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_CLEAR_ALL
Command8=ID_STUDENT_HOME
Command9=ID_STUDENT_PREV
Command10=ID_STUDENT_NEXT
Command11=ID_STUDENT_END
Command12=ID_STUDENT_DEL
Command13=ID_STUDENT_INS
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

