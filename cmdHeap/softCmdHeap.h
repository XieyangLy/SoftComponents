
#ifndef _SOFT_CMD_HEAP_H__
#define _SOFT_CMD_HEAP_H__

#include "../softType.h"

#define softHeapCtrlTypeDef(name,heap_cap)   struct softCmdItemType name##HeapBuf[heap_cap];  \
struct cmdHeapType name = \
{   \
    .cmdHeap = name##HeapBuf,\
    .heapCapaciity = heap_cap,\
    .heapPtr = 0,\
};


struct softCmdItemType
{
    void (*taskFun)(void);
    void (*callback)(void *param);
    uint32_t callbackParam;
};

struct cmdHeapType
{
	struct cmdHeapItemType *cmdHeap;		//命令堆
	uint8_t heapCapaciity;
	uint8_t heapPtr;
};

/*
*获取当前命令堆顶部元素
*参数:命令堆句柄
*返回值:命令堆元素
*/
#define cmdHeapCurItem(x)		(x)->cmdHeap[(x)->cmdHeapPtr]

/*
*将命令压入命令堆
*参数:cmdHeap要操作的命令堆 cmdFun 要压入的命令		funParam:命令调用时传入的参数
*返回值:0:命令压入成功,	1命令压入失败
*/
int8_t cmdHeapPush(struct cmdHeapType *cmdHeap,void (*cmdFun)(void),void (*cmdCpltClbk)(uint32_t param),uint32_t funParam);

/*
*弹出命令堆顶层命令
*参数:cmdHeap要操控的命令堆
*返回值:	0:操作成功,		1:操作失败
*/
int8_t cmdHeapPop(struct cmdHeapType *cmdHeap);

/*
*移除命令堆顶层命令，该操作不会调用回调函数
*参数:cmdHeap要操控的命令堆
*返回值:	0:操作成功,		1:操作失败
*
*/
int8_t cmdHeapRemove(struct cmdHeapType *cmdHeap);



#endif
