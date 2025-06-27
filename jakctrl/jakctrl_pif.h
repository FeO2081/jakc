/*
 * jakctrlpif.h
 *
 *  Created on: May 21, 2025
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKCTRL_JAKCTRL_PIF_H_
#define THIRD_PARTY_JAKCTRL_JAKCTRL_PIF_H_
//
#include "../jakmath/jakmath.h"
//
struct jakctrl_pif_fact
{
	sint m0kp;
	sint m0ki;
	sint m0kf;
	sint u0iptmax;
	sint u0iptmin;
};
struct jakctrl_pif_feed
{
	sint u0ref;
	sint u0feb;
};
struct jakctrl_pif
{
	struct jakctrl_pif_fact *fact;
	//
	struct jakctrl_pif_feed *feed;
	//
	sint u0err;
	sint u0out;
	sint u0ppt;
	sint u0ipt;
	sint u0fpt;
};
sint u0_jakctrl_pif(struct jakctrl_pif *pif, struct jakctrl_pif_fact *fact, struct jakctrl_pif_feed *feed);
void reset_jakctrl_pif(struct jakctrl_pif *pif);
//
#endif /* THIRD_PARTY_JAKCTRL_JAKCTRL_PIF_H_ */
