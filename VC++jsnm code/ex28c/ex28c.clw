; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex28c.h"
LastPage=0

ClassCount=7
Class1=CEx28cApp
Class2=CAboutDlg
Class3=CEx28cDoc
Class4=CEx28cSet
Class5=CEx28cView
Class6=CMainFrame
Class7=CSectionSet

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_EX28C_FORM

[CLS:CEx28cApp]
Type=0
BaseClass=CWinApp
HeaderFile=ex28c.h
ImplementationFile=ex28c.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ex28c.cpp
ImplementationFile=ex28c.cpp
LastObject=CAboutDlg

[CLS:CEx28cDoc]
Type=0
BaseClass=CDocument
HeaderFile=ex28cdoc.h
ImplementationFile=ex28cdoc.cpp

[CLS:CEx28cSet]
Type=0
HeaderFile=ex28cset.h
ImplementationFile=ex28cset.cpp

[CLS:CEx28cView]
Type=0
BaseClass=CRecordView
HeaderFile=ex28cview.h
ImplementationFile=ex28cview.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=Mainfrm.h
ImplementationFile=MAINFRM.CPP

[CLS:CSectionSet]
Type=0
HeaderFile=Sectionset.h
ImplementationFile=Sectionset.cpp

[DB:CEx28cSet]
DB=1

[DB:CSectionSet]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EX28C_FORM]
Type=1
Class=CEx28cView
ControlCount=9
Control1=IDC_ID,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NAME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ROOM,edit,1350631552
Control8=IDC_SECTIONS,listbox,1352728835
Control9=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_RECORD_FIRST
Command7=ID_RECORD_PREV
Command8=ID_RECORD_NEXT
Command9=ID_RECORD_LAST
Command10=ID_RECORD_CLEARFIELDS
Command11=ID_RECORD_ADD
Command12=ID_RECORD_UPDATE
Command13=ID_RECORD_DELETE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
CommandCount=10

