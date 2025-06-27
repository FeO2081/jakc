/*
 * _jak_adc.h
 *
 *  Created on: Nov 10, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKSTM32_JAKSTM32_ADC_H_
#define THIRD_PARTY_JAKSTM32_JAKSTM32_ADC_H_
//
#include "adc.h"
//
enum flag_samp
{
	esamphalf, esampfull,
};
//
void jakstm32_adc_aver(const uint16_t *wxbuff, const int chnlcnt, const int sampdep, int *dxavrg);
int jakstm32_adc_m0ux(const int d0ad12res);
void jakstm32_adc_ject(int a4av[4]);
//
//int jakstm32_adc_d0iac();
void jakstm32_adc_init(uint16_t *adcbuff, int dep);
void jakstm32_adc_jnit();
void call_samp(enum flag_samp e0flag);
void call_hwoc(int d0iacorg);
//
#endif /* THIRD_PARTY_JAKSTM32_JAKSTM32_ADC_H_ */
