         .386p
         .xlist
         include vmm.inc
         include dosmgr.inc
         include debug.inc
         include vwin32.inc
         .list

Declare_Virtual_Device MYVXD, 1, 0, myvxd_control, undefined_device_id, undefined_init_order

Begin_Control_Dispatch myvxd
Control_Dispatch Sys_Dynamic_Device_Init, OnSysDynamicDeviceInit
Control_Dispatch Sys_Dynamic_Device_Exit, OnSysDynamicDeviceExit
Control_Dispatch W32_DeviceIoControl, OnDeviceIoControl
End_Control_Dispatch myvxd

VxD_LOCKED_DATA_SEG
next_begin dd  0
next_end dd    0
beginfunc dd   0
endfunc  dd    0
appthread dd   0

ctlfunc  label dword
         dd    offset32 ignore
         dd    offset32 setbegin
         dd    offset32 setend
numfunc  equ   ($-ctlfunc)/4

VxD_LOCKED_DATA_ENDS

;------------------------------------------------------------------------------

BeginProc OnSysDynamicDeviceInit, locked
         GetVxDServiceOrdinal eax, DOSMGR_Begin_V86_App
         mov   esi, offset32 BeginHook
         VMMCall Hook_Device_Service
         jc    initfail

         GetVxDServiceOrdinal eax, DOSMGR_End_V86_App
         mov   esi, offset32 EndHook
         VMMCall Hook_Device_Service
         jc    initfail1

;        clc
         ret

initfail1:
         GetVxDServiceOrdinal eax, DOSMGR_Begin_V86_App
         mov   esi, offset32 BeginHook
         VMMCall Unhook_Device_Service

initfail:
         stc
         ret
EndProc OnSysDynamicDeviceInit

;------------------------------------------------------------------------------

BeginProc OnSysDynamicDeviceExit, locked
         GetVxDServiceOrdinal eax, DOSMGR_Begin_V86_App
         mov   esi, offset32 BeginHook
         VMMCall Unhook_Device_Service

         GetVxDServiceOrdinal eax, DOSMGR_End_V86_App
         mov   esi, offset32 EndHook
         VMMCall Unhook_Device_Service

         clc
         ret
EndProc OnSysDynamicDeviceExit

;------------------------------------------------------------------------------

BeginProc OnDeviceIoControl, pageable
         mov   eax, [esi + dwIoControlCode]
         cmp   eax, numfunc
         jae   ignore
         jmp   [ctlfunc + 4 *eax]

ignore:
         xor   eax, eax
         ret

setbegin:
         mov   eax, [esi + lpvInBuffer]
         mov   eax, [eax]
         mov   beginfunc, eax
         VMMCall Get_Cur_Thread_Handle
         mov   appthread, edi
         jmp   ignore

setend:
         mov   eax, [esi + lpvInBuffer]
         mov   eax, [eax]
         mov   endfunc, eax
         jmp   ignore

EndProc OnDeviceIoControl

;------------------------------------------------------------------------------

BeginProc BeginHook, service, hook_proc, next_begin, locked
         pushad
         mov   eax, beginfunc
         call  DoApc
         popad
         jmp   [next_begin]
EndProc BeginHook

;------------------------------------------------------------------------------

BeginProc EndHook, service, hook_proc, next_end, locked
         pushad
         mov   eax, endfunc
         call  DoApc
         popad
         jmp   [next_end]
EndProc EndHook

;------------------------------------------------------------------------------

BeginProc DoApc, locked
         test  eax, eax
         jz    doapc_done
         VxDCall _VWIN32_QueueUserApc, <eax, esi, appthread>

doapc_done:
         ret
EndProc  DoApc

         end
