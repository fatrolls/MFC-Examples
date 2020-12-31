// Thread.h

extern int g_nIndent;
extern const char* g_szBlanks;
extern const char* g_szRootStorageName;

UINT WriteThreadProc(LPVOID pParam);
UINT ReadThreadProc(LPVOID pParam);
void ReadDirectory(const char* szPath, LPSTORAGE pStg);
void ReadStorage(LPSTORAGE pStg);
