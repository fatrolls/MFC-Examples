// Monitor.cpp -- IOS Monitor application
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#include "stdafx.h"
#pragma hdrstop

#include "Monitor.h"
#include "reqmon.h"
#include "ReqOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMonitorApp theApp;
CMainFrame* mainframe;
CTreePane*	treepane;
CDataPane*	datapane;

_IVT* ivt;						// address of IOS IVT
pIDA ida;						// address of IOS IDA

static char *lgn[] = {
	"DRP_IFS",
	"DRP_RESRVD1",
	"DRP_FSD",
	"DRP_FSD_EXT_1",
	"DRP_FSD_EXT_2",
	"DRP_VOLTRK",
	"DRP_CLASS_DRV",
	"DRP_TSD",
	"DRP_VSD_1",
	"DRP_VSD_2",
	"DRP_VSD_3",
	"DRP_SCSI_LAYER",
	"DRP_VSD_4",
	"DRP_VSD_5",
	"DRP_VSD_6",
	"DRP_VSD_7",
	"DRP_VSD_8",
	"DRP_VSD_9",
	"DRP_RESRVD18",
	"DRP_MISC_PD",
	"DRP_NT_MPD",
	"DRP_NT_PD",
	"DRP_ESDI_PD",
	"DRP_ESDIEMUL_PD",
	"DRP_RESRVD23",
	"DRP_ABIOS_PD",
	"DRP_ABIOS_PREMPT_PD",
	"DRP_NEC_FLOPPY",
	"DRP_RESRVD28",
	"DRP_SOC_SER_DRV",
	"DRP_SOC_DRV",
	"DRP_IOS_REG",
	};

///////////////////////////////////////////////////////////////////////////////
// Global helper functions

CString csprintf(LPCTSTR ctl, ...)
	{							// csprintf
	char buffer[256];
	va_list(ap);
	va_start(ap, ctl);
	_vsnprintf(buffer, sizeof(buffer), ctl, ap);
	va_end(ap);
	return buffer;
	}							// csprintf

CString FixString(char *s, int size)
	{							// FixString
	CString result;
	char *fs = result.GetBuffer(size);
	char *p;
	char ch;

	memcpy(fs, s, size);
	fs[size] = 0;
	for (p = fs; (ch = *p); ++p)
		if (ch < ' ' || ch >= 127)
			break;
	*p = 0;
	result.ReleaseBuffer();
	return result;
	}							// FixString

CString DevnodeName(PVOID devnode)
	{							// DevnodeName
	if (!devnode)
		return "";
	if (((PDWORD) devnode)[0] != 'YPLR')
		return "";
	return (char *) ((PDWORD) devnode)[1];
	}							// DevnodeName

CString DriveName(PIOSDCB dcb)
	{							// DriveName
	CString drvname;
	UINT devtype = dcb->DCB_cmn.DCB_device_type;

	if (dcb->DCB_cmn.DCB_device_flags & DCB_DEV_LOGICAL)
		drvname = csprintf("%c-Drive", dcb->DCB_cmn.DCB_drive_lttr_equiv + 'A');
	else if (devtype != DCB_type_floppy && devtype != DCB_type_disk && devtype != DCB_type_cdrom)
		drvname = "Non-disk Device";
	else
		{						// physical volume with partitions
		if (dcb->DCB_cmn.DCB_device_flags & DCB_DEV_INT13_DRIVE)
			drvname = csprintf("INT 13h drive %2.2X [", dcb->DCB_bdd.DCB_BDD_Int_13h_Number);
		else
			drvname = "Partitioned Volume [";
		char *comma = "";
		PIOSDCB logdcb = (PIOSDCB) dcb->DCB_cmn.DCB_next_logical_dcb;
		for (; logdcb; logdcb = (PIOSDCB) logdcb->DCB_cmn.DCB_next_logical_dcb)
			{					// for each partition
			drvname += csprintf("%s%c", comma, logdcb->DCB_cmn.DCB_drive_lttr_equiv + 'A');
			comma = ", ";
			}					// for each partition
		drvname += ']';
		}						// physical volume with partitions
	return drvname;
	}							// DriveName

///////////////////////////////////////////////////////////////////////////////

CMonitorApp::CMonitorApp()
	{							// CMonitorApp::CMonitorApp
	mainframe = NULL;
	m_reqmon = INVALID_HANDLE_VALUE;
	}							// CMonitorApp::CMonitorApp

CMonitorApp::~CMonitorApp()
	{							// CMonitorApp::~CMonitorApp
	if (m_reqmon != INVALID_HANDLE_VALUE)
		{						// deregister with our VxD
		DWORD pnull = 0;
		DeviceIoControl(m_reqmon, REQMON_SETMONITORADDRESS,
			&pnull, sizeof(pnull), NULL, 0, NULL, NULL);
		CloseHandle(m_reqmon);
		}						// deregister with our VxD
	}							// CMonitorApp::CMonitorApp

