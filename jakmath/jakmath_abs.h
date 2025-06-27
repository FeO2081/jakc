/*
 * _jak_abs.h
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH_JAKMATH_ABS_H_
#define THIRD_PARTY_JAKMATH_JAKMATH_ABS_H_
//
sint d0_sgn(sint d0val);
sint64 q0_sgn(sint64 q0val);

sint d0_abs(sint d0val);
sint64 q0_abs(sint64 q0val);
float f0_abs(float f0val);

sint d0_abssgn(sint d0val, sint *d1sgn);
sint64 q0_abssgn(sint64 q0val, sint64 *q1sgn);

sint r0_samsgn(sint d0val1, sint d0val2);
sint r0_samsgn64(sint64 q0val1, sint64 q0val2);

sint r0_oppsgn(sint d0val1, sint d0val2);
sint r0_oppsgn64(sint64 q0val1, sint64 q0val2);

sint d0_expand(const sint d0val, const sint d0expabs);
//
#endif /* THIRD_PARTY_JAKMATH_JAKMATH_ABS_H_ */
