// fanView.cpp : implementation of the CFanView class
//

#include "stdafx.h"
#include "fan.h"

#include "fanDoc.h"
#include "fanView.h"
#include "MainFrm.h"
#include "math.h"
#include "MemDC.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define IDC_TIMER 100

static const double PI = 3.141592654;


/////////////////////////////////////////////////////////////////////////////
// CFanView

IMPLEMENT_DYNCREATE(CFanView, CView)

BEGIN_MESSAGE_MAP(CFanView, CView)
	//{{AFX_MSG_MAP(CFanView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_COMMAND(ID_1, On1)
	ON_UPDATE_COMMAND_UI(ID_1, OnUpdate1)
	ON_COMMAND(ID_2, On2)
	ON_UPDATE_COMMAND_UI(ID_2, OnUpdate2)
	ON_COMMAND(ID_3, On3)
	ON_UPDATE_COMMAND_UI(ID_3, OnUpdate3)
	ON_COMMAND(ID_STAR, OnStar)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFanView construction/destruction

CFanView::CFanView()
{
	// TODO: add construction code here

}

CFanView::~CFanView()
{
}

BOOL CFanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFanView drawing

/*void CFanView::OnDraw(CDC* pDC)
{
	CFanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC pcd1,pcd2;
	CBitmap bitmap,bitmap2;
	BITMAP bm,bm2;
	int wide,hight;
	pDC->FillRect(CRect(0,0,50,400),NULL);
	bitmap.LoadBitmap(IDB_BITMAP1);
	bitmap.GetObject(sizeof(bm),&bm);
	bitmap2.LoadBitmap(IDB_BITMAP2);
	bitmap2.GetObject(sizeof(bm2),&bm2);
	wide=bm.bmWidth;
	hight=bm.bmHeight;
	pcd1.CreateCompatibleDC(NULL);
	pcd1.SelectObject(&bitmap);
	pcd2.CreateCompatibleDC(NULL);
	pcd2.SelectObject(&bitmap2);
//	wait.Restore();
	//pDC->Draw3dRect(2,2,200+2,400+2,NULL,NULL);
	if(flag)
	{
		for(int a=0;a<4;a++)
		{
				cor[aa[a].x][aa[a].y]=1;
		}
	}
	for(int x=0;x<20;x++)
	{
		for(int j=0;j<10;j++)
		{
			if(j==0)
			{
				pDC->BitBlt(100+0,x*20,wide,hight,&pcd2,0,0,SRCCOPY);
			}
			if(j==9)
			{
				pDC->BitBlt(100+220,x*20,wide,hight,&pcd2,0,0,SRCCOPY);
			}
			if(x==19)
			{
				pDC->BitBlt(100+j*20,x*20+20,wide,hight,&pcd2,0,0,SRCCOPY);
			}
			if((cor[x][j]==1)||(cor[x][j]==2))
			{
		//	m_pbmpContents->GetBitmapBits(
				pDC->BitBlt(100+20+j*20,x*20,wide,hight,&pcd1,0,0,SRCCOPY);
			}
		}
		if(x==19)
		{
			pDC->BitBlt(100+200,400,wide,hight,&pcd2,0,0,SRCCOPY);
			//wait.Restore();

			pDC->BitBlt(100+220,400,wide,hight,&pcd2,0,0,SRCCOPY);
			//wait.Restore();

		}
	}



	//bitmap[k].DeleteObject();

}*/

/////////////////////////////////////////////////////////////////////////////
// CFanView printing

BOOL CFanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFanView diagnostics

#ifdef _DEBUG
void CFanView::AssertValid() const
{
	CView::AssertValid();
}

void CFanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFanDoc* CFanView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFanDoc)));
	return (CFanDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFanView message handlers

int CFanView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	flag2=0;
/*		m_nMaxX=GetSystemMetrics(SM_CXSCREEN);
		m_nMaxY=GetSystemMetrics(SM_CYSCREEN);
		HDC hdc=::GetDC(m_hWnd);
		m_memdc=::CreateCompatibleDC(hdc);
		m_hBit=CreateCompatibleBitmap(hdc,m_nMaxX,m_nMaxY);
		SelectObject(m_memdc,m_hBit);
		m_hBrush=(HBRUSH)GetStockObject(WHITE_BRUSH);
		SelectObject(m_memdc,m_hBrush);
		PatBlt(m_memdc,0,0,m_nMaxX,m_nMaxY,PATCOPY);*/
	k=0;
	time=500;
	K=0;
	Y=0;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<11;j++)
		{
			cor[i][j]=0;
		}
	}
	count=0;
	R=0;
	L=0;
	H=0;
	index=0;
	flag=0;
	Star();
	SetTimer(IDC_TIMER,time,NULL);

	return 0;
}

