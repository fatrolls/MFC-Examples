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

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	These classes encapsulate the OLE Messaging client interface which was originally
//	designed to develop powerful Visual Basic Messaging applications.
//	The OLE Messaging objects use variants as input and output parameters.
//	This is a good solution for Visual Basic, because Visual Basic can automatically
//	cast variables. In C++ you have to cast these parameters manually to the correct
//	variable types.
//	The classes in this framework do this type conversion for you.

// Remark:
//	For a full documentation on these classes we refer to the Microsoft SDK documentation:
//		SDK
//			Win32 SDK
//				Win32 Messaging API (MAPI)
//					OLE Messaging Library

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXMDISP_H__
#define __OXMDISP_H__


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


// Predeclarations
class COXMSession;
class COXMInfoStores;
class COXMInfoStore;
class COXMFolders;
class COXMFolder;
class COXMMessages;
class COXMMessage;
class COXMFields;
class COXMField;
class COXMRecipients;
class COXMRecipient;
class COXMAttachments;
class COXMAttachment;
class COXMAddressEntry;

enum EOXMClass
{
	oxmAddressEntry = 8,
	oxmAttachment = 5,
	oxmAttachments = 21,
	oxmField = 6,
	oxmFields = 22,
	oxmFolder = 2,
	oxmFolders = 18,
	oxmInfoStore = 1, 
	oxmInfoStores = 17,
	oxmMsg = 3,
	oxmMessages = 19,
	oxmRecipient = 4,
	oxmRecipients = 20,
	oxmSession = 0
};

enum EOXMDisplayType
{
	oxmdtMailUser = 0,
	oxmdtDistList = 1,
	oxmdtForum = 2,
	oxmdtAgent = 3,
	oxmdtOrganisation = 4,
	oxmdtPrivateDistList = 5,
	oxmdtRemoteMailUser = 6
};

enum EOXMRecipientType
{
	oxmrtTo = 1,
	oxmrtCc = 2,
	oxmrtBcc = 3
};

enum EOXMAttachmentType
{
	oxmatFileData = 1,
	oxmatFileLink = 2,
	oxmatOleObject = 3
};


/////////////////////////////////////////////////////////////////////////////
// COXMSession wrapper class

