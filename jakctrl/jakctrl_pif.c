/*
 * jakctrlpif.c
 *
 *  Created on: May 21, 2025
 *      Author: JAK
 */

#include "jakctrl.h"
//
sint u0_jakctrl_pif(struct jakctrl_pif *pif, struct jakctrl_pif_fact *fact, struct jakctrl_pif_feed *feed)
{
	if (pif == 0) return 0;
	if (fact == 0) return 0;
	if (feed == 0) return 0;
	//
	pif->u0err = pif->feed->u0ref - pif->feed->u0feb;
	pif->u0ppt = m0_mpy(pif->u0err, pif->fact->m0kp);
	pif->u0ipt = d0_sat(pif->u0ipt + m0_mpy(pif->u0ppt, pif->fact->m0ki), pif->fact->u0iptmax, pif->fact->u0iptmin);
	pif->u0fpt = m0_mpy(pif->feed->u0ref, pif->fact->m0kf);
	pif->u0out = d0_sat(pif->u0ppt + pif->u0ipt + pif->u0fpt, u0one, -u0one);
	return pif->u0out;
}
void reset_jakctrl_pif(struct jakctrl_pif *pif)
{
	pif->u0ipt = 0;
}
