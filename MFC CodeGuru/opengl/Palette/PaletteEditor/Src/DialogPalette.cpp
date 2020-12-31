// DialogPalette.cpp : implementation file
#include "stdafx.h"
#include "Palette.h"
#include "DialogPalette.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogPalette dialog


CDialogPalette::CDialogPalette(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPalette::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPalette)
	m_StringBlue = _T("");
	m_StringGreen = _T("");
	m_StringRed = _T("");
	//}}AFX_DATA_INIT

	// Init nodes and default ramp
	Init();

	// Init geometry
	m_Width = 20;
	m_Height = 20;
	m_Space = 2;

	// Init selection
	m_Selected=0;

}




//**************************************************
// Init
// Default : grey scale
//**************************************************
void CDialogPalette::Init()
{
	for(int i=0;i <256;i++)
		{
		m_Red[i]    = i;
		m_Green[i]  = i;
		m_Blue[i]   = i;
		m_IsNode[i] = 0;
		}
	// Nodes 0 & 255 selected
	m_IsNode[0] = 1;
	m_IsNode[255] = 1;

}

void CDialogPalette::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPalette)
	DDX_Text(pDX, IDC_EDIT_BLUE, m_StringBlue);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_StringGreen);
	DDX_Text(pDX, IDC_EDIT_RED, m_StringRed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPalette, CDialog)
	//{{AFX_MSG_MAP(CDialogPalette)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL, OnButtonDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPalette message handlers

BOOL CDialogPalette::OnInitDialog() 
{
  CDialog::OnInitDialog();
	
  // Bitmap and drawing...
  // MemDC and Bitmap
  CSize SizeImage(16*(m_Width+m_Space),16*(m_Height+m_Space)+30);
  CWindowDC dc(this);
  int NbPlane = dc.GetDeviceCaps(PLANES);
  int NbBit = dc.GetDeviceCaps(BITSPIXEL);
  m_MemDC.CreateCompatibleDC(&dc);//int nWidth, int nHeight, UINT nPlanes, UINT nBitcount, const void* lpBits );
  m_Bitmap.CreateBitmap(SizeImage.cx,SizeImage.cy,NbPlane,NbBit,NULL);
  m_MemDC.SelectObject(&m_Bitmap);
  m_MemDC.SetMapMode(MM_TEXT);
  CBrush brush;
  brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
  CPen pen(PS_SOLID,1,::GetSysColor(COLOR_3DFACE));
  m_MemDC.SelectObject(&pen);
  m_MemDC.SelectObject(&brush);
  m_MemDC.Rectangle(0,0,SizeImage.cx,SizeImage.cy);
	this->DrawPalette();	
  m_Oldi = 0;
  m_Oldj = 0;

	SetDlgItemInt(IDC_EDIT_RED,m_Red[0]);
	SetDlgItemInt(IDC_EDIT_GREEN,m_Green[0]);
	SetDlgItemInt(IDC_EDIT_BLUE,m_Blue[0]);

	// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_ADD), "Ramps are calculated from node to node");
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_DELETE), "Delete selected node");
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_DELETE_ALL), "Delete every node between first and last");
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_SELECTED), "Entry selected in the ramp");
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_RED), "Red");
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_GREEN), "Green");
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_BLUE), "Blue");

	return TRUE;  
}

