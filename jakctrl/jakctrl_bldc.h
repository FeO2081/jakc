/*
 * jakctrl_bldc.h
 *
 *  Created on: May 21, 2025
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKCTRL_JAKCTRL_BLDC_H_
#define THIRD_PARTY_JAKCTRL_JAKCTRL_BLDC_H_
//
enum jakonoff
{
	off, onn
};
struct jakctrl_bldc_svpwm
{
	WORD W0cmprHalf;
	WORD W0cmprA;
	WORD W0cmprB;
	WORD W0cmprC;
	//
	sint u0cita;
	sint d0tmp1;
	sint d0tmp2;
	sint d0tmp3;
};
struct jakctrl_bldc_para
{
	float f0kve;
	float f0wtpk;
	float f0uzpk;
	float f0rs;
	float f0ls;
	float f0msec2hzpk;
	float f0msec2tepk;
	sint m0iz4096;
	sint m0iz0;
	sint m0uz4096;
};
struct jakctrl_bldc_feed
{
	float f0uz;
	float f0iz;
	float f0tm;
	sint m0hz1;
	sint d0izavr;
	sint d0uzavr;
	sint d0tmavr;

};
struct jakctrl_bldc
{
	struct jakctrl_bldc_para *para;
	struct jakctrl_bldc_feed *feed;
	struct jakctrl_ref s0ref;
	struct cir64 cir64izorg;
	struct cir64 cir64uzorg;
	struct cir64 cir64tmorg;
	//
	struct
	{
		float f0omega;
		float f0uoemf;
		sint u0omega1;
		sint u0uoemf1;
		sint u0uoidl1;
	} hz;
	struct
	{
		sint u0uoacc1;
		sint u0uoizf1;
		sint u0dummy1;
	} te;
	struct
	{
		sint u0uoexe1;
		sint u0uoext1;
		sint shift;
	} ff;
	struct jakctrl_bldc_svpwm pwm;
	struct
	{
		sint u0omeg;
		sint u0uexe;
	} fast;
	struct
	{
		float f0hz;
		float f0omega;
		float f0uzemf;
		float f0uoacc;
		float f0uoidl;
		float f0uoizf;
	} pk;
	struct
	{
		float f0hzrt;
		float f0uoext;
		float f0uoexe;
		float f0uoacc;
		float f0uoizf;
		float f0uoidl;
	} view;
	float f0uzf;
	float f0izf;
	float f0ite;
	float f0idz;
	float f0idzf;
	float f0xs;
	float f0zs;
	sint d0star;
	sint d0starfact;
};
void itrr_jakctrl_bldc(struct jakctrl_bldc *bldc, sint d0arr, sint d0izorg, sint d0udcorg, sint d0tmorg);
void work_jakctrl_bldc(struct jakctrl_bldc *bldc, struct jakctrl_bldc_para *para, struct jakctrl_bldc_feed *feed);
void PWMONOFF(enum jakonoff e0onoff);
//
#endif /* THIRD_PARTY_JAKCTRL_JAKCTRL_BLDC_H_ */
