#ifndef DAO_RECORDSET_CREATE_H
#define DAO_RECORDSET_CREATE_H

// CDaoRecordsetCreate.h : header file
//

#ifndef __AFXTEMPL_H__
	#include <afxtempl.h>
#endif


#ifndef DAO_RECORDSET_EXT_H
	#include "DAOExtensions.h"
#endif


class CDaoRecordsetCreate : public CDaoRecordsetEx
{
	CArray<CDaoFieldInfoEx,CDaoFieldInfoEx&> m_Field;
public:

	struct SFieldInfo
	{
		char*		m_strName;           // Primary
		short		m_nType;             // Primary
		long		m_lSize;             // Primary
		long		m_lAttributes;       // Primary
	};


public:
	CDaoRecordsetCreate(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoRecordsetCreate)

	~CDaoRecordsetCreate();

	virtual int CreateTable(LPCTSTR lpszName, long lAttributes = 0,
		LPCTSTR lpszSrcTable = NULL, LPCTSTR lpszConnect = NULL);

	int AddField(LPCTSTR lpszName, short nType, long lSize, long lAttributes = 0);
	int AddField(CDaoFieldInfoEx& fieldinfo);
	void AddField(SFieldInfo fieldInfo[],int nSize);
	void ClearField();


// Field/Param Data
	//{{AFX_FIELD(CDaoRecordsetCreate, CDaoRecordsetEx)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoRecordsetCreate)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	virtual void Close();
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


#endif