void CFanView::OnTimer(UINT nIDEvent) 
{
	Y=1;
	if(K)
	{
	if(Isbottom())
	{
			flag=1;
			clean(0);
			R=R+2;
			for(int a=0;a<4;a++)
			{
				aa[a].x++;
			}
		//	clean(1);
		//	Invalidate();
		//	OnPaint();
				myDraw();
		}
		else if(K)
		{
			Isover();
			Star();
			flag=1;
		}
	}
	Y=0;
	CView::OnTimer(nIDEvent);
}


void CFanView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

		CView::OnChar(nChar, nRepCnt, nFlags);
}



void CFanView::clean(int b)
{
	for(int a=0;a<4;a++)
	{
			cor[aa[a].x][aa[a].y]=0;
			dd[a].x=aa[a].x;
			dd[a].y=aa[a].y;
	}
		
}

int CFanView::round(int as)
{
	int tempx=0,tempy=0,a,d=0,h=0;
	int temp2=0,temp1=0;
	for(a=0;a<4;a++)
	{
		bb[a].x=aa[a].x;
		bb[a].y=aa[a].y;
	}
	if(index==1)
	{
		temp1=aa[2].x;
		temp2=aa[2].y;
		h=2;

	}
	else
	{
		temp1=aa[1].x;
		temp2=aa[1].y;
		h=1;
	}
	for(a=0;a<4;a++)
	{
		if(a!=h)
		{
			tempx=(aa[a].x-temp1);
			tempy=(aa[a].y-temp2);
			aa[a].x=tempy+temp1;
			aa[a].y=-tempx+temp2;
			if((cor[aa[a].x][aa[a].y]==2)||(aa[a].y>9)||(aa[a].y<0)||(aa[a].x>19)||(aa[a].x<0))
			{
				for(int d=0;d<4;d++)
				{
					aa[d].x=bb[d].x;
					aa[d].y=bb[d].y;
				}
				return 0;
			}
		}
	}
	return 1;
	//aa[a].x=tempx*temp1+tempy*temp2+aa[1].x;
	//		aa[a].y=tempy*temp1-tempx*temp2+aa[1].y;
}

int CFanView::Isout(int w)
{
	if(w==2)
	{
		for(int a=0;a<4;a++)
		{
			if((aa[a].y>=9)||(cor[aa[a].x][aa[a].y+1]==2))
			{
				return 1;
			}
		}
	}
	if(w==1)
	{
		for(int a=0;a<4;a++)
		{
			if((aa[a].y<=0)||(cor[aa[a].x][aa[a].y-1]==2))
			{
				return 2;
			}
		}

	}
	return 3;

}

int CFanView::Isbottom()
{
   for(int a=0;a<4;a++)
   {
      if(aa[a].x==19)
      {
         for(int c=0;c<4;c++)
         {
            cor[aa[c].x][aa[c].y]=2;
            color[aa[c].x][aa[c].y]=tempcolor;
            flag2=1;
         }
         k=0;
         return 0;
      }
      if(cor[aa[a].x+1][aa[a].y]==2)
      {
         for(int c=0;c<4;c++)
         {
            cor[aa[c].x][aa[c].y]=2;
            color[aa[c].x][aa[c].y]=tempcolor;
            flag2=1;
         }
         k=0;
         return 0;
      }

   }
   return 1;


}

int CFanView::dop()
{
	for(int u=0;u<20;u++)
	{
	
		for(int a=0;a<4;a++)
		{
			if(cor[aa[a].x+1][aa[a].y]==2)
			{
				for(int c=0;c<4;c++)
				{
						cor[aa[c].x][aa[c].y]=2;
						color[aa[c].x][aa[c].y]=tempcolor;
						flag2=1;
				}
			//	flag=1;
				return 0;
			}
		}
		for(int a=0;a<4;a++)
		{
			if(aa[a].x==19)
			{
				for(int c=0;c<4;c++)
				{
					cor[aa[c].x][aa[c].y]=2;
					color[aa[c].x][aa[c].y]=tempcolor;
				flag2=1;
				}
		//	flag=1;
			return 0;
			}
		}
		for(int o=0;o<4;o++)
		{
			aa[o].x=aa[o].x+1;
		}
	}
	return 1;

}

