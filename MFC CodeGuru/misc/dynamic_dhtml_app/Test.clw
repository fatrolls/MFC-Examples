; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Test.h"
LastPage=0

ClassCount=8
Class1=CTestApp
Class2=CTestDoc
Class3=CTestView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_SETTING_DIALOG
Class5=CAboutDlg
Class6=CInstructorSet
Class7=CStudentSet
Resource2=IDD_ABOUTBOX
Resource3=IDR_TEST_MENU
Class8=CSettingDlg
Resource4=IDR_MAINFRAME

[CLS:CTestApp]
Type=0
HeaderFile=Test.h
ImplementationFile=Test.cpp
Filter=N
LastObject=CTestApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CTestDoc]
Type=0
HeaderFile=TestDoc.h
ImplementationFile=TestDoc.cpp
Filter=N

[CLS:CTestView]
Type=0
HeaderFile=TestView.h
ImplementationFile=TestView.cpp
Filter=C
BaseClass=CBrowserView
VirtualFilter=VWC
LastObject=CTestView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_OPTIONS



[CLS:CAboutDlg]
Type=0
HeaderFile=Test.cpp
ImplementationFile=Test.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
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
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_INSTRUCTOR_FORM
Command17=ID_STUDENT_FORM
Command18=ID_OPTIONS
Command19=ID_APP_ABOUT
CommandCount=19

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
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_BUTTON32772
CommandCount=9

[CLS:CInstructorSet]
Type=0
HeaderFile=InstructorSet.h
ImplementationFile=InstructorSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CInstructorSet

[DB:CInstructorSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[InstructorID], 12, 8
Column2=[Name], 12, 40
Column3=[RoomNo], 12, 10

[CLS:CStudentSet]
Type=0
HeaderFile=StudentSet.h
ImplementationFile=StudentSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CStudentSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[StudentID], 4, 4
Column2=[Name], 12, 40
Column3=[GradYear], 5, 2

[MNU:IDR_TEST_MENU]
Type=1
Class=CTestView
CommandCount=0

[DLG:IDD_SETTING_DIALOG]
Type=1
Class=CSettingDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_INST_FORM,edit,1350631552
Control4=IDC_BROWSE,button,1342242816
Control5=IDC_STATIC,static,1342308352

[CLS:CSettingDlg]
Type=0
HeaderFile=SetDlg.h
ImplementationFile=SetDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

