; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftNavDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PukamSoft.h"

ClassCount=11
Class1=CPukamSoftApp
Class2=CPukamSoftDlg
Class3=CAboutDlg

ResourceCount=16
Resource1=IDD_OUTWARDTRANSACTIONS_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_CUSTOMERINFO_DIALOG
Resource4=IDD_TOPBAND_DIALOG
Resource5=IDD_LEFTNAV_DIALOG
Resource6=IDD_CUSTOMERS_DIALOG
Resource7=IDD_BILLING_DIALOG
Resource8=IDD_TRANSACTIONS_OUTWARD_DIALOG
Class4=CCustomerInfoDlg
Class5=CBillingInfoDlg
Class6=CInwardTransactionsDlg
Class7=COutwardTransactionsDlg
Class8=CReportsDlg
Resource9=IDD_TRANSACTIONS_INWARD_DIALOG
Class9=CMainMenuDlg
Resource10=IDD_BILLINGINFO_DIALOG
Resource11=IDD_MESSAGEBOX_DIALOG
Resource12=IDD_PUKAMSOFT_DIALOG
Resource13=IDD_INWARDTRANSACTIONS_DIALOG
Resource14=IDD_MAINMENU_DIALOG
Class10=CTopBandDlg
Class11=CLeftNavDlg
Resource15=IDD_REPORTS_DIALOG
Resource16=IDD_EDIT_DIALOG

[CLS:CPukamSoftApp]
Type=0
HeaderFile=PukamSoft.h
ImplementationFile=PukamSoft.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CPukamSoftDlg]
Type=0
HeaderFile=PukamSoftDlg.h
ImplementationFile=PukamSoftDlg.cpp
Filter=D
LastObject=CPukamSoftDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=PukamSoftDlg.h
ImplementationFile=PukamSoftDlg.cpp
Filter=D

[DLG:IDD_PUKAMSOFT_DIALOG]
Type=1
Class=CPukamSoftDlg
ControlCount=0

[DLG:IDD_MESSAGEBOX_DIALOG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_CUSTOMERS_DIALOG]
Type=1
Class=CCustomerInfoDlg
ControlCount=0

[DLG:IDD_TRANSACTIONS_INWARD_DIALOG]
Type=1
Class=CInwardTransactionsDlg
ControlCount=0

[DLG:IDD_TRANSACTIONS_OUTWARD_DIALOG]
Type=1
Class=COutwardTransactionsDlg
ControlCount=0

[DLG:IDD_BILLING_DIALOG]
Type=1
Class=CBillingInfoDlg
ControlCount=0

[DLG:IDD_REPORTS_DIALOG]
Type=1
Class=CReportsDlg
ControlCount=0

[CLS:CCustomerInfoDlg]
Type=0
HeaderFile=CustomerInfoDlg.h
ImplementationFile=CustomerInfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCustomerInfoDlg

[CLS:CBillingInfoDlg]
Type=0
HeaderFile=BillingInfoDlg.h
ImplementationFile=BillingInfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CBillingInfoDlg

[CLS:CInwardTransactionsDlg]
Type=0
HeaderFile=InwardTransactionsDlg.h
ImplementationFile=InwardTransactionsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInwardTransactionsDlg

[CLS:COutwardTransactionsDlg]
Type=0
HeaderFile=OutwardTransactionsDlg.h
ImplementationFile=OutwardTransactionsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=COutwardTransactionsDlg

[CLS:CReportsDlg]
Type=0
HeaderFile=ReportsDlg.h
ImplementationFile=ReportsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CReportsDlg

[DLG:IDD_MAINMENU_DIALOG]
Type=1
Class=CMainMenuDlg
ControlCount=0

[CLS:CMainMenuDlg]
Type=0
HeaderFile=MainMenuDlg.h
ImplementationFile=MainMenuDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMainMenuDlg

[DLG:IDD_CUSTOMERINFO_DIALOG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_INWARDTRANSACTIONS_DIALOG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_OUTWARDTRANSACTIONS_DIALOG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_BILLINGINFO_DIALOG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_TOPBAND_DIALOG]
Type=1
Class=CTopBandDlg
ControlCount=0

[CLS:CTopBandDlg]
Type=0
HeaderFile=TopBandDlg.h
ImplementationFile=TopBandDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTopBandDlg

[DLG:IDD_LEFTNAV_DIALOG]
Type=1
Class=CLeftNavDlg
ControlCount=0

[CLS:CLeftNavDlg]
Type=0
HeaderFile=LeftNavDlg.h
ImplementationFile=LeftNavDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLeftNavDlg
VirtualFilter=dWC

[DLG:IDD_EDIT_DIALOG]
Type=1
Class=?
ControlCount=0

