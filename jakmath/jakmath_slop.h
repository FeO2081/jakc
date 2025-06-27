/*
 * _jak_slop.h
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH_JAKMATH_SLOP_H_
#define THIRD_PARTY_JAKMATH_JAKMATH_SLOP_H_
//
struct jakmath_slopvar
{
	sint d0rq;
	sint d0rt;
	sint d0rabs;
	sint _d0ex;
	sint d0sinc;
	sint m0ra1;
};
void slopvar(struct jakmath_slopvar *ptr, sint rq, sint rabs);
sint d0_slop_fb(const sint d0req, const sint d0act, const sint rateabs, sint *ratert);
struct jakmath_slop0
{
	sint d0rt;
	sint d0dtex;
	sint d0tmp;
	sint d0dt;
	sint d0cntr;
};
void slop0(struct jakmath_slop0 *slop, const sint d0rq, const sint rabs, sint zeromsec);
//
sint d0_slop_fb31(const sint d0req, const sint d0act, const sint rateabs, sint *m1ratert1);
sint d0_slop(const sint d0req, const sint d0act, const sint rateabs);
sint64 q0_slop(const sint64 q0req, const sint64 q0act, const sint64 rateabs);
float f0_slop(const float f0req, const float f0act, const float f0rabs);
//
#define SlopSelf(req,act,rateabs) act = d0_slop(req,act,rateabs)
//
#endif /* THIRD_PARTY_JAKMATH_JAKMATH_SLOP_H_ */
