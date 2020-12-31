; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMailSendDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mailsend.h"
LastPage=0

ClassCount=5
Class1=CCgiHandler
Class2=CMailMessage
Class3=CMailSendApp
Class4=CAboutDlg
Class5=CMailSendDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDD_MAILSEND_DIALOG
Resource3=IDD_ABOUTBOX
Resource4=IDD_MAILSEND_DIALOG (English (Canada))

[CLS:CCgiHandler]
Type=0
BaseClass=COXOwnThreadCmdTarget
HeaderFile=CgiHandler.h
ImplementationFile=CgiHandler.cpp

[CLS:CMailMessage]
Type=0
BaseClass=COXOwnThreadCmdTarget
HeaderFile=MailMessage.h
ImplementationFile=MailMessage.cpp

[CLS:CMailSendApp]
Type=0
BaseClass=CWinApp
HeaderFile=MailSend.h
ImplementationFile=MailSendDlg.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MailSendDlg.cpp
ImplementationFile=MailSendDlg.cpp

[CLS:CMailSendDlg]
Type=0
BaseClass=CDialog
HeaderFile=MailSendDlg.h
ImplementationFile=MailSendDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_REMOVEATTACHMENT

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_MAILSEND_DIALOG]
Type=1
Class=CMailSendDlg
ControlCount=15
Control1=IDC_PROFILE,edit,1350631552
Control2=IDC_PASSWORD,edit,1350631552
Control3=IDC_ADDRESS,edit,1350631552
Control4=IDC_SUBJECT,edit,1350631552
Control5=IDC_CONTENT,edit,1352728580
Control6=IDC_ATTACHMENT,edit,1350631552
Control7=IDC_SEND_MAIL,button,1342242816
Control8=IDC_ABOUT,button,1342242816
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_MAILSEND_DIALOG (English (Canada))]
Type=1
Class=CMailSendDlg
ControlCount=17
Control1=IDC_PROFILE,edit,1350631552
Control2=IDC_PASSWORD,edit,1350631552
Control3=IDC_ADDRESS,edit,1350631552
Control4=IDC_SUBJECT,edit,1350631552
Control5=IDC_CONTENT,edit,1352728580
Control6=IDC_SEND_MAIL,button,1342242816
Control7=IDC_ABOUT,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_LIST_ATTACHMENTS,listbox,1352728833
Control16=IDC_BUTTON_ADDATTACHMENT,button,1342242816
Control17=IDC_BUTTON_REMOVEATTACHMENT,button,1342242816

