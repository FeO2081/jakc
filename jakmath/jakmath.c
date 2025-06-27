/*
 * jak_math.c
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
FASTFUNC sint W0_div(sint W0a, sint W0b)
{
	return ((uint) W0a << 16) / W0b;
}
FASTFUNC sint m0_mpy32(sint m0a, sint m0b)
{
	return 0;
}
FASTFUNC sint m0_div32(sint m0a, sint m0b)
{
	return 0;
}
FASTFUNC sint m0_mpy(sint m0a, sint m0b)
{
	return (jkreal) m0a * m0b >> 10;
}
FASTFUNC sint m0_div(sint m0a, sint m0b)
{
	return (jkreal) m0a * 1024 / m0b;
}
FASTFUNC sint u0_mpy(sint u0a, sint u0b)
{
	return (jkreal) u0a * u0b >> 20;
}
FASTFUNC sint u0_div(sint u0a, sint u0b)
{
	return (jkreal) u0a * 1024 * 1024 / u0b;
}
FASTFUNC sint64 n0_mpy64(sint64 n0a, sint64 n0b)
{
	return n0a * n0b >> 30;
}
FASTFUNC sint64 n0_div64(sint64 n0a, sint64 n0b)
{
	return (n0a << 30) / n0b;
}
FASTFUNC sint n0_mpy(sint n0a, sint n0b)
{
	return (jkreal) n0a * n0b >> 30;
}
FASTFUNC sint n0_div(sint n0a, sint n0b)
{
	return (jkreal) n0a * n0one / n0b;
}
FASTFUNC sint g0_mpy(sint g0a, sint g0b)
{
	sint64 tmp = g0a;
	return tmp * g0b >> 14;
}
FASTFUNC sint g0_div(sint g0a, sint g0b)
{
	if (g0b == 0) return 0;
	sint64 tmp = g0a;
	return tmp * 16384 / g0b;
}
FASTFUNC sint m0_fr_u0sint(sint val)
{
	return val >> 10;
}
FASTFUNC sint m0_mpy64(sint64 m0a, sint64 m0b)
{
	return m0a * m0b >> 10;
}
FASTFUNC sint a0_mpy(sint a0a, sint a0b)
{
	sint64 tmp = a0a;
	return tmp * a0b >> 12;
}
FASTFUNC sint a0_div(sint a0a, sint a0b)
{
	if (a0b == 0) return 0;
	sint64 tmp = a0a;
	return tmp * a0one / a0b;
}
FASTFUNC sint m0_safediv(sint m0a, sint m0b, sint m0mx)
{
	if (m0b == 0) return m0mx;
	return m0_div(m0a, m0b);
}
