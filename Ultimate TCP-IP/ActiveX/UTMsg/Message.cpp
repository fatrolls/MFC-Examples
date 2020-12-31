//=================================================================
//  class: CMessage
//  File:  Message.cpp
//
//  Implementation of CMessage class
//
//=================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//=================================================================

#include "stdafx.h"
#include "UTMsg.h"
#include "Message.h"
#include "AboutDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CMessage
/////////////////////////////////////////////////////////////////////////////
/***************************************************
CMessage
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CMessage::CMessage() 
{
	// Load Message Icon
	m_hMessageIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_MESSAGE));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
  
}

/***************************************************
~CMessage
	Destructor.
Params
    none
Return
	none
****************************************************/
CMessage::~CMessage()
{
	// Destroy Message icon handle
	if(m_hMessageIcon) {
		DestroyIcon( m_hMessageIcon );							
		m_hMessageIcon = NULL;
		}
}

/***************************************************
InterfaceSupportsErrorInfo
	Checks if specified interface supports error
	information.
Params
    riid	- inteface id
Return
	S_OK	- support error info
	S_FALSE - don't support error info
****************************************************/
STDMETHODIMP CMessage::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMessage,
	};
	for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

/***************************************************
OnDraw
	Draw the icon
Params
    di	- A reference to the ATL_DRAWINFO structure
Return
	S_OK	- success
****************************************************/
HRESULT CMessage::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Message Icon
	if(m_hMessageIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hMessageIcon);	
 		
	return S_OK;
}



////////////////////////////////////////////////////
//	IMessage interface methods
////////////////////////////////////////////////////

/***************************************************
AboutBox
	Display about box
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMessage::AboutBox()
{
	CAboutDlg	dlg;

	dlg.DoModal();
	return S_OK;
}

/***************************************************
GetErrorText
	Returns a string representation of numeric error code.
Params
	ErrorCode	- number of error code
	ErrorText	- pointer to the error text varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
}

/***************************************************
GetInterfaceSafetyOptions
	Gets inteface safety options
Params
	riid				- interface ID
	pdwSupportedOptions	- supported options
	pdwEnabledOptions	- enabled options
Return
	S_OK			- success
	E_NOINTERFACE	- no such interface
	E_FAIL			- failed
****************************************************/
STDMETHODIMP CMessage::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
{

	ATLTRACE(_T("CObjectSafetyImpl::GetInterfaceSafetyOptions\n"));

	if (!pdwSupportedOptions || !pdwEnabledOptions)
		return E_FAIL;

	LPUNKNOWN pUnk;
	if (_InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE) {
		// Our object doesn't even support this interface.
		return E_NOINTERFACE;
		}
	else {
		// Cleanup after ourselves.
		pUnk->Release();
		pUnk = NULL;
		}

	if (riid == IID_IDispatch) {
		// IDispatch is an interface used for scripting. If your
		// control supports other IDispatch or Dual interfaces, you
		// may decide to add them here as well. Client wants to know
		// if object is safe for scripting. Only indicate safe for
		// scripting when the interface is safe.
		*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		*pdwEnabledOptions = m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		return S_OK;
		}
	else if ((riid == IID_IPersistStreamInit) || (riid == IID_IPersistStorage) || (riid == IID_IPersistPropertyBag)) {
		// IID_IPersistStreamInit and IID_IPersistStorage are
		// interfaces used for Initialization. If your control
		// supports other Persistence interfaces, you may decide to
		// add them here as well. Client wants to know if object is
		// safe for initializing. Only indicate safe for initializing
		// when the interface is safe.
		*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
		*pdwEnabledOptions = m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_DATA;
		return S_OK;
		}
	else {
		// We are saying that no other interfaces in this control are
		// safe for initializing or scripting.
		*pdwSupportedOptions = 0;
		*pdwEnabledOptions = 0;
		return E_FAIL;
		}
   }


