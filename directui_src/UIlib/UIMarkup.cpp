
#include "StdAfx.h"

#ifndef TRACE
   #define TRACE
#endif


///////////////////////////////////////////////////////////////////////////////////////
//
//
//

CMarkupNode::CMarkupNode() : m_pOwner(NULL)
{
}

CMarkupNode::CMarkupNode(CMarkup* pOwner, int iPos) : m_pOwner(pOwner), m_iPos(iPos), m_nAttributes(0)
{
}

CMarkupNode CMarkupNode::GetSibling()
{
   if( m_pOwner == NULL ) return CMarkupNode();
   ULONG iPos = m_pOwner->m_pElements[m_iPos].iNext;
   if( iPos == 0 ) return CMarkupNode();
   return CMarkupNode(m_pOwner, iPos);
}

bool CMarkupNode::HasSiblings() const
{
   if( m_pOwner == NULL ) return false;
   ULONG iPos = m_pOwner->m_pElements[m_iPos].iNext;
   return iPos > 0;
}

CMarkupNode CMarkupNode::GetChild()
{
   if( m_pOwner == NULL ) return CMarkupNode();
   ULONG iPos = m_pOwner->m_pElements[m_iPos].iChild;
   if( iPos == 0 ) return CMarkupNode();
   return CMarkupNode(m_pOwner, iPos);
}

CMarkupNode CMarkupNode::GetChild(LPCTSTR pstrName)
{
   if( m_pOwner == NULL ) return CMarkupNode();
   ULONG iPos = m_pOwner->m_pElements[m_iPos].iChild;
   while( iPos != 0 ) {
      if( _tcscmp(m_pOwner->m_pstrXML + m_pOwner->m_pElements[iPos].iStart, pstrName) == 0 ) {
         return CMarkupNode(m_pOwner, iPos);
      }
      iPos = m_pOwner->m_pElements[iPos].iNext;
   }
   return CMarkupNode();
}

bool CMarkupNode::HasChildren() const
{
   if( m_pOwner == NULL ) return false;
   return m_pOwner->m_pElements[m_iPos].iChild != 0;
}

CMarkupNode CMarkupNode::GetParent()
{
   if( m_pOwner == NULL ) return CMarkupNode();
   ULONG iPos = m_pOwner->m_pElements[m_iPos].iParent;
   if( iPos == 0 ) return CMarkupNode();
   return CMarkupNode(m_pOwner, iPos);
}

bool CMarkupNode::IsValid() const
{
   return m_pOwner != NULL;
}

LPCTSTR CMarkupNode::GetName() const
{
   if( m_pOwner == NULL ) return NULL;
   return m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iStart;
}

LPCTSTR CMarkupNode::GetValue() const
{
   if( m_pOwner == NULL ) return NULL;
   return m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iData;
}

LPCTSTR CMarkupNode::GetAttributeName(int iIndex)
{
   if( m_pOwner == NULL ) return NULL;
   if( m_nAttributes == 0 ) _MapAttributes();
   if( iIndex < 0 || iIndex >= m_nAttributes ) return _T("");
   return m_pOwner->m_pstrXML + m_aAttributes[iIndex].iName;
}

LPCTSTR CMarkupNode::GetAttributeValue(int iIndex)
{
   if( m_pOwner == NULL ) return NULL;
   if( m_nAttributes == 0 ) _MapAttributes();
   if( iIndex < 0 || iIndex >= m_nAttributes ) return _T("");
   return m_pOwner->m_pstrXML + m_aAttributes[iIndex].iValue;
}

LPCTSTR CMarkupNode::GetAttributeValue(LPCTSTR pstrName)
{
   if( m_pOwner == NULL ) return NULL;
   if( m_nAttributes == 0 ) _MapAttributes();
   for( int i = 0; i < m_nAttributes; i++ ) {
      if( _tcscmp(m_pOwner->m_pstrXML + m_aAttributes[i].iName, pstrName) == 0 ) return m_pOwner->m_pstrXML + m_aAttributes[i].iValue;
   }
   return _T("");
}

bool CMarkupNode::GetAttributeValue(int iIndex, LPTSTR pstrValue, SIZE_T cchMax)
{
   if( m_pOwner == NULL ) return false;
   if( m_nAttributes == 0 ) _MapAttributes();
   if( iIndex < 0 || iIndex >= m_nAttributes ) return false;
   _tcsncpy(pstrValue, m_pOwner->m_pstrXML + m_aAttributes[iIndex].iValue, cchMax);
   return true;
}

