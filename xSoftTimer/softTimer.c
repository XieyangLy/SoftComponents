
#include "./softTimer.h"
#include "stm32f7xx_hal.h"
//#include "stm32f7xx_hal_tim.h"

int32_t  softTimerInc(softTimer* const st);
int32_t  softTimerPause(softTimer* const st);
int32_t  softTimerResume(softTimer* const st);
int32_t softTimerCntSet(softTimer* const st,uint32_t cnt);
int32_t softTimerCircleSet(softTimer* const st,uint32_t circle);
int32_t softTimerGetTick(softTimer* const st,uint8_t* circle,uint32_t* cnt);
int32_t softTimerGetUUID(softTimer* const st);
int32_t softTimeritemInsert(softTimer* const st,softTimerItem *item);
int32_t softTimerRemove(softTimer* const st,softTimerItem *item);
int32_t softTimerTask(softTimer* const st);
int32_t softTimerCheckDelay(softTimer* const st,struct softTimerStampType stamp,uint32_t ticks);
int32_t softTimerGetDelay(softTimer* const st,struct softTimerStampType stamp,uint32_t *ticks);
int32_t softTimerGetStamp(softTimer* const st,struct softTimerStampType *sTamp);

/*
*********************  variable
*/
TIM_HandleTypeDef  htim7; 

struct softTimerType hSoftTimer1;

/*
* softtime init
*/

int32_t softTimerInit(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    st->stat.run = true;
    st->stamp.circle = 0;
    st->stamp.cnt = 0;
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
		st->getDelay					= softTimerGetDelay;
		st->checkDelay			= softTimerCheckDelay;
		st->getStamp				= softTimerGetStamp;
		return soft_OK;
}



int32_t  softTimerInc(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    if(!st->stat.run) return soft_OK;
    st->stamp.cnt++;
    if(st->stamp.cnt == 0xFFFFFFFF) st->stamp.circle++;
    return soft_OK;
}

int32_t  softTimerPause(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    st->stat.run = false;
		return soft_OK;
}


int32_t  softTimerResume(softTimer* const st)
{
    if(st == NULL) return soft_PtrNULL;

    st->stat.run = true;
		return soft_OK;
}



int32_t softTimerCntSet(softTimer* const st,uint32_t cnt)
{
    if(st == NULL) return soft_PtrNULL;

		st->stamp.cnt = cnt;
		return soft_OK;
}


int32_t softTimerCircleSet(softTimer* const st,uint32_t circle)
{
    if(st == NULL) return soft_PtrNULL;

    st->stamp.circle = circle;
		return soft_OK;
}

 int32_t softTimerGetTick(softTimer* const st,uint8_t* circle,uint32_t* cnt)
 {
     if(st == NULL) return soft_PtrNULL;

     *cnt = st->stamp.cnt;
     *circle = st->stamp.circle;

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

inline static int32_t SoftTimerStampSub(struct softTimerStampType stampSrc,struct softTimerStampType StampDec,uint32_t *ticks)
{
	if(stampSrc.circle - StampDec.circle > 1) return 	soft_OverFlow;
	
	if((stampSrc.circle > StampDec.circle)&&(stampSrc.cnt >= StampDec.cnt)) return soft_OverFlow;
	
	if(stampSrc.cnt >= StampDec.cnt)
	{
		*ticks = stampSrc.cnt - StampDec.cnt;
		return soft_OK;
	}
	*ticks =0xFFFFFFFF  - StampDec.cnt +stampSrc.cnt;
	return soft_OK;
}

int32_t softTimerGetDelay(softTimer* const st,struct softTimerStampType stamp,uint32_t *ticks)
{
	return SoftTimerStampSub(st->stamp,stamp,ticks);

}

int32_t softTimerCheckDelay(softTimer* const st,struct softTimerStampType stamp,uint32_t ticks)
{
	uint32_t detTicks;
	if(SoftTimerStampSub(st->stamp,stamp,&detTicks) != soft_OK) return 1;
	if(detTicks > ticks) return 1;
	
	return 0;
}




int32_t softTimerGetStamp(softTimer* const st,struct softTimerStampType *sTamp)
{
	if(st == NULL) return soft_PtrNULL; 
	if(sTamp == NULL) return soft_PtrNULL; 
	*sTamp = st->stamp;
	
	return soft_OK;

}



/*
*检查是否有item触发，并进行回调
*/
int32_t softTimerTask(softTimer* const st)
{


	return soft_OK;
}


void TIM7_Init(void)
{
		//初始化Timer7
	RCC_ClkInitTypeDef    clkconfig = {0};
  uint32_t              uwTimclock = 0;
  uint32_t              uwPrescalerValue = 0;
  uint32_t              pFLatency;
  
	
  /*Configure the TIM7 IRQ priority */
  HAL_NVIC_SetPriority(TIM7_IRQn, TICK_INT_PRIORITY ,0); 
  
  /* Enable the TIM7 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM7_IRQn); 
  
  /* Enable TIM7 clock */
  __HAL_RCC_TIM7_CLK_ENABLE();
  
  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  
  /* Compute TIM6 clock */
  uwTimclock = 2*HAL_RCC_GetPCLK1Freq();
   
  /* Compute the prescaler value to have TIM7 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000) - 1);
  
  /* Initialize TIM7 */
  htim7.Instance = TIM7;
  
  /* Initialize TIMx peripheral as follow:
  + Period = [(TIM7CLK/1000) - 1]. to have a (1/1000) s time base.
  + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
  + ClockDivision = 0
  + Counter direction = Up
  */
  htim7.Init.Period = (1000000 / 1000) - 1;
  htim7.Init.Prescaler = uwPrescalerValue;
  htim7.Init.ClockDivision = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&htim7) == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
		HAL_TIM_Base_Start_IT(&htim7);
    return ;
  }
  
  /* Return function status */
  return ;
}


void TIM7_IRQHandler(void)
{
	if (__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) != RESET)
	{
		hSoftTimer1.inc(&hSoftTimer1);
		__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
	}
}


/*
* 初始化系统时钟  
*/
int32_t softTimerBaseInit(void)
{
	/*
	* 初始化句柄
	*/
	softTimerInit(&hSoftTimer1);

	
	//初始化时钟
	TIM7_Init();
	
	return soft_OK;
}






