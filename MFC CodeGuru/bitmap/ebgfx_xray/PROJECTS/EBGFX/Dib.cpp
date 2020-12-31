// Dib.cpp: implementation of the CDib class.
//
//	Creator : El Barto (ef00@luc.ac.be)
//	Location : http://www.luc.ac.be/~ef00/ebgfx
//	Date : 09-04-98
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib ()
{
	m_Bits=NULL;
	m_Bitmap=NULL;
	m_Size=CSize ( 0, 0 );
}

CDib::~CDib ()
{
	Destroy ();
}

BOOL CDib::Create ( int Width, int Height )
{
	Destroy ();

	ZeroMemory ( &m_Info, sizeof (BITMAPINFO) );

	m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
	m_Info.bmiHeader.biWidth=Width;
	m_Info.bmiHeader.biHeight=Height;
	m_Info.bmiHeader.biPlanes=1;
	m_Info.bmiHeader.biBitCount=32; 
	m_Info.bmiHeader.biCompression=BI_RGB;
	m_Info.bmiHeader.biSizeImage=Width*Height*4;
	
	m_Bitmap=CreateDIBSection ( NULL, &m_Info, DIB_RGB_COLORS, (void **)&m_Bits, NULL, NULL ); 

	if ( m_Bitmap )
	{
		m_Size=CSize ( Width, Height );
		return TRUE;
	}
	else
	{
		m_Size=CSize ( 0, 0 );
		return FALSE;
	}
}

BOOL CDib::Destroy ()
{
	if ( m_Bitmap )
		DeleteObject ( m_Bitmap );
	m_Bitmap=NULL;
	m_Size=CSize ( 0, 0 );
	
	return TRUE;
}

void CDib::CopyDC ( CDC *pDC, int x, int y )
{
	SetDIBitsToDevice ( pDC->m_hDC, x, y, m_Size.cx, m_Size.cy, 0, 0, 0, m_Size.cy, m_Bits, &m_Info, 0); 
}

void CDib::PasteDC ( CDC *pDC, int x, int y, int w, int h )
{
	// If DibSize Wrong Re-Create Dib
	if ( (m_Size.cx!=w) || (m_Size.cy!=h) )
		Create ( w, h );
	
	CDC BufferDC;
	CBitmap BufferBitmap, *OldBitmap;

	BufferDC.CreateCompatibleDC ( pDC );
	BufferBitmap.CreateCompatibleBitmap ( pDC, w, h );
	OldBitmap=BufferDC.SelectObject ( &BufferBitmap );
	BufferDC.FillSolidRect ( 0, 0, w, h, 0 );
	BufferDC.BitBlt ( 0, 0, w, h, pDC, x, y, SRCCOPY );
	BufferDC.SelectObject ( OldBitmap );
	GetDIBits ( pDC->m_hDC, HBITMAP(BufferBitmap), 0, h, m_Bits, &(m_Info), DIB_RGB_COLORS ); 
}

void CDib::SetBitmap ( CDC *pDC, CBitmap *pBitmap )
{
	if ( m_Bitmap )
		GetDIBits ( pDC->m_hDC, HBITMAP(*pBitmap), 0, m_Size.cy, m_Bits, &(m_Info), DIB_RGB_COLORS ); 
}

void CDib::Fill ( int R, int G, int B )
{
	COLORREF Color=RGB ( B, G, R );
	int Size=m_Size.cx*m_Size.cy;

	for ( int i=0; i<Size; i++ )
		m_Bits[i]=Color;
}

void CDib::FillGlass ( int R, int G, int B, int A )
{
	BYTE *dst=(BYTE*)m_Bits;
	int Size=m_Size.cx*m_Size.cy;
		
	while ( Size-- )
	{
		dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
		dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
		dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);	
		dst+=4;
	}
}

void CDib::FillStippledGlass ( int R, int G, int B )
{	
	COLORREF Color=RGB ( B, G, R );
	int w=m_Size.cx;
	int h=m_Size.cy;

	for ( int j=0; j<w; j++ )
	{
		for ( int i=0; i<h; i++ )
		{
			m_Bits[j*w+i]=((i+j)&0x1) ? m_Bits[j*w+i] : Color;
		}
	}
}