//********************************************
// MakePalette
//********************************************
void CDialogPalette::MakePalette() 
{
 int j;
 m_ArrayNode.RemoveAll();
 for(int i=0;i<=255;i++)
   {
   if(m_IsNode[i]==TRUE)
     m_ArrayNode.Add(i);
   }
 
 int size = m_ArrayNode.GetSize();
 TRACE("%d nodes\n",size);
 int x1,y1,x2,y2,b;
 float a;
 for(i=0;i<size-1;i++)
   {
    x1=m_ArrayNode[i];
    x2=m_ArrayNode[i+1];
    VERIFY(x1<x2);
    y1=m_Red[x1];
    y2=m_Red[x2];
    a = (float)(y2-y1)/(float)(x2-x1);
    b = y1 - (int)(a*(float)x1);
    for(j=x1;j<x2;j++)
      m_Red[j]=(BYTE)(a*(float)j+b);
   }
 for(i=0;i<size-1;i++)
   {
    x1=m_ArrayNode[i];
    x2=m_ArrayNode[i+1];
    VERIFY(x1<x2);
    y1=m_Green[x1];
    y2=m_Green[x2];
    a = (float)(y2-y1)/(float)(x2-x1);
    b = y1 - (int)(a*(float)x1);
    for(j=x1;j<x2;j++)
      m_Green[j]=(BYTE)(a*(float)j+b);
   }
 for(i=0;i<size-1;i++)
   {
    x1=m_ArrayNode[i];
    x2=m_ArrayNode[i+1];
    VERIFY(x1<x2);
    y1=m_Blue[x1];
    y2=m_Blue[x2];
    a = (float)(y2-y1)/(float)(x2-x1);
    b = y1 - (int)(a*(float)x1);
    for(j=x1;j<x2;j++)
      m_Blue[j]=(BYTE)(a*(float)j+b);
   }
}

//********************************************
// DrawItem
//********************************************
void CDialogPalette::DrawItem(CDC *pDC,
                              COLORREF LineColor,
                              COLORREF FillColor,
                              CRect &rect) 
{
	CBrush brush;
  brush.CreateSolidBrush(FillColor);
	CPen pen(PS_SOLID,1,LineColor);
  CPen *pOldPen = m_MemDC.SelectObject(&pen);
  CBrush *pOldBrush = m_MemDC.SelectObject(&brush);
  pDC->RoundRect(rect.left,rect.top,rect.right+1,rect.bottom+1,0,0);
  m_MemDC.SelectObject(pOldBrush);      
  m_MemDC.SelectObject(pOldPen);
}

//********************************************
// DrawPalette
//********************************************
void CDialogPalette::DrawPalette() 
{
  CRect rect;
  CRect item;
  int i,j;
  for(j=0;j<16;j++)
    for(i=0;i<16;i++)
     {
      item.SetRect(i*(m_Width+m_Space),j*(m_Width+m_Space),
                   i*(m_Width+m_Space)+m_Width,j*(m_Width+m_Space)+m_Height);

      // Selected item
      if(m_IsNode[j*16+i]==TRUE)
        { 
         rect.SetRect(item.left,item.top,item.right,item.bottom);
         this->DrawItem(&m_MemDC,RGB(255,0,0),RGB(0,0,0),rect);
        }
	  else
        { 
         rect.SetRect(item.left,item.top,item.right,item.bottom);
         this->DrawItem(&m_MemDC,::GetSysColor(COLOR_3DFACE),RGB(0,0,0),rect);
        }
      if(m_Selected == (j*16+i))
        {
         rect.SetRect(item.left+1,item.top+1,item.right-1,item.bottom-1);
         this->DrawItem(&m_MemDC,RGB(255,255,255),RGB(m_Red[j*16+i],m_Green[j*16+i],m_Blue[j*16+i]),rect);
        }
      else
        {
         rect.SetRect(item.left+1,item.top+1,item.right-1,item.bottom-1);
         this->DrawItem(&m_MemDC,::GetSysColor(COLOR_3DFACE),RGB(m_Red[j*16+i],m_Green[j*16+i],m_Blue[j*16+i]),rect);
        }
      
     }

int left = 0;
int top = 16*(m_Height+m_Space)+10;
for(i=0;i<256;i++)
   this->DrawLine(&m_MemDC,left+i,top,left+i,top+20,RGB(m_Red[i],m_Green[i],m_Blue[i]));


}