CMonitorApp::InitInstance()
	{							// CMonitorApp::InitInstance
	m_reqmon = CreateFile("\\\\.\\reqmon", 0, 0, NULL, 0,
		FILE_FLAG_DELETE_ON_CLOSE, NULL);

	if (m_reqmon == INVALID_HANDLE_VALUE)
		{						// VxD not loaded
		mainframe->MessageBox("REQMON.VXD not loaded");
		return FALSE;
		}						// VxD not loaded

	if (!DeviceIoControl(m_reqmon, REQMON_GETIVTADDR, NULL,
		0, &ivt, sizeof(ivt), NULL, NULL) || !ivt)
		{						// doesn't handle GETIVTADDR
		mainframe->MessageBox("The wrong version of REQMON.VXD is loaded");
		return FALSE;
		}						// doesn't handle GETIVTADDR

	ida = (pIDA) ivt->IVT_ios_mem_virtual;

	mainframe = new CMainFrame();
	m_pMainWnd = mainframe;
	mainframe->ShowWindow(m_nCmdShow);
	mainframe->UpdateWindow();

	treepane->UpdateAll();
	treepane->m_ctlTree.SetFocus();

	return TRUE;
	}							// CMonitorApp::InitInstance

///////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_MESSAGE(WM_DEVICECHANGE, OnDeviceChange)
	ON_COMMAND(ID_REQUESTS_MONITOR, OnRequestsMonitor)
	ON_COMMAND(ID_REQUESTS_OPTIONS, OnRequestsOptions)
	ON_UPDATE_COMMAND_UI(ID_REQUESTS_MONITOR, OnUpdateRequestsMonitor)
	ON_COMMAND(ID_REQUESTS_CLEARLOG, OnRequestsClearlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainFrame::CMainFrame() : m_log(theApp.m_reqmon)
	{							// CMainFrame::CMainFrame
	Create(AfxRegisterWndClass(0, theApp.LoadCursor(IDC_ARROW),
		(HBRUSH) GetStockObject(WHITE_BRUSH)),
		"I/O Supervisor Monitor");
	m_menu.LoadMenu(MAINMENU);
	SetMenu(&m_menu);
	m_changepending = FALSE;
	m_monitoring = FALSE;
	m_log.Create(CRequestLog::IDD, this);
	}							// CMainFrame::CMainFrame

CMainFrame::~CMainFrame()
	{							// CMainFrame::~CMainFrame	
	}							// CMainFrame::~CMainFrame

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
	{							// CMainFrame::OnCreateClient

	CRect rc;
	GetClientRect(rc);
	m_splitter.CreateStatic(this, 1, 2);

	CSize size(rc.right/3, rc.bottom);
	if (m_splitter.CreateView(0, 0, RUNTIME_CLASS(CTreePane), size, pContext))
		treepane = (CTreePane*) m_splitter.GetPane(0, 0);
	else
		return FALSE;

	size.cx = rc.right - size.cx;
	if (m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDataPane), size, pContext))
		datapane = (CDataPane*) m_splitter.GetPane(0, 1);
	else
		return FALSE;

	return TRUE;
	}							// CMainFrame::OnCreateClient

void CMainFrame::OnFileExit() 
	{							// CMainFrame::OnFileExit
	SendMessage(WM_CLOSE, 0, 0);
	}							// CMainFrame::OnFileExit

void CMainFrame::OnRequestsMonitor() 
	{							// CMainFrame::OnRequestsMonitor
	m_monitoring = !m_monitoring;
	m_log.SendMessage(WM_COMMAND, m_monitoring ? IDB_RESUME : IDB_PAUSE);
	m_log.ShowWindow(m_monitoring ? SW_SHOW : SW_HIDE);
	}							// CMainFrame::OnRequestsMonitor

void CMainFrame::OnUpdateRequestsMonitor(CCmdUI* pCmdUI) 
	{							// CMainFrame::OnUpdateRequestsMonitor
	pCmdUI->SetCheck(m_monitoring);
	}							// CMainFrame::OnUpdateRequestsMonitor

void CMainFrame::OnRequestsOptions() 
	{							// CMainFrame::OnRequestsOptions
	CReqOptions dlg(this);
	for (PIOSDCB dcb = (PIOSDCB) ida->IDA_first_dcb; dcb; dcb = (PIOSDCB) dcb->DCB_cmn.DCB_next_dcb)
		dlg.m_devlist.Add(dcb);
	dlg.m_log = &m_log;
	dlg.m_numlog = m_log.m_nlog;
	if (dlg.DoModal() != IDOK)
		return;
	
	m_log.m_nlog = dlg.m_numlog;
	EnterCriticalSection(&m_log.m_cs);
	m_log.m_all = FALSE;
	m_log.m_devlist.RemoveAll();
	for (int i = 0; i < dlg.m_devlist.GetSize(); ++i)
		m_log.m_devlist.Add(dlg.m_devlist[i]);
	LeaveCriticalSection(&m_log.m_cs);
	}							// CMainFrame::OnRequestsOptions

