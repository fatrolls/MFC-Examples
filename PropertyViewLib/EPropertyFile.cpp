// EPropertyFile.cpp: implementation of the EPropertyFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropertyFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropertyFile::EPropertyFile( IPropertyHost* pHost , const CString& sName , CString* pProperty , const CString& sFilters ) : EPropertyString( pHost , sName , pProperty )
{
	m_sFilters = sFilters;
}

EPropertyFile::~EPropertyFile()
{
}

bool EPropertyFile::HasButton()
{
	return true;
}

bool EPropertyFile::OnCommand( EPropWnd* pParent , WPARAM wParam , LPARAM lParam )
{
	bool bPropertyChanged = false;

//	CFileDialog dia(TRUE,NULL,m_sProperty,OFN_HIDEREADONLY,m_sFilters,NULL);
	CFileDialog dia(TRUE,NULL,NULL,OFN_HIDEREADONLY,m_sFilters,NULL);

	if(dia.DoModal() == IDOK )
	{
		CString s = dia.GetPathName();

		if( m_pHost->PropertyChanging(m_pProperty,&s) )
		{
			*(CString*)m_pProperty = s;
			bPropertyChanged = true;
		}
	}

	return bPropertyChanged;
}

//"Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||";

void EPropertyFile::AddFilterItem( CString sDescription , CString sFilter )
{
	CString sNew;
	CString sOld = m_sFilters;

	sNew.Format( "%s|%s" , sDescription , sFilter );

	m_sFilters.Format("%s|%s",sNew,sOld);
}

