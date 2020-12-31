// $$recset_hfile$$.cpp : implementation of the $$RECSET_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"
#include "$$recset_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$RECSET_CLASS$$ implementation

$$IF(DAO)
IMPLEMENT_DYNAMIC($$RECSET_CLASS$$, CDaoRecordset)
$$ELSE
IMPLEMENT_DYNAMIC($$RECSET_CLASS$$, CRecordset)
$$ENDIF

$$IF(DAO)
$$RECSET_CLASS$$::$$RECSET_CLASS$$(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
$$ELSE
$$RECSET_CLASS$$::$$RECSET_CLASS$$(CDatabase* pdb)
	: CRecordset(pdb)
$$ENDIF
{
	//{{AFX_FIELD_INIT($$RECSET_CLASS$$)
$$RECSET_VAR_BINDINGS$$
	//}}AFX_FIELD_INIT
	m_nDefaultType = $$DB_TABLE_TYPE$$;$$PARAM_VAR_BINDINGS$$
$$IF(DAO)
$$IF(DB_NO_DETECT)
	m_bCheckCacheForDirtyFields = FALSE;
$$ENDIF // DB_NO_DETECT
$$ENDIF // DAO
}

$$IF(DAO)
CString $$RECSET_CLASS$$::GetDefaultDBName()
{
	return _T("$$DB_CONNECT$$");
}

$$ELSE
CString $$RECSET_CLASS$$::GetDefaultConnect()
{
	return _T("ODBC;DSN=$$DB_CONNECT$$");
}
$$ENDIF

CString $$RECSET_CLASS$$::GetDefaultSQL()
{
	return _T("$$DB_SOURCE$$");
}

$$IF(DAO)
void $$RECSET_CLASS$$::DoFieldExchange(CDaoFieldExchange* pFX)
$$ELSE
void $$RECSET_CLASS$$::DoFieldExchange(CFieldExchange* pFX)
$$ENDIF
{
	//{{AFX_FIELD_MAP($$RECSET_CLASS$$)
$$IF(DAO)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
$$ELSE
	pFX->SetFieldType(CFieldExchange::outputColumn);
$$ENDIF
$$RECSET_RFX$$
	//}}AFX_FIELD_MAP$$PARAM_RFX$$
}

/////////////////////////////////////////////////////////////////////////////
// $$RECSET_CLASS$$ diagnostics

#ifdef _DEBUG
void $$RECSET_CLASS$$::AssertValid() const
{
$$IF(DAO)
	CDaoRecordset::AssertValid();
$$ELSE
	CRecordset::AssertValid();
$$ENDIF
}

void $$RECSET_CLASS$$::Dump(CDumpContext& dc) const
{
$$IF(DAO)
	CDaoRecordset::Dump(dc);
$$ELSE
	CRecordset::Dump(dc);
$$ENDIF
}
#endif //_DEBUG
