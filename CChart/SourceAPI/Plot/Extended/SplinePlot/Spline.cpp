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
#include "Spline.h"

#include "../../Accessary/Numerical/NlFit/NlFit.h"

void ClearAdjoinCoincide(MyVData2D& vData)
{
	if (vData.size() <= 1)
		return;
	for (int i = vData.size() - 1; i >= 1; i--)
	{
		if (vData[i].x == vData[i - 1].x && vData[i].y == vData[i - 1].y)
			vData.erase(vData.begin() + i);
	}
}

CSpline::CSpline()
{
	m_nSegments=10;
	m_nEdgeMode=kSplEdgeModeFree;
	m_dpTanStart.x=0.0;
	m_dpTanStart.y=0.0;
	m_dpTanEnd.x=0.0;
	m_dpTanEnd.y=0.0;
}

CSpline::~CSpline()
{
}

DataPoint2D CSpline::GetEdgePoint(int realIdx, const MyVData2D &vData)
{
	int nPt=vData.size();
	if(nPt<3)return vData[0];

	DataPoint2D datapoint;

	switch(m_nEdgeMode)
	{
	case kSplEdgeModeClose:
		if(realIdx<=-2)
			return vData[nPt-2];
		else if(realIdx==-1)
			return vData[nPt-1];
		else if(realIdx==nPt)
			return vData[0];
		else if(realIdx>=nPt+1)
			return vData[1];
		else
			return vData[realIdx];
	case kSplEdgeModeTangent:
		if(realIdx>=0 && realIdx<=nPt-1)
			return vData[realIdx];
		else if(realIdx<=-1)
		{
			datapoint.x=vData[1].x-m_dpTanStart.x;
			datapoint.y=vData[1].y-m_dpTanStart.y;
			return datapoint;
		}
		else if(realIdx>=nPt)
		{
			datapoint.x=vData[nPt-2].x+m_dpTanEnd.x;
			datapoint.y=vData[nPt-2].y+m_dpTanEnd.y;
			return datapoint;
		}
	default:
		if(realIdx<=-1)
			return vData[0];
		else if(realIdx>=nPt)
			return vData[nPt-1];
		else
			return vData[realIdx];
	}
}

DataPoint2D CSpline::GetBSplCtrlPoint(const MyVData2D &vData,int index,int order,bool bLeft)
{
	DataPoint2D datapoint;
	datapoint.x=0.0;
	datapoint.y=0.0;

	if(order<2)return datapoint;
	if((int)vData.size()<=order)return datapoint;

	if(index<0 || index+order>=(int)vData.size())return datapoint;//n阶共有n+1个点参与计算

	int nSeg=GetSegments();
	SetSegments(1);
	if(bLeft)
	{
		GetBSplineValue(datapoint,vData,index,order,0);
	}
	else
	{
		GetBSplineValue(datapoint,vData,index,order,GetSegments());
	}
	SetSegments(nSeg);

	return datapoint;
}

double CSpline::GetXLength(const MyVData2D &vData)
{
	if(vData.size()<=1)return 0.0;
	
	double length=0.0;

	for(int i=0;i<=(int)vData.size()-2;i++)
	{
		length+=fabs(vData[i+1].x-vData[i].x);
	}
	return length;
}

bool CSpline::Tridag(double *a,double *b,double *c,double *r,double *u,int n)
{
	bool retval=false;
	if(n<3)return retval;

	double *gam=new double[n];

	if(b[0]==0)
	{
		delete []gam;
		return retval;
	}

	double bet=b[0];
	u[0]=r[0]/bet;

	int j;

	for(j=1;j<n;j++)
	{
		gam[j-1]=c[j-1]/bet;
		bet=b[j]-a[j]*gam[j-1];
		if(bet==0.0)
		{
			delete []gam;
			return retval;
		}
		u[j]=(r[j]-a[j]*u[j-1])/bet;
	}
	for(j=n-2;j>=0;j--)
	{
		u[j]=u[j]-gam[j]*u[j+1];
	}

	delete []gam;
	retval=true;
	return retval;
}

bool CSpline::GetParSplineValue(DataPoint2D &val,const MyVData2D &vData,int idxLeft,int idxSeg)
{
	bool retval=false;

	int nPt=vData.size();
	if(nPt<3)return retval;

	double t,t1,t2,t3;
	double a,b,c,d;
	t=0.5/m_nSegments;
	t1=t*idxSeg;
	t2=t1*t1;
	t3=t2*t1;

	a=4.0*t2-t1-4.0*t3;
	b=1.0-10.0*t2+12.0*t3;
	c=t1+8.0*t2-12.0*t3;
	d=4.0*t3-2.0*t2;

	double x0,x1,x2,x3,y0,y1,y2,y3;
	DataPoint2D datapoint;
	if(idxLeft-1>=0)
	{
		x0=vData[idxLeft-1].x;y0=vData[idxLeft-1].y;
	}
	else
	{
		datapoint=GetEdgePoint(idxLeft-1,vData);
		x0=datapoint.x;y0=datapoint.y;
	}

	x1=vData[idxLeft].x;y1=vData[idxLeft].y;
	x2=vData[idxLeft+1].x;y2=vData[idxLeft+1].y;
	if(idxLeft+2<=nPt-1)
	{
		x3=vData[idxLeft+2].x;y3=vData[idxLeft+2].y;
	}
	else
	{
		datapoint=GetEdgePoint(idxLeft+2,vData);
		x3=datapoint.x;y3=datapoint.y;
	}
	val.x=a*x0+b*x1+c*x2+d*x3;
	val.y=a*y0+b*y1+c*y2+d*y3;

	retval=true;
	return retval;
}

