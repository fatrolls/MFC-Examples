#pragma once

#include "XmlNode.h"


//-------------------------------------------------------------------------
// Classes Name	    : CXml CXmlNode CXmlNodes
// Author			: Kingfisher
// CreateTime       : 2005-11-03
// Memo             : Xml结点类库
// Version          : v1.0.5
//-------------------------------------------------------------------------



class CXML_API CXml
{
public:
	enum EnXmlSrcType
	{
		XST_FILE,
		XST_STREAM,
	};

public:
	CXml(LPCTSTR pszXmlSrc = NULL, EnXmlSrcType xst = XST_FILE);
	~CXml(void);

public:
	BOOL Base64Decode(LPCTSTR pszIn, LPBYTE& pBuf, LONG& lSize);
	CString Base64Encode(LPBYTE pBuf, ULONG ulSize);

	// 载入Xml
	BOOL Open(LPCTSTR pszXmlSrc, EnXmlSrcType xst = XST_FILE);

	// 保存Xml文件
	BOOL Save(LPCTSTR lpszFilePath = NULL);

	// 关闭Xml文件
	void Close(void);

	// 输出为Xml符串 (BSTR)
	BSTR ToBSTR() const;

	// 输出为Xml符串 (CString)
	BOOL ToString(CString& strOut) const;

	// 获取最近的错误信息
	CString GetLastError(void) const;

	// 获取Xml树的根结点
	CXmlNodePtr GetRoot(void) const;		

	// 选择单个结点
	CXmlNodePtr SelectSingleNode(LPCTSTR lpszPath) const;

	// 选择结点集合
	CXmlNodesPtr SelectNodes(LPCTSTR lpszPath) const;

	// 是否可用
	BOOL IsValid()  const {return m_pDoc != NULL;}

	// 创建结点
	CXmlNodePtr CreateNode(LPCTSTR pszName);

	// 创建Xml文档
	static CXml CreateDocument(LPCTSTR pszRootName, LPCTSTR pszCharSet = _T("GBK"), BOOL bCreateHeader = TRUE);

private:
	// 判断文件是否存在
	//static BOOL IsFileExist(LPCTSTR pszFilePath);

protected:
	MSXML2::IXMLDOMDocument2Ptr m_pDoc; 
	CString						m_strFilePath;
};
