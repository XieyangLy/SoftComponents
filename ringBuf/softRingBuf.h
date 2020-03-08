#ifndef __SOFT_RING_BUF_H__
#define __SOFT_RING_BUF_H__
#include "../softType.h"


typedef struct softRingBufType softRingBuf;
typedef struct softRingFrameType softRingFrame;

struct softRingFrameAttrType
{
    uint32_t use:1;
    uint32_t :0;
};


struct softRingFrameType
{
   softRingFrame* next;
    uint32_t begin;
    uint32_t length;
    struct softRingFrameAttrType frameAttr;
};

struct softRingBufType
{
    uint8_t  *memPtr;
    uint32_t memSize;
    uint32_t read;
    uint32_t write;
    uint32_t frameNumber;                         //
    uint32_t frameEnable;                       //使能fram
    softRingFrame *softRingFrame;                 //存储fram
/*
*
*/
    int32_t (*putChar)(softRingBuf* const pRingBuf,uint8_t chr);
/*
*
*/
    int32_t (*getChar)(softRingBuf* const pRingBuf,uint8_t *chr);
/*
*
*/
		int32_t (*putData)(softRingBuf* const pRingBuf,uint8_t *pBuf,uint32_t length);
/*
*
*/
    int32_t (*putFrame)(softRingBuf* const pRingBuf,uint8_t *pBuf,uint32_t length);
/*
*
*/
    int32_t (*getFrame)(softRingBuf* const pRingBuf,uint8_t *pBuf,uint32_t length);
/*
*
*/
    int32_t (*clear)(softRingBuf* const pRingBuf);
/*
*
*/
    int32_t (*space)(softRingBuf* const pRingBuf);
/*
*
*/
    int32_t (*amount)(softRingBuf* const pRingBuf);
/*
*
*/
    int32_t (*frameSpace)(softRingBuf* const pRingBuf);
/*
*
*/
    int32_t (*frameAmount)(softRingBuf* const pRingBuf);
};



/*
*
*/
int32_t softRingBufInit(softRingBuf* pRingBuf);












#endif

