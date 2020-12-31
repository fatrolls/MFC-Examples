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


// DaoRecordsetEx.cpp : implementation file
//

#include "stdafx.h"
#include "DAOExtensions.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// functions

template <class T> 
void GetTemplateFieldValue(CDaoRecordsetEx *record,LPCTSTR fieldName,T &field,T &defValue,COleVariant &var,bool throwEx)
{
	try
	{
		record->GetFieldValue(fieldName, var);

		if(var.vt == VT_NULL)
			field = defValue;
	}
	catch(CDaoException *e)
	{
		TRACE_DAO_EXCEPTION(e);

		field = defValue;
		var.ChangeType(VT_NULL);
		if(record->m_IgnoreException == false && throwEx != false)
		{
			throw e;
		}
		e->Delete();
	}
}


void TraceDaoType(LPCTSTR szFieldName,COleVariant &var,LPCTSTR szType)
{ 
	CString strOLE = COLEVariantEx::strVariantType(var); 

	if(szType != NULL)
	{
		TRACE("DAO: -> Incorrect type in field [%s]. Detected '%s' must be '%s'\n",szFieldName,(LPCTSTR)strOLE,szType);
	}
	else
	{
		TRACE("DAO: -> Incorrect type in field [%s]. Detected '%s'\n",szFieldName,(LPCTSTR)strOLE);
	}
}



void TraceDaoException(CDaoException *e,int lineInFile,CString strFileName)
{							
	TCHAR szCause[255];						
	CString strFormatted;					
	CString strLineInFile;
											
	strLineInFile.Format("%i",lineInFile);	
	e->GetErrorMessage(szCause, 255);		
	strFormatted = _T("DAO Exception [");	
	strFormatted += strFileName;				
	strFormatted += ":";					
	strFormatted += strLineInFile;			
	strFormatted += "] - ";					
	strFormatted += szCause;				
	TRACE("%s\n",(LPCTSTR)strFormatted);	
};

/////////////////////////////////////////////////////////////////////////////
// COLEVariantEx
CDaoFieldInfoEx::CDaoFieldInfoEx()
{
	m_strName = "";
	m_nType = 0;
	m_lSize = 0;
	m_lAttributes = 0;
	m_nOrdinalPosition = 0;
	m_bRequired = FALSE;
	m_bAllowZeroLength = FALSE;
	m_lCollatingOrder = 0;
	m_strForeignName = "";
	m_strSourceField = "";
	m_strSourceTable = "";
	m_strValidationRule = "";
	m_strValidationText = "";
	m_strDefaultValue = "";
}

CDaoFieldInfoEx::CDaoFieldInfoEx(const CDaoFieldInfo &infoEx)
{
	*this = infoEx;
}

CDaoFieldInfoEx::~CDaoFieldInfoEx()
{
	m_strName.Empty();
	m_strForeignName.Empty();
	m_strSourceField.Empty();
	m_strSourceTable.Empty();
	m_strValidationRule.Empty();
	m_strValidationText.Empty();
	m_strDefaultValue.Empty();
}

