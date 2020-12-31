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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is a templated class 

#ifndef __PLOTDATA_H_122333444455555__
#define __PLOTDATA_H_122333444455555__

//#include "Origin.h"
#include "../Accessary/Deelx/deelx.h"
#include "../Accessary/MyString/MyString.h"
#include <vector>
using namespace std;
#include <fstream>
#include <sstream>

typedef struct stDataPoint2D
{
	double x,y;
}DataPoint2D;

typedef struct stDataPoint3D
{
	double x,y,z;
}DataPoint3D;

typedef vector<double> MyVData1D;
typedef vector<DataPoint2D> MyVData2D;
typedef vector<DataPoint3D> MyVData3D;

void GetDataPoint(string aline, double &result);
void GetDataPoint(string aline, DataPoint2D &result);
void GetDataPoint(string aline, DataPoint3D &result);

void GetDataLine(double datapoint, string &result);
void GetDataLine(DataPoint2D datapoint, string &result);
void GetDataLine(DataPoint3D datapoint, string &result);

////////////////////////////////////////////////////////////////////////////////////////////

template<typename TypeT>
class CPlotData
{
public:
	CPlotData();
	virtual ~CPlotData();

protected:
	vector<TypeT>		m_vData;

	string				m_strTitle;
	string				m_strInfo;//Draw at the first point
	bool				m_bInfoDraw;
	int					m_nInfoFontsize;

	int					m_nDataLevel;
public:
	void				CopySettings(const CPlotData *plotdata);
	void				CopyAll(const CPlotData *plotdata);

	inline	const vector<TypeT>		&GetDataConst() const {return m_vData;}
	inline	vector<TypeT>			&GetData() {return m_vData;}
	inline	int						GetDataSize() {return m_vData.size();}

	void				DeleteData( void );
	inline string		GetTitle(){if(m_strTitle=="")return "Untitled";	else return m_strTitle;	};
	inline void			SetTitle(string title){m_strTitle=title;};
	inline string		GetInfo(){return m_strInfo;};
	inline void			SetInfo(string info){m_strInfo=info;};
	inline bool			IsInfoDraw(){return m_bInfoDraw;}
	inline void			SetInfoDraw(bool bDraw){m_bInfoDraw=bDraw;}
	inline int			GetInfoFontsize(){return m_nInfoFontsize;}
	inline void			SetInfoFontsize(int fontsize){if(fontsize>4)m_nInfoFontsize=fontsize;else m_nInfoFontsize=4;}
	inline int			GetDataLevel(){return m_nDataLevel;}
	inline void			SetDataLevel(int level){m_nDataLevel=level;}

	bool				SetData( vector<TypeT> vData );

	bool				ReadFromFile(string filename);
//	bool				WriteToFile(FILE *fp);
	bool				WriteToFile(ofstream &ofs);
	bool				WriteToFile(string filename);
	bool				AppendToFile(string filename);
};

template<typename TypeT>
CPlotData<TypeT>::CPlotData()
{
	m_strTitle = "Untitled";
	m_strInfo = "";
	m_bInfoDraw = false;
	m_nInfoFontsize = 12;
	
	m_nDataLevel = -1;
}

template<typename TypeT>
CPlotData<TypeT>::~CPlotData()
{
	DeleteData();
}

template<typename TypeT>
void CPlotData<TypeT>::CopySettings(const CPlotData* plotdata)
{
	m_strTitle = plotdata->m_strTitle;
	m_strInfo = plotdata->m_strInfo;
	m_bInfoDraw = plotdata->m_bInfoDraw;
	m_nInfoFontsize = plotdata->m_nInfoFontsize;
	m_nDataLevel = plotdata->m_nDataLevel;
}

template<typename TypeT>
void CPlotData<TypeT>::CopyAll(const CPlotData* plotdata)
{
	CopySettings(plotdata);
	m_vData = plotdata->m_vData;
}

// Delete the data set
template<typename TypeT>
void CPlotData<TypeT>::DeleteData(void)
{
	// Check if valid data. If so, delete it
	m_strTitle = "";
	m_vData.clear();
}

