/*
 * jak_abs.c
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
FASTFUNC sint d0_sgn(sint d0val)
{
	if (d0val > 0) return +1;
	if (d0val < 0) return -1;
	return 0;
}
FASTFUNC sint64 q0_sgn(sint64 q0val)
{
	if (q0val > 0) return +1LL;
	if (q0val < 0) return -1LL;
	return 0;
}
//
FASTFUNC sint d0_abs(sint d0val)
{
	if (d0val > 0) return +d0val;
	if (d0val < 0) return -d0val;
	return 0;
}
FASTFUNC sint64 q0_abs(sint64 q0val)
{
	if (q0val > 0) return +q0val;
	if (q0val < 0) return -q0val;
	return 0;
}
//
FASTFUNC sint d0_abssgn(sint d0val, sint *d1sgn)
{
	if (d1sgn == 0)
	{
		return d0_abs(d0val);
	}
	d1sgn[0] = d0_sgn(d0val);
	return d1sgn[0] * d0val;
}
FASTFUNC sint64 q0_abssgn(sint64 q0val, sint64 *q1sgn)
{
	if (q1sgn == 0)
	{
		return q0_abs(q0val);
	}
	sint64 q0sgn = q0_sgn(q0val);
	q1sgn[0] = q0sgn;
	return q0sgn * q0val;
}
//
FASTFUNC sint r0_samsgn(sint d0val1, sint d0val2)
{
	sint64 qqe = d0val1;
	qqe *= d0val2;
	if (qqe > 0) return 1;
	return 0;
}
FASTFUNC sint r0_samsgn64(sint64 q0val1, sint64 q0val2)
{
	if (q0val1 > 0 && q0val2 > 0) return 1;
	if (q0val1 < 0 && q0val2 < 0) return 1;
	return 0;
}
FASTFUNC sint r0_oppsgn(sint d0val1, sint d0val2)
{
	sint64 qqe = d0val1;
	qqe *= d0val2;
	if (qqe < 0) return 1;
	return 0;
}
FASTFUNC sint r0_oppsgn64(sint64 q0val1, sint64 q0val2)
{
	if (q0val1 > 0 && q0val2 < 0) return 1;
	if (q0val1 < 0 && q0val2 > 0) return 1;
	return 0;
}
//
FASTFUNC sint d0_expand(const sint d0val, const sint d0expabs)
{
	if (d0val > 0) return d0val + d0expabs;
	if (d0val < 0) return d0val - d0expabs;
	return 0;
}
FASTFUNC float f0_abs(float f0val)
{
	if (f0val > 0) return +f0val;
	return -f0val;
}