//********************************************
// DrawPalette
//********************************************
void CDialogPalette::DrawPaletteItem(int i,int j) 
{
  CRect rect;
  CRect item;
  item.SetRect(i*(m_Width+m_Space),j*(m_Width+m_Space),
               i*(m_Width+m_Space)+m_Width,j*(m_Width+m_Space)+m_Height);

  // Selected item
  if(m_IsNode[j*16+i]==TRUE)
    { 
     rect.SetRect(item.left,item.top,item.right,item.bottom);
     this->DrawItem(&m_MemDC,RGB(255,0,0),RGB(0,0,0),rect);
    }
	else
    { 
     rect.SetRect(item.left,item.top,item.right,item.bottom);
     this->DrawItem(&m_MemDC,::GetSysColor(COLOR_3DFACE),RGB(0,0,0),rect);
    }
  if(m_Selected == (j*16+i))
    {
     rect.SetRect(item.left+1,item.top+1,item.right-1,item.bottom-1);
     this->DrawItem(&m_MemDC,RGB(255,255,255),RGB(m_Red[j*16+i],m_Green[j*16+i],m_Blue[j*16+i]),rect);
    }
  else
    {
     rect.SetRect(item.left+1,item.top+1,item.right-1,item.bottom-1);
     this->DrawItem(&m_MemDC,::GetSysColor(COLOR_3DFACE),RGB(m_Red[j*16+i],m_Green[j*16+i],m_Blue[j*16+i]),rect);
    }
      
}



void CDialogPalette::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(10,10,16*(m_Width+m_Space),16*(m_Height+m_Space)+30,&m_MemDC,0,0,SRCCOPY);

}

void CDialogPalette::OnClose() 
{
 m_MemDC.DeleteDC();
 m_Bitmap.DeleteObject();
 CDialog::OnClose();
}

void CDialogPalette::OnMouseMove(UINT nFlags, CPoint point) 
{
 CDialog::OnMouseMove(nFlags, point);
}

void CDialogPalette::OnLButtonDown(UINT nFlags, CPoint point) 
{
 CRect rect;
 int i,j;
 for(j=0;j<16;j++)
   for(i=0;i<16;i++)
   {
    rect.SetRect(10+i*(m_Width+m_Space),10+j*(m_Width+m_Space),
                 10+i*(m_Width+m_Space)+m_Width,10+j*(m_Height+m_Space)+m_Height);
    if(rect.PtInRect(point))
      {
      m_Selected = j*16+i;
      this->DrawPaletteItem(m_Oldi,m_Oldj);
      this->DrawPaletteItem(i,j);
      CRect rect(10,10,10+16*(m_Width+m_Space)+m_Width,10+16*(m_Height+m_Space)+m_Width+30);
      RedrawWindow(rect,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE ); 
      SetDlgItemInt(IDC_EDIT_SELECTED,m_Selected);
      SetDlgItemInt(IDC_EDIT_RED,m_Red[m_Selected]);
      SetDlgItemInt(IDC_EDIT_GREEN,m_Green[m_Selected]);
      SetDlgItemInt(IDC_EDIT_BLUE,m_Blue[m_Selected]);
      m_Oldi = i;
      m_Oldj = j;
      }
   }


  CDialog::OnLButtonDown(nFlags, point);
}


//**************************************************
// OnButtonChange
//**************************************************
void CDialogPalette::OnButtonChange() 
{
 CColorDialog dlg;
 if(dlg.DoModal()==IDOK)
   {
   COLORREF color = dlg.GetColor();
   SetDlgItemInt(IDC_EDIT_RED,GetRValue(color));
   SetDlgItemInt(IDC_EDIT_GREEN,GetGValue(color));
   SetDlgItemInt(IDC_EDIT_BLUE,GetBValue(color));
   m_Red[m_Selected] = GetRValue(color);
   m_Green[m_Selected] = GetGValue(color);
   m_Blue[m_Selected] = GetBValue(color);
   if(m_IsNode[m_Selected]==TRUE)
     this->MakePalette();
   this->DrawPalette();
   RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE ); 
   }
}

void CDialogPalette::OnButtonAdd() 
{
m_IsNode[m_Selected]=TRUE;
this->MakePalette();
this->DrawPalette();
CRect rect(10,10,10+16*(m_Width+m_Space)+m_Width,10+16*(m_Height+m_Space)+m_Width+30);
RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE ); 
}

//**************************************************
// OnButtonDelete
//**************************************************
void CDialogPalette::OnButtonDelete() 
{
	if(m_Selected == 0 || m_Selected == 255)
		return; 
	m_IsNode[m_Selected]=FALSE;
	MakePalette();
	DrawPalette();
	RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE ); 
}


