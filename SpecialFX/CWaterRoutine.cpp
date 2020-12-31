// WaterRoutine.cpp: implementation of the CWaterRoutine class.
//
//////////////////////////////////////////////////////////////////////

#include "CWaterRoutine.h"

#include <math.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define random( min, max ) (( rand() % (int)((( max ) + 1 ) - ( min ))) + ( min ))

CWaterRoutine::CWaterRoutine()
{
	m_iHeightField1 = NULL;
	m_iHeightField2 = NULL;

	m_iWidth = 0;
	m_iHeight = 0;

	m_bDrawWithLight = TRUE;
	m_iLightModifier = 1;
	m_iHpage = 0;
	m_density = 5;
}

CWaterRoutine::~CWaterRoutine()
{
	// Cleanup
	if(m_iHeightField1 != NULL)
		delete [] m_iHeightField1;
	if(m_iHeightField2 != NULL)
		delete [] m_iHeightField2;

	m_iHeightField1 = NULL;
	m_iHeightField2 = NULL;
}
void CWaterRoutine::Create(int iWidth,int iHeight)
{
	if(m_iHeightField1 != NULL)
		delete [] m_iHeightField1;
	if(m_iHeightField2 != NULL)
		delete [] m_iHeightField2;

	// Create our height fields
	m_iHeightField1 = new int[(iWidth*iHeight)];
	m_iHeightField2 = new int[(iWidth*iHeight)];

	// Clear our height fields
	memset(m_iHeightField1,0,(iWidth*iHeight)*sizeof(int));
	memset(m_iHeightField2,0,(iWidth*iHeight)*sizeof(int));

	m_iWidth = iWidth;
	m_iHeight = iHeight;

	// Set our page to 0
	m_iHpage = 0;

}
void CWaterRoutine::FlattenWater()
{
	// Clear our height fields
	memset(m_iHeightField1,0,(m_iWidth*m_iHeight)*sizeof(int));
	memset(m_iHeightField2,0,(m_iWidth*m_iHeight)*sizeof(int));
}
void CWaterRoutine::Render(DWORD* pSrcImage,DWORD* pTargetImage)
{
	// Yes they have to be the same size...(for now)
	if(m_bDrawWithLight == FALSE)
	{
		DrawWaterNoLight(m_iHpage,pSrcImage,pTargetImage);
	}
	else
	{
		DrawWaterWithLight(m_iHpage,m_iLightModifier,pSrcImage,pTargetImage);
	}
	CalcWater(m_iHpage,m_density);


	m_iHpage ^= 1;

}
void CWaterRoutine::CalcWater(int npage, int density)
{
  int newh;
  int count = m_iWidth + 1;
  int *newptr;
  int *oldptr;

  // Set up the pointers
  if(npage == 0)
  {
	newptr = &m_iHeightField1[0];
	oldptr = &m_iHeightField2[0];
  }
  else
  {
	newptr = &m_iHeightField2[0];
	oldptr = &m_iHeightField1[0];
  }

  int x, y;

  // Sorry, this function might not be as readable as I'd like, because
  // I optimized it somewhat.  (enough to make me feel satisfied with it)

  for (y = (m_iHeight-1)*m_iWidth; count < y; count += 2)
  {
    for (x = count+m_iWidth-2; count < x; count++)
    {

// This does the eight-pixel method.  It looks much better.

      newh          = ((oldptr[count + m_iWidth]
                      + oldptr[count - m_iWidth]
                      + oldptr[count + 1]
                      + oldptr[count - 1]
                      + oldptr[count - m_iWidth - 1]
                      + oldptr[count - m_iWidth + 1]
                      + oldptr[count + m_iWidth - 1]
                      + oldptr[count + m_iWidth + 1]
                       ) >> 2 )
                      - newptr[count];


      newptr[count] =  newh - (newh >> density);
/*
// This is the "sludge" method...
      newh = (oldptr[count]<<2)
           +  oldptr[count-1-m_iWidth]
           +  oldptr[count+1-m_iWidth]
           +  oldptr[count-1+m_iWidth]
           +  oldptr[count+1+m_iWidth]
           + ((oldptr[count-1]
           +   oldptr[count+1]
           +   oldptr[count-m_iWidth]
           +   oldptr[count+m_iWidth])<<1);

      newptr[count] = (newh-(newh>>6)) >> density;
*/
    }
  }
}
void CWaterRoutine::SmoothWater(int npage)
{
  int newh;
  int count = m_iWidth + 1;

  int *newptr;
  int *oldptr;

  // Set up the pointers
  if(npage == 0)
  {
	newptr = &m_iHeightField1[0];
	oldptr = &m_iHeightField2[0];
  }
  else
  {
	newptr = &m_iHeightField2[0];
	oldptr = &m_iHeightField1[0];
  }


  int x, y;

  // Sorry, this function might not be as readable as I'd like, because
  // I optimized it somewhat.  (enough to make me feel satisfied with it)

  for(y=1; y<m_iHeight-1; y++)
  {
    for(x=1; x<m_iWidth-1; x++)
    {
// This does the eight-pixel method.  It looks much better.

      newh          = ((oldptr[count + m_iWidth]
                      + oldptr[count - m_iWidth]
                      + oldptr[count + 1]
                      + oldptr[count - 1]
                      + oldptr[count - m_iWidth - 1]
                      + oldptr[count - m_iWidth + 1]
                      + oldptr[count + m_iWidth - 1]
                      + oldptr[count + m_iWidth + 1]
                       ) >> 3 )
                      + newptr[count];


      newptr[count] =  newh>>1;
      count++;
    }
    count += 2;
  }
}

