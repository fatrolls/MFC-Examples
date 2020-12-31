// EPropertyTextblock.cpp: implementation of the EPropertyTextblock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropertyTextblockWindow.h"
#include "EPropertyTextblock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropertyTextblock::EPropertyTextblock( IPropertyHost* pHost , const CString& sName , CString* pProperty , bool bEnabled ) : EIconTextButtonProperty( pHost , sName , pProperty , bEnabled )
{
	m_pPropertyEditWindow = NULL;
	m_pCtrl = NULL;
}

EPropertyTextblock::~EPropertyTextblock()
{
	CloseEditWindow();
}

bool EPropertyTextblock::HasButton()
{
	return true;
}

CString EPropertyTextblock::GetTextValue()
{
	CString s = *(CString*)m_pProperty;

	CString t;
	int n = s.GetLength();

	for( int i=0 ; i<n ; i++ )
	{
		char c = s[i];

		if( c == '\r' )
		{
//			t += "\\r";
			t += "<>";
		}
		else if( c == '\n' )
		{
//			t += "\\n";
			t += "<>";
		}
		else
		{
			t += c;
		}
	}

	return t;
}

//CString EPropertyTextblock::GetEditText()
//{
//	return "aaa\\nbbb";
////	return m_sTextblock;
//}

bool EPropertyTextblock::OnCommand( EPropWnd* pParent , WPARAM wParam , LPARAM lParam )
{
	bool bPropertyChanged = false;

	m_pCtrl = pParent;

	if( m_pPropertyEditWindow == NULL )
	{
		m_pPropertyEditWindow = new EPropertyTextblockWindow( this , pParent , m_sName );

		int scrw = GetSystemMetrics(SM_CXSCREEN);
		int scrh = GetSystemMetrics(SM_CYSCREEN);

		CPoint ButtonCenter = m_ButtRect.CenterPoint();
		pParent->ClientToScreen(&ButtonCenter);

		CRect r(0,0,200,200);
		r.OffsetRect(ButtonCenter.x,ButtonCenter.y);

		if( ButtonCenter.x >= scrw/2 )
		{
			r.OffsetRect( -200 , 0 );
		}
		
		if( ButtonCenter.y >= scrh/2 )
		{
			r.OffsetRect( 0 , -200 );
		}
	
		//m_pPropertyEditWindow->Create( NULL , m_sName , WS_OVERLAPPEDWINDOW | WS_VISIBLE , r , pCtrl );
		m_pPropertyEditWindow->Create( NULL , m_sName , WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE , r , pParent );

		//WS_OVERLAPPEDWINDOW = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX


		m_pPropertyEditWindow->SetEditText( *((CString*)m_pProperty) );
//		m_pPropertyEditWindow->SetIcon( AfxGetApp()->LoadIcon(IDR_MAINFRAME) );
	}

	return bPropertyChanged;
}

void EPropertyTextblock::OnWindowButtonOk()
{
	m_pCtrl->OnDoPropApply();
}

void EPropertyTextblock::OnWindowButtonCancel()
{
	CloseEditWindow();
}

void EPropertyTextblock::CloseEditWindow()
{
	if( m_pPropertyEditWindow != NULL )
	{
		m_pPropertyEditWindow->DestroyWindow();
		m_pPropertyEditWindow = NULL;
	}
}

bool EPropertyTextblock::OnPropApply()
{
	bool bChangeOK = false;

	if( m_pPropertyEditWindow == NULL )
	{
	}
	else
	{
		CString s = m_pPropertyEditWindow->GetEditText();

		bChangeOK = m_pHost->PropertyChanging( m_pProperty , &s );

		if( bChangeOK )
		{
			*((CString*)m_pProperty) = s;
		}

		CloseEditWindow();
	}

	return bChangeOK;
}

void EPropertyTextblock::OnPropClose()
{
	EIconTextButtonProperty::OnPropClose();
	OnWindowButtonCancel();
}
