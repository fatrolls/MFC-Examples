#include "StdAfx.h"
#include ".\xmlnodes.h"


// 下面是构造函数 和 析构函数
CXmlNodes::CXmlNodes(MSXML2::IXMLDOMNodeListPtr pNodeList)
{
	m_pNodeList = pNodeList;
}

CXmlNodes::CXmlNodes(CXmlNodes& refNodes)
{
	m_pNodeList = refNodes.m_pNodeList;
}

CXmlNodes::CXmlNodes(void)
: m_pNodeList(NULL)
{
}

CXmlNodes::~CXmlNodes(void)
{
	Release();
}

//////////////////////////////////////////////////////////////////////////
void CXmlNodes::Release(void)
{
	RELEASE_PTR(m_pNodeList);
}


//-------------------------------------------------------------------------
// Function Name    :operator =
// Parameter(s)     :CXmlNodesPtr pNodes
// Return           :CXmlNodesPtr
// Memo             :重载 = 号
//-------------------------------------------------------------------------
CXmlNodesPtr CXmlNodes::operator = (CXmlNodesPtr pNodes IN)
{
	RELEASE_PTR(m_pNodeList);

	m_pNodeList = pNodes->m_pNodeList;
	return pNodes;
}


//-------------------------------------------------------------------------
// Function Name    :operator =
// Parameter(s)     :CXmlNodes& refNodes
// Return           :CXmlNodes&
// Memo             :重载 = 号
//-------------------------------------------------------------------------
CXmlNodes& CXmlNodes::operator = (CXmlNodes& refNodes)
{
	RELEASE_PTR(m_pNodeList);

	m_pNodeList = refNodes.m_pNodeList;
	return (*this);
}



//-------------------------------------------------------------------------
// Function Name    :GetCount
// Parameter(s)     :void
// Return           :LONG
// Memo             :获取数量
//-------------------------------------------------------------------------
LONG CXmlNodes::GetCount(void)
{
	ASSERT(m_pNodeList != NULL);

	try
	{
		return m_pNodeList->length;
	}
	catch (_com_error e)
	{
		TRACE(_T("CXmlNodes::GetCount 发生异常：%s\n"), e.ErrorMessage());
		ASSERT(FALSE);
		return -1;
	}
}



//-------------------------------------------------------------------------
// Function Name    :GetItem
// Parameter(s)     :LONG nIndex	索引
// Return           :CXmlNodePtr
// Memo             :获取集合中的结点
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNodes::GetItem(LONG nIndex)
{
	ASSERT(m_pNodeList != NULL);
	ASSERT(nIndex >= 0 && nIndex < GetCount());

	CXmlNodePtr pNode (new CXmlNode(m_pNodeList->item[nIndex]));

	return pNode;
}


//-------------------------------------------------------------------------
// Function Name    :operator[]
// Parameter(s)     :INT nIndex
// Return           :CXmlNodePtr
// Memo             :作用同 GetItem(LONG nIndex)
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNodes::operator[] (LONG lIndex)
{
	return GetItem(lIndex);
}


//-------------------------------------------------------------------------
// Function Name    :GetItem
// Parameter(s)     :LPCTSTR lpszName	结点名称
// Return           :CXmlNodePtr
// Memo             :根据名称在结点集中查结点
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNodes::GetItem(LPCTSTR lpszName)
{
	ASSERT(m_pNodeList != NULL);
	ASSERT(lpszName != NULL);
	
	CXmlNodePtr pNode (new CXmlNode());

	try
	{
		HRESULT hr = S_OK;
		CString strName;
		BSTR bstr = NULL;
		MSXML2::IXMLDOMNodePtr pItem = NULL;	

		for(int i = 0; i < m_pNodeList->length; i++)
		{
			pItem = m_pNodeList->item[i];

			hr = pItem->get_nodeName(&bstr);		

			strName = (LPCTSTR)_bstr_t(bstr, false);

			// 查找第一个相等的
			if(strName.Compare(lpszName) == 0)
			{
				pNode->m_pNode = pItem;
				RELEASE_PTR(pItem);
				return pNode;
			}

			RELEASE_PTR(pItem);
		}
	}
	catch (_com_error e)
	{
		TRACE(_T("CXmlNodes::GetItem 发生异常：%s\n"), e.ErrorMessage());
		ASSERT(FALSE);
	}

	return pNode;
}


//-------------------------------------------------------------------------
// Function Name    :operator[]
// Parameter(s)     :LPCTSTR lpszName	结点名称
// Return           :CXmlNodePtr
// Memo             :作用同 GetItem(LPCTSTR lpszName)
//-------------------------------------------------------------------------
CXmlNodePtr CXmlNodes::operator[] (LPCTSTR lpszName)
{
	return GetItem(lpszName);
}

