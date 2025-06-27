/*
 * jak_slop.c
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
FASTFUNC sint d0_slop(const sint d0req, const sint d0act, const sint rateabs)
{
	sint tmp = d0req - d0act;
	if (tmp > +rateabs) return d0act + rateabs;
	if (tmp < -rateabs) return d0act - rateabs;
	return d0req;
}
FASTFUNC sint64 q0_slop(const sint64 q0req, const sint64 q0act, const sint64 rateabs)
{
	sint64 tmp = q0req - q0act;
	if (tmp > +rateabs) return q0act + rateabs;
	if (tmp < -rateabs) return q0act - rateabs;
	return q0req;
}
//	across=ax
static sint r0_ax(const sint d0obj, const sint d0act, const sint d0expect)
{
	if (d0act == d0obj) return etrue;
	if (d0expect == d0obj) return etrue;
	return r0_samsgn(d0expect - d0obj, d0obj - d0act);
}
sint d0_trace(const sint d0obj, const sint d0act, const sint rate)
{
	sint d0exp = d0act + rate;
	if (r0_ax(d0obj, d0act, d0exp))
	{
		return d0obj;
	}
	return d0exp;
}
static sint r0_ax64(const sint64 q0ob, const sint64 q0rt, const sint64 q0nx)
{
	if (q0rt == q0ob) return etrue;
	if (q0nx == q0ob) return etrue;
	return r0_samsgn64(q0nx - q0ob, q0ob - q0rt);
}
sint64 q0_trace(const sint64 q0obj, const sint64 q0act, const sint64 q0rate)
{
	sint64 q0nx = q0act + q0rate;
	if (r0_ax64(q0obj, q0act, q0nx)) return q0obj;
	return q0nx;
}
sint d0_slop_fb(const sint d0req, const sint d0act, const sint rateabs, sint *ratert)
{
	sint tmp = d0req - d0act;
	if (tmp > +rateabs)
	{
		*ratert = +rateabs;
		return d0act + rateabs;
	}
	if (tmp < -rateabs)
	{
		*ratert = -rateabs;
		return d0act - rateabs;
	}
	*ratert = 0; //tmp;
	return d0req;
}
sint d0_slop_fb31(const sint d0req, const sint d0act, const sint rateabs, sint *m1ratert1)
{
	sint tmp = d0req - d0act;
	m1ratert1[0] = d0_sat(m0_div(tmp, rateabs), m0one, -m0one);
	if (tmp > +rateabs)
	{
		return d0act + rateabs;
	}
	if (tmp < -rateabs)
	{
		return d0act - rateabs;
	}
	return d0req;
}
void slopvar(struct jakmath_slopvar *ptr, sint rq, sint d0rabs)
{
//	ptr->d0rq = d0_sat(rq, mx_abs, -mx_abs);
//	ptr->d0rabs = mx_abs / step;
//	ptr->d0rt = d0_slop_fb31(ptr->d0rq, ptr->d0rt, ptr->d0rabs, &ptr->m0ra1);
}
void slop0(struct jakmath_slop0 *slop, const sint d0rq, const sint rabs, sint zeromsec)
{
	slop->d0tmp = d0_slop_fb(d0rq, slop->d0rt, rabs, &slop->d0dt);
	if (r0_oppsgn(slop->d0dt, slop->d0dtex)) slop->d0cntr++;
	if (slop->d0cntr == zeromsec + 2) slop->d0cntr = 0;
	if (slop->d0cntr == 0)
	{
		slop->d0rt = slop->d0tmp;
		slop->d0dtex = slop->d0dt;
	}
}
float f0_slop(const float f0req, const float f0act, const float f0rabs)
{
	float tmp = f0req - f0act;
	if (tmp > +f0rabs) return f0act + f0rabs;
	if (tmp < -f0rabs) return f0act - f0rabs;
	return f0req;
}
