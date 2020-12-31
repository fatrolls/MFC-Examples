// DlgDemo.cpp : implementation file
//

#include "stdafx.h"
#include "LayoutManager.h"
#include "DlgDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDemo dialog


CDlgDemo::CDlgDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDemo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDemo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgDemo)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDemo message handlers

BOOL CDlgDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LayoutManager.Attach(this);
	m_LayoutManager.AddChild(IDC_BUTTON3);

	
	// Constrain button2 to the right and left sides of buttons 1 and 3 respectively
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 10, IDC_BUTTON1);
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -10, IDC_BUTTON3);

	// Constrain the bottom of button 3 to the top of button 4
	// This is used for vertical resize. (button4 will never be hidden by button3)

	m_LayoutManager.RemoveConstraint(IDC_BUTTON3, OX_LMS_LEFT);
	m_LayoutManager.SetConstraint(IDC_BUTTON3, OX_LMS_RIGHT, OX_LMT_SAME, -10);
	m_LayoutManager.SetConstraint(IDC_BUTTON3, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -10, IDC_BUTTON4);
	
	// Make button 4 start at the left of button1 and end at the right of button3
	m_LayoutManager.SetConstraint(IDC_BUTTON4, OX_LMS_LEFT,  OX_LMT_SAME, 0, IDC_BUTTON1);
	m_LayoutManager.SetConstraint(IDC_BUTTON4, OX_LMS_RIGHT, OX_LMT_SAME, 0, IDC_BUTTON3);

	// Make button 4 10 below button1 and 10 above the botton of the window
	m_LayoutManager.SetConstraint(IDC_BUTTON4, OX_LMS_TOP, OX_LMT_OPPOSITE, 10, IDC_BUTTON1);
	m_LayoutManager.SetConstraint(IDC_BUTTON4, OX_LMS_BOTTOM, OX_LMT_SAME, -10);
	
	// Set the minimum size of the window
	m_LayoutManager.SetMinMax(IDC_BUTTON2, CSize(40,0));
	m_LayoutManager.SetMinMax(IDC_BUTTON4, CSize(0,60), CSize(0,0));
	
	// Draw the layout with the new constraints
	// This is necessary when constraints are implemented and the window must be refreshed
	m_LayoutManager.RedrawLayout();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDemo::OnButton1() 
	{
	// Set buttons 1,2,3 to have a default constraint (windows default)
	m_LayoutManager.SetDefaultConstraint(IDC_BUTTON1);
	m_LayoutManager.SetDefaultConstraint(IDC_BUTTON2);
	m_LayoutManager.SetDefaultConstraint(IDC_BUTTON3);

	m_LayoutManager.RedrawLayout();
	MessageBox(_T("Buttons 1,2,3 have default behavior"));
	}

void CDlgDemo::OnButton2() 
	{
	// Constrain button 1 to 10 points from the left of the window
	// Remove any constraints on the right of button1
	m_LayoutManager.SetConstraint(IDC_BUTTON1, OX_LMS_LEFT, OX_LMT_SAME, 10);
	m_LayoutManager.RemoveConstraint(IDC_BUTTON1, OX_LMS_RIGHT);

	//Constrain the left of button 2 to the right of button1
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 10, IDC_BUTTON1);
	//Constrain the right of button2 to the left of button3
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -10, IDC_BUTTON3);

	// Remove any constraints on the left of button3
	m_LayoutManager.RemoveConstraint(IDC_BUTTON3, OX_LMS_LEFT);
	// Constrain the right of button3 to the right of the window
	m_LayoutManager.SetConstraint(IDC_BUTTON3, OX_LMS_RIGHT, OX_LMT_SAME, -10);

	m_LayoutManager.RedrawLayout();
	MessageBox(_T("Button3's left side will be free.\nButton2 will stretch between buttons 1 and 3"));
	}

void CDlgDemo::OnButton3() 
	{
	//Button1 will be 10 points from the left of the window
	m_LayoutManager.SetConstraint(IDC_BUTTON1, OX_LMS_LEFT, OX_LMT_SAME, 10);
	//Free the right side of button1
	m_LayoutManager.RemoveConstraint(IDC_BUTTON1, OX_LMS_RIGHT);

	// The following code will cause button2 to stretch between button1 and button 3
	// if the right of button1 or the left of button2 is moved
	// Button2's left side will be constrained to the right of button1
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 10, IDC_BUTTON1);
	// Button2's right side will be constrained to the left of button3
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -10, IDC_BUTTON3);
	
	// The following code will cause the left of button3 to remain stationary while the right
	// moves with the resizing of the window.  This causes button 3 to stretch with the window
	// Button3 will have default constraints
	m_LayoutManager.SetDefaultConstraint(IDC_BUTTON3);
	// Button3's right side will be constrained to the right of the window
	m_LayoutManager.SetConstraint(IDC_BUTTON3, OX_LMS_RIGHT, OX_LMT_SAME, -10);

	m_LayoutManager.RedrawLayout();
	MessageBox(_T("Button3's left side will be constrainted to the container's left side.\nButton3 will stretch between button2 and the windows right side"));
	}

void CDlgDemo::OnButton4() 
	{
	
	// Button1's right side will be 33 percent of the way accross the window 
	m_LayoutManager.SetConstraint(IDC_BUTTON1, OX_LMS_LEFT, OX_LMT_SAME, 10);
	m_LayoutManager.SetConstraint(IDC_BUTTON1, OX_LMS_RIGHT, OX_LMT_POSITION, 33);
  
	// Button2 will be between buttons 1 and 3.  Since button1 and 3 occupy 66 percent of the window between
	// then (0-33,66-100) button 2 will also occupy 33 percent of the space (33-66)
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_BUTTON1);
	m_LayoutManager.SetConstraint(IDC_BUTTON2, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5, IDC_BUTTON3);

	// Button3's left side will be 66 percent of the way accross the window
	m_LayoutManager.SetConstraint(IDC_BUTTON3, OX_LMS_LEFT, OX_LMT_POSITION, 66);
	m_LayoutManager.SetConstraint(IDC_BUTTON3, OX_LMS_RIGHT,  OX_LMT_SAME, -10);

	m_LayoutManager.RedrawLayout();
	MessageBox(_T("Buttons 1,2,3 will be equally constrained"));
	}
