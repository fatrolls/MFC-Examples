; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgSample
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CSH.h"
LastPage=0

ClassCount=7
Class1=CCSHApp
Class2=CCSHDoc
Class3=CCSHView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_SAMPLE_DIALOG
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Class6=CCSHDialog
Class7=CDlgSample
Resource4=IDD_CSH_FORM

[CLS:CCSHApp]
Type=0
HeaderFile=CSH.h
ImplementationFile=CSH.cpp
Filter=N

[CLS:CCSHDoc]
Type=0
HeaderFile=CSHDoc.h
ImplementationFile=CSHDoc.cpp
Filter=N

[CLS:CCSHView]
Type=0
HeaderFile=CSHView.h
ImplementationFile=CSHView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_BUTTON_SAMPLE_DLG

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=CSH.cpp
ImplementationFile=CSH.cpp
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
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_HELP_FINDER
Command14=ID_APP_ABOUT
CommandCount=14

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
Command14=ID_CONTEXT_HELP
Command15=ID_HELP
CommandCount=15

[DLG:IDD_CSH_FORM]
Type=1
Class=CCSHView
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342177298
Control4=IDC_CHECK_WITH_INTERNET,button,1342242819
Control5=IDC_RADIO_RADIO,button,1342177289
Control6=IDC_RADIO_TV,button,1342177289
Control7=IDC_COMBO_SELECT_SHOP,combobox,1344340226
Control8=IDC_BUTTON_HELP,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342177298
Control11=IDC_BUTTON_SAMPLE_DLG,button,1342242816

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
Command9=ID_CONTEXT_HELP
CommandCount=9

[CLS:CCSHDialog]
Type=0
HeaderFile=CSHDialog.h
ImplementationFile=CSHDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CCSHDialog

[DLG:IDD_SAMPLE_DIALOG]
Type=1
Class=CDlgSample
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177298
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_COMBO1,combobox,1344340226
Control5=IDC_LIST1,listbox,1352728835

[CLS:CDlgSample]
Type=0
HeaderFile=DlgSample.h
ImplementationFile=DlgSample.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgSample
VirtualFilter=dWC