bool CMarkupNode::GetAttributeValue(LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax)
{
   if( m_pOwner == NULL ) return false;
   if( m_nAttributes == 0 ) _MapAttributes();
   for( int i = 0; i < m_nAttributes; i++ ) {
      if( _tcscmp(m_pOwner->m_pstrXML + m_aAttributes[i].iName, pstrName) == 0 ) {
         _tcsncpy(pstrValue, m_pOwner->m_pstrXML + m_aAttributes[i].iValue, cchMax);
         return true;
      }
   }
   return false;
}

int CMarkupNode::GetAttributeCount()
{
   if( m_pOwner == NULL ) return 0;
   if( m_nAttributes == 0 ) _MapAttributes();
   return m_nAttributes;
}

bool CMarkupNode::HasAttributes()
{
   if( m_pOwner == NULL ) return false;
   if( m_nAttributes == 0 ) _MapAttributes();
   return m_nAttributes > 0;
}

bool CMarkupNode::HasAttribute(LPCTSTR pstrName)
{
   if( m_pOwner == NULL ) return false;
   if( m_nAttributes == 0 ) _MapAttributes();
   for( int i = 0; i < m_nAttributes; i++ ) {
      if( _tcscmp(m_pOwner->m_pstrXML + m_aAttributes[i].iName, pstrName) == 0 ) return true;
   }
   return false;
}

void CMarkupNode::_MapAttributes()
{
   m_nAttributes = 0;
   LPCTSTR pstr = m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iStart;
   LPCTSTR pstrEnd = m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iData;
   pstr += _tcslen(pstr) + 1;
   while( pstr < pstrEnd ) {
      m_pOwner->_SkipWhitespace(pstr);
      m_aAttributes[m_nAttributes].iName = pstr - m_pOwner->m_pstrXML;
      pstr += _tcslen(pstr) + 1;
      if( *pstr++ != '\"' && *pstr++ != '\'' ) return;
      m_aAttributes[m_nAttributes++].iValue = pstr - m_pOwner->m_pstrXML;
      if( m_nAttributes >= MAX_XML_ATTRIBUTES ) return;
      pstr += _tcslen(pstr) + 1;
   }
}


///////////////////////////////////////////////////////////////////////////////////////
//
//
//

CMarkup::CMarkup(LPCTSTR pstrXML)
{
   m_pstrXML = NULL;
   m_pElements = NULL;
   m_nElements = 0;
   m_bPreserveWhitespace = false;
   if( pstrXML != NULL ) Load(pstrXML);
}

CMarkup::~CMarkup()
{
   Release();
}

bool CMarkup::IsValid() const
{
   return m_pElements != NULL;
}

void CMarkup::SetPreserveWhitespace(bool bPreserve)
{
   m_bPreserveWhitespace = bPreserve;
}

bool CMarkup::Load(LPCTSTR pstrXML)
{
   Release();
   SIZE_T cbLen = (_tcslen(pstrXML) + 1) * sizeof(TCHAR);
   m_pstrXML = static_cast<LPTSTR>(malloc(cbLen));
   ::CopyMemory(m_pstrXML, pstrXML, cbLen);
   bool bRes = _Parse();
   if( !bRes ) Release();
   return bRes;
}

