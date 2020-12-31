; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COutlookApp
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Outlook.h"
LastPage=0

ClassCount=8
Class1=COutlookApp
Class2=COutlookDoc
Class3=COutlookView
Class4=CMainFrame

ResourceCount=7
Resource1=IDR_MAINFRAME (English (U.S.))
Class5=CAboutDlg
Class6=COutlookTreeView
Resource2=IDD_SHBPROPERTIES_DIALOG
Class7=COutlookListView
Resource3=IDR_POPUP_MENU (English (U.S.))
Class8=COutlookFormView
Resource4=IDR_POPUP_MENU
Resource5=IDD_FORMVIEW (English (U.S.))
Resource6=IDR_MAINFRAME
Resource7=IDD_SHBPROPERTIES_DIALOG (English (U.S.))

[CLS:COutlookApp]
Type=0
HeaderFile=Outlook.h
ImplementationFile=Outlook.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=COutlookApp

[CLS:COutlookDoc]
Type=0
HeaderFile=OutlookDoc.h
ImplementationFile=OutlookDoc.cpp
Filter=N
LastObject=ID_VIEW_TOOLBAR
BaseClass=CDocument
VirtualFilter=DC

[CLS:COutlookView]
Type=0
HeaderFile=OutlookView.h
ImplementationFile=OutlookView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=COutlookView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_VIEW_OUTLOOKBAR



[CLS:CAboutDlg]
Type=0
HeaderFile=Outlook.cpp
ImplementationFile=Outlook.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_APP_EXIT
Command4=ID_REPLY
Command5=ID_REPLY_TO_ALL
Command6=ID_FORWARD_MESSAGE
Command7=ID_MOVE_TO_FOLDER
Command8=ID_DELETE
Command9=ID_FORWARD
Command10=ID_BACK
Command11=ID_UP_ONE_FOLDER
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_APP_ABOUT
CommandCount=14

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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_NEW_MESSAGE
Command2=ID_BACK
Command3=ID_FORWARD
Command4=ID_UP_ONE_FOLDER
Command5=ID_TOGGLE_TREE
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_MOVE_TO_FOLDER
Command9=ID_DELETE
Command10=ID_REPLY
Command11=ID_REPLY_TO_ALL
Command12=ID_FORWARD_MESSAGE
Command13=ID_ADDRESS_BOOK
Command14=ID_GROUP_BY_BOX
Command15=ID_AUTO_PREVIEW
Command16=ID_FIND_ITEMS
Command17=ID_OFFICE_ASSISTANT
CommandCount=17

[CLS:COutlookTreeView]
Type=0
HeaderFile=OutlookTreeView.h
ImplementationFile=OutlookTreeView.cpp
BaseClass=CTreeView
Filter=C
LastObject=COutlookTreeView
VirtualFilter=VWC

[CLS:COutlookListView]
Type=0
HeaderFile=OutlookListView.h
ImplementationFile=OutlookListView.cpp
BaseClass=CListView
Filter=C
LastObject=COutlookListView
VirtualFilter=VWC

[DLG:IDD_SHBPROPERTIES_DIALOG]
Type=1
Class=?
ControlCount=32
Control1=IDC_CLRBACK,button,1342242827
Control2=IDC_HDRCLRBACK,button,1342242827
Control3=IDC_TEXTFONT,button,1342242816
Control4=IDC_HDRFONT,button,1342242816
Control5=IDC_EDIT_HDRHEIGHT,edit,1350631552
Control6=IDC_CHECK_APPLYTOEXPANDED,button,1342242819
Control7=IDC_EDIT_GRPMARGIN,edit,1350631552
Control8=IDC_EDIT_LEFTMARGIN,edit,1350631552
Control9=IDC_EDIT_TOPMARGIN,edit,1350631552
Control10=IDC_EDIT_RIGHTMARGIN,edit,1350631552
Control11=IDC_EDIT_BOTTOMMARGIN,edit,1350631552
Control12=IDC_EDIT_SCROLLBTNWIDTH,edit,1350631552
Control13=IDC_EDIT_SCROLLBTNHEIGHT,edit,1350631552
Control14=IDOK,button,1342242817
Control15=IDCANCEL,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342177287
Control20=IDC_NAMETEXTFONT,static,1342312459
Control21=IDC_NAMEHDRFONT,static,1342312460
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352

[CLS:COutlookFormView]
Type=0
HeaderFile=OutlookFormView.h
ImplementationFile=OutlookFormView.cpp
BaseClass=CFormView
Filter=D
LastObject=COutlookFormView

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=ID_NEW_MESSAGE
Command2=ID_POST_IN_FOLDER
Command3=ID_APPOINTMENT
Command4=ID_MEETING_REQUEST
Command5=ID_CONTACT
Command6=ID_TASK
Command7=ID_TASK_REQUEST
Command8=ID_NOTE
Command9=ID_OFFICE_DOCUMENT
CommandCount=9

[DLG:IDD_FORMVIEW (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_LIST,SysListView32,1350631425

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_NEW_MESSAGE
Command2=ID_BACK
Command3=ID_FORWARD
Command4=ID_UP_ONE_FOLDER
Command5=ID_TOGGLE_TREE
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_MOVE_TO_FOLDER
Command9=ID_DELETE
Command10=ID_REPLY
Command11=ID_REPLY_TO_ALL
Command12=ID_FORWARD_MESSAGE
Command13=ID_ADDRESS_BOOK
Command14=ID_GROUP_BY_BOX
Command15=ID_AUTO_PREVIEW
Command16=ID_FIND_ITEMS
Command17=ID_OFFICE_ASSISTANT
CommandCount=17

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_APP_EXIT
Command4=ID_REPLY
Command5=ID_REPLY_TO_ALL
Command6=ID_FORWARD_MESSAGE
Command7=ID_MOVE_TO_FOLDER
Command8=ID_DELETE
Command9=ID_FORWARD
Command10=ID_BACK
Command11=ID_UP_ONE_FOLDER
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_APP_ABOUT
CommandCount=14

[MNU:IDR_POPUP_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_NEW_MESSAGE
Command2=ID_POST_IN_FOLDER
Command3=ID_APPOINTMENT
Command4=ID_MEETING_REQUEST
Command5=ID_CONTACT
Command6=ID_TASK
Command7=ID_TASK_REQUEST
Command8=ID_NOTE
Command9=ID_OFFICE_DOCUMENT
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
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

[DLG:IDD_SHBPROPERTIES_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=32
Control1=IDC_CLRBACK,button,1342242827
Control2=IDC_HDRCLRBACK,button,1342242827
Control3=IDC_TEXTFONT,button,1342242816
Control4=IDC_HDRFONT,button,1342242816
Control5=IDC_EDIT_HDRHEIGHT,edit,1350631552
Control6=IDC_CHECK_APPLYTOEXPANDED,button,1342242819
Control7=IDC_EDIT_GRPMARGIN,edit,1350631552
Control8=IDC_EDIT_LEFTMARGIN,edit,1350631552
Control9=IDC_EDIT_TOPMARGIN,edit,1350631552
Control10=IDC_EDIT_RIGHTMARGIN,edit,1350631552
Control11=IDC_EDIT_BOTTOMMARGIN,edit,1350631552
Control12=IDC_EDIT_SCROLLBTNWIDTH,edit,1350631552
Control13=IDC_EDIT_SCROLLBTNHEIGHT,edit,1350631552
Control14=IDOK,button,1342242817
Control15=IDCANCEL,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342177287
Control20=IDC_NAMETEXTFONT,static,1342312459
Control21=IDC_NAMEHDRFONT,static,1342312460
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352

