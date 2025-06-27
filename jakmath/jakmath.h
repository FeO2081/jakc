/*
 * jak_math.h
 *
 *  Created on: Nov 16, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH_JAKMATH_H_
#define THIRD_PARTY_JAKMATH_JAKMATH_H_

//
typedef int sint;
typedef unsigned int uint;
typedef long long sint64, jkreal;
typedef short word;
typedef unsigned short WORD;
typedef unsigned char CHAR;
typedef float real;
//
#define		FASTFUNC	__attribute__((optimize("Ofast")))
#define		VOID		FASTFUNC void
//
enum
{
	efals = 0, etrue = 1,
};
#define fals 0
#ifndef true
#define true 1
#endif
//
#include "jakmath_cir.h"
#include "jakmath_abs.h"
#include "jakmath_sat.h"
#include "jakmath_tab.h"

#include "jakmath_filt.h"
#include "jakmath_sin.h"
#include "jakmath_pid.h"
#include "jakmath_root.h"
#include "jakmath_slop.h"
#include "jakmath_vect.h"
#include "jakmath_max.h"
#include "string.h"
//
enum jakable
{
	dsable = 0, enable = 1,
};
enum jakmode
{
	jakmode_norm = 0, jakmode_cali, jakmode_boot, jakmode_faut,
};
//
#define		_1Mf	(1024.0f*1024.0f)
#define		_2pai	(3.1415926f*2.0f)
#define		sqr(x)	(x*x)
//
#define		LEFT(x, y)	(x<<y)
#define		RIGT(x, y)	(x>>y)
//
#define		_1k		(1024)
#define		_2k		(2048)
#define		_4k		(4096)
#define		_8k		(8192)
#define		_16k	(16384)
#define		_32k	(32768)
#define		_64k	(65536)
//
#define		g0one	(16384)
#define		g0(X)	((jkreal)(X)*g0one)

#define		m0one	(1024)
#define		m0(X)	((jkreal)(X)*m0one)

#define		n0one	(1024*1024*1024)
#define		n0(X)	((jkreal)(X)*n0one)

#define		u0one	(1024*1024)
#define		u0haf	(1024*512)
#define		u0max	(u0one-1)
#define		u0(X)	((jkreal)(X)*u0one)

#define		a0one	(4096)
#define		a0max	(a0one-1)
#define		a0(X)	((jkreal)(X)*a0one)

#define		W0one	(65536)
#define		W0max	(W0one-1)
#define		W0(X)	((jkreal)(X)*W0one)

#define		u0f(x)	((x)*1.0e-6f)
#define		m0f(x)	((x)*1.0e-3f)

#define 	Dual	(2)
#define		Trip	(3)
#define		nullptr	(0)
#define		_1min60secs	(60)
//
sint W0_div(sint W0a, sint W0b);
sint a0_mpy(sint a0a, sint a0b);
sint a0_div(sint a0a, sint a0b);
sint g0_mpy(sint g0a, sint g0b);
sint g0_div(sint g0a, sint g0b);
sint m0_mpy(sint m0a, sint m0b);
sint m0_div(sint m0a, sint m0b);
sint u0_mpy(sint u0a, sint u0b);
sint u0_div(sint u0a, sint u0b);
sint64 n0_mpy64(sint64 n0a, sint64 n0b);
sint64 n0_div64(sint64 n0a, sint64 n0b);
sint n0_mpy(sint n0a, sint n0b);
sint n0_div(sint n0a, sint n0b);
sint m0_mpy32(sint u0a, sint u0b);
sint m0_div32(sint u0a, sint u0b);
sint m0_fr_u0sint(sint val);
sint m0_safediv(sint m0a, sint m0b, sint m0mx);
//
void jakmath_calc_dpt(struct jakmath_dpt *ptr, sint64 q0rq, sint64 q0dt_mx_abs, sint d0shift);
//
sint d0_trace(const sint d0obj, const sint d0act, const sint rate);
sint64 q0_trace(const sint64 q0obj, const sint64 q0act, const sint64 q0rate);
sint d0_slop_fb(const sint d0req, const sint d0act, const sint rateabs, sint *ratert);
//
#endif /* THIRD_PARTY_JAKMATH_JAKMATH_H_ */
