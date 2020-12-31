// PlasmaRoutine.h: interface for the CPlasmaRoutine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLASMAROUTINE_H__29FFEFB6_A053_483E_8CB6_676A1B6F6DAC__INCLUDED_)
#define AFX_PLASMAROUTINE_H__29FFEFB6_A053_483E_8CB6_676A1B6F6DAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <Windows.h>

class CPlasmaRoutine  
{
public:
	CPlasmaRoutine();
	virtual ~CPlasmaRoutine();


	// Methods
	void		SetDefaultValues(VARIANT* pExtParms);
	void		InitializePlasma(VARIANT* pExtParms);
	void		Create(int iWidth,int iHeight);
	void		Render(DWORD* pBits, 
		                 int iwidth, 
						 int iheight,
						 int iLineLength);
	void		SetRGB(int iIndex,int R,int G,int B);

	void		InitCostBLTable();
	void		InitPallette();

	void		CalcPlasma();
	void		CreateGradient(COLORREF clrStart,COLORREF clrEnd,long lSteps,COLORREF* pBuffer);

	// Props

	int			m_iWidth;
	int			m_iHeight;
	int			m_iAlpha;

	BYTE*		m_pPlasmaBits;
	DWORD		m_pPalletteBuffer[256];
	int			m_icostbl[256];
	COLORREF	m_PlasmaColors[16];// Yep 16 colors needed to generate our pallete...

	unsigned char	m_a1,m_a2,m_a3,m_a4,m_b1,m_b2,m_b3,m_b4;

	int			m_iModifier1;
	int			m_iModifier2;
	int			m_iModifier3;
	int			m_iModifier4;

	int			m_iXModifier1;
	int			m_iXModifier2;
	int			m_iYModifier1;
	int			m_iYModifier2;


};

#endif // !defined(AFX_PLASMAROUTINE_H__29FFEFB6_A053_483E_8CB6_676A1B6F6DAC__INCLUDED_)
