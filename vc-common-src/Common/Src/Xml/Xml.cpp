#include "stdafx.h"
#include ".\xml.h"


/*
// Create xml Example ...
MSXML2::IXMLDOMProcessingInstructionPtr pPI = NULL;
pPI = m_pDoc->createProcessingInstruction(_bstr_t(_T("xml")), _bstr_t(_T("version=\"1.0\"")));
ASSERT(pPI != NULL);

hr = m_pDoc->appendChild(pPI);
ASSERT(SUCCEEDED(hr));

// 创建根节点
MSXML2::IXMLDOMElementPtr pRoot = NULL;
pRoot = m_pDoc->createElement(_bstr_t(_T("xmlRoot")));
m_pDoc->appendChild(pRoot);
RELEASE_PTR(pRoot);

vbSuccessful = SUCCEEDED(hr) ? VARIANT_TRUE : VARIANT_FALSE;
*/


CXml::CXml(LPCTSTR pszXmlSrc, EnXmlSrcType xst)
: m_pDoc(NULL)
{
	if(pszXmlSrc)
		Open(pszXmlSrc, xst);
}

CXml::~CXml(void)
{
	Close();
}

/*
//-------------------------------------------------------------------------
// Function Name    :IsFileExist	[static]
// Parameter(s)     :LPCTSTR pszFilePath	文件路径和名称
// Return           :BOOL
// Memo             :判断文件是否存在
//-------------------------------------------------------------------------
BOOL CXml::IsFileExist(LPCTSTR pszFilePath)
{
	BOOL bExist = FALSE;
	HANDLE hFile = NULL;

	hFile = ::CreateFile(pszFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, 0
		, 0
		);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		bExist = TRUE;
	}

	return (bExist);
}
*/

//-------------------------------------------------------------------------
// Function Name    :CreateDocument
// Parameter(s)     :LPCTSTR pszRootName	根结点名称
//					:LPCTSTR pszCharSet		XML字符集
// Return           :CXml					新建的CXml对象
// Memo             :创建XML
//-------------------------------------------------------------------------
CXml CXml::CreateDocument(LPCTSTR pszRootName, LPCTSTR pszCharSet, BOOL bCreateHeader)
{
	ASSERT(pszRootName);
#ifdef _DEBUG
	if(bCreateHeader)
		ASSERT(pszCharSet);
#endif

	CString strXml;
	if(bCreateHeader)
		strXml.Format(_T("<?xml version=\"1.0\" encoding=\"%s\" ?><%s></%s>"), pszCharSet, pszRootName, pszRootName);
	else
		strXml.Format(_T("<%s></%s>"), pszRootName, pszRootName);
	
	return CXml(strXml, XST_STREAM);
}

//-------------------------------------------------------------------------
// Function Name    :CreateNode
// Parameter(s)     :CString strName	结点名称
// Return           :CXmlNodePtr
// Memo             :创建结点
//-------------------------------------------------------------------------
CXmlNodePtr CXml::CreateNode(LPCTSTR pszName)
{
	ASSERT(m_pDoc != NULL);

	CXmlNodePtr pChild(new CXmlNode());
	
	try
	{	MSXML2::IXMLDOMNodePtr pChildNode = NULL;
		pChildNode = m_pDoc->createElement(_bstr_t(pszName));
		ASSERT(pChildNode != NULL);
		pChild->m_pNode = pChildNode;
		RELEASE_PTR(pChildNode);
	}
	catch (_com_error e)
	{
		TRACE(_T("CXml::CreateNode 发生异常：%s\n"), e.ErrorMessage());
		ASSERT(FALSE);
	}
	return pChild;
}

//-------------------------------------------------------------------------
// Function Name    :Open
// Parameter(s)     :LPCTSTR pszXmlFilePath	文件路径和名称
// Return           :BOOL	是否成功
//-------------------------------------------------------------------------
BOOL CXml::Open(LPCTSTR pszXmlSrc, CXml::EnXmlSrcType xst)
{
	HRESULT hr = S_OK;
#ifdef USES_MSXML60
	hr = m_pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
#elif defined USES_MSXML40
	hr = m_pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40));
#elif defined USES_MSXML30
	hr = m_pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
#else
	hr = m_pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
