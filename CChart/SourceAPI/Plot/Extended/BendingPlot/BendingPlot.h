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

#ifndef __BENDINGPLOT_H_122333444455555__
#define __BENDINGPLOT_H_122333444455555__

//#include "../../Basics/Origin.h"
#include <vector>
using namespace std;

typedef struct stBendingSect
{
	double z1;//
	double psi1;//normal direction along positive y
	double z2;//
	double psi2;//normal direction along positive y
}BendingSect;

typedef vector<BendingSect> vBendingSect;

class CBendingPlot
{
public:
	CBendingPlot();
	virtual ~CBendingPlot();
protected:
	double m_fDeltaAngle;

protected:
	vBendingSect m_vBendingSect;
	void ConvertData(double x, double y, double &xn, double &yn);
	bool GetCoodOfSect(int idx, double &x1, double &y1, double &x2, double &y2);
	void GetCoodOfZAxis(double z, double &x, double &y);
public:
	bool AddBendingSect(double z1, double psi1, double z2, double psi2);
};

#endif