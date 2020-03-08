#ifndef __SOFT_CHAIN_H__
#define __SOFT_CHAIN_H__
#include "./softType.h"

typedef struct softChainItemType    softChainItem;
typedef struct softChainType    softChain;

struct softChainItemType
{
  void  *memPtr;
  struct chainItem *chainItemNext;
};

struct softChainType
{
    void *mem;
    uint32_t size;
    uint32_t usedAmount;
    uint32_t emptyAmount;
    uint32_t itemSize;
    softChainItem* itemUsed;
    softChainItem* itemEmpty;
};


/*
*
*/
int32_t softChainInit(softChain *sc);

/*
*
*/
int32_t softChainMallco(softChain *sc);

/*
*
*/
int32_t softChainfree(softChain *sc);

/*
*
*/
int32_t softChainPuthead(softChain *sc);

/*
*
*/
int32_t softChainPuttail(softChain *sc);

/*
*
*/
int32_t softChaininsertfront(softChain *sc,softChainItem* ins,softChainItem* ref);

/*
*
*/
int32_t softChaininsertback(softChain *sc,softChainItem* ins,softChainItem* ref);

/*
*
*/
int32_t softChaininsertIndex(softChain *sc,softChainItem* ins,uint32_t index);

/*
*
*/
int32_t softChainPutDataToItem(softChainItem* item,void* pData,int32_t len);

/*
*
*/
int32_t softChainGetDataFromItem(softChainItem* item,void* pData,int32_t *len);
























#endif

