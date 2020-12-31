// XmlDocument.h: interface for the CXmlDocument class.
//
//////////////////////////////////////////////////////////////////////

#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

class CXmlElement : public CObject
{
public:
	CXmlElement() 
	{
		m_posFind = NULL;
		m_pParentElement = NULL;
	};
	virtual ~CXmlElement() 
	{
		while (!m_ChildElements.IsEmpty())
		{
			delete m_ChildElements.RemoveHead();
		}
	};

	CString m_strName;
	CString m_strAttributes;
	CString m_strData;
	
	CObList m_ChildElements;
	
	CXmlElement *m_pParentElement;

	POSITION m_posFind;
	CString m_strFind;

	CString GetValue(CString attribute);
};

class CXmlDocument
{
public:
	CXmlDocument();
	virtual ~CXmlDocument();

	//CString Generate();
	BOOL Parse(LPCTSTR lpszString);

	//BOOL Load(LPCTSTR lpszFileName);
	//BOOL Store(LPCTSTR lpszFileName);
	CXmlElement *GetFirstChild(CXmlElement *pElement);
	CXmlElement *GetRootElement() { return &m_RootElement; }
	CXmlElement * CXmlDocument::GetNextSibling(CXmlElement *pElement);
	
	CXmlElement *FindElement(CXmlElement *pElement, LPCTSTR lpszName);
	CXmlElement *FindNextElement(CXmlElement *pElement);

	CXmlElement *AddElement(CXmlElement *pElement, LPCTSTR lpszName, LPCTSTR lpszData = NULL, LPCTSTR lpszAttributes = NULL);

	void DeleteContents();

protected:
	int m_nLevel;
	int ValidateTag(CString &strTag, CString &strResult);
	//BOOL CreateTag(CXmlElement *pElement, CString &strTag);

	CString m_strXml;

	CXmlElement m_RootElement;
	CXmlElement *m_pCurElement;
};

#endif //XMLDOCUMENT_H
