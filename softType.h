#ifndef __SOFT_TYPE_H__
#define __SOFT_TYPE_H__

#include "stdint.h"


#ifndef false
#define false 0
#endif

#ifndef true
#define true !false
#endif

#ifndef NULL
#define NULL 0
#endif



#define soft_OK                  0       //操作成功
#define soft_OpErr              -1      //操作错误
#define soft_OverFlow           -2      //溢出错误
#define soft_PtrNULL            -3      //指针为空
#define soft_NoData             -4      //没有数据
#define soft_FrameExhausted     -5      //帧资源耗尽







#endif
