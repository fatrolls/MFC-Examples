; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRanDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SecureChat.h"

ClassCount=5
Class1=CSecureChatApp
Class2=CSecureChatDlg

ResourceCount=5
Resource2=IDD_SECURECHAT_DIALOG
Resource1=IDR_MAINFRAME
Resource3=IDD_SECURECHAT_DIALOG (English (U.S.))
Class3=CHistoryEdit
Resource4=IDD_SECURECHAT_DIALOG (Neutral)
Class4=CRanDialog
Class5=MyListCtrl
Resource5=IDD_RANDOM (Neutral)

[CLS:CSecureChatApp]
Type=0
HeaderFile=SecureChat.h
ImplementationFile=SecureChat.cpp
Filter=N

[CLS:CSecureChatDlg]
Type=0
HeaderFile=SecureChatDlg.h
ImplementationFile=SecureChatDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSecureChatDlg



[DLG:IDD_SECURECHAT_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSecureChatDlg

[DLG:IDD_SECURECHAT_DIALOG (English (U.S.))]
Type=1
Class=CSecureChatDlg
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_TXTOUT,edit,1352729924
Control3=IDC_SIMPLELIBTEST,button,1342242816

[DLG:IDD_SECURECHAT_DIALOG (Neutral)]
Type=1
Class=CSecureChatDlg
ControlCount=27
Control1=IDC_STARTSTOPSERVER,button,1342242816
Control2=IDC_ADDRESS,edit,1350631552
Control3=IDC_PORTNR,edit,1350631552
Control4=IDC_NROFIO,edit,1350631552
Control5=IDC_MAXCONNECT,edit,1350631552
Control6=IDC_DISCONNECT,button,1342242816
Control7=IDC_DISCONNECTALL,button,1342242816
Control8=IDC_TEXT,edit,1352732996
Control9=IDC_SENDTXT,button,1342242816
Control10=IDC_KEYSIZE,edit,1350631552
Control11=IDC_SIMPLELIBTEST,button,1342242816
Control12=IDC_RSATEST,button,1342242816
Control13=IDC_DHTEST,button,1342242816
Control14=IDC_GENERATEKEY,button,1342242816
Control15=IDCANCEL,button,1342242816
Control16=IDC_TXTOUT,edit,1352729924
Control17=IDC_KEYSIZETXT,static,1342308352
Control18=IDC_TOPTAP,SysTabControl32,1342177282
Control19=IDC_BIGLOGG,button,1073741831
Control20=IDC_SMALLLOGG,button,1073741831
Control21=IDC_LISTPLACEHOLDER,button,1073741831
Control22=IDC_USERLIST,SysListView32,1350631429
Control23=IDC_SERVERADRESSTXT,static,1342308352
Control24=IDC_PORTTXT,static,1342308352
Control25=IDC_TXTNROFIOWORKER,static,1342308352
Control26=IDC_TXTMAXCONNECT,static,1342308352
Control27=IDC_CLEARLOG,button,1342242816

[CLS:CHistoryEdit]
Type=0
HeaderFile=HistoryEdit.h
ImplementationFile=HistoryEdit.cpp
BaseClass=CEdit
LastObject=CHistoryEdit

[CLS:CRanDialog]
Type=0
HeaderFile=RanDialog.h
ImplementationFile=RanDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRanDialog

[DLG:IDD_RANDOM (Neutral)]
Type=1
Class=CRanDialog
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308353
Control3=IDC_PROGRESS,msctls_progress32,1350565889

[CLS:MyListCtrl]
Type=0
HeaderFile=MyListCtrl.h
ImplementationFile=MyListCtrl.cpp
BaseClass=CListCtrl

