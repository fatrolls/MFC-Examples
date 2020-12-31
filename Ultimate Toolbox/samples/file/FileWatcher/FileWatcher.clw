; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileWatcherApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "filewatcher.h"
LastPage=0

ClassCount=3
Class1=CEnterNewDir
Class2=CFileWatcherApp
Class3=CFileWatcherDlg

ResourceCount=2
Resource1=IDD_ENTER_DIR
Resource2=IDD_FILEWATCHER_DIALOG

[CLS:CEnterNewDir]
Type=0
BaseClass=CDialog
HeaderFile=EnterNewDir.h
ImplementationFile=EnterNewDir.cpp
LastObject=CEnterNewDir

[CLS:CFileWatcherApp]
Type=0
BaseClass=CWinApp
HeaderFile=FileWatcher.h
ImplementationFile=FileWatcher.cpp
Filter=N
VirtualFilter=AC
LastObject=CFileWatcherApp

[CLS:CFileWatcherDlg]
Type=0
BaseClass=CDialog
HeaderFile=FileWatcherDlg.h
ImplementationFile=FileWatcherDlg.cpp

[DLG:IDD_ENTER_DIR]
Type=1
Class=CEnterNewDir
ControlCount=14
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DIR,edit,1350631552
Control3=IDC_WATCH_SUB_TREE,button,1342242819
Control4=IDC_STATIC,button,1342177287
Control5=IDC_CHANGE_FILE_NAME,button,1342242819
Control6=IDC_CHANGE_DIR_NAME,button,1342242819
Control7=IDC_CHANGE_ATTRIBUTES,button,1342242819
Control8=IDC_CHANGE_SIZE,button,1342242819
Control9=IDC_CHANGE_LAST_WRITE,button,1342242819
Control10=IDC_CHANGE_LAST_ACCESS,button,1342242819
Control11=IDC_CHANGE_CREATION,button,1342242819
Control12=IDC_CHANGE_SECURITY,button,1342242819
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816

[DLG:IDD_FILEWATCHER_DIALOG]
Type=1
Class=CFileWatcherDlg
ControlCount=7
Control1=IDC_ADD_DIR,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_REMOVE_DIR,button,1342242816
Control4=IDOK,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_WATCHED_DIRS,SysListView32,1350631429
Control7=IDC_NOTIFICATIONS,SysListView32,1350631425

