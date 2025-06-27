/*
 * jak_tab.c
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
FASTFUNC sint g0_ip1(const sint g0left, const sint g0right, const sint g0x)
{
	//  return g0left + (g0right - g0left) * g0x / g0one;
	//sint64 q0tmp1 = d0right - d0left;
	//sint64 q0tmp2 = d0x;
	//return (sint64) d0left + q0tmp1 * q0tmp2 / g0one;
	return g0left + g0_mpy(g0right - g0left, g0x);
}
FASTFUNC sint u0_ip1(const sint d0left, const sint d0right, const sint u0x)
{
	return d0left + u0_mpy(d0right - d0left, u0x);
}
FASTFUNC sint m0_ip1(const sint d0left, const sint d0right, const sint m0x)
{
	return d0left + m0_mpy(d0right - d0left, m0x);
}
FASTFUNC sint d0_look16(const word *tab16, const sint g0idx, const sint dep)
{
	if (g0idx < 0) return tab16[0];
	if (g0idx > (dep - 1) * g0one) return tab16[dep - 1];
	int d0idx = g0idx / g0one;
	int g0idxReal = g0idx % g0one;
	int left = tab16[d0idx];
	int right = tab16[d0idx + 1];
	return g0_ip1(left, right, g0idxReal);
}

FASTFUNC sint d0_lookword65(const word *w65tab, const sint g0idx)
{
	if (g0idx < 0) return w65tab[0];
	if (g0idx > g0(64)) return w65tab[64];
	//
	sint d0idx = g0idx >> 14;
	sint g0tail = g0idx - (d0idx << 14);
	sint left = w65tab[d0idx];
	sint right = w65tab[d0idx + 1];
	//
	return g0_ip1(left, right, g0tail);
}
FASTFUNC sint d0_look32(const sint *tab32, const sint g0idx, const sint dep)
{
	if (g0idx < 0) return tab32[0];
	sint idxmx = dep - 1;
	if (g0idx > idxmx * g0one) return tab32[idxmx];
	//
	sint d0idx = g0idx >> 14;
	sint g0idxreal = g0idx - (d0idx << 14);
	sint d0left = tab32[d0idx];
	sint d0rigt = tab32[d0idx + 1];
	return g0_ip1(d0left, d0rigt, g0idxreal);
}
FASTFUNC sint m0_looksint(const sint *tabsint, const sint m0idx, const sint dep)
{
	if (m0idx < 0) return tabsint[0];
	sint idxmx = dep - 1;
	if (m0idx > idxmx * m0one) return tabsint[idxmx];
	//
	sint d0idx = m0idx >> 10;
	sint m0idxreal = m0idx - (d0idx << 10);
	sint d0left = tabsint[d0idx];
	sint d0rigt = tabsint[d0idx + 1];
	return m0_ip1(d0left, d0rigt, m0idxreal);
}
FASTFUNC sint a0_ip1(const sint d0left, const sint d0right, const sint a0x)
{
	return d0left + a0_mpy(d0right - d0left, a0x);
}
FASTFUNC sint a0_lookword(const word *tabword, const sint a0idx, const sint dep)
{
	if (a0idx < 0) return tabword[0];
	sint idxend = dep - 1;
	if (a0idx >= a0(idxend)) return tabword[idxend];
	//
	sint d0idx = a0idx >> 12;
	sint a0idxreal = a0idx - a0(d0idx);
	sint d0left = tabword[d0idx];
	sint d0rigt = tabword[d0idx + 1];
	return a0_ip1(d0left, d0rigt, a0idxreal);
}
