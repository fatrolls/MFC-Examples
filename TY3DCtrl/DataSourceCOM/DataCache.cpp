// DataCache.cpp : CDataCache µÄÊµÏÖ

#include "stdafx.h"
#include "DataCache.h"


// CDataCache

STDMETHODIMP CDataCache::CheckNew(LONG type, LONG version, VARIANT_BOOL* b)
{
    *b = FALSE;
    return S_OK;
}

STDMETHODIMP CDataCache::BeginCache(LONG id, BSTR url)
{

    return S_OK;
}