/*
 * jak_sat.c
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
FASTFUNC sint d0_sat(const sint d0input, const sint up, const sint down)
{
	if (d0input > up) return up;
	if (d0input < down) return down;
	return d0input;
}
FASTFUNC sint d0_sat0(const sint d0input, const sint up)
{
	if (d0input > up) return up;
	if (d0input < 0) return 0;
	return d0input;
}

FASTFUNC sint64 q0_sat(const sint64 q0input, const sint64 up, const sint64 down)
{
	if (q0input > up) return up;
	if (q0input < down) return down;
	return q0input;
}
FASTFUNC sint d0_sat_abs(const sint d0in, const sint upabs, const sint downabs)
{
	if (d0in < 0) return d0_sat(-d0in, upabs, downabs);
	return d0_sat(d0in, upabs, downabs);
}
FASTFUNC sint d0_satH(const sint d0input, const sint d0up)
{
	if (d0input > d0up) return d0up;
	return d0input;
}
FASTFUNC sint d0_satL(const sint d0input, const sint d0down)
{
	if (d0input < d0down) return d0down;
	return d0input;
}
FASTFUNC float f0_sat(float f0input, float up, float down)
{
	if (f0input > up) return up;
	if (f0input < down) return down;
	return f0input;
}
