///////////////////////////////////////////////////////////////////////////////
//
// ustring.cpp - Copyright 1997, Don Box
//
// This file contains overloaded ustrcpy, ustrcat, and ustrlen that
// take either wchar_t or char strings for either argument and map to
// the appropriate CRT routine to do the work. The routines are inlined
// and incur no additional overhead.
//
//     size_t ustrlen(const uchar *p); 
//     uchar *ustrcpy(uchar *p1, const uchar *p2); 
//     uchar *ustrcat(uchar *p1, const uchar *p2); 
//
// where uchar = { wchar_t , char }
//
// This file contains the prototypes for several conversion routines 
// that are used by the String816 class for duplicating/converting strings
// on the fly.
//
//     uxdup(const char *psz) - returns a new-ed wchar_t string based on psz
//     uxdup(const wchar_t *psz) - returns a new-ed char string based on psz
//     
// Finally, this file contains two class definitions:
// 
//     _U - converts const uchar * to const uchar *
//     _UNCC - converts const uchar * to uchar * (needed for non-const correct code)
//
// Usage:
/*

void f(const OLECHAR *pwsz, HWND hwnd)
{
    TCHAR sz[MAX_PATH];
    GUID guid;
    ustrcpy(sz, pwsz); // overloads to correct copy/conversion routine
    SetWindowText(hwnd, _U(pwsz)); // _U temporarily dups buffer if needed
    GetWindowText(hwnd, sz, MAX_PATH);
    CLSIDFromString(_UNCC(sz), &guid); // _UNCC needed because api non-const-correct
}

*/

#ifndef _USTR_H
#define _USTR_H

#include <limits.h>

inline size_t ustrlen(const wchar_t *psz)
{
    return wcslen(psz);
}

inline size_t ustrlen(const char *psz)
{
    return strlen(psz);
}

inline char *ustrcpy(char *pszTarget, const wchar_t *pszSrc)
{
    return wcstombs(pszTarget, pszSrc, INT_MAX), pszTarget;
}

inline wchar_t *ustrcpy(wchar_t *pszTarget, const wchar_t *pszSrc)
{
    return wcscpy(pszTarget, pszSrc), pszTarget;
}

inline char *ustrcpy(char *pszTarget, const char *pszSrc)
{
    return strcpy(pszTarget, pszSrc), pszTarget;
}

inline wchar_t *ustrcpy(wchar_t *pszTarget, const char *pszSrc)
{
    return mbstowcs(pszTarget, pszSrc, INT_MAX), pszTarget;
}

inline char *ustrcat(char *pszTarget, const wchar_t *pszSrc)
{
    return wcstombs(pszTarget + ustrlen(pszTarget), pszSrc, INT_MAX), pszTarget;
}

inline wchar_t *ustrcat(wchar_t *pszTarget, const wchar_t *pszSrc)
{
    return wcscat(pszTarget, pszSrc);
}

inline char *ustrcat(char *pszTarget, const char *pszSrc)
{
    return strcat(pszTarget, pszSrc);
}

inline wchar_t *ustrcat(wchar_t *pszTarget, const char *pszSrc)
{
    return mbstowcs(pszTarget + ustrlen(pszTarget), pszSrc, INT_MAX), pszTarget;
}

// these two routines are equivalent to strdup but convert 
// instead of just copying

wchar_t *uxdup(const char *psz);
char *uxdup(const wchar_t *pwsz);


// String816 maps const wchar_t * and const char * to 
// either const wchar_t * or const char * depending on context
class String816
{
    wchar_t *m_pwsz;
    char    *m_psz;
    BOOL     m_bIsWide;
public:
    String816(const char *psz)
        : m_pwsz(0), m_psz((char*)psz), m_bIsWide(FALSE)
    {
    }

    String816(const wchar_t *pwsz)
        : m_pwsz((wchar_t*)pwsz), m_psz(0), m_bIsWide(TRUE)
    {
    }

    operator const wchar_t * (void)
    {
        if (!m_bIsWide && m_pwsz == 0)
            m_pwsz = uxdup(m_psz);
        return m_pwsz;
    }

    operator const char * (void)
    {
        if (m_bIsWide && m_psz == 0)
            m_psz = uxdup(m_pwsz);
        return m_psz;
    }

    ~String816(void)
    {
        if (m_bIsWide && m_psz)
            free(m_psz);
        else if (!m_bIsWide && m_pwsz)
            free(m_pwsz);
    }
};

typedef String816 _U;
// class _UNCC adds non-const conversion operators to String816
class _UNCC : public String816
{
public:
    _UNCC(const char *psz)
        : String816(psz)
    {
    }

    _UNCC(const wchar_t *pwsz)
        : String816(pwsz)
    {
    }

    operator wchar_t * (void)
    {
        return (wchar_t*)operator const wchar_t *();
    }

    operator char * (void)
    {
        return (char*)operator const char *();
    }

};


#endif
