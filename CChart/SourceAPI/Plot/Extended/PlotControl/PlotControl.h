#ifndef __PLOTCONTROL_H_122333444455555__
#define __PLOTCONTROL_H_122333444455555__

#define WM_SETPLOTDATA		WM_USER+600
#define WM_SETPLOTTITLE		WM_USER+601
#define WM_SETAXISTITLE		WM_USER+602

typedef struct stPlotData
{
	double *pX;
	double *pY;
	int	nLen;
}PlotData;

ATOM RegisterPlotControl();

#endif