void CMainFrame::OnRequestsClearlog() 
	{							// CMainFrame::OnRequestsClearlog
	m_log.m_ctlList.DeleteAllItems();
	}							// CMainFrame::OnRequestsClearlog

LRESULT CMainFrame::OnDeviceChange(WPARAM wParam, LPARAM lParam)
	{							// CMainFrame::OnDeviceChange
	switch (wParam)
		{						// handle device change notification
	case DBT_DEVICEREMOVEPENDING:
		m_changepending = TRUE;	// block selection changes for the moment
		datapane->ClearContents();
		break;
	case DBT_DEVICEARRIVAL:
	case DBT_DEVICEREMOVECOMPLETE:
		m_changepending = FALSE;
		treepane->UpdateAll();
		treepane->OnSelChanged(NULL, NULL);
		break;
		}						// handle device change notification
	return 0;
	}							// CMainFrame::OnDeviceChange

///////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CTreePane, CWnd)

BEGIN_MESSAGE_MAP(CTreePane, CWnd)
	//{{AFX_MSG_MAP(CTreePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, ID_TREE_CONTROL, OnSelChanged)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTreePane::CTreePane()
	{							// CTreePane::CTreePane
	}							// CTreePane::CTreePane

CTreePane::~CTreePane()
	{							// CTreePane::~CTreePane
	}							// CTreePane::~CTreePane

void CTreePane::PostNcDestroy()
	{							// CTreePane::PostNcDestroy
	delete this;
	}							// CTreePane::PostNcDestroy

void CTreePane::OnDestroy() 
	{							// CTreePane::OnDestroy
	DiscardChildren(m_root);
	delete (CIda*) m_ctlTree.GetItemData(m_root);
	CWnd::OnDestroy();
	}							// CTreePane::

int CTreePane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{							// CTreePane::OnCreate
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rc;
	GetClientRect(rc);
	m_ctlTree.Create(WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_LINESATROOT |TVS_HASBUTTONS,
		rc, this, ID_TREE_CONTROL);

	m_root = m_ctlTree.InsertItem("I/O Supervisor Information", 0, 0);
	m_ctlTree.SetItemData(m_root, (DWORD) new CIda(ida));

	m_volumes = m_ctlTree.InsertItem("Volumes", m_root, 0);
	m_drives = m_ctlTree.InsertItem("Physical Drives", m_root, 0);
	m_drivers = m_ctlTree.InsertItem("Device Drivers", m_root, 0);

	return 0;
	}							// CTreePane::OnCreate

void CTreePane::OnSize(UINT nType, int cx, int cy) 
	{							// CTreePane::OnSize
	CWnd::OnSize(nType, cx, cy);
	m_ctlTree.MoveWindow(0, 0, cx, cy);
	}							// CTreePane::OnSize

void CTreePane::UpdateAll()
	{							// CTreePane::UpdateAll
	UpdateDriverInfo();
	UpdateDriveInfo();
	UpdateVolumeInfo();
	}							// CTreePane::UpdateAll

void CTreePane::AddDriver(_DVT* dvt)
	{							// CTreePane::AddDriver
	CString dvrname = FixString(dvt->DVT_ascii_name, sizeof(dvt->DVT_ascii_name));
	if (dvrname.GetLength() == 0 || dvrname[0] == ' ')
		dvrname = csprintf("<unnamed driver %8.8x>", dvt);
	CDriver* driver = new CDriver(dvt);
	driver->Add(dvrname, m_drivers);

	for (PDDB ddb = (PDDB) dvt->DVT_ddb; ddb; ddb = (PDDB) ddb->DDB_Next_DDB)
		{						// for each device data block
		CDdb* ddbnode = new CDdb(ddb);
		ddbnode->Add(DevnodeName(ddb->DDB_devnode_ptr), driver->m_treeitem);
		for (PIOSDCB dcb = (PIOSDCB) ddb->DDB_dcb_ptr; dcb; dcb = (PIOSDCB) dcb->DCB_next_ddb_dcb)
			AddDrive(dcb, ddbnode->m_treeitem);
		}						// for each device data block
	}							// CTreePane::AddDriver

void CTreePane::UpdateDriverInfo()
	{							// CTreePane::UpdateDriverInfo
	_DVT* dvt = (_DVT*) ivt->IVT_first_dvt;
	DiscardChildren(m_drivers);
	for ( ; dvt; dvt = (_DVT*) dvt->DVT_next_dvt)
		AddDriver(dvt);
	}							// CTreePane::UpdateDriverInfo

