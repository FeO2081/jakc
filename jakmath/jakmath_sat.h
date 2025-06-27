/*
 * _jak_sat.h
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH_JAKMATH_SAT_H_
#define THIRD_PARTY_JAKMATH_JAKMATH_SAT_H_
//
sint d0_sat(const sint d0input, const sint up, const sint down);
sint d0_sat0(const sint d0input, const sint up);
sint64 q0_sat(const sint64 q0input, const sint64 up, const sint64 down);
sint d0_sat_abs(const sint d0in, const sint upabs, const sint downabs);
sint d0_satH(const sint d0input, const sint d0up);
sint d0_satL(const sint d0input, const sint d0down);
float f0_sat(float f0input, float up, float down);
//
#define	d0_sat_cen(in, cenabs) d0_sat(in,cenabs,-cenabs)
//
#endif /* THIRD_PARTY_JAKMATH_JAKMATH_SAT_H_ */
