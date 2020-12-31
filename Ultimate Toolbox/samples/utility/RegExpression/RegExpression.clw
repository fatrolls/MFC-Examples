; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFindDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RegExpression.h"
LastPage=0

ClassCount=8
Class1=CRegExpressionApp
Class2=CRegExpressionDoc
Class3=CRegExpressionView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDR_HISTORY_COMBO
Class7=CFindDialog
Resource4=IDR_REGEXPTYPE
Class8=CParseDialog
Resource5=IDD_DIALOG_FIND

[CLS:CRegExpressionApp]
Type=0
HeaderFile=RegExpression.h
ImplementationFile=RegExpression.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CRegExpressionDoc]
Type=0
HeaderFile=RegExpressionDoc.h
ImplementationFile=RegExpressionDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CRegExpressionDoc

[CLS:CRegExpressionView]
Type=0
HeaderFile=RegExpressionView.h
ImplementationFile=RegExpressionView.cpp
Filter=C
LastObject=CRegExpressionView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=RegExpression.cpp
ImplementationFile=RegExpression.cpp
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
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_REGEXPTYPE]
Type=1
Class=CRegExpressionView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_FIND_BUTTON
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DIALOG_FIND]
Type=1
Class=CFindDialog
ControlCount=7
Control1=IDOK,button,1342242816
Control2=ID_FIND_BUTTON,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_HISTORY,combobox,1344340034
Control5=IDC_STATIC,button,1342177287
Control6=IDC_LIST_RESULT,SysListView32,1350664333
Control7=IDC_CHECK_FOCUS,button,1342242819

[CLS:CFindDialog]
Type=0
HeaderFile=FindDialog.h
ImplementationFile=FindDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_RESULT

[CLS:CParseDialog]
Type=0
HeaderFile=ParseDialog.h
ImplementationFile=ParseDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATICINFO

[TB:IDR_HISTORY_COMBO]
Type=1
Class=?
Command1=ID_HISTORY_COMBO_NEW
Command2=ID_HISTORY_COMBO_DELETE
CommandCount=2

