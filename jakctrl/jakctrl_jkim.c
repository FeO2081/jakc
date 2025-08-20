/*
 * jakctrl_jkim.c
 *
 *  Created on: Jan 21, 2025
 *      Author: JAK
 */

#include "jakctrl.h"
//
#define	_10deg	(g0one/36)
#define	_15deg	(g0one/24)
#define _30deg	(g0one/12)
#define	_45deg	(g0one/8)
#define _120deg	(g0one/3)
//
void jakctrl_jkim12_step(struct jkim *jkim)
{
	jkim->g18cita[0] = (jkim->g18cita[0] + jkim->g0omega) & g0max;
	jkim->g18cita[1] = (jkim->g18cita[0] + _120deg) & g0max;
	jkim->g18cita[2] = (jkim->g18cita[1] + _120deg) & g0max;
	jkim->g18cita[3] = (jkim->g18cita[1] + _120deg) & g0max;
	jkim->g18cita[4] = (jkim->g18cita[3] + _120deg) & g0max;
	jkim->g18cita[5] = (jkim->g18cita[4] + _120deg) & g0max;
}
void jakctrl_jkim8_step(struct jkim *jkim)
{
	jkim->g18cita[0] = (jkim->g18cita[0] + jkim->g0omega) & g0max;
	jkim->g18cita[1] = (jkim->g18cita[0] + _45deg) & g0max;
	jkim->g18cita[2] = (jkim->g18cita[1] + _45deg) & g0max;
	jkim->g18cita[3] = (jkim->g18cita[2] + _45deg) & g0max;
	//
	jkim->d18cmpr[0] = jakctrl_d0_gpwm;
}
