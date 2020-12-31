#pragma once
#include "..\Base\ControlBase.h"

// °´Å¥×´Ì¬
enum enumPhotoFrameState
{
	pfNormal = 0,
	pfHover,
	pfDown,
	pfDisable
};

class CPhotoFrame : public CControlBase
{
public:
	CPhotoFrame(HWND hWnd, UINT uControlID, CRect rc, CString strTitle = "", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bRresponse = FALSE);
	bool SetImageBitmap(UINT nResourceID);
	bool SetImageBitmap(CString strImage);
	bool SetFrameBitmap(UINT nResourceID);
	bool SetFrameBitmap(CString strImage);
	~CPhotoFrame(void);
protected:
	void Draw(CDC &dc, CRect rcUpdate);
	
public:
	CString m_strFileImage;
	Image *m_pImage;
	Image *m_pFrameImage;
	CSize m_sizeImage;
	CSize m_sizeFrameImage;
	enumPhotoFrameState m_state;
};