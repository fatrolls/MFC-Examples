// UCVTable.cpp: implementation of the CUCVTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ucvtable.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUCVTable::CUCVTable()
{
	m_SWnd = NULL;
}

CUCVTable::~CUCVTable()
{

}

int CUCVTable::AddItem(CUCWnd *cwnd)
{
	ListWnd *temp;
	temp=new ListWnd;
	temp->WndClass=cwnd;
	temp->Next=m_SWnd;
	m_SWnd=temp;
	
	return 1;
}


CUCWnd * CUCVTable::FindClass(HWND wnd)
{
	ListWnd *temp;
	temp=m_SWnd;
	while(temp){
		if(wnd==temp->WndClass->m_hWnd)return temp->WndClass;
		temp=temp->Next;
	}
	return NULL;
}

int CUCVTable::DeleteClass(CUCWnd *cwnd)
{
	ListWnd *temp,*tempsr;
	temp=m_SWnd;
	if(m_SWnd->WndClass==cwnd){
		m_SWnd=m_SWnd->Next;
		delete temp;
		return 1;
	}
	tempsr=temp;
	while(temp){
		if(cwnd==temp->WndClass){
			tempsr->Next=temp->Next;
			delete temp;
			return 1;
		}
		tempsr=temp;
		temp=temp->Next;
	}
	return 0;
}