bool CSpline::GetCubicSplineValue(DataPoint2D &val,const MyVData2D &vData,int idxLeft,int idxSeg)
{
	bool retval=false;

	int nPt=vData.size();
	if(nPt<3)return retval;
	if(idxLeft<0 || idxLeft>=nPt-1)return retval;

	int i;
	double tt,B1,B2,B3,B4,p1,p2,p1p,p2p;

	double *t,*a,*b,*c,*rx,*ry,*ux,*uy;
	t=new double[nPt];
	a=new double[nPt];
	b=new double[nPt];
	c=new double[nPt];
	rx=new double[nPt];
	ry=new double[nPt];
	ux=new double[nPt];
	uy=new double[nPt];

	for(i=1;i<nPt;i++)
	{
		t[i]=sqrt((vData[i].x-vData[i-1].x)*(vData[i].x-vData[i-1].x)
			+(vData[i].y-vData[i-1].y)*(vData[i].y-vData[i-1].y));
		if(fabs(t[i])<=1.0e-15)goto CubicRet;
	}
	tt=idxSeg*t[idxLeft+1]/m_nSegments;

	
	switch(m_nEdgeMode)
	{
	case kSplEdgeModeClamp:
		a[0]=0.0;
		b[0]=1.0;
		c[0]=0.0;
		rx[0]=m_dpTanStart.x;
		ry[0]=m_dpTanStart.y;

		a[nPt-1]=0.0;
		b[nPt-1]=1.0;
		c[nPt-1]=0.0;
		rx[nPt-1]=m_dpTanEnd.x;
		ry[nPt-1]=m_dpTanEnd.y;
		break;
	default:
		a[0]=0.0;
		b[0]=1.0;
		c[0]=0.5;
		rx[0]=3.0*(vData[1].x-vData[0].x)/(2.0*t[1]);
		ry[0]=3.0*(vData[1].y-vData[0].y)/(2.0*t[1]);

		a[nPt-1]=1.0;
		b[nPt-1]=2.0;
		c[nPt-1]=0.0;
		rx[nPt-1]=3.0*(vData[nPt-1].x-vData[nPt-2].x)/t[nPt-1];
		ry[nPt-1]=3.0*(vData[nPt-1].y-vData[nPt-2].y)/t[nPt-1];
		break;
	}
	for(i=1;i<nPt-1;i++)
	{
		a[i]=t[i+1];
		b[i]=2.0*(t[i+1]+t[i]);
		c[i]=t[i];

		rx[i]=3.0*(t[i]/t[i+1]*(vData[i+1].x-vData[i].x)+t[i+1]/t[i]*(vData[i].x-vData[i-1].x));
		ry[i]=3.0*(t[i]/t[i+1]*(vData[i+1].y-vData[i].y)+t[i+1]/t[i]*(vData[i].y-vData[i-1].y));
	}

	if(!Tridag(a,b,c,rx,ux,nPt))goto CubicRet;
	if(!Tridag(a,b,c,ry,uy,nPt))goto CubicRet;

	p1=vData[idxLeft].x;
	p2=vData[idxLeft+1].x;
	switch(m_nEdgeMode)
	{
	case kSplEdgeModeClamp:
		if(idxLeft==0)
			p1p=m_dpTanStart.x;
		else
			p1p=ux[idxLeft];
		if(idxLeft==nPt-2)
			p2p=m_dpTanEnd.x;
		else
			p2p=ux[idxLeft+1];
		break;
	default:
		p1p=ux[idxLeft];
		p2p=ux[idxLeft+1];
		break;
	}
	B1=p1;
	B2=p1p;
	B3=3.0*(p2-p1)/(t[idxLeft+1]*t[idxLeft+1])-2.0*p1p/t[idxLeft+1]-p2p/t[idxLeft+1];
	B4=2.0*(p1-p2)/(t[idxLeft+1]*t[idxLeft+1]*t[idxLeft+1])+p1p/(t[idxLeft+1]*t[idxLeft+1])+p2p/(t[idxLeft+1]*t[idxLeft+1]);
	val.x=B1+B2*tt+B3*tt*tt+B4*tt*tt*tt;

	p1=vData[idxLeft].y;
	p2=vData[idxLeft+1].y;
	switch(m_nEdgeMode)
	{
	case kSplEdgeModeClamp:
		if(idxLeft==0)
			p1p=m_dpTanStart.y;
		else
			p1p=uy[idxLeft];
		if(idxLeft==nPt-2)
			p2p=m_dpTanEnd.y;
		else
			p2p=uy[idxLeft+1];
		break;
	default:
		p1p=uy[idxLeft];
		p2p=uy[idxLeft+1];
		break;
	}
	B1=p1;
	B2=p1p;
	B3=3.0*(p2-p1)/(t[idxLeft+1]*t[idxLeft+1])-2.0*p1p/t[idxLeft+1]-p2p/t[idxLeft+1];
	B4=2.0*(p1-p2)/(t[idxLeft+1]*t[idxLeft+1]*t[idxLeft+1])+p1p/(t[idxLeft+1]*t[idxLeft+1])+p2p/(t[idxLeft+1]*t[idxLeft+1]);
	val.y=B1+B2*tt+B3*tt*tt+B4*tt*tt*tt;

	retval=true;

CubicRet:
	delete []t;
	delete []a;
	delete []b;
	delete []c;
	delete []rx;
	delete []ry;
	delete []ux;
	delete []uy;

	return retval;
}