void CDib::Copy ( CDib *Dib )
{
	// If DibSize Wrong Re-Create Dib
	if ( (Dib->m_Size.cx!=m_Size.cx) || (Dib->m_Size.cy!=m_Size.cy) )
		Dib->Create ( m_Size.cx, m_Size.cy );
	// do Copy
	memcpy ( Dib->m_Bits, m_Bits, m_Size.cx*m_Size.cy*4 );
}

void CDib::Paste ( CDib *Dib )
{
	// If DibSize Wrong Re-Create Dib
	if ( (m_Size.cx!=Dib->m_Size.cx) || (m_Size.cy!=Dib->m_Size.cy) )
		Create ( Dib->m_Size.cx, Dib->m_Size.cx );
	// do Paste
	memcpy ( m_Bits, Dib->m_Bits, m_Size.cx*m_Size.cy*4 );
}

void CDib::Blend ( CDib *Dib, int A )
{
	if ( m_Size!=Dib->m_Size )
		return;

	BYTE *src=(BYTE*)Dib->m_Bits;
	BYTE *dst=(BYTE*)m_Bits;
	int Size=m_Size.cx*m_Size.cy;
		
	while ( Size-- )
	{
		dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
		dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
		dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);	
		dst+=4;
		src+=4;
	}
}

void CDib::Darken ( CDib *Dib )
{
	if ( m_Size!=Dib->m_Size )
		return;

	BYTE *src=(BYTE*)Dib->m_Bits;
	BYTE *dst=(BYTE*)m_Bits;
	int Size=m_Size.cx*m_Size.cy;
		
	while ( Size-- )
	{
		dst[0]=(BYTE)((src[0]<dst[0]) ? src[0] : dst[0]);
		dst[1]=(BYTE)((src[1]<dst[1]) ? src[1] : dst[1]);
		dst[2]=(BYTE)((src[2]<dst[2]) ? src[2] : dst[2]);	
		dst+=4;
		src+=4;
	}
}

void CDib::Difference ( CDib *Dib )
{
	if ( m_Size!=Dib->m_Size )
		return;

	BYTE *src=(BYTE*)Dib->m_Bits;
	BYTE *dst=(BYTE*)m_Bits;
	int Size=m_Size.cx*m_Size.cy;
		
	while ( Size-- )
	{
		int Difference;
		Difference=src[0]-dst[0];
		dst[0]=(BYTE)((Difference<0) ? -Difference : Difference);
		Difference=src[1]-dst[1];
		dst[1]=(BYTE)((Difference<0) ? -Difference : Difference);
		Difference=src[2]-dst[2];
		dst[2]=(BYTE)((Difference<0) ? -Difference : Difference);	
		dst+=4;
		src+=4;
	}
}

void CDib::Lighten ( CDib *Dib )
{
	if ( m_Size!=Dib->m_Size )
		return;

	BYTE *src=(BYTE*)Dib->m_Bits;
	BYTE *dst=(BYTE*)m_Bits;
	int Size=m_Size.cx*m_Size.cy;
		
	while ( Size-- )
	{
		dst[0]=(BYTE)((src[0]>dst[0]) ? src[0] : dst[0]);
		dst[1]=(BYTE)((src[1]>dst[1]) ? src[1] : dst[1]);
		dst[2]=(BYTE)((src[2]>dst[2]) ? src[2] : dst[2]);	
		dst+=4;
		src+=4;
	}
}

void CDib::Multiply ( CDib *Dib )
{
	if ( m_Size!=Dib->m_Size )
		return;

	BYTE *src=(BYTE*)Dib->m_Bits;
	BYTE *dst=(BYTE*)m_Bits;
	int Size=m_Size.cx*m_Size.cy;
		
	while ( Size-- )
	{
		dst[0]=(BYTE)(((src[0])*(dst[0]))>>8);
		dst[1]=(BYTE)(((src[1])*(dst[1]))>>8);
		dst[2]=(BYTE)(((src[2])*(dst[2]))>>8);	
		dst+=4;
		src+=4;
	}
}