void CFanView::Isover()
{
	int flagover=0,n=0;
	for(int a=19;a>=0;a--)
	{
		flagover=0;
		for(int b=0;b<10;b++)
		{
			if(cor[a][b]==2)
			{
				flagover++;
			}
		}
		if(flagover==10)
		{
			count=count+100;
			for(int b=0;b<10;b++)
			{
					cor[a][b]=0;
					color[a][b]=RGB(255,255,255);
			}
			for(int t=a;t>0;t--)
			{

            for(int b=0;b<10;b++)
				{
					if(cor[t-1][b]==2)
					{
						cor[t][b]=2;
						color[t][b]=color[t-1][b];
						flag2=1;
						cor[t-1][b]=0;
						color[t-1][b]=RGB(255,255,255);
					}
				}
			}
			a=a+1;
		}
	}
	for(int a=0;a<9;a++)
	{
		if(cor[0][a]==2)
		{
			KillTimer(IDC_TIMER);
			MessageBox("游戏结束");
		//	clean(1);
			count=0;
			for(int i=0;i<20;i++)
			{
				for(int j=0;j<10;j++)
				{
					cor[i][j]=0;
					flag2=1;
				}
			}
			SetTimer(IDC_TIMER,time,NULL);

		}
	}
	CMainFrame * frame=(CMainFrame *)AfxGetMainWnd();
	UINT nID,nStyle;
	int cxwidth;
	frame->m_wndStatusBar.GetPaneInfo(0,nID,nStyle,cxwidth);
	frame->m_wndStatusBar.SetPaneInfo(0,nID,SBPS_STRETCH|SBPS_NORMAL,cxwidth);
	CString cs;
	cs.Format("得分=%d",count);
	frame->m_wndStatusBar.SetPaneText(0,cs);
}

void CFanView::Star()
{
	for(int i=0;i<4;i++)
	{
		aa[i].x=0;
		aa[i].y=0;
	}
//	KillTimer(IDC_TIMER);
//	SetTimer(IDC_TIMER,time,NULL);
	R=0;
	H=5;
	index=rand()%7;
	switch(index)
	{
		case 1:
				aa[0].x=R;
				aa[0].y=H;
				aa[1].x=R;
				aa[1].y=H+1;
				aa[2].x=R;
				aa[2].y=H-1;
				aa[3].x=R;
				aa[3].y=H-2;
				tempcolor=RGB(80,154,175);
				
				/*//cor[R][H]=1;//----//
				cor[R][H+1]=1;
				cor[R][H-1]=1;
				cor[R][H-2]=1;*/
				break;
		case 2:
				aa[0].x=R;
				aa[0].y=H;
				aa[1].x=R;
				aa[1].y=H+1;
				aa[2].x=R+1;
				aa[2].y=H+1;
				aa[3].x=R+1;
				aa[3].y=H+2;
				tempcolor=RGB(43,213,140);
				
			/*	cor[R][H]=1;
				cor[R][H+1]=1;	//|_
				cor[R+1][H+1]=1;//  |
				cor[R+1][H+2]=1;*/
				break;
		case 3:
				aa[0].x=R;
				aa[0].y=H;
				aa[1].x=R;
				aa[1].y=H+1;
				aa[2].x=R-1;
				aa[2].y=H+1;
				aa[3].x=R-1;
				aa[3].y=H+2;
				tempcolor=RGB(233,149,22);
				/*cor[R][H]=1;		//	_|
				cor[R+1][H]=1;	//     |
				cor[R+1][H-1]=1;
				cor[R+2][H-1]=1;*/
				break;
		case 4:
				aa[0].x=R;
				aa[0].y=H;
				aa[1].x=R;
				aa[1].y=H+1;
				aa[2].x=R;
				aa[2].y=H+2;
				aa[3].x=R+1;
				aa[3].y=H+2;
				tempcolor=RGB(210,23,191);
				/*cor[R][H]=1;	//|
				cor[R+1][H]=1;//  |
				cor[R+2][H]=1;//  |__
				cor[R+2][H+1]=1;*/
				break;
		case 5:
				aa[0].x=R;
				aa[0].y=H;
				aa[1].x=R;
				aa[1].y=H+1;
				aa[2].x=R;
				aa[2].y=H+2;
				aa[3].x=R-1;
				aa[3].y=H+2;
				tempcolor=RGB(9,24,225);
				/*cor[R][H]=1;	//|
				cor[R+1][H]=1;//  |
				cor[R+2][H]=1;//__|
				cor[R+2][H-1]=1;*/
				break;
		case 6:
				aa[0].x=R;
				aa[0].y=H;
				aa[1].x=R+1;
				aa[1].y=H;
				aa[2].x=R+1;
				aa[2].y=H+1;
				aa[3].x=R+1;
				aa[3].y=H-1;
				tempcolor=RGB(5,228,211);
				/*cor[R][H]=1;//  |
				cor[R+1][H]=1;// _|_
				cor[R+1][H+1]=1;// 
				cor[R+1][H-1]=1;*/
				break;
		case 0:
				aa[0].x=R;
				aa[0].y=H;
				aa[1].x=R;
				aa[1].y=H+1;
				aa[2].x=R+1;
				aa[2].y=H;
				aa[3].x=R+1;
				aa[3].y=H+1;
				tempcolor=RGB(77,68,70);
				/*cor[R][H]=1;	//|----|
				cor[R][H+1]=1;//  |____|
				cor[R+1][H]=1;//  
				cor[R+1][H+1]=1;*/
				break;


	}	
	myDraw();
//	Invalidate();
//	OnPaint();
		K=1;
}

