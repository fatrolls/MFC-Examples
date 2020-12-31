// CFireRoutine.cpp: implementation of the CFireRoutine class.
//
//////////////////////////////////////////////////////////////////////

#include "CFireRoutine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFireRoutine::CFireRoutine()
{
	m_iWidth = 0;
	m_iHeight = 0;
	m_pFireBits = NULL;
	m_pYIndexes = NULL;
	m_iFireSource = 2;
	m_iFireChance = 10;
	m_iFlameHeight = 50;
	m_iAlpha = 255;

	m_FireColors[0]  = RGB(0,0,0);// Black
	m_FireColors[1]  = RGB(255,0,0);// Red
	m_FireColors[2]  = RGB(255,255,0);// Yellow
	m_FireColors[3]  = RGB(255,255,255);// White
	m_iAvgFlameWidth = 35;
}

CFireRoutine::~CFireRoutine()
{
	if(m_pFireBits != NULL)
		delete [] m_pFireBits;

	if(m_pYIndexes != NULL)
		delete [] m_pYIndexes;

	m_pFireBits = NULL;
	m_pYIndexes = NULL;
}
void CFireRoutine::InitFire()
{
	// Get Rid of anything already there
	if(m_pFireBits != NULL)
		delete [] m_pFireBits;

	if(m_pYIndexes != NULL)
		delete [] m_pYIndexes;

	// Add three to the height
	m_iHeight+=3;

	m_pYIndexes = new long[m_iHeight];

	m_pFireBits = new BYTE[m_iWidth*m_iHeight];

	// Clear the Fire bits
	memset(m_pFireBits,0,(m_iWidth*m_iHeight));
	// do all the y index pre-calc..
	for (int y = m_iHeight; y >0; y--)  
		m_pYIndexes[y] = y * m_iWidth;  

	// Create our pallete

	InitPallette();
	ClrHotSpots();

}
void CFireRoutine::ClrHotSpots()
{
	// clear the fire line
	memset(&m_pFireBits[m_pYIndexes[m_iFireSource]],0,m_iWidth);
}
void CFireRoutine::InitPallette()
{
	// Create a gradient between all the colors we have for our fire...

	long iCount = 0;
	COLORREF clrStart;
	COLORREF clrEnd;

	for(int iColor = 1;iColor<4;iColor++)
	{

		
		clrStart = m_FireColors[iColor-1];
		clrEnd = m_FireColors[iColor];

			
		int r, g, b;							// First distance, then starting value
		float rStep, gStep, bStep;		// Step size for each color

		// Get the color differences
		r = (GetRValue(clrEnd) - GetRValue(clrStart));
		g = (GetGValue(clrEnd) - GetGValue(clrStart));
		b =  (GetBValue(clrEnd) - GetBValue(clrStart));

		int nSteps = max(abs(r), max(abs(g), abs(b)));
		float fStep = (float)(255/3)/ (float)nSteps;
		// Calculate the step size for each color
		rStep = r/(float)nSteps;
		gStep = g/(float)nSteps;
		bStep = b/(float)nSteps;

		// Reset the colors to the starting position
		r = GetRValue(clrStart);
		g = GetGValue(clrStart);
		b = GetBValue(clrStart);

		for (int iOnBand = 0; iOnBand < nSteps; iOnBand++) 
		{
			//COLORREF color = RGB(r+rStep*iOnBand, g + gStep*iOnBand, b + bStep *iOnBand);
			COLORREF color = RGB(b + bStep *iOnBand, g + gStep*iOnBand,r+rStep*iOnBand);

			long lIndex = (int)(iOnBand * fStep);

			if(lIndex+((iColor-1)*85) < 255)
				m_pPalletteBuffer[lIndex+((iColor-1)*85)] = color;				
		}
	}
	// Step on the second color a little bit...
	clrStart = m_FireColors[0];
	clrEnd = m_FireColors[1];

	for(int kj=0;kj<m_iFlameHeight;kj++)
		m_pPalletteBuffer[kj] = 0;

	int r, g, b;							// First distance, then starting value
	float rStep, gStep, bStep;		// Step size for each color

	// Get the color differences
	r = (GetRValue(clrEnd) - GetRValue(clrStart));
	g = (GetGValue(clrEnd) - GetGValue(clrStart));
	b =  (GetBValue(clrEnd) - GetBValue(clrStart));

	int nSteps = max(abs(r), max(abs(g), abs(b)));
	float fStep = (float)(85-m_iFlameHeight)/ (float)nSteps;
	// Calculate the step size for each color
	rStep = r/(float)nSteps;
	gStep = g/(float)nSteps;
	bStep = b/(float)nSteps;

	// Reset the colors to the starting position
	r = GetRValue(clrStart);
	g = GetGValue(clrStart);
	b = GetBValue(clrStart);

	for (int iOnBand = 0; iOnBand < nSteps; iOnBand++) 
	{
		//COLORREF color = RGB(r+rStep*iOnBand, g + gStep*iOnBand, b + bStep *iOnBand);
		COLORREF color = RGB(b + bStep *iOnBand, g + gStep*iOnBand,r+rStep*iOnBand);

		long lIndex = (int)(iOnBand * fStep);

		m_pPalletteBuffer[lIndex+(85-m_iFlameHeight)] = color;				
	}

}
// Macro to get a random integer within a specified range */
#define getrandom( min, max ) (( rand() % (int)((( max ) + 1 ) - ( min ))) + ( min ))
#include <time.h>

