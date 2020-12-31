; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestPrintFormDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestPrintForm.h"
LastPage=0

ClassCount=7
Class1=CTestPrintFormApp
Class2=CTestPrintFormDoc
Class3=CTestPrintFormView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_PRINT_STATUS
Resource2=IDD_DIALOG1
Resource3=IDD_TESTPRINTFORM_FORM
Class5=CAboutDlg
Class6=CPrintStatus
Resource4=IDD_ABOUTBOX
Class7=CTestPrintFormDlg
Resource5=IDR_MAINFRAME

[CLS:CTestPrintFormApp]
Type=0
HeaderFile=TestPrintForm.h
ImplementationFile=TestPrintForm.cpp
Filter=N

[CLS:CTestPrintFormDoc]
Type=0
HeaderFile=TestPrintFormDoc.h
ImplementationFile=TestPrintFormDoc.cpp
Filter=N

[CLS:CTestPrintFormView]
Type=0
HeaderFile=TestPrintFormView.h
ImplementationFile=TestPrintFormView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_CHECK1

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=TestPrintForm.cpp
ImplementationFile=TestPrintForm.cpp
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
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_TEST
Command16=ID_APP_ABOUT
CommandCount=16

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

[DLG:IDD_TESTPRINTFORM_FORM]
Type=1
Class=CTestPrintFormView
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT4,edit,1350631552
Control9=IDC_STATIC,static,1342177296
Control10=IDC_LIST1,SysListView32,1342275589
Control11=IDC_CHECK1,button,1342242819

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
CommandCount=8

[DLG:IDD_PRINT_STATUS]
Type=1
Class=CPrintStatus
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_ANIMATE1,SysAnimate32,1342177286
Control3=IDC_PROGRESS1,msctls_progress32,1342177280
Control4=IDC_PC,static,1342308354
Control5=IDC_TEXT1,static,1342308352
Control6=IDC_PAGES,static,1342308352

[CLS:CPrintStatus]
Type=0
HeaderFile=PrintStatus.h
ImplementationFile=PrintStatus.cpp
BaseClass=CDialog

[DLG:IDD_DIALOG1]
Type=1
Class=CTestPrintFormDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350631552
Control11=IDC_STATIC,static,1342177296
Control12=IDC_LIST1,SysListView32,1342275589
Control13=IDC_CHECK1,button,1342242819

[CLS:CTestPrintFormDlg]
Type=0
HeaderFile=TestPrintFormDlg.h
ImplementationFile=TestPrintFormDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

