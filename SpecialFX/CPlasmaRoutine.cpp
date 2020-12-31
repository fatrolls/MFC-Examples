// PlasmaRoutine.cpp: implementation of the CPlasmaRoutine class.
//
//////////////////////////////////////////////////////////////////////

#include "CPlasmaRoutine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <math.h>

CPlasmaRoutine::CPlasmaRoutine()
{
	m_iHeight = 0;
	m_iWidth  = 0;
	m_pPlasmaBits = NULL;
	m_iAlpha = 255;

	m_a1=0;
	m_a2=0;
	m_a3=0;
	m_a4=0;
	m_b1=0;
	m_b2=0;
	m_b3=0;
	m_b4=0;

	m_iModifier1=1;
	m_iModifier2=2;
	m_iModifier3=1;
	m_iModifier4=2;

	m_iXModifier1 = -1;
	m_iXModifier2 = 3;

	m_iYModifier1 = 1;
	m_iYModifier2 = -2;

	// Set up our defalt plasma colors
	m_PlasmaColors[0]=RGB(0,0,0);// From black 
	m_PlasmaColors[1]=RGB(0,0,255);// To Blue

	m_PlasmaColors[2]=RGB(0,0,255);// From  Blue
	m_PlasmaColors[3]=RGB(0,255,0);// To Green

	m_PlasmaColors[4]=RGB(0,255,0);// From Green
	m_PlasmaColors[5]=RGB(0,255,255);// To Cyan

	m_PlasmaColors[6]=RGB(0,255,255);// Cyan
	m_PlasmaColors[7]=RGB(0,255,255); 

	m_PlasmaColors[8]=RGB(0,255,255);// Cyan
	m_PlasmaColors[9]=RGB(0,255,255); 

	m_PlasmaColors[10]=RGB(0,255,255);// From White
	m_PlasmaColors[11]=RGB(0,255,0); // To dark green

	m_PlasmaColors[12]=RGB(0,255,0);// From Dark Blue
	m_PlasmaColors[13]=RGB(0,0,255);// To dark green

	m_PlasmaColors[14]=RGB(0,0,255);// From Dark Blue
	m_PlasmaColors[15]=RGB(0,0,0);// To Black

}

CPlasmaRoutine::~CPlasmaRoutine()
{
	if(m_pPlasmaBits != NULL)
		delete [] m_pPlasmaBits;

	m_pPlasmaBits = NULL;
}
void CPlasmaRoutine::InitCostBLTable()
{
  for(int t=0;t<256;t++)
        m_icostbl[t] = (int)( 30 * cos(t * (3.14159/64) ) );
}
inline void CPlasmaRoutine::SetRGB(int iIndex,int R,int G,int B)
{
	COLORREF color = RGB(R+50,G+50,B+50);
	m_pPalletteBuffer[iIndex] = color;	

}
void CPlasmaRoutine::InitPallette()
{
	// Create a gradient between all the colors we have for our plasma
	CreateGradient(m_PlasmaColors[0],m_PlasmaColors[1],32,&m_pPalletteBuffer[0]); // From black to Blue
	CreateGradient(m_PlasmaColors[2],m_PlasmaColors[3],32,&m_pPalletteBuffer[32]); // From Green to Blue
	CreateGradient(m_PlasmaColors[4],m_PlasmaColors[5],32,&m_pPalletteBuffer[64]); // From Green to White
	CreateGradient(m_PlasmaColors[6],m_PlasmaColors[6],32,&m_pPalletteBuffer[96]);// From Cyan to Cyan
	CreateGradient(m_PlasmaColors[8],m_PlasmaColors[9],32,&m_pPalletteBuffer[128]);// Cyan To Cyan
	CreateGradient(m_PlasmaColors[10],m_PlasmaColors[11],32,&m_pPalletteBuffer[160]);// While to dark Green
	CreateGradient(m_PlasmaColors[12],m_PlasmaColors[13],32,&m_pPalletteBuffer[192]);// Dark Blue to dark green
	CreateGradient(m_PlasmaColors[14],m_PlasmaColors[15],32,&m_pPalletteBuffer[224]);// Dark Blue to black
			
}
inline void CPlasmaRoutine::CreateGradient(COLORREF clrStart,COLORREF clrEnd,long lSteps,COLORREF* pBuffer)
{
	// I created this routine to make real smooth gradients...
	// It may not be real optimized, but it works....and that is what matters to me right now...

	int r, g, b;							// First distance, then starting value
	int rTotal,gTotal,bTotal;
	int roffset,goffset,boffset;
	int scalerR;
	int scalerG;
	int scalerB;


	roffset = goffset = boffset = 0;
	scalerR = scalerG = scalerB = 0;

	// Get the color differences and scalers
	rTotal = GetRValue(clrEnd) - GetRValue(clrStart);
	if(rTotal < 0)
		scalerR = -1;
	else if(rTotal > 0)
		scalerR = 1;	

	gTotal = GetGValue(clrEnd) - GetGValue(clrStart);
	if(gTotal < 0)
		scalerG = -1;
	else if(gTotal > 0)
		scalerG = 1;

	bTotal = GetBValue(clrEnd) - GetBValue(clrStart);

	if(bTotal < 0)
		scalerB = -1;
	else if(bTotal > 0)
		scalerB = 1;

	// reset to positives
	rTotal=abs(rTotal);
	gTotal=abs(gTotal);
	bTotal=abs(bTotal);

	// Get the starting color values...
	r = GetRValue(clrStart);
	g = GetGValue(clrStart);
	b = GetBValue(clrStart);

	for(int i=0;i<lSteps;i++)
	{
		roffset = ::MulDiv(i, rTotal, lSteps);
		goffset = ::MulDiv(i, gTotal, lSteps);
		boffset = ::MulDiv(i, bTotal, lSteps);

		roffset*=scalerR;
		goffset*=scalerG;
		boffset*=scalerB;

		COLORREF color = RGB( (b+boffset),(g+goffset),(r+roffset));

		pBuffer[i] = color;

	}

}

