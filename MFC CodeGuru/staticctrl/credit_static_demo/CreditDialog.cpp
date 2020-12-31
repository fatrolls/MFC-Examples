// CreditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CreditsTest.h"
#include "CreditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static BOOL bClicked = FALSE;

char *pArrCredit = { "|NETBAS FOR WINDOWS NT\t||Copyright (c) 1998|"
        "Test Data AS|All Rights Reserved||"
        "BITMAP1^||"    // this is a quoted bitmap resource 
        "Project Lead\r||Kjetil Kvamme|||"
        "Technical Lead\r||Paul K. Tonder|||"
        "Engineering Lead\r||Paul K. Tonder|||"
        "Product Lead\r||Tom Rotting|||"
        "Engineering\r||Paul K. Tonder,  Rolf T. Wold,  Sigbjorn Helset|"
        "Reidar Ognedal,  Kjetil Kvamme, Arne Bakken|||"
        "BITMAP2^|||"  // this is a quoted bitmap resource 
        "QA\r||Mary Hech,  Sam Bamnm,  Ron Fonn,  Steve Waeve|"
        "Igor Borisnoff,  FellaB |||"
        "Documentation\r||"
        "Arvid Molnvik,  Joanne Hone,  Annette Fune|||"
        "Technical Program Office\r||Burf Murphy, Foll Roller||||"
        "Systems Support\r||Bendy Land|||"
        "Administrative Support\r||Donna Fonna|||"
        "* * * * * * * * *\t|||"
        "BITMAP3^||"
        "Project Manager\r||Dwain Kinghorn|||"
        "Engineering\r||"
        "Hank Bank,  Ray Fay,  Bill Sill,  Mark Dark,  Peter Leter|"
        "Lev Bef|||Quality Assurance\r||"
        "Biff Bin||||"
        "BITMAP4^|||||"
        };

/////////////////////////////////////////////////////////////////////////////
// CCreditDialog dialog

CCreditDialog::CCreditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCreditDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreditDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	bitmapIDs[0] = IDB_BITMAP1;
	bitmapIDs[1] = IDB_BITMAP2;
}


void CCreditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreditDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreditDialog, CDialog)
	//{{AFX_MSG_MAP(CCreditDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreditDialog message handlers
#define  DISPLAY_TIMER_ID		151

BOOL CCreditDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_static.SubclassDlgItem(IDC_DISPLAY_STATIC,this);
	m_static.SetCredits(pArrCredit,'|');
	m_static.SetSpeed(DISPLAY_FAST);
	m_static.SetColor(BACKGROUND_COLOR, RGB(0,0,255));
	m_static.SetTransparent();
//	m_static.SetGradient(GRADIENT_RIGHT_DARK);
	m_static.SetBkImage(bitmapIDs[0]);
	m_static.StartScrolling();
	TimerOn = SetTimer(DISPLAY_TIMER_ID,5000,NULL);
    ASSERT(TimerOn != 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreditDialog::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent != DISPLAY_TIMER_ID)
	{
		CDialog::OnTimer(nIDEvent);
		return;
	}

	static int index = 0;

	index = ++index % 2;
	
	m_static.SetBkImage(bitmapIDs[index]);
	
	CDialog::OnTimer(nIDEvent);
}

void CCreditDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(TimerOn)
		ASSERT(KillTimer(DISPLAY_TIMER_ID));
}