void CFireRoutine::SetHotSpots()
{  
	ClrHotSpots();
	//m_iAvgFlameWidth

	long lPosition = 0;
	while(lPosition < m_iWidth)
	{
		// see if we should do a flame
		if (getrandom(0,100) < m_iFireChance)
		{
			// get a flame width
			long lFlameWidth = getrandom(1,m_iAvgFlameWidth);
			for(int i=0;i<lFlameWidth;i++)
			{
				if(lPosition < m_iWidth)
				{
					m_pFireBits[m_pYIndexes[m_iFireSource]+lPosition] =254;// set a hot spot! 
					lPosition++;
				}
			}
		}
		lPosition++;
	}
//	for (x = 0; x < m_iWidth; x++)  
//	{  
//		if (getrandom(0,100) < m_iFireChance)
//		{
			
//		}
//	}  
} 

void CFireRoutine::MakeLines()  
{  
	int x, y;  

	for (x = 0; x < m_iWidth; x++)  
	{
		 for (y = m_iFireSource; y<m_iHeight-1;y++) 
 //       for (y = m_iHeight; y > m_iFireSource; y--)  
		{
			//m_pFireBits[m_pYIndexes[y-1]+x] =Average(x,y);
			 m_pFireBits[m_pYIndexes[y+1]+x] =Average(x,y);
		}
	}
} 
unsigned char CFireRoutine::Average(int x, int y)  
{  

	unsigned char ave_color;  
	unsigned char ave1, ave2, ave3, ave4, ave5, ave6, ave7;  

	// Make sure we are not at the last line...
	if(y == m_iHeight)
		ave1 = m_pFireBits[m_pYIndexes[y-1] + x];  
	else
		ave1 = m_pFireBits[m_pYIndexes[y + 1] + x];  

	ave2 = m_pFireBits[m_pYIndexes[y - 1] + x];  
	ave3 = m_pFireBits[m_pYIndexes[y] + x + 1];  
	ave4 = m_pFireBits[m_pYIndexes[y] + x - 1];  
	ave5 = m_pFireBits[m_pYIndexes[y] + x + 2];  
	ave6 = m_pFireBits[m_pYIndexes[y] + x - 2];  
	ave7 = m_pFireBits[m_pYIndexes[y] + x];

	ave_color = (ave1 + ave2 + ave3 + ave4 + ave5 + ave6 + ave7) / 7;  

	return(ave_color);  
} 
void CFireRoutine::Render(DWORD* pVideoMemory,
		                 int iwidth, 
						 int iheight 						 
						 )
{
	SetHotSpots();   // generate random hotspots  
	MakeLines();  // do all the math and screen updating  

	// Right now Im just going to blit it right onto the video memory
	unsigned char* pSrcBitlin;// = m_pFireBits+(m_iWidth*3);// get rid of our fire source
	BYTE *dst;//=(BYTE*)Dib->pVideoMemory;

	BYTE r;
	BYTE g;
	BYTE b;

	for(int i=0;i<m_iHeight-3;i++)
	{
		dst = (BYTE*)&pVideoMemory[(iwidth*i)];
		pSrcBitlin =&m_pFireBits[m_pYIndexes[i+3]];

		for(int x=0;x<m_iWidth;x++)
		{
			r = GetRValue(m_pPalletteBuffer[pSrcBitlin[x]]);
			g = GetGValue(m_pPalletteBuffer[pSrcBitlin[x]]);
			b = GetBValue(m_pPalletteBuffer[pSrcBitlin[x]]);

			dst[0]=(BYTE)(((r-dst[0])*m_iAlpha+(dst[0]<<8))>>8);
			dst[1]=(BYTE)(((g-dst[1])*m_iAlpha+(dst[1]<<8))>>8);
			dst[2]=(BYTE)(((b-dst[2])*m_iAlpha+(dst[2]<<8))>>8);	
			dst+=4;
		}
	}

}


