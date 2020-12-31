; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInPlaceEdit
LastTemplate=CCmdTarget
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gridctrldemo.h"
LastPage=0

ClassCount=5
Class1=CGridCtrl
Class2=CGridCtrlDemoApp
Class3=CGridCtrlDemoDlg
Class4=CInPlaceEdit

ResourceCount=6
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MENU
Class5=CGridDropTarget
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU (English (Australia))
Resource5=IDD_GRIDCTRLDEMO_DIALOG
Resource6=IDD_GRIDCTRLDEMO_DIALOG (English (Australia))

[CLS:CGridCtrl]
Type=0
BaseClass=CWnd
HeaderFile=GridCtrl.h
ImplementationFile=GridCtrl.cpp
LastObject=CGridCtrl
Filter=W
VirtualFilter=WC

[CLS:CGridCtrlDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=GridCtrlDemo.h
ImplementationFile=GridCtrlDemo.cpp
LastObject=ID_APP_ABOUT

[CLS:CGridCtrlDemoDlg]
Type=0
BaseClass=CDialog
HeaderFile=GridCtrlDemoDlg.h
ImplementationFile=GridCtrlDemoDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_READ_ONLY

[CLS:CInPlaceEdit]
Type=0
BaseClass=CEdit
HeaderFile=InPlaceEdit.h
ImplementationFile=InPlaceEdit.cpp
Filter=W
VirtualFilter=WC
LastObject=CInPlaceEdit

[DLG:IDD_GRIDCTRLDEMO_DIALOG]
Type=1
Class=CGridCtrlDemoDlg
ControlCount=27
Control1=IDCANCEL,button,1342242816
Control2=IDC_GRID,MFCGridCtrl,1350631424
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_ROWS,edit,1350631552
Control6=IDC_SPIN_ROW,msctls_updown32,1342177334
Control7=IDC_EDIT_COLS,edit,1350631552
Control8=IDC_SPIN_COL,msctls_updown32,1342177334
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_FIXROWS,edit,1350631552
Control12=IDC_SPIN_FIXROW,msctls_updown32,1342177334
Control13=IDC_EDIT_FIXCOLS,edit,1350631552
Control14=IDC_SPIN_FIXCOL,msctls_updown32,1342177334
Control15=IDC_VERT_LINES,button,1342242819
Control16=IDC_HORZ_LINES,button,1342242819
Control17=IDC_LISTMODE,button,1342242819
Control18=IDC_EDITABLE,button,1342242819
Control19=IDC_STATIC,static,1342308352
Control20=IDC_PRINT_BUTTON,button,1342242816
Control21=IDC_ALLOW_SELECTION,button,1342242819
Control22=IDC_ROW_RESIZE,button,1342242819
Control23=IDC_COL_RESIZE,button,1342242819
Control24=IDC_STATIC,static,1342308352
Control25=IDC_FONT_BUTTON,button,1342242816
Control26=IDC_HEADERSORT,button,1342242819
Control27=IDC_SIZEBOX,scrollbar,1342177308

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CGridDropTarget]
Type=0
HeaderFile=GridDropTarget.h
ImplementationFile=GridDropTarget.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_GRIDCTRLDEMO_DIALOG (English (Australia))]
Type=1
Class=CGridCtrlDemoDlg
ControlCount=28
Control1=IDC_GRID,MFCGridCtrl,1350631424
Control2=IDC_EDIT_ROWS,edit,1350631552
Control3=IDC_SPIN_ROW,msctls_updown32,1342177334
Control4=IDC_EDIT_COLS,edit,1350631552
Control5=IDC_SPIN_COL,msctls_updown32,1342177334
Control6=IDC_EDIT_FIXROWS,edit,1350631552
Control7=IDC_SPIN_FIXROW,msctls_updown32,1342177334
Control8=IDC_EDIT_FIXCOLS,edit,1350631552
Control9=IDC_SPIN_FIXCOL,msctls_updown32,1342177334
Control10=IDC_VERT_LINES,button,1342242819
Control11=IDC_HORZ_LINES,button,1342242819
Control12=IDC_ROW_RESIZE,button,1342242819
Control13=IDC_COL_RESIZE,button,1342242819
Control14=IDC_EDITABLE,button,1342242819
Control15=IDC_ALLOW_SELECTION,button,1342242819
Control16=IDC_LISTMODE,button,1342242819
Control17=IDC_HEADERSORT,button,1342242819
Control18=IDC_READ_ONLY,button,1342242819
Control19=IDC_FONT_BUTTON,button,1342242816
Control20=IDC_PRINT_BUTTON,button,1342242816
Control21=IDCANCEL,button,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_SIZEBOX,scrollbar,1342177308

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MENU]
Type=1
Class=CGridCtrlDemoDlg
Command1=ID_FILE_PRINT
Command2=ID_APP_EXIT
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_SELECTALL
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_MENU (English (Australia))]
Type=1
Command1=ID_FILE_PRINT
Command2=ID_APP_EXIT
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_SELECTALL
Command7=ID_APP_ABOUT
CommandCount=7

