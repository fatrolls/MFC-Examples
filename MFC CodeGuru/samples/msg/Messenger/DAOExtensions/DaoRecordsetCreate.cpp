//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================


#include "StdAfx.h"
#include "DaoRecordsetCreate.h"


//////////////////////////////////////////////////////////////////////////
// CDaoRecordsetCreate

IMPLEMENT_DYNAMIC(CDaoRecordsetCreate, CDaoRecordsetEx)

CDaoRecordsetCreate::CDaoRecordsetCreate(CDaoDatabase* pDatabase)
	: CDaoRecordsetEx(pDatabase)
{
	//{{AFX_FIELD_INIT(CDaoRecordsetEx)
	//}}AFX_FIELD_INIT

}

CDaoRecordsetCreate::~CDaoRecordsetCreate()
{
	ClearField();
}

// this lines need class wizard
void CDaoRecordsetCreate::DoFieldExchange(CDaoFieldExchange* pFX)
{
	pFX;
	//{{AFX_FIELD_MAP(CDaoRecordsetCreate)
	//}}AFX_FIELD_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetCreate diagnostics

#ifdef _DEBUG
void CDaoRecordsetCreate::AssertValid() const
{
	CDaoRecordsetEx::AssertValid();
}

void CDaoRecordsetCreate::Dump(CDumpContext& dc) const
{
	CDaoRecordsetEx::Dump(dc);
}
#endif //_DEBUG

void CDaoRecordsetCreate::Close() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (IsOpen())
	{
		CDaoRecordsetEx::Close();
	}
}

int CDaoRecordsetCreate::CreateTable(LPCTSTR lpszName, long lAttributes,
	LPCTSTR lpszSrcTable, LPCTSTR lpszConnect)
{
	int ret = 0;
	int i;
	CDaoTableDef tableDef(m_pDatabase);

	ASSERT(m_Field.GetSize());
	if(m_Field.GetSize())
	{
		try
		{
			try
			{
				CDaoTableDefInfo tableDefInfo;
				m_pDatabase->GetTableDefInfo(lpszName,tableDefInfo);
				return 0;
			}
			catch(CDaoException *e)
			{
				TRACE_DAO_EXCEPTION(e);
				e->Delete();
			}

			tableDef.Create(lpszName,lAttributes,lpszSrcTable,lpszConnect);

			for(i = 0;i < m_Field.GetSize();i ++)
			{
				tableDef.CreateField(m_Field[i]);
			}
			tableDef.Append();
		}
		catch(CDaoException *e)
		{
			TRACE_DAO_EXCEPTION(e);

			ret = -1;
			e->Delete();
		}
	}
	return ret;
}


int CDaoRecordsetCreate::AddField(LPCTSTR lpszName, short nType, long lSize, long lAttributes)
{
	CDaoFieldInfoEx fieldinfo;

	fieldinfo.m_strName = lpszName;
	fieldinfo.m_nType = nType;
	fieldinfo.m_lSize = lSize;
	fieldinfo.m_lAttributes = lAttributes;

	fieldinfo.m_bRequired = FALSE;
	fieldinfo.m_bAllowZeroLength = FALSE;
	if(nType == dbText)
	{
		fieldinfo.m_bAllowZeroLength = TRUE;
	}

	return m_Field.Add(fieldinfo);
}

int CDaoRecordsetCreate::AddField(CDaoFieldInfoEx& fieldinfo)
{
	return m_Field.Add(fieldinfo);
}

void CDaoRecordsetCreate::AddField(SFieldInfo fieldInfo[],int nSize)
{
	int i;

	for(i = 0;i < nSize;i ++)
	{
		AddField(fieldInfo[i].m_strName,
				fieldInfo[i].m_nType,
				fieldInfo[i].m_lSize,
				fieldInfo[i].m_lAttributes);
	}
}

void CDaoRecordsetCreate::ClearField()
{
	m_Field.RemoveAll();
}