void CTreePane::AddDrive(PIOSDCB dcb, HTREEITEM parent)
	{							// CTreePane::AddDrive
	CDrive* drive = new CDrive(dcb);
	CString drvname = DriveName(dcb);

	drive->Add(drvname, parent);

	HTREEITEM hcd = m_ctlTree.InsertItem("Calldown Stack", drive->m_treeitem, 0);

	DCB_cd_entry* cdp = (DCB_cd_entry*) dcb->DCB_cmn.DCB_ptr_cd;
	for (; cdp; cdp = (DCB_cd_entry*) cdp->DCB_cd_next)
		{						// add calldown entries
		CString name = csprintf("%s CallDown", lgn[cdp->DCB_cd_lgn]);
		CCalldown* calldown = new CCalldown(cdp);
		calldown->Add(name, hcd);
		}						// add calldown entries

	if (!(dcb->DCB_cmn.DCB_device_flags & DCB_DEV_LOGICAL))
		{						// add logical drives
		PIOSDCB logdcb = (PIOSDCB) dcb->DCB_cmn.DCB_next_logical_dcb;
		for (; logdcb; logdcb = (PIOSDCB) logdcb->DCB_cmn.DCB_next_logical_dcb)
			AddDrive(logdcb, drive->m_treeitem);
		}						// add logical drives
	}							// CTreePane::AddDrive

void CTreePane::UpdateDriveInfo()
	{							// CTreePane::UpdateDriveInfo
	DiscardChildren(m_drives);
	PIOSDCB dcb = (PIOSDCB) ida->IDA_first_dcb;
	for (; dcb; dcb = (PIOSDCB) dcb->DCB_cmn.DCB_next_dcb)
		if (dcb->DCB_cmn.DCB_device_flags & DCB_DEV_PHYSICAL)
			AddDrive(dcb, m_drives);
	}							// CTreePane::UpdateDriveInfo

void CTreePane::AddVolume(PVRP vrp, HTREEITEM parent)
	{							// CTreePane::AddVolume
	CVolume* volume = new CVolume(vrp);
	PIOSDCB dcb = (PIOSDCB) vrp->VRP_logical_handle;
	CString volname;

	if (dcb && (dcb->DCB_cmn.DCB_device_flags & DCB_DEV_LOGICAL))
		volname = csprintf("%c:", dcb->DCB_cmn.DCB_drive_lttr_equiv + 'A');
	else
		volname = csprintf("%8.8X", vrp);
	
	volume->Add(volname, parent);
	}							// CTreePane::AddVolume

void CTreePane::UpdateVolumeInfo()
	{							// CTreePane::UpdateVolumeInfo
	DiscardChildren(m_volumes);
	PVRP vrp = (PVRP) ida->IDA_first_vrp;
	for (; vrp; vrp = (PVRP) vrp->VRP_next_vrp)
		AddVolume(vrp, m_volumes);
	}							// CTreePane::UpdateVolumeInfo

void CTreePane::OnSelChanged(NMHDR* nfy, LRESULT* result)
	{							// CTreePane::OnSelChanged
	if (mainframe->m_changepending)
		return;					// ignore selection change during update
	
	HTREEITEM hitem = m_ctlTree.GetSelectedItem();
	CIosObject* op = (CIosObject*) m_ctlTree.GetItemData(hitem);
	datapane->ClearContents();
	if (op)
		op->Show();
	}							// CTreePane::OnSelChanged

void CTreePane::DiscardChildren(HTREEITEM item)
	{							// CTreePane::DiscardChildren
	HTREEITEM child;
	while(child = m_ctlTree.GetChildItem(item))
		{						// for each child
		DiscardChildren(child);
		CIosObject* op = (CIosObject*) m_ctlTree.GetItemData(child);
		if (op)
			delete op;
		m_ctlTree.DeleteItem(child);
		}						// for each child
	}							// CTreePane::DiscardChildren

///////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CDataPane, CWnd)

BEGIN_MESSAGE_MAP(CDataPane, CWnd)
	//{{AFX_MSG_MAP(CDataPane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDataPane::CDataPane()
	{							// CDataPane::CDataPane
	}							// CDataPane::CDataPane

CDataPane::~CDataPane()
	{							// CDataPane::~CDataPane
	}							// CDataPane::~CDataPane

void CDataPane::PostNcDestroy()
	{							// CDataPane::PostNcDestroy
	delete this;
	}							// CDataPane::PostNcDestroy

int CDataPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{							// CDataPane::OnCreate
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rc;
	GetClientRect(rc);
	m_ctlList.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL,
		rc, this, ID_LIST_CONTROL);

	TEXTMETRIC tm;
	CClientDC dc(this);
	dc.GetTextMetrics(&tm);

	int colwidth = 24 * tm.tmAveCharWidth;
	m_ctlList.InsertColumn(0, "Parameter", LVCFMT_LEFT, colwidth, 0);
	m_ctlList.InsertColumn(1, "Value", LVCFMT_LEFT, 10000, 1);

	return 0;
	}							// CDataPane::OnCreate

void CDataPane::OnSize(UINT nType, int cx, int cy) 
	{							// CDataPane::OnSize
	CWnd::OnSize(nType, cx, cy);
	m_ctlList.MoveWindow(0, 0, cx, cy);
//	m_ctlList.SetColumnWidth(1, cx - m_ctlList.GetColumnWidth(0)); // avoid having a ghost 3d column
	}							// CDataPane::OnSize

void CDataPane::ClearContents()
	{							// CDataPane::ClearContents
	m_ctlList.DeleteAllItems();
	}							// CDataPane::ClearContents

