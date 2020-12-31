// MyWindow.cpp: implementation of the CMyWindow class.
//
//////////////////////////////////////////////////////////////////////
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com

#include "stdafx.h"
#include "ATLNewGrid.h"
#include "resource.h"
#include "MyWindow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyWindow::CMyWindow() : m_Cell(0)
{

}

CMyWindow::~CMyWindow()
{
}

void CMyWindow::SetCell(CGridCell *cell,
					 int row,
					 int col)
{
	m_Cell = cell;
	m_nCol = col;
	m_nRow = row;


}

void CMyWindow::StopEdit()
{
}
