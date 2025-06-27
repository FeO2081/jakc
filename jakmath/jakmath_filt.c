/*
 * jak_filt.c
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
sint d0_log2firsint(struct jakmath_fir *fir, sint val)
{
	fir->dnpool[fir->d0idx] = val;
	fir->d0idx = fir->d0idx == fir->d0dep - 1 ? 0 : fir->d0idx + 1;
	fir->q0sum += val - fir->dnpool[fir->d0idx];
	return fir->q0sum / fir->d0dep;
}
sint d0_log2firword(struct jakmath_fir *fir, word val)
{
	fir->wnpool[fir->d0idx] = val;
	fir->d0idx = fir->d0idx == fir->d0dep - 1 ? 0 : fir->d0idx + 1;
	fir->q0sum += val - fir->wnpool[fir->d0idx];
	return fir->q0sum / fir->d0dep;
}
//
FASTFUNC sint d0_iir(const sint d0org, const int d0new, const int d0fact)
{
	if (d0fact <= 0) return 0;
	//
	sint64 tmp = d0org;
	tmp = tmp * (d0fact - 1) + d0new;
	return tmp / d0fact;
}
FASTFUNC sint64 q0_iir(const sint64 q0org, const sint64 q0new, const sint64 q0fact)
{
	if (q0fact <= 0) return 0;
	//
	sint64 tmp = q0org * (q0fact - 1) + q0new;
	return tmp / q0fact;
}
FASTFUNC sint d0_cycle_iir(const sint d0org, const sint d0new, const int d0cycle)
{
	return d0_iir(d0org, d0new, d0cycle >> 3);
}
FASTFUNC sint64 q0_cycle_iir(const sint64 q0org, const sint64 q0new, const sint64 q0cycle)
{
	return q0_iir(q0org, q0new, q0cycle >> 3);
}
float f0_iir(const float f0org, const float f0new, float f0fact)
{
	return f0org * (1.0f - f0fact) + f0new * f0fact;
}
