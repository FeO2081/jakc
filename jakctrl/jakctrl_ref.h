/*
 * jakctrl_ref.h
 *
 *  Created on: May 26, 2025
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKCTRL_JAKCTRL_REF_H_
#define THIRD_PARTY_JAKCTRL_JAKCTRL_REF_H_
//
struct jakctrl_ref
{
	struct cirword512 _firword1;
	struct cirword512 _firword2;
	struct cirword512 _firword3;
	sint _g0rt1;
	sint _d0tmp;
	sint _u0rtf;
	sint _d0acrt;
	float f0rtf1;
	float f0acf1;
	float f0acfview;
	float f0rtfview;
};
//
void work1ms_jakctrl_ref(struct jakctrl_ref *ref, word g0rq1, sint msecshift);
//
#endif /* THIRD_PARTY_JAKCTRL_JAKCTRL_REF_H_ */
