; RMREG.ASM -- Test of real-mode registry access

    .386p
    include vmm.inc
    include vmmreg.inc
    include regstr.inc

Declare_Virtual_Device RMREG, 1, 0, rmreg_control,\
    Undefined_Device_Id, Undefined_Init_Order

Begin_Control_Dispatch RMREG
End_Control_Dispatch RMREG

VxD_REAL_INIT_SEG

  ; INT 3

    mov   _ServiceEntry, ecx

    LDR_RegOpenKey HKEY_LOCAL_MACHINE, <offset namevxd>, ds,\
	<offset hvxd>, ds

    test  ax, ax
    jnz   fail1

    LDR_RegOpenKey hvxd, <offset myname>, ds, <offset hme>, ds

    test  ax, ax
    jnz   fail2

    Ldr_RegQueryValueEx hme, <offset portname>, ds, 0, 0, 0,\
	<offset port>, ds, <offset portsize>, ds

    test  ax, ax
    jnz   fail3

fail3:
    LDR_RegCloseKey hme
fail2:
    LDR_RegCloseKey hvxd
fail1:

alldone:
    xor   ax, ax
    xor   bx, bx
    xor   si, si
    ret

_ServiceEntry dd 0

namevxd  db    REGSTR_PATH_VXD, 0
hvxd	 dd    0
myname	 db    'RMREG', 0
hme	 dd    0
portname db    'port', 0
port	 dd    0
portsize dd    size port
VxD_REAL_INIT_ENDS

    end
