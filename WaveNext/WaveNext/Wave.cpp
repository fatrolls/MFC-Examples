/*****************************************************************************************
模 块 名：Wave.cpp
说    明：水波效果实现函数
创 建 人：魔佳
描    述：Wave VC版本根据罗云彬的汇编代码改写,
	实现水波特效的代码例子，参考了不少网上代码，特别参考了书林跋涉的
	VB版本
版    本：V1.0.0
*****************************************************************************************/

/*****************************************************************************************
 在源代码中需要 include Wave.h
 然后按以下步骤调用：
********************************************************************
1、创建水波对象：
要对一个窗口进行绘画，首先要创建一个水波对象（本函数申请一些缓冲区）
WaveInit(LPWAVEOBJECT lpWaveObject, HWND hWnd, HBITMAP hBmp, UINT dwSpeed, UINT dwType)
	lpWaveObject --> 指向一个空的 WAVE_OBJECT 结构
	hWnd --> 要绘画水波效果的窗口，渲染后的图片将画到窗口的客户区中
	hBmp --> 背景图片，绘画的范围大小同背景图片大小
	dwTime --> 刷新的时间间隔（毫秒），建议值：10～30
	dwType --> =0 表示圆形水波，=1表示椭圆型水波（用于透视效果）
	返回值：eax = 0（成功，对象被初始化），eax = 1（失败）
********************************************************************
 2、如果 WaveInit 函数返回成功，则对象被初始化，将对象传给下列各种函数
 可以实现各种效果，下面函数中的 lpWaveObject 参数指向在 WaveInit 函数
 中初始化的 WAVEOBJECT 结构。

	(1) 在指定位置“扔石头”，激起水波
	WaveDropStone(LPWAVEOBJECT lpWaveObject, int dwPosX, int dwPosY, int dwStoneSize,int dwStoneWeight);
		dwPosX,dwPosY --> 扔下石头的位置
		dwStoneSize --> 石头的大小，即初始点的大小，建议值：0～5
		dwStoneWeight --> 石头的重量，决定了波最后扩散的范围大小，建议值：10～1000

	(2) 自动显示特效
	WaveEffect(LPWAVEOBJECT lpWaveObject, UINT dwType,int dwParam1,int dwParam2,int dwParam3)
		dwParam1,dwParam2,dwParam3 --> 效果参数，对不同的特效类型参数含义不同
		dwEffectType --> 特效类型
		0 --> 关闭特效
		1 --> 下雨，Param1＝密集速度（0最密，越大越稀疏），建议值：0～30
			Param2＝最大雨点直径，建议值：0～5
                        Param3＝最大雨点重量，建议值：50～250
		2 --> 汽艇，Param1＝速度（0最慢，越大越快），建议值：0～8
                        Param2＝船大小，建议值：0～4
                        Param3＝水波扩散的范围，建议值：100～500
		3 --> 风浪，Param1＝密度（越大越密），建议值：50～300
                        Param2＝大小，建议值：2～5
                        Param3＝能量，建议值：5～10

	(3) 窗口客户区强制更新（用于在窗口的WM_PAINT消息中强制更新客户端）
	WaveUpdateFrame(LPWAVEOBJECT lpWaveObject, HDC hDc, BOOL bIfForce);
********************************************************************
 3、释放水波对象：
使用完毕后，必须将水波对象释放（本函数将释放申请的缓冲区内存等资源）
	WaveFree(LPWAVEOBJECT lpWaveObject)
	lpWaveObject --> 指向 WAVE_OBJECT 结构

实现上的细节说明：

1、 水波的特征：
   (1) 扩散：每一点的波会扩散到其四周的位置中
   (2) 衰减：每次扩散会损失少量能量（否则水波会永不停止的震荡下去）

2、 为了保存两个时刻中的能量分步图，对象中定义2个缓冲区Wave1和Wave2
（保存在lpWave1和lpWave2指向的缓冲区内），Wave1为当前数据，Wave2
为上一帧的数据，每次渲染时将根据上面的2个特征，由Wave1的数据计算出新
能量分别图后，保存到Wave2中，然后调换Wave1和Wave2，这时Wave1仍是
最新的数据。
	计算的方法为，某个点的能量＝点四周的上次能量的平均值 * 衰减系数取四
周的平均值表现了扩展特征，乘以衰减系数表现了衰减特征。
      这部分代码在WaveSpread 函数中实现。

 3、 对象在 lpDIBitsSource 中保存了原始位图的数据，每次渲染时，由原始位
 图的数据根据Wave1中保存的能量分步数据产生新的位图。从视觉上看，某个点
 的能量越大（水波越大），则光线折射出越远处的场景。
	算法为：对于点（x,y），在Wave1中找出该点，计算出相邻点的波能差
（Dx和Dy两个数据），则新位图像素（x,y）＝原始位图像素（x+Dx,y+Dy），该
算法表现了能量大小影响了像素折射的偏移大小。
      这部分代码在 WaveRender 子程序中实现。

 4、 扔石头的算法很好理解，即将Wave1中的某个点的能量值置为非0值，数值越
 大，表示扔下的石头的能量越大。石头比较大，则将该点四周的点全部置为非0值。

	本程序补充的资料见资料文件resource.txt。
	程序中的缓冲区采用一维数组，注释为了方便采用二维数组。当然，缓冲区采
用二维数组更加易于理解。
*****************************************************************************************/

