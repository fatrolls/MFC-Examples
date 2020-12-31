#include "StdAfx.h"
#include "ReadWrite.h"
#include "TextComp.h"

CLSID g_clsid; // for the Text Component
int g_nLevel = 0;

UINT ReadThreadProc(const char* g_szRootStorageName);
void ReadStorage(LPSTORAGE pStg);
UINT WriteThreadProc(const char * g_szDirectionPathName, 
					 const char* g_szRootStorageName);
void ReadDirectory(const char* szPath, LPSTORAGE pStg);

UINT ReadThreadProc(const char* g_szRootStorageName)
{
    USES_CONVERSION;
	g_nLevel = 0;
	::CLSIDFromProgID(L"Text.Object", &g_clsid);
	LPSTORAGE pStgRoot = NULL;
	if(::StgOpenStorage(T2COLE(g_szRootStorageName), NULL,
	                    STGM_READ|STGM_SHARE_EXCLUSIVE,
			            NULL, 0, &pStgRoot) == S_OK) {
		ASSERT(pStgRoot!= NULL);
		ReadStorage(pStgRoot);
		pStgRoot->Release();
	}
	else {
		AfxMessageBox("Storage file not available or not readable");
	}
	AfxMessageBox("Read complete");
	return 0;
}

// reads one storage -- recursive calls for substorages
void ReadStorage(LPSTORAGE pStg)
{
    LPSTORAGE pSubStg = NULL;
    LPSTREAM pStream = NULL;
    LPENUMSTATSTG pEnum = NULL;
    STATSTG statstg;
    LPPERSISTSTREAM pPersistStream = NULL;
	
	g_nLevel++;
	if(pStg->EnumElements(0, NULL, 0, &pEnum) != NOERROR) {
		ASSERT(FALSE);
		return;
	}
	while(pEnum->Next(1, &statstg, NULL) == NOERROR) {
		if(statstg.type == STGTY_STORAGE) {
			VERIFY(pStg->OpenStorage(statstg.pwcsName, NULL,
				   STGM_READ|STGM_SHARE_EXCLUSIVE,
				   NULL, 0, &pSubStg) == S_OK);
			ASSERT(pSubStg != NULL);
			ReadStorage(pSubStg);
			pSubStg->Release();
		}
		else if(statstg.type == STGTY_STREAM) {
			VERIFY(pStg->OpenStream(statstg.pwcsName, NULL,
				   STGM_READ|STGM_SHARE_EXCLUSIVE,
				   0, &pStream) == S_OK);
			ASSERT(pStream != NULL);
			ITextObject textObject;
			VERIFY(textObject.CreateDispatch(g_clsid));
			textObject.m_lpDispatch->QueryInterface(IID_IPersistStream, 
				(void**) &pPersistStream);
			ASSERT(pPersistStream != NULL);
			pPersistStream->Load(pStream);
			pPersistStream->Release();
			COleVariant va = textObject.GetText();
			ASSERT(va.vt == VT_BSTR);
			CString str = va.bstrVal;
    		TRACE("%s\n", str);
			pStream->Release();
		}
		else {
			ASSERT(FALSE);  // LockBytes?
		}
		::CoTaskMemFree(statstg.pwcsName);
	}
	pEnum->Release();
	g_nLevel--;
}

UINT WriteThreadProc(const char * g_szDirectionPathName, 
					 const char* g_szRootStorageName)
{
    USES_CONVERSION;
    LPSTORAGE pStgRoot = NULL;
    g_nLevel = 0;
	::CLSIDFromProgID(L"Text.Object", &g_clsid);
    if (::StgCreateDocfile(T2COLE(g_szRootStorageName),
           STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		   0, &pStgRoot) != S_OK) 
	{
	    AfxMessageBox("Create DocFile Failed!");
		return -1;
	}
    ReadDirectory(g_szDirectionPathName, pStgRoot);
    pStgRoot->Release();
    AfxMessageBox("Write Compound File Complete");
    return 0;
}

// read one directory and write one storage 
//      -- recursive calls for substorages
void ReadDirectory(const char* szPath, LPSTORAGE pStg)
{
    USES_CONVERSION;
    WIN32_FIND_DATA fData;
    HANDLE h;
    char szNewPath[MAX_PATH];
    char szStorageName[100];
    char szStreamName[100];
	char szData[512];
    char* pch = NULL;

    LPSTORAGE pSubStg = NULL;
    LPSTREAM pStream = NULL;
    LPPERSISTSTREAM pPersistStream = NULL;

    g_nLevel++;
    strcpy(szNewPath, szPath);
    strcat(szNewPath, "*.*");
    h = ::FindFirstFile(szNewPath, &fData);
    if (h == (HANDLE) 0xFFFFFFFF) return;  // can't find directory
    do {
      if (!strcmp(fData.cFileName, "..") ||
          !strcmp(fData.cFileName, ".") ) continue;
      while((pch = strchr(fData.cFileName, '!')) != NULL) 
      {
	      *pch = '|';
	  }
      if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		// It's a directory, so make a storage
        strcpy(szNewPath, szPath);
        strcat(szNewPath,fData.cFileName);
        strcat(szNewPath, "\\");

        strcpy(szStorageName, fData.cFileName);
        szStorageName[31] = '\0';
        TRACE("%d -- sStorage = %s\n", (g_nLevel - 1) * 4, szStorageName);
        VERIFY(pStg->CreateStorage(T2COLE(szStorageName),
               STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
               0, 0, &pSubStg) == S_OK);
        ASSERT(pSubStg != NULL);
        ReadDirectory(szNewPath, pSubStg);
        pSubStg->Release();
      } 
	  else 
	  {
        if ((pch = strrchr(fData.cFileName, '.')) != NULL) {
          if (!stricmp(pch, ".txt")
			  ||!stricmp(pch, ".c")
			  ||!stricmp(pch, ".cpp")
			  ||!stricmp(pch, ".h")) {
			// It's a text file, so make a stream
			strcpy(szStreamName, fData.cFileName);
            strcpy(szNewPath, szPath);
            strcat(szNewPath, szStreamName);
 			szStreamName[32] = '\0'; // OLE max length
            TRACE("%d -- sStream = %s\n", (g_nLevel - 1) * 4, szNewPath);
			CStdioFile file(szNewPath, CFile::modeRead);
            // Ignore zero-length files
			if(file.ReadString(szData, 511)) {
              TRACE("%s\n", szData);
              VERIFY(pStg->CreateStream(T2COLE(szStreamName),
                     STGM_CREATE | STGM_READWRITE | 
			     	 STGM_SHARE_EXCLUSIVE,
                     0, 0, &pStream) == S_OK);
              ASSERT(pStream != NULL);
			  // Include the null terminator in the stream
			  ITextObject textObject;
			  VERIFY(textObject.CreateDispatch(g_clsid));
			  textObject.m_lpDispatch->QueryInterface(IID_IPersistStream, 
				  (void**) &pPersistStream);
			  ASSERT(pPersistStream != NULL);
			  textObject.SetText(COleVariant(szData));
			  pPersistStream->Save(pStream, TRUE);
			  pPersistStream->Release();
              pStream->Release();
            }
          }
        }
      }
    } while (::FindNextFile(h, &fData));
    g_nLevel--;
}
