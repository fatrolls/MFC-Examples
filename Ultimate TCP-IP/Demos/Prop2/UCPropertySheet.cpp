// UCPropertySheet.cpp: implementation of the CUCPropertySheet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UCPropertySheet.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUCPropertySheet::CUCPropertySheet(HWND hParent, HINSTANCE hInst)
{
	m_hWndParent=hParent;
	SetInstan(hInst);
	NumPages=0;
}

CUCPropertySheet::~CUCPropertySheet()
{

}

int CUCPropertySheet::Create(TCHAR* Title,CUCPropertyElement* /* element */)
{
	int i;
	for(i=0;i<NumPages;i++)
		memcpy(&psp[i],&(Pages[i]->psp),sizeof(PROPSHEETPAGE));

	for(i=0;i<NumPages;i++)
		psp[i].hInstance=GetInstan();

	// Define structure for the PropertySheet.
	HeaderStructure.dwSize = sizeof(PROPSHEETHEADER);
    HeaderStructure.dwFlags = PSH_PROPSHEETPAGE | PSH_USECALLBACK |PSH_NOAPPLYNOW;
    HeaderStructure.hwndParent = m_hWndParent;
    HeaderStructure.hInstance = GetInstan();
    HeaderStructure.pszIcon = MAKEINTRESOURCE(IDI_ICON1);
    HeaderStructure.pszCaption = Title;
    HeaderStructure.nPages = NumPages;
    HeaderStructure.nStartPage = 0;
    HeaderStructure. ppsp = (LPCPROPSHEETPAGE) &(psp[0]);
    HeaderStructure.pfnCallback = PropSheetProc;
	
	return (int)PropertySheet(&HeaderStructure);
}

int CALLBACK CUCPropertySheet::PropSheetProc(HWND hwndDlg,UINT uMsg,LPARAM /* lParam */)
{
	//DLGTEMPLATE *templ;
	switch(uMsg){
	case PSCB_PRECREATE:
		
	
		break;
	case PSCB_INITIALIZED:
		{
		// Ghazi 
		//remove the Ok Button so when the property sheet is crteated 
		// only the cancel button will be visible
		HWND hOkButn = GetDlgItem(hwndDlg,IDOK);
		EnableWindow(hOkButn,FALSE);
		ShowWindow(hOkButn,SW_HIDE);
		// change the cacel button to an exit 
		HWND hCancelButn = GetDlgItem(hwndDlg,IDCANCEL);
		SetWindowText(hCancelButn,_T("Exit"));
		break;
		}
	}	
return 1;
}



int CUCPropertySheet::AddPage(CUCPage *page)
{
	Pages[NumPages]=page;
	NumPages++;

return 0;
}


