; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "msdidao.h"
LastPage=0

ClassCount=16
Class1=CCategoriesSet
Class2=CCategoriesTable
Class3=CCustomersSet
Class4=CCustomersTable
Class5=CMSDIDaoDoc
Class6=CMSDIDaoView
Class7=CMainFrame
Class8=CMSDIWinApp
Class9=CMSDIDaoApp
Class10=CAboutDlg
Class11=CMSDIFrame
Class12=CMSDIViewFrame
Class13=CDaoTableFrame
Class14=CDaoTableView

ResourceCount=5
Resource1=IDR_MDIDAOTYPE (English (U.S.))
Resource2=IDD_ABOUTBOX (English (U.S.))
Resource3=IDD_CATEG_PICTURE (English (U.S.))
Resource4=IDD_DATABASE_FORM (English (U.S.))
Class15=CCategoriesView
Class16=CDIBView
Resource5=IDR_MAINFRAME (English (U.S.))

[CLS:CCategoriesSet]
Type=0
HeaderFile=CategSet.h
ImplementationFile=CategSet.cpp

[CLS:CCategoriesTable]
Type=0
BaseClass=CDaoTableView
HeaderFile=CategTbl.h
ImplementationFile=CategTbl.cpp

[CLS:CCustomersSet]
Type=0
HeaderFile=CustSet.h
ImplementationFile=CustSet.cpp

[CLS:CCustomersTable]
Type=0
BaseClass=CDaoTableView
HeaderFile=CustTbl.h
ImplementationFile=CustTbl.cpp

[CLS:CMSDIDaoDoc]
Type=0
BaseClass=CDocument
HeaderFile=DaoDoc.h
ImplementationFile=DaoDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=ID_VIEW_DIB

[CLS:CMSDIDaoView]
Type=0
BaseClass=CFormView
HeaderFile=DaoView.h
ImplementationFile=DaoView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC

[CLS:CMSDIWinApp]
Type=0
BaseClass=CWinApp
HeaderFile=Msdiapp.h
ImplementationFile=Msdiapp.cpp

[CLS:CMSDIDaoApp]
Type=0
BaseClass=CMSDIWinApp
HeaderFile=MSDIDao.h
ImplementationFile=MSDIDao.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MSDIDao.cpp
ImplementationFile=MSDIDao.cpp
LastObject=CAboutDlg

[CLS:CMSDIFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=MsdiFrm.h
ImplementationFile=MsdiFrm.cpp

[CLS:CMSDIViewFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=MsdivFrm.h
ImplementationFile=MsdivFrm.cpp

[CLS:CDaoTableFrame]
Type=0
BaseClass=CMSDIViewFrame
HeaderFile=TblFrame.h
ImplementationFile=TblFrame.cpp

[CLS:CDaoTableView]
Type=0
BaseClass=CListView
HeaderFile=TblView.h
ImplementationFile=TblView.cpp

[DB:CCategoriesSet]
DB=1

[DB:CCustomersSet]
DB=1

[DLG:IDD_DATABASE_FORM]
Type=1
Class=CMSDIDaoView

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_RECORD_FIRST
Command8=ID_RECORD_PREV
Command9=ID_RECORD_NEXT
Command10=ID_RECORD_LAST
Command11=ID_FILE_PRINT
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_DIB
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MDIDAOTYPE (English (U.S.))]
Type=1
Class=CMSDIDaoDoc
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_TABLE_CATEG
Command16=ID_TABLE_CUSTOM
Command17=ID_TABLE_EMPL
Command18=ID_TABLE_DETAIL
Command19=ID_TABLE_ORDER
Command20=ID_TABLE_PRODUCT
Command21=ID_TABLE_SHIPP
Command22=ID_TABLE_SUPPL
Command23=ID_FORM_CATEG
Command24=ID_VIEW_DIB
Command25=ID_VIEW_TOOLBAR
Command26=ID_VIEW_STATUS_BAR
Command27=ID_WINDOW_NEW
Command28=ID_WINDOW_CASCADE
Command29=ID_WINDOW_TILE_HORZ
Command30=ID_WINDOW_ARRANGE
Command31=ID_APP_ABOUT
CommandCount=31

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_DATABASE_FORM (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DATABASE_NAME,edit,1484849280
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DATABASE_VERSION,edit,1484849280

[CLS:CCategoriesView]
Type=0
HeaderFile=CategVw.h
ImplementationFile=CategVw.cpp
BaseClass=CDaoRecordView
Filter=D
LastObject=ID_FORM_CATEG
VirtualFilter=VWC

[DLG:IDD_CATEG_PICTURE (English (U.S.))]
Type=1
Class=CCategoriesView
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CATEG_DESCRIPTION,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CATEG_ID,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CATEG_NAME,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CATEG_PICTURE,static,1342177294

[CLS:CDIBView]
Type=0
HeaderFile=DIBView.h
ImplementationFile=DIBView.cpp
BaseClass=CView
Filter=C
LastObject=CDIBView
VirtualFilter=VWC

