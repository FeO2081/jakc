/*
 * jakstm32adcll.c
 *
 *  Created on: Jul 13, 2025
 *      Author: JAK
 */
#include "jakmath/jakmath.h"
#include "jakstm32.h"
//
void jakstm32_adcll_init(word wxsamp[], int len)
{
	__IO uint32_t backup_setting_adc_dma_transfer = 0U;
	backup_setting_adc_dma_transfer = LL_ADC_REG_GetDMATransfer(ADC1);
	LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);
	osDelay(10);
	LL_ADC_StartCalibration(ADC1);
	while (LL_ADC_IsCalibrationOnGoing(ADC1))
	{
		NOP;
	}
	LL_ADC_REG_SetDMATransfer(ADC1, backup_setting_adc_dma_transfer);
	osDelay(10);
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t) (&ADC1->DR));
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t) (wxsamp));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, len);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_ADC_Enable(ADC1);
}
VOID jakstm32_adcll_samp()
{
//	LL_ADC_REG_StopConversion(ADC1);
	LL_ADC_REG_StartConversion(ADC1);
}