void CDataPane::AddParameter(const char *name, const CString value)
	{							// CDataPane::AddParameter
	int item = m_ctlList.InsertItem(m_ctlList.GetItemCount(), name);
	m_ctlList.SetItemText(item, 1, value);
	}							// CDataPane::AddParameter

void CDataPane::ShowFlags(DWORD flags, const BITNAME* bnp)
	{							// CDataPane::ShowFlags
	for (; bnp->bit; ++bnp)
		if (flags & bnp->bit)
			{					// bit is set
			int item = m_ctlList.InsertItem(m_ctlList.GetItemCount(), "");
			m_ctlList.SetItemText(item, 1, csprintf("%8.8X  %s", bnp->bit, bnp->name));
			}					// bit is set
	}							// CDataPane::ShowFlags

///////////////////////////////////////////////////////////////////////////////

void CIosObject::Add(const CString name, HTREEITEM parent)
	{							// CIosObject::Add
	m_treeitem = treepane->m_ctlTree.InsertItem(name, parent);
	treepane->m_ctlTree.SetItemData(m_treeitem, (DWORD) this);
	}							// CIosObject::Add

void CIosObject::AddParameter(const char* name, const CString value) const
	{							// CIosObject::AddParameter
	datapane->AddParameter(name, value);
	}							// CIosObject::AddParameter

void CIosObject::ShowFlags(DWORD flags, const BITNAME* bnp) const
	{							// CIosObject::ShowFlags
	datapane->ShowFlags(flags, bnp);
	}							// CIosObject::ShowFlags

void CDriver::Show()
	{							// CDriver::Show
	#undef pf
	#define pf(f) AddParameter(#f, csprintf("%8.8X", m_dvt->DVT_##f));

	AddParameter("DVT Address", csprintf("%8.8X", m_dvt));
	pf(next_dvt)
	pf(device_cnt)
	pf(aer)
	pf(ddb)

	// feature flags

	#undef PFX
	#define PFX() DVT_FC
	BNTStart(features)
	bn(SCAN_DOWN)
	bn(IO_FOR_INQ_AEP)
	bn(HALF_SEC)
	bn(1_SEC)
	bn(2_SECS)
	bn(4_SECS)
	bn(DYNALOAD)
	bn(NEED_PRELOAD)
	bn(NEED_PRE_POST_LOAD)
	BNTEnd()

	pf(feature_code)
	ShowFlags(m_dvt->DVT_feature_code, features);

	// bus type

	static char *bustypes[] = {"ESDI", "SCSI", "FLOPPY", "SMART", "ABIOS"};
	AddParameter("bus_type", csprintf("%d (%s)", m_dvt->DVT_bus_type, bustypes[m_dvt->DVT_bus_type]));

	pf(reference_data)
	pf(first_drive)
	AddParameter("current_lgn", csprintf("%d (%s)", m_dvt->DVT_current_lgn, lgn[m_dvt->DVT_current_lgn]));
	pf(LoadHandle)
	pf(scsi_max_target)
	pf(scsi_max_lun)
	pf(entry_point)
	pf(init_count)

	}							// CDriver::Show

