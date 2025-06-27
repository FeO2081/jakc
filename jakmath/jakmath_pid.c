/*
 * jak_dpt.c
 *
 *  Created on: Dec 15, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
void jakmath_calc_dpt(struct jakmath_dpt *ptr, sint64 q0rq, sint64 q0dt_mx_abs, sint d0shift)
{
	ptr->q0dt_rq = q0_sat((q0rq - ptr->q0rt) >> d0shift, q0dt_mx_abs, -q0dt_mx_abs);
	ptr->q0dt_ra_abs = q0dt_mx_abs >> d0shift;
	ptr->q0dt_rt = q0_slop(ptr->q0dt_rq, ptr->q0dt_rt, ptr->q0dt_ra_abs);
	ptr->q0rt = q0_slop(q0rq, ptr->q0rt, q0_abs(ptr->q0dt_rt));
}
//
sint jakmath_m0_pid(struct jakmath_pid *pid, sint m0err, sint m0kp, sint m0ki, sint m0up, sint m0down)
{
	sint m0pp1 = m0_mpy(m0kp, m0err);
	sint m0pp2 = m0_mpy(m0kp, m0pp1);
	pid->m0pp = m0_mpy(m0kp, m0pp2);
//	pid->m0ip = d0_sat(pid->m0ip + m0_mpy(m0ki, m0pp), m0up, m0down);
	//
	return 0;
}
