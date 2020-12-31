// UCWnd.cpp: implementation of the CUCWnd class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "UCWnd.h"
//#include "UCPropertySheet.h"

COLORREF dwCustColors[16];


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HINSTANCE CUCWnd::m_hInstance=NULL;
CHOOSECOLOR CUCWnd::ColorTable;
CUCVTable CUCWnd::Vtable;
//CUCPropertyElement *CUCWnd::PropertyElement=NULL;




CUCWnd::CUCWnd()
{
	CUCVTable *table;
	table=GetVTable();
	table->AddItem(this);
	m_bChanged=FALSE;
}

CUCWnd::~CUCWnd()
{
	CUCVTable *table;
	table=GetVTable();
	table->DeleteClass(this);
}




/*UINT CALLBACK PagePatternProc(HWND hwndDlg,UINT uMsg,LPPROPSHEETPAGE lParam)
{
	//DLGTEMPLATE *templ;
	switch(uMsg){
	case PSCB_PRECREATE:
		//templ=(DLGTEMPLATE*)lParam;
		//if(templ->style && WS_POPUP)
		//	MessageBox(NULL,"Already a child Window","Msg",MB_OK);
		//templ->style=WS_CHILD | DS_MODALFRAME | WS_DLGFRAME | WS_OVERLAPPED | DS_3DLOOK | WS_VISIBLE |WS_CLIPSIBLINGS | DS_SETFONT;
		//templ->x=-100;
		//templ->y=-100;
		//templ->cx=300;
		//templ->cy=300;
/*		break;
	}
	
return 1;
}
*/


void CUCWnd::OnDrawItem(LPDRAWITEMSTRUCT)
{
}

void CUCWnd::OnInitDialog(WPARAM /* wParam */, LPARAM /* lParam */)
{

}

void CUCWnd::OnWndCommand(int notification,int item,HWND handle)
{
	switch(notification){
	case BN_CLICKED:
		OnClicked(item);
		break;
	case CBN_SELCHANGE:
		OnSelChange(item,handle);
		break;
	case CBN_DROPDOWN:
		OnDropDown(item,handle);
		break;
	case CBN_SETFOCUS:
		OnSetFocus(item,handle);
		break;
	case EN_CHANGE:
		OnEditChange(item,handle);
		break;
	case EN_UPDATE:
		OnUpdate(item,handle);
		break;

	}

}

void CUCWnd::OnCommand(WPARAM /* wParam */,LPARAM /* lParam */)
{


}
// GW: Added for help invoking
void CUCWnd::OnHelp(LPARAM /* lParam */)
{

}

void CUCWnd::OnClicked(int)
{

}

void CUCWnd::OnSelChange(int,HWND)
{

}

void CUCWnd::OnPaint(HDC)
{

}

void CUCWnd::OnMeasureitem(LPMEASUREITEMSTRUCT)
{
}

void CUCWnd::OnDropDown(int /* item */, HWND /* handle */)
{

}

void CUCWnd::OnSetFocus(int /* item */, HWND /* handle */)
{

}

COLORREF CUCWnd::OpenColorDialog(COLORREF color)
{
	CHOOSECOLOR *cc;
	cc=GetChooseColor();
	cc->lStructSize=sizeof(CHOOSECOLOR);
	cc->hwndOwner = m_hWnd; 
	cc->hInstance = NULL;
	cc->rgbResult = color; 
	cc->lpCustColors = &dwCustColors[0]; 
	cc->Flags = CC_ANYCOLOR | CC_SOLIDCOLOR | CC_RGBINIT; 
	cc->lCustData = NULL;
	cc->lpfnHook = NULL; 
	cc->lpTemplateName = NULL; 
	ChooseColor(cc);
	return cc->rgbResult;
}


void CUCWnd::OnLButtonDown(int /* key */, int /* px */, int /* py */)
{

}


void CUCWnd::OnLButtonUp(int /* key */, int /* px */, int /* py */)
{

}


void CUCWnd::OnMouseMove(int /* key */, WORD /* px */, WORD /* py */)
{

}

