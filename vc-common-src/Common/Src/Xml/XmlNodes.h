#pragma once


#include ".\XmlNode.h"


class CXML_API CXmlNodes
{
	friend class CXml;
	friend class CXmlNode;
	friend class CXmlNodes;

public:
	~CXmlNodes(void);
	CXmlNodes(void);
	CXmlNodes(CXmlNodes& refNodes);

	CXmlNodesPtr	operator =	(CXmlNodesPtr pNodes);
	CXmlNodes&		operator =	(CXmlNodes& refNodes);
	CXmlNodePtr		operator []	(LONG lIndex);
	CXmlNodePtr		operator []	(LPCTSTR lpszName);


	LONG GetCount(void);
	void Release(void);

	CXmlNodePtr GetItem(LONG nIndex);
	CXmlNodePtr GetItem(LPCTSTR lpszName);

protected:
	CXmlNodes(MSXML2::IXMLDOMNodeListPtr pNodeList);
	MSXML2::IXMLDOMNodeListPtr m_pNodeList;

};