#endif
	if(!SUCCEEDED(hr))
	{
		// did u CoInitialize ?
		// did u install MSXML ?
		ASSERT(FALSE);
		return FALSE;
	}

	if(xst == XST_FILE)
		m_strFilePath			= pszXmlSrc;

	VARIANT_BOOL vbSuccessful	= VARIANT_TRUE;

	try
	{
		m_pDoc->preserveWhiteSpace	= VARIANT_FALSE;
		m_pDoc->validateOnParse		= VARIANT_FALSE;

		if(xst == XST_FILE/* && IsFileExist(pszXmlSrc)*/)
			vbSuccessful = (m_pDoc->load(CComVariant(pszXmlSrc)) == VARIANT_TRUE) ? TRUE : FALSE;
		else if(xst == XST_STREAM)
			vbSuccessful = (m_pDoc->loadXML(pszXmlSrc) == VARIANT_TRUE) ? TRUE : FALSE;
		else
			vbSuccessful = FALSE;
	}
	catch(...)
	{
		vbSuccessful = FALSE;
		ASSERT(FALSE);
	}

	if(!vbSuccessful)
		m_pDoc = NULL;

	return vbSuccessful;
}

//-------------------------------------------------------------------------
// Function Name    :Close
// Parameter(s)     :void
// Return           :void
// Memo             :关闭
//-------------------------------------------------------------------------
void CXml::Close(void)
{
	RELEASE_PTR(m_pDoc);
}



//-------------------------------------------------------------------------
// Function Name    :GetLastError
// Parameter(s)     :void
// Return           :CString
// Memo             :获取最后的出错信息
//-------------------------------------------------------------------------
CString CXml::GetLastError(void) const
{
	ASSERT(m_pDoc != NULL);

	HRESULT hr = S_OK;
	MSXML2::IXMLDOMParseErrorPtr pIParseError = NULL;

	hr = m_pDoc->get_parseError(&pIParseError);
	ASSERT(SUCCEEDED(hr));

	CString strRet;
	if(pIParseError != NULL)
	{
		BSTR bstr = NULL;
        hr = pIParseError->get_reason(&bstr);
		ASSERT(SUCCEEDED(hr));

		strRet = (LPCTSTR)_bstr_t(bstr, false);

		RELEASE_PTR(pIParseError);		
	}

	return strRet;
}



//-------------------------------------------------------------------------
// Function Name    :GetRoot
// Parameter(s)     :
// Return           :
// Memo             :获取根节点
//-------------------------------------------------------------------------
CXmlNodePtr CXml::GetRoot(void) const
{	
	ASSERT(m_pDoc != NULL);

	CXmlNodePtr pNode(new CXmlNode());

	try
	{
		MSXML2::IXMLDOMElementPtr pElement = NULL;
		HRESULT hr = m_pDoc->get_documentElement(&pElement);
		ASSERT(SUCCEEDED(hr));
		ASSERT(pElement != NULL);

		pNode->m_pNode = pElement;
		RELEASE_PTR(pElement);
	}
	catch (_com_error e)
	{
		TRACE(_T("CXml::GetRoot 发生异常：%s\n"), e.ErrorMessage());
		ASSERT(FALSE);
	}
	
	return pNode;
}

//-------------------------------------------------------------------------
// Function Name    :Save
// Parameter(s)     :LPCTSTR lpszFilePath	[in] 保存的位置
// Return           :BOOL
// Memo             :保存Xml文件
//-------------------------------------------------------------------------
BOOL CXml::Save(LPCTSTR lpszFilePath /* = NULL */)
{
	ASSERT(m_pDoc != NULL);

	HRESULT hr = S_OK;
	if(lpszFilePath == NULL)
		hr = m_pDoc->save(CComVariant((LPCTSTR)m_strFilePath));
	else
		hr = m_pDoc->save(_variant_t(lpszFilePath));

	return SUCCEEDED(hr);
}

//-------------------------------------------------------------------------
// Function Name    :ToString
// Parameter(s)     :BSTR* pbstrOut	[Out] 输出的字符串
// Return           :BOOL
// Memo             :输出为Xml符串
//-------------------------------------------------------------------------
BSTR CXml::ToBSTR() const
{
	ASSERT(m_pDoc  != NULL);

	BSTR bstrOut	= NULL;
	m_pDoc->get_xml(&bstrOut);

	return bstrOut;
}

//-------------------------------------------------------------------------
// Function Name    :ToString
// Parameter(s)     :CString& strOut	[Out] 输出的字符串
// Return           :BOOL
// Memo             :输出为Xml符串
//-------------------------------------------------------------------------
BOOL CXml::ToString(CString& strOut) const
{
	ASSERT(m_pDoc != NULL);

	strOut.Empty();

	BSTR bstr = ToBSTR();

	if(!bstr)
		return FALSE;

	strOut = (LPCTSTR)_bstr_t(bstr, false);

	return TRUE;
}

