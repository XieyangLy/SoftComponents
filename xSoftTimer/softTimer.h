
#ifndef X_SOFT_TIMER_H__
#define X_SOFT_TIMER_H__
#include "../SoftType.h"

#ifdef __cplusplus
extern "C" {
#endif
	
typedef struct softTimerType softTimer;
typedef struct softTimerItemType softTimerItem;


struct softTimerItemType
{
    uint32_t uuid;
    uint32_t callbackTick;
    uint32_t callbackCircle;
    void (*callback)(uint32_t param);
    uint32_t param;
    softTimerItem* next;
};

struct softTimerStampType
{
	  uint8_t circle;               //计时圈数
    uint32_t cnt;
};


struct softTimerType
{
    struct {
        uint32_t run:1;           //运行状态
        uint32_t :0;
    }stat;
		struct softTimerStampType stamp;
//    uint8_t circle;               //计时圈数
//    uint32_t cnt;
    uint32_t uuidNext;            //下一个可用的uuid
    softTimerItem* item;
    int32_t (*inc)(softTimer* const st);
    int32_t (*pause)(softTimer* const st);
    int32_t (*resume)(softTimer* const st);
    int32_t (*cntSet)(softTimer* const st,uint32_t cnt);
    int32_t (*circleSet)(softTimer* const st,uint32_t circle);
    int32_t (*getTick)(softTimer* const st,uint8_t *circle,uint32_t *cnt);
    int32_t (*getUUID)(softTimer* const st);
    int32_t (*itemInsert)(softTimer* const st,softTimerItem *item);
    int32_t (*itemRemove)(softTimer* const st,softTimerItem *item);
    int32_t (*task)(softTimer* const st);
		/*
		*检查时间溢出，0:时间未溢出,1时间溢出
		*/
		int32_t (*checkDelay)(softTimer* const st,struct softTimerStampType stamp,uint32_t ticks);
		
		/*
		*获取时间差
		*/
		int32_t (*getDelay)(softTimer* const st,struct softTimerStampType stamp);
		
		/*
		*获取时间戳
		*/
		int32_t (*getStamp)(softTimer* const st,struct softTimerStampType *sTamp);
};

extern struct softTimerType hSoftTimer1;


/*
* softtime init
*/

int32_t softTimerInit(softTimer *st);


/*
* 初始化系统时钟
*/
int32_t softTimerBaseInit(void);

#ifdef __cplusplus
}
#endif

#endif //X_SOFT_TIMER_H__
