// DaoSet.cpp : implementation of the CDAORecordset class
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCSTR lpcsPrimaryKey = "PrimaryKey";

/////////////////////////////////////////////////////////////////////////////
// CDAORecordset implementation

IMPLEMENT_DYNAMIC(CDAORecordset, CDaoRecordset)

CDAORecordset::CDAORecordset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
  m_OpenCount = 0;
  m_strKey = lpcsPrimaryKey;
}

CDAORecordset::~CDAORecordset()
{
  ASSERT(m_OpenCount == 0);
}

void CDAORecordset::Open(int nOpenType, LPCTSTR lpszSQL, int nOptions)
{
  if (m_OpenCount == 0)
  {
    CDaoRecordset::Open(nOpenType, lpszSQL, nOptions);
    if (!m_strKey.IsEmpty()) SetCurrentIndex(m_strKey);
    m_pDatabase->GetTableDefInfo(GetName(), m_TableDefInfo, AFX_DAO_ALL_INFO);
  }
  m_OpenCount++;
}

void CDAORecordset::Close()
{
  if (IsOpen())
  {
    if (m_OpenCount) m_OpenCount--;
    if (m_OpenCount == 0) CDaoRecordset::Close();
  }
  else ASSERT(m_OpenCount == 0);
}

long CDAORecordset::GetRecordCount()
{
  // refresh the TableDefInfo values
  m_pDatabase->GetTableDefInfo(GetName(), m_TableDefInfo, AFX_DAO_ALL_INFO);
  return m_TableDefInfo.m_lRecordCount;
}