template<typename TypeT>
bool CPlotData<TypeT>::SetData(vector<TypeT> vData)
{
	if (vData.size() <= 0)
		return false;
	m_vData.clear();
	m_vData = vData;
	return true;
}

template<typename TypeT>
bool CPlotData<TypeT>::ReadFromFile(string filename)
{
//	FILE *fp = fopen(filename.c_str(),"r+b");
//	if(fp == 0)return false;

	ifstream ifs;
	ifs.open(filename.c_str());
	if(!ifs.is_open())return false;
	

	int	num = sizeof(TypeT)/sizeof(double);
	if(num<=0 || num>3)return false;

	ostringstream pattern;
	if(num==1)
	{
		pattern<<"^\\s*-?\\d+(.\\d*)\\s*$";
	}
	else if(num==2)
	{
		pattern<<"^(\\s*-?\\d+(.\\d*)){2}\\s*$";
	}
	else if(num==3)
	{
		pattern<<"^(\\s*-?\\d+(.\\d*)){3}\\s*$";
	}
	
	int filesize=get_file_size(filename.c_str());
	char *pBuff=new char[filesize+1];
	memset(pBuff,0,(filesize+1)*sizeof(char));
	ifs.read(pBuff,filesize);
	string content=pBuff;
	delete []pBuff;

	string aline;
	string pat=pattern.str();
	CRegexpT <char> dataline(pat.c_str());
	MatchResult rst1;
	int match1;

	TypeT datapoint;

	m_strTitle="Untitled";

	vector<TypeT> vData;
	string value;
	string::size_type curpos;

	curpos=0;
	do
	{
		aline=readline(content,curpos);
		rst1=dataline.MatchExact(aline.c_str());
		match1=rst1.IsMatched();
		if(match1)
		{
			GetDataPoint(aline, datapoint);
			vData.push_back(datapoint);
		}
	}while(curpos>0);

	//fclose(fp);
	ifs.close();
	if(vData.size()<=0)
	{
		return false;
	}
	else
	{
		m_vData.clear();
		m_vData = vData;
		return true;
	}
}
/*
template<typename TypeT>
bool	CPlotData<TypeT>::WriteToFile(FILE *fp)
{
	if(!fp || m_vData.size()<=0)
		return false;
	
	string aline,content;
	int i;
	
	for(i=0; i<m_vData.size(); i++)
	{
		GetDataLine(m_vData[i], aline);
		content += aline;
	}
	fputs(content.c_str(), fp);
	return true;
}
*/
template<typename TypeT>
bool	CPlotData<TypeT>::WriteToFile(ofstream &ofs)
{
	if(!ofs.is_open() || m_vData.size()<=0)
		return false;
	
	string aline,content;
	int i;
	
	for(i=0; i<(int)m_vData.size(); i++)
	{
		GetDataLine(m_vData[i], aline);
		content += aline;
	}
	//fputs(content.c_str(), fp);
	ofs.write(content.c_str(), content.length());
	return true;
}

template<typename TypeT>
bool	CPlotData<TypeT>::WriteToFile(string filename)
{
	if(m_vData.size()<=0)
		return false;
	ofstream ofs;
	ofs.open(filename.c_str());
	if(!ofs.is_open())return false;
	bool ret = WriteToFile(ofs);
	ofs.close();
/*	FILE *fp = fopen(filename.c_str(),"w+");
	if(fp==0)return false;
	bool ret = WriteToFile(fp);
	fclose(fp);*/
	return ret;
}

template<typename TypeT>
bool	CPlotData<TypeT>::AppendToFile(string filename)
{
	if(m_vData.size()<=0)
		return false;

	ofstream ofs;
	ofs.open(filename.c_str(),ios::app);
	if(!ofs::is_open())return false;
	bool ret = WriteToFile(ofs);
	ofs.close();
/*	
	FILE *fp = fopen(filename.c_str(),"a+");
	if(fp==0)return false;
	bool ret = WriteToFile(fp);
	fclose(fp);*/
	return ret;
}

#endif