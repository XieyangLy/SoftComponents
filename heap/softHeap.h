/*
*描述文件
*
*/

#ifndef _SOFT_HEAP_H__
#define _SOFT_HEAP_H__
#include "../softType.h"

#define softHeapOK      0
#define softHeapFail    1




struct softHeapCtrlType
{
    void *heap;
    uint32_t heapDeepth;
    uint32_t heapPtr;
    size_t itemSzie;
};


int32_t softHeapinitialize(struct softHeapCtrlType *hSoftHeap,void *heapBuf,size_t bufSize,size_t itemSize);


















#endif
