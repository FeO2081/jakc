/*
 * jakhal.h
 *
 *  Created on: Sep 17, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKSTM32_JAKSTM32_H_
#define THIRD_PARTY_JAKSTM32_JAKSTM32_H_
//
#define		JAKADC		1
#define		JAKUART		0
#define		JAKFLASH	0
#define		JAKTIM		1
#define		JAKSPI		1
//
#include <main.h>
#if JAKADC
#include "jakstm32_adc.h"
#endif
#if JAKFLASH
#include "jakstm32_flash.h"
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

//
#endif /* THIRD_PARTY_JAKSTM32_JAKSTM32_H_ */
