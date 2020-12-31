/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2011 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */

#include "stdafx.h"
#include "nlfit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//残差计算程序
//函数：a1+a2*exp(-( (x-a3)/a4 )^2/2)
//pA:待求参数
//cnum:待求参数个数
//pX:自变量
//pY:因变量
//no:序号
double remain(double *pA,int cnum,double *pX,double *pY,int no)
{
	/*double a1,a2,a3,a4;
	double val,x,y;

	a1=pA[0];
	a2=pA[1];
	a3=pA[2];
	a4=pA[3];

	x=pX[no];
	y=pY[no];

	val=a1+a2*exp(-pow((x-a3)/a4,2)/2);

	return y-val;*/
	double val,x,y;
	int i;

	x=pX[no];
	y=pY[no];

	val=pA[0];
	for(i=1;i<cnum;i+=3)
	{
		val+=pA[i]*exp(-pow((x-pA[i+1])/pA[i+2],2)/2);
	}
	return y-val;
}

//对系数的偏导数计算程序
//函数：a1+a2*exp(-( (x-a3)/a4 )^2/2)
//pA:待求参数
//pDiff:偏导数
//cnum:待求参数个数
//pX:自变量
//no:数据序号
void derivative(double *pA,double *pDiff,int cnum,double *pX,int no)
{
	/*double a1,a2,a3,a4;
	double x,tmp;

	a1=pA[0];
	a2=pA[1];
	a3=pA[2];
	a4=pA[3];

	x=pX[no];

	tmp=exp(-pow((x-a3)/a4,2)/2);

	pDiff[0]=1;
	pDiff[1]=tmp;
	pDiff[2]=a2*tmp*(x-a3)/(a4*a4);
	pDiff[3]=a2*tmp*(x-a3)*(x-a3)/(a4*a4*a4);

	return;*/
	double x,tmp;
	int i;

	x=pX[no];

	pDiff[0]=1;
	for(i=1;i<cnum;i++)
	{
		pDiff[i]=0;
	}
	for(i=1;i<cnum;i+=3)
	{
		tmp=exp(-pow((x-pA[i+1])/pA[i+2],2)/2);

		pDiff[i]+=tmp;
		pDiff[i+1]+=pA[i]*tmp*(x-pA[i+1])/(pA[i+2]*pA[i+2]);
		pDiff[i+2]+=pA[i]*tmp*(x-pA[i+1])*(x-pA[i+1])/(pA[i+2]*pA[i+2]*pA[i+2]);
	}

	return;
}