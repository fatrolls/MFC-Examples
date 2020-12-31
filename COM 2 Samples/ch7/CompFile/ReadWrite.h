extern UINT ReadThreadProc(const char* g_szRootStorageName);
extern void ReadStorage(LPSTORAGE pStg);
extern UINT WriteThreadProc(const char * g_szDirectionPathName, 
							const char* g_szRootStorageName);
extern void ReadDirectory(const char* szPath, LPSTORAGE pStg);

