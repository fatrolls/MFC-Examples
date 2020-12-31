// MYVXD.h - include file for VxD MYVXD

#include <vtoolscp.h>

#define DEVICE_CLASS		MyvxdDevice
#define MYVXD_DeviceID		UNDEFINED_DEVICE_ID
#define MYVXD_Init_Order	UNDEFINED_INIT_ORDER
#define MYVXD_Major		1
#define MYVXD_Minor		0

class MyvxdDevice : public VDevice
{
public:
};

class MyvxdVM : public VVirtualMachine
{
public:
	MyvxdVM(VMHANDLE hVM);
};

class MyvxdThread : public VThread
{
public:
	MyvxdThread(THREADHANDLE hThread);
};

