/*
 * jakhal.h
 *
 *  Created on: Sep 17, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKSTM32_JAKSTM32_H_
#define THIRD_PARTY_JAKSTM32_JAKSTM32_H_
//
#define		JAKADC		0
#define		JAKADCLL	1
#define		JAKUART		0
#define		JAKFLASH	0
#define		JAKTIM		1
#define		JAKSPI		0
//
#define		NOP		asm("nop")
//
#include <main.h>
#if JAKADC
#include "jakstm32_adc.h"
#endif
#if JAKFLASH
#include "jakstm32_flash.h"
#endif
#if JAKADCLL
#include "jakstm32_adcll.h"
#endif
#if JAKTIM
#include "jakstm32_timer.h"
#endif
#if JAKUART
#include "jakstm32_usart.h"
#endif
#if JAKSPI
#include "jakstm32_spi.h"
#endif
#include "stdint.h"
#include "cmsis_os.h"
//
extern int d0corehz;
extern int d0usec;
//
#endif /* THIRD_PARTY_JAKSTM32_JAKSTM32_H_ */