void CDrive::Show()
	{							// CDrive::Show
	#undef pfc
	#undef pf
	#define pfc(f) AddParameter(#f, csprintf("%8.8X", m_dcb->DCB_cmn.DCB_##f));
	#define pf(f)  AddParameter(#f, csprintf("%8.8X", m_dcb->DCB_##f));

	AddParameter("DCB Address", csprintf("%8.8X", m_dcb));

	pfc(physical_dcb)
	pfc(expansion_length)

	pfc(ptr_cd)
	pfc(next_dcb)
	pfc(next_logical_dcb)
	pfc(drive_lttr_equiv)
	pfc(unit_number)
	
	pfc(TSD_Flags)
		{
		#undef PFX
		#define PFX() DCB_TSD
		BNTStart(tsdflags)
		bn(INVALID_PARTITION)
		bn(BAD_MBR)
		bn(USER_LETTERS_CHECKED)
		bn(FIRST_USER_CHECK)
		bn(BID_SET_GEOM)
		bn(USER_SET)
		bn(NO_USER_INT13)
		bn(PROTMODE_INT_13)
		bn(MBPB_PBR)
		bn(RBPB_INIT)
		bn(MBPB_INIT)
		bn(APPARENT_PBR)
		bn(APPARENT_ROM)
		bn(ACTUAL_SET)
		bn(ACTUAL_PRE_SET)
		bn(APPARENT_PRE_SET)
		BNTEnd()

		ShowFlags(m_dcb->DCB_cmn.DCB_TSD_Flags, tsdflags);
		}

	pfc(vrp_ptr)

	pfc(dmd_flags)
		{
		#undef PFX
		#define PFX() DCB_dmd
		BNTStart(dmdflags)
		bn(srb_cdb)
		bn(logical)
		bn(physical)
		bn(small_memory)
		bn(not_512)
		bn(word_align)
		bn(dword_align)
		bn(phys_sgd)
		bn(phys_sgd_ptr)
		bn(do_a_b_toggling)
		bn(query_remov)
		bn(request_sns)
		bn(lock_unlock_media)
		bn(load_eject_media)
		bn(clear_media_chg)
		bn(serialize)
		bn(prot_mode)
		bn(no_xclusive)
		bn(pageability)
		BNTEnd()

		ShowFlags(m_dcb->DCB_cmn.DCB_dmd_flags, dmdflags);
		}

	#pragma warning(disable:4245)

	pfc(device_flags)
		{
		#undef PFX
		#define PFX() DCB_DEV
		BNTStart(devflags)
		bn(SPINDOWN_SUPPORTED)
		bn(SPUN_DOWN)
		bn(IO_ACTIVE)
		bn(INT13_CONFIGURED)
		bn(NO_ASPICAM)
		bn(REMOVAL_PENDING)
		bn(RMM_INT13)
		bn(TSD_PROCESSED)
		bn(SINGLE_FLOPPY)
		bn(REAL_MODE)
		bn(QUE_DESCEND)
		bn(MEDIA_CHANGED)
		bn(INVALID_GEOM)
		bn(INHIBIT_SW_TIMED_SUPPORT)
		bn(ASYNC_MED_CHG_SUPPORT)
		bn(SYNC_MED_CHG_SUPPORT)
		bn(PHYSICAL)
		bn(LOGICAL)
		bn(RMM)
		bn(UNCERTAIN_MEDIA)
		bn(ROM_CFG_REQ)
		bn(MUST_CONFIGURE)
		bn(SSTOR_VOL)
		bn(PAGING_DEVICE)
		{DCB_CHAR_DEVICE, "DCB_CHAR_DEVICE"},
		bn(I13_IN_PROGRESS)
		{BDF_Cache, "DCB_DEV_CACHE"},
		bn(SERIAL_CMD)
		bn(REMOTE)
		bn(REMOVABLE)
		bn(WRITEABLE)
		bn(INT13_DRIVE)
		BNTEnd()

		ShowFlags(m_dcb->DCB_cmn.DCB_device_flags, devflags);
		}

	#pragma warning(default:4245)

	pfc(device_flags2)
		{
		#undef PFX
		#define PFX() DCB_DEV2
		BNTStart(dev2flags)
		bn(THREAD_LOCK)
		bn(ATAPI_DEVICE)
		bn(DMF_DISK)
		bn(I13_COPY_PROT)
		BNTEnd()

		ShowFlags(m_dcb->DCB_cmn.DCB_device_flags2, dev2flags);
		}

	pfc(Partition_Start)
	pfc(track_table_ptr)
	pfc(bds_ptr)
	pfc(apparent_blk_shift)
	pfc(partition_type)
	pfc(sig)
	
	{
	static char *typenames[] = {"disk", "tape", "printer", "processor", "worm",
		"cdrom", "scanner", "optical_memory", "changer", "comm", "floppy", "optical_nec"};
	AddParameter("device_type", csprintf("%d (DCB_type_%s)", m_dcb->DCB_cmn.DCB_device_type, typenames[m_dcb->DCB_cmn.DCB_device_type]));
	}

	pfc(Exclusive_VM)
	pfc(disk_bpb_flags)
		{
		#undef PFX
		#define PFX() DCBF_DISK_BPB
		BNTStart(bpbflags)
		bn(USEFAKE)
		BNTEnd()
		ShowFlags(m_dcb->DCB_cmn.DCB_disk_bpb_flags, bpbflags);
		}

	pfc(cAssoc)
	pfc(Sstor_Host)
	pfc(user_drvlet)

	if (m_dcb->DCB_cmn.DCB_device_flags & DCB_DEV_PHYSICAL)
		{						// physical dcb
		AddParameter("", "");
		pf(max_xfer_len)
		pf(actual_sector_cnt[0])
		pf(actual_sector_cnt[1])
		pf(actual_blk_size)
		pf(actual_head_cnt)
		pf(actual_cyl_cnt)
		pf(actual_spt)
		pf(next_ddb_dcb)
		AddParameter("dev_node", csprintf("%8.8X (%s)", m_dcb->DCB_dev_node, DevnodeName(m_dcb->DCB_dev_node)));
	
		{
		static char *bustype[] = {"ESDI", "SCSI", "NEC", "SMART", "ABIOS"};
		AddParameter("bus_type", csprintf("%d (DCB_BUS_%s)", m_dcb->DCB_bus_type, bustype[m_dcb->DCB_bus_type]));
		}

		pf(bus_number)
		pf(queue_freeze)
		pf(max_sg_elements)
		pf(io_pend_count)
		pf(lock_count)
		pf(SCSI_VSD_FLAGS)
		pf(scsi_target_id)
		pf(scsi_lun)
		pf(scsi_hba)
		pf(max_sense_data_len)
		pf(srb_ext_size)
	
		{
		#define x m_dcb->DCB_inquiry_flags
		printf("%-22s%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X\n", "inquiry_flags", x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7]);
		#undef x
		AddParameter("vendor_id", FixString((char *) m_dcb->DCB_vendor_id, 8));
		AddParameter("product_id", FixString((char *) m_dcb->DCB_product_id, 16));
		AddParameter("rev_level", FixString((char *) m_dcb->DCB_rev_level, 4));
		AddParameter("port_name", FixString((char *) m_dcb->DCB_port_name, 8));
		}

		pf(current_unit)
		pf(blocked_iop)
		pf(vol_unlock_timer)
		pf(access_timer)
	
		pf(Vol_Flags)
			{
			#undef PFX
			#define PFX() DCB_VF
			BNTStart(volflags)
			bn(INHIBIT_LOCKING)
			bn(INHIBIT_IO)
			bn(INHIBIT_GEOM_RECOMPUTE)
			bn(UNLOCK_SCHED)
			bn(NEED_PHYS_RECOMP)
			bn(PROT_NEC_DRIVE)
			BNTEnd()

			ShowFlags(m_dcb->DCB_Vol_Flags, volflags);
			}

		pf(q_algo)
		pf(unit_on_ctl)
		pf(Port_Specific)
		pf(spindown_timer)

		if (m_dcb->DCB_cmn.DCB_device_flags & DCB_DEV_INT13_CONFIGURED)
			{					// int 13 drive
			#undef pf
			#undef pfd
			#define pf(f)  AddParameter(#f, csprintf("%8.8X", m_dcb->DCB_bdd.DCB_##f));
			#define pfd(f)  AddParameter(#f, csprintf("%8.8X", m_dcb->DCB_bdd.DCB_BDD_##f));
			AddParameter("", "");
			pfd(Next)
			pfd(BD_Major_Version)
			pfd(BD_Minor_Version)
			pfd(Device_SubType)
			pfd(Int_13h_Number)
			pfd(flags)
			pfd(Name_Ptr)
			pf(apparent_sector_cnt[0])
			pf(apparent_sector_cnt[1])
			pf(apparent_blk_size)
			pf(apparent_head_cnt)
			pf(apparent_cyl_cnt)
			pf(apparent_spt)
			pfd(Sync_Cmd_Proc)
			pfd(Command_Proc)
			pfd(Hw_Int_Proc)
			#undef pfd
			#define pfd(f)  AddParameter(#f, csprintf("%8.8X", m_dcb->DCB_bdd.DCB_BDP_##f));
			pfd(Cmd_Queue_Ascending)
			pfd(Current_Flags)
			pfd(Int13_Param_Ptr)
			pfd(Current_Command)
			pfd(Current_Position[0])
			pfd(Current_Position[1])
			pf(fastdisk_bdd)
			}					// int 13 drive
		}						// physical dcb
	}							// CDrive::Show

