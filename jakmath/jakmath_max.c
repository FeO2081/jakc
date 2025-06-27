/*
 * jakmath_max.c
 *
 *  Created on: Jan 30, 2025
 *      Author: JAK
 */

#include "jakmath.h"
//
sint d0_maxabs2(int a, int b)
{
	sint absa = d0_abs(a);
	sint absb = d0_abs(b);
	if (absa > absb) return absa;
	return absb;
}
sint d0_minabs2(int a, int b)
{
	sint absa = d0_abs(a);
	sint absb = d0_abs(b);
	if (absa > absb) return absb;
	return absa;
}
sint d0_minabs3(int a, int b, int c)
{
	return d0_minabs2(d0_minabs2(a, b), c);
}