void CWaterRoutine::CalcWaterBigFilter(int npage, int density)
{
  int newh;
  int count = (2*m_iWidth) + 2;

  int *newptr;
  int *oldptr;

  // Set up the pointers
  if(npage == 0)
  {
	newptr = &m_iHeightField1[0];
	oldptr = &m_iHeightField2[0];
  }
  else
  {
	newptr = &m_iHeightField2[0];
	oldptr = &m_iHeightField1[0];
  }

  int x, y;

  // Sorry, this function might not be as readable as I'd like, because
  // I optimized it somewhat.  (enough to make me feel satisfied with it)

  for(y=2; y<m_iHeight-2; y++)
  {
    for(x=2; x<m_iWidth-2; x++)
    {
// This does the 25-pixel method.  It looks much okay.

      newh        = (
                     (
                      (
                       (oldptr[count + m_iWidth]
                      + oldptr[count - m_iWidth]
                      + oldptr[count + 1]
                      + oldptr[count - 1]
                       )<<1)
                      + ((oldptr[count - m_iWidth - 1]
                      + oldptr[count - m_iWidth + 1]
                      + oldptr[count + m_iWidth - 1]
                      + oldptr[count + m_iWidth + 1]))
                      + ( (
                          oldptr[count - (m_iWidth*2)]
                        + oldptr[count + (m_iWidth*2)]
                        + oldptr[count - 2]
                        + oldptr[count + 2]
                        ) >> 1 )
                      + ( (
                          oldptr[count - (m_iWidth*2) - 1]
                        + oldptr[count - (m_iWidth*2) + 1]
                        + oldptr[count + (m_iWidth*2) - 1]
                        + oldptr[count + (m_iWidth*2) + 1]
                        + oldptr[count - 2 - m_iWidth]
                        + oldptr[count - 2 + m_iWidth]
                        + oldptr[count + 2 - m_iWidth]
                        + oldptr[count + 2 + m_iWidth]
                        ) >> 2 )
                     )
                    >> 3)
                    - (newptr[count]);


      newptr[count] =  newh - (newh >> density);
      count++;
    }
    count += 4;
  }
}

