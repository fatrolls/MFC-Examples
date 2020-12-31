; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgAttachments
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ZapMail.h"

ClassCount=4
Class1=CZapMailApp
Class2=CZapMailDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ZAPMAIL_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CDlgAttachments
Resource4=IDD_ATTACHMENTS

[CLS:CZapMailApp]
Type=0
HeaderFile=ZapMail.h
ImplementationFile=ZapMail.cpp
Filter=N

[CLS:CZapMailDlg]
Type=0
HeaderFile=ZapMailDlg.h
ImplementationFile=ZapMailDlg.cpp
Filter=D
LastObject=IDC_EDIT_SERVER
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ZapMailDlg.h
ImplementationFile=ZapMailDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ZAPMAIL_DIALOG]
Type=1
Class=CZapMailDlg
ControlCount=13
Control1=IDC_EDIT_SERVER,edit,1350631552
Control2=IDC_EDIT_FROM,edit,1350631552
Control3=IDC_EDIT_TO,edit,1350631552
Control4=IDC_EDIT_SUBJECT,edit,1350631552
Control5=IDC_EDIT_BODY,edit,1352732740
Control6=IDC_BUTTON_SEND,button,1342242816
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_BUTTON_ATTACHMENTS,button,1342242816

[DLG:IDD_ATTACHMENTS]
Type=1
Class=CDlgAttachments
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_FILES,listbox,1352728835
Control4=IDC_BUTTON_ADD,button,1342242816
Control5=IDC_BUTTON_REMOVE,button,1342242816

[CLS:CDlgAttachments]
Type=0
HeaderFile=DlgAttachments.h
ImplementationFile=DlgAttachments.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgAttachments
VirtualFilter=dWC

