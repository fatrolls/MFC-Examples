; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEditDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Phones.h"
LastPage=0

ClassCount=7
Class1=CPhonesApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class2=CChildView
Class5=CPhonesListBox
Class6=CPhoneEdit
Resource2=IDR_MAINFRAME
Class7=CEditDialog
Resource3=IDD_EDITDLG

[CLS:CPhonesApp]
Type=0
HeaderFile=Phones.h
ImplementationFile=Phones.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
BaseClass=CPhonesListBox
VirtualFilter=bWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Phones.cpp
ImplementationFile=Phones.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_NEXT_PANE
Command9=ID_PREV_PANE
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_CUT
Command13=ID_EDIT_UNDO
CommandCount=13

[CLS:CPhonesListBox]
Type=0
HeaderFile=PhonesListBox.h
ImplementationFile=PhonesListBox.cpp
BaseClass=CListBox
Filter=W
LastObject=CPhonesListBox
VirtualFilter=bWC

[CLS:CPhoneEdit]
Type=0
HeaderFile=PhoneEdit.h
ImplementationFile=PhoneEdit.cpp
BaseClass=CEdit
Filter=W
LastObject=CPhoneEdit
VirtualFilter=WC

[DLG:IDD_EDITDLG]
Type=1
Class=CEditDialog
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PHONE,edit,1350631552
Control5=IDOK,button,1342242881
Control6=IDCANCEL,button,1342242880

[CLS:CEditDialog]
Type=0
HeaderFile=EditDialog.h
ImplementationFile=EditDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEditDialog

