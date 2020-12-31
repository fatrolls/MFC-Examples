#pragma once

// 加载图片
bool LoadImage(const CString strPathFile, CBitmap &bitmap, CSize &size);	
// 加载图片
bool ImageFromIDResource(UINT nID, CString strType, Image * & pImg);
// 取得图片平均颜色
bool GetAverageColor(CDC *pDC, CBitmap &bitmap, const CSize &sizeImage, COLORREF &clrImage);
// 取得图片大小
bool GetSize(CBitmap &bitmap, CSize &size);


// 绘画函数

// 画垂直过渡
int DrawVerticalTransition(CDC &dcDes, CDC &dcSrc, const CRect &rcDes, const CRect &rcSrc, int nBeginTransparent = 0, int nEndTransparent = 100);
// 画水平过渡
int DrawHorizontalTransition(CDC &dcDes, CDC &dcSrc, const CRect &rcDes, const CRect &rcSrc, int nBeginTransparent = 0, int nEndTransparent = 100);
// 画右下角过渡
void DrawRightBottomTransition(CDC &dc, CDC &dcTemp, CRect rc, const int nOverRegio, const COLORREF clrBackground);
// 画图片边框
void DrawImageFrame(Graphics &graphics, Image *pIamge, const CRect &rcControl, int nX, int nY, int nW, int nH, int nFrameSide = 4);
// 画过渡圆角矩形
void DrawRectangle(CDC &dcDes, const CRect &rcDes, BOOL bUp = TRUE, int nBeginTransparent = 60, int nEndTransparent = 90);