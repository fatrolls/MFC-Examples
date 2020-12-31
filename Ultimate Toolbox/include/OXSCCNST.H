#ifndef __OXSCCNST_H_
#define __OXSCCNST_H_

const int COMM_MSRSHADOW = 35;              // Modem Status Register "shadow"
const int MSR_CTS = 0x10;                   // see Microsoft PSS ID Q101417
const int MSR_DSR = 0x20;
const int MSR_RI = 0x40;
const int MSR_RLSD = 0x80;

const UINT DefaultSizeReceivingQueue = 4096;
const UINT DefaultSizeTransmissionQueue = 4096;
const UINT DefaultCdTimeout = 2000;
const UINT DefaultCtsTimeout = 5000;
const UINT DefaultDsrTimeout = 5000;

const int MaxNumberOfBuffers = 4;
const int RS232TimerId = 0x1245;
const int RS232TimerValue = 100;                // 100 mSec.
const UINT _Rs232PostMessage_ = WM_USER;
const UINT _Rs232InternalNotify_ = WM_USER+1;

#endif __OXSCCNST_H_
