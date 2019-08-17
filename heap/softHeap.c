#include "../softType.h"
#include "./softHeap.h"
#include "stdlib.h"

    
 
int32_t softHeapinitialize(struct softHeapCtrlType *hSoftHeap,void *heapBuf,size_t bufSize,size_t itemSize)
{
    if(heapBuf == NULL) return softHeapFail;
    hSoftHeap->heap = heapBuf;
    hSoftHeap->itemSzie = itemSize;
    hSoftHeap->heapCapaciity = bufSize;
    hSoftHeap->heapPtr = 0;
    return softHeapOK;
}

int32_t softHeapPush(struct softHeapCtrlType *hSoftHeap,void *item)
{
    char *des = (uint32_t)hSoftHeap->heap + hSoftHeap->heapPtr *hSoftHeap->itemSzie;
    char *src = item;
    if(hSoftHeap == NULL) return softHeapPtrNull;
    if(item == NULL) return softHeapParamErr;
    if(hSoftHeap->heapPtr >= hSoftHeap->heapCapaciity ) return softHeapFull;

    //数据转移
    for (size_t i = 0 ; i < hSoftHeap->itemSzie; i++)
    {
        *(des++) = *(src++);
    }

    //指针移动
    hSoftHeap->heapPtr++;

    return softHeapOK;
}

int32_t softHeapPop(struct  softHeapCtrlType *hSoftHeap,void *item)
{
    char *src = (uint32_t)hSoftHeap->heap + hSoftHeap->heapPtr *hSoftHeap->itemSzie;
    char *des = item;
    if(hSoftHeap == NULL) return softHeapPtrNull;
    if(item == NULL) return softHeapParamErr;
    if(hSoftHeap->heapPtr <= 0 ) return softHeapEmpty;

    //数据转移
    for (size_t i = 0 ; i < hSoftHeap->itemSzie; i++)
    {
        *(des++) = *(src++);
    }

    //指针移动
    hSoftHeap->heapPtr--;
    
    return softHeapOK;
}

int32_t softHeapReset(struct softHeapCtrlType *hSoftHeap)
{
    if(hSoftHeap == NULL) return softHeapPtrNull;

    //清除数据
    memset(hSoftHeap->heap,0,hSoftHeap->heapCapaciity * hSoftHeap->itemSzie);

    //更新指针
    hSoftHeap->heapPtr = 0;

    return softHeapOK;
}

int32_t softHeapGetItemQuantity(struct softHeapCtrlType *hSoftHeap)
{
    if(hSoftHeap == NULL) return softHeapPtrNull;

    return hSoftHeap->heapPtr;
}

int32_t softHeapGetCapaciity(struct softHeapCtrlType *hSoftHeap)
{
    if(hSoftHeap == NULL) return softHeapPtrNull;

    return hSoftHeap->heapCapaciity;
}

int32_t softHeapGetFreeCapaciity(struct softHeapCtrlType *hSoftHeap)
{
    if(hSoftHeap == NULL) return softHeapPtrNull;
    if(hSoftHeap->heapPtr > hSoftHeap->heapCapaciity) return softHeapOverFlow;

    return hSoftHeap->heapCapaciity - hSoftHeap->heapPtr;
}

