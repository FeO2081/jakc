/*
 * jakstm32timer.c
 *
 *  Created on: Jan 9, 2025
 *      Author: JAK
 */
#include "tim.h"
#include "jakmath/jakmath.h"
#include "jakstm32.h"
//
static int jd0usec = 1000;
FASTFUNC void jakstm32_runtimeSTAR(struct jakstm32_runtime *ptr)
{
	int dum = ptr->runtimex - SysTick->VAL;
	ptr->runtimex = SysTick->VAL;
	ptr->runtpr = dum < 0 ? SysTick->LOAD + dum : dum;
	ptr->runtpr_usec = ptr->runtpr / jd0usec;
}
FASTFUNC void jakstm32_runtimeOVER(struct jakstm32_runtime *ptr)
{
	int dum = ptr->runtimex - SysTick->VAL;
	ptr->runtime = dum < 0 ? SysTick->LOAD + dum : dum;
	ptr->runtim_usec = ptr->runtime / jd0usec;
}
//
static void mastTIMX(TIM_TypeDef *timx, sint d0arr)
{
	LL_TIM_EnableMasterSlaveMode(timx);
	LL_TIM_SetTriggerOutput(timx, LL_TIM_TRGO_ENABLE);
	LL_TIM_SetCounterMode(timx, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
	LL_TIM_SetAutoReload(timx, d0arr);
	LL_TIM_EnableIT_UPDATE(timx);
	timx->CCR1 = d0arr >> 1;
	timx->CCR2 = d0arr >> 1;
	timx->CCR3 = d0arr >> 1;
	timx->CCR4 = d0arr >> 1;
	LL_TIM_CC_EnableChannel(timx, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2 | LL_TIM_CHANNEL_CH3 | LL_TIM_CHANNEL_CH4);
	LL_TIM_EnableAllOutputs(timx);
	LL_TIM_EnableCounter(timx);
}
static void slavTIMX(TIM_TypeDef *timx, sint d0arr)
{
	LL_TIM_DisableMasterSlaveMode(timx);
	LL_TIM_SetSlaveMode(timx, LL_TIM_SLAVEMODE_TRIGGER);
	LL_TIM_SetTriggerOutput(timx, LL_TIM_TRGO_UPDATE);
	LL_TIM_SetTriggerInput(timx, LL_TIM_TS_ITR0);
	LL_TIM_SetCounterMode(timx, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
	LL_TIM_SetAutoReload(timx, d0arr);
	LL_TIM_DisableIT_UPDATE(timx);
	timx->CCR1 = d0arr >> 1;
	timx->CCR2 = d0arr >> 1;
	timx->CCR3 = d0arr >> 1;
	timx->CCR4 = d0arr >> 1;
	LL_TIM_CC_EnableChannel(timx, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2 | LL_TIM_CHANNEL_CH3 | LL_TIM_CHANNEL_CH4);
	LL_TIM_EnableAllOutputs(timx);
}
static LL_RCC_ClocksTypeDef clks;
void jakstm32_timer_initPWM3(enum pwmarr e0arr, enum polar e0polar)
{
	LL_RCC_GetSystemClocksFreq(&clks);
	jd0usec = clks.SYSCLK_Frequency / 1000 / 1000;
	uint16_t arr = 0xffff;
	if (e0arr == arr_16khz) arr = jd0usec * 32;
	//
	slavTIMX(TIM3, arr);
	//
	LL_TIM_EnableMasterSlaveMode(TIM1);
	LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_ENABLE);
	LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
	LL_TIM_SetAutoReload(TIM1, arr);	//32usec 实际上是64usec，16khz
	LL_TIM_EnableIT_UPDATE(TIM1);
	LL_TIM_OC_SetCompareCH1(TIM1, arr / 2);
	LL_TIM_OC_SetCompareCH2(TIM1, arr / 2);
	LL_TIM_OC_SetCompareCH3(TIM1, arr / 2);
	LL_TIM_OC_SetCompareCH4(TIM1, arr / 2);
	switch (e0polar)
	{
	case polar_H1L1:
		LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1N, LL_TIM_OCPOLARITY_HIGH);
		LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH2N, LL_TIM_OCPOLARITY_HIGH);
		LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH3N, LL_TIM_OCPOLARITY_HIGH);
		LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH1N, LL_TIM_OCIDLESTATE_LOW);
		LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH2N, LL_TIM_OCIDLESTATE_LOW);
		LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH3N, LL_TIM_OCIDLESTATE_LOW);
		LL_TIM_OC_SetDeadTime(TIM1, jd0usec);
		break;
	case polar_H1L0:
		LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1N, LL_TIM_OCPOLARITY_LOW);
		LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH2N, LL_TIM_OCPOLARITY_LOW);
		LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH3N, LL_TIM_OCPOLARITY_LOW);
		LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH1N, LL_TIM_OCIDLESTATE_HIGH);
		LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH2N, LL_TIM_OCIDLESTATE_HIGH);
		LL_TIM_OC_SetIdleState(TIM1, LL_TIM_CHANNEL_CH3N, LL_TIM_OCIDLESTATE_HIGH);
		LL_TIM_OC_SetDeadTime(TIM1, jd0usec);
		break;
	case polar_H1:
		LL_TIM_OC_SetDeadTime(TIM1, 0);
	}
	LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2 | LL_TIM_CHANNEL_CH3);
	LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1N | LL_TIM_CHANNEL_CH2N | LL_TIM_CHANNEL_CH3N | LL_TIM_CHANNEL_CH4);
	LL_TIM_EnableAllOutputs(TIM1);
	LL_TIM_EnableCounter(TIM1);
}
//
VOID jakstm32_timer_starPWMP()
{
	LL_GPIO_SetOutputPin(exeHEN_GPIO_Port, exeHEN_Pin);
	LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2 | LL_TIM_CHANNEL_CH3);
}
VOID jakstm32_timer_starPWMN()
{
	LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1N | LL_TIM_CHANNEL_CH2N | LL_TIM_CHANNEL_CH3N);
}
VOID jakstm32_timer_stopPWMP()
{
	LL_GPIO_ResetOutputPin(exeHEN_GPIO_Port, exeHEN_Pin);
	LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH2 | LL_TIM_CHANNEL_CH3);
}
VOID jakstm32_timer_stopPWMN()
{
	LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1N | LL_TIM_CHANNEL_CH2N | LL_TIM_CHANNEL_CH3N);
}
FASTFUNC int jakstm32_timer_d0arr()
{
	return TIM1->ARR;
}
VOID jakstm32_timer_updtPWM(int c1, int c2, int c3, int c4)
{
	TIM1->CCR1 = c1;
	TIM1->CCR2 = c2;
	TIM1->CCR3 = c3;
	TIM1->CCR4 = c4;
}
void jakstm32_timer_init(struct jakstm32_timer_config *cfg)
{
	TIM_TypeDef *timx;
	if (cfg->timerNumb == 1) timx = TIM1;
	if (cfg->timerNumb == 2) timx = TIM2;
	if (cfg->timerNumb == 3) timx = TIM3;
	if (cfg->timerNumb == 4) timx = TIM4;
	//
	LL_RCC_GetSystemClocksFreq(&clks);
	jd0usec = clks.SYSCLK_Frequency / 1000 / 1000;
	uint16_t arr = jd0usec * (int) (0.5e+6f / cfg->f0freq);
	mastTIMX(timx, arr);
}

//
