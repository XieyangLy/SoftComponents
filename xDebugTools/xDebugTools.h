
#ifndef _X_DEBUG_TOOLS_H__
#define _X_DEBUG_TOOLS_H__

#define SYS_TIME_ENABLE
#define xDebug_IO_Use		xDebug_stdio


#define xDebug_stdio					1				//stdio可以重定向到 ITM,串口,EVR等
#define xDebug_segger_rtt			2







#define HEX_CACHE_ARRY_LEN			200



#if (xDebug_IO_Use == xDebug_stdio)
#include "stdio.h"

#define xDebug_Print(port,...)	printf("%s",__VA_ARGS__)
#define xDebug_TerminalOut(port,...) printf("%s",__VA_ARGS__)

#elif(xDebug_IO_Use == xDebug_segger_rtt)
#include "./SEGGER_RTT_V634h/RTT/SEGGER_RTT.h"

#define xDebug_TerminalOut(port,...)						SEGGER_RTT_TerminalOut(port,__VA_ARGS__)
#define xDebug_Print(port,...)									SEGGER_RTT_printf(port,__VA_ARGS__)

#endif


#ifdef SYS_TIME_ENABLE
				
#define xDebug_printWithTick(port,...)			SEGGER_RTT_printf(port,"%d",HAL_GetTick()) \
		SEGGER_RTT_printf(port,__VA_ARGS__)
#else 
		xDebug_printWithTick()	SEGGER_RTT_printf(port,__VA_ARGS__)
#endif






int xDebug_HexArryPrint(char TerminalId,char* arry,unsigned int len);

#endif
