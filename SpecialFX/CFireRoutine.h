// CFireRoutine.h: interface for the CFireRoutine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFIREROUTINE_H__413FF819_B711_4B5A_8EC1_580A70862BE4__INCLUDED_)
#define AFX_CFIREROUTINE_H__413FF819_B711_4B5A_8EC1_580A70862BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <Windows.h>

class CFireRoutine  
{
public:
	CFireRoutine();
	virtual ~CFireRoutine();

	// Functs (public)

	void		InitFire();
	void		ClrHotSpots();
	void		InitPallette();
	void		SetHotSpots();
	void		MakeLines();
	void		Render(DWORD* pVideoMemory,
		                 int iwidth, 
						 int iheight);


	unsigned char	Average(int x, int y);

	// props
	int			m_iFlameHeight;
	int			m_iWidth;
	int			m_iHeight;
	int			m_iFireSource;//The y position for the lit spots
	int			m_iFireChance;
	int			m_iAvgFlameWidth;
	int			m_iAlpha;

	COLORREF	m_FireColors[4];

	BYTE*	m_pFireBits;
	DWORD   m_pPalletteBuffer[256];
	long*	m_pYIndexes;


};

#endif // !defined(AFX_CFIREROUTINE_H__413FF819_B711_4B5A_8EC1_580A70862BE4__INCLUDED_)