#include "Wave.h"
#include "targetver.h"

/*****************************************************************************************
随机数产生子程序
 输入：要产生的随机数的最大值，输出：随机数
 根据：
 1. 数学公式 Rnd=(Rnd*I+J) mod K 循环回带生成 K 次以内不重复的
    伪随机数，但K,I,J必须为素数
 2. 2^(2n-1)-1 必定为素数（即2的奇数次方减1）
*****************************************************************************************/
DWORD WaveRandom16 (LPWAVEOBJECT lpWaveObject)
{
	DWORD dwRnd;
	dwRnd = ((lpWaveObject->dwRandom & 0xFFFF) * 0x7FF + 0x7F) % 0x7FFF;
	lpWaveObject->dwRandom = dwRnd;
	return (dwRnd & 0xFF);
}

DWORD WaveRandom (LPWAVEOBJECT lpWaveObject, DWORD dwMax)
{
	DWORD lRnd1, lRnd2, lRnd;
	lRnd1 = WaveRandom16 (lpWaveObject);
	lRnd2 = WaveRandom16 (lpWaveObject);

	if (dwMax == 0)
		lRnd = 0;
	else
		lRnd = (((lRnd2<<16)+lRnd1) % dwMax);

	return lRnd;
	
}

/*****************************************************************************************
 波能扩散
 算法：
椭圆扩散
 Wave2(x,y) = ((Wave1(x+1,y)+Wave1(x-1,y)+Wave1(x+2,y)+Wave1(x-2,y))*3+Wave1(x+3,y)*2+Wave1(x-3,y)*2+ Wave1(x,y+1)*8+Wave1(x,y-1)*8)\16-Wave2(x,y)
圆形扩散
 Wave2(x,y) = (Wave1(x+1,y)+Wave1(x-1,y)+Wave1(x,y+1)+Wave1(x,y-1))\2-Wave2(x,y)
 Wave2(x,y) = Wave2(x,y) - Wave2(x,y) >> 5
 交换 Wave1,Wave2
*****************************************************************************************/
void WaveSpread (LPWAVEOBJECT lpWaveObject)
{
	PINT lpWave1, lpWave2;
	int dwBmpWidth, dwBmpHeight;
	int i;

	if ((lpWaveObject->dwFlag & F_WO_ACTIVE) == 0)
		return;
	
	lpWave1 = lpWaveObject->lpWave1;
	lpWave2 = lpWaveObject->lpWave2;
	dwBmpWidth = lpWaveObject->dwBmpWidth;
	dwBmpHeight = lpWaveObject->dwBmpHeight;

	for (i = dwBmpWidth; i < (dwBmpHeight-1)*dwBmpWidth; i++) {
		if (lpWaveObject->dwFlag & F_WO_ELLIPSE) {//椭圆扩散
			lpWave2[i] = ((lpWave1[i+1] + lpWave1[i-1] + lpWave1[i+2] + lpWave1[i-2])*3 + (lpWave1[i+3] + lpWave1[i-3])*2 + (lpWave1[i+dwBmpWidth] + lpWave1[i-dwBmpWidth])*8)/16 - lpWave2[i];
		} else {//圆形扩散
			lpWave2[i] = (lpWave1[i+1] + lpWave1[i-1] + lpWave1[i+dwBmpWidth] + lpWave1[i-dwBmpWidth])/2 - lpWave2[i];
		}
		if (lpWave2[i] == 0) lpWave2[i] = 0;
		lpWave2[i] -= (lpWave2[i] >> 5);
	}

	lpWaveObject->lpWave1 = lpWave2;
	lpWaveObject->lpWave2 = lpWave1;
}

/*****************************************************************************************
' 渲染函数，将新的帧数据渲染到 lpDIBitsRender 中
 算法：
 posx = Wave1(x-1,y)-Wave1(x+1,y)+x
 posy = Wave1(x,y-1)-Wave1(x,y+1)+y
 SourceBmp(x,y) = DestBmp(posx,posy)
*****************************************************************************************/
void WaveRender (LPWAVEOBJECT lpWaveObject)
{
	int dwPosX, dwPosY, dwPtrSource, dwPtrDest;
	UINT dwFlag;
	PINT lpWave1;
	UINT LineIdx = lpWaveObject->dwBmpWidth;
	int dwBmpWidth = lpWaveObject->dwBmpWidth;
	PBYTE DIBitsSource = NULL;
	PBYTE DIBitsRender = NULL;
	int i, j, k;

	dwFlag = 0;
	if ((lpWaveObject->dwFlag & F_WO_ACTIVE) == 0) 
		return;
	lpWaveObject->dwFlag |= F_WO_NEED_UPDATE;
	lpWave1 = lpWaveObject->lpWave1;
	DIBitsSource = lpWaveObject->lpDIBitsSource;
	DIBitsRender = lpWaveObject->lpDIBitsRender;
	for (i = 1; i < lpWaveObject->dwBmpHeight-1; i++) {
		for (j = 0; j < lpWaveObject->dwBmpWidth; j++) {
			//计算偏移量
			//PosY=i+像素上1能量-像素下1能量
			//PosX=j+像素左1能量-像素右1能量
			dwPosY = i + lpWave1[LineIdx-dwBmpWidth] - lpWave1[LineIdx+dwBmpWidth];
			dwPosX = j + lpWave1[LineIdx-1] - lpWave1[LineIdx+1];

			//判断坐标是否在窗口范围内
			if (dwPosX < 0 || dwPosY < 0) goto Continue;
			if (dwPosX >= lpWaveObject->dwBmpWidth || dwPosY >= lpWaveObject->dwBmpHeight) goto Continue;

			//计算出偏移像素和原始像素的内存地址偏移量
			dwPtrSource = dwPosY*lpWaveObject->dwDIByteWidth + dwPosX*3;
			dwPtrDest = i*lpWaveObject->dwDIByteWidth + j*3;

			//渲染像素 [ptrDest] = 原始像素 [ptrSource]
			if (dwPtrSource != dwPtrDest) {
				dwFlag |= 1;	//如果存在源像素和目标像素不同，则表示还在活动状态
				for (k = 0; k < 3; k++) {
					DIBitsRender[dwPtrDest+k] = DIBitsSource[dwPtrSource+k];
					//DIBitsRender[dwPtrDest+k] = (DIBitsSource[dwPtrSource+k]*4 + (DIBitsSource[dwPtrSource+k-1] + 
					//	DIBitsSource[dwPtrSource+k+1] + DIBitsSource[dwPtrSource+k-lpWaveObject->dwDIByteWidth] +
					//	DIBitsSource[dwPtrSource+k+lpWaveObject->dwDIByteWidth])*3)/16;
				}
			} else {
				for (k = 0; k < 3; k++) {
					DIBitsRender[dwPtrDest+k] = DIBitsSource[dwPtrSource+k];
				}
			}

		Continue:
			LineIdx++;
		}
	}
	SetDIBits (lpWaveObject->hDcRender, lpWaveObject->hBmpRender, 0, lpWaveObject->dwBmpHeight, lpWaveObject->lpDIBitsRender, &lpWaveObject->stBmpInfo, DIB_RGB_COLORS);
	if (dwFlag = 0)
		lpWaveObject->dwFlag &= ~F_WO_ACTIVE;
}

