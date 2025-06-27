/*
 * jakstm32timer.h
 *
 *  Created on: Jan 9, 2025
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKSTM32_JAKSTM32_TIMER_H_
#define THIRD_PARTY_JAKSTM32_JAKSTM32_TIMER_H_
//
#include "main.h"
#include "tim.h"
//
struct jakstm32_timer_config
{
	int timerNumb;
	float f0freq;
	int d0chnluse;
	int d0chnlpolar;
	int d0deadusec;
};
struct jakstm32_runtime
{
	int runtimex;
	int runtime;
	int runtpr;
};
void jakstm32_runtimeSTAR(struct jakstm32_runtime *ptr);
void jakstm32_runtimeOVER(struct jakstm32_runtime *ptr);
//
enum pwmarr
{
	arr_1khz = 0, //
	arr_2khz, //
	arr_3khz, //
	arr_4khz, //
	arr_8khz, //
	arr_10khz, //
	arr_16khz, //
	arr_user, //
};
enum polar
{
	polar_H1L1, polar_H1L0, polar_H1,
};
void jakstm32_timer_init(struct jakstm32_timer_config *cfg);
void jakstm32_timer_initPWM3(enum pwmarr e0arr, enum polar e0polar);
int jakstm32_timer_d0arr();
//
void jakstm32_timer_starPWMP();
void jakstm32_timer_starPWMN();
void jakstm32_timer_stopPWMP();
void jakstm32_timer_stopPWMN();
//
void jakstm32_timer_updtPWM(int c1, int c2, int c3, int c4);
void jakstm32_timer_itrrPWM();
//
#endif /* THIRD_PARTY_JAKSTM32_JAKSTM32_TIMER_H_ */
