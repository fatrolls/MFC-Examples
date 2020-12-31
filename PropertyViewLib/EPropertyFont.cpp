// EPropertyFont.cpp: implementation of the EPropertyFont class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EPropListCtrl.h"
#include "IPropertyHost.h"
#include "EPropertyFont.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropertyFont::EPropertyFont( IPropertyHost* pHost , const CString& sName , CFont* pProperty ) : EIconTextButtonProperty( pHost , sName , pProperty , true )
{
}

EPropertyFont::~EPropertyFont()
{

}

bool EPropertyFont::HasButton()
{
	return true;
}

bool EPropertyFont::OnCommand( EPropWnd* pParent , WPARAM wParam , LPARAM lParam )
{
	bool bPropertyChanged = false;

	int nBeg;
	int nEnd;
	pParent->GetIDRange( nBeg , nEnd );

	if( wParam == nBeg + 1 )
	{
		LOGFONT log;
		((CFont*)m_pProperty)->GetLogFont(&log);

		CFontDialog dia(&log,CF_INITTOLOGFONTSTRUCT|CF_SCREENFONTS);

		if( dia.DoModal() == IDOK )
		{
			dia.GetCurrentFont(&log);
			bPropertyChanged = m_pHost->PropertyChanging( m_pProperty , &log );

			if( bPropertyChanged )
			{
				((CFont*)m_pProperty)->DeleteObject();
				((CFont*)m_pProperty)->CreateFontIndirect(&log);
			}
		}
	}

	return bPropertyChanged;
}

CString EPropertyFont::GetTextValue()
{
	LOGFONT log;
	((CFont*)m_pProperty)->GetLogFont(&log);

	CString s;

//------
//	s.Format("%s (%d)",log.lfFaceName,log.lfHeight);
//------
	s = log.lfFaceName;
//------

	return s;
}