void CWaterRoutine::HeightBlob(int x, int y, int radius, int height, int page)
{
  int rquad;
  int cx, cy, cyq;
  int left, top, right, bottom;

  int *newptr;
  int *oldptr;

  // Set up the pointers
  if(page == 0)
  {
	newptr = &m_iHeightField1[0];
	oldptr = &m_iHeightField2[0];
  }
  else
  {
	newptr = &m_iHeightField2[0];
	oldptr = &m_iHeightField1[0];
  }

  rquad = radius * radius;

  // Make a randomly-placed blob...
  if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
  if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);

  left=-radius; right = radius;
  top=-radius; bottom = radius;

  // Perform edge clipping...
  if(x - radius < 1) left -= (x-radius-1);
  if(y - radius < 1) top  -= (y-radius-1);
  if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
  if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);


  for(cy = top; cy < bottom; cy++)
  {
    cyq = cy*cy;
    for(cx = left; cx < right; cx++)
    {
      if(cx*cx + cyq < rquad)
        newptr[m_iWidth*(cy+y) + (cx+x)] += height;
    }
  }

}

void CWaterRoutine::HeightBox (int x, int y, int radius, int height, int page)
{
  int cx, cy;
  int left, top, right, bottom;
  int *newptr;
  int *oldptr;

  // Set up the pointers
  if(page == 0)
  {
	newptr = &m_iHeightField1[0];
	oldptr = &m_iHeightField2[0];
  }
  else
  {
	newptr = &m_iHeightField2[0];
	oldptr = &m_iHeightField1[0];
  }

  if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
  if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);

  left=-radius; right = radius;
  top=-radius; bottom = radius;

  // Perform edge clipping...
  if(x - radius < 1) left -= (x-radius-1);
  if(y - radius < 1) top  -= (y-radius-1);
  if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
  if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

  for(cy = top; cy < bottom; cy++)
  {
    for(cx = left; cx < right; cx++)
    {
        newptr[m_iWidth*(cy+y) + (cx+x)] = height;
    }
  }

}


void CWaterRoutine::WarpBlob(int x, int y, int radius, int height, int page)
{
  int cx, cy;
  int left,top,right,bottom;
  int square;
  int radsquare = radius * radius;
  int *newptr;
  int *oldptr;

  // Set up the pointers
  if(page == 0)
  {
	newptr = &m_iHeightField1[0];
	oldptr = &m_iHeightField2[0];
  }
  else
  {
	newptr = &m_iHeightField2[0];
	oldptr = &m_iHeightField1[0];
  }
//  radsquare = (radius*radius) << 8;
  radsquare = (radius*radius);

  height /= 64;

  left=-radius; right = radius;
  top=-radius; bottom = radius;

  // Perform edge clipping...
  if(x - radius < 1) left -= (x-radius-1);
  if(y - radius < 1) top  -= (y-radius-1);
  if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
  if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

  for(cy = top; cy < bottom; cy++)
  {
    for(cx = left; cx < right; cx++)
    {
      square = cy*cy + cx*cx;
//      square <<= 8;
      if(square < radsquare)
      {
//        Height[page][WATERWID*(cy+y) + cx+x]
//          += (sqrt(radsquare)-sqrt(square))*height;
        newptr[m_iWidth*(cy+y) + cx+x]
          += int((radius-sqrt(square))*(float)(height));
      }
    }
  }
}

void CWaterRoutine::SineBlob(int x, int y, int radius, int height, int page)
{
  int cx, cy;
  int left,top,right,bottom;
  int square, dist;
  int radsquare = radius * radius;
  float length = float((1024.0/(float)radius)*(1024.0/(float)radius));
  int *newptr;
  int *oldptr;

  // Set up the pointers
  if(page == 0)
  {
	newptr = &m_iHeightField1[0];
	oldptr = &m_iHeightField2[0];
  }
  else
  {
	newptr = &m_iHeightField2[0];
	oldptr = &m_iHeightField1[0];
  }

  if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
  if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);


//  radsquare = (radius*radius) << 8;
  radsquare = (radius*radius);

//  height /= 8;

  left=-radius; right = radius;
  top=-radius; bottom = radius;


  // Perform edge clipping...
  if(x - radius < 1) left -= (x-radius-1);
  if(y - radius < 1) top  -= (y-radius-1);
  if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
  if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

  for(cy = top; cy < bottom; cy++)
  {
    for(cx = left; cx < right; cx++)
    {
      square = cy*cy + cx*cx;
      if(square < radsquare)
      {
        dist = int(sqrt(square*length));
        newptr[m_iWidth*(cy+y) + cx+x]
          += (int)((cos(dist)+0xffff)*(height)) >> 19;
      }
    }
  }
}

