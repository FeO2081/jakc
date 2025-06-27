/*
 * _jak_dpt.h
 *
 *  Created on: Dec 15, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH_JAKMATH_PID_H_
#define THIRD_PARTY_JAKMATH_JAKMATH_PID_H_
//
struct jakmath_dpt
{
	sint64 q0rt;
	sint64 q0dt_rq;
	sint64 q0dt_rt;
	sint64 q0dt_ra_abs;
};
struct jakmath_pid
{
	sint m0kd;
	//
	sint m0ip;
	sint m0pp;
	//
	sint m0rf;
	sint m0fb;
};
struct jakmath_mipt
{
	sint m0ki;
	sint m0ip;
	sint m0mx;
	sint m0mi;
};
//
#endif /* THIRD_PARTY_JAKMATH_JAKMATH_PID_H_ */
