// ==========================================================================
// 					Class Specification : MAPI Framework
//						COXMSession;
//						COXMInfoStores;
//						COXMInfoStore;
//						COXMFolders;
//						COXMFolder;
//						COXMMessages;
//						COXMMessage;
//						COXMFields;
//						COXMField;
//						COXMRecipients;
//						COXMRecipient;
//						COXMAttachments;
//						COXMAttachment;
//						COXMAddressEntry;

// ==========================================================================

// Header file : oxmdisp.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "oxmdisp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COXMSession class

CString COXMSession::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

EOXMClass COXMSession::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LPUNKNOWN COXMSession::GetMapiobject()
{
	VARIANT result;
	GetProperty(0x31, VT_VARIANT, (void*)&result);
	return result.punkVal;
}

void COXMSession::SetMapiobject(LPUNKNOWN pSession)
{
	COleVariant vSession;
	vSession.vt = VT_UNKNOWN;
	vSession.punkVal = pSession;
	SetProperty(0x31, VT_VARIANT, &vSession);
}

CString COXMSession::GetVersion()
{
	VARIANT result;
	GetProperty(0x2c, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMSession::GetOperatingSystem()
{
	VARIANT result;
	GetProperty(0x18, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMSession::GetName()
{
	VARIANT result;
	GetProperty(0x17, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMAddressEntry COXMSession::GetCurrentUser()
{
	COXMAddressEntry entry;
	VARIANT result;
	GetProperty(0x1, VT_VARIANT, (void*)&result);
	entry.m_bCurrentSessionUser = TRUE;
	entry.AttachDispatch(result.pdispVal);
	return entry;
}

COXMFolder COXMSession::GetInbox()
{
	VARIANT result;
	GetProperty(0xf, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMFolder COXMSession::GetOutbox()
{
	VARIANT result;
	GetProperty(0x10, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMInfoStores COXMSession::GetInfoStores()
{
	VARIANT result;
	GetProperty(0x39, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}


void COXMSession::Logon(CString sProfileName /*= _T("")*/, CString sProfilePassword /*= _T("")*/, BOOL bShowDialog /*= TRUE*/, BOOL bNewSession /*= FALSE*/, HWND hParentWindow /*= NULL*/)
{
	VARIANT result;
	COleVariant vProfileName;
	if (!sProfileName.IsEmpty())
		vProfileName = sProfileName;
	COleVariant vProfilePassword;
	if (!sProfilePassword.IsEmpty())
		vProfilePassword = sProfilePassword;
	COleVariant vShowDialog((short)bShowDialog, VT_BOOL);
	COleVariant vNewSession((short)bNewSession, VT_BOOL);
	COleVariant vParentWindow((LONG) hParentWindow);
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x77, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vProfileName, &vProfilePassword, &vShowDialog, &vNewSession, &vParentWindow);
}

void COXMSession::Logoff()
{
	VARIANT result;
	InvokeHelper(0x76, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}

COXMInfoStore COXMSession::GetInfoStore(CString sStoreID)
{
	VARIANT result;
	COleVariant vStoreID(sStoreID);

	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vStoreID);
	return result.pdispVal;
}

COXMFolder COXMSession::GetFolder(CString sFolderID, CString sStoreID /*=_T("")*/)
{
	VARIANT result;
	COleVariant vFolderID(sFolderID);
	COleVariant vStoreID;
	
	if (!sStoreID.IsEmpty())
		vStoreID = sStoreID;

	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x74, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vFolderID, &vStoreID);
	return result.pdispVal;
}

COXMMessage COXMSession::GetMessage(CString sMessageID, CString sStoreID /*=NULL*/)
{
	VARIANT result;
	COleVariant vMessageID(sMessageID);
	COleVariant vStoreID;
	if (!sStoreID.IsEmpty())
		vStoreID = sStoreID;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vMessageID, &vStoreID);
	return result.pdispVal;
}

COXMAddressEntry COXMSession::GetAddressEntry(CString sEntryID)
{
	VARIANT result;
	COleVariant vEntryID(sEntryID);
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x72, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vEntryID);
	return result.pdispVal;
}

COXMRecipients COXMSession::AddressBook(LPDISPATCH pRecipients /*= NULL*/,
	CString sTitle /*= _T("")*/,
	BOOL bOneAddress /*= FALSE*/,
	BOOL bForceResolution /*= TRUE*/,
	LONG nRecipLists /*= 0*/,
	CString sTOLabel /*= _T(")*/,
	CString sCCLabel /*= _T("")*/,
	CString sBCCLabel /*= _T("")*/, 
	HWND hParentWindow /*= NULL*/)
{
	VARIANT result;
	VARIANT vRecipients;
	vRecipients.vt = VT_DISPATCH;
	vRecipients.pdispVal = pRecipients;
	COleVariant vTitle(sTitle);
	COleVariant vOneAddress((short)bOneAddress, VT_BOOL);
	COleVariant vForceResolution((short)bForceResolution, VT_BOOL);
	COleVariant vRecipLists(nRecipLists);
	COleVariant vTOLabel;
	if (!sTOLabel.IsEmpty())
		vTOLabel = sTOLabel;
	COleVariant vCCLabel;
	if (!sCCLabel.IsEmpty())
		vCCLabel = sCCLabel;
	COleVariant vBCCLabel;
	if (!sBCCLabel.IsEmpty())
		vBCCLabel = sBCCLabel;
	COleVariant vParentWindow((LONG)hParentWindow);

	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vRecipients, &vTitle, &vOneAddress, &vForceResolution, &vRecipLists, &vTOLabel, &vCCLabel, &vBCCLabel, &vParentWindow);
	return result.pdispVal;
}


/////////////////////////////////////////////////////////////////////////////
// COXMInfoStores Class

CString COXMInfoStores::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

EOXMClass COXMInfoStores::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LONG COXMInfoStores::GetCount()
{
	VARIANT result;
	GetProperty(0x9, VT_VARIANT, (void*)&result);
	return result.lVal;
}

COXMInfoStore COXMInfoStores::GetItem(LONG nItem)
{
	COleVariant vItem(nItem);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&vItem);
	return result.pdispVal;
}


/////////////////////////////////////////////////////////////////////////////
// COXMInfoStore Class

CString COXMInfoStore::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMInfoStores COXMInfoStore::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMInfoStore::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMInfoStore::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LONG COXMInfoStore::GetIndex()
{
	VARIANT result;
	GetProperty(0x13, VT_VARIANT, (void*)&result);
	return result.lVal;
}

CString COXMInfoStore::GetName()
{
	VARIANT result;
	GetProperty(0x17, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMInfoStore::GetId()
{
	VARIANT result;
	GetProperty(0xe, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMInfoStore::GetProviderName()
{
	VARIANT result;
	GetProperty(0x3a, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMFolder COXMInfoStore::GetRootFolder()
{
	VARIANT result;
	GetProperty(0x3b, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

/////////////////////////////////////////////////////////////////////////////
// COXMFolder Class

CString COXMFolder::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

LPDISPATCH COXMFolder::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMFolder::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMFolder::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LPUNKNOWN COXMFolder::GetMapiobject()
{
	VARIANT result;
	GetProperty(0x31, VT_VARIANT, (void*)&result);
	return result.punkVal;
}

void COXMFolder::SetMapiobject(LPUNKNOWN punkVal)
{
	COleVariant vProp;
	vProp.vt = VT_UNKNOWN;
	vProp.punkVal = punkVal;
	SetProperty(0x31, VT_VARIANT, &vProp);
}

CString COXMFolder::GetName()
{
	VARIANT result;
	GetProperty(0x17, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMFolder::SetName(CString sName)
{
	COleVariant propVal(sName);
	SetProperty(0x17, VT_VARIANT, &propVal);
}

CString COXMFolder::GetId()
{
	VARIANT result;
	GetProperty(0xe, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMFolder::GetFolderID()
{
	VARIANT result;
	GetProperty(0x33, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMFolder::GetStoreID()
{
	VARIANT result;
	GetProperty(0x34, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMFolders COXMFolder::GetFolders()
{
	VARIANT result;
	GetProperty(0xd, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMMessages COXMFolder::GetMessages()
{
	VARIANT result;
	GetProperty(0x16, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMFields COXMFolder::GetFields()
{
	VARIANT result;
	GetProperty(0xc, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

void COXMFolder::Update(BOOL bMakePermanent /*= TRUE*/, BOOL bRrefreshObject /*= FALSE*/)
{
	COleVariant vMakePermanent((short) bMakePermanent, VT_BOOL);
	COleVariant vRefreshObject((short) bRrefreshObject, VT_BOOL);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x84, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vMakePermanent, &vRefreshObject);
}


/////////////////////////////////////////////////////////////////////////////
// COXMFolders properties

CString COXMFolders::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMFolder COXMFolders::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMFolders::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMFolders::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

COXMFolder COXMFolders::GetFirst()
{
	VARIANT result;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result.pdispVal;
}

COXMFolder COXMFolders::GetNext()
{
	VARIANT result;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result.pdispVal;
}

COXMFolder COXMFolders::GetLast()
{
	VARIANT result;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result.pdispVal;
}

COXMFolder COXMFolders::GetPrevious()
{
	VARIANT result;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result.pdispVal;
}


/////////////////////////////////////////////////////////////////////////////
// COXMMessages class

CString COXMMessages::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMFolder COXMMessages::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMMessages::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMMessages::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

COXMMessage COXMMessages::Add(CString sSubject /*= _T("")*/,
		CString sText /*= _T("")*/,
		CString sType /*= _T("")*/,
		LONG nImportance /*= 1*/)
{
	VARIANT result;
	COleVariant vSubject;
	if (!sSubject.IsEmpty())
		vSubject = sSubject;
	COleVariant vText;
	if (!sText.IsEmpty())
		vText = sText;
	COleVariant vType;
	if (!sType.IsEmpty())
		vType = sType;
	COleVariant vImportance(nImportance);

	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vSubject, &vText, &vType, &vImportance);
	return result.pdispVal;
}

void COXMMessages::Delete(BOOL bSubFolders /*= TRUE*/)
{
	COleVariant vSubFolders((short)bSubFolders, VT_BOOL);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vSubFolders);
}

void COXMMessages::Sort(LONG nSortOrder)
{
	COleVariant vSortOrder(nSortOrder);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x86, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vSortOrder);
}

COXMMessage COXMMessages::GetFirst(CString sFilter /*= _T("")*/)
{
	COleVariant vFilter;
	if (!sFilter.IsEmpty())
		vFilter = sFilter;
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vFilter);
	return result.pdispVal;
}

COXMMessage COXMMessages::GetNext()
{
	VARIANT result;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result.pdispVal;
}

COXMMessage COXMMessages::GetLast(CString sFilter /*= _T("")*/)
{
	COleVariant vFilter;
	if (!sFilter.IsEmpty())
		vFilter = sFilter;
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vFilter);
	return result.pdispVal;
}

COXMMessage COXMMessages::GetPrevious()
{
	VARIANT result;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result.pdispVal;
}


/////////////////////////////////////////////////////////////////////////////
// COXMMessage class

CString COXMMessage::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMMessages COXMMessage::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMMessage::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMMessage::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LPUNKNOWN COXMMessage::GetMapiobject()
{
	VARIANT result;
	GetProperty(0x31, VT_VARIANT, (void*)&result);
	return result.punkVal;
}

void COXMMessage::SetMapiobject(LPUNKNOWN pSession)
{
	COleVariant vSession;
	vSession.vt = VT_UNKNOWN;
	vSession.punkVal = pSession;
	SetProperty(0x31, VT_VARIANT, &vSession);
}

CString COXMMessage::GetId()
{
	VARIANT result;
	GetProperty(0xe, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMMessage::GetFolderID()
{
	VARIANT result;
	GetProperty(0x33, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMMessage::GetStoreID()
{
	VARIANT result;
	GetProperty(0x34, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

CString COXMMessage::GetType()
{
	VARIANT result;
	GetProperty(0x11, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMMessage::SetType(CString sType)
{
	COleVariant propVal(sType);
	SetProperty(0x11, VT_VARIANT, &propVal);
}

LONG COXMMessage::GetSize()
{
	VARIANT result;
	GetProperty(0x24, VT_VARIANT, (void*)&result);
	return result.lVal;
}

LONG COXMMessage::GetImportance()
{
	VARIANT result;
	GetProperty(0x1b, VT_VARIANT, (void*)&result);
	return result.lVal;
}

void COXMMessage::SetImportance(LONG nImportance)
{
	COleVariant  propVal(nImportance);
	SetProperty(0x1b, VT_VARIANT, &propVal);
}

CString COXMMessage::GetSubject()
{
	VARIANT result;
	GetProperty(0x26, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMMessage::SetSubject(CString sSubject)
{
	COleVariant propVal(sSubject);
	SetProperty(0x26, VT_VARIANT, &propVal);
}

COXMAddressEntry COXMMessage::GetSender()
{
	VARIANT result;
	GetProperty(0x20, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COleDateTime COXMMessage::GetTimeSent()
{
	VARIANT result;
	GetProperty(0x29, VT_VARIANT, (void*)&result);
	return result.date;
}

void COXMMessage::SetTimeSent(COleDateTime tDate)
{
	COleVariant propVal(tDate);
	SetProperty(0x29, VT_VARIANT, &propVal);
}

COleDateTime COXMMessage::GetTimeReceived()
{
	VARIANT result;
	GetProperty(0x28, VT_VARIANT, (void*)&result);
	return result.date;
}

void COXMMessage::SetTimeReceived(COleDateTime tDate)
{
	COleVariant propVal(tDate);
	SetProperty(0x28, VT_VARIANT, &propVal);
}

CString COXMMessage::GetText()
{
	VARIANT result;
	GetProperty(0x27, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMMessage::SetText(CString sText)
{
	COleVariant propVal(sText);
	SetProperty(0x27, VT_VARIANT, &propVal);
}

BOOL COXMMessage::GetSent()
{
	VARIANT result;
	GetProperty(0x21, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

void COXMMessage::SetSent(BOOL bSent)
{
	COleVariant propVal((short) bSent, VT_BOOL);
	SetProperty(0x21, VT_VARIANT, &propVal);
}

BOOL COXMMessage::GetSubmitted()
{
	VARIANT result;
	GetProperty(0x12, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

void COXMMessage::SetSubmitted(BOOL bFlag)
{
	COleVariant propVal((short) bFlag, VT_BOOL);
	SetProperty(0x12, VT_VARIANT, &propVal);
}

BOOL COXMMessage::GetUnread()
{
	VARIANT result;
	GetProperty(0x2a, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

void COXMMessage::SetUnread(BOOL bFlag)
{
	COleVariant propVal((short) bFlag, VT_BOOL);
	SetProperty(0x2a, VT_VARIANT, &propVal);
}

BOOL COXMMessage::GetSigned()
{
	VARIANT result;
	GetProperty(0x23, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

void COXMMessage::SetSigned(BOOL bFlag)
{
	COleVariant propVal((short) bFlag, VT_BOOL);
	SetProperty(0x23, VT_VARIANT, &propVal);
}

BOOL COXMMessage::GetEncrypted()
{
	VARIANT result;
	GetProperty(0xa, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

void COXMMessage::SetEncrypted(BOOL bFlag)
{
	COleVariant propVal((short) bFlag, VT_BOOL);
	SetProperty(0xa, VT_VARIANT, &propVal);
}

BOOL COXMMessage::GetReadReceipt()
{
	VARIANT result;
	GetProperty(0x1e, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

void COXMMessage::SetReadReceipt(BOOL bFlag)
{
	COleVariant propVal((short) bFlag, VT_BOOL);
	SetProperty(0x1e, VT_VARIANT, &propVal);
}

BOOL COXMMessage::GetDeliveryReceipt()
{
	VARIANT result;
	GetProperty(0x32, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

void COXMMessage::SetDeliveryReceipt(BOOL bFlag)
{
	COleVariant propVal((short) bFlag, VT_BOOL);
	SetProperty(0x32, VT_VARIANT, &propVal);
}

CString COXMMessage::GetConversationIndex()
{
	VARIANT result;
	GetProperty(0x37, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMMessage::SetConversationIndex(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x37, VT_VARIANT, &propVal);
}

CString COXMMessage::GetConversationTopic()
{
	VARIANT result;
	GetProperty(0x36, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMMessage::SetConversationTopic(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x36, VT_VARIANT, &propVal);
}

COXMFields COXMMessage::GetFields()
{
	VARIANT result;
	GetProperty(0xc, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMRecipients COXMMessage::GetRecipients()
{
	VARIANT result;
	GetProperty(0x1c, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMAttachments COXMMessage::GetAttachments()
{
	VARIANT result;
	GetProperty(0x5, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

void COXMMessage::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}

void COXMMessage::Update(BOOL bMakePermanent /*= TRUE*/, BOOL bRefreshObject /*= FALSE*/)
{
	COleVariant vMakePermanent((short) bMakePermanent, VT_BOOL);
	COleVariant vRefreshObject((short)bRefreshObject, VT_BOOL);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x84, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vMakePermanent, &vRefreshObject);
}

void COXMMessage::Send(BOOL bSaveCopy /*= TRUE*/, BOOL bShowDialog /*= FALSE*/, HWND hParentWindow /*= NULL*/)
{
	COleVariant vSaveCopy((short) bSaveCopy, VT_BOOL);
	COleVariant vShowDialog((short) bShowDialog, VT_BOOL);
	COleVariant vParentWindow((LONG) hParentWindow);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x83, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vSaveCopy, &vShowDialog, &vParentWindow);
}

void COXMMessage::Options(HWND hParentWindow)
{
	COleVariant vParentWindow((LONG) hParentWindow);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vParentWindow);
}


/////////////////////////////////////////////////////////////////////////////
// COXMFields Class

CString COXMFields::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

LPDISPATCH COXMFields::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMFields::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMFields::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LONG COXMFields::GetCount()
{
	VARIANT result;
	GetProperty(0x9, VT_VARIANT, (void*)&result);
	return result.lVal;
}

COXMField COXMFields::GetItem(COleVariant vItem, CString sPropSetID /* = _T("")*/)
{
	COleVariant vPropSetID;
	if (!sPropSetID.IsEmpty())
		vPropSetID = sPropSetID;
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&vItem, vPropSetID);
	return result.pdispVal;
}

void COXMFields::SetNamespace(CString sValue)
{
	COleVariant vPropsetID(sValue);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vPropsetID);
}

COXMField COXMFields::Add(CString sName, COleVariant value, CString sPropsetID /*= _T("")*/)
{
	ASSERT(	value.vt == VT_NULL ||
			value.vt == VT_I2 ||
			value.vt == VT_I4 ||
			value.vt == VT_R4 ||
			value.vt == VT_R8 ||
			value.vt == VT_CY ||
			value.vt == VT_DATE ||
			value.vt == VT_BSTR ||
			value.vt == VT_BOOL ||
			value.vt == VT_UNKNOWN ||
			value.vt == VT_BLOB);
	COleVariant vName(sName);
	COleVariant vClass((LONG) value.vt);
	COleVariant vPropsetID;
	if (!sPropsetID.IsEmpty())
		vPropsetID = sPropsetID;
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vName, &vClass, &value, &vPropsetID);
	return result.pdispVal;
}

void COXMFields::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COXMField properties

CString COXMField::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMFields COXMField::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMField::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMField::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LONG COXMField::GetIndex()
{
	VARIANT result;
	GetProperty(0x13, VT_VARIANT, (void*)&result);
	return result.lVal;
}

LONG COXMField::GetType()
{
	VARIANT result;
	GetProperty(0x11, VT_VARIANT, (void*)&result);
	return result.lVal;
}

CString COXMField::GetName()
{
	VARIANT result;
	GetProperty(0x17, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

LONG COXMField::GetId()
{
	VARIANT result;
	GetProperty(0xe, VT_VARIANT, (void*)&result);
	return result.lVal;
}

COleVariant COXMField::GetValue()
{
	VARIANT result;
	GetProperty(0x2b, VT_VARIANT, (void*)&result);
	return result;
}

void COXMField::SetValue(COleVariant propVal)
{
	COleVariant vType((LONG) propVal.vt);
	SetProperty(0x11, VT_VARIANT, &vType);
	SetProperty(0x2b, VT_VARIANT, &propVal);
}

void COXMField::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}

void COXMField::ReadFromFile(CString sPath)
{
	COleVariant vFileName(sPath);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vFileName);
}

void COXMField::WriteToFile(CString sPath)
{
	COleVariant vFileName(sPath);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x85, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vFileName);
}


/////////////////////////////////////////////////////////////////////////////
// COXMRecipients Class

CString COXMRecipients::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMFolder COXMRecipients::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMRecipients::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMRecipients::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

COXMRecipient COXMRecipients::GetItem(LONG nIndex)
{
	COleVariant vItem(nIndex);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&vItem);
	return result.pdispVal;
}

LONG COXMRecipients::GetCount()
{
	VARIANT result;
	GetProperty(0x9, VT_VARIANT, (void*)&result);
	return result.lVal;
}

BOOL COXMRecipients::GetResolved()
{
	VARIANT result;
	GetProperty(0x1d, VT_VARIANT, (void*)&result);
	return V_BOOL(&result);
}

COXMRecipient COXMRecipients::Add(CString sName /*= _T("")*/, CString sAddress /*= _T("")*/, EOXMRecipientType eType/*= oxmrtTo*/, CString sEntryID /*= _T("")*/)
{
	COleVariant vName;
	if (!sName.IsEmpty())
		vName = sName;
	COleVariant vAddress;
	if (!sAddress.IsEmpty())
		vAddress = sAddress;
	COleVariant vType((LONG) eType);
	COleVariant vEntryID;
	if (!sEntryID.IsEmpty())
		vEntryID = sEntryID;
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vName, &vAddress, &vType, &vEntryID);
	return result.pdispVal;
}

void COXMRecipients::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}

void COXMRecipients::Resolve(BOOL bShowDialog)
{
	COleVariant vShowDialog((short) bShowDialog, VT_BOOL);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x82, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vShowDialog);
}


/////////////////////////////////////////////////////////////////////////////
// COXMRecipient properties

CString COXMRecipient::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMRecipients COXMRecipient::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMRecipient::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMRecipient::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

LONG COXMRecipient::GetIndex()
{
	VARIANT result;
	GetProperty(0x13, VT_VARIANT, (void*)&result);
	return result.lVal;
}

EOXMDisplayType COXMRecipient::GetDisplayType()
{
	VARIANT result;
	GetProperty(0x38, VT_VARIANT, (void*)&result);
	return (EOXMDisplayType) result.lVal;
}

CString COXMRecipient::GetName()
{
	VARIANT result;
	GetProperty(0x17, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMRecipient::SetName(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x17, VT_VARIANT, &propVal);
}

EOXMRecipientType COXMRecipient::GetType()
{
	VARIANT result;
	GetProperty(0x11, VT_VARIANT, (void*)&result);
	return (EOXMRecipientType) result.lVal;
}

void COXMRecipient::SetType(EOXMRecipientType eValue)
{
	COleVariant propVal((LONG) eValue);
	SetProperty(0x11, VT_VARIANT, &propVal);
}

CString COXMRecipient::GetAddress()
{
	VARIANT result;
	GetProperty(0x2, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMRecipient::SetAddress(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x2, VT_VARIANT, &propVal);
}

COXMAddressEntry COXMRecipient::GetAddressEntry()
{
	VARIANT result;
	GetProperty(0x35, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

void COXMRecipient::SetAddressEntry(LPDISPATCH pAddressEntry)
{
	VARIANT propVal;
	propVal.vt = VT_DISPATCH;
	propVal.pdispVal = pAddressEntry;
	SetProperty(0x35, VT_VARIANT, &propVal);
}

void COXMRecipient::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}

void COXMRecipient::Resolve(BOOL bShowDialog)
{
	COleVariant vShowDialog((short) bShowDialog, VT_BOOL);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x82, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vShowDialog);
}


/////////////////////////////////////////////////////////////////////////////
// COXMAttachments Class

CString COXMAttachments::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMMessage COXMAttachments::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMAttachments::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMAttachments::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

COXMAttachment COXMAttachments::GetItem(LONG nIndex)
{
	COleVariant vItem(nIndex);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&vItem);
	return result.pdispVal;
}

LONG COXMAttachments::GetCount()
{
	VARIANT result;
	GetProperty(0x9, VT_VARIANT, (void*)&result);
	return result.lVal;
}

COXMAttachment COXMAttachments::Add(CString sName /*= _T("")*/, LONG nPosition /*= 0*/, EOXMAttachmentType eType /*= oxmatFileData*/, CString sSource /*= _T("")*/)
{
	COleVariant vName;
	if (!sName.IsEmpty())
		vName = sName;
	COleVariant vPosition(nPosition);
	COleVariant vType((LONG) eType);
	COleVariant vSource;
	if (!sSource.IsEmpty())
		vSource = sSource;
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vName, &vPosition, &vType, &vSource);
	return result.pdispVal;
}

void COXMAttachments::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COXMAttachment properties

CString COXMAttachment::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMAttachments COXMAttachment::GetParent()
{
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMAttachment::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMAttachment::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

CString COXMAttachment::GetName()
{
	VARIANT result;
	GetProperty(0x17, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMAttachment::SetName(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x17, VT_VARIANT, &propVal);
}

EOXMAttachmentType COXMAttachment::GetType()
{
	VARIANT result;
	GetProperty(0x11, VT_VARIANT, (void*)&result);
	return (EOXMAttachmentType) result.lVal;
}

void COXMAttachment::SetType(EOXMAttachmentType eValue)
{
	COleVariant propVal((LONG) eValue);
	SetProperty(0x11, VT_VARIANT, &propVal);
}

LONG COXMAttachment::GetIndex()
{
	VARIANT result;
	GetProperty(0x13, VT_VARIANT, (void*)&result);
	return result.lVal;
}

LONG COXMAttachment::GetPosition()
{
	VARIANT result;
	GetProperty(0x1a, VT_VARIANT, (void*)&result);
	return result.lVal;
}

void COXMAttachment::SetPosition(LONG nValue)
{
	COleVariant propVal(nValue);
	SetProperty(0x1a, VT_VARIANT, &propVal);
}

CString COXMAttachment::GetSource()
{
	VARIANT result;
	GetProperty(0x25, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMAttachment::SetSource(CString sSource)
{
	COleVariant vSource(sSource);
	SetProperty(0x25, VT_VARIANT, &sSource);
}

void COXMAttachment::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}

void COXMAttachment::ReadFromFile(CString sPath)
{
	COleVariant vFileName(sPath);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	SetProperty(0x25, VT_VARIANT, &vFileName);
	InvokeHelper(0x7f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vFileName);
}

void COXMAttachment::WriteToFile(CString sPath)
{
	COleVariant vFileName(sPath);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	SetProperty(0x25, VT_VARIANT, &vFileName);
	InvokeHelper(0x85, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vFileName);
}


/////////////////////////////////////////////////////////////////////////////
// COXMAddressEntry class

CString COXMAddressEntry::GetApplication()
{
	VARIANT result;
	GetProperty(0x14, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMRecipient COXMAddressEntry::GetParent()
{
	if (m_bCurrentSessionUser)
		return NULL;
	VARIANT result;
	GetProperty(0x19, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

COXMSession COXMAddressEntry::GetSession()
{
	VARIANT result;
	GetProperty(0x22, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

EOXMClass COXMAddressEntry::GetClass()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return (EOXMClass) result.lVal;
}

EOXMDisplayType COXMAddressEntry::GetDisplayType()
{
	VARIANT result;
	GetProperty(0x38, VT_VARIANT, (void*)&result);
	return (EOXMDisplayType) result.lVal;
}

CString COXMAddressEntry::GetName()
{
	VARIANT result;
	GetProperty(0x17, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMAddressEntry::SetName(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x17, VT_VARIANT, &propVal);
}

CString COXMAddressEntry::GetAddress()
{
	VARIANT result;
	GetProperty(0x2, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMAddressEntry::SetAddress(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x2, VT_VARIANT, &propVal);
}

CString COXMAddressEntry::GetType()
{
	VARIANT result;
	GetProperty(0x11, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

void COXMAddressEntry::SetType(CString sValue)
{
	COleVariant propVal(sValue);
	SetProperty(0x11, VT_VARIANT, &propVal);
}

CString COXMAddressEntry::GetId()
{
	VARIANT result;
	GetProperty(0xe, VT_VARIANT, (void*)&result);
	return result.bstrVal;
}

COXMFields COXMAddressEntry::GetFields()
{
	VARIANT result;
	GetProperty(0xc, VT_VARIANT, (void*)&result);
	return result.pdispVal;
}

void COXMAddressEntry::Details(HWND hParentWindow)
{
	COleVariant vParentWindow((LONG) hParentWindow);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vParentWindow);
}

void COXMAddressEntry::Update(BOOL bMakePermanent /*=TRUE*/, BOOL bRefreshObject /*= FALSE*/)
{
	COleVariant vMakePermanent((short) bMakePermanent, VT_BOOL);
	COleVariant vRefreshObject((short) bRefreshObject, VT_BOOL);
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x84, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vMakePermanent, &vRefreshObject);
}

void COXMAddressEntry::Delete()
{
	VARIANT result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
}