void CDib::Screen ( CDib *Dib )
{
	if ( m_Size!=Dib->m_Size )
		return;

	BYTE *src=(BYTE*)Dib->m_Bits;
	BYTE *dst=(BYTE*)m_Bits;
	int Size=m_Size.cx*m_Size.cy;
		
	while ( Size-- )
	{
		dst[0]=(BYTE)(255-(((255-src[0])*(255-dst[0]))>>8));
		dst[1]=(BYTE)(255-(((255-src[1])*(255-dst[1]))>>8));
		dst[2]=(BYTE)(255-(((255-src[2])*(255-dst[2]))>>8));	
		dst+=4;
		src+=4;
	}
}

//////////////////////////////////////////////////////////////////////
// Rectangle Functions
//////////////////////////////////////////////////////////////////////

void CDib::CopyRect ( CDib *Dib, int x, int y )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Copy return
	if ( (dx<=0) || (dy<=0) )
		return;
	// If DibSize Wrong Re-Create Dib
	if ( (dx!=Dib->m_Size.cx) || (dy!=Dib->m_Size.cy) )
		Dib->Create ( dx, dy );

	// Prepare Buffer Addresses
	COLORREF *src=m_Bits+(py*m_Size.cx)+px;
	COLORREF *dst=Dib->m_Bits;

	// Do Copy
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
			dst[i]=src[i];
		src+=m_Size.cx;
		dst+=Dib->m_Size.cx;
	}
}

void CDib::PasteRect ( CDib *Dib, int x, int y )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Paste return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Addresses
	COLORREF *src=Dib->m_Bits+((py-y)*Dib->m_Size.cx)+px-x;
	COLORREF *dst=m_Bits+(py*m_Size.cx)+px;

	// Do Paste
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
			dst[i]=src[i];
		src+=Dib->m_Size.cx;
		dst+=m_Size.cx;
	}
}

void CDib::FillRect ( int x, int y, int w, int h, int R, int G, int B )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+w)<m_Size.cx) ? w : m_Size.cx-x;
	int dy=((y+h)<m_Size.cy) ? h : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Fill return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Address
	COLORREF *dst=m_Bits+(py*m_Size.cx)+px;
	COLORREF Color=RGB ( B, G, R );

	// Do Fill
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[i]=Color;	
		}
		dst+=m_Size.cx;
	}
}

void CDib::FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+w)<m_Size.cx) ? w : m_Size.cx-x;
	int dy=((y+h)<m_Size.cy) ? h : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to FillGlass return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Address
	BYTE *dst=(BYTE *)m_Bits+((py*m_Size.cx)+px)*4;

	// Do FillGlass
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
			dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
			dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);	
			dst+=4;
		}
		dst+=(m_Size.cx-dx)<<2;
	}
}

void CDib::FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+w)<m_Size.cx) ? w : m_Size.cx-x;
	int dy=((y+h)<m_Size.cy) ? h : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to FillStippledGlass return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Address
	COLORREF *dst=m_Bits+(py*m_Size.cx)+px;
	COLORREF Color=RGB ( B, G, R );

	// Do FillStippledGlass
	for ( int j=0; j<dy; j++ )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[i]=((i+j)&0x1) ? dst[i] : Color;	
		}
		dst+=m_Size.cx;
	}
}

void CDib::BlendRect ( CDib *Dib, int x, int y, int A )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Blend return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Addresses
	BYTE *src=(BYTE *)Dib->m_Bits+(((py-y)*Dib->m_Size.cx)+px-x)*4;
	BYTE *dst=(BYTE *)m_Bits+((py*m_Size.cx)+px)*4;

	// Do Blend
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
			dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
			dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);	
			dst+=4;
			src+=4;
		}
		dst+=(m_Size.cx-dx)<<2;
		src+=(Dib->m_Size.cx-dx)<<2;
	}
}

void CDib::DarkenRect ( CDib *Dib, int x, int y )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Darken return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Addresses
	BYTE *src=(BYTE *)Dib->m_Bits+(((py-y)*Dib->m_Size.cx)+px-x)*4;
	BYTE *dst=(BYTE *)m_Bits+((py*m_Size.cx)+px)*4;

	// Do Darken
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[0]=(BYTE)((src[0]<dst[0]) ? src[0] : dst[0]);
			dst[1]=(BYTE)((src[1]<dst[1]) ? src[1] : dst[1]);
			dst[2]=(BYTE)((src[2]<dst[2]) ? src[2] : dst[2]);	
			dst+=4;
			src+=4;
		}
		dst+=(m_Size.cx-dx)<<2;
		src+=(Dib->m_Size.cx-dx)<<2;
	}
}

