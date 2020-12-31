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

#ifndef __NLFIT_32167_H__
#define __NLFIT_32167_H__

#include <math.h>

double sign(double val);
//用Gauss-Jordan消去法解线性方程组
void gaussj(double *a,int n,double *b,int &flag);
//残差平方和计算
double sum(double *pA,int cnum,double *pX,double *pY,int len,double *pErr);
//非线性拟和主程序
void nlfit(double *pA,int cnum,double *pX,double *pY,int len,double err,int iter,int method,int &fail);

//残差计算程序
double remain(double *pA,int cnum,double *pX,double *pY,int no);
//偏导数计算程序
void derivative(double *pA,double *pDiff,int cnum,double *pX,int no);

#endif