/***************************************************
SetInterfaceSafetyOptions
	Sets inteface safety options
Params
	riid				- interface ID
	dwOptionSetMask		- options mask
	pdwEnabledOptions	- enabled options
Return
	S_OK			- success
	E_NOINTERFACE	- no such interface
	E_FAIL			- failed
****************************************************/
STDMETHODIMP CMessage::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
{

	ATLTRACE(_T("CObjectSafetyImpl::SetInterfaceSafetyOptions\n"));

	if (!dwOptionSetMask && !dwEnabledOptions) return E_FAIL;
   
	LPUNKNOWN pUnk;
	if (_InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE) {
		// Our object doesn't even support this interface.
		return E_NOINTERFACE;
		}
	else {
		// Cleanup after ourselves.
		pUnk->Release();
		pUnk = NULL;
		}

	// Store our current safety level to return in
	// GetInterfaceSafetyOptions
	m_dwCurrentSafety |= dwEnabledOptions & dwOptionSetMask;
	if ((riid == IID_IDispatch) && (m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_CALLER)) {
		// Client wants us to disable any functionality that would
		// make the control unsafe for scripting. The same applies to
		// any other IDispatch or Dual interfaces your control may
		// support. Because our control is safe for scripting by
		// default we just return S_OK.
		return S_OK;
		}
	else if (((riid == IID_IPersistStreamInit) || (riid == IID_IPersistStorage) || (riid == IID_IPersistPropertyBag)) &&
             (m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_DATA)) {
		// Client wants us to make the control safe for initializing
		// from persistent data. For these interfaces, this control
		// is safe so we return S_OK. For Any interfaces that are not
		// safe, we would return E_FAIL.
		return S_OK;
		}
	else {
		// This control doesn't allow Initialization or Scripting
		// from any other interfaces so return E_FAIL.
		return E_FAIL;
		}
}

