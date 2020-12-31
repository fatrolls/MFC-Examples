// stddcls.h -- Precompiled headers for WDM drivers
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifdef __cplusplus
extern "C" {
#endif

#include <wdm.h>
#include <stdio.h>
#include <wmilib.h>
#include <wmistr.h>

#ifdef __cplusplus
	}
#endif

#define PAGEDCODE code_seg("page")
#define LOCKEDCODE code_seg()
#define INITCODE code_seg("init")

#define PAGEDDATA data_seg("page")
#define LOCKEDDATA data_seg()
#define INITDATA data_seg("init")

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

// Override DDK definition of ASSERT so that debugger halts in the
// affected code and halts even in the unchecked OS

#if DBG && defined(_X86_)
	#undef ASSERT
	#define ASSERT(e) if(!(e)){DbgPrint("Assertion failure in "\
	__FILE__ ", line %d: " #e "\n", __LINE__);\
	_asm int 1\
  }
#endif
