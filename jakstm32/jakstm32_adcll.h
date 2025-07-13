/*
 * jakstm32adcll.h
 *
 *  Created on: Jul 13, 2025
 *      Author: JAK
 */

#ifndef JAKC_JAKSTM32_JAKSTM32ADCLL_H_
#define JAKC_JAKSTM32_JAKSTM32ADCLL_H_
//
#include "jakmath/jakmath.h"
#include "adc.h"
//
void jakstm32_adcll_init(word wxsamp[], int len);
void jakstm32_adcll_samp();
//
#endif /* JAKC_JAKSTM32_JAKSTM32ADCLL_H_ */
