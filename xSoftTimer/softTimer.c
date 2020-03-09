
#include "softTimer.h"

int32_t  softTimerInc(softTimer* const st);
int32_t  softTimerPause(softTimer* const st);
int32_t  softTimerResume(softTimer* const st);
int32_t softTimerCntSet(softTimer* const st,uint32_t cnt);
int32_t softTimerCircleSet(softTimer* const st,uint32_t circle);
int32_t softTimerGetTick(softTimer* const st,uint8_t* circle,uint32_t* cnt);
int32_t softTimerGetUUID(softTimer* const st);
int32_t softTimeritemInsert(softTimer* const st,softTimerItem *item);
int32_t softTimerRemove(softTimer* const st,softTimerItem *item);
int32_t softTimerTask(void);





/*
* softtime init
*/

int32_t softTimerInit(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    st->stat.run = true;
    st->circle = 0;
    st->cnt = 0;
    st->uuidNext = 0;
    st->item = NULL;

    st->inc             = softTimerInc;
    st->pause           = softTimerPause;
    st->resume          = softTimerResume;
    st->cntSet          = softTimerCntSet;
    st->circleSet       = softTimerCircleSet;
    st->getTick         = softTimerGetTick;
    st->getUUID         = softTimerGetUUID;
    st->itemInsert      = softTimeritemInsert;
    st->itemRemove      = softTimerRemove;
    st->task            = softTimerTask;
}



int32_t  softTimerInc(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    if(!st->stat.run) return soft_OK;
    st->cnt++;
    if(st->cnt == 0xFFFFFFFF) st->circle++;
    return soft_OK;
}

int32_t  softTimerPause(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    if(st->stat.run = 0) return soft_OK;
}


int32_t  softTimerResume(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    if(st->stat.run = 1) return soft_OK;
}



int32_t softTimerCntSet(softTimer* const st,uint32_t cnt)
{
     if(st == NULL) return soft_PtrNULL;

    if(st->cnt = cnt) return soft_OK;
}


int32_t softTimerCircleSet(softTimer* const st,uint32_t circle)
{
    if(st == NULL) return soft_PtrNULL;

    if(st->circle = circle) return soft_OK;
}

 int32_t softTimerGetTick(softTimer* const st,uint8_t* circle,uint32_t* cnt)
 {
     if(st == NULL) return soft_PtrNULL;

     *cnt = st->cnt;
     *circle = st->circle;

     return soft_OK;
 }


 int32_t softTimerGetUUID(softTimer* const st)
 {
     if(st == NULL) return soft_PtrNULL;
     return st->uuidNext++;
 }

int32_t softTimeritemInsert(softTimer* const st,softTimerItem *item)
{
    softTimerItem *ptr;
    if(st == NULL) return soft_PtrNULL;  
    if(item == NULL) return soft_PtrNULL;  

    if(st->item == NULL) st->item = item;
    ptr = st->item;

    for(;ptr->next != NULL;)
    {
        if(ptr->uuid == item->uuid) return soft_UUIDduplicate;
    }

    ptr->next = item;
    return soft_OK;
}

int32_t softTimerRemove(softTimer* const st,softTimerItem *item)
{
    softTimerItem *ptr;
    if(st == NULL) return soft_PtrNULL;  
    if(item == NULL) return soft_PtrNULL;  

    if(st->item == NULL) return soft_NoData;
    if(st->item->uuid == item->uuid) 
    {
        st->item = NULL;
        return soft_OK;
    }

    ptr = st->item;
    while(ptr->next != NULL )
    {
        if(ptr->next->uuid == item->uuid) 
        {
            ptr->next = ptr->next->next;
            return soft_OK;
        }
    }
    return soft_NoData;
}



/*
*检查是否有item触发，并进行回调
*/
int32_t softTimerTask(void)
{



}