void CFanView::On1() 
{
	time=1000;
}

void CFanView::OnUpdate1(CCmdUI* pCmdUI) 
{
	if(time==1000)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	
}

void CFanView::On2() 
{
	time=300;
	
}

void CFanView::OnUpdate2(CCmdUI* pCmdUI) 
{
	if(time==300)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	
}

void CFanView::On3() 
{
	time=60;	
}

void CFanView::OnUpdate3(CCmdUI* pCmdUI) 
{
	if(time==60)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	

	
}

void CFanView::OnStar() 
{
	Star();	
}

void CFanView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(!Y)
	{
		K=0;
		switch(nChar)
		{
			case VK_LEFT:
			case VK_NUMPAD4:
						if(!(Isout(1)==2))
						{
							flag=1;
							clean(0);
							H--;
							for(int a=0;a<4;a++)
							{
										aa[a].y--;
							}
						//	Invalidate();
						}
						break;

			case VK_RIGHT:
			case VK_NUMPAD6:	
						if(!(Isout(2)==1))
						{
								flag=1;
								clean(0);
								H++;
								for(int a=0;a<4;a++)
								{
									aa[a].y++;
								}
							//	Invalidate();
						}
								break;
		
			case VK_DOWN:
			case VK_NUMPAD2:
//					KillTimer(IDC_TIMER);
						clean(0);
						dop();
						Isover();
						Star();
						break;
			case VK_UP:
			case VK_NUMPAD8:
			case VK_NUMPAD5:
					clean(0);
					k++;
					round(k);
				//	Invalidate();
					break;
						

		}
			K=1;				
	}
	myDraw();
//	OnPaint();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFanView::OnPaint() 
{
	

	CPaintDC pdc(this); // device context for painting
	
	//	ShowWindow(SW_HIDE);
	
	COLORREF clrTopLeft = RGB(68, 71, 140);
	COLORREF clrBottomRight = RGB(70, 166,152);
	COLORREF clrTopLeft2 = ::GetSysColor(COLOR_BTNHILIGHT);
	COLORREF clrBottomRight2 = ::GetSysColor(COLOR_BTNSHADOW);
	CRect rect;
	CMemDC dc(&pdc);


	register const UINT wide =20;
	register const UINT hight = 20;

	// paint the board itself
	
	if(flag)
	{
		for(int a=0;a<4;a++)
		{
				cor[aa[a].x][aa[a].y]=1;
		}
		for(int x=0;x<20;x++)
		{
			for(int j=0;j<10;j++)
			{
				if(cor[x][j]==1)
				{
				dc.FillSolidRect(100+20+j*20,x*20,wide,hight,clrTopLeft);
				dc.Draw3dRect(100+20+j*20,x*20,wide,hight,clrTopLeft, clrBottomRight);
				}
			}
		}

	}

	for(int x=0;x<20;x++)
	{
		for(int j=0;j<10;j++)
		{
				dc.FillSolidRect(100+20+j*20,x*20,wide,hight,clrTopLeft2);
				dc.Draw3dRect(100+20+j*20,x*20,wide,hight,clrTopLeft, clrTopLeft2);
		}
	}
	for(int x=0;x<20;x++)
	{
		for(int j=0;j<10;j++)
		{
			if((cor[x][j]==1)||(cor[x][j]==2))
			{
				dc.FillSolidRect(100+20+j*20,x*20,wide,hight,clrTopLeft);
				dc.Draw3dRect(100+20+j*20,x*20,wide,hight,clrTopLeft, clrBottomRight);
			}
		}
	}


/*		if(x==19)
		{
			pDC->BitBlt(100+200,400,wide,hight,&pcd2,0,0,SRCCOPY);
			//wait.Restore();

			pDC->BitBlt(100+220,400,wide,hight,&pcd2,0,0,SRCCOPY);
			//wait.Restore();

		}
	}
		

				dc.FillSolidRect(j*m_nSquareWidth, i*m_nSquareHeight, m_nSquareWidth, m_nSquareHeight, m_Board[i][j]);
				dc.Draw3dRect(j*m_nSquareWidth, i*m_nSquareHeight, m_nSquareWidth, m_nSquareHeight, clrTopLeft, clrBottomRight);
			}
		}
		
	// now paint the current piece ...
	if( m_pCurPiece != 0 ) {
		register const int nLines = m_pCurPiece->GetLines();
		register const int nCols  = m_pCurPiece->GetColumns();

		for( register int l = nLines-1 ; l >= 0 ; --l )
			for( register int c = 0 ; c < nCols ; ++c ) {
				int nL = m_nCurLine - ((nLines-1) & l);
				int nC = m_nCurCol + c;
				if( nL >= 0 && nL < Height() &&
					nC >= 0 && nC < Width() )
					if( m_pCurPiece->IsSquare(l, c) ) {
						dc.FillSolidRect(nC*m_nSquareWidth, nL*m_nSquareHeight, m_nSquareWidth, m_nSquareHeight, m_clrCurPiece);
						dc.Draw3dRect(nC*m_nSquareWidth, nL*m_nSquareHeight, m_nSquareWidth, m_nSquareHeight, clrTopLeft, clrBottomRight);
					}
			}
	}

	// draw the grid
	if( m_bShowGrid ) {
		// draw vertical lines
		for( register h = m_nSquareWidth; h < rect.Width(); h += m_nSquareWidth ) {
			dc.MoveTo(h, 0);
			dc.LineTo(h, rect.bottom);
		}

		// draw horizontal lines
		for( register v = m_nSquareHeight; v < rect.Height(); v += m_nSquareHeight ) {
			dc.MoveTo(0, v);
			dc.LineTo(rect.right, v);
		}*/
	//ShowWindow(SW_SHOW);
}


