#include "./softRingBuf.h"

/*
#define container_of(ptr, type, member) ({ \
     const typeof( ((type *)0)->member ) *__mptr = (ptr); \
     (type *)( (char *)__mptr - offsetof(type,member) );})    
*/



int32_t softRingBufInit(softRingBuf pRingBuf)
{



}


int32_t softRingPushChar(softRingBuf pRingBuf,uint8_t chr)
{



}


int32_t softRingPushFrame(softRingBuf pRingBuf,uint8_t *pBuf,uint32_t length)
{




}


int32_t softRingPopChar(softRingBuf pRingBuf,uint8_t *chr)
{



}


int32_t softRingPopFrame(softRingBuf pRingBuf,uint8_t *pBuf,uint32_t length)
{


}

int32_t softRingClear(softRingBuf pRingBuf)
{


}


int32_t softRingSpace(softRingBuf pRingBuf)
{



}


int32_t softRingAmount(softRingBuf pRingBuf)
{




}


