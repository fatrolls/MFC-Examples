/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File char_str.h
// class CWizCharString
// template class for strings with WELL KNOWN maximum length
//
// 16/05/1995 12:14                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizCharString_H
#define __CWizCharString_H

#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif

/////////////////////////////////////////////////////////////////////////////
// class CWizCharString
template <int MAX_SIZE>
class CWizCharString
{
public:
        enum { MIN_SHORT_DIGITS = 6, MIN_LONG_DIGITS = 12 };
// Constructors:
        CWizCharString () { buffer [0] = 0; }
        CWizCharString (const CWizCharString& T)
                { assign (T.buffer); }
        CWizCharString (LPCSTR str)
                { assign (str); }
        CWizCharString (short Number)
                { itoa (Number, buffer, 10); ASSERT(strlen(buffer) < MAX_SIZE);}
        
        CWizCharString (long Number)
                { ltoa (Number, buffer, 10); ASSERT(strlen(buffer) < MAX_SIZE);}

// Destructor:
        ~CWizCharString () {};
public:
// Operators
        CWizCharString& operator= (const CWizCharString& T)
                { assign (T.buffer); return *this; }
        CWizCharString& operator= (LPCSTR str)
                { assign (str); return *this;}
        
        CWizCharString& operator+= (const CWizCharString& T)
                { append (T.buffer); return *this;}
        CWizCharString& operator+= (LPCSTR str)
                { append (str); return *this;}

        CWizCharString operator+ (const CWizCharString& T)
                { return construct (buffer, T.buffer); }
        CWizCharString operator+ (LPCSTR str)
                { return construct (buffer,str); }

        BOOL operator == (LPCSTR str) const { return (Compare(str) == 0);}
        BOOL operator != (LPCSTR str) const { return (Compare(str) != 0);}
        BOOL operator <= (LPCSTR str) const { return (Compare(str) <= 0);}
        BOOL operator <  (LPCSTR str) const { return (Compare(str) <  0);}
        BOOL operator >= (LPCSTR str) const { return (Compare(str) >= 0);}
        BOOL operator >  (LPCSTR str) const { return (Compare(str) >  0);}

        operator LPCSTR() const { return buffer; }
        operator LPSTR()        { return buffer; }
        char operator[] (int i ) const 
                { 
                ASSERT(i >= 0);
                ASSERT(i < MAX_SIZE);
                return buffer [i];
                }
// Operations:
        int Compare (LPCSTR str)       const { return strcmp (buffer,str); }
        int CompareNoCase (LPCSTR str) const { return stricmp (buffer,str);}
        
        int     Length()  const { return strlen (buffer); }
        BOOL    IsEmpty() const { return (buffer [0] == 0);}
        
        LPCSTR Find     (LPCSTR str) const { return strstr (buffer, str); }
        LPCSTR Find     (char ch)    const { return strchr (buffer, ch ); }
        LPCSTR FindOneOf(LPCSTR str) const 
                { int i = strcspn (buffer, str); 
                  return ((buffer [i] == 0) ? NULL : &buffer [i]);}
        LPCSTR FindNotOneOf(LPCSTR str) const 
                { int i = strspn (buffer, str); 
                  return ((buffer [i] == 0) ? NULL : &buffer [i]);}

        void Empty()         { buffer [0] = 0; }
        void MakeUpper()     { strupr (buffer); }
        void MakeLower()     { strlwr (buffer); }
        void Reverse()       { strrev (buffer); }

        void Set (char ch, int i) 
                {
                ASSERT(i >= 0);
                ASSERT(i < MAX_SIZE);
                strnset (buffer, ch, i);
                } 
        void Set (char ch) 
                { strset (buffer, ch); }
// Virtual operations:
protected:
// Implementation:
        void assign (LPCSTR str)
                {
                ASSERT(strlen (str) < MAX_SIZE);
                strcpy (buffer, str);
                }
        void append (LPCSTR str)
                {
                ASSERT((strlen (str) + strlen (buffer)) < MAX_SIZE);
                strcat (buffer, str);
                }
        CWizCharString construct (LPCSTR str1, LPCSTR str2)
                {
                CWizCharString s (str1);
                s += str2;
                return s;
                } 
// Members
        char    buffer [MAX_SIZE];
};

/////////////////////////////////////////////////////////////////////////////
#endif // __CWizCharString_H


