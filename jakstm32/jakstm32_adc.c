/*
 * jakhal_adc.h
 *
 *  Created on: Sep 17, 2024
 *      Author: JAK
 */
#include "jakstm32.h"
#include "../jakmath/jakmath.h"
//
FASTFUNC void jakstm32_adc_aver(const uint16_t *wxbuff, const int chnlcnt, const int sampdep, int *dxavrg)
{
	if (wxbuff == 0) return;
	if (dxavrg == 0) return;
	if (sampdep == 0) return;
	if (chnlcnt == 0) return;
	//
	int tmp1;
	//
	for (int chnl = 0; chnl < chnlcnt; chnl++)
	{
		tmp1 = 0;
		for (int i = 0; i < sampdep; i++)
		{
			tmp1 += wxbuff[chnlcnt * i + chnl];
		}
		dxavrg[chnl] = tmp1 / sampdep;
	}
}
sint jakstm32_adc_m0ux(const int d0ad12res)
{
	int64_t tmp = d0ad12res;
	return tmp * 3300ll / 4096;
}
//
void jakstm32_adc_init(uint16_t *adcbuff, int dep)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
//	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcbuff, dep);
}
void jakstm32_adc_jnit()
{
	HAL_ADCEx_Calibration_Start(&hadc1);
}
VOID jakstm32_adc_ject(sint a4av[4])
{
//	LL_ADC_INJ_StopConversionExtTrig(ADC1);
//	a4av[0] = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_1);
//	a4av[1] = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_2);
//	a4av[2] = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_3);
//	a4av[3] = LL_ADC_INJ_ReadConversionData12(ADC1, LL_ADC_INJ_RANK_4);
//	LL_ADC_INJ_StartConversionExtTrig(ADC1, LL_ADC_INJ_TRIG_EXT_RISING);
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	call_samp(esampfull);
}
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	call_samp(esamphalf);
}
__weak void call_samp(enum flag_samp e0flag)
{
}
__weak void call_hwoc(int d0iacorg)
{
}