class OX_CLASS_DECL COXMSession : public COleDispatchDriver
{
// Member Functions
public:
	COXMSession() {}		// Calls COleDispatchDriver default constructor
	COXMSession(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMSession(const COXMSession& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Session object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	LPUNKNOWN GetMapiobject();
	// --- In: none
	// --- Out: none
	// --- Returns: an IUnknown pointer to the real Extended MAPI Session (IMAPISession) object.
	// --- Effect: none

	void SetMapiobject(LPUNKNOWN pSession);
	// --- In: pSession: IUnknown pointer of an Extended MAPI Session (IMAPISession) object
	// --- Out: none
	// --- Returns: none
	// --- Effect: Attaches an IUnknown pointer of an Extended MAPI Session (IMAPISession) object.

	CString GetVersion();
	// --- In: none
	// --- Out: none
	// --- Returns: the version number of the OLE Messaging Library as a string, for example, "1.00".
	// --- Effect: none

	CString GetOperatingSystem();
	// --- In: none
	// --- Out: none
	// --- Returns: the name and version number of the current operating system. 
	// --- Effect: none

	CString GetName();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the profile logged on to this session.
	// --- Effect: none

	COXMAddressEntry GetCurrentUser();
	// --- In: none
	// --- Out: none
	// --- Returns: the active user as an AddressEntry object.
	// --- Effect: none

	COXMFolder GetInbox();
	// --- In: none
	// --- Out: none
	// --- Returns: a Folder object representing the current user's default Inbox folder.
	// --- Effect: none

	COXMFolder GetOutbox();
	// --- In: none
	// --- Out: none
	// --- Returns: a Folder object representing the current user's default Outbox folder. 
	// --- Effect: none

	COXMInfoStores GetInfoStores();
	// --- In: none
	// --- Out: none
	// --- Returns: an InfoStores object representing a collection of available information stores. Each InfoStore object contains a root folder object.
	// --- Effect: none

	void Logon(CString sProfileName = _T(""), CString sProfilePassword = _T(""), BOOL bShowDialog = TRUE, BOOL bNewSession = FALSE, HWND hParentWindow = NULL);
	// --- In: sProfileName: specifies the user's logon name. To prompt the user to enter a logon name, omit profileName and set showDialog to TRUE.
	//		   sProfilePassword: specifies the user's logon password.
	//		   bShowDialog: If TRUE, displays a logon dialog box.
	//		   bNewSession: Determines whether the application opens a new MAPI session or uses the current shared MAPI session.
	//		   hParentWindow: Specifies the parent window handle for the logon dialog box. A value of 0 (the default) specifies that any dialog box
	//					      displayed is application modal.
	// --- Out: none
	// --- Returns: none
	// --- Effect: The Logon method logs on to the MAPI system.
	// --- COleDispatchException: MAPI_E_LOGON_FAILURE if not successful

	void Logoff();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: logs off from the MAPI system.

	COXMInfoStore GetInfoStore(CString sStoreID);
	// --- In: specifies the unique identifier of the store to retrieve
	// --- Out: none
	// --- Returns: if successful an InfoStore object that can be used to
	//		 navigate through both public folders and the user's personal folders. 
	//		 If not successful: an COXMInfoStore object with an m_lpDispatch member 
	//		 set to NULL
	// --- Effect: none

	COXMFolder GetFolder(CString sFolderID, CString sStoreID = _T(""));
	// --- In: sFolderId: specifies the unique identifier of the folder. When you provide an empty string, some providers return the root folder.
	//         sStoreID: specifies the unique identifier of the store. The default value is an empty string, which corresponds to the default store.
	// --- Out: none
	// --- Returns: if successful a Folder object from a MAPI information store. 
	//		 If not successful: an COXMInfoStore object with an m_lpDispatch member 
	//		 set to NULL
	// --- Effect: none

	COXMMessage GetMessage(CString sMessageID, CString sStoreID = _T(""));
	// --- In: sMessageID:specifies the unique identifier of the message.
	//		   sStoreID: specifies the unique identifier of the store. The default value is an empty string, which corresponds to the default store.
	// --- Out: none
	// --- Returns: if successful a Message object from a MAPI information store. 
	//		 If not successful: an COXMInfoStore object with an m_lpDispatch member 
	//		 set to NULL
	// --- Effect: none

	COXMAddressEntry GetAddressEntry(CString sEntryID);
	// --- In: sEntryID: specifies the unique identifier of the address entry.
	// --- Out: none
	// --- Returns: On successful return, represents the AddressEntry object specified by entryID.
	// --- Effect: none

	COXMRecipients AddressBook(LPDISPATCH pRecipients = NULL,
				CString sTitle = _T(""),
				BOOL bOneAddress = FALSE,
				BOOL bForceResolution = TRUE,
				LONG nRecipLists = 0,
				CString sTOLabel = _T(""),
				CString sCCLabel = _T(""),
				CString sBCCLabel = _T(""), 
				HWND hParentWindow = NULL);
	// --- In: pRecipients: A Recipients collection object that provides the initial value for the recipient list boxes in the address book.
	//		   sTitle: The title or caption of the address book dialog box.
	//		   bOneAddress: Allows the user to enter or select only one address.
	//		   bForceResolution: If TRUE, attempts to resolve all names before closing the address book. Prompts the user to resolve any ambiguous names.
	//		   nRecipLists: The number of recipient list boxes to display in the address book dialog box:
	//						0: no list boxes; 1: To; 2: To and CC; 3: TO, CC and BCC 
	//		   sTOLabel:The caption for the button associated with the first list box
	//		   sCCLabel:The caption for the button associated with the second list box
	//		   sBCCLabel:The caption for the button associated with the third list box
	//		   hParentWindow:The parent window handle for the address book dialog box. A value of 0 (the default) specifies that any dialog box displayed is application modal. 
	// --- Out: none
	// --- Returns:  The selections are returned in a Recipients collection object. 
	// --- Effect: The AddressBook method displays the MAPI dialog box that allows the user to select entries from the address book.

};

/////////////////////////////////////////////////////////////////////////////
// COXMInfoStores wrapper class

class OX_CLASS_DECL COXMInfoStores : public COleDispatchDriver
{
// Member Functions
public:
	COXMInfoStores() {}		// Calls COleDispatchDriver default constructor
	COXMInfoStores(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMInfoStores(const COXMInfoStores& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging InfoStores object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	LONG GetCount();
	// --- In: none
	// --- Out: none
	// --- Returns: the number of InfoStore objects in the collection.
	// --- Effect: none

	COXMInfoStore GetItem(LONG nItem);
	// --- In: nItem: the index
	// --- Out: none
	// --- Returns: a single item from this collection.
	// --- Effect: none
};

/////////////////////////////////////////////////////////////////////////////
// COXMInfoStore wrapper class

class OX_CLASS_DECL COXMInfoStore : public COleDispatchDriver
{
// Member Functions
public:
	COXMInfoStore() {}		// Calls COleDispatchDriver default constructor
	COXMInfoStore(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMInfoStore(const COXMInfoStore& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging InfoStore object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMInfoStores GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: the collection this store belongs to
	// --- Effect: none

	LONG GetIndex();
	// --- In: none
	// --- Out: none
	// --- Returns: the index number for the InfoStore object within the parent InfoStores collection.
	// --- Effect: none

	CString GetName();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the InfoStore object as a string. Read-only. The string "Public Folders" is the name of the InfoStore object that contains the public folders.
	// --- Effect: none

	CString GetId();
	// --- In: none
	// --- Out: none
	// --- Returns: the unique identifier of this InfoStore object as a string.
	// --- Effect: none

	CString GetProviderName();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the InfoStore provider as a string.
	// --- Effect: none

	COXMFolder GetRootFolder();
	// --- In: none
	// --- Out: none
	// --- Returns: a folder object representing the root of the IPM tree for this InfoStore object.
	// --- Effect: none

};

/////////////////////////////////////////////////////////////////////////////
// COXMFolder wrapper class

class OX_CLASS_DECL COXMFolder : public COleDispatchDriver
{
// Member Functions
public:
	COXMFolder() {}		// Calls COleDispatchDriver default constructor
	COXMFolder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMFolder(const COXMFolder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Folder object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	LPDISPATCH GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: The Parent property returns the parent of the object.
	//				An Inbox, Outbox and Root folder return a Session Object
	//				Other Folders return a Folders collection
	// --- Effect: none

	LPUNKNOWN GetMapiobject();
	// --- In: none
	// --- Out: none
	// --- Returns: returns an IUnknown pointer to the real Extended MAPI Folder (IMAPIFolder) object.
	// --- Effect:
	
	void SetMapiobject(LPUNKNOWN pSession);
	// --- In: pSession: an IUnknown pointer to the real Extended MAPI Folder (IMAPIFolder) object.
	// --- Out: none 
	// --- Returns: none
	// --- Effect: Attaches an IUnknown pointer of an Extended MAPI Folder (IMAPIFolder) object.

	CString GetName();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the Folder object as a string.
	// --- Effect: none

	void SetName(CString sName);
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the Folder object as a string.
	// --- Effect: none

	CString GetId();
	// --- In: none
	// --- Out: none
	// --- Returns: the unique identifier of this Folder object as a string.
	// --- Effect: none

	CString GetFolderID();
	// --- In: none
	// --- Out: none
	// --- Returns: the unique identifier of this subfolder's parent folder as a string.
	// --- Effect: none

	CString GetStoreID();
	// --- In: none
	// --- Out: none
	// --- Returns: the identifier of the Store object in which this Folder object resides.
	// --- Effect: none

	COXMFolders GetFolders();
	// --- In: none
	// --- Out: none
	// --- Returns: a collection of subfolders within the parent folder.
	// --- Effect: none

	COXMMessages GetMessages();
	// --- In: none
	// --- Out: none
	// --- Returns: a Messages collection object within the folder.
	// --- Effect: none

	COXMFields GetFields();
	// --- In: none
	// --- Out: none
	// --- Returns: a single field (a Field object) or a collection of fields (a Fields collection object) of the Folder object.
	// --- Effect: none

	void Update(BOOL bMakePermanent = TRUE, BOOL bRrefreshObject = FALSE);
	// --- In: bMakePermanent: TRUE indicates that the property cache is flushed and all changes are committed in the underlying store.
	//			FALSE indicates that the property cache is flushed and not committed to the store. 
	//		   bRrefreshObject: TRUE indicates that the property cache is reloaded from the values in the underlying store.
	//			FALSE indicates that the property cache is not reloaded.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Saves the folder in the MAPI system.

};

/////////////////////////////////////////////////////////////////////////////
// COXMFolders wrapper class

class OX_CLASS_DECL COXMFolders : public COleDispatchDriver
{
// Member Functions
public:
	COXMFolders() {}		// Calls COleDispatchDriver default constructor
	COXMFolders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMFolders(const COXMFolders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Folders object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMFolder GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: a Folder object
	// --- Effect: none

	COXMFolder GetFirst();
	// --- In: none
	// --- Out: none
	// --- Returns: the first object in the Folders collection.
	//		Returns an object witch a m_lpDispatch member set to NULL if no first object exists.
	// --- Effect: increments the internal item pointer

	COXMFolder GetNext();
	// --- In: none
	// --- Out: none
	// --- Returns: the first object in the Folders collection.
	//		Returns an object with a m_lpDispatch member set to NULL if no first object exists.
	// --- Effect: increments the internal item pointer

	COXMFolder GetLast();
	// --- In: none
	// --- Out: none
	// --- Returns: the last object in the Folders collection.
	//		Returns an object with a m_lpDispatch member set to NULL if no last object exists.
	// --- Effect: none

	COXMFolder GetPrevious();
	// --- In: none
	// --- Out: none
	// --- Returns: the first object in the Folders collection.
	//		Returns an object witch a m_lpDispatch member set to NULL if no first object exists.
	// --- Effect: decrements the internal item pointer

};
/////////////////////////////////////////////////////////////////////////////
// COXMMessages wrapper class

class OX_CLASS_DECL COXMMessages : public COleDispatchDriver
{
// Member Functions
public:
	COXMMessages() {}		// Calls COleDispatchDriver default constructor
	COXMMessages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMMessages(const COXMMessages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Messages object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMFolder GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: the parent of the object.
	// --- Effect: none

	COXMMessage Add(CString sSubject = _T(""), CString sText = _T(""), CString sType = _T(""), LONG nImportance=1);
	// --- In: sSubject: The subject of the message.
	//		   sText: The body text of the message.
	//		   sType: The message class of the message. When ommited type is IPM.Note.
	//		 nImportance: 0: Low priority; 1: Normal priority (default); 2: High priority
	// --- Out: none
	// --- Returns: a new created Message object
	// --- Effect: creates and returns a new Message object in the Messages collection

	void Delete(BOOL bSubFolders = TRUE);
	// --- In: bSubFolders: if TRUE: deletes all subfolders too 
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes all messages in the collection.

	void Sort(LONG nSortOrder);
	// --- In: nSortOrder: 0: No sort; 1: Ascending; 2: Descending
	// --- Out: none
	// --- Returns: none
	// --- Effect: sorts the messages in the collection according to the specified sort order

	COXMMessage GetFirst(CString sFilter = _T(""));
	// --- In: sFilter: Specifies the message class of the object, such as the default value, IPM.Note (if ommitted).
	//				Corresponds to  the Type property of the Message object.
	// --- Out: none
	// --- Returns: the first Message object in the collection.
	// --- Effect: increments the internal item pointer

	COXMMessage GetNext();
	// --- In: none
	// --- Out: none
	// --- Returns: The next object in the Messages collection. Nothing if no next object exists.
	// --- Effect: increments the internal item pointer

	COXMMessage GetLast(CString sFilter = _T(""));
	// --- In: sFilter: Specifies the message class of the object, such as the default value, IPM.Note (if ommitted).
	//				Corresponds to  the Type property of the Message object.
	// --- Out: none
	// --- Returns: the last Message object in the collection.
	// --- Effect: remembers the filter
	
	COXMMessage GetPrevious();
	// --- In: none
	// --- Out: none
	// --- Returns: The previous object in the collection. Nothing if no previous object exists.
	// --- Effect: decrements the internal item pointer

};

/////////////////////////////////////////////////////////////////////////////
// COXMMessage wrapper class

class OX_CLASS_DECL COXMMessage : public COleDispatchDriver
{
// Member Functions
public:
	COXMMessage() {}		// Calls COleDispatchDriver default constructor
	COXMMessage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMMessage(const COXMMessage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Session object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMMessages GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: The parent of the object which is the messages collection.
	// --- Effect: none

	LPUNKNOWN GetMapiobject();
	// --- In: none
	// --- Out: none
	// --- Returns: an IUnknown pointer to the real Extended MAPI Session (IMAPISession) object.
	// --- Effect: none

	void SetMapiobject(LPUNKNOWN pSession);
	// --- In: pSession: IUnknown pointer of an Extended MAPI Session (IMAPISession) object
	// --- Out: none
	// --- Returns: none
	// --- Effect: Attaches an IUnknown pointer of an Extended MAPI Session (IMAPISession) object.
	
	CString GetId();
	// --- In: none
	// --- Out: none
	// --- Returns: the unique ID of the object as a string.
	// --- Effect: none

	CString GetFolderID();
	// --- In: none
	// --- Out: none
	// --- Returns: the unique ID of the folder in which the message resides.
	// --- Effect: none

	CString GetStoreID();
	// --- In: none
	// --- Out: none
	// --- Returns: The unique identifier for the information store that contains this message.
	// --- Effect: none
	
	CString GetType();
	// --- In: none
	// --- Out: none
	// --- Returns: the MAPI message class for the message.
	// --- Effect: none

	void SetType(CString sType);
	// --- In: the MAPI message class for the message.
	// --- Out: none
	// --- Returns: none
	// --- Effect: sets the MAPI message class for the message.

	LONG GetSize();
	// --- In: none
	// --- Out: none
	// --- Returns: The approximate size in bytes of the message. 
	// --- Effect: none
	
	LONG GetImportance();
	// --- In: none
	// --- Out: none
	// --- Returns:  the importance of the message as one of mapiNormal (the default), mapiLow, or mapiHigh. 
	// --- Effect: none

	void SetImportance(LONG);
	// --- In: the importancy of the message. 
	// --- Out: none
	// --- Returns: none  
	// --- Effect: sets the importance of the message as one of mapiNormal (the default), mapiLow, or mapiHigh. 

	CString GetSubject();
	// --- In: none
	// --- Out: none
	// --- Returns: Returns the subject of the message as a string. 
	// --- Effect: none

	void SetSubject(CString);
	// --- In: the subject of the message as a string. 
	// --- Out: none
	// --- Returns: none 
	// --- Effect: sets the subject of the message as a string. 

	COXMAddressEntry GetSender();
	// --- In: none
	// --- Out: none
	// --- Returns: the originator or original author of a message as an AddressEntry object.
	// --- Effect: none
	
	COleDateTime GetTimeSent();
	// --- In: none
	// --- Out: none
	// --- Returns: the date and time the message was sent as a vbDate variant data type. 
	// --- Effect: none

	void SetTimeSent(COleDateTime);
	// --- In:  the date and time the message was sent 
	// --- Out: none
	// --- Returns: none 
	// --- Effect: Sets the date and time the message was sent as a vbDate variant data type. 

	COleDateTime GetTimeReceived();
	// --- In: none
	// --- Out: none
	// --- Returns: the date and time the message was received as a vbDate variant data type. 
	// --- Effect: none

	void SetTimeReceived(COleDateTime);
	// --- In:  the date and time the message was received. 
	// --- Out: none
	// --- Returns: none 
	// --- Effect: Sets the date and time the message was received as a vbDate variant data type. 

	CString GetText();
	// --- In: none
	// --- Out: none
	// --- Returns: the body text of the message as a string.
	// --- Effect: none

	void SetText(CString);
	// --- In:  the body text of the message.
	// --- Out: none
	// --- Returns: none 
	// --- Effect: sets the body text of the message as a string.

	BOOL GetSent();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE if the message has been sent through the MAPI system.
	// --- Effect: none

	void SetSent(BOOL);
	// --- In:  TRUE or FALSE
	// --- Out: none
	// --- Returns: none 
	// --- Effect: flags the message that it has been sent or not.

	BOOL GetSubmitted();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE when the message has been submitted.
	// --- Effect: none

	void SetSubmitted(BOOL);
	// --- In:  TRUE or FALSE
	// --- Out: none
	// --- Returns: none 
	// --- Effect: flags the message that has been submitted or not.

	BOOL GetUnread();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE if the message has not been read by the current user.
	// --- Effect: none

	void SetUnread(BOOL );
	// --- In:  TRUE or FALSE
	// --- Out: none
	// --- Returns: none 
	// --- Effect: flags the message that has not been read by the current user, or not.

	BOOL GetSigned();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE if the message has been tagged with a digital signature. 
	// --- Effect: none

	void SetSigned(BOOL);
	// --- In: TRUE or FALSE 
	// --- Out: none
	// --- Returns: none 
	// --- Effect: flags the message that has been tagged with a digital signature, or not. 

	BOOL GetEncrypted();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE if the message has been encrypted. 
	// --- Effect: none

	void SetEncrypted(BOOL);
	// --- In:  TRUE or FALSE
	// --- Out: none
	// --- Returns: none 
	// --- Effect: flags the message that has been encrypted, or not. 

	BOOL GetReadReceipt();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE if a read-receipt notification message is requested.
	// --- Effect: none

	void SetReadReceipt(BOOL);
	// --- In:  TRUE or FALSE
	// --- Out: none
	// --- Returns: none 
	// --- Effect: flags that a read-receipt notification message is requested, or not.

	BOOL GetDeliveryReceipt();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE if a delivery-receipt notification message is requested. 
	// --- Effect: none

	void SetDeliveryReceipt(BOOL);
	// --- In: TRUE or FALSE 
	// --- Out: none
	// --- Returns: none 
	// --- Effect: flags that a delivery-receipt notification message is requested, or not. 

	CString GetConversationIndex();
	// --- In: none
	// --- Out: none
	// --- Returns: the index to the conversation thread of the message.
	// --- Effect: none

	void SetConversationIndex(CString);
	// --- In:  index to the conversation thread of the message
	// --- Out: none
	// --- Returns: none 
	// --- Effect: sets the index to the conversation thread of the message.

	CString GetConversationTopic();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the conversation thread.
	// --- Effect: none

	void SetConversationTopic(CString);
	// --- In: name of the conversation thread. 
	// --- Out: none
	// --- Returns: none 
	// --- Effect: specifies the name of the conversation thread.

	COXMFields GetFields();
	// --- In: none
	// --- Out: none
	// --- Returns: a single field (a Field object) or a collection of fields (a Fields collection object) of the Message object. 
	// --- Effect: none

	COXMRecipients GetRecipients();
	// --- In: none
	// --- Out: none
	// --- Returns:  a single Recipient object or a Recipients collection object.
	// --- Effect: none

	COXMAttachments GetAttachments();
	// --- In: none
	// --- Out: none
	// --- Returns: a single Attachment object or an Attachments collection.
	// --- Effect: none

	void Delete();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes the Message object.

	void Update(BOOL bMakePermanent = TRUE, BOOL bRefreshObject = FALSE);
	// --- In: bMakePermanent: TRUE indicates that the property cache is flushed and all changes are committed to the underlying store.
	//				FALSE indicates that the property cache is flushed and not committed to the store.
	//		   bRefreshObject: TRUE indicates that the property cache is reloaded from the values in the underlying store.
	//				FALSE indicates that the property cache is not reloaded.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Saves the message in the MAPI system.
	
	void Send(BOOL bSaveCopy = TRUE, BOOL bShowDialog = FALSE, HWND hParentWindow = NULL);
	// --- In: bSaveCopy: Saves a copy of the Message in a user folder, such as the Sent Messages folder.
	//		   bShowDialog: Displays a Send Message dialog box where the user can change the message contents or recipients.
	//		   hParentWindow: The parent window handle for the Send Message dialog box.
	//				A value of NULL (the default) specifies that any dialog box displayed is application-modal.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Sends the message to the recipients via the MAPI system.

	void Options(HWND hParentWindow = NULL);
	// --- In: hParentWindow: The parent window handle for the options dialog box.
	//			A value of NULL (the default) specifies an application-modal dialog box.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Displays a message options dialog box where the user can change the submission options for a message.

};

/////////////////////////////////////////////////////////////////////////////
// COXMFields wrapper class

class OX_CLASS_DECL COXMFields : public COleDispatchDriver
{
// Member Functions
public:
	COXMFields() {}		// Calls COleDispatchDriver default constructor
	COXMFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMFields(const COXMFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Fields object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	LPDISPATCH GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: The parent of the object (Message or Folder object).
	// --- Effect: none

	LONG GetCount();
	// --- In: none
	// --- Out: none
	// --- Returns: The number of Field objects in the collection.
	// --- Effect: none

	COXMField GetItem(COleVariant vItem, CString sPropSetID = _T(""));
	// --- In: vItem: + short -> index within collection
	//				  + LONG -> property tag value for the MAPI property to be retrieved
	//				  + string -> Specifies the name of the user-defined property
	//		   sPropSetID: Contains the unique identifier for the property set, represented as a string
	//				of hexadecimal characters. When propsetID is not supplied, the property set used for
	//				the access is the default property set value set by this collection's SetNamespace
	//				method, or the initial default property set value, PS_PUBLIC_STRINGS. 
	// --- Out: none
	// --- Returns: a single item from a collection.
	// --- Effect: none

	void SetNamespace(CString sPropsetID);
	// --- In: sPropsetID: Contains a unique identifier that identifies the property set,
	//			represented as a string of hexadecimal characters. The PropsetID
	//			identifies the property set to be used for subsequent property accesses
	//			using the Field object and Fields collection. An empty string resets
	//			the default to the property set PS_PUBLIC_STRINGS.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Selects the property set that is to be used for subsequent property
	//				accesses using the Add method and Item property.

	COXMField Add(CString sName, COleVariant value, CString sPropsetID = _T(""));
	// --- In: sName: the name of the new field object
	//		   value: the value of the field. There are limited number of supported types:
	//					VT_NULL, VT_I2, VT_I4, VT_R4, VT_R8, VT_CY, VT_DATE, VT_BSTR,
	//					VT_BOOL, VT_UNKNOWN, VT_BLOB 
	// --- Out: none
	// --- Return: The new added field object
	// --- Effect: Creates a new Field object in the Fields collection. 
	
	void Delete();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: Deletes all user-defined fields of this collection object.
};

/////////////////////////////////////////////////////////////////////////////
// COXMField wrapper class

class OX_CLASS_DECL COXMField : public COleDispatchDriver
{
// Member Functions
 public:
	COXMField() {}		// Calls COleDispatchDriver default constructor
	COXMField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMField(const COXMField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Field object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMFields GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: the parent of the object which is the collection object. 
	// --- Effect: none

	LONG GetIndex();
	// --- In: none
	// --- Out: none
	// --- Returns: the index number of this Field object within the Fields collection.
	// --- Effect: none

	LONG GetType();
	// --- In: none
	// --- Out: none
	// --- Returns: the variant data type of the Field object. 
	// --- Effect: none

	CString GetName();
	// --- In: none
	// --- Out: none
	// --- Returns:  the name of the field as a string. 
	// --- Effect: none

	LONG GetId();
	// --- In: none
	// --- Out: none
	// --- Returns: the unique ID of the object as a long integer.
	// --- Effect: none

	COleVariant GetValue();
	// --- In: none
	// --- Out: none
	// --- Returns: the value of the Field object.
	// --- Effect: none

	void SetValue(COleVariant);
	// --- In: value of the Field object.
	// --- Out: none
	// --- Returns: none
	// --- Effect: sets value of the Field object.

	void Delete();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes the user-defined or optional Field object

	void ReadFromFile(CString sPath);
	// --- In: sPath: The full path and file name to read
	// --- Out: none
	// --- Returns: none
	// --- Effect: loads the value of a string or binary field from the specified file

	void WriteToFile(CString sPath);
	// --- In: sPath: The full path and file name to read
	// --- Out: none
	// --- Returns: none
	// --- Effect:  saves the field value to a file in the file system
};

/////////////////////////////////////////////////////////////////////////////
// COXMRecipients wrapper class

class OX_CLASS_DECL COXMRecipients : public COleDispatchDriver
{
// member Functions
public:
	COXMRecipients() {}		// Calls COleDispatchDriver default constructor
	COXMRecipients(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMRecipients(const COXMRecipients& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Recipients object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMFolder GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: the parent of the object which is a COXMFolder object. 
	// --- Effect: none

	COXMRecipient GetItem(LONG nIndex);
	// --- In: nIndex: the index within the collection
	// --- Out: none
	// --- Returns: a single Recipient from the collection.
	// --- Effect: none

	LONG GetCount();
	// --- In: none
	// --- Out: none
	// --- Returns: the number of Recipient objects in the collection. 
	// --- Effect: none

	BOOL GetResolved();
	// --- In: none
	// --- Out: none
	// --- Returns: TRUE if all of the recipients in the collection are resolved.
	// --- Effect: none

	COXMRecipient Add(CString sName = _T(""), CString sAddress = _T(""), EOXMRecipientType eType = oxmrtTo, CString sEntryID = _T(""));
	// --- In: sName: The display name of the recipient.
	//		   sAddress: The address of the recipient.
	//		   eType: oxmrtTo, oxmrtCc or oxmrtBcc
	//		   sEntryID: The identifier of a valid AddressEntry object for this recipient.
	//				When present, the other parameters are not used. When not present,
	//				the method uses the name, address, and type parameters to determine the recipient.
	// --- Out: none
	// --- Returns: represents the new Recipient object added to the collection
	// --- Effect: creates a new Recipient object in the Recipients collection

	void Delete();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes all Recipients in the collection

	void Resolve(BOOL bShowDialog = TRUE);
	// --- In: bShowDialog: if dialog should be shown or not
	// --- Out: none
	// --- Returns: none
	// --- Effect: searches the Recipients collection to resolve all names
};

/////////////////////////////////////////////////////////////////////////////
// COXMRecipient wrapper class

class OX_CLASS_DECL COXMRecipient : public COleDispatchDriver
{
public:
	COXMRecipient() {}		// Calls COleDispatchDriver default constructor
	COXMRecipient(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMRecipient(const COXMRecipient& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Recipient object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMRecipients GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: the parent of the object. 
	// --- Effect: none

	LONG GetIndex();
	// --- In: none
	// --- Out: none
	// --- Returns: the index number of this Recipient object within the Recipients collection. 
	// --- Effect: none

	EOXMDisplayType GetDisplayType();
	// --- In: none
	// --- Out: none
	// --- Returns: Identifies the recipient type. Enables special processing based on the type,
	//			such as displaying an icon associated with that type.
	//			oxmdtMailUser (0)			Local user
	//			oxmdtDistList (1)			Distribution list
	//			oxmdtForum (2)				Public folder
	//			oxmdtAgent (3)				Agent
	//			oxmdtOrganisation (4)		Organization
	//			oxmdtPrivateDistList (5)	Private distribution list
	//			oxmdtRemoteMailUser (6)		Remote user
	// --- Effect: none
	
	CString GetName();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of this Recipient object.
	// --- Effect: none

	void SetName(CString);
	// --- In: the name of this Recipient object.
	// --- Out: none
	// --- Returns: none
	// --- Effect: sets the name of this Recipient object.

	EOXMRecipientType GetType();
	// --- In: none
	// --- Out: none
	// --- Returns: the type of the Recipient object
	//		oxmrtTo	(1) The recipient is on the To: line
	//		oxmrtCc	(2)	The recipient is on the Cc: line.
	//		oxmrtBcc (3)The recipient is on the Bcc: line.
	// --- Effect: none

	void SetType(EOXMRecipientType);
	// --- In: the type of the Recipient object
	//			oxmrtTo	(1) The recipient is on the To: line
	//			oxmrtCc	(2)	The recipient is on the Cc: line.
	//			oxmrtBcc (3)The recipient is on the Bcc: line.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Sets the type of the Recipient object

	CString GetAddress();
	// --- In: none
	// --- Out: none
	// --- Returns: the full address for this recipient. 
	// --- Effect: none

	void SetAddress(CString);
	// --- In: the full address for this recipient. 
	// --- Out: none
	// --- Returns: none
	// --- Effect: sets the full address for this recipient. 

	COXMAddressEntry GetAddressEntry();
	// --- In: none
	// --- Out: none
	// --- Returns: the AddressEntry object for this recipient.
	// --- Effect: none

	void SetAddressEntry(LPDISPATCH);
	// --- In: the AddressEntry object.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Sets the AddressEntry object for this recipient.

	void Delete();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes the Recipient object

	void Resolve(BOOL bShowDialog = TRUE);
	// --- In: bShowDialog: if dialog should be shown or not
	// --- Out: none
	// --- Returns: none
	// --- Effect: Resolves address information. When the Recipient object's Name property
	//			is supplied, looks up the corresponding address from the address book.
	//			When the Recipient object's Address property is supplied, resolves as a
	//			custom address.
};

/////////////////////////////////////////////////////////////////////////////
// COXMAttachments wrapper class

class OX_CLASS_DECL COXMAttachments : public COleDispatchDriver
{
// Member Functions
public:
	COXMAttachments() {}		// Calls COleDispatchDriver default constructor
	COXMAttachments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMAttachments(const COXMAttachments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Attachments object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMMessage GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns:  the parent of the object.
	// --- Effect: none

	COXMAttachment GetItem(LONG nIndex);
	// --- In: nIndex: the index within the collection
	// --- Out: none
	// --- Returns: a single item from a collection. 
	// --- Effect: none

	LONG GetCount();
	// --- In: none
	// --- Out: none
	// --- Returns: the number of Attachment objects in the collection.
	// --- Effect: none

	COXMAttachment Add(CString sName = _T(""), LONG nPosition = 0, EOXMAttachmentType eType = oxmatFileData, CString sSource = _T(""));
	// --- In: sName: The display name of the attachment. To allow a user to click on the attachment that
	//				appears in the message and activate an associated application, supply the full filename,
	//				including the file extension. In case of an OleObject you have to specify the Class name
	//				ex: EXCEL.DOCUMENT
	//		   nPosition: The position of the attachment within the body text of the message.
	//		   eType: oxmatFileData, oxmatFileLink or oxmatOleObject
	//		   sSource: depending of the value for type:
	//				FileData	Specifies a full path and file name that contains the data for the attachment.
	//							For example, C:\DOCUMENT\BUDGET.XLS. The data is read into the attachment.
	//				FileLink	Specifies a full path name in a universal naming convention (UNC) format,
	//							such as \\SALES\INFO\PRODUCTS\NEWS.DOC. The attachment is a link, so the Add
	//							method does not read the data. 
	//				OleObject	Specifies a full path and file name to a valid OLE docfile. For example,
	//							C:\DOCUMENT\BUDGET2.XLS. The data is read into the attachment. 
	// --- Out: none
	// --- Returns: none
	// --- Effect: creates a new Attachment object in the Attachments collection

	void Delete();
	// --- In:none
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes the entire Attachments collection
};

/////////////////////////////////////////////////////////////////////////////
// COXMAttachment wrapper class

class OX_CLASS_DECL COXMAttachment : public COleDispatchDriver
{
// Member Functions
public:
	COXMAttachment() {}		// Calls COleDispatchDriver default constructor
	COXMAttachment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COXMAttachment(const COXMAttachment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging Attachment object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMAttachments GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: the parent of the object.
	// --- Effect: none

	CString GetName();
	// --- In: none
	// --- Out: none
	// --- Returns: the display name of the Attachment object as a string (FileData or FileLink type attachments)
	//			returns the OLE class name for OleObject attachments (see GetType and SetType functions)
	// --- Effect: none

	void SetName(CString);
	// --- In: the name of this Attachment object.
	// --- Out: none
	// --- Returns: none
	// --- Effect: sets the display name of the Attachment object as a string

	EOXMAttachmentType GetType();
	// --- In: none
	// --- Out: none
	// --- Returns: describes the attachment type: oxmatFileData, oxmatFileLink or oxmatOleObject
	// --- Effect: none

	void SetType(EOXMAttachmentType);
	// --- In: the type of the Attachment object:
	//				oxmatFileData
	//				oxmatFileLink
	//				oxmatOleObject
	// --- Out: none
	// --- Returns: none
	// --- Effect: Sets the type of the Attachment object

	LONG GetIndex();
	// --- In: none
	// --- Out: none
	// --- Returns: the index number for the Attachment object within the Attachments collection. 
	// --- Effect: none

	LONG GetPosition();
	// --- In: none
	// --- Out: none
	// --- Returns: the position of the attachment within the body text of the message. 
	// --- Effect: none

	void SetPosition(LONG);
	// --- In: the position of the attachment. 
	// --- Out: none
	// --- Returns: none
	// --- Effect: sets the position of the attachment within the body text of the message. 

	CString GetSource();
	// --- In: none
	// --- Out: none
	// --- Returns:the full path name of the attachment data file (For FileLink attachments).
	//			For OleObject attachments, returns the OLE class name for the attachment. 
	// --- Effect: none

	void SetSource(CString);
	// --- In: the source for this attachment
	// --- Out: none
	// --- Returns:none
	// --- Effect: When using oxmatFileData or oxmatOleObject this value is set by the ReadFromFile
	//				or WriteToFile functions.


	void Delete();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes the attachment.

	void ReadFromFile(CString sPath);
	// --- In: sPath: The full path and file name to read. For example, C:\DOCUMENT\BUDGET.XLS.
	// --- Out: none
	// --- Returns: none
	// --- Effect: loads the contents of an attachment from a file

	void WriteToFile(CString sPath);
	// --- In: sPath: The full path and file name for the saved attachment. For example, C:\DOCUMENT\BUDGET.XLS.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Saves the attachment to a file in the file system.
	//			Note that if the file already exists, this method overwrites it without warning.

};

/////////////////////////////////////////////////////////////////////////////
// COXMAddressEntry wrapper class

class OX_CLASS_DECL COXMAddressEntry : public COleDispatchDriver
{
// Data Members
public:
	BOOL	m_bCurrentSessionUser;
// Member Functions
public:
	COXMAddressEntry() : m_bCurrentSessionUser(FALSE) {}		// Calls COleDispatchDriver default constructor
	COXMAddressEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch),  m_bCurrentSessionUser(FALSE)  {}
	COXMAddressEntry(const COXMAddressEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc), m_bCurrentSessionUser(FALSE) {}
	// --- In: pDispatch: the IDispatch pointer of the OLE messaging AddressEntry object
	//		   dispatchSrc: the source object which will be copied
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs this rapper object and attaches the real dispatch Interface with it
	//	      The copy constructor version will increment the reference count of the IDispatch interface

	CString GetApplication();
	// --- In: none
	// --- Out: none
	// --- Returns: the name of the active application, which is the OLE Messaging Library, "OLE/Messaging." 
	// --- Effect: none

	EOXMClass GetClass();
	// --- In: none
	// --- Out: none
	// --- Returns: the OLE Messaging Library class type (see EOXMClass definition)
	// --- Effect: none

	COXMSession GetSession();
	// --- In: none
	// --- Out: none
	// --- Returns: the top-level Session object associated with the specified OLE Messaging Library object
	// --- Effect: none

	COXMRecipient GetParent();
	// --- In: none
	// --- Out: none
	// --- Returns: the parent of the object.
	//			m_lpDispatch member of returned object can be NULL (Current User)
	// --- Effect: none
	
	EOXMDisplayType GetDisplayType();
	// --- In: none
	// --- Out: none
	// --- Returns: Identifies the type of the address entry. This property enables special
	//			processing based on the type, such as displaying an icon associated with that type.
	//			oxmdtMailUser (0)			Local user
	//			oxmdtDistList (1)			Distribution list
	//			oxmdtForum (2)				Public folder
	//			oxmdtAgent (3)				Agent
	//			oxmdtOrganisation (4)		Organization
	//			oxmdtPrivateDistList (5)	Private distribution list
	//			oxmdtRemoteMailUser (6)		Remote user
	// --- Effect: none

	CString GetName();
	// --- In: none
	// --- Out: none
	// --- Returns: the display name or alias of the AddressEntry object as a string.
	// --- Effect: none

	void SetName(CString);
	// --- In: the display name or alias of the AddressEntry object
	// --- Out: none
	// --- Returns: none
	// --- Effect: sets the display name or alias of the AddressEntry object as a string.

	CString GetAddress();
	// --- In: none
	// --- Out: none
	// --- Returns: the messaging address of an address list entry or message recipient. 
	// --- Effect: none

	void SetAddress(CString);
	// --- In: the messaging address of an address list entry or message recipient.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Sets the messaging address of an address list entry or message recipient. 

	CString GetType();
	// --- In: none
	// --- Out: none
	// --- Returns: the address type, such as "SMTP," "Fax," or "X.400." 
	// --- Effect: none

	void SetType(CString);
	// --- In: the address type 
	// --- Out: none
	// --- Returns: none
	// --- Effect: Specifies the address type, such as "SMTP," "Fax," or "X.400." 

	CString GetId();
	// --- In: none
	// --- Out: none
	// --- Returns: the unique ID of the object as a string.
	// --- Effect: none
	
	COXMFields GetFields();
	// --- In: none
	// --- Out: none
	// --- Returns: a single field (a Field object) or a collection of fields (a Fields collection object) of the Folder object.
	// --- Effect: none

	void Details(HWND hParentWindow = NULL);
	// --- In: hParentWindow: The parent window handle for the details dialog box.
	//			A value of NULL specifies a application modal dialog box.
	// --- Out: none
	// --- Returns: none
	// --- Effect: displays a dialog box that provides detailed information about an AddressEntry object

	void Update(BOOL bMakePermanent = TRUE, BOOL bRefreshObject = FALSE);
	// --- In: bMakePermanent: TRUE indicates that the property cache is flushed and all changes are
	//			committed in the underlying store. FALSE indicates that the property cache is flushed and
	//			not committed to the store.
	//		   bRefreshObject: TRUE indicates that the property cache is reloaded from the values in the
	//			underlying store. FALSE indicates that the property cache is not reloaded.
	// --- Out: none
	// --- Returns: none
	// --- Effect: Saves AddressEntry object changes in the MAPI system

	void Delete();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: deletes the specified address from the address book
};


#endif
