; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CColorPage
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PropDemo.h"
LastPage=0

ClassCount=7
Class1=CPropDemoApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SIZE_PAGE
Class2=CChildView
Class5=CSizePage
Class6=CColorPage
Class7=CMyPropertySheet
Resource4=IDD_COLOR_PAGE

[CLS:CPropDemoApp]
Type=0
HeaderFile=PropDemo.h
ImplementationFile=PropDemo.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=PropDemo.cpp
ImplementationFile=PropDemo.cpp
Filter=D
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
Command1=ID_FILE_PROPERTIES
Command2=ID_APP_EXIT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_SIZE_PAGE]
Type=1
Class=CSizePage
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_WIDTH,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_HEIGHT,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_INCHES,button,1342308361
Control7=IDC_CENTIMETERS,button,1342177289
Control8=IDC_PIXELS,button,1342177289

[DLG:IDD_COLOR_PAGE]
Type=1
Class=CColorPage
ControlCount=4
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RED,button,1342308361
Control3=IDC_GREEN,button,1342177289
Control4=IDC_BLUE,button,1342177289

[CLS:CSizePage]
Type=0
HeaderFile=SizePage.h
ImplementationFile=SizePage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CSizePage
VirtualFilter=idWC

[CLS:CColorPage]
Type=0
HeaderFile=ColorPage.h
ImplementationFile=ColorPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CColorPage
VirtualFilter=idWC

[CLS:CMyPropertySheet]
Type=0
HeaderFile=MyPropertySheet.h
ImplementationFile=MyPropertySheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CMyPropertySheet

