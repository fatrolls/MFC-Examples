#include "StdAfx.h"
#include "PlotData.h"
#include <sstream>

void GetDataPoint(string aline, double &result)
{
	istringstream istr(aline);
	istr>>result;
}

void GetDataPoint(string aline, DataPoint2D &result)
{
	istringstream istr(aline);
	istr>>result.x>>result.y;
}

void GetDataPoint(string aline, DataPoint3D &result)
{
	istringstream istr(aline);
	istr>>result.x>>result.y>>result.z;
}

void GetDataLine(double datapoint, string &result)
{
	ostringstream ostr;
	ostr<<datapoint<<"\n";
	result = ostr.str();
}

void GetDataLine(DataPoint2D datapoint, string &result)
{
	ostringstream ostr;
	ostr<<datapoint.x<<"\t"<<datapoint.y<<"\n";
	result = ostr.str();
}
void GetDataLine(DataPoint3D datapoint, string &result)
{
	ostringstream ostr;
	ostr<<datapoint.x<<"\t"<<datapoint.y<<"\t"<<datapoint.z<<"\n";
	result = ostr.str();
}