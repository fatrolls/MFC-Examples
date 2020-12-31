; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPizzaDlg
LastTemplate=CDaoRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Pizza.h"

ClassCount=7
Class1=CPizzaApp
Class2=CPizzaDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PIZZA_DIALOG (English (U.S.))
Resource4=IDD_ABOUTBOX (English (U.S.))
Class4=CDBListBox
Class5=CClientsRecordset
Class6=CDeliveryDlg
Class7=CItemsRecordset
Resource5=IDD_PIZZA_DIALOG

[CLS:CPizzaApp]
Type=0
HeaderFile=Pizza.h
ImplementationFile=Pizza.cpp
Filter=N

[CLS:CPizzaDlg]
Type=0
HeaderFile=PizzaDlg.h
ImplementationFile=PizzaDlg.cpp
Filter=D
LastObject=IDC_BUTTON5
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=PizzaDlg.h
ImplementationFile=PizzaDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PIZZA_DIALOG (English (U.S.))]
Type=1
Class=CPizzaDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:CDBListBox]
Type=0
HeaderFile=DBListBox.h
ImplementationFile=DBListBox.cpp
BaseClass=CListBox
Filter=W
LastObject=CDBListBox
VirtualFilter=bWC

[DB:CClientsRecordset]
DB=1
DBType=DAO
ColumnCount=6
Column1=[id], 4, 4
Column2=[SurName], 12, 15
Column3=[SecondName], 12, 15
Column4=[Address], 12, 25
Column5=[No], 12, 3
Column6=[Phone], 12, 13

[DLG:IDD_PIZZA_DIALOG]
Type=1
Class=CPizzaDlg
ControlCount=17
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_EDIT3,edit,1350631552
Control4=IDC_EDIT4,edit,1350631552
Control5=IDC_EDIT5,edit,1350631552
Control6=IDC_EDIT6,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_BUTTON1,button,1342242816
Control14=IDC_BUTTON2,button,1342242816
Control15=IDC_BUTTON3,button,1342242816
Control16=IDC_BUTTON4,button,1342242816
Control17=IDC_BUTTON5,button,1342242816

[DB:CClientsRecordset1]
DB=1
DBType=DAO
ColumnCount=6
Column1=[id], 4, 4
Column2=[SurName], 12, 15
Column3=[SecondName], 12, 15
Column4=[Address], 12, 25
Column5=[No], 12, 3
Column6=[Phone], 12, 13

[CLS:CClientsRecordset]
Type=0
HeaderFile=ClientsRecordset.h
ImplementationFile=ClientsRecordset.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[CLS:CDeliveryDlg]
Type=0
HeaderFile=DeliveryDlg.h
ImplementationFile=DeliveryDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDeliveryDlg
VirtualFilter=dWC

[CLS:CItemsRecordset]
Type=0
HeaderFile=ItemsRecordset.h
ImplementationFile=ItemsRecordset.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x
LastObject=CItemsRecordset

[DB:CItemsRecordset]
DB=1
DBType=DAO
ColumnCount=3
Column1=[id], 4, 4
Column2=[Name], 12, 20
Column3=[Prize], 4, 4

[DB:test]
DB=1
DBType=DAO
ColumnCount=9
Column1=[Clients].[id], 4, 4
Column2=[SurName], 12, 15
Column3=[SecondName], 12, 15
Column4=[Address], 12, 25
Column5=[AddrNo], 12, 3
Column6=[Phone], 12, 13
Column7=[Items].[id], 4, 4
Column8=[Name], 12, 20
Column9=[Prize], 4, 4

[DB:CDataBase]
DB=1
DBType=DAO
ColumnCount=9
Column1=[Clients].[id], 4, 4
Column2=[SurName], 12, 15
Column3=[SecondName], 12, 15
Column4=[Address], 12, 25
Column5=[AddrNo], 12, 3
Column6=[Phone], 12, 13
Column7=[Items].[id], 4, 4
Column8=[Name], 12, 20
Column9=[Prize], 4, 4

