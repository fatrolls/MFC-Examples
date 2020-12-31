// ReadThread.cpp (EX26C)

#include "StdAfx.h"
#include "Thread.h"
#include "itext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT ReadThreadProc(LPVOID pParam)
{								   
	g_nIndent = 0;
	::CoInitialize(NULL);
	::CLSIDFromProgID(L"EX26B.TEXT", &g_clsid);
	LPSTORAGE pStgRoot = NULL;
	if(::StgOpenStorage(L"\\DIRECT.STG", NULL,
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

void ReadStorage(LPSTORAGE pStg)
// reads one storage -- recursive calls for substorages
{
    LPSTORAGE pSubStg = NULL;
    LPSTREAM pStream = NULL;
    LPENUMSTATSTG pEnum = NULL;
    STATSTG statstg;
    LPPERSISTSTREAM pPersistStream = NULL;
	
	g_nIndent++;
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
			IText text;
			VERIFY(text.CreateDispatch(g_clsid));
			text.m_lpDispatch->QueryInterface(IID_IPersistStream, 
				(void**) &pPersistStream);
			ASSERT(pPersistStream != NULL);
			pPersistStream->Load(pStream);
			pPersistStream->Release();
			COleVariant va = text.GetText();
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
	g_nIndent--;
}
