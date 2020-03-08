#include "./softRingBuf.h"

/*
#define container_of(ptr, type, member) ({ \
     const typeof( ((type *)0)->member ) *__mptr = (ptr); \
     (type *)( (char *)__mptr - offsetof(type,member) );})    
*/


int32_t softRingBufInit(softRingBuf* const pRingBuf)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(pRingBuf->memPtr ==NULL) return soft_OpErr;

     //初始化begin和end
     pRingBuf->read = pRingBuf->memSize -1;
     pRingBuf->write = 0;

     //初始化frame
     for(int i=0;i < pRingBuf->frameNumber;i++)
     {
          pRingBuf->softRingFrame[i].next = pRingBuf->softRingFrame[i+1].next;
          pRingBuf->softRingFrame[i].frameAttr.use = false;
     }
}


int32_t softRingPutChar(softRingBuf* const pRingBuf,uint8_t chr)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(pRingBuf->frameEnable) return soft_OpErr;

     //缓冲区满
     if((pRingBuf->write +1)%pRingBuf->memSize == pRingBuf->read) return soft_OverFlow;    

     pRingBuf->memPtr[(pRingBuf->write +1)%pRingBuf->memSize] = chr; return soft_OK;
}


int32_t softRingPutFrame(softRingBuf* const pRingBuf,uint8_t *pBuf,uint32_t length)
{
     softRingFrame * framePtr; 

     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(pBuf == NULL)     return soft_PtrNULL;

     if(!pRingBuf->frameEnable) return soft_OpErr;

     if(pRingBuf->softRingFrame == NULL) return soft_OpErr;

     //缓冲区满
     if((pRingBuf->write + length)%pRingBuf->memSize == pRingBuf->read) return soft_OverFlow;    

     //写入frame信息
     softRingFrame* framePtr = pRingBuf->softRingFrame;
     for(int i=0;framePtr->frameAttr.use;framePtr = framePtr->next)
     {
          if(!framePtr->frameAttr.use)
          {
               framePtr->frameAttr.use = true;
               framePtr->begin = pRingBuf->write;
               framePtr->length = length;
               break;
          }
          if(++i >= pRingBuf->frameNumber) return soft_FrameExhausted;
     }
    
    //写入数据
     for(int i=0;i < length;i++);
     {
          pRingBuf->memPtr[(pRingBuf->write++ + 1)%pRingBuf->memSize] = pBuf++;
     }

     return soft_OK;
}


int32_t softRingGetChar(softRingBuf* const pRingBuf,uint8_t *chr)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(pRingBuf->frameEnable) return soft_OpErr;

      //缓冲区空
     if((pRingBuf->read +1)%pRingBuf->memSize == pRingBuf->write) return soft_NoData;   

     *chr =  pRingBuf->memPtr[(pRingBuf->write +1)%pRingBuf->memSize]; return soft_OK;
}


int32_t softRingGetFrame(softRingBuf* const pRingBuf,uint8_t *pBuf,uint32_t bufLength)
{
     softRingFrame * framePtr;
     int32_t redLength;

     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(pBuf == NULL)     return soft_PtrNULL;

     if(!pRingBuf->frameEnable) return soft_OpErr;

     if(pRingBuf->softRingFrame == NULL) return soft_OpErr;

     //缓冲区满  --fram区段读取不需要判数据空
 //    if((pRingBuf->read + length)%pRingBuf->memSize == pRingBuf->write) return soft_NoData;    

     //查询是否有数据
     if(!pRingBuf->softRingFrame->frameAttr.use) return soft_NoData;
     else framePtr = pRingBuf->softRingFrame;

     if(framePtr->length > bufLength)
     {    //不能全部读取，不清除use标记
          redLength = bufLength;
          framePtr->length -= bufLength;
     }
     else{     //全部读取,指针后移
          redLength = bufLength;
          pRingBuf->softRingFrame->frameAttr.use = false;
          pRingBuf->softRingFrame = pRingBuf->softRingFrame->next;
     }

     //读取数据
     for(int i=0;i < redLength;i++)
     {
          *pBuf++ = pRingBuf->memPtr[framePtr->begin];
          framePtr->begin =  (framePtr->begin +1)% pRingBuf->memSize;
     }
     return redLength;
}

int32_t softRingClear(softRingBuf* const pRingBuf)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;

     //清除数据记录
     pRingBuf->write = 0;
     pRingBuf->read = pRingBuf->memSize - 1;

     //清空frame
     for(int i=0;i<pRingBuf->frameNumber;i++)
     {
          pRingBuf->softRingFrame->begin = 0;
          pRingBuf->softRingFrame->frameAttr.use = 0;
          pRingBuf->softRingFrame->length = 0;
          pRingBuf->softRingFrame = pRingBuf->softRingFrame->next;
     }

     //抹除数据
     #include "stdlib.h"
     memset(pRingBuf->memPtr,0, pRingBuf->memSize);
}


int32_t softRingSpace(softRingBuf* const pRingBuf)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;
     
     if(pRingBuf->write >= pRingBuf->read) return pRingBuf->write - pRingBuf->read;
     else return pRingBuf->memSize - pRingBuf->read + pRingBuf->write;
}


int32_t softRingAmount(softRingBuf* const pRingBuf)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(pRingBuf->read >= pRingBuf->write) return pRingBuf->read - pRingBuf->write;
     else return pRingBuf->memSize - pRingBuf->write+ pRingBuf->read;
}


int32_t softRingFameSpace(softRingBuf* const pRingBuf)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(!pRingBuf->frameEnable) return soft_OpErr;

     if(pRingBuf->softRingFrame == NULL) return soft_OpErr;

     for(int i=0;i < pRingBuf->frameNumber;)
     {
          if(pRingBuf->softRingFrame->frameAttr.use)
          {
               i++;
               continue;
          }
          return pRingBuf->frameNumber - i;
     }

     return 0; //无空闲frame

}

int32_t softRingFameAmount(softRingBuf* const pRingBuf)
{
     if(pRingBuf == NULL)     return soft_PtrNULL;

     if(!pRingBuf->frameEnable) return soft_OpErr;

     if(pRingBuf->softRingFrame == NULL) return soft_OpErr;
     
     for(int i=0;i < pRingBuf->frameNumber;)
     {
          if(pRingBuf->softRingFrame->frameAttr.use)
          {
               i++;
               continue;
          }
          return i;
     }
}









