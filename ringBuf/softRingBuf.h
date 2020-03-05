#ifndef __SOFT_RING_BUF_H__
#define __SOFT_RING_BUF_H__
#include "../softType.h"


typedef struct softRingBufType* softRingBuf;
typedef struct softRingFrameType* softRingFrame;

struct softRingFrameType
{
   softRingFrame next;
    uint32_t begin;
    uint32_t length;

};

struct softRingBufType
{
    uint8_t  *memPtr;
    uint32_t memSize;
    softRingFrame framBuf;
    uint32_t frameSize;
    uint32_t begin;
    uint32_t end;
    softRingFrame frameChainBegin;
    softRingFrame frameChainEnd;
    uint32_t frameNumber;
    uint32_t frameEnable;
    int32_t (*pushChar)(softRingBuf pRingBuf,uint8_t chr);
    int32_t (*pushFrame)(softRingBuf pRingBuf,uint8_t *pBuf,uint32_t length);
    int32_t (*popChar)(softRingBuf pRingBuf,uint8_t *chr);
    int32_t (*popFrame)(softRingBuf pRingBuf,uint8_t *pBuf,uint32_t length);
    int32_t (*clear)(softRingBuf pRingBuf);
    int32_t (*space)(softRingBuf pRingBuf);
    int32_t (*amount)(softRingBuf pRingBuf);

};


/*
*
*/
int32_t softRingBufInit(softRingBuf pRingBuf);

/*
*
*/
int32_t softRingPushChar(softRingBuf pRingBuf,uint8_t chr);

/*
*
*/
int32_t softRingPushFrame(softRingBuf pRingBuf,uint8_t *pBuf,uint32_t length);

/*
*
*/
int32_t softRingPopChar(softRingBuf pRingBuf,uint8_t *chr);

/*
*
*/
int32_t softRingPopFrame(softRingBuf pRingBuf,uint8_t *pBuf,uint32_t length);

/*
*
*/
int32_t softRingClear(softRingBuf pRingBuf);

/*
*
*/
int32_t softRingSpace(softRingBuf pRingBuf);

/*
*
*/
int32_t softRingAmount(softRingBuf pRingBuf);

















#endif

