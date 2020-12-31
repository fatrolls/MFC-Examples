; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDBDoc
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DB.h"
LastPage=0

ClassCount=9
Class1=CDBApp
Class2=CDBDoc
Class3=CDBView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMLPropertySheet
Resource2=IDD_DIALOG_PAGE1
Resource3=IDD_DIALOG_PAGE2
Resource4=IDR_MAINFRAME
Class7=CPage3
Class8=CPage1
Resource5=IDD_DIALOG_PAGE3
Class9=CPage2

[CLS:CDBApp]
Type=0
HeaderFile=DB.h
ImplementationFile=DB.cpp
Filter=N

[CLS:CDBDoc]
Type=0
HeaderFile=DBDoc.h
ImplementationFile=DBDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_PROPERTYSHEET_MODELESS

[CLS:CDBView]
Type=0
HeaderFile=DBView.h
ImplementationFile=DBView.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=DB.cpp
ImplementationFile=DB.cpp
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
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_PROPERTYSHEET_MODELESS
Command17=ID_APP_ABOUT
CommandCount=17

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
CommandCount=8

[CLS:CMLPropertySheet]
Type=0
HeaderFile=PSht.h
ImplementationFile=PSht.cpp
BaseClass=CPropertySheet
Filter=W

[DLG:IDD_DIALOG_PAGE1]
Type=1
Class=CPage1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_PAGE2]
Type=1
Class=CPage2
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_PAGE3]
Type=1
Class=CPage3
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352

[CLS:CPage3]
Type=0
HeaderFile=Page.h
ImplementationFile=Page.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:CPage1]
Type=0
HeaderFile=Page.h
ImplementationFile=Page.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:CPage2]
Type=0
HeaderFile=Page.h
ImplementationFile=Page.cpp
BaseClass=CPropertyPage
Filter=D

