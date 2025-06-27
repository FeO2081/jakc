/*
 * _jak_filt.h
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH_JAKMATH_FILT_H_
#define THIRD_PARTY_JAKMATH_JAKMATH_FILT_H_
//
struct jakmath_fir
{
	sint *dnpool;
	word *wnpool;
	sint d0idx;
	sint d0dep;
	sint64 q0sum;
};
sint d0_log2firsint(struct jakmath_fir *fir, sint val);
sint d0_log2firword(struct jakmath_fir *fir, word val);
#define	INIT_FIR_WORD(name,dep)	static word name##_wnpool[dep]; struct jakmath_fir name={.wnpool=name##_wnpool,.d0dep = dep}
#define	INIT_FIR_SINT(name,dep)	static sint name##_dnpool[dep]; struct jakmath_fir name={.dnpool=name##_dnpool,.d0dep = dep}
//
sint d0_expand(const sint d0val, const sint d0expabs);
sint d0_iir(const sint d0org, const int d0new, const int d0fact);
sint64 q0_iir(const sint64 q0org, const sint64 q0new, const sint64 q0fact);
sint d0_cycle_iir(const sint d0org, const sint d0new, const int d0cycle);
sint64 q0_cycle_iir(const sint64 q0org, const sint64 q0new, const sint64 q0cycle);
float f0_iir(const float f0org, const float f0new, float f0fact);
//
#define IIR32(ORG,NEW,FACT) ORG = d0_iir(ORG,NEW,FACT)
//
#endif /* THIRD_PARTY_JAKMATH_JAKMATH_FILT_H_ */
