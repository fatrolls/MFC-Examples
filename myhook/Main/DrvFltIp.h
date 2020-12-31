/////////////////////////////////////////////////////
// DrvFltIp.h文件

#ifndef __DRVFLTIP_H__
#define __DRVFLTIP_H__

// 自定义设备类型，在创建设备对象时使用
// 注意，自定义值的范围是32768-65535
#define FILE_DEVICE_DRVFLTIP  0x00654322

// 自定义的IO控制代码，用于区分不同的设备控制请求
// 注意，自定义值的范围是2048-4095
#define DRVFLTIP_IOCTL_INDEX  0x830

//
// 定义各种设备控制代码。分别是开始过滤、停止过滤、添加过滤规则、清除过滤规则
// 
#define START_IP_HOOK	CTL_CODE(FILE_DEVICE_DRVFLTIP, \
				DRVFLTIP_IOCTL_INDEX, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define STOP_IP_HOOK	CTL_CODE(FILE_DEVICE_DRVFLTIP, \
				DRVFLTIP_IOCTL_INDEX+1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define ADD_FILTER	CTL_CODE(FILE_DEVICE_DRVFLTIP, \
				DRVFLTIP_IOCTL_INDEX+2, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define CLEAR_FILTER	CTL_CODE(FILE_DEVICE_DRVFLTIP, \
				DRVFLTIP_IOCTL_INDEX+3, METHOD_BUFFERED, FILE_ANY_ACCESS)

// 定义过滤规则的结构
struct CIPFilter
{
	USHORT protocol;		// 使用的协议

	ULONG sourceIP;			// 源IP地址
	ULONG destinationIP;		// 目标IP地址

	ULONG sourceMask;		// 源地址屏蔽码
	ULONG destinationMask;		// 目的地址屏蔽码

	USHORT sourcePort;		// 源端口号
	USHORT destinationPort;		// 目的端口号
	
	BOOLEAN bDrop;			// 是否丢弃此封包
};

#endif // __DRVFLTIP_H__