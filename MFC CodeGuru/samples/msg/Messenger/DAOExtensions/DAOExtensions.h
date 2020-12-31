#ifndef DAO_RECORDSET_EXT_H
#define DAO_RECORDSET_EXT_H

// DaoRecordsetEx.h : header file
//
#ifndef __AFXDAO_H
	#include <afxdao.h>
#endif


/////////////////////////////////////////////////////////////////////////////
// CDaoFieldInfoEx 

class CDaoFieldInfoEx : public CDaoFieldInfo
{
public:
	CDaoFieldInfoEx();
	CDaoFieldInfoEx(const CDaoFieldInfo &infoEx);
	virtual ~CDaoFieldInfoEx();

	const CDaoFieldInfoEx& operator = (const CDaoFieldInfo &infoEx);
};


/////////////////////////////////////////////////////////////////////////////
// COLEVariantEx OLE Variant

class COLEVariantEx
{
public:
	static LPCTSTR strFieldType(short sType);
	static LPCTSTR strQueryDefType(short sType);
	static LPCTSTR strBOOL(BOOL bFlag);
	static CString strVARIANT(const COleVariant& var);
	static CString strVariantType(const COleVariant& var);
};


/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetEx DAO recordset

class CDaoRecordsetEx : public CDaoRecordset
{
public:
	CDaoRecordsetEx(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoRecordsetEx)


public:
	// Atributes 
	bool m_IgnoreException;
public:

	//GetField functions return (field != NULL)
	virtual bool GetField(LPCTSTR fieldName, bool& field,bool defValue = false,bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, long& field,long defValue = 0,bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, int& field,int defValue = 0,bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, float& field,float defValue = .0,bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, double& field,double defValue = .0,bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, CString& field,CString defValue = _T(""),bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, WORD& field,WORD defValue = 0,bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, unsigned char& field,unsigned char defValue = 0,bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, COleCurrency& field,COleCurrency defValue = COleCurrency(),bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, COleDateTime& field,COleDateTime defValue = COleDateTime(),bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, char *field,int size,char *defValue = "",bool throwEx = true);
	virtual bool GetField(LPCTSTR fieldName, CByteArray& field, bool throwEx = true);

	//SetField functions return (Exception != NULL)
	virtual bool SetField(LPCTSTR fieldName, bool field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, long field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, int field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, float field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, double field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, LPCTSTR field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, WORD field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, unsigned char field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, COleCurrency& field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, COleDateTime& field,bool throwEx = true);
	virtual bool SetField(LPCTSTR fieldName, CByteArray& field, bool throwEx = true);

private:
	void SetTemplateFieldValue(CDaoRecordsetEx *record,LPCTSTR fieldName,COleVariant &var,bool throwEx);


public:
// Field/Param Data
	//{{AFX_FIELD(CDaoRecordsetEx, CDaoRecordset)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoRecordsetEx)
	public:

	// this line need class wizard
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


#ifdef _DEBUG

	void TraceDaoException(CDaoException *e,int lineInFile = __LINE__,CString strFileName = __FILE__);
	#define TRACE_DAO_EXCEPTION(e)	TraceDaoException(e,__LINE__,__FILE__);

	void TraceDaoType(LPCTSTR szFieldName,COleVariant &var,LPCTSTR szType);
	#define TRACE_DAO_INCORRECT_TYPE(szFieldName,var,szType) TraceDaoType(szFieldName,var,szType);

#else
	#define TRACE_DAO_EXCEPTION(e)
	#define TRACE_DAO_INCORRECT_TYPE(fieldName,var,type)
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


#endif 