#include "../softType.h"
#include "./softHeap.h"

    
/*
*初始化softHeap
*参数:  hSoftHeap:要操作的栈，heapBuf栈缓存，itemSize栈元素大小
*返回值:
*/    
int32_t softHeapinitialize(struct softHeapCtrlType *hSoftHeap,void *heapBuf,size_t bufSize,size_t itemSize)
{
    if(heapBuf == NULL) return softHeapFail;
    hSoftHeap->heap = heapBuf;
    hSoftHeap->itemSzie = itemSize;
    hSoftHeap->heapDeepth = bufSize;
    hSoftHeap->heapPtr = 0;
    return softHeapOK;
}




int32_t softHeapPush(struct softHeapCtrlType *hSoftHeap,void *item)
{



}


int32_t softHeapPop(struct  softHeapCtrlType *hSoftHeap,void *item)
{
    
};


int32_t softHeapPopAll(struct softHeapCtrlType *hSoftHeap)
{


}
