const CDaoFieldInfoEx& CDaoFieldInfoEx::operator = (const CDaoFieldInfo &infoEx)
{
	if(&infoEx != this)
	{
		m_strName = infoEx.m_strName;
		m_nType = infoEx.m_nType;
		m_lSize = infoEx.m_lSize;
		m_lAttributes = infoEx.m_lAttributes;
		m_nOrdinalPosition = infoEx.m_nOrdinalPosition;
		m_bRequired = infoEx.m_bRequired;
		m_bAllowZeroLength = infoEx.m_bAllowZeroLength;
		m_lCollatingOrder = infoEx.m_lCollatingOrder;
		m_strForeignName = infoEx.m_strForeignName;
		m_strSourceField = infoEx.m_strSourceField;
		m_strSourceTable = infoEx.m_strSourceTable;
		m_strValidationRule = infoEx.m_strValidationRule;
		m_strValidationText = infoEx.m_strValidationText;
		m_strDefaultValue = infoEx.m_strDefaultValue;
	}

	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// COLEVariantEx

LPCTSTR COLEVariantEx::strFieldType(short sType)
{
	switch(sType)
	{
		case (dbBoolean):
			return _T("Bool");
		case (dbByte):
			return _T("Byte");
		case (dbInteger):
			return _T("Integer");
		case (dbLong):
			return _T("Long");
		case (dbCurrency):
			return _T("Currency");
		case (dbSingle):
			return _T("Single");
		case (dbDouble):
			return _T("Double");
		case (dbDate):
			return _T("Date");
		case (dbText):
			return _T("Text");
		case (dbLongBinary):
			return _T("Long Binary");
		case (dbMemo):
			return _T("Memo");
		case (dbGUID):
			return _T("GUID");
	}
	return _T("Unknown");
}

LPCTSTR COLEVariantEx::strQueryDefType(short sType)
{
	switch(sType)
	{
		case (dbQSelect):
			return _T("Select");
		case (dbQAction):
			return _T("Action");
		case (dbQCrosstab):
			return _T("Crosstab");
		case (dbQDelete):
			return _T("Delete");
		case (dbQUpdate):
			return _T("Update");
		case (dbQAppend):
			return _T("Append");
		case (dbQMakeTable):
			return _T("MakeTable");
		case (dbQDDL):
			return _T("DDL");
		case (dbQSQLPassThrough):
			return _T("SQLPassThrough");
		case (dbQSetOperation):
			return _T("Set Operation");
		case (dbQSPTBulk):
			return _T("SPTBulk");
	}
	return _T("Unknown");
}

LPCTSTR COLEVariantEx::strBOOL(BOOL bFlag)
{
	return bFlag ? _T("TRUE") : _T("FALSE");
}

CString COLEVariantEx::strVariantType(const COleVariant& var)
{
	CString strRet;
	strRet = _T("Fish");
	switch(var.vt)
	{
	case VT_EMPTY:            
		strRet = _T("nothing");
		break;
	case VT_NULL:             
		strRet = _T("SQL style Null");
		break;
	case VT_I2:               
		strRet = _T("2 byte signed int");
		break;
	case VT_I4:               
		strRet = _T("4 byte signed int");
		break;
	case VT_R4:               
		strRet = _T("4 byte real");
		break;
	case VT_R8:               
		strRet = _T("8 byte real");
		break;
	case VT_CY:               
		strRet = _T("currency");
		break;
	case VT_DATE:             
		strRet = _T("date");
		break;
	case VT_BSTR:             
		strRet = _T("OLE Automation string");
		break;
	case VT_DISPATCH:         
		strRet = _T("IDispatch *");
		break;
	case VT_ERROR:            
		strRet = _T("SCODE");
		break;
	case VT_BOOL:             
		strRet = _T("True=-1, False=0");
		break;
	case VT_VARIANT:          
		strRet = _T("VARIANT *");
		break;
	case VT_UNKNOWN:          
		strRet = _T("IUnknown *");
		break;
	case VT_DECIMAL:          
		strRet = _T("16 byte fixed point");
		break;
	case VT_I1:               
		strRet = _T("signed char");
		break;
	case VT_UI1:              
		strRet = _T("unsigned char");
		break;
	case VT_UI2:              
		strRet = _T("unsigned short");
		break;
	case VT_UI4:              
		strRet = _T("unsigned short");
		break;
	case VT_I8:               
		strRet = _T("signed 64-bit int");
		break;
	case VT_UI8:              
		strRet = _T("unsigned 64-bit int");
		break;
	case VT_INT:              
		strRet = _T("signed machine int");
		break;
	case VT_UINT:             
		strRet = _T("unsigned machine int");
		break;
	case VT_VOID:             
		strRet = _T("C style void");
		break;
	case VT_HRESULT:          
		strRet = _T("Standard return type");
		break;
	case VT_PTR:              
		strRet = _T("pointer type");
		break;
	case VT_SAFEARRAY:        
		strRet = _T("(use VT_ARRAY in VARIANT)");
		break;
	case VT_CARRAY:           
		strRet = _T("C style array");
		break;
	case VT_USERDEFINED:      
		strRet = _T("user defined type");
		break;
	case VT_LPSTR:            
		strRet = _T("null terminated string");
		break;
	case VT_LPWSTR:           
		strRet = _T("wide null terminated string");
		break;
	case VT_FILETIME:         
		strRet = _T("FILETIME");
		break;
	case VT_BLOB:             
		strRet = _T("Length prefixed bytes");
		break;
	case VT_STREAM:           
		strRet = _T("Name of the stream follows");
		break;
	case VT_STORAGE:          
		strRet = _T("Name of the storage follows");
		break;
	case VT_STREAMED_OBJECT:  
		strRet = _T("Stream contains an object");
		break;
	case VT_STORED_OBJECT:    
		strRet = _T("Storage contains an object");
		break;
	case VT_BLOB_OBJECT:      
		strRet = _T("Blob contains an object");
		break;
	case VT_CF:               
		strRet = _T("Clipboard format");
		break;
	case VT_CLSID:            
		strRet = _T("A Class ID");
		break;
	case VT_VECTOR:           
		strRet = _T("simple counted array");
		break;
	case VT_ARRAY:            
		strRet = _T("SAFEARRAY*");
		break;
	case VT_BYREF:            
		strRet = _T("void* for local use");
		break;
	}

	return strRet;
}




CString COLEVariantEx::strVARIANT(const COleVariant& var)
{
	CString strRet;
	strRet = _T("Fish");
	switch(var.vt)
	{
		case VT_EMPTY:
		case VT_NULL:
			strRet = _T("NULL");
			break;
		case VT_I2:
			strRet.Format(_T("%hd"),V_I2(&var));
			break;
		case VT_I4:
			strRet.Format(_T("%d"),V_I4(&var));
			break;
		case VT_R4:
			strRet.Format(_T("%e"),(double)V_R4(&var));
			break;
		case VT_R8:
			strRet.Format(_T("%e"),V_R8(&var));
			break;
		case VT_CY:
			strRet = COleCurrency(var).Format();
			break;
		case VT_DATE:
			strRet = COleDateTime(var).Format(_T("%m %d %y"));
			break;
		case VT_BSTR:
			strRet = V_BSTRT(&var);
			break;
		case VT_DISPATCH:
			strRet = _T("VT_DISPATCH");
			break;
		case VT_ERROR:
			strRet = _T("VT_ERROR");
			break;
		case VT_BOOL:
			return strBOOL(V_BOOL(&var));
		case VT_VARIANT:
			strRet = _T("VT_VARIANT");
			break;
		case VT_UNKNOWN:
			strRet = _T("VT_UNKNOWN");
			break;
		case VT_I1:
			strRet = _T("VT_I1");
			break;
		case VT_UI1:
			strRet.Format(_T("0x%02hX"),(unsigned short)V_UI1(&var));
			break;
		case VT_UI2:
			strRet = _T("VT_UI2");
			break;
		case VT_UI4:
			strRet = _T("VT_UI4");
			break;
		case VT_I8:
			strRet = _T("VT_I8");
			break;
		case VT_UI8:
			strRet = _T("VT_UI8");
			break;
		case VT_INT:
			strRet = _T("VT_INT");
			break;
		case VT_UINT:
			strRet = _T("VT_UINT");
			break;
		case VT_VOID:
			strRet = _T("VT_VOID");
			break;
		case VT_HRESULT:
			strRet = _T("VT_HRESULT");
			break;
		case VT_PTR:
			strRet = _T("VT_PTR");
			break;
		case VT_SAFEARRAY:
			strRet = _T("VT_SAFEARRAY");
			break;
		case VT_CARRAY:
			strRet = _T("VT_CARRAY");
			break;
		case VT_USERDEFINED:
			strRet = _T("VT_USERDEFINED");
			break;
		case VT_LPSTR:
			strRet = _T("VT_LPSTR");
			break;
		case VT_LPWSTR:
			strRet = _T("VT_LPWSTR");
			break;
		case VT_FILETIME:
			strRet = _T("VT_FILETIME");
			break;
		case VT_BLOB:
			strRet = _T("VT_BLOB");
			break;
		case VT_STREAM:
			strRet = _T("VT_STREAM");
			break;
		case VT_STORAGE:
			strRet = _T("VT_STORAGE");
			break;
		case VT_STREAMED_OBJECT:
			strRet = _T("VT_STREAMED_OBJECT");
			break;
		case VT_STORED_OBJECT:
			strRet = _T("VT_STORED_OBJECT");
			break;
		case VT_BLOB_OBJECT:
			strRet = _T("VT_BLOB_OBJECT");
			break;
		case VT_CF:
			strRet = _T("VT_CF");
			break;
		case VT_CLSID:
			strRet = _T("VT_CLSID");
			break;
	}
	
	DWORD vt = var.vt;
	if(vt & VT_ARRAY)
	{
		vt = vt & ~VT_ARRAY;
		strRet = _T("Array of ");
	}
	
	if(vt & VT_BYREF)
	{
		vt = vt & ~VT_BYREF;
		strRet += _T("Pointer to ");
	}
	
	if(vt != var.vt)
	{
		switch(vt)
		{
			case VT_EMPTY:
				strRet += _T("VT_EMPTY");
				break;
			case VT_NULL:
				strRet += _T("VT_NULL");
				break;
			case VT_I2:
				strRet += _T("VT_I2");
				break;
			case VT_I4:
				strRet += _T("VT_I4");
				break;
			case VT_R4:
				strRet += _T("VT_R4");
				break;
			case VT_R8:
				strRet += _T("VT_R8");
				break;
			case VT_CY:
				strRet += _T("VT_CY");
				break;
			case VT_DATE:
				strRet += _T("VT_DATE");
				break;
			case VT_BSTR:
				strRet += _T("VT_BSTR");
				break;
			case VT_DISPATCH:
				strRet += _T("VT_DISPATCH");
				break;
			case VT_ERROR:
				strRet += _T("VT_ERROR");
				break;
			case VT_BOOL:
				strRet += _T("VT_BOOL");
				break;
			case VT_VARIANT:
				strRet += _T("VT_VARIANT");
				break;
			case VT_UNKNOWN:
				strRet += _T("VT_UNKNOWN");
				break;
			case VT_I1:
				strRet += _T("VT_I1");
				break;
			case VT_UI1:
				strRet += _T("VT_UI1");
				break;
			case VT_UI2:
				strRet += _T("VT_UI2");
				break;
			case VT_UI4:
				strRet += _T("VT_UI4");
				break;
			case VT_I8:
				strRet += _T("VT_I8");
				break;
			case VT_UI8:
				strRet += _T("VT_UI8");
				break;
			case VT_INT:
				strRet += _T("VT_INT");
				break;
			case VT_UINT:
				strRet += _T("VT_UINT");
				break;
			case VT_VOID:
				strRet += _T("VT_VOID");
				break;
			case VT_HRESULT:
				strRet += _T("VT_HRESULT");
				break;
			case VT_PTR:
				strRet += _T("VT_PTR");
				break;
			case VT_SAFEARRAY:
				strRet += _T("VT_SAFEARRAY");
				break;
			case VT_CARRAY:
				strRet += _T("VT_CARRAY");
				break;
			case VT_USERDEFINED:
				strRet += _T("VT_USERDEFINED");
				break;
			case VT_LPSTR:
				strRet += _T("VT_LPSTR");
				break;
			case VT_LPWSTR:
				strRet += _T("VT_LPWSTR");
				break;
			case VT_FILETIME:
				strRet += _T("VT_FILETIME");
				break;
			case VT_BLOB:
				strRet += _T("VT_BLOB");
				break;
			case VT_STREAM:
				strRet += _T("VT_STREAM");
				break;
			case VT_STORAGE:
				strRet += _T("VT_STORAGE");
				break;
			case VT_STREAMED_OBJECT:
				strRet += _T("VT_STREAMED_OBJECT");
				break;
			case VT_STORED_OBJECT:
				strRet += _T("VT_STORED_OBJECT");
				break;
			case VT_BLOB_OBJECT:
				strRet += _T("VT_BLOB_OBJECT");
				break;
			case VT_CF:
				strRet += _T("VT_CF");
				break;
			case VT_CLSID:
				strRet += _T("VT_CLSID");
				break;
		}
	}
	return strRet;
}



/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetEx

IMPLEMENT_DYNAMIC(CDaoRecordsetEx, CDaoRecordset)

CDaoRecordsetEx::CDaoRecordsetEx(CDaoDatabase *pDatabase)
	: CDaoRecordset(pDatabase)
{
	//{{AFX_FIELD_INIT(CDaoRecordsetEx)
	//}}AFX_FIELD_INIT

	m_IgnoreException = false;
}

// this lines need class wizard
void CDaoRecordsetEx::DoFieldExchange(CDaoFieldExchange* pFX)
{
	pFX;
	//{{AFX_FIELD_MAP(CDaoRecordsetEx)
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetEx diagnostics

#ifdef _DEBUG
void CDaoRecordsetEx::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoRecordsetEx::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG



bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, bool& field,bool defValue,bool throwEx)
{
	COleVariant		var;

	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	if(var.vt != VT_BOOL)
	{
		field = defValue;
	}
	else
	{
		field = (V_BOOL(&var) != false);
	}
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, long& field,long defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	switch(var.vt)
	{
	case VT_BOOL:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		field = V_BOOL(&var);
		break;
	case VT_I1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		field = V_I1(&var);
		break;
	case VT_UI1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		field = V_UI1(&var);
		break;
	case VT_I2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		field = V_I2(&var);
		break;
	case VT_UI2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		field = V_UI2(&var);
		break;
	case VT_I4:
		field = V_I4(&var);
		break;
	case VT_UI4:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		field = V_UI4(&var);
		break;
	case VT_INT:
		field = V_INT(&var);
		break;
	case VT_UINT:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		field = V_UINT(&var);
		break;
	default:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Long"));
		TRACE("DAO: -> Assigned default value\n");
		field = defValue;
		break;
	};
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, int& field,int defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	switch(var.vt)
	{
	case VT_BOOL:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		field = V_BOOL(&var);
		break;
	case VT_I1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		field = V_I1(&var);
		break;
	case VT_UI1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		field = V_UI1(&var);
		break;
	case VT_I2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		field = V_I2(&var);
		break;
	case VT_UI2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		field = V_UI2(&var);
		break;
	case VT_I4:
		field = V_I4(&var);
		break;
	case VT_UI4:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		field = V_UI4(&var);
		break;
	case VT_INT:
		field = V_INT(&var);
		break;
	case VT_UINT:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		field = V_UINT(&var);
		break;
	default:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Int"));
		TRACE("DAO: -> Assigned default value\n");
		field = defValue;
		break;
	};
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, float& field,float defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	switch(var.vt)
	{
	case VT_BOOL:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = V_BOOL(&var);
		break;
	case VT_I1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = V_I1(&var);
		break;
	case VT_UI1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = V_UI1(&var);
		break;
	case VT_I2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = V_I2(&var);
		break;
	case VT_UI2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = V_UI2(&var);
		break;
	case VT_I4:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = (float)V_I4(&var);
		break;
	case VT_UI4:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = (float)V_UI4(&var);
		break;
	case VT_INT:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = (float)V_INT(&var);
		break;
	case VT_UINT:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		field = (float)V_UINT(&var);
		break;
	case VT_R4:
		field = V_R4(&var);
		break;
	default:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Float"));
		TRACE("DAO: -> Assigned default value\n");
		field = defValue;
		break;
	};
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, double& field,double defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	switch(var.vt)
	{
	case VT_BOOL:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_BOOL(&var);
		break;
	case VT_I1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_I1(&var);
		break;
	case VT_UI1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_UI1(&var);
		break;
	case VT_I2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_I2(&var);
		break;
	case VT_UI2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_UI2(&var);
		break;
	case VT_I4:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_I4(&var);
		break;
	case VT_UI4:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_UI4(&var);
		break;
	case VT_I8:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
//		field = V_I8(&var);
		break;
	case VT_UI8:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
//		field = V_UI8(&var);
		break;
	case VT_INT:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_INT(&var);
		break;
	case VT_UINT:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_UINT(&var);
		break;
	case VT_R4:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		field = V_R4(&var);
		break;
	case VT_R8:
		field = V_R8(&var);
		break;
	default:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("Double"));
		TRACE("DAO: -> Assigned default value\n");
		field = defValue;
		break;
	};
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, CString& field,CString defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	if(var.vt != VT_BSTR)
	{
		field = defValue;
	}
	else
	{
		field = V_BSTRT(&var);
	}
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, WORD& field,WORD defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	switch(var.vt)
	{
	case VT_BOOL:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("WORD"));
		field = V_BOOL(&var);
		break;
	case VT_I1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("WORD"));
		field = V_I1(&var);
		break;
	case VT_UI1:
		field = V_UI1(&var);
		break;
	case VT_I2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("WORD"));
		field = V_I2(&var);
		break;
	case VT_UI2:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("WORD"));
		field = V_UI2(&var);
		break;
	default:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("WORD"));
		TRACE("DAO: -> Assigned default value\n");
		field = defValue;
		break;
	};
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, unsigned char& field,unsigned char defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	switch(var.vt)
	{
	case VT_BOOL:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("BYTE"));
		field = (unsigned char)V_BOOL(&var);
		break;
	case VT_I1:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("BYTE"));
		field = V_I1(&var);
		break;
	case VT_UI1:
		field = V_UI1(&var);
		break;
	default:
		TRACE_DAO_INCORRECT_TYPE(fieldName,var,_T("BYTE"));
		TRACE("DAO: -> Assigned default value\n");
		field = defValue;
		break;
	};
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, COleCurrency& field,COleCurrency defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	if(var.vt != VT_CY)
	{
		field = defValue;
	}
	else
	{
		field = var;
	}
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, COleDateTime& field,COleDateTime defValue,bool throwEx)
{
	COleVariant		var;
	
	GetTemplateFieldValue(this,fieldName,field,defValue,var,throwEx);
	
	if(var.vt != VT_DATE)
	{
		field = defValue;
	}
	else
	{
		field = var;
	}
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, char *field,int size,char *defValue,bool throwEx)
{
	CString str;
	bool ret;

	ret = GetField(fieldName,str,defValue,throwEx);

	ASSERT(str.GetLength() <= size);
	strncpy(field,str,size - 1);

	return ret;
}