void CDib::DifferenceRect ( CDib *Dib, int x, int y )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Difference return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Addresses
	BYTE *src=(BYTE *)Dib->m_Bits+(((py-y)*Dib->m_Size.cx)+px-x)*4;
	BYTE *dst=(BYTE *)m_Bits+((py*m_Size.cx)+px)*4;

	// Do Difference
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			int Difference;
			Difference=src[0]-dst[0];
			dst[0]=(BYTE)((Difference<0) ? -Difference : Difference);
			Difference=src[1]-dst[1];
			dst[1]=(BYTE)((Difference<0) ? -Difference : Difference);
			Difference=src[2]-dst[2];
			dst[2]=(BYTE)((Difference<0) ? -Difference : Difference);	
			dst+=4;
			src+=4;
		}
		dst+=(m_Size.cx-dx)<<2;
		src+=(Dib->m_Size.cx-dx)<<2;
	}
}

void CDib::LightenRect ( CDib *Dib, int x, int y )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Lighten return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Addresses
	BYTE *src=(BYTE *)Dib->m_Bits+(((py-y)*Dib->m_Size.cx)+px-x)*4;
	BYTE *dst=(BYTE *)m_Bits+((py*m_Size.cx)+px)*4;

	// Do Lighten
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[0]=(BYTE)((src[0]>dst[0]) ? src[0] : dst[0]);
			dst[1]=(BYTE)((src[1]>dst[1]) ? src[1] : dst[1]);
			dst[2]=(BYTE)((src[2]>dst[2]) ? src[2] : dst[2]);
			dst+=4;
			src+=4;
		}
		dst+=(m_Size.cx-dx)<<2;
		src+=(Dib->m_Size.cx-dx)<<2;
	}
}

void CDib::MultiplyRect ( CDib *Dib, int x, int y )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Multiply return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Addresses
	BYTE *src=(BYTE *)Dib->m_Bits+(((py-y)*Dib->m_Size.cx)+px-x)*4;
	BYTE *dst=(BYTE *)m_Bits+((py*m_Size.cx)+px)*4;

	// Do Multiply
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[0]=(BYTE)(((src[0])*(dst[0]))>>8);
			dst[1]=(BYTE)(((src[1])*(dst[1]))>>8);
			dst[2]=(BYTE)(((src[2])*(dst[2]))>>8);
			dst+=4;
			src+=4;
		}
		dst+=(m_Size.cx-dx)<<2;
		src+=(Dib->m_Size.cx-dx)<<2;
	}
}

void CDib::ScreenRect ( CDib *Dib, int x, int y )
{
	// Clip Rect
	int px=(x>=0) ? x : 0;
	int py=(y>=0) ? y : 0;
	int dx=((x+Dib->m_Size.cx)<m_Size.cx) ? Dib->m_Size.cx : m_Size.cx-x;
	int dy=((y+Dib->m_Size.cy)<m_Size.cy) ? Dib->m_Size.cy : m_Size.cy-y;
	dx=(x>=0) ? dx : dx + x;
	dy=(y>=0) ? dy : dy + y;

	// If Nothing to Screen return
	if ( (dx<=0) || (dy<=0) )
		return;

	// Prepare Buffer Addresses
	BYTE *src=(BYTE *)Dib->m_Bits+(((py-y)*Dib->m_Size.cx)+px-x)*4;
	BYTE *dst=(BYTE *)m_Bits+((py*m_Size.cx)+px)*4;

	// Do Screen
	while ( dy-- )
	{
		for ( int i=0; i<dx; i++ )
		{
			dst[0]=(BYTE)(255-(((255-src[0])*(255-dst[0]))>>8));
			dst[1]=(BYTE)(255-(((255-src[1])*(255-dst[1]))>>8));
			dst[2]=(BYTE)(255-(((255-src[2])*(255-dst[2]))>>8));
			dst+=4;
			src+=4;
		}
		dst+=(m_Size.cx-dx)<<2;
		src+=(Dib->m_Size.cx-dx)<<2;
	}
}

