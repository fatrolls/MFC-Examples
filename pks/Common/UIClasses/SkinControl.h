// SkinControl.h: interface for the CSkinControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINCONTROL_H__9968774D_F710_44D1_B9FC_CD4806086D4D__INCLUDED_)
#define AFX_SKINCONTROL_H__9968774D_F710_44D1_B9FC_CD4806086D4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GlobalConstants.h"

class CSkinControl
{
//Attributes
private:

//Attributes
protected:
	long m_lPaddingTop;
	long m_lPaddingLeft;
	int m_nCurrentState;
	int m_nUnPressedID;
	int m_nHoverID;
	int m_nPressedID;
	int m_nLeft;
	int m_nTop;
	int m_nWidth;
	int m_nHeight;
	CString m_csText;
	BOOL m_bEnabled;
	CWnd *m_pParentWnd;
	int m_nCommandID;
	UINT m_nControlID;
	BOOL m_bShape;

	CString m_csFontName;
	UINT m_nFontSize;
	UINT m_nFontStyle;
	COLORREF m_crBackgroundColorUnPressed;
	COLORREF m_crBackgroundColorPressed;
	COLORREF m_crBackgroundColorHover;
	COLORREF m_crForegroundColor;
	COLORREF m_crTextColor;
	CFont m_cfFaceTextFont;

	CDC m_dcMemory;
	CBitmap m_bmpMemory;

	long m_lImageWidth;
	long m_lImageHeight;

	CString m_csDLLFileName;
	long m_lTextAlign;

//Implementation
public:
	HBITMAP GetCurrentStateBitmap();
	HBITMAP m_hbmpDisabled;
	HBITMAP m_hbmpDown;
	HBITMAP m_hbmpHover;
	HBITMAP m_hbmpNormal;
	HBITMAP LoadGIF(HINSTANCE hInstance, LPCTSTR lpGIFName);
	void SetPadding(long lLeft, long lTop);
	COLORREF GetCurrentBackgroundColor();
	COLORREF GetTextColor() { return m_crTextColor; }
	COLORREF GetBackgroundColor(int nBackgroundState);
	void SetBackgroundColor(int nBackgroundState, COLORREF crColor);
	virtual void BltEx()=0;
	virtual CString GetControlText();	//gets the face text
	void SetForegroundColor(COLORREF crForeColor);
	void SetTextColor(COLORREF crTextColor=BLACK);
	void SetControlText(LPCTSTR lpszFaceText);	//setting the face text
	CSkinControl();
	virtual ~CSkinControl();

	void SetCurrentState(int nState);
	int GetCurrentState() const;

	int GetLeft() const;
	int GetTop() const;
	int GetWidth() const;
	int GetHeight() const;

	void SetCoordinates(int nLeft, int nTop);
	void SetDimensions(int nWidth, int nHeight);

	int GetControlID();
	int GetCommandID() const;
	virtual void SetEnabled(BOOL bEnabled);
	BOOL IsEnabled();

	virtual LPCTSTR SetFontName(LPCTSTR lpszFontFaceName);
	LPCTSTR GetFontName();
	virtual int SetFontSize(int nFontSize);
	virtual int GetFontSize();
	virtual int SetFontStyle(int nFontStyle);
	virtual int GetFontStyle();

	void SetImageResource(INT nUnPressedID=-1, INT nHoverID=-1, INT nPressedID=-1, INT nDisabledID=-1);
//Implementation
protected:
	HMODULE GetDllInstance(LPCTSTR lpModuleName);
	int GetDisabledID() const;
	COLORREF m_crBackgroundColorDisabled;
	int m_nReserved;
	int m_nDisabledID;
	LOGFONT m_lfFontStruct;
	UINT GetID() const;		//control ID
	int GetUnPressedID() const;
	int GetHoverID() const;
	int GetPressedID() const;
	void SetCommandID(int nID);
	BOOL PrepareFont();
	virtual int UpdateMemoryDC();
};

#endif // !defined(AFX_SKINCONTROL_H__9968774D_F710_44D1_B9FC_CD4806086D4D__INCLUDED_)