void CFanView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CFanView::myDraw()
{
	CDC* dc=GetDC();
	COLORREF clrTopLeft = RGB(68, 71, 140);
	COLORREF clrBottomRight = RGB(70, 166,152);
	COLORREF clrTopLeft2 = ::GetSysColor(COLOR_BTNHILIGHT);
	COLORREF clrBottomRight2 = ::GetSysColor(COLOR_BTNSHADOW);
	
	register const UINT wide =20;
	register const UINT hight = 20;

	// paint the board itself
		for(int a=0;a<4;a++)
		{
				dc->FillSolidRect(100+20+dd[a].y*20,dd[a].x*20,wide,hight,clrTopLeft2);
				dc->Draw3dRect(100+20+dd[a].y*20,dd[a].x*20,wide,hight,clrTopLeft2, clrBottomRight2);
				dc->FillSolidRect(100+20+dd[a].y*20,dd[a].x*20,wide,hight,clrTopLeft2);
				dc->Draw3dRect(100+20+dd[a].y*20,dd[a].x*20,wide,hight,clrTopLeft, clrTopLeft2);
		}

	if(flag)
	{
		for(int a=0;a<4;a++)
		{
				cor[aa[a].x][aa[a].y]=1;
		}
		for(int x=0;x<20;x++)
		{
			for(int j=0;j<10;j++)
			{
				if(cor[x][j]==1)
				{
				dc->FillSolidRect(100+20+j*20,x*20,wide,hight,tempcolor);
				dc->Draw3dRect(100+20+j*20,x*20,wide,hight,clrTopLeft, tempcolor);
				}
			}
		}

	}
	if(flag2)
	{
			for(int x=0;x<20;x++)
			{
				for(int j=0;j<10;j++)
				{
						dc->FillSolidRect(100+20+j*20,x*20,wide,hight,clrTopLeft2);
						dc->Draw3dRect(100+20+j*20,x*20,wide,hight,clrTopLeft, clrTopLeft2);
				}
			}
			for(int x=0;x<20;x++)
			{
				for(int j=0;j<10;j++)
				{
					if((cor[x][j]==1)||(cor[x][j]==2))
					{
						dc->FillSolidRect(100+20+j*20,x*20,wide,hight,color[x][j]);
						dc->Draw3dRect(100+20+j*20,x*20,wide,hight,clrTopLeft, color[x][j]);
					}
				}
			}
			flag2=0;
	}


}

void CFanView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
//	KillTimer(IDC_TIMER);
	// TODO: Add your message handler code here
	
}

void CFanView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
//	SetTimer(IDC_TIMER,time,NULL);	
}
