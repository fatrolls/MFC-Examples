// PingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nettools.h"
#include "pingparmlist.h"
#include "PingDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define IPOPT_TOS_LOW_DELAY    16
#define IPOPT_TOS_HIGH_RELIAB  4
#define IPOPT_TOS_HIGH_THRU    8 
/////////////////////////////////////////////////////////////////////////////
// CPingDlg dialog


CPingDlg::CPingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPingDlg)
	m_ping_hostname = _T("");
	m_ping_opt_resolve = FALSE;
	m_ping_opt_ttl_val = 0;
	m_ping_opt_dontfragment = FALSE;
	m_ping_opt_packetlen_val = 64;
	m_ping_opt_numpackets_val = 4;
	m_ping_opt_rroute_val = 0;
	m_ping_opt_timestamp_val = 0;
	m_ping_opt_interrupt = FALSE;
	m_ping_opt_tos_high_reliab = FALSE;
	m_ping_opt_tos_high_thru = FALSE;
	m_ping_opt_tos_low_delay = FALSE;
	m_ping_opt_tos_none = TRUE;
	m_ping_opt_timeout_val = 0;
	m_ping_opt_rrloose = FALSE;
	m_ping_opt_rrstrict = FALSE;
	m_ping_opt_routes = _T("");
	m_ping_opt_tracert = FALSE;
	//}}AFX_DATA_INIT
}


void CPingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPingDlg)
	DDX_Text(pDX, IDC_PING_HOSTNAME, m_ping_hostname);
	DDX_Check(pDX, IDC_PING_OPT_A, m_ping_opt_resolve);
	DDX_Text(pDX, IDC_PING_OPT_I_VAL, m_ping_opt_ttl_val);
	DDV_MinMaxUInt(pDX, m_ping_opt_ttl_val, 0, 255);
	DDX_Check(pDX, IDC_PING_OPT_F, m_ping_opt_dontfragment);
	DDX_Text(pDX, IDC_PING_OPT_L_VAL, m_ping_opt_packetlen_val);
	DDV_MinMaxUInt(pDX, m_ping_opt_packetlen_val, 64, 8192);
	DDX_Text(pDX, IDC_PING_OPT_N_VAL, m_ping_opt_numpackets_val);
	DDV_MinMaxUInt(pDX, m_ping_opt_numpackets_val, 4, 64);
	DDX_Text(pDX, IDC_PING_OPT_R_VAL, m_ping_opt_rroute_val);
	DDV_MinMaxUInt(pDX, m_ping_opt_rroute_val, 0, 9);
	DDX_Text(pDX, IDC_PING_OPT_S_VAL, m_ping_opt_timestamp_val);
	DDV_MinMaxUInt(pDX, m_ping_opt_timestamp_val, 0, 4);
	DDX_Check(pDX, IDC_PING_OPT_T, m_ping_opt_interrupt);
	DDX_Check(pDX, IDC_PING_OPT_TOS_HIGH_RELIAB, m_ping_opt_tos_high_reliab);
	DDX_Check(pDX, IDC_PING_OPT_TOS_HIGH_THRU, m_ping_opt_tos_high_thru);
	DDX_Check(pDX, IDC_PING_OPT_TOS_LOW_DELAY, m_ping_opt_tos_low_delay);
	DDX_Check(pDX, IDC_PING_OPT_TOS_NONE, m_ping_opt_tos_none);
	DDX_Text(pDX, IDC_PING_OPT_W_VAL, m_ping_opt_timeout_val);
	DDV_MinMaxUInt(pDX, m_ping_opt_timeout_val, 0, 10000);
	DDX_Check(pDX, IDC_PING_OPT_RRLOOSE, m_ping_opt_rrloose);
	DDX_Check(pDX, IDC_PING_OPT_RRSTRICT, m_ping_opt_rrstrict);
	DDX_Text(pDX, IDC_PING_OPT_RROUTE_LRSR, m_ping_opt_routes);
	DDV_MaxChars(pDX, m_ping_opt_routes, 200);
	DDX_Check(pDX, IDC_PING_OPT_TRACERT, m_ping_opt_tracert);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPingDlg, CDialog)
	//{{AFX_MSG_MAP(CPingDlg)
	ON_BN_CLICKED(IDC_PING_OPT_TOS_NONE, OnPingOptTosNone)
	ON_BN_CLICKED(IDC_PING_OPT_TOS_HIGH_RELIAB, OnPingOptTosHighReliab)
	ON_BN_CLICKED(IDC_PING_OPT_TOS_HIGH_THRU, OnPingOptTosHighThru)
	ON_BN_CLICKED(IDC_PING_OPT_TOS_LOW_DELAY, OnPingOptTosLowDelay)
	ON_BN_CLICKED(IDC_PING_OPT_RRLOOSE, OnPingOptRrloose)
	ON_BN_CLICKED(IDC_PING_OPT_RRSTRICT, OnPingOptRrstrict)
	ON_EN_CHANGE(IDC_PING_OPT_R_VAL, OnChangePingOptRVal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPingDlg message handlers

BOOL CPingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPingDlg::OnOK() 
{
	
	CHAR SrchBuff[256];
	CHAR HoldBuff[256];
	CHAR *pSrchBuff;
	CHAR *pSrchMax;
	CHAR *pHoldBuff;
	CHAR *pcsLine;
	CHAR *SrchArg = ", ";
	int HitOffset;
	
	CString csLine;




	if (!UpdateData(TRUE))  // retrieve and validate data
		return;				// validate failed

	
	if (m_ping_hostname.IsEmpty())
	{
		AfxMessageBox("Please enter a Hostname");
		return;
	}

	if ((m_ping_opt_rrloose) || (m_ping_opt_rrstrict))
	{
		
		if (m_ping_opt_routes.IsEmpty())
		{
			AfxMessageBox("Must Specify Addr's Routing");
			return;
		}
		else
		{
			pSrchBuff = SrchBuff;
			pHoldBuff = HoldBuff;
			strcpy(pSrchBuff,m_ping_opt_routes);
			pSrchMax = pSrchBuff + strlen(SrchBuff);
			m_lpPingParms->opt_rrdata.RemoveAll();
			while(TRUE)
			{
				HitOffset = strcspn(pSrchBuff,SrchArg);
				pcsLine = csLine.GetBuffer(HitOffset);
				memcpy(pcsLine,pSrchBuff,HitOffset);
				csLine.ReleaseBuffer(HitOffset);
				m_lpPingParms->opt_rrdata.Add(csLine);
				HitOffset ++;  //bump past ',' or blank
				pSrchBuff += HitOffset;
				if (pSrchBuff >= pSrchMax)
					break;
			}
			if (m_lpPingParms->opt_rrdata.GetSize() > 9)
			{
				AfxMessageBox("Too Many Routes Max 9");
				m_lpPingParms->opt_rrdata.RemoveAll();
				return;
			}



		}

	}


	// initialize the threads parmslist with
	// the data from the dialog box.
	//

	m_lpPingParms->opt_tos_val = 0;

	if (m_ping_opt_tos_high_reliab)
		m_lpPingParms->opt_tos_val |= IPOPT_TOS_HIGH_RELIAB;

	if (m_ping_opt_tos_high_thru)
		m_lpPingParms->opt_tos_val |= IPOPT_TOS_HIGH_THRU;

	if (m_ping_opt_tos_low_delay)
		m_lpPingParms->opt_tos_val |= IPOPT_TOS_LOW_DELAY;

	if (m_ping_opt_tos_none)
		m_lpPingParms->opt_tos_val = 0;

	memset(m_lpPingParms->hostname,
		   0,
		   sizeof(m_lpPingParms->hostname));

	strcat(m_lpPingParms->hostname,m_ping_hostname);
	m_lpPingParms->opt_resolve = m_ping_opt_resolve;
	m_lpPingParms->opt_dontfragment =	m_ping_opt_dontfragment;
	m_lpPingParms->opt_interrupt = m_ping_opt_interrupt;
	m_lpPingParms->opt_ttl_val = m_ping_opt_ttl_val;
	m_lpPingParms->opt_packetlen_val = m_ping_opt_packetlen_val;
	m_lpPingParms->opt_numpackets_val = m_ping_opt_numpackets_val;
	m_lpPingParms->opt_rroute_val = m_ping_opt_rroute_val;
	m_lpPingParms->opt_timestamp_val = m_ping_opt_timestamp_val;
	m_lpPingParms->opt_timeout_val = m_ping_opt_timeout_val;
	m_lpPingParms->opt_rrloose = m_ping_opt_rrloose;
	m_lpPingParms->opt_rrstrict = m_ping_opt_rrstrict;
	m_lpPingParms->opt_tracert = m_ping_opt_tracert;

	//
	//
	//
	//

	

	//while(lbcount)
	//{
	//	lbcount = m_ping_opt_routes_lb.GetLine(lbline,
	//										   lbbuf,
	//										   sizeof(lbbuf));
	//	if (lbcount == 0)
	//		break;
	//	lp_line = cs_line.GetBuffer(lbcount);
	//	memcpy(lp_line,lbbuf,lbcount);
	//	cs_line.ReleaseBuffer(lbcount);
	//	m_lpPingParms->opt_rrdata.Add(cs_line);
	//	lbline++;
	//}
	
	

	CDialog::OnOK();
	// TODO: Add extra validation here
	
	
}

void CPingDlg::OnPingOptTosNone() 
{
	CheckDlgButton(IDC_PING_OPT_TOS_HIGH_THRU,0);
	CheckDlgButton(IDC_PING_OPT_TOS_HIGH_RELIAB,0);
	CheckDlgButton(IDC_PING_OPT_TOS_LOW_DELAY,0);
	CheckDlgButton(IDC_PING_OPT_TOS_NONE,1);
	
	
	// TODO: Add your control notification handler code here
	
}

void CPingDlg::OnPingOptTosHighReliab() 
{
	CheckDlgButton(IDC_PING_OPT_TOS_HIGH_RELIAB,1);
	CheckDlgButton(IDC_PING_OPT_TOS_NONE,0);
	
	
	// TODO: Add your control notification handler code here
	
}

void CPingDlg::OnPingOptTosHighThru() 
{
	CheckDlgButton(IDC_PING_OPT_TOS_HIGH_THRU,1);
	CheckDlgButton(IDC_PING_OPT_TOS_NONE,0);
	
	// TODO: Add your control notification handler code here
	
}

void CPingDlg::OnPingOptTosLowDelay() 
{
	CheckDlgButton(IDC_PING_OPT_TOS_LOW_DELAY,1);
	CheckDlgButton(IDC_PING_OPT_TOS_NONE,0);

	// TODO: Add your control notification handler code here
	
}


void CPingDlg::OnPingOptRrloose() 
{
	CheckDlgButton(IDC_PING_OPT_RRLOOSE,1);
	CheckDlgButton(IDC_PING_OPT_RRSTRICT,0);
	SetDlgItemInt(IDC_PING_OPT_R_VAL,0,FALSE);
  

	// TODO: Add your control notification handler code here
	
}

void CPingDlg::OnPingOptRrstrict() 
{
	CheckDlgButton(IDC_PING_OPT_RRLOOSE,0);
	CheckDlgButton(IDC_PING_OPT_RRSTRICT,1);
	SetDlgItemInt(IDC_PING_OPT_R_VAL,0,FALSE);
	// TODO: Add your control notification handler code here
	
}

void CPingDlg::OnChangePingOptRVal() 
{
	BOOL m_btrans;
	BOOL *m_pbtrans;
	UINT m_editint;
	m_btrans = TRUE;  // check for errors
	m_pbtrans = &m_btrans;

	m_editint = GetDlgItemInt(IDC_PING_OPT_R_VAL,
					   m_pbtrans,
					   FALSE);
  
	if ((m_btrans) && (m_editint > 0))
	{
		CheckDlgButton(IDC_PING_OPT_RRLOOSE,0);
		CheckDlgButton(IDC_PING_OPT_RRSTRICT,0);
	}
		
	// TODO: Add your control notification handler code here
	
}
