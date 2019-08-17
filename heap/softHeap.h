/*
*描述文件
*
*/

#ifndef _SOFT_HEAP_H__
#define _SOFT_HEAP_H__
#include "../softType.h"

#define softHeapOK          0
#define softHeapFail        -1
#define softHeapFull        -2
#define softHeapEmpty       -3
#define softHeapOverFlow    -4
#define softHeapParamErr    -5
#define softHeapNotFound    -6
#define softHeapPtrNull     -7


#define softHeapCtrlTypeDef(name,heap_cap,i_size)   uint8_t name##HeapBuf[heap_cap*i_size];  \
struct softHeapCtrlType name= \
{   \
    .heap = name##HeapBuf,\
    .heapCapaciity = heap_cap,\
    .itemSzie = i_size,\
    .heapPtr = 0,\
}

struct softHeapCtrlType
{
    void *heap;
    int32_t heapCapaciity;
    int32_t heapPtr;
    size_t itemSzie;
};


/*
*   基础操作
*/

/*
*初始化softHeap,用于自己创建
*参数:  hSoftHeap:要操作的栈指针，heapBuf栈缓存，itemSize栈元素大小
*返回值:操作成功softHeapOK，否作，返回故障信息
*/   
int32_t softHeapinitialize(struct softHeapCtrlType *hSoftHeap,void *heapBuf,size_t bufSize,size_t itemSize);

/*
*将数据入栈
*参数：hSoftHeap:要操作的栈指针，item要压入的元素
*返回值:操作成功softHeapOK，否则返回故障信息
*/
int32_t softHeapPush(struct softHeapCtrlType *hSoftHeap,void *item);

/*
*弹出栈顶数据
*参数：hSoftHeap:要操作的栈指针，item接收数据的buf
*返回值:操作成功softHeapOK，否则返回故障信息
*/
int32_t softHeapPop(struct  softHeapCtrlType *hSoftHeap,void *item);

/*
*栈数据复位，清空所有数据
*参数：hSoftHeap:要操作的栈指针
*返回值:操作成功softHeapOK，否则返回故障信息
*/
int32_t softHeapReset(struct softHeapCtrlType *hSoftHeap);

/*
*获取栈内数据量
*参数：hSoftHeap:要操作的栈指针
*返回值:元素数量，如果hSoftHeap为空，则返回错误
*/
int32_t softHeapGetItemQuantity(struct softHeapCtrlType *hSoftHeap);

/*
*获取栈总容量
*参数：hSoftHeap:要操作的栈指针
*返回值:栈总容量，如果hSoftHeap为空，则返回错误
*/
int32_t softHeapGetCapaciity(struct softHeapCtrlType *hSoftHeap);

/*
*获取剩余容量
*参数：hSoftHeap:要操作的栈指针
*返回值:栈剩余容量，如果hSoftHeap为空，则返回错误
*/
int32_t softHeapGetFreeCapaciity(struct softHeapCtrlType *hSoftHeap);

#endif
