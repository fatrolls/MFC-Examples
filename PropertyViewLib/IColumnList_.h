#ifndef ICOLUMNLIST_H
#define ICOLUMNLIST_H

class EProperty;
class EPropertyDouble;
class EPropertyInt;
class EPropertyCombo;
class EPropertyFile;
class IPropertyHost;

class IColumnList
{

public:

	virtual void             AddProperty     ( EProperty * pProperty ){}
	virtual void             AddPropString   ( IPropertyHost* pHost , const CString& sName , CString*  pString   , bool bEnabled = true ){}
	virtual EPropertyDouble* AddPropDouble   ( IPropertyHost* pHost , const CString& sName , double*   pDouble   , const CString& sUnit = "" , double dMinAllowed=0 , double dMaxAllowed=0 , bool bEnabled=true ){return NULL;}
	virtual EPropertyInt*    AddPropInt      ( IPropertyHost* pHost , const CString& sName , void*     pProperty , const CString& sUnit = "" , bool bEnabled = true ){return NULL;}
	virtual void             AddPropFont     ( IPropertyHost* pHost , const CString& sName , CFont*    pFont    ){}
	virtual void             AddPropColor    ( IPropertyHost* pHost , const CString& sName , COLORREF* pColor    , bool bEnabled = true ){}
	virtual void             AddPropCheck    ( IPropertyHost* pHost , const CString& sName , bool*     pBoolean ){}
	virtual void             AddPropTextblock( IPropertyHost* pHost , const CString& sName , CString*  pText    , bool bEnabled = true ){}
	virtual EPropertyCombo*  AddPropCombo    ( IPropertyHost* pHost , const CString& sName , int*      pComboIndex ){return NULL;}
	virtual EPropertyFile*   AddPropFile     ( IPropertyHost* pHost , const CString& sName , CString*  pFilename , const CString& sFilters = "All Files (*.*)|*.*||" ){return NULL;}

};

#endif