void CDdb::Show()
	{							// CDdb::Show
	#undef pf
	#define pf(f) AddParameter(#f, csprintf("%8.8X", m_ddb->DDB_##f));

	AddParameter("DDB Address", csprintf("%8.8X", m_ddb));

	pf(phys_addr)
	pf(Next_DDB)
	pf(Next_DDB_init)
	pf(dcb_ptr)
	pf(number_buses)

	pf(ios_flags)
		{
		#undef PFX
		#define PFX() DDB_IOS_FL
		BNTStart(iosflags)
		bn(PENDING_REMOVAL)
		bn(PAGE_ALLOCED)
		bn(PLEASE_DESTROY)
		BNTEnd()
		
		ShowFlags(m_ddb->DDB_ios_flags, iosflags);
		}

	pf(sig)
	pf(dvt)
	
	AddParameter("devnode_ptr", csprintf("%8.8X (%s)", m_ddb->DDB_devnode_ptr, DevnodeName(m_ddb->DDB_devnode_ptr))); 
	}							// CDdb::Show

void CIda::Show()
	{							// CIda::Show
	#undef pf
	#define pf(f)  AddParameter(#f, csprintf("%8.8X", m_ida->IDA_##f));

	AddParameter("IDA Address", csprintf("%8.8X", m_ida));
	
	pf(first_ice)
	pf(current_ice)
	pf(ios_mem_phys)
	pf(current_ice_len)
	pf(ios_timer)
	pf(ios_counter)
	pf(start_eci)
	pf(start_cct)
	
	AddParameter("esdi_p_in_use", ida->IDA_esdi_p_in_use ? "Yes" : "No");
	AddParameter("esdi_s_in_use", ida->IDA_esdi_s_in_use ? "Yes" : "No");
	AddParameter("Num_Floppies", csprintf("%d", ida->IDA_Num_Floppies));

	pf(platform)
		{
		#undef PFX
		#define PFX() IS
		BNTStart(platforms)
		bn(ISA)
		bn(EISA)
		bn(MCA)
		bn(FAMILY3)
		BNTEnd()

		ShowFlags(m_ida->IDA_platform, platforms);
		}

	pf(flags)
		{
		#undef PFX
		#define PFX() IDAF
		BNTStart(idaflags)
		bn(BOOT_COMPLETE)
		bn(REAL_MODE_ONLY)
		bn(FORCE_RM_IO)
		bn(REAL_MODE_LOGICAL)
		bn(FORCE_PM_IO)
		bn(V86_AREA_TAKEN)
		bn(BIG_MEMORY)
		bn(MAPPER_BUSY)
		bn(NEED_4BHOOK)
		bn(INT13_DUE_TO_RMM)
		bn(MAPPER_INIT)
		bn(PUNT_CDS)
		bn(MSCDEX_PRESENT)
		bn(DOS_PAGER)
		bn(SHUTDOWN)
		bn(INT13_FCN_8)
		bn(STAC_PRESENT)
		bn(START_SUCCESS)
		bn(CANT_SHARE_IRQ)
		bn(NO_BOOT_CONFIG)
		bn(512_BYTE_EMUL_POSSIBLE)
		bn(INT13_IGNORE_COPY_PROT)
		bn(EZ_DRIVE)
		bn(NO_SPARROW)
		#ifdef NEC_98
		bn(BIOSCDROM_PRESENT)
		#endif
		BNTEnd()

		ShowFlags(m_ida->IDA_flags, idaflags);
		}

	pf(platform_config_data)
	pf(first_dcb)
	pf(logical_dev_map)
	pf(physical_dev_map)
	pf(rmm_phys_dcb)
	pf(first_vrp)
	pf(drive_letter_map)
	pf(cdrom_letter_map)
	pf(rmd_ptr)
	pf(aspi_cam_rmds)
	pf(big_mem_buf_virt)
	pf(big_mem_buf_phys)
	pf(big_mem_buf_size)
	pf(ios_mem_pool_size)
	pf(dbl_vol_map)
	pf(ontrack_data)
	pf(rm_irq)
	}							// CIda::Show