//*********************************************************
//  DrawLine
//*********************************************************
void CDialogPalette::DrawLine(CDC *pDC,
                           int x1,
                           int y1,
                           int x2,
                           int y2,
                           COLORREF color /* = RGB(0,0,0) */,
                           int PenStyle   /* = PS_SOLID     */)
{
 if(!pDC)
   return;
 CPen pen(PenStyle,1,color);
 CPen *pOldPen; 
 pOldPen = pDC->SelectObject(&pen);
 int OldBkMode = pDC->SetBkMode(TRANSPARENT);
 pDC->MoveTo(x1,y1);
 pDC->LineTo(x2,y2);
 pDC->SelectObject(pOldPen);
 pDC->SetBkMode(OldBkMode);
}


//**************************************************
// OnButtonDeleteAll
//**************************************************
void CDialogPalette::OnButtonDeleteAll() 
{
	int i;
	for(i=1;i<=254;i++)
		m_IsNode[i]=FALSE;
	MakePalette();
	DrawPalette();
	RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE ); 
}

BOOL CDialogPalette::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);

		return CDialog::PreTranslateMessage(pMsg);
	}
}

//**************************************************
// OnOK
//**************************************************
void CDialogPalette::OnOK() 
{
	m_MemDC.DeleteDC();
	m_Bitmap.DeleteObject();

	CDialog::OnOK();
}

void CDialogPalette::OnCancel() 
{
	m_MemDC.DeleteDC();
	m_Bitmap.DeleteObject();
	CDialog::OnCancel();
}

//**************************************************
// OnButtonLoad
//**************************************************
void CDialogPalette::OnButtonLoad() 
{
	CFileDialog dlg(TRUE,
                  _T("PAL"),
                  _T("*.PAL"),
                  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                  _T("Palette files (*.PAL)|*.PAL|") );
  if(dlg.DoModal()==IDOK)
    {
    CString FileName = dlg.GetPathName();
		TRACE("Filename : %s\n",FileName);

		CFile file;
		CFileException ex;
		
		if(!file.Open(FileName, CFile::modeRead | CFile::typeBinary,&ex))
		{
			#ifdef _DEBUG
					afxDump << "File could not be opened " << ex.m_cause << "\n";
			#endif
			AfxMessageBox("Unable to open file for reading");
			return;
		}

		TRY
		{
			for(int i=0;i<256;i++)
			{
			file.Read(&m_Red[i],1);
			file.Read(&m_Green[i],1);
			file.Read(&m_Blue[i],1);
			file.Read(&m_IsNode[i],1);
			}
		}
		CATCH(CFileException, e)
		{
			#ifdef _DEBUG
					afxDump << "Error during reading " << e->m_cause << "\n";
			#endif
			AfxMessageBox("Error during reading");
			return;
		}
		END_CATCH

    file.Close();

    MakePalette();
    DrawPalette();
		RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE ); 
  }
	
}

//**************************************************
// OnButtonSave
//**************************************************
void CDialogPalette::OnButtonSave() 
{
	CFileDialog dlg(FALSE,
                  _T("PAL"),
                  _T("*.PAL"),
                  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                  _T("Palette files (*.PAL)|*.PAL|") );
  if(dlg.DoModal()==IDOK)
    {
    CString FileName = dlg.GetPathName();
		TRACE("Filename : %s\n",FileName);

		CFile file;
		CFileException ex;
		
		if(!file.Open(FileName,CFile::modeCreate | 
													 CFile::modeWrite | 
													 CFile::typeBinary,&ex))
		{
			#ifdef _DEBUG
					afxDump << "File could not be opened " << ex.m_cause << "\n";
			#endif
			AfxMessageBox("Unable to open file for writing");
			return;
		}

		TRY
		{
			for(int i=0;i<256;i++)
			{
			file.Write(&m_Red[i],1);
			file.Write(&m_Green[i],1);
			file.Write(&m_Blue[i],1);
			file.Write(&m_IsNode[i],1);
			}
		}
		CATCH(CFileException, e)
		{
			#ifdef _DEBUG
					afxDump << "Error during writing " << e->m_cause << "\n";
			#endif
		}
		END_CATCH

    file.Close();
  }
}
