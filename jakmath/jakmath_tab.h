/*
 * _jak_tab.h
 *
 *  Created on: Nov 17, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH_JAKMATH_TAB_H_
#define THIRD_PARTY_JAKMATH_JAKMATH_TAB_H_
//
sint m0_ip1(const sint d0left, const sint d0right, const sint m0x);
sint d0_look16(const word *tab16, const sint g0idx, const sint d0dep);
sint d0_look32(const sint *tab32, const sint g0idx, const sint dep);
sint u0_ip1(const sint d0left, const sint d0right, const sint u0x);
sint d0_lookword65(const word *w65tab, const sint u0idx);
sint g0_ip1(const sint g0left, const sint g0right, const sint g0x);
sint m0_looksint(const sint *tab32, const sint m0idx, const sint dep);
sint a0_ip1(const sint d0left, const sint d0right, const sint a0x);
sint a0_lookword(const word *tabword, const sint a0idx, const sint dep);
//sint lookword(const word *tabword, const sint g0idx, const sint d0dep);
//
#endif /* THIRD_PARTY_JAKMATH_JAKMATH_TAB_H_ */
