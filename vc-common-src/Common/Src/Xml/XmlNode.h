#pragma once

#include "MsXmlVersion.h"

/************************************************************/
/** imports / exports in dll or just use it by source code **/

#if defined(CXML_USE_IN_DLL_EXPORTS)
	#define CXML_API __declspec(dllexport)
#elif defined(CXML_USE_IN_DLL_IMPORTS)
	#define CXML_API __declspec(dllimport)
#else	// use by source code
	#define CXML_API
#endif

#ifdef USES_MSXML60
	#import "msxml6.dll"
#elif defined USES_MSXML40
	#import "msxml4.dll"
#elif defined USES_MSXML30
	#import "msxml3.dll"
#else
	#import "msxml2.dll"
#endif

#if !defined TRACE
	#ifdef _DEBUG
		#define TRACE	ATLTRACE
	#else
		#define TRACE	__noop
	#endif
#endif

#include <memory>
#include <atlbase.h>
#include <atltrace.h>
#include <afxcom_.h>


#ifndef RELEASE_PTR
#define RELEASE_PTR(x)	\
	if(x != NULL)		\
	{					\
		x.Release();	\
		x = NULL;		\
	}
#endif

class CXml;
class CXmlNode;
class CXmlNodes;

typedef std::auto_ptr<CXmlNode>  CXmlNodePtr;
typedef std::auto_ptr<CXmlNodes>  CXmlNodesPtr;

//////////////////////////////////////////////////////////////////////////

#include ".\XmlNodes.h"

class CXML_API CXmlNode
{
	friend class CXml;
	friend class CXmlNode;
	friend class CXmlNodes;

protected:
	
	MSXML2::IXMLDOMNodePtr   m_pNode;

	CXmlNode(MSXML2::IXMLDOMNodePtr pNode);

	BOOL _GetValue(CString& strValue);
	BOOL _SetValue(LPCTSTR pszValue);

	BOOL _GetAttribute(LPCTSTR pszName, CString& strValue);
	BOOL _SetAttribute(LPCTSTR pszName, CString& strValue);

public:

	//		 _______________
	//______|	构造析构	|___________________________________________________________________
	CXmlNode(void);
	CXmlNode(CXmlNode& refNode IN);
	~CXmlNode(void);


	//		 _______________
	//______|	重载 = 号	|___________________________________________________________________
	CXmlNodePtr operator = (CXmlNodePtr pNode);
	CXmlNode& operator = (CXmlNode& refNode);



	BOOL IsNull(void);			// 当前结点是否为空
	CString GetName(void);		// 获取当前结点名称
	CXmlNode& Remove(void);	// 将结点与父结点分离
	void Release(void);;		// 释放节点


	//		 _______________
	//______|	父子操作	|___________________________________________________________________
	CXmlNodePtr GetChild(LPCTSTR pszName, BOOL bBuildIfNotExist = FALSE);
	CXmlNodePtr NewChild(LPCTSTR pszName);
	CXmlNodePtr GetParent(void);
	CXmlNodesPtr GetChildren();
	void AddChild(CXmlNodePtr& pChildNode);
	void AddChild(CXmlNode& refChildNode);
	BOOL HasChildren(void);
	BOOL RemoveChildren(void);



	//		 _______________
	//______|	属性操作	|___________________________________________________________________
	CString	GetAttribute(LPCTSTR pszName, LPCTSTR lpszDefault = NULL);
	bool	GetAttribute(LPCTSTR pszName, bool bDefault);	
	int		GetAttribute(LPCTSTR pszName, int nDefault);	
	float	GetAttribute(LPCTSTR pszName, float fDefault);	
	double	GetAttribute(LPCTSTR pszName, double dDefault);

	BOOL	SetAttribute(LPCTSTR pszName, LPCTSTR lpszValue);
	BOOL	SetAttribute(LPCTSTR pszName, bool bValue);
	BOOL	SetAttribute(LPCTSTR pszName, int nValue);
	BOOL	SetAttribute(LPCTSTR pszName, float fValue);
	BOOL	SetAttribute(LPCTSTR pszName, double dValue);

	BOOL RemoveAttribute(LPCTSTR pszName);


	//		 _______________
	//______|	值操作		|___________________________________________________________________	
	CString	GetValue(LPCTSTR lpszDefault = NULL);
	bool	GetValue(bool bDefault);
	int		GetValue(int nDefault);
	float	GetValue(float fDefault);
	double	GetValue(double dDefault);

	BOOL	SetValue(LPCTSTR lpszValue);
	BOOL	SetValue(bool bValue);
	BOOL	SetValue(int nValue);
	BOOL	SetValue(float fValue);
	BOOL	SetValue(double dValue);


	//		 _______________
	//______|	XPath查询	|___________________________________________________________________
	CXmlNodePtr SelectSingleNode(LPCTSTR lpszPath);
	CXmlNodesPtr SelectNodes(LPCTSTR lpszPath);


};
