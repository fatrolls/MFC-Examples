///////////////////////////////////////////////////////////////////////////////
//
// ustring.cpp - Copyright 1997, Don Box
//
// This file contains the implementation of several conversion routines 
// that are used by the String816 class for duplicating/converting strings
// on the fly.
//
//     uxdup(const char *psz) - returns a new-ed wchar_t string based on psz
//     uxdup(const wchar_t *psz) - returns a new-ed char string based on psz
//     

#ifndef _USTRING_CPP
#define _USTRING_CPP

wchar_t *uxdup(const char *psz)
{
    size_t cch = strlen(psz) + 1;
    wchar_t *pwszResult = (wchar_t*)malloc(cch * sizeof(wchar_t));
    if (pwszResult)
        mbstowcs(pwszResult, psz, cch);
    return pwszResult;
}

char *uxdup(const wchar_t *pwsz)
{
    size_t cch = wcslen(pwsz) + 1;
    char *pszResult = (char*)malloc(sizeof(char) * cch);
    if (pszResult)
        wcstombs(pszResult, pwsz, cch);
    return pszResult;
}

#endif