bool CSpline::GetBezierSplineValue(DataPoint2D &val,const MyVData2D &vData,int idxSeg)
{
	bool retval=false;
	int nPt=vData.size();
	if(nPt<3)return retval;

	double t=idxSeg/(double)m_nSegments;

	val.x=0.0;
	val.y=0.0;

	double bern=1.0;

	for(int i=0;i<nPt;i++)
	{
		//val.x+=vData[i].x*Bernstain(nPt-1,i,t);
		//val.y+=vData[i].y*Bernstain(nPt-1,i,t);
		//调用Bernstain函数效率较低，改算法
		if(i==0)
		{
			bern=pow(1.0-t,nPt-1);
		}
		else
		{
			if(fabs(1.0-t)>=1.0e-15)
			{
				bern*=((double)(nPt-1-i+1)/i)*t/(1.0-t);
			}
			else
			{
				bern= (i<nPt-1)?0.0:1.0;
			}

		}
		val.x+=vData[i].x*bern;
		val.y+=vData[i].y*bern;
	}
	retval=true;
	return retval;
}

double CSpline::Bernstnew(int n,int k,double t)
{
	double val=0,dv;
	double comb=1.0;
	for(int j=0;j<=n-k;j++)
	{
		//dv=Combination(n+1,j)*pow(t+n-k-j,n);
		//if(j%2==1)dv*=-1.0;
		//优化算法
		if(j==0)
		{
			comb=1.0;
			dv=pow(t+n-k,n);
		}
		else
		{
			comb*=(double(n+1-j+1)/j);
			dv=comb*pow(t+n-k-j,n);
		}
		if(j%2==1)dv*=-1.0;

		val+=dv;
	}
	return val/Factorial(n);
}

bool CSpline::GetBSplineValue(DataPoint2D &val,const MyVData2D &vData,int nIndex,int nOrder,int idxSeg)
{
	bool retval=false;

	int nPt=vData.size();
	if(nPt<nIndex+nOrder+1)return retval;

	double t;
	t=1.0/m_nSegments*idxSeg;
	val.x=0.0;
	val.y=0.0;
	double bern;
	for(int i=nIndex; i<=nIndex+nOrder; i++)
	{
		bern=Bernstnew(nOrder,i-nIndex,t);
		val.x+=vData[i].x*bern;
		val.y+=vData[i].y*bern;
	}
	retval=true;

	return retval;
}

bool CSpline::GetLeastSqualValue(DataPoint2D &val,const MyVData2D &vData,int nOrder)
{
	bool retval=false;

	int nPt=vData.size();
	if(nPt<3)return retval;
	if(nOrder<2)return retval;

	double *a,*b;
	a=new double[(nOrder+1)*(nOrder+1)];
	b=new double[nOrder+1];

	int i,j,k,l;

	double sum;
	for(k=0;k<=2*nOrder;k++)
	{
		if(k==0)
		{
			sum=vData.size();
			a[0*(nOrder+1)+nOrder]=sum;
			continue;
		}

		sum=0.0;
		for(l=0;l<nPt;l++)
		{
			sum+=pow(vData[l].x,k);
		}
		for(i=0;i<=nOrder;i++)
		{
			for(j=0;j<=nOrder;j++)
			{
				if(j-i==nOrder-k)
				{
					a[i*(nOrder+1)+j]=sum;
				}
			}
		}
	}
	for(i=0;i<=nOrder;i++)
	{
		sum=0.0;
		for(j=0;j<nPt;j++)
		{
			if(i==0)
				sum+=vData[j].y;
			else
				sum+=vData[j].y*pow(vData[j].x,i);
		}
		b[i]=sum;
	}

	int flag;
	gaussj(a,nOrder+1,b,flag);
	if(flag)
	{
		goto LeastSqualRet;
	}

	val.y=0;
	for(i=0;i<=nOrder;i++)
	{
		val.y+=b[i]*pow(val.x,nOrder-i);
	}
	retval=true;

LeastSqualRet:
	delete []a;
	delete []b;

	return retval;
}