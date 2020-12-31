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

#include "StdAfx.h"
#include "BendingPlotImpl.h"

CBendingPlotImpl::CBendingPlotImpl()
{

}

CBendingPlotImpl::~CBendingPlotImpl()
{

}

void CBendingPlotImpl::InitBendingAxis()
{
	if(m_vBendingSect.size()<=0)return;
	DeleteAllData();

	//calculate points firstly
	int i,j,cnt,np=1;
	for(i=0; i<(int)m_vBendingSect.size(); i++)
	{
		if(m_vBendingSect[i].psi1==m_vBendingSect[i].psi2)
		{
			np++;
		}
		else
		{
			np+=(int)ceil( (m_vBendingSect[i].psi2-m_vBendingSect[i].psi1)/m_fDeltaAngle );
		}
	}
	double *px, *py;
	px = new double[np];
	py = new double[np];

	cnt=0;
	px[cnt]=m_vBendingSect[0].z1;
	py[cnt]=0;
	cnt++;

	double x,y,z;
	for(i=0; i<(int)m_vBendingSect.size(); i++)
	{
		if(m_vBendingSect[i].psi1==m_vBendingSect[i].psi2)
		{
			GetCoodOfZAxis(m_vBendingSect[i].z2, x, y);
			px[cnt]=x;
			py[cnt]=y;
			cnt++;
		}
		else
		{
			z=m_vBendingSect[i].z1;
			int cs=(int)ceil( (m_vBendingSect[i].psi2-m_vBendingSect[i].psi1)/m_fDeltaAngle );
			for(j=1; j<=cs; j++)
			{
				z+=(m_vBendingSect[i].z2-m_vBendingSect[i].z1)/cs;
				GetCoodOfZAxis(z,x,y);
				px[cnt]=x;
				py[cnt]=y;
				cnt++;
			}
		}
	}

	int dataID = CXYPlot::AddCurve(px, py, np);
	SetDataTitle(dataID, "Bending Axis");

	delete []px;
	delete []py;
}

int CBendingPlotImpl::AddCurve( double *pX, double *pY, int nLen )
{
	if(!pX || !pY || nLen<=0)
	{
		return -1;
	}

	double *pxn,*pyn;
	pxn = new double[nLen];
	pyn = new double[nLen];

	int i, dataID;
	for(i=0; i<nLen; i++)
	{
		ConvertData(pX[i], pY[i], pxn[i], pyn[i]);
	}
	dataID=CXYPlot::AddCurve(pxn, pyn, nLen);

	delete []pxn;
	delete []pyn;

	return dataID;
}
