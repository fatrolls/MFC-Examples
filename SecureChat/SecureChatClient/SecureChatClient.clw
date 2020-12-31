; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSecureChatClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SecureChatClient.h"

ClassCount=2
Class1=CSecureChatClientApp
Class2=CSecureChatClientDlg

ResourceCount=6
Resource2=IDR_MAINFRAME
Resource3=IDD_SECURECHATCLIENT_DIALOG
Resource4=IDD_SECURECHATCLIENT_DIALOG (Neutral)
Resource5=IDD_RANDOM (Neutral)
Resource6=IDR_ACCELERATOR1 (Neutral)

[CLS:CSecureChatClientApp]
Type=0
HeaderFile=SecureChatClient.h
ImplementationFile=SecureChatClient.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSecureChatClientDlg]
Type=0
HeaderFile=SecureChatClientDlg.h
ImplementationFile=SecureChatClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSecureChatClientDlg



[DLG:IDD_SECURECHATCLIENT_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSecureChatClientDlg

[DLG:IDD_RANDOM (Neutral)]
Type=1
Class=?
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308353
Control3=IDC_PROGRESS,msctls_progress32,1350565889

[DLG:IDD_SECURECHATCLIENT_DIALOG (Neutral)]
Type=1
Class=CSecureChatClientDlg
ControlCount=15
Control1=IDCANCEL,button,1342242816
Control2=IDC_LOGG,edit,1344279556
Control3=IDC_IP,edit,1350631552
Control4=IDC_CONNECT,button,1342242816
Control5=IDC_NAME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_USESAVEDPUBLICKEY,button,1342242819
Control9=IDC_MESSAGE,edit,1352729668
Control10=IDC_SEND,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_PKEYSIZE,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_PORT,edit,1350631552
Control15=IDC_CLEARWINDOW,button,1342242816

[ACL:IDR_ACCELERATOR1 (Neutral)]
Type=1
Class=CSecureChatClientDlg
Command1=ID_SEND_MESSAGE
CommandCount=1

