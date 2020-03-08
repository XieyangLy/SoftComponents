#include "xDebugTools.h"

#include "stdint.h"


inline char hexToChar(char hex);

char hexCacheArry[HEX_CACHE_ARRY_LEN + 1];
int xDebug_HexArryPrint(char TerminalId,char* arry,unsigned int len)
{
	uint16_t arryPtr=0,cachePtr=0;
	int sendLen = 0;
	int ret;
	for(arryPtr = 0;arryPtr < len;arryPtr++)
	{
		hexCacheArry[cachePtr++] = hexToChar((arry[arryPtr]>>4)&0x0F);
		hexCacheArry[cachePtr++] = hexToChar(arry[arryPtr]&0x0F);
		hexCacheArry[cachePtr++] = ' ';
		if(cachePtr > HEX_CACHE_ARRY_LEN-3)		//HEX_CACHE_ARRY_LEN-2”√¿¥∑¿÷π“Á≥ˆ
		{
			hexCacheArry[cachePtr++] = '\0';
			ret = xDebug_TerminalOut(TerminalId,hexCacheArry);
			cachePtr = 0;
			if(ret < 0)
			{
				return ret;
			}else{
			sendLen +=ret;
			}
		}
	}
	if(cachePtr != 0)
	{
		hexCacheArry[cachePtr++] = '\0';		
		ret = xDebug_TerminalOut(TerminalId,hexCacheArry);
	}
	xDebug_TerminalOut(TerminalId,"\r\n");
	if(ret < 0)
	{
		return ret;
	}else{
		sendLen +=ret;
	}

	return sendLen;
}




char hexToChar(char hex)
{
	return hex < 10?hex + '0':hex + 'A' - 10;
}





