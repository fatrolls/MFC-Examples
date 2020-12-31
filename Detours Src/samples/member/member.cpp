//////////////////////////////////////////////////////////////////////////////
//
//	Module:		member.exe - Detour a member function.
//	File:		member.cpp
//
//  Copyright 2000-2001, Microsoft Corporation
//
//  Microsoft Research Detours Package, Version 1.5 (Build 46)
//
//  By default, C++ member functions use the __thiscall calling convention.
//  In order to Detour a member function, both the trampoline and the detour
//  must have exactly the same calling convention as the target function.
//  Unfortunately, the VC compiler does not support a __thiscall, so the only
//  way to create legal detour and trampoline functions is by making them
//  class members of a "detour" class.
//
//  In addition, C++ does not support converting a pointer to a member
//  function to an arbitrary pointer.  To get a raw pointer, the address of
//  the member function must be moved into a temporrary member-function
//  pointer, then passed by taking it's address, then de-referencing it.
//  Fortunately, the compiler will optimize the code to remove the extra
//  pointer operations.
//
//  If X::Target is a virtual function, the following code will *NOT* work
//  because &X::Target is the address of a thunk that does a virtual call,
//  not the real address of the X::Target.  You can get the real address
//  of X::Target by looking directly in the VTBL for class X, but there
//  is no legal way to 1) get the address of X's VTBL or 2) get the offset
//  of ::Target within that VTBL.  You can of course, figure these out for
//  a particular class and function, but there is no general way to do so.
//
#include <stdio.h>
#include <windows.h>
#include <detours.h>

#pragma warning(disable:4100)   // Trampolines don't use formal parameters.

//////////////////////////////////////////////////////////////// Target Class.
//
class CTarget
{
  public:
    void Target(void) 
        {
            printf("  CTarget::Target!   (this:%08x)\n", this);
        }
};

//////////////////////////////////////////////////////////////// Detour Class.
//
class CDetour /* add ": public CTarget" to enable access member variables... */
{
  public:
    void Detour(void)
        {
            printf("  CDetour::Function! (this:%08x)\n", this);
            Trampoline();
        }

    void Trampoline(void);

    // Class shouldn't have any member variables or virtual functions.
};

DETOUR_TRAMPOLINE_EMPTY(void CDetour::Trampoline());

//////////////////////////////////////////////////////////////////////////////
//
int main(int argc, char **argv)
{
    //////////////////////////////////////////////////////////////////////////
    //
    void (CTarget::* pfTarget)(void) = CTarget::Target;
    void (CDetour::* pfDetour)(void) = CDetour::Detour;
    void (CDetour::* pfTrampoline)(void) = CDetour::Trampoline;
    
	DetourFunctionWithEmptyTrampoline(*(PBYTE*)&pfTrampoline,
                                      *(PBYTE*)&pfTarget,
                                      *(PBYTE*)&pfDetour);

    //////////////////////////////////////////////////////////////////////////
    //
    CTarget target;

    printf("Calling CTarget (w/o Detour):\n");
    ((CDetour*)&target)->Trampoline();
    
    printf("Calling CTarget:\n");
    target.Target();
    
    return 0;
}