bool CMarkup::LoadFromFile(LPCTSTR pstrFilename)
{
   Release();
   HANDLE hFile = ::CreateFile(pstrFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if( hFile == INVALID_HANDLE_VALUE ) return _Failed(_T("Error opening file"));
   DWORD dwSize = ::GetFileSize(hFile, NULL);
   if( dwSize == 0 ) return _Failed(_T("File is empty"));
   DWORD dwRead = 0;
#ifdef _UNICODE
   // BUG: We don't support UNICODE file loading yet.
   ::CloseHandle(hFile);
   return false;
#else
   m_pstrXML = static_cast<LPTSTR>(malloc(dwSize + 1));
   ::ReadFile(hFile, m_pstrXML, dwSize, &dwRead, NULL);
   ::CloseHandle(hFile);
   m_pstrXML[dwSize] = '\0';
#endif // _UNICODE
   if( dwRead != dwSize ) {
      Release();
      return _Failed(_T("Could not read file"));
   }
   bool bRes = _Parse();
   if( !bRes ) Release();
   return bRes;
}

void CMarkup::Release()
{
   if( m_pstrXML != NULL ) free(m_pstrXML);
   if( m_pElements != NULL ) free(m_pElements);
   m_pstrXML = NULL;
   m_pElements = NULL;
   m_nElements;
}

void CMarkup::GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const
{
   _tcsncpy(pstrMessage, m_szErrorMsg, cchMax);
}

void CMarkup::GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const
{
   _tcsncpy(pstrSource, m_szErrorXML, cchMax);
}

CMarkupNode CMarkup::GetRoot()
{
   if( m_nElements == 0 ) return CMarkupNode();
   return CMarkupNode(this, 1);
}

bool CMarkup::_Parse()
{
   _ReserveElement(); // Reserve index 0 for errors
   ::ZeroMemory(m_szErrorMsg, sizeof(m_szErrorMsg));
   ::ZeroMemory(m_szErrorXML, sizeof(m_szErrorXML));
   LPTSTR pstrXML = m_pstrXML;
   return _Parse(pstrXML, 0);
}

bool CMarkup::_Parse(LPTSTR& pstrText, ULONG iParent)
{
   ULONG iPrevious = 0;
   for( ; ; ) 
   {
      if( *pstrText == '\0' && iParent <= 1 ) return true;
      if( *pstrText != '<' ) return _Failed(_T("Expected start tag"), pstrText);
      if( pstrText[1] == '/' ) return true;
      *pstrText++ = '\0';
      // Skip comment or processing directive
      if( *pstrText == '!' || *pstrText == '?' ) {
         TCHAR chEnd = *pstrText == '!' ? '-' : '?';
         while( *pstrText != '\0' && !(*pstrText == chEnd && *(pstrText + 1) == '>') ) pstrText = ::CharNext(pstrText);
         if( *pstrText != '\0' ) pstrText += 2;
         _SkipWhitespace(pstrText);
         continue;
      }
      // Fill out element structure
      XMLELEMENT* pEl = _ReserveElement();
      ULONG iPos = pEl - m_pElements;
      pEl->iStart = pstrText - m_pstrXML;
      pEl->iParent = iParent;
      pEl->iNext = pEl->iChild = 0;
      if( iPrevious != 0 ) m_pElements[iPrevious].iNext = iPos;
      else if( iParent > 0 ) m_pElements[iParent].iChild = iPos;
      iPrevious = iPos;
      // Parse name
      LPCTSTR pstrName = pstrText;
      _SkipIdentifier(pstrText);
      LPTSTR pstrNameEnd = pstrText;
      if( *pstrText == '\0' ) return _Failed(_T("Error parsing element name"), pstrText);
      // Parse attributes
      if( !_ParseAttributes(pstrText) ) return false;
      _SkipWhitespace(pstrText);
      if( pstrText[0] == '/' && pstrText[1] == '>' )
      {
         pEl->iData = pstrText - m_pstrXML;
         *pstrText = '\0';
         pstrText += 2;
      }
      else
      {
         if( *pstrText != '>' ) return _Failed(_T("Expected start-tag closing"), pstrText);
         // Parse node data
         pEl->iData = ++pstrText - m_pstrXML;
         LPTSTR pstrDest = pstrText;
         if( !_ParseData(pstrText, pstrDest, '<') ) return false;
         // Determine type of next element
         if( *pstrText == '\0' && iParent <= 1 ) return true;
         if( *pstrText != '<' ) return _Failed(_T("Expected end-tag start"), pstrText);
         if( pstrText[0] == '<' && pstrText[1] != '/' ) 
         {
            if( !_Parse(pstrText, iPos) ) return false;
         }
         if( pstrText[0] == '<' && pstrText[1] == '/' ) 
         {
            *pstrDest = '\0';
            *pstrText = '\0';
            pstrText += 2;
            SIZE_T cchName = pstrNameEnd - pstrName;
            if( _tcsncmp(pstrText, pstrName, cchName) != 0 ) return _Failed(_T("Unmatched closing tag"), pstrText);
            if( pstrText[cchName] != '>' ) return _Failed(_T("Unmatched closing tag"), pstrText);
            pstrText += cchName + 1;
         }
      }
      *pstrNameEnd = '\0';
      _SkipWhitespace(pstrText);
   }
}

CMarkup::XMLELEMENT* CMarkup::_ReserveElement()
{
   if( m_nElements == 0 ) m_nReservedElements = 0;
   if( m_nElements >= m_nReservedElements ) {
      m_nReservedElements += (m_nReservedElements / 2) + 500;
      m_pElements = static_cast<XMLELEMENT*>(realloc(m_pElements, m_nReservedElements * sizeof(XMLELEMENT)));
   }
   return &m_pElements[m_nElements++];
}

void CMarkup::_SkipWhitespace(LPCTSTR& pstr) const
{
   while( *pstr != '\0' && *pstr <= ' ' ) pstr++;
}

void CMarkup::_SkipWhitespace(LPTSTR& pstr) const
{
   while( *pstr != '\0' && *pstr <= ' ' ) pstr++;
}

void CMarkup::_SkipIdentifier(LPCTSTR& pstr) const
{
   while( *pstr != '\0' && (*pstr == '_' || *pstr == ':' || _istalnum(*pstr)) ) pstr++;
}

void CMarkup::_SkipIdentifier(LPTSTR& pstr) const
{
   while( *pstr != '\0' && (*pstr == '_' || *pstr == ':' || _istalnum(*pstr)) ) pstr++;
}

bool CMarkup::_ParseAttributes(LPTSTR& pstrText)
{   
   if( *pstrText == '>' ) return true;
   *pstrText++ = '\0';
   _SkipWhitespace(pstrText);
   while( *pstrText != '\0' && *pstrText != '>' && *pstrText != '/' ) {
      _SkipIdentifier(pstrText);
      if( *pstrText != '=' ) return _Failed(_T("Error while parsing attributes"), pstrText);
      *pstrText++ = '\0';
      TCHAR chQuote = *pstrText++;
      if( chQuote != '\"' && chQuote != '\'' ) return _Failed(_T("Expected attribute value"), pstrText);
      LPTSTR pstrDest = pstrText;
      if( !_ParseData(pstrText, pstrDest, chQuote) ) return false;
      if( *pstrText == '\0' ) return _Failed(_T("Error while parsing attribute string"), pstrText);
      *pstrDest = '\0';
      *pstrText++ = '\0';
      _SkipWhitespace(pstrText);
   }
   return true;
}

bool CMarkup::_ParseData(LPTSTR& pstrText, LPTSTR& pstrDest, char cEnd)
{
   while( *pstrText != '\0' && *pstrText != cEnd ) {
      if( *pstrText == '&' ) {
         _ParseMetaChar(++pstrText, pstrDest);
      }
      if( *pstrText == ' ' ) {
         *pstrDest++ = *pstrText++;
         if( !m_bPreserveWhitespace ) _SkipWhitespace(pstrText);
      }
      else {
         *pstrDest++ = *pstrText++;
#ifdef _MBCS
         if( ::IsDBCSLeadByte(*(pstrText - 1)) ) *pstrDest++ = *pstrText++;
#endif // _MBCS
      }
   }
   // Make sure that MapAttributes() works correctly when it parses
   // over a value that has been transformed.
   LPTSTR pstrFill = pstrDest + 1;
   while( pstrFill < pstrText ) *pstrFill++ = ' ';
   return true;
}

void CMarkup::_ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest)
{
   if( pstrText[0] == 'a' && pstrText[1] == 'm' && pstrText[2] == 'p' && pstrText[3] == ';' ) {
      *pstrDest++ = '&';
      pstrText += 4;
   }
   else if( pstrText[0] == 'l' && pstrText[1] == 't' && pstrText[2] == ';' ) {
      *pstrDest++ = '<';
      pstrText += 3;
   }
   else if( pstrText[0] == 'g' && pstrText[1] == 't' && pstrText[2] == ';' ) {
      *pstrDest++ = '>';
      pstrText += 3;
   }
   else if( pstrText[0] == 'q' && pstrText[1] == 'u' && pstrText[2] == 'o' && pstrText[3] == 't' && pstrText[4] == ';' ) {
      *pstrDest++ = '\"';
      pstrText += 5;
   }
   else if( pstrText[0] == 'a' && pstrText[1] == 'p' && pstrText[2] == 'o' && pstrText[3] == 's' && pstrText[4] == ';' ) {
      *pstrDest++ = '\'';
      pstrText += 5;
   }
   else {
      *pstrDest++ = '&';
   }
}

bool CMarkup::_Failed(LPCTSTR pstrError, LPCTSTR pstrLocation)
{
   // Register last error
   TRACE("XML Error: %s", pstrError);
   TRACE(pstrLocation);
   _tcsncpy(m_szErrorMsg, pstrError, (sizeof(m_szErrorMsg) / sizeof(m_szErrorMsg[0])) - 1);
   _tcsncpy(m_szErrorXML, pstrLocation != NULL ? pstrLocation : _T(""), lengthof(m_szErrorXML) - 1);
   return false; // Always return 'false'
}