void CCalldown::Show()
	{							// CCalldown::Show
	#undef pf
	#define pf(f)  AddParameter(#f, csprintf("%8.8X", m_cdp->DCB_cd_##f));

	AddParameter("Calldown Entry Address", csprintf("%8.8X", m_cdp));
	pf(io_address)
	pf(flags)
		{
		#undef PFX
		#define PFX() DCB_dmd
		BNTStart(dmdflags)
		bn(srb_cdb)
		bn(logical)
		bn(physical)
		bn(small_memory)
		bn(not_512)
		bn(word_align)
		bn(dword_align)
		bn(phys_sgd)
		bn(phys_sgd_ptr)
		bn(do_a_b_toggling)
		bn(query_remov)
		bn(request_sns)
		bn(lock_unlock_media)
		bn(load_eject_media)
		bn(clear_media_chg)
		bn(serialize)
		bn(prot_mode)
		bn(no_xclusive)
		bn(pageability)
		BNTEnd()

		ShowFlags(m_cdp->DCB_cd_flags, dmdflags);
		}
	pf(next)
	pf(expan_off)
	pf(layer_flags)
	AddParameter("lgn", csprintf("%d (%s)", m_cdp->DCB_cd_lgn, lgn[m_cdp->DCB_cd_lgn]));
	}							// CCalldown::Show

void CVolume::Show()
	{							// CVolume::Show
	#undef pf
	#define pf(f)  AddParameter(#f, csprintf("%8.8X", m_vrp->VRP_##f));
	
	AddParameter("VRP Address", csprintf("%8.8X", m_vrp));

	pf(demand_flags)
		{
		#undef PFX
		#define PFX() DCB_dmd
		BNTStart(dmdflags)
		bn(srb_cdb)
		bn(logical)
		bn(physical)
		bn(small_memory)
		bn(not_512)
		bn(word_align)
		bn(dword_align)
		bn(phys_sgd)
		bn(phys_sgd_ptr)
		bn(do_a_b_toggling)
		bn(query_remov)
		bn(request_sns)
		bn(lock_unlock_media)
		bn(load_eject_media)
		bn(clear_media_chg)
		bn(serialize)
		bn(prot_mode)
		bn(no_xclusive)
		bn(pageability)
		BNTEnd()

		ShowFlags(m_vrp->VRP_demand_flags, dmdflags);
		}
	pf(event_flags)
		{
		#undef PFX
		#define PFX() VRP_ef
		BNTStart(evflags)
		bn(media_changed)
		bn(media_uncertain)
		bn(prompting)
		bn(input_share)
		bn(output_share)
		bn(user_canceled)
		bn(write_protected)
		bn(real_mode_mapped)
		bn(ios_locked)
		BNTEnd()

		ShowFlags(m_vrp->VRP_event_flags, evflags);
		}
	pf(max_sgd)
	pf(max_req_size)
	pf(delta_to_ior)
	pf(block_size)
	pf(fsd_hvol)
	pf(fsd_entry)
	pf(device_handle)
	pf(partition_offset)
	pf(next_vrp)
	pf(logical_handle)
	}							// CVolume::Show
