// DNSPage.cpp: implementation of the CDNSPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DNSPage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDNSPage::CDNSPage()
{

}

CDNSPage::~CDNSPage()
{

}
void CDNSPage::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	
}

void CDNSPage::OnPaint(HDC dc)
{
	PAINTSTRUCT lpPaint;
	BeginPaint(m_hWnd,&lpPaint);
	SelectedType();
	EndPaint(m_hWnd,&lpPaint);
	
}

void CDNSPage::OnLButtonDown(int key, int px, int py)
{
	
}
