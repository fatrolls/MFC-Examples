// Page1.cpp -- Sample power control panel property page
// Copyright (C) 1998 by Walter Oney
// All rights reserved

// This sample illustrates a power-management property page for a
// non-standard device that registers a device interface.

#include "stdafx.h"
#include "powcpl.h"
#include "driver.h"
#include "GenericPower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Conversion table between drop-list indices and timeout
// values in seconds.

// TODO expand this list

DWORD timeout[] = {
	0,							// never
	10,							// 10 sec
	60,							// 1 min
	120,						// 2 min
	3600,						// 1 hour
	};

///////////////////////////////////////////////////////////////////////////////
// CPage1 property page

IMPLEMENT_DYNAMIC(CPage1, CShellPropPage)

CPage1::CPage1(CCmdTarget* parent) : CShellPropPage(parent, CPage1::IDD)
	{							// CPage1::CPage1
	//{{AFX_DATA_INIT(CPage1)
	m_wakeup = FALSE;
	m_idleplugged = -1;
	m_idleunplugged = -1;
	//}}AFX_DATA_INIT

	m_current = NULL;
	}							// CPage1::CPage1

CPage1::~CPage1()
	{							// CPage1::~CPage1
	}							// CPage1::~CPage1

BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPage1)
	ON_LBN_SELCHANGE(IDC_DEVICELIST, OnSelchangeDevicelist)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_WAKEUP, OnWakeup)
	ON_CBN_SELENDOK(IDC_IDLEPLUGGED, OnSelendokIdleplugged)
	ON_CBN_SELENDOK(IDC_IDLEUNPLUGGED, OnSelendokIdleunplugged)
	ON_BN_CLICKED(IDB_IDLENOW, OnIdlenow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////

int CPage1::ConvertTimeout(DWORD to)
	{							// CPage1::ConvertTimeout
	for (int i = 0; i < arraysize(timeout); ++i)
		if (timeout[i] == to)
			return i;
	return -1;
	}							// CPage1::ConvertTimeout

///////////////////////////////////////////////////////////////////////////////

BOOL CPage1::DevicesPresent()
	{							// CPage1::DevicesPresent
	HDEVINFO info = SetupDiGetClassDevs(CPage1::InterfaceGuid(), NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (info == INVALID_HANDLE_VALUE)
		return FALSE;
	SP_INTERFACE_DEVICE_DATA ifdata;
	ifdata.cbSize = sizeof(ifdata);
	BOOL yes = SetupDiEnumDeviceInterfaces(info, NULL, CPage1::InterfaceGuid(), 0, &ifdata);
	SetupDiDestroyDeviceInfoList(info);
	return yes;
	}							// CPage1::DevicesPresent

///////////////////////////////////////////////////////////////////////////////

void CPage1::DoDataExchange(CDataExchange* pDX)
	{							// CPage1::DoDataExchange

	// If we're setting the controls in the page, obtain current
	// values from the device driver.

	if (!pDX->m_bSaveAndValidate && m_current)
		{						// get current settings
		POWER_DEVICE_TIMEOUTS to;
		m_current->GetIdleTimeouts(&to);
		m_idleplugged = ConvertTimeout(to.PerformanceIdleTime);
		m_idleunplugged = ConvertTimeout(to.ConservationIdleTime);
		m_wakeup = m_current->IsWakeupEnabled();
		}						// get current settings

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage1)
	DDX_Control(pDX, IDC_ISIDLE, m_ctlIsidle);
	DDX_Control(pDX, IDC_IDLEUNPLUGGED, m_ctlIdleunplugged);
	DDX_Control(pDX, IDC_IDLEPLUGGED, m_ctlIdleplugged);
	DDX_Control(pDX, IDB_IDLENOW, m_ctlIdlenow);
	DDX_Control(pDX, IDB_WAKEUP, m_ctlWakeup);
	DDX_Control(pDX, IDC_DEVICELIST, m_ctlDevicelist);
	DDX_Check(pDX, IDB_WAKEUP, m_wakeup);
	DDX_CBIndex(pDX, IDC_IDLEPLUGGED, m_idleplugged);
	DDX_CBIndex(pDX, IDC_IDLEUNPLUGGED, m_idleunplugged);
	//}}AFX_DATA_MAP

	// If we're saving values, call the device driver interface
	// to save them. We won't actually set the values at the
	// device driver level until the user presses the Apply button, though.

	if (pDX->m_bSaveAndValidate && m_current)
		{						// save current settings
		POWER_DEVICE_TIMEOUTS to;
		to.PerformanceIdleTime = timeout[m_idleplugged];
		to.ConservationIdleTime = timeout[m_idleunplugged];
		m_current->SetIdleTimeouts(&to);

		m_current->SetWakeupEnable(m_wakeup);
		}						// save current settings
	}							// CPage1::DoDataExchange

///////////////////////////////////////////////////////////////////////////////

LPGUID CPage1::InterfaceGuid()
	{							// CPage1::InterfaceGuid
	return (LPGUID) &GUID_GENERIC_POWER;
	}							// CPage1::InterfaceGuid

///////////////////////////////////////////////////////////////////////////////

void CPage1::InitializeDeviceList(CListBox* list)
	{							// CPage1::InitializeDeviceList

	// Build a list of devices that support the generic power interface

	CDeviceList devices(*InterfaceGuid());
	devices.Initialize();
	for (int i = 0; i < devices.m_list.GetSize(); ++i)
		{						// for each device
		CDriver* driver = new CDriver(&devices.m_list[i]);
		if (driver->IsResponding())
			{					// add to dialog
			int index = list->AddString(driver->m_friendlyname);
			list->SetItemDataPtr(index, (PVOID) driver);
			}					// add to dialog
		else
			delete driver;		// never mind this device
		}						// for each device

	if (i)
		{						// at least one device
		list->SetCurSel(0);		// select 1st entry
		OnSelchangeDevicelist();// capture settings for 1st entry
		}						// at least one device
	}							// CPage1::InitializeDeviceList

///////////////////////////////////////////////////////////////////////////////

BOOL CPage1::OnApply() 
	{							// CPage1::OnApply
	for (int i = 0; i < m_ctlDevicelist.GetCount(); ++i)
		((CDriver*) m_ctlDevicelist.GetItemDataPtr(i))->SaveChanges();
	return CPropertyPage::OnApply();
	}							// CPage1::OnApply

///////////////////////////////////////////////////////////////////////////////

void CPage1::OnDestroy() 
	{							// CPage1::OnDestroy
	CPropertyPage::OnDestroy();

	for (int i = 0; i < m_ctlDevicelist.GetCount(); ++i)
		delete (CDriver*) m_ctlDevicelist.GetItemDataPtr(i);
	}							// CPage1::OnDestroy

///////////////////////////////////////////////////////////////////////////////

void CPage1::OnIdlenow() 
	{							// CPage1::OnIdlenow
	if (m_current)
		m_current->IdleNow();
	m_ctlIdlenow.EnableWindow(m_current->CanIdle() && !m_current->IsIdle());
	m_ctlIsidle.ShowWindow(m_current->IsIdle() ? SW_SHOW : SW_HIDE);
	}							// CPage1::OnIdlenow

///////////////////////////////////////////////////////////////////////////////

BOOL CPage1::OnInitDialog() 
	{							// CPage1::OnInitDialog
	CPropertyPage::OnInitDialog();
	
	InitializeDeviceList(&m_ctlDevicelist);
	
	return TRUE;
	}							// CPage1::OnInitDialog

///////////////////////////////////////////////////////////////////////////////

void CPage1::OnSelchangeDevicelist() 
	{							// CPage1::OnSelchangeDevicelist
	UpdateData(TRUE);

	int index = m_ctlDevicelist.GetCurSel();
	if (index == -1)
		return;
	m_current = (CDriver*) m_ctlDevicelist.GetItemDataPtr(index);
	m_ctlIdleplugged.EnableWindow(m_current->CanIdle());
	m_ctlIdleunplugged.EnableWindow(m_current->CanIdle());
	m_ctlIdlenow.EnableWindow(m_current->CanIdle() && !m_current->IsIdle());
	m_ctlWakeup.EnableWindow(m_current->CanWake());
	m_ctlIsidle.ShowWindow(m_current->IsIdle() ? SW_SHOW : SW_HIDE);
	UpdateData(FALSE);
	}							// CPage1::OnSelchangeDevicelist

///////////////////////////////////////////////////////////////////////////////

void CPage1::OnSelendokIdleplugged() 
	{							// CPage1::OnSelendokIdleplugged
	SetModified(TRUE);
	}							// CPage1::OnSelendokIdleplugged

///////////////////////////////////////////////////////////////////////////////

void CPage1::OnSelendokIdleunplugged() 
	{							// CPage1::OnSelendokIdleunplugged
	SetModified(TRUE);
	}							// CPage1::OnSelendokIdleunplugged

///////////////////////////////////////////////////////////////////////////////

void CPage1::OnWakeup() 
	{							// CPage1::OnWakeup
	SetModified(TRUE);
	}							// CPage1::OnWakeup