//////////////////////////////////////////////////////////////////////
// Line Functions
//////////////////////////////////////////////////////////////////////

/*void CDib::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
{
	int dx, dy, k1, k2, d, x, y;
	COLORREF Color=RGB ( B, G, R );

	dx=x2-x1;
	dy=y2-y1;
	d=(dy<<1)-dx;
	k1=dy<<1;
	k2=(dy-dx)<<1;
	x=x1;
	y=y1;

	m_Bits[y*m_Size.cx+x]=Color;
	while (x<dx) 
	{
		if (d<=0) 
		{
			d+=k1;
			x++;
		} 
		else 
		{
			d+=k2;
			x++;
			y++;
		}
		m_Bits[y*m_Size.cx+x]=Color;
	}
}*/

void CDib::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
{
	int d, x, y, ax, ay, sx, sy, dx, dy;
	COLORREF Color=RGB ( B, G, R );
	
	dx=x2-x1;
	ax=abs ( dx )<<1;
	sx=(dx<0) ? -1 : 1;
	dy=y2-y1;
	ay=abs ( dy )<<1;
	sy=(dy<0) ? -1 : 1;
	x=x1;
	y=y1;
	
	if ( ax>ay )
	{
		d=ay-(ax>>1);
		while ( x!=x2 )
		{
			m_Bits[y*m_Size.cx+x]=Color;
			if ( d>=0 )
			{
				y+=sy;
				d-=ax;
			}
			x+=sx;
			d+=ay;
		}
	}
	else
	{
		d=ax-(ay>>1);
		while ( y!=y2 )
		{
			m_Bits[y*m_Size.cx+x]=Color;
			if ( d>=0 )
			{
				x+=sx;
				d-=ay;
			}
			y+=sy;
			d+=ax;
		}
	}
}

void CDib::LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A )
{
	int d, x, y, ax, ay, sx, sy, dx, dy;
	COLORREF Color=RGB ( B, G, R );
	BYTE *dst=(BYTE *)m_Bits;
	
	dx=x2-x1;
	ax=abs ( dx )<<1;
	sx=(dx<0) ? -1 : 1;
	dy=y2-y1;
	ay=abs ( dy )<<1;
	sy=(dy<0) ? -1 : 1;
	x=x1;
	y=y1;
	
	if ( ax>ay )
	{
		d=ay-(ax>>1);
		while ( x!=x2 )
		{
			dst[(y*m_Size.cx+x)<<2]=(BYTE)(((B-dst[(y*m_Size.cx+x)<<2])*A+(dst[(y*m_Size.cx+x)<<2]<<8))>>8);
			dst[((y*m_Size.cx+x)<<2)+1]=(BYTE)(((G-dst[((y*m_Size.cx+x)<<2)+1])*A+(dst[((y*m_Size.cx+x)<<2)+1]<<8))>>8);
			dst[((y*m_Size.cx+x)<<2)+2]=(BYTE)(((R-dst[((y*m_Size.cx+x)<<2)+2])*A+(dst[((y*m_Size.cx+x)<<2)+2]<<8))>>8);
			if ( d>=0 )
			{
				y+=sy;
				d-=ax;
			}
			x+=sx;
			d+=ay;
		}
	}
	else
	{
		d=ax-(ay>>1);
		while ( y!=y2 )
		{
			dst[(y*m_Size.cx+x)<<2]=(BYTE)(((B-dst[(y*m_Size.cx+x)<<2])*A+(dst[(y*m_Size.cx+x)<<2]<<8))>>8);
			dst[((y*m_Size.cx+x)<<2)+1]=(BYTE)(((G-dst[((y*m_Size.cx+x)<<2)+1])*A+(dst[((y*m_Size.cx+x)<<2)+1]<<8))>>8);
			dst[((y*m_Size.cx+x)<<2)+2]=(BYTE)(((R-dst[((y*m_Size.cx+x)<<2)+2])*A+(dst[((y*m_Size.cx+x)<<2)+2]<<8))>>8);
			if ( d>=0 )
			{
				x+=sx;
				d-=ay;
			}
			y+=sy;
			d+=ax;
		}
	}
}