BOOL CALLBACK CUCWnd::DialogProc(HWND hwndDlg,UINT uMsg, WPARAM wParam,LPARAM lParam){
	//LPPAINTSTRUCT lpPaint;
	LPMEASUREITEMSTRUCT lpmis;  
	PROPSHEETPAGE *Spage;
	CUCWnd *wnd;




	switch(uMsg){
		case WM_INITDIALOG:
			Spage=(PROPSHEETPAGE*)lParam;
			wnd=(CUCWnd*)Spage->lParam;
			wnd->m_hWnd=hwndDlg;                // Set HWND handle in CUCWnd class.
			wnd=Vtable.FindClass(hwndDlg);		// Find the CUCWnd class by HWND handle.
			if(wnd!=NULL)wnd->OnInitDialog(wParam,lParam);
			return TRUE;

		case WM_COMMAND:
			wnd=Vtable.FindClass(hwndDlg);		// Find the CUCWnd class by HWND handle.
			if(wnd!=NULL)wnd->OnWndCommand(HIWORD(wParam),LOWORD(wParam),(HWND) lParam);
			break;

		case WM_DRAWITEM:
			LPDRAWITEMSTRUCT lpdis;
			lpdis = (LPDRAWITEMSTRUCT) lParam; 
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnDrawItem(lpdis);
			break;

		case WM_MEASUREITEM:             
			lpmis = (LPMEASUREITEMSTRUCT) lParam;  
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnMeasureitem(lpmis);
			break;

		case WM_PAINT:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnPaint((HDC)wParam);
			break;

		case WM_LBUTTONDOWN:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnLButtonDown((int)wParam,LOWORD(lParam),HIWORD(lParam));
			break;
	
		case WM_LBUTTONUP:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnLButtonUp((int)wParam,LOWORD(lParam),HIWORD(lParam));
			break;
	
		case WM_MOUSEMOVE:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnMouseMove((int)wParam,LOWORD(lParam),HIWORD(lParam));
			break;

		case WM_NOTIFY:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnNotify(wParam,lParam);
			break;

		case WM_TIMER:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnTimer((int)wParam);
			break;
		case WM_HELP:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnHelp(lParam);
			break;
		case WM_SETCURSOR:
			wnd=Vtable.FindClass(hwndDlg);
			if(wnd!=NULL)wnd->OnSetCursor();
			break;

		default:
			//return DefDlgProc(hwndDlg,uMsg,wParam,lParam);
			return FALSE;
			break;
	}
	return TRUE;
}

CUCVTable * CUCWnd::GetVTable(){
	return &Vtable;
}


CHOOSECOLOR * CUCWnd::GetChooseColor(){
	return &ColorTable;
}

HINSTANCE CUCWnd::GetInstan(){
	return m_hInstance;
}

void CUCWnd::SetInstan(HINSTANCE Inst){
	m_hInstance=Inst;
}

void CUCWnd::OnEditChange(int /* item */,HWND /* handle */)
{

}

void CUCWnd::OnNotify(WPARAM /* wParam */,LPARAM lParam)
{

	LPPSHNOTIFY Notif;
	switch (((NMHDR FAR *) lParam)->code) 
            {

                case PSN_SETACTIVE:
					OnSetActivePage();
                    break;
                case PSN_APPLY:
					Notif=(LPPSHNOTIFY) lParam;
					if(m_bChanged)OnApply((int)Notif->lParam);
					m_bChanged=FALSE;
                    break;
                case PSN_KILLACTIVE:
				
//					pPage->OnKillActive();
                    break;

                case PSN_RESET:
					
//					pPage->OnReset();
                    break;
                
				case PSN_HELP:
				
//					pPage->OnHelp();
                    break;
                
				case PSN_QUERYCANCEL:
					
//					return pPage->OnQueryCancel();
                    break;

			}
	return;
}

void CUCWnd::OnApply(BOOL)
{

}

void CUCWnd::OnSetActivePage()
{

}
/*
CUCPropertyElement* CUCWnd::GetPropertyElement(){
	return PropertyElement;
}

void CUCWnd::SetPropertyElement(CUCPropertyElement* element){
	PropertyElement=element;
}
*/


void CUCWnd::OnUpdate(int /* item */, HWND /* handle */)
{

}


void CUCWnd::OnTimer(int /* nIdent */)
{

}

void CUCWnd::OnSetCursor()
{

}
