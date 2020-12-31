; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx12aView
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex12a.h"
LastPage=0

ClassCount=10
Class1=CEx12aApp
Class2=CAboutDlg
Class3=CEx12aDoc
Class4=CEx12aView
Class5=CMainFrame
Class6=CPage1
Class7=CPage2
Class8=CPage3
Class9=CPage4

ResourceCount=6
Resource1=IDD_PAGE4
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_PAGE3
Resource5=IDD_PAGE2
Class10=CFontSheet
Resource6=IDD_PAGE1

[CLS:CEx12aApp]
Type=0
BaseClass=CWinApp
HeaderFile=ex12a.h
ImplementationFile=ex12a.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ex12a.cpp
ImplementationFile=ex12a.cpp
LastObject=CAboutDlg

[CLS:CEx12aDoc]
Type=0
BaseClass=CDocument
HeaderFile=ex12aDoc.h
ImplementationFile=ex12aDoc.cpp

[CLS:CEx12aView]
Type=0
BaseClass=CView
HeaderFile=ex12aView.h
ImplementationFile=ex12aView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_FORMAT_SELECTION

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CPage1]
Type=0
BaseClass=CPropertyPage
HeaderFile=Property.h
ImplementationFile=Property.cpp

[CLS:CPage2]
Type=0
BaseClass=CPropertyPage
HeaderFile=Property.h
ImplementationFile=Property.cpp

[CLS:CPage3]
Type=0
BaseClass=CPropertyPage
HeaderFile=Property.h
ImplementationFile=Property.cpp

[CLS:CPage4]
Type=0
BaseClass=CPropertyPage
HeaderFile=Property.h
ImplementationFile=Property.cpp
Filter=D
VirtualFilter=idWC
LastObject=CPage4

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PAGE1]
Type=1
Class=CPage1
ControlCount=3
Control1=IDC_FONT,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO3,button,1342177289

[DLG:IDD_PAGE2]
Type=1
Class=CPage2
ControlCount=3
Control1=IDC_BOLD,button,1342242819
Control2=IDC_ITALIC,button,1342242819
Control3=IDC_UNDERLINE,button,1342242819

[DLG:IDD_PAGE3]
Type=1
Class=CPage3
ControlCount=3
Control1=IDC_COLOR,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO3,button,1342177289

[DLG:IDD_PAGE4]
Type=1
Class=CPage4
ControlCount=2
Control1=IDC_FONTSIZE,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177330

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

[MNU:IDR_MAINFRAME]
Type=1
Class=?
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
Command11=ID_EDIT_CLEAR_ALL
Command12=ID_FORMAT_DEFAULT
Command13=ID_FORMAT_SELECTION
Command14=ID_TRANSFER_GETDATA
Command15=ID_TRANSFER_STOREDATA
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_TRANSFER_GETDATA
Command9=ID_TRANSFER_STOREDATA
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[CLS:CFontSheet]
Type=0
HeaderFile=property.h
ImplementationFile=property.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CFontSheet