void CPlasmaRoutine::CalcPlasma()
{
	// Initialize with outer variables 
    m_a1 = m_b1;
    m_a2 = m_b2;
	unsigned char  *tscr = (unsigned char*)&m_pPlasmaBits[0];

    for(long y=0;y<m_iHeight;y++)
    {
	// Initialize with outer variables 

        m_a3 = m_b3;
        m_a4 = m_b4;

        for(long x=0;x<m_iWidth;x++)
        {
            *tscr++ = m_icostbl[m_a1] +
                      m_icostbl[m_a2] +
                      m_icostbl[m_a3] +
                      m_icostbl[m_a4] ;

            // Higher values result in many slower plasmas 

            m_a3 += m_iModifier1;//4;
            m_a4 += m_iModifier2;//1;
        }

        // Same as the previous comment

        m_a1 += m_iModifier3;//1;
        m_a2 += m_iModifier4;//4;

    }

	m_b1 += m_iYModifier1;//y modifier 1
	m_b2 += m_iYModifier2;//y modifier 2
	m_b3 += m_iXModifier1;//x modifier 1
	m_b4 += m_iXModifier2;//x modifier 2

}
void CPlasmaRoutine::Create(int iWidth,int iHeight)
{
	if(m_pPlasmaBits != NULL)
		delete [] m_pPlasmaBits;
	
	m_pPlasmaBits = new BYTE[(iWidth*iHeight)];
	m_iHeight = iHeight;
	m_iWidth  = iWidth;

	// zero out our plasma
	memset(m_pPlasmaBits,0,(iWidth*iHeight));
	// Init the Cost Table
	InitCostBLTable();
	// Init our pallette
	InitPallette();
	// Go ahead and calculate a plasma
	CalcPlasma();
}
void CPlasmaRoutine::Render(DWORD* pBits,int iwidth,int iheight,int iLineLength)
{
	// Right now Im just going to blit it right onto the video memory
	unsigned char* pSrcBitlin;// = m_pFireBits+(m_iWidth*3);// get rid of our fire source
	BYTE *dst;//=(BYTE*)Dib->pVideoMemory;
	COLORREF myColor;
	BYTE r;
	BYTE g;
	BYTE b;

	for(int i=0;i<m_iHeight;i++)
	{
		if(i <= iheight)
		{
			dst = (BYTE*)&pBits[(iLineLength*i)];
			pSrcBitlin =&m_pPlasmaBits[m_iWidth*i];

			for(int x=0;x<m_iWidth;x++)
			{
				if(x <= iLineLength)
				{
					myColor =m_pPalletteBuffer[pSrcBitlin[x]];

					r = GetRValue(myColor);
					g = GetGValue(myColor);
					b = GetBValue(myColor);

					dst[0]=(BYTE)(((r-dst[0])*m_iAlpha+(dst[0]<<8))>>8);
					dst[1]=(BYTE)(((g-dst[1])*m_iAlpha+(dst[1]<<8))>>8);
					dst[2]=(BYTE)(((b-dst[2])*m_iAlpha+(dst[2]<<8))>>8);	
					dst+=4;
				}
			}
		}
	}
	CalcPlasma();

}
void CPlasmaRoutine::SetDefaultValues(VARIANT* pExtParms)
{
	m_iAlpha = 255;
	pExtParms[2].intVal =m_iAlpha;

	m_iModifier1=1;
	m_iModifier2=2;
	m_iModifier3=1;
	m_iModifier4=2;

	pExtParms[3].intVal = m_iModifier1;
	pExtParms[4].intVal = m_iModifier2;
	pExtParms[5].intVal = m_iModifier3;
	pExtParms[6].intVal = m_iModifier4;

	m_iXModifier1 = -1;
	m_iXModifier2 = 3;

	m_iYModifier1 = 1;
	m_iYModifier2 = -2;

	pExtParms[7].intVal = m_iXModifier1;
	pExtParms[8].intVal = m_iXModifier2;
	pExtParms[9].intVal = m_iYModifier1;
	pExtParms[10].intVal = m_iYModifier2;

	// Set up our defalt plasma colors
	m_PlasmaColors[0]=RGB(0,0,0);// From black 
	m_PlasmaColors[1]=RGB(0,0,255);// To Blue
	m_PlasmaColors[2]=RGB(0,0,255);// From  Blue
	m_PlasmaColors[3]=RGB(0,255,0);// To Green
	m_PlasmaColors[4]=RGB(0,255,0);// From Green
	m_PlasmaColors[5]=RGB(0,255,255);// To Cyan
	m_PlasmaColors[6]=RGB(0,255,255);// Cyan
	m_PlasmaColors[7]=RGB(0,255,255); 
	m_PlasmaColors[8]=RGB(0,255,255);// Cyan
	m_PlasmaColors[9]=RGB(0,255,255); 
	m_PlasmaColors[10]=RGB(0,255,255);// From White
	m_PlasmaColors[11]=RGB(0,255,0); // To dark green
	m_PlasmaColors[12]=RGB(0,255,0);// From Dark Blue
	m_PlasmaColors[13]=RGB(0,0,255);// To dark green
	m_PlasmaColors[14]=RGB(0,0,255);// From Dark Blue
	m_PlasmaColors[15]=RGB(0,0,0);// To Black


	pExtParms[11].ulVal = m_PlasmaColors[0];
	pExtParms[12].ulVal = m_PlasmaColors[1];
	pExtParms[13].ulVal = m_PlasmaColors[2];
	pExtParms[14].ulVal = m_PlasmaColors[3];
	pExtParms[15].ulVal = m_PlasmaColors[4];
	pExtParms[16].ulVal = m_PlasmaColors[5];
	pExtParms[17].ulVal = m_PlasmaColors[6];
	pExtParms[18].ulVal = m_PlasmaColors[7];
	pExtParms[19].ulVal = m_PlasmaColors[8];
	pExtParms[20].ulVal = m_PlasmaColors[9];
	pExtParms[21].ulVal = m_PlasmaColors[10];
	pExtParms[22].ulVal = m_PlasmaColors[11];
	pExtParms[23].ulVal = m_PlasmaColors[12];
	pExtParms[24].ulVal = m_PlasmaColors[13];
	pExtParms[25].ulVal = m_PlasmaColors[14];
	pExtParms[26].ulVal = m_PlasmaColors[15];

	InitPallette();
}
void CPlasmaRoutine::InitializePlasma(VARIANT* pExtParms)
{
	m_iAlpha = pExtParms[2].intVal;

	m_iModifier1 = pExtParms[3].intVal;
	m_iModifier2 = pExtParms[4].intVal;
	m_iModifier3 = pExtParms[5].intVal;
	m_iModifier4 = pExtParms[6].intVal;

	m_iXModifier1 = pExtParms[7].intVal;
	m_iXModifier2 = pExtParms[8].intVal;
	m_iYModifier1 = pExtParms[9].intVal;
	m_iYModifier2 = pExtParms[10].intVal;

	m_PlasmaColors[0]=pExtParms[11].ulVal;
	m_PlasmaColors[1]=pExtParms[12].ulVal;
	m_PlasmaColors[2]=pExtParms[13].ulVal;
	m_PlasmaColors[3]=pExtParms[14].ulVal;
	m_PlasmaColors[4]=pExtParms[15].ulVal;
	m_PlasmaColors[5]=pExtParms[16].ulVal;
	m_PlasmaColors[6]=pExtParms[17].ulVal;
	m_PlasmaColors[7]=pExtParms[18].ulVal;
	m_PlasmaColors[8]=pExtParms[19].ulVal;
	m_PlasmaColors[9]=pExtParms[20].ulVal;
	m_PlasmaColors[10]=pExtParms[21].ulVal;
	m_PlasmaColors[11]=pExtParms[22].ulVal;
	m_PlasmaColors[12]=pExtParms[23].ulVal;
	m_PlasmaColors[13]=pExtParms[24].ulVal;
	m_PlasmaColors[14]=pExtParms[25].ulVal;
	m_PlasmaColors[15]=pExtParms[26].ulVal;

	if(pExtParms[0].intVal != m_iWidth || pExtParms[1].intVal != m_iHeight)
		Create(pExtParms[0].intVal,pExtParms[1].intVal);
	else
		InitPallette();
}

