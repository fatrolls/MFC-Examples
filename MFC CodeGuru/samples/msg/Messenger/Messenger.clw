; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "messenger.h"
LastPage=0

ClassCount=13
Class1=CMainFrame
Class2=CMessengerApp
Class3=CAboutDlg
Class4=CMessengerDoc
Class5=CMessengerEdit
Class6=CMessengerList
Class7=CMessengerTree
Class8=CPropDlg
Class9=CColorTreeCtrl
Class10=CCustomTreeCtrl
Class11=CMultiSelTreeCtrl
Class12=CToolTipsTreeCtrl
Class13=CTreeCtrlEx

ResourceCount=4
Resource1=IDR_LIST
Resource2=IDR_TRAY_MENU
Resource3=IDR_MAINFRAME
Resource4=IDD_ABOUTBOX

[CLS:CMainFrame]
Type=0
BaseClass=CStealthFrame
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC

[CLS:CMessengerApp]
Type=0
BaseClass=CWinApp
HeaderFile=Messenger.h
ImplementationFile=Messenger.cpp
LastObject=CMessengerApp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Messenger.cpp
ImplementationFile=Messenger.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CMessengerDoc]
Type=0
BaseClass=CDocument
HeaderFile=MessengerDoc.h
ImplementationFile=MessengerDoc.cpp
LastObject=CMessengerDoc

[CLS:CMessengerEdit]
Type=0
BaseClass=CEditView
HeaderFile=MessengerEdit.h
ImplementationFile=MessengerEdit.cpp

[CLS:CMessengerList]
Type=0
BaseClass=CView
HeaderFile=MessengerList.h
ImplementationFile=MessengerList.cpp

[CLS:CMessengerTree]
Type=0
BaseClass=CView
HeaderFile=MessengerTree.h
ImplementationFile=MessengerTree.cpp

[CLS:CPropDlg]
Type=0
BaseClass=CTPropertiesDlg
HeaderFile=PropDlg.h
ImplementationFile=PropDlg.cpp
LastObject=ID_TOOLS_PROPERTIESSHEET

[CLS:CColorTreeCtrl]
Type=0
BaseClass=CCustomTreeCtrl
HeaderFile=TreeCtrl\ColorTreeCtrl.h
ImplementationFile=TreeCtrl\ColorTreeCtrl.cpp

[CLS:CCustomTreeCtrl]
Type=0
BaseClass=CToolTipsTreeCtrl
HeaderFile=TreeCtrl\CustomTreeCtrl.h
ImplementationFile=TreeCtrl\CustomTreeCtrl.cpp
Filter=W
VirtualFilter=GWC
LastObject=CCustomTreeCtrl

[CLS:CMultiSelTreeCtrl]
Type=0
BaseClass=CTreeCtrlEx
HeaderFile=TreeCtrl\MultiSelTreeCtrl.h
ImplementationFile=TreeCtrl\MultiSelTreeCtrl.cpp

[CLS:CToolTipsTreeCtrl]
Type=0
BaseClass=CMultiSelTreeCtrl
HeaderFile=TreeCtrl\ToolTipsTreeCtrl.h
ImplementationFile=TreeCtrl\ToolTipsTreeCtrl.cpp

[CLS:CTreeCtrlEx]
Type=0
BaseClass=CTreeCtrl
HeaderFile=TreeCtrl\TreeCtrlEx.h
ImplementationFile=TreeCtrl\TreeCtrlEx.cpp
Filter=W
VirtualFilter=GWC
LastObject=CTreeCtrlEx

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VERSION_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPERTIES_DIALOG]
Type=1
Class=CPropDlg

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_COMBO_BUTTON
Command5=ID_SEND_BUTTON
Command6=ID_APP_ABOUT
CommandCount=6

[TB:IDR_LIST]
Type=1
Class=?
Command1=ID_LIST_DELETE
Command2=ID_LIST_REPLAY
Command3=ID_LIST_FORWARD
Command4=ID_WINDOW_SPLIT
Command5=ID_WINDOW_CASCADE
Command6=ID_WINDOW_TILE_HORZ
Command7=ID_WINDOW_TILE_VERT
CommandCount=7

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_WINDOW_SPLIT
Command9=ID_TOOLS_REFRESH_NETWORK_TREE
Command10=ID_TOOLS_PROPERTIESDIALOG
Command11=ID_TOOLS_PROPERTIESSHEET
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_TRAY_MENU]
Type=1
Class=?
Command1=ID_APP_ABOUT
Command2=ID_APP_EXIT
CommandCount=2

[MNU:IDR_LIST]
Type=1
Class=?
Command1=ID_LIST_DELETE
Command2=ID_LIST_REPLAY
Command3=ID_LIST_FORWARD
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_TOOLS_REFRESH_NETWORK_TREE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

