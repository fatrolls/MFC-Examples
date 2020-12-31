; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx32bView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex32b.h"
LastPage=0

ClassCount=8
Class1=CAddrDialog
Class2=CEx32bApp
Class3=CAboutDlg
Class4=CEx32bDoc
Class5=CEx32bView
Class6=CInPlaceFrame
Class7=CMainFrame
Class8=CValidForm

ResourceCount=7
Resource1=IDR_SRVR_EMBEDDED
Resource2=IDD_ADDRDIALOG
Resource3=IDR_CNTR_INPLACE
Resource4=IDR_SRVR_INPLACE
Resource5=IDD_ABOUTBOX
Resource6=IDD_EX32B_FORM
Resource7=IDR_MAINFRAME

[CLS:CAddrDialog]
Type=0
BaseClass=CDialog
HeaderFile=AddrDialog.h
ImplementationFile=AddrDialog.cpp
Filter=D
VirtualFilter=dWC

[CLS:CEx32bApp]
Type=0
BaseClass=CWinApp
HeaderFile=ex32b.h
ImplementationFile=ex32b.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ex32b.cpp
ImplementationFile=ex32b.cpp

[CLS:CEx32bDoc]
Type=0
BaseClass=COleServerDoc
HeaderFile=ex32bDoc.h
ImplementationFile=ex32bDoc.cpp

[CLS:CEx32bView]
Type=0
BaseClass=CValidForm
HeaderFile=ex32bView.h
ImplementationFile=ex32bView.cpp
LastObject=CEx32bView

[CLS:CInPlaceFrame]
Type=0
BaseClass=COleDocIPFrameWnd
HeaderFile=IpFrame.h
ImplementationFile=IpFrame.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CValidForm]
Type=0
BaseClass=CFormView
HeaderFile=valform.h
ImplementationFile=valform.cpp

[DLG:IDD_ADDRDIALOG]
Type=1
Class=CAddrDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SERVERNAME,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FILE,edit,1350631552

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EX32B_FORM]
Type=1
Class=CEx32bView
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PERIOD,edit,1350641792
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EMPLOYEE,combobox,1344340226
Control5=IDC_STATIC,static,1342308352
Control6=IDC_HOURS,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_JOB,edit,1350639744
Control9=IDC_SPIN1,msctls_updown32,1342177330
Control10=IDC_SUBMIT,button,1342242817
Control11=IDCANCEL,button,1342242816

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

[TB:IDR_SRVR_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_MAINFRAME]
Type=1
Class=?
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
Command14=ID_EDIT_PASTE_SPECIAL
Command15=ID_OLE_INSERT_NEW
Command16=ID_OLE_EDIT_LINKS
Command17=ID_OLE_VERB_FIRST
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_SERVER_ADDRESS
Command21=ID_APP_ABOUT
CommandCount=21

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
CommandCount=9

[MNU:IDR_SRVR_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_PASTE_SPECIAL
Command6=ID_OLE_INSERT_NEW
Command7=ID_OLE_EDIT_LINKS
Command8=ID_OLE_VERB_FIRST
Command9=ID_VIEW_TOOLBAR
Command10=ID_SERVER_ADDRESS
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_SRVR_EMBEDDED]
Type=1
Class=?
Command1=ID_FILE_UPDATE
Command2=ID_FILE_SAVE_COPY_AS
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_PASTE_SPECIAL
Command12=ID_OLE_INSERT_NEW
Command13=ID_OLE_EDIT_LINKS
Command14=ID_OLE_VERB_FIRST
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_SERVER_ADDRESS
Command18=ID_APP_ABOUT
CommandCount=18

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
Command15=ID_CANCEL_EDIT_CNTR
CommandCount=15

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[ACL:IDR_SRVR_INPLACE]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_CANCEL_EDIT_SRVR
CommandCount=9

[ACL:IDR_SRVR_EMBEDDED]
Type=1
Class=?
Command1=ID_FILE_UPDATE
Command2=ID_FILE_PRINT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_CANCEL_EDIT_CNTR
CommandCount=13

