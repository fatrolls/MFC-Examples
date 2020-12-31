// EPropertyDir.cpp: implementation of the EPropertyDir class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <shlobj.h>

#include "IPropertyHost.h"
#include "EPropertyDir.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropertyDir::EPropertyDir(IPropertyHost* pHost , const CString& sName , CString* Property )
: EPropertyString( pHost, sName, Property)
{

}

EPropertyDir::~EPropertyDir()
{

}

bool EPropertyDir::HasButton()
{
	return true;
}

bool EPropertyDir::OnCommand(EPropWnd* pParent , WPARAM wParam , LPARAM lParam )
{
	char folder_path[MAX_PATH];//will receive the folder complete path 
	LPMALLOC shallocator;//will point to IMalloc interface of shell memory allocator 
	LPITEMIDLIST itemids=NULL;//pointer to items list

	BROWSEINFO bwinfo;//the structure which contains necessary informations 
	char buffer[MAX_PATH];//will receive the folder name 
	FillMemory((void*)&bwinfo,sizeof(bwinfo),0);//memory cleaning 
	bwinfo.hwndOwner=NULL;//handle of owner window (NULL here) 
	bwinfo.pidlRoot=NULL;//starting point for browse (NULL means Computer Desktop) 
	bwinfo.pszDisplayName=(char*) buffer;//will receive folder name (as displayed) 
	bwinfo.lpszTitle="Select the folder";//dialog title 
	bwinfo.ulFlags=0;//browsing flags (0 means no restrictions) 
	itemids = SHBrowseForFolder(&bwinfo);// now browsing for folder...and keep the results 

	bool bPropertyChanged = false;

	if (itemids !=NULL)//was dialog canceled ? 
	{ 
		SHGetPathFromIDList(itemids,(char*) folder_path);//get the folder path from SHBrowseForFolder result 

		CString s(folder_path);

		if( m_pHost->PropertyChanging(m_pProperty,&s) )
		{
			*(CString*)m_pProperty = s;
			bPropertyChanged = true;
		}

		SHGetMalloc(&shallocator);//get shell memory allocator (a pointer to his IMalloc interface) 
		shallocator->Free((void*) itemids);//releasing memory via this allocator 
		shallocator->Release();//releasing allocator 
	}	 

	return bPropertyChanged;


}