//扔一块石头
void __stdcall WaveDropStone (LPWAVEOBJECT lpWaveObject, int dwX, int dwY, int dwStoneSize, int dwStoneWeight)
{
	int dwSize, dwX1, dwY1, dwX2, dwY2, dwY2_t;
	PINT lpWave1;

	//计算范围
	dwSize = dwStoneSize / 2;
	dwX1 = dwX + dwSize;
	dwX2 = dwX - dwSize;
	if (lpWaveObject->dwFlag & F_WO_ELLIPSE) dwSize /= 2;
	dwY1 = dwY + dwSize;
	dwY2 = dwY - dwSize;
	dwSize = dwStoneSize;
	if (dwSize == 0) dwSize = 1;
	
	//判断范围的合法性
	if (dwX1+1 >= lpWaveObject->dwBmpWidth || dwX2 < 1 || dwY1+1 >= lpWaveObject->dwBmpHeight || dwY2 < 1) return;

	//将范围内的点的能量置为 dwStoneWeight
	while (dwX2 <= dwX1) {
		dwY2_t = dwY2;
		while (dwY2 < dwY1) {
			if (((dwX2-dwX)*(dwX2-dwX) + (dwY2-dwY)*(dwY2-dwY))
				<= dwSize*dwSize) {
			lpWave1 = lpWaveObject->lpWave1 + (dwY2*lpWaveObject->dwBmpWidth + dwX2);
			*lpWave1 = dwStoneWeight;
			}
			dwY2++; 
		}
		dwX2++; dwY2 = dwY2_t;
	}
	lpWaveObject->dwFlag |= F_WO_ACTIVE;
}

void __stdcall  WaveUpdateFrame (LPWAVEOBJECT lpWaveObject, HDC hDc, BOOL bIfForce)
{
	if (bIfForce || (lpWaveObject->dwFlag & F_WO_NEED_UPDATE)) {
		BitBlt (hDc, 0, 0, lpWaveObject->dwBmpWidth, lpWaveObject->dwBmpHeight, lpWaveObject->hDcRender, 0, 0, SRCCOPY);
		lpWaveObject->dwFlag &= ~F_WO_NEED_UPDATE;
	}
}

//计算扩散数据、渲染位图、更新窗口、处理特效的定时器过程
void CALLBACK WaveTimerProc (HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	HDC hDc;
	int dwX, dwY, dwSize, dwWeight;
	int i;

	LPWAVEOBJECT lpWaveObject = (LPWAVEOBJECT) idEvent;
	WaveSpread (lpWaveObject);
	WaveRender (lpWaveObject);
	if (lpWaveObject->dwFlag & F_WO_NEED_UPDATE) {
		hDc = GetDC (lpWaveObject->hWnd);
		WaveUpdateFrame (lpWaveObject, hDc, FALSE);
		ReleaseDC (lpWaveObject->hWnd, hDc);
	}

	//特效处理
	if ((lpWaveObject->dwFlag & F_WO_EFFECT) == 0)
		return;
	switch (lpWaveObject->dwEffectType) {
	case 1:	//Type = 1 雨点，Param1＝速度（0最快，越大越慢），Param2＝雨点大小，Param3＝能量
		if (!lpWaveObject->dwEffectParam1 || !WaveRandom (lpWaveObject, lpWaveObject->dwEffectParam1)) {
			dwX = WaveRandom(lpWaveObject, lpWaveObject->dwBmpWidth-2) + 1;
			dwY = WaveRandom (lpWaveObject, lpWaveObject->dwBmpHeight-2) + 1;
			dwSize = WaveRandom (lpWaveObject, lpWaveObject->dwEffectParam2) + 1;			
			dwWeight = WaveRandom (lpWaveObject, lpWaveObject->dwEffectParam3) + 50;
			WaveDropStone (lpWaveObject, dwX, dwY, dwSize, dwWeight);
		}
		break;
	case 2:	//Type = 2 行船，Param1＝速度（0最快，越大越快），Param2＝大小，Param3＝能量
		lpWaveObject->dwEff2Flip++;
		if ((lpWaveObject->dwEff2Flip & 1) != 0) return;
		dwX = lpWaveObject->dwEff2X + lpWaveObject->dwEff2XAdd;
		dwY = lpWaveObject->dwEff2Y + lpWaveObject->dwEff2YAdd;
		if (dwX < 1) {
			dwX = -(dwX-1);
			lpWaveObject->dwEff2XAdd = -lpWaveObject->dwEff2XAdd;
		}
		if (dwY < 1) {
			dwY = -(dwY-1);
			lpWaveObject->dwEff2YAdd = -lpWaveObject->dwEff2YAdd;
		}
		if (dwX > lpWaveObject->dwBmpWidth-1) {
			dwX = (lpWaveObject->dwBmpWidth-1)*2 - dwX;
			lpWaveObject->dwEff2XAdd = -lpWaveObject->dwEff2XAdd;
		}
		if (dwY > lpWaveObject->dwBmpHeight-1) {
			dwY = (lpWaveObject->dwBmpHeight-1)*2 - dwY;
			lpWaveObject->dwEff2YAdd = -lpWaveObject->dwEff2YAdd;
		}
		lpWaveObject->dwEff2X = dwX;
		lpWaveObject->dwEff2Y = dwY;
		WaveDropStone (lpWaveObject, dwX, dwY, lpWaveObject->dwEffectParam2, lpWaveObject->dwEffectParam3);
		break;
	case 3:	//Type = 3 波浪，Param1＝密度，Param2＝大小，Param3＝能量
		for (i = 0; i <= lpWaveObject->dwEffectParam1; i++) {
		dwX = WaveRandom (lpWaveObject, lpWaveObject->dwBmpWidth-2) + 1;
		dwY = WaveRandom (lpWaveObject, lpWaveObject->dwBmpHeight-2) + 1;
		dwSize = WaveRandom (lpWaveObject, lpWaveObject->dwEffectParam2) + 1;
		dwWeight = WaveRandom (lpWaveObject, lpWaveObject->dwEffectParam3);
		WaveDropStone (lpWaveObject, dwX, dwY, dwSize, dwWeight);
		}
		break;
	}
}

