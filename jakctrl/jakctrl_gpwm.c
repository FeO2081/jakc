/*
 * jakctrlgpwm.c
 *
 *  Created on: Jun 23, 2025
 *      Author: JAK
 */

#include "jakctrl.h"
//
static sint u0citax, u0normx, a0normx, u0tmp, a0tmp;
static const word w129gsin[129] =
{
	0000, 2344, 2687, 3030, 3372, 3714, 4054, 4393, 4731, 5067,			  // 10
	5402, 5734, 6064, 6392, 6716, 7039, 7358, 7673, 7986, 8295,			  // 20
	8600, 8901, 9197, 9490, 9778, 10061, 10340, 10613, 10882, 11144,	  // 30
	11402, 11654, 11899, 12139, 12373, 12601, 12822, 13037, 13245, 13446, // 40
	13641, 13828, 14008, 14181, 14347, 14505, 14656, 14799, 14934, 15062, // 50
	15182, 15293, 15397, 15493, 15580, 15660, 15731, 15794, 15848, 15895, // 60
	15933, 15962, 15983, 15996, 16000, 15996, 15983, 15962, 15933, 15895, // 70
	15848, 15794, 15731, 15660, 15580, 15493, 15397, 15293, 15182, 15062, // 80
	14934, 14799, 14656, 14505, 14347, 14181, 14008, 13828, 13641, 13446, // 90
	13245, 13037, 12822, 12601, 12373, 12139, 11899, 11654, 11402, 11144, // 100
	10882, 10613, 10340, 10061, 9778, 9490, 9197, 8901, 8600, 8295,		  // 110
	7986, 7673, 7358, 7039, 6716, 6392, 6064, 5734, 5402, 5067,			  // 120
	4731, 4393, 4054, 3714, 3372, 3030, 2687, 2344, 0000,				  // 129
};
//
FASTFUNC sint jakctrl_d0_gpwm(sint u0cita, sint u0norm, sint d0cent)
{
	if (u0cita < u0haf)
	{
		u0citax = u0cita;
		u0normx = u0norm;
	}
	else
	{
		u0citax = u0cita - u0haf;
		u0normx = 0 - u0norm;
	}
	u0tmp = g0_mpy(a0_lookword(w129gsin, u0citax, 129), u0normx);
	return u0_mpy(u0tmp, d0cent) + d0cent;
}
static const word w129gsin8sect[129] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 800, 1600, 2400, 3200, 4000, 4800, 5600, 6400, 7200, 8000, 8800, 9600, 10400, 11200, 12000,
	12800, 13600, 14400, 15200, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000,
	16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000,
	16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000,
	16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000, 16000,
	16000, 16000, 16000, 16000, 16000, 16000, 15200, 14400, 13600, 12800, 12000, 11200, 10400, 9600, 8800, 8000, 7200, 6400,
	5600, 4800, 4000, 3200, 2400, 1600, 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				  //
};
FASTFUNC sint jakctrl_d0_gpwm8sect(sint u0cita, sint a0norm, sint d0cent)
{
	if (u0cita < u0haf)
	{
		u0citax = u0cita;
		a0normx = a0norm;
	}
	else
	{
		u0citax = u0cita - u0haf;
		a0normx = 0 - a0norm;
	}
	a0tmp = a0_lookword(w129gsin8sect, u0citax, 129);
	a0tmp = a0tmp * a0normx >> (12 + 2);	//a0_mpy(a0tmp, a0normx);
	a0tmp = a0tmp * d0cent >> 12;
	return a0tmp + d0cent;
}
FASTFUNC sint jakctrl_d0_gpwmN12(sint g0cita, sint d0cmpr)	//XX
{
#define	_30deg	(g0one/12)	// 360/12=30deg
#define _60deg	(_30deg*2)
#define _120deg	(_30deg*4)
#define	_180deg	(_30deg*6)
#define	_240deg	(_30deg*8)
	// 180DEG - 6part.
	sint base = d0cmpr >> 2;
	sint dt = d0cmpr - base;
	sint phi = _180deg - g0cita;
	if (g0cita < _60deg)
	{
		return d0cmpr;
	}
	else //
	if (g0cita < _180deg)
	{
		return base + phi * dt / _120deg;
	}
	else //
	if (g0cita < _240deg)
	{
		return -d0cmpr;
	}
	else ;
	return 0 - base - phi * dt / _120deg;
}
FASTFUNC sint jakctrl_d0_gpwmN8(sint g0cita, sint d0cmpr)
{
#define _45deg	(g0one/8)
	// 180deg-4part
	sint base = d0cmpr >> 2;
	sint dt = d0cmpr - base;
	sint phi = 0;
	sint g0tmp;
	if (g0cita > _45deg * 7)
	{
		phi = g0one - g0cita;
		return -base - phi * dt / (_180deg - _45deg);
	}
	else //
	if (g0cita > _45deg * 6)
	{
		phi = g0one - g0cita;
		return -base - phi * dt / (_180deg - _45deg);
	}
	else //
	if (g0cita > _45deg * 5)
	{
		phi = g0one - g0cita;
		return -base - phi * dt / (_180deg - _45deg);
	}
	else //
	if (g0cita > _45deg * 4)
	{
		phi = g0one - g0cita;
		return 0 - d0cmpr;
	}
	else //
	if (g0cita > _45deg * 3)
	{
		phi = _180deg - g0cita;
		return base + phi * dt / (_180deg - _45deg);
	}
	else //
	if (g0cita > _45deg * 2)
	{
		phi = _180deg - g0cita;
		return base + phi * dt / (_180deg - _45deg);
	}
	else //
	if (g0cita > _45deg * 1)
	{
		phi = _180deg - g0cita;
		return base + phi * dt / (_180deg - _45deg);
	}
	else ;
	return d0cmpr;
}
