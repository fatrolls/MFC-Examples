; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBLOBSDlg
LastTemplate=CDaoRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BLOBS.h"

ClassCount=4
Class1=CBLOBSApp
Class2=CBLOBSDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=RSOle
Resource3=IDD_BLOBS_DIALOG

[CLS:CBLOBSApp]
Type=0
HeaderFile=BLOBS.h
ImplementationFile=BLOBS.cpp
Filter=N

[CLS:CBLOBSDlg]
Type=0
HeaderFile=BLOBSDlg.h
ImplementationFile=BLOBSDlg.cpp
Filter=D
LastObject=IDC_BUTTON1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=BLOBSDlg.h
ImplementationFile=BLOBSDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BLOBS_DIALOG]
Type=1
Class=CBLOBSDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LOADIMAGE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ABOUT,button,1342242816

[CLS:RSOle]
Type=0
HeaderFile=RSOle.h
ImplementationFile=RSOle.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:RSOle]
DB=1
DBType=DAO
ColumnCount=3
Column1=[ID], 4, 4
Column2=[SomeText], 12, 50
Column3=[Images], -4, 0