//-------------------------------------------------------------------------
// Function Name    :SelectSingleNode
// Parameter(s)     :LPCTSTR strPath  路径名
// Return           :CXmlNodePtr
// Memo             :取单个节点
//-------------------------------------------------------------------------
CXmlNodePtr CXml::SelectSingleNode(LPCTSTR lpszPath) const
{
	ASSERT(m_pDoc != NULL);

	CXmlNodePtr pNode (new CXmlNode());

	if(!GetRoot()->IsNull())
		(*pNode) = GetRoot()->SelectSingleNode(lpszPath);
	
	return pNode;
}



//-------------------------------------------------------------------------
// Function Name    :SelectNodes
// Parameter(s)     :LPCTSTR strPath	路径名
// Return           :CXmlNodesPtr
// Memo             :取结点集合
//-------------------------------------------------------------------------
CXmlNodesPtr CXml::SelectNodes(LPCTSTR lpszPath) const
{
	ASSERT(m_pDoc != NULL);

	CXmlNodesPtr pNodes(new CXmlNodes());

	if(!GetRoot()->IsNull())
		(*pNodes) = GetRoot()->SelectNodes(lpszPath);

    return pNodes;
}



//-------------------------------------------------------------------------
// Function Name    :EncodeBase64
// Parameter(s)     :LPBYTE *pBuf	首地址
//					:ULONG ulSize	大小
// Return           :CString		编码后的结果
// Memo             :堆二进制数据编码成Base64格式
//-------------------------------------------------------------------------
CString CXml::Base64Encode(LPBYTE pBuf, ULONG ulSize)
{
	ASSERT(m_pDoc != NULL);
	ASSERT(pBuf != NULL);
	
	CString strRet = _T("");
	try
	{
		MSXML2::IXMLDOMElementPtr pElement = NULL;
		pElement = m_pDoc->createElement(_bstr_t(_T("Base64")));
		ASSERT(pElement != NULL);

		HRESULT hr = S_OK;
		hr = pElement->put_dataType(_bstr_t(_T("bin.base64")));
		ASSERT(SUCCEEDED(hr));

		SAFEARRAY * pAry = SafeArrayCreateVector(VT_UI1, 0L, ulSize);
		::memcpy(pAry->pvData, pBuf, ulSize);

		VARIANT var;
        VariantInit(&var);
        var.parray = pAry;
        var.vt = VT_ARRAY | VT_UI1;
        pElement->nodeTypedValue = var;

		BSTR bstr = NULL;
		hr = pElement->get_text(&bstr);
		ASSERT(SUCCEEDED(hr));	
		strRet = (LPCTSTR)_bstr_t(bstr, false);

		RELEASE_PTR(pElement);
	}
	catch (_com_error e)
	{
		TRACE(_T("CXml::Base64Encode 发生异常：%s\n"), e.ErrorMessage());
		ASSERT(FALSE);
	}

	return strRet;
}



//-------------------------------------------------------------------------
// Function Name    :Base64Decode
// Parameter(s)     :LPCTSTR pszIn	Base64编码
//					:LPBYTE pBuf	缓冲区首地址
//					:ULONG &ulSize	缓冲区大小
// Return           :BOOL
// Memo             :将Base64编码解码为二进制形式 
//					注意！此函数的缓冲区需要在函数调用完后删除
//-------------------------------------------------------------------------
BOOL CXml::Base64Decode(LPCTSTR pszIn, LPBYTE& pBuf, LONG& lSize)
{
	ASSERT(m_pDoc != NULL);
	
	try
	{
		MSXML2::IXMLDOMElementPtr pElement = NULL;
		pElement = m_pDoc->createElement(_bstr_t(_T("Base64")));
		ASSERT(pElement != NULL);

		HRESULT hr = S_OK;
		hr = pElement->put_dataType(_bstr_t(_T("bin.base64")));
		ASSERT(SUCCEEDED(hr));

		hr = pElement->put_text(CComBSTR(pszIn));
		ASSERT(SUCCEEDED(hr));

        hr = SafeArrayGetUBound(pElement->nodeTypedValue.parray, 1, &lSize);
		ASSERT(SUCCEEDED(hr));
		lSize ++;

		pBuf = new BYTE[lSize];
		memset(pBuf, 0, lSize);

		memcpy(pBuf, LPVOID(pElement->nodeTypedValue.parray->pvData), lSize);	

		RELEASE_PTR(pElement);
	}
	catch (_com_error e)
	{
		TRACE(_T("CXml::Base64Decode 发生异常：%s\n"), e.ErrorMessage());
		ASSERT(FALSE);
		return FALSE;
	}
	
	return TRUE;
}