void CWaterRoutine::DrawWaterNoLight(int page,DWORD* pSrcImage,DWORD* pTargetImage)
{

//  int ox, oy;
  int dx, dy;
  int x, y;
  DWORD c;

  int offset=m_iWidth + 1;

  int *ptr = &m_iHeightField1[0];

  for (y = (m_iHeight-1)*m_iWidth; offset < y; offset += 2)
  {
    for (x = offset+m_iWidth-2; offset < x; offset++)
    {
      dx = ptr[offset] - ptr[offset+1];
      dy = ptr[offset] - ptr[offset+m_iWidth];

	  //Shading = dx;?
	  // Water draw method?
//      c = BkGdImage[offset + WATERWID*(dy>>3) + (dx>>3)];
	  c = pSrcImage[offset + m_iWidth*(dy>>3) + (dx>>3)];

     // If anyone knows a better/faster way to do this, please tell me...
//      temp[offset] = (c < 0) ? 0 : (c > 255) ? 255 : c;
	  pTargetImage[offset] = c;

      offset++;
      dx = ptr[offset] - ptr[offset+1];
      dy = ptr[offset] - ptr[offset+m_iWidth];
//    c = BkGdImage[offset + m_iWidth*(dy>>3) + (dx>>3)];
	  c = pSrcImage[offset + m_iWidth*(dy>>3) + (dx>>3)];
	  pTargetImage[offset] = c;
//      temp[offset] = (c < 0) ? 0 : (c > 255) ? 255 : c;
 
    }
  }
}

void CWaterRoutine::DrawWaterWithLight(int page, int LightModifier,DWORD* pSrcImage,DWORD* pTargetImage)
{

//  int ox, oy;
  int dx, dy;
  int x, y;
  DWORD c;

  int offset=m_iWidth + 1;
  long lIndex;
  long lBreak = m_iWidth*m_iHeight;

  int *ptr = &m_iHeightField1[0];


  for (y = (m_iHeight-1)*m_iWidth; offset < y; offset += 2)
  {
    for (x = offset+m_iWidth-2; offset < x; offset++)
    {
      dx = ptr[offset] - ptr[offset+1];
      dy = ptr[offset] - ptr[offset+m_iWidth];

	  lIndex = offset + m_iWidth*(dy>>3) + (dx>>3);
	  if(lIndex < lBreak && lIndex > 0)
	  {
		  c = pSrcImage[lIndex];// - (dx>>LightModifier);
		  // Now we shift it by the dx component...
		  // 
		  c = GetShiftedColor(c,dx);

 		  pTargetImage[offset] = c;
 	  }

      offset++;
      dx = ptr[offset] - ptr[offset+1];
      dy = ptr[offset] - ptr[offset+m_iWidth];

	  lIndex = offset + m_iWidth*(dy>>3) + (dx>>3);
	  if(lIndex < lBreak && lIndex > 0)
	  {
		  c = pSrcImage[lIndex];// - (dx>>LightModifier);
		  c = GetShiftedColor(c,dx);
	//      temp[offset] = (c < 0) ? 0 : (c > 255) ? 255 : c;
		  pTargetImage[offset] = c;
	  }
 
    }
  }
 
}
inline COLORREF CWaterRoutine::GetShiftedColor(COLORREF color,int shift)
{
	long R;
	long G;
	long B;
	int ir;
	int ig;
	int ib;

	R = GetRValue(color)-shift;
	G = GetGValue(color)-shift;
	B = GetBValue(color)-shift;

	ir = (R < 0) ? 0 : (R > 255) ? 255 : R;
	ig = (G < 0) ? 0 : (G > 255) ? 255 : G;
	ib = (B < 0) ? 0 : (B > 255) ? 255 : B;

	return RGB(ir,ig,ib);
}