/***************************************************
AddAttachment
	Adds attachment to the message
Params
	FileName	- full path to add
    Params      - optional attachment parameters separated by ','.
                  Different encoding classes will have different needs. 
                  e.g. the UUEncode ignores the string entirely, 
                  whereas the MimeEncode uses the first four:

                  The first string in the list contains the encoding 
                  type, which can be any of the following values:
  
                        "0" - CUT_MIME_7BIT
                        "1" - CUT_MIME_BASE64
                        "2" - CUT_MIME_QUOTEDPRINTABLE
                        "3" - CUT_MIME_8BIT
                        "4" - CUT_MIME_BINARY

                  The second string contains MIME compliant content 
                  type that the attachment will be identified by,
                  E.g. "image/bmp"

                  The third string contains the char-set portion of 
                  the content type, E.g. "US-ASCII"

                  The fourth string contains attachment type.

                  Each of these can be the empty string, in which 
                  case the default will be used.
 
	Result	    - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::AddAttachment(BSTR FileName, BSTR Params, long *Result)
{
    CUT_StringList  listParams;
	int				index = 0;
	char			buffer[1024];

    // Make String list out of string items separated with coma
    while(CUT_StrMethods::ParseString(_bstr_t(Params), ",", index++, buffer, sizeof(buffer)-1) == UTE_SUCCESS)
		listParams.AddString(buffer);

    // Call message class function
    *Result = CUT_Msg::AddAttachment(_bstr_t(FileName), &listParams);
	return S_OK;
}

/***************************************************
GetAttachmentNumber
	Gets the number of the attachments
Params
	Number	- pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetAttachmentNumber(long *Number)
{
	*Number = CUT_Msg::GetAttachmentNumber();
	return S_OK;
}

/***************************************************
EmptyAttachmentList
	Clears attachment list
Params
	none
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::EmptyAttachmentList()
{
	CUT_Msg::EmptyAttachmentList();
	return S_OK;
}

/***************************************************
GetAttachmentSize
	Gets attachment size
Params
    Index   - index of the attachment or -1 to get
              the size of all attachments.
	Size	- pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetAttachmentSize(long Index, long *Size)
{
	*Size = CUT_Msg::GetAttachmentSize(Index);
	return S_OK;
}

/***************************************************
GetAttachmentName
	Gets attachment name
Params
    Index   - index of the attachment.
	Name	- pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetAttachmentName(long Index, BSTR *Name)
{
    _bstr_t         bstrName;
 	HRESULT		    hResult			= S_OK;
    char            szName[MAX_PATH+1], szType[MAX_PATH+1];
    CUT_StringList  listParams;
 
    if(CUT_Msg::GetAttachmentInfo(Index, szName, MAX_PATH, szType, MAX_PATH, &listParams) == UTE_SUCCESS) 
        bstrName = szName;

 	if(!SysReAllocString(Name, bstrName))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
GetAttachmentType
	Gets attachment type
Params
    Index   - index of the attachment.
	Type	- pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetAttachmentType(long Index, BSTR *Type)
{
    _bstr_t         bstrType;
 	HRESULT		    hResult			= S_OK;
    char            szName[MAX_PATH+1], szType[MAX_PATH+1];
    CUT_StringList  listParams;
 
    if(CUT_Msg::GetAttachmentInfo(Index, szName, MAX_PATH, szType, MAX_PATH, &listParams) == UTE_SUCCESS) 
        bstrType = szType;

 	if(!SysReAllocString(Type, bstrType))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
GetAttachmentParam
	Gets attachment optional param. 
    UUEncode class will not use this. 
    The MimeEncode will return the encoding type (e.g. 7bit, base-64) 
    See AddAttachment function.
Params
    Index   - index of the attachment.
	Param	- pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetAttachmentParam(long Index, BSTR *Param)
{
    _bstr_t         bstrParam;
 	HRESULT		    hResult			= S_OK;
    char            szName[MAX_PATH+1], szType[MAX_PATH+1];
    CUT_StringList  listParams;
 
    if(CUT_Msg::GetAttachmentInfo(Index, szName, MAX_PATH, szType, MAX_PATH, &listParams) == UTE_SUCCESS) 
        for(int i=0; i < listParams.GetCount(); i++) {
            if(i != 0)
                bstrParam += ",";
            bstrParam += listParams.GetString(i);
            }

 	if(!SysReAllocString(Param, bstrParam))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
AddAttachmentHeaderTag
	Add custom headers to an individual attachment
	Affect the last added attachment. Can be called
	several times to form a list of headers.
Params
    Tag     - tag to add
	Param	- pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::AddAttachmentHeaderTag(BSTR Tag, long *Result)
{
	*Result = CUT_Msg::AddAttachmentHeaderTag(_bstr_t(Tag));
	return S_OK;
}

/***************************************************
SetDefaultEncoding
	Sets default encoding MIME or UUEncode.
    Default is Mime.
Params
    Type    - etUUEncode or etMime
	Result	- pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::SetDefaultEncoding(EncodingType Type, long *Result)
{
    *Result = CUT_Msg::SetDefEncoding((Type == etMime) ? "Mime" : "UUEncode");
	return S_OK;
}

/***************************************************
GetCustomFieldName
	Gets custom field name by index
Params
    Index   - index of the field to get
	Name    - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetCustomFieldName(long Index, BSTR *Name)
{
 	HRESULT		hResult			= S_OK;
 
 	if(!SysReAllocString(Name, _bstr_t(CUT_Msg::GetCustomFieldName(Index))))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
GetFieldName
	Gets field name by field ID
Params
    Field   - field id
	Name    - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetFieldName(HeaderFieldType Field, BSTR *Name)
{
 	HRESULT		hResult			= S_OK;
 
 	if(!SysReAllocString(Name, _bstr_t(CUT_Msg::GetFieldName((HeaderFieldID)Field))))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
GetMessageBody
	Gets message body text
Params
    Text    - message body text
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetMessageBody(BSTR *Text)
{
 	HRESULT		hResult			= S_OK;
 
 	if(!SysReAllocString(Text, _bstr_t(CUT_Msg::GetMessageBody())))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
SetMessageBody
	Sets message body text
Params
    Text    - message body text to set
    Result  - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::SetMessageBody(BSTR Text, long *Result)
{
	*Result = UTE_MSG_BODY_TOO_BIG;
    if(CUT_Msg::SetMessageBody(_bstr_t(Text)))
        *Result = UTE_SUCCESS;

	return S_OK;
}

/***************************************************
AddHeaderField
	Adds a new message field. If nID == UTM_CUSTOM_FIELD
	you must specify the name of the field in lpszFieldName
Params
    Data		- pointer to the field's field data
    Type		- ID of the field 
	[FieldName] - pointer to the field's field name
    Result      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::AddHeaderField(BSTR Data, HeaderFieldType Type, BSTR FieldName, long *Result)
{
	*Result = UTE_ERROR;
    if(CUT_Msg::AddHeaderField(_bstr_t(Data), (HeaderFieldID)Type, _bstr_t(FieldName)) != 0)
        *Result = UTE_SUCCESS;

	return S_OK;
}

/***************************************************
ClearHeader
	Clears fields
Params
    Type		- ID of the field to clear
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::ClearHeader(HeaderFieldType Type, BSTR CustomName)
{
    _bstr_t bstrCustomName = CustomName;
    if(bstrCustomName.length() > 0)
	    CUT_Msg::ClearHeader((HeaderFieldID)Type, bstrCustomName);
    else
        CUT_Msg::ClearHeader((HeaderFieldID)Type);
	return S_OK;
}

/***************************************************
GetHeaderCountByName
	Returns number of field with specified name
Params
    Name        - name of the fields to count
    Number      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetHeaderCountByName(BSTR Name, long *Number)
{
	*Number = CUT_Msg::GetHeaderCount(_bstr_t(Name));
	return S_OK;
}

/***************************************************
GetHeaderCountByType
	Returns number of field with specified type
Params
    Type        - type of the fields to count
    Number      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetHeaderCountByType(HeaderFieldType Type, long *Number)
{
	*Number = CUT_Msg::GetHeaderCount((HeaderFieldID)Type);
	return S_OK;
}

/***************************************************
GetHeaderByName
	Get header field data with specified index by it's name
Params
    Name        - field name
    Index       - index of the field
    Header      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetHeaderByName(BSTR Name, long Index, BSTR *Header)
{
 	HRESULT		hResult			= S_OK;
    _bstr_t     bstrHeader;
 
    if(Index == -1) {
        char    szBuffer[5120];
        if(CUT_Msg::GetHeaderByName(_bstr_t(Name), szBuffer, sizeof(szBuffer)-1))
            bstrHeader = szBuffer;
        }
    else
        bstrHeader = CUT_Msg::GetHeaderByName(_bstr_t(Name), Index);

 	if(!SysReAllocString(Header, bstrHeader))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
GetHeaderByType
	Get header field data with specified index by it's type
Params
    Type        - type of the field
    Index       - index of the field
    Header      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::GetHeaderByType(HeaderFieldType Type, long Index, BSTR *Header)
{
 	HRESULT		hResult			= S_OK;
    _bstr_t     bstrHeader;
 
    if(Index == -1) {
        char    szBuffer[5120];
        if(CUT_Msg::GetHeaderByType((HeaderFieldID)Type, szBuffer, sizeof(szBuffer)-1))
            bstrHeader = szBuffer;
        }
    else
        bstrHeader = CUT_Msg::GetHeaderByType((HeaderFieldID)Type, Index);

 	if(!SysReAllocString(Header, bstrHeader))
 		hResult = E_OUTOFMEMORY;

	return hResult;
}

/***************************************************
Load
	Loads message from the file
Params
    FileName    - file name to load
    Result      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::Load(BSTR FileName, long *Result)
{
	*Result = CUT_Msg::LoadMessage(_bstr_t(FileName));
	return S_OK;
}

/***************************************************
Save
	Saves message to the file
Params
    FileName    - file name to save
    Result      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::Save(BSTR FileName, long *Result)
{
	*Result = CUT_Msg::SaveMessage(_bstr_t(FileName));
	return S_OK;
}

/***************************************************
DecodeAttachment
	Decodes attachment
Params
    Index       - zero based index of the attachment
    FileName    - file name to save
    Result      - pointer to the varaible receiving the return value
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMessage::DecodeAttachment(long Index, BSTR FileName, long *Result)
{
	*Result = CUT_Msg::Decode(Index, _bstr_t(FileName));
	return S_OK;
}
