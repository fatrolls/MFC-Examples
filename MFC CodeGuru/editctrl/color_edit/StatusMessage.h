#ifndef _STATUSMESSAGE_H_
#define _STATUSMESSAGE_H_
#include <stdarg.h>

void StatusBarMessage(int pane, char* fmt, ...);
void StatusBarMessage(char* fmt, ...);
#endif