/*****************************************************************************************
模 块 名：Wave.h
说    明：水波效果实现函数的头文件
创 建 人：魔佳
版    本：V1.0.0
*****************************************************************************************/

#include <windows.h>

#define	F_WO_ACTIVE	0X0001
#define	F_WO_NEED_UPDATE	0x0002
#define	F_WO_EFFECT	0x0004
#define	F_WO_ELLIPSE	0x0008

typedef struct _WAVEOBJECT
{
	HWND hWnd;
	UINT dwFlag;			//见 F_WO_xxx 组合
	HDC hDcRender;
	HBITMAP hBmpRender;
	PBYTE lpDIBitsSource;
	PBYTE   lpDIBitsRender;	// 用于显示到屏幕的像素数据
	int * lpWave1;			// 水波能量数据缓冲1
	int * lpWave2;			// 水波能量数据缓冲2

	int dwBmpWidth;
	int dwBmpHeight;
	UINT dwDIByteWidth;		// = (dwBmpWidth * 3 + 3) and ~3
	UINT dwWaveByteWidth;	// = dwBmpWidth * 4
	UINT dwRandom;

	// 特效参数
	UINT dwEffectType;
	int dwEffectParam1;
	int dwEffectParam2;
	int dwEffectParam3;

	// 用于行船特效
	int dwEff2X;
	int dwEff2Y;
	int dwEff2XAdd;
	int dwEff2YAdd;
	int dwEff2Flip;
	//********************************************************************
	BITMAPINFO stBmpInfo;
} WAVEOBJECT,*LPWAVEOBJECT;

extern "C" UINT __stdcall WaveInit(LPWAVEOBJECT lpWaveObject, HWND hWnd, HBITMAP hBmp, UINT dwSpeed, UINT dwType);

extern "C" void __stdcall WaveDropStone(LPWAVEOBJECT lpWaveObject, int dwPosX, int dwPosY, int dwStoneSize,int dwStoneWeight);

extern "C" void __stdcall WaveUpdateFrame(LPWAVEOBJECT lpWaveObject, HDC hDc, BOOL bIfForce);

extern "C" void __stdcall WaveFree(LPWAVEOBJECT lpWaveObject);

extern "C" void __stdcall WaveEffect(LPWAVEOBJECT lpWaveObject, UINT dwType,int dwParam1,int dwParam2,int dwParam3);