//释放对象
void __stdcall WaveFree (LPWAVEOBJECT lpWaveObject)
{
	if (lpWaveObject->hDcRender)
		DeleteDC (lpWaveObject->hDcRender);
	if (lpWaveObject->hBmpRender)
		DeleteObject (lpWaveObject->hBmpRender);
	if (lpWaveObject->lpDIBitsSource)
		GlobalFree (lpWaveObject->lpDIBitsSource);
	if (lpWaveObject->lpDIBitsRender)
		GlobalFree (lpWaveObject->lpDIBitsRender);
	if (lpWaveObject->lpWave1)
		GlobalFree (lpWaveObject->lpWave1);
	if (lpWaveObject->lpWave2)
		GlobalFree (lpWaveObject->lpWave2);
	KillTimer (lpWaveObject->hWnd, (UINT_PTR) lpWaveObject);
	RtlZeroMemory (lpWaveObject, sizeof WAVEOBJECT);	
}

UINT __stdcall WaveInit (LPWAVEOBJECT lpWaveObject, HWND hWnd, HBITMAP hBmp, UINT dwSpeed, UINT dwType)
{
	BITMAP stBmp;
	UINT dwReturn = 0;
	HDC hDc = NULL;
	HDC hDcRender = NULL;
	
	RtlZeroMemory (lpWaveObject, sizeof (WAVEOBJECT));
	//dwType是水波图形的开关
	//dwType＝0时为圆形水波，dwType＝1时为椭圆形水波
	if (dwType)
		lpWaveObject->dwFlag = lpWaveObject->dwFlag | F_WO_ELLIPSE;
	
	//获取位图尺寸
	lpWaveObject->hWnd = hWnd;
	//GetTickCount返回从操作系统启动到现在所经过（elapsed）的毫秒数，
	//它的返回值是DWORD。 
	lpWaveObject->dwRandom = GetTickCount ();
	
	if (!GetObject (hBmp, sizeof (BITMAP), &stBmp)) {
		dwReturn = 1;
		goto result;
	}	
	lpWaveObject->dwBmpHeight = stBmp.bmHeight;
	if (stBmp.bmHeight <= 3) 
		dwReturn = 1;
	lpWaveObject->dwBmpWidth = stBmp.bmWidth;
	if (stBmp.bmWidth <= 3) 
		dwReturn = 1;
		
	lpWaveObject->dwWaveByteWidth = stBmp.bmWidth * 4;
	lpWaveObject->dwDIByteWidth = (stBmp.bmWidth * 3 + 3) & (~3);

	//创建用于渲染的位图
	hDc = GetDC (hWnd);
	//创建一个与指定设备兼容的内存设备上下文环境
	lpWaveObject->hDcRender = CreateCompatibleDC (hDc);
	//HBITMAP CreateCompatibleBitmap (HDC hDc, int cx, int cy); 
	//指定高、宽和色彩组合以满足CreateCompatibleDC调用的需要
	//该函数创建与指定的设备环境相关的设备兼容的位图
	lpWaveObject->hBmpRender = CreateCompatibleBitmap (hDc, 
		lpWaveObject->dwBmpWidth, lpWaveObject->dwBmpHeight);
	
	//该函数选择一对象到指定的设备上下文环境中，该新对象替换先前的相同类型的对象。 
	SelectObject (lpWaveObject->hDcRender, lpWaveObject->hBmpRender);
		
	//分配波能缓冲区
	lpWaveObject->lpWave1 = (PINT) GlobalAlloc (GPTR, 
		lpWaveObject->dwWaveByteWidth * lpWaveObject->dwBmpHeight);
	lpWaveObject ->lpWave2 = (PINT) GlobalAlloc (GPTR, 
		lpWaveObject->dwWaveByteWidth * lpWaveObject->dwBmpHeight);

	//分配像素缓冲区
	lpWaveObject->lpDIBitsSource = (PBYTE) GlobalAlloc (GPTR, 
		lpWaveObject->dwDIByteWidth * lpWaveObject->dwBmpHeight);
	lpWaveObject->lpDIBitsRender = (PBYTE) GlobalAlloc (GPTR, 
		lpWaveObject->dwDIByteWidth * lpWaveObject->dwBmpHeight);

	//获取像素原始数据
	lpWaveObject->stBmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
	lpWaveObject->stBmpInfo.bmiHeader.biWidth = lpWaveObject->dwBmpWidth;
	lpWaveObject->stBmpInfo.bmiHeader.biHeight =   - lpWaveObject->dwBmpHeight;
	lpWaveObject->stBmpInfo.bmiHeader.biPlanes = 1;
	lpWaveObject->stBmpInfo.bmiHeader.biBitCount = 24;
	lpWaveObject->stBmpInfo.bmiHeader.biCompression = BI_RGB;
	lpWaveObject->stBmpInfo.bmiHeader.biSizeImage = 0;

	hDcRender = CreateCompatibleDC (hDc);
	SelectObject (hDcRender, hBmp);
	ReleaseDC (hWnd, hDc);

	//GetDIBits函数检取指定位图的信息，并将其以指定格式复制到一个缓冲区中
	GetDIBits (hDcRender, hBmp, 0, lpWaveObject->dwBmpHeight, 
	lpWaveObject->lpDIBitsSource, &lpWaveObject->stBmpInfo, DIB_RGB_COLORS);
	GetDIBits (hDcRender, hBmp, 0, lpWaveObject->dwBmpHeight, 
	lpWaveObject->lpDIBitsRender, &lpWaveObject->stBmpInfo, DIB_RGB_COLORS);
	DeleteDC (hDcRender);

	if (!lpWaveObject->lpWave1 || !lpWaveObject->lpWave2 || !lpWaveObject->lpDIBitsSource || !lpWaveObject->lpDIBitsRender || !lpWaveObject->hDcRender) {
		MessageBox (hWnd, TEXT ("内存申请失败"), TEXT ("错误"), MB_OK);
		WaveFree (lpWaveObject);
		dwReturn = 1;
	}

	SetTimer (hWnd, (UINT_PTR) lpWaveObject, dwSpeed, WaveTimerProc);

	lpWaveObject->dwFlag = lpWaveObject->dwFlag | F_WO_ACTIVE | F_WO_NEED_UPDATE;
	WaveRender (lpWaveObject);
	hDc = GetDC (hWnd);
	WaveUpdateFrame (lpWaveObject, hDc, TRUE);
	ReleaseDC  (hWnd, hDc);
result:
	return dwReturn;
}

