#include <afxwin.h>
#include <afxdlgs.h>
#include "resource.h"

class CSheet : public CPropertySheet
{
public:
	
	CPropertyPage Page1;
	CPropertyPage Page2;
	CPropertyPage Page3;
	CPropertyPage Page4;
	CMenu  Menu;

	CSheet() : CPropertySheet( "Property Sheet Demo By Piperopoulos Panagiotis" )
	{
		Page1.Construct( IDD_VIEW1 );
		Page2.Construct( IDD_VIEW2 );
		Page3.Construct( IDD_VIEW3 );
		Page4.Construct( IDD_VIEW4 );
		AddPage( &Page1 );
		AddPage( &Page2 );
		AddPage( &Page3 );
		AddPage( &Page4 );
	}

	~CSheet(){}

	BOOL OnInitDialog( )
	{
		CPropertySheet::OnInitDialog();

		GetDlgItem( IDOK )->ShowWindow( SW_HIDE );
		GetDlgItem( IDCANCEL )->ShowWindow( SW_HIDE );
		GetDlgItem( ID_APPLY_NOW )->ShowWindow( SW_HIDE );

		Menu.LoadMenu( IDR_MENU );
		SetMenu( &Menu );
		
		return TRUE;
	}
	
	void DisplayPage( int Page )
	{
		switch( Page )
		{
			case IDM_1 :
				SetActivePage( &Page1 );
				break;
			case IDM_2 :
				SetActivePage( &Page2 );
				break;
			case IDM_3 :
				SetActivePage( &Page3 );
				break;
			case IDM_4 :
				SetActivePage( &Page4 );
				break;
		}
	}

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP( CSheet, CPropertySheet )
	
	ON_COMMAND_RANGE( IDM_1, IDM_4, DisplayPage )

END_MESSAGE_MAP()


class TheApp : public CWinApp
{
public:
	
	TheApp(){}
	~TheApp(){}

	virtual BOOL InitInstance()
	{
	#ifdef _AFXDLL
		Enable3dControls();		
	#else
		Enable3dControlsStatic();
	#endif

	CSheet ps;
	m_pMainWnd = &ps;
	ps.DoModal();

	return FALSE;
	}
};

TheApp MyApp;
