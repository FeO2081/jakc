/*
 * jakctrl_ref.cpp
 *
 *  Created on: May 26, 2025
 *      Author: JAK
 */
#include "jakctrl.h"
//
void work1ms_jakctrl_ref(struct jakctrl_ref *ref, word g0rq1, sint msecshift)
{
	if (r0_oppsgn(ref->_u0rtf, g0rq1)) //gen
	{
		ref->_g0rt1 = d0_slop(00000, ref->_g0rt1, g0one >> msecshift);

	}
	else
	{
		ref->_g0rt1 = d0_slop(g0rq1, ref->_g0rt1, g0one >> msecshift);

	}
	//
	ref->_d0tmp = d0_log_to_cirword512(&ref->_firword1, ref->_g0rt1, 512) >> 9;
	if (r0_oppsgn(ref->_firword1.d0dt, ref->_d0tmp))
	{
		ref->_d0acrt = 0;
	}
	else
	{
		ref->_d0acrt = ref->_firword1.d0dt;
	}
	ref->_u0rtf = d0_log_to_cirword512(&ref->_firword2, ref->_d0tmp, 512) >> 3;
	ref->f0rtf1 = (float) ref->_u0rtf / 1048576.0f;
	//
	ref->_d0tmp = d0_log_to_cirword512(&ref->_firword3, ref->_d0acrt, 512);
	ref->f0acf1 = (float) d0_abs(ref->_d0tmp) / (float) (1 << (14 + 9 + 9 - msecshift));
	ref->f0rtfview = ref->f0rtf1 * 16384.0f;
	ref->f0acfview = ref->f0acf1 * 16384.0f;
}
