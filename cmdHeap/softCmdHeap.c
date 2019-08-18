/*
*命令堆
*流程控制器
*
*/
// include *************************
#include "softCmdHeap.h"
#include "string.h"
//**********************************


//definition ***********************


//**********************************


//global variable ******************


//**********************************


//private variable *****************


//**********************************


//function *************************

//**********************************


//Code *****************************
/*
*将命令压入命令堆
*参数:cmdHeap要操作的命令堆 cmdFun 要压入的命令		funParam:命令调用时传入的参数
*返回值:0:命令压入成功,	1命令压入失败
*/
int8_t cmdHeapPush(struct cmdHeapType *cmdHeap,void (*cmdFun)(void),void (*cmdCpltClbk)(uint32_t param),uint32_t funParam)
{
	if(cmdHeap->cmdHeapPtr >= cmdHeap->cmdHeapLength) return 1;
	cmdHeap->cmdHeapPtr++;	//命令堆指针移动	
	cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].Clbkparam = funParam;
	cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdCpltClbk = cmdCpltClbk;
	cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdFun = cmdFun;
	
	return 0;
}


/*
*弹出命令堆顶层命令
*参数:cmdHeap要操控的命令堆
*返回值:	0:操作成功,		1:操作失败
*
*/
int8_t cmdHeapPop(struct cmdHeapType *cmdHeap)
{
	if(cmdHeap->cmdHeapPtr > 0)
	{
		cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdFun = NULL;
		//执行回调动作
		if(cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdCpltClbk != NULL)
		{
			cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdCpltClbk(cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].Clbkparam);
		}
		cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdCpltClbk = NULL;
		cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].Clbkparam = 0;
		cmdHeap->cmdHeapPtr--;
		return 0;
	}
	return 1;
}

/*
*移除命令堆顶层命令，该操作不会调用回调函数
*参数:cmdHeap要操控的命令堆
*返回值:	0:操作成功,		1:操作失败
*
*/
int8_t cmdHeapRemove(struct cmdHeapType *cmdHeap)
{
	if(cmdHeap->cmdHeapPtr > 0)
	{
		cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdFun = NULL;
		cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].cmdCpltClbk = NULL;
		cmdHeap->cmdHeap[cmdHeap->cmdHeapPtr].Clbkparam = 0;
		cmdHeap->cmdHeapPtr--;
		return 0;
	}
	return 1;
}

//**********************************