//特效函数
void __stdcall WaveEffect (LPWAVEOBJECT lpWaveObject, UINT dwEffectType, int dwParam1, int dwParam2, int dwParam3)
{
	switch (dwEffectType) {
	case 0:
		lpWaveObject->dwFlag &= ~F_WO_EFFECT;
		lpWaveObject->dwEffectType = dwEffectType;
		break;
	case 2:
		lpWaveObject->dwEff2XAdd = dwParam1;
		lpWaveObject->dwEff2YAdd = dwParam1;
		lpWaveObject->dwEff2X = WaveRandom (lpWaveObject, lpWaveObject->dwBmpWidth-2) + 1;
		lpWaveObject->dwEff2Y = WaveRandom (lpWaveObject, lpWaveObject->dwBmpHeight-2) + 1;
		lpWaveObject->dwEffectType = dwEffectType;
		lpWaveObject->dwEffectParam1 = dwParam1;
		lpWaveObject->dwEffectParam2 = dwParam2;
		lpWaveObject->dwEffectParam3 = dwParam3;
		lpWaveObject->dwFlag |= F_WO_EFFECT;
		break;
	default:
		lpWaveObject->dwEffectType = dwEffectType;
		lpWaveObject->dwEffectParam1 = dwParam1;
		lpWaveObject->dwEffectParam2 = dwParam2;
		lpWaveObject->dwEffectParam3 = dwParam3;
		lpWaveObject->dwFlag |= F_WO_EFFECT;
	}
}