         .386p
         include vmm.inc
         include debug.inc

Declare_Virtual_Device MYVXD, 1, 0, MYVXD_control,\
                       Undefined_Device_ID, Undefined_Init_Order

Begin_Control_Dispatch MYVXD

Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
Control_Dispatch Create_Thread, _OnCreateThread, cCall, <edi>
Control_Dispatch Destroy_Thread, _OnDestroyThread, cCall, <edi>
Control_Dispatch W32_DeviceIoControl, _OnW32DeviceIoControl, cCall, <esi>

End_Control_Dispatch   MYVXD

         end
