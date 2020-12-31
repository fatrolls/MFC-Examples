//透明滑动控件的实现，只要声明控件是CmySliderControl的对象即可，如CmySliderControl m_Slider
//二〇〇九年十一月二十七日 非原创
// mySliderControl.cpp : 实现文件
//

#include "stdafx.h" 
#include "Player.h" 
#include "mySliderControl.h" 


// CmySliderControl

//IMPLEMENT_DYNAMIC(CmySliderControl, CSliderCtrl)

CmySliderControl :: CmySliderControl()
{
    m_dcBk.m_hDC=NULL ;
}

CmySliderControl ::~CmySliderControl()
{
    DeleteObject(m_dcBk.SelectObject(&m_bmpBkOld));
    DeleteDC(m_dcBk);
}

BEGIN_MESSAGE_MAP(CmySliderControl,CSliderCtrl)
//{{AFX_MSG_MAP(CMySliderControl)
ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnCustomDraw)
ON_WM_ERASEBKGND()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CmySliderControl :: OnCustomDraw(NMHDR*pNMHDR,LRESULT*pResult)
{
    LPNMCUSTOMDRAW lpcd=(LPNMCUSTOMDRAW)pNMHDR ;
    CDC*pDC=CDC :: FromHandle(lpcd->hdc);
    switch(lpcd->dwDrawStage)
    {
        case CDDS_PREPAINT :
        *pResult=CDRF_NOTIFYITEMDRAW ;
        break ;
        //return;
        case CDDS_ITEMPREPAINT :
        if(lpcd->dwItemSpec==TBCD_THUMB)
        {
            *pResult=CDRF_DODEFAULT ;
            break ;
        }
        if(lpcd->dwItemSpec==TBCD_CHANNEL)
        {
            CClientDC clientDC(GetParent());
            CRect crect ;
            CRect wrect ;
            GetClientRect(crect);
            GetWindowRect(wrect);
            GetParent()->ScreenToClient(wrect);
            if(m_dcBk.m_hDC==NULL)
            {
                m_dcBk.CreateCompatibleDC(&clientDC);
                m_bmpBk.CreateCompatibleBitmap(&clientDC,crect.Width(),crect.Height());
                m_bmpBkOld=m_dcBk.SelectObject(&m_bmpBk);
                m_dcBk.BitBlt(0,0,crect.Width(),crect.Height(),&clientDC,wrect.left,wrect.top,SRCCOPY);
            }
            //This bit does the tics marks transparently.
            CDC SaveCDC ;
            CBitmap SaveCBmp,maskBitmap ;
            //set the colours for the monochrome mask bitmap
            COLORREF crOldBack=pDC->SetBkColor(RGB(0,0,0));
            COLORREF crOldText=pDC->SetTextColor(RGB(255,255,255));
            CDC maskDC ;
            int iWidth=crect.Width();
            int iHeight=crect.Height();
            SaveCDC.CreateCompatibleDC(pDC);
            SaveCBmp.CreateCompatibleBitmap(&SaveCDC,iWidth,iHeight);
            CBitmap*SaveCBmpOld=(CBitmap*)SaveCDC.SelectObject(SaveCBmp);
            //fill in the memory dc for the mask
            maskDC.CreateCompatibleDC(&SaveCDC);
            //create a monochrome bitmap
            maskBitmap.CreateBitmap(iWidth,iHeight,1,1,NULL);
            //select the mask bitmap into the dc
            CBitmap*OldmaskBitmap=maskDC.SelectObject(&maskBitmap);
            //copy the oldbitmap data into the bitmap, this includes the tics.
            SaveCDC.BitBlt(0,0,iWidth,iHeight,pDC,crect.left,crect.top,SRCCOPY);
            //now copy the background into the slider
            BitBlt(lpcd->hdc,0,0,iWidth,iHeight,m_dcBk.m_hDC,0,0,SRCCOPY);
            // Blit the mask based on background colour
            maskDC.BitBlt(0,0,iWidth,iHeight,&SaveCDC,0,0,SRCCOPY);
            // Blit the image using the mask
            pDC->BitBlt(0,0,iWidth,iHeight,&SaveCDC,0,0,SRCINVERT);
            pDC->BitBlt(0,0,iWidth,iHeight,&maskDC,0,0,SRCAND);
            pDC->BitBlt(0,0,iWidth,iHeight,&SaveCDC,0,0,SRCINVERT);
            //restore and clean up
            pDC->SetBkColor(crOldBack);
            pDC->SetTextColor(crOldText);
            DeleteObject(SelectObject(SaveCDC,SaveCBmpOld));
            DeleteDC(SaveCDC);
            DeleteObject(maskDC.SelectObject(OldmaskBitmap));
            DeleteDC(maskDC);
            *pResult=0 ;
            break ;
        }
    }
}

BOOL CmySliderControl :: OnEraseBkgnd(CDC*pDC)
{
    return FALSE ;
}