bool CDaoRecordsetEx::GetField(LPCTSTR fieldName, CByteArray& field, bool throwEx)
{
	COleVariant		var;
	
	try
	{
		GetFieldValue(fieldName, var);

		if(var.vt == VT_NULL)
			field.SetSize(0);

	}
	catch(CDaoException *e)
	{
		TRACE_DAO_EXCEPTION(e);

		field.SetSize(0);
		var.ChangeType(VT_NULL);
		if(m_IgnoreException == false && throwEx != false)
		{
			throw e;
		}
		e->Delete();
	}
	
	if(var.vt != VT_NULL)
	{
	    void *pArrayData;
		COleSafeArray safe((LPCVARIANT)var);

		//Retrieve size of array
		DWORD size = var.parray->rgsabound[0].cElements;
		field.SetSize(size);

		safe.AccessData(&pArrayData);
		CopyMemory(field.GetData(),pArrayData,size);
		safe.UnaccessData();
	}
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, bool field,bool throwEx)
{
	COleVariant		var((short)field,VT_BOOL);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, long field,bool throwEx)
{
	COleVariant		var(field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, int field,bool throwEx)
{
	COleVariant		var((long)field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, float field,bool throwEx)
{
	COleVariant		var(field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, double field,bool throwEx)
{
	COleVariant		var(field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, LPCTSTR field,bool throwEx)
{
	COleVariant		var(field,VT_BSTRT);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, WORD field,bool throwEx)
{
	COleVariant		var((short)field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, unsigned char field,bool throwEx)
{
	COleVariant		var(field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, COleCurrency& field,bool throwEx)
{
	COleVariant		var(field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, COleDateTime& field,bool throwEx)
{
	COleVariant		var(field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

bool CDaoRecordsetEx::SetField(LPCTSTR fieldName, CByteArray& field, bool throwEx)
{
	COleVariant		var(field);

	SetTemplateFieldValue(this,fieldName,var,throwEx);
	
	return (var.vt != VT_NULL);
}

void CDaoRecordsetEx::SetTemplateFieldValue(CDaoRecordsetEx *record,LPCTSTR fieldName,COleVariant &var,bool throwEx)
{
	try
	{
		record->SetFieldValue(fieldName, var);
	}
	catch(CDaoException *e)
	{
		TRACE_DAO_EXCEPTION(e);

		var.ChangeType(VT_NULL);
		if(record->m_IgnoreException == false && throwEx != false)
		{
			throw e;
		}
		e->Delete();
	}
}
