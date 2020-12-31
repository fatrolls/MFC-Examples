 
//CProSliderCtrl .h

#pragma once

#define WM_FREEZE WM_USER+0xF003
// CProSliderCtrl

class CProSliderCtrl : public CSliderCtrl
{
 DECLARE_DYNAMIC(CProSliderCtrl)
public: // Progress Control functions
 // Gets the current lower and upper limits, or range, of the progress bar control.
 void _GetRange(int& nLower, int& nUpper);
 // Sets the upper and lower limits of the progress bar control's range and redraws the bar to reflect the new ranges.
 void _SetRange(short nLower, short nUpper);
 // Sets the upper and lower limits of the progress bar control's range and redraws the bar to reflect the new ranges.
 void _SetRange32(int nLower, int nUpper);
 // Sets the background color for the progress bar. 
 COLORREF _SetBkColor(COLORREF clrNew);
 // Sets the thumb color
 COLORREF _SetThumbColor(COLORREF clrNew);
 // Sets the channel color
 COLORREF _SetChColor(COLORREF clrNew);
 // Gets the current position of the progress bar.
 int _GetPos(void);
 // Advances the current position of a progress bar control by a specified increment and redraws the bar to reflect the new position.
 int _OffsetPos(int nPos);
 // Sets the current position for a progress bar control and redraws the bar to reflect the new position.
 int _SetPos(int nPos);
 // Specifies the step increment for a progress bar control.
 int _SetStep(int nStep);
 // Advances the current position for a progress bar control by the step increment and redraws the bar to reflect the new position.
 int _StepIt(void);
 // De/Freezes the slider and returns the prev. state
 BOOL Freeze(void);
 // Enables/Disables borders
 HRESULT _EnableBorders(BOOL bEnable=TRUE);
 BOOL _IsEnabled(void);
public:
 CProSliderCtrl();
 virtual ~CProSliderCtrl();
protected:
 DECLARE_MESSAGE_MAP()
 // General Purpose Draw Function
 void Draw(LPNMCUSTOMDRAW pNMCD);
 void RecursiveRect(CDC *pDC, CRect rc, COLORREF nClr, BOOL First=FALSE);
 void RecursiveChannel(CDC *pDC, CRect rc, COLORREF nClr,
  BOOL First=FALSE, BOOL Vertical=FALSE,BYTE StepSize=20);
protected: // Progress Control variables
 // Progress bar background color
 COLORREF m_ProBkColor;
 // Progress bar color;
 COLORREF m_ProgressBarColor;
 // Progress bar ranges
 PBRANGE m_ProRange; 
 // Progress bar position
 int m_ProgressPos;
 // Step increment for Progress control
 int m_ProgressStep;
 // Direction, V/H
 DWORD m_Direction;
 // Thumb Color when mouse is over
 COLORREF m_ThClOver;
 // Thumb Color when mouse is out
 COLORREF m_ThClOut;
 // Thumb Color when mouse is pressed
 COLORREF m_ThClPre;
 // Thumb Default Color
 COLORREF m_ThClDef;
 // Borders
 BOOL m_bBorders;
 // Slider Freezed?
 BOOL m_bFreezed;
 // Temproray color storages
 COLORREF tmp1,tmp2;
 BOOL m_bBlink;
public:
 afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
protected:
 // Draws the slider thumb
 HRESULT DrawSliderThumb(LPNMCUSTOMDRAW pNMCD);
 HRESULT DrawSliderBorder(LPNMCUSTOMDRAW pNMCD);
 HRESULT DrawSliderChannel(LPNMCUSTOMDRAW pNMCD);
 void SetThumbColor(COLORREF nClr);
public:
 afx_msg void OnMouseMove(UINT nFlags, CPoint point);
 afx_msg void OnTimer(UINT nIDEvent);
 afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


