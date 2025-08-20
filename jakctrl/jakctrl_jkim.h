/*
 * jakctrl_jkim.h
 *
 *  Created on: Jan 21, 2025
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKCTRL_JAKCTRL_JKIM_H_
#define THIRD_PARTY_JAKCTRL_JAKCTRL_JKIM_H_
//
enum jkim_phas
{
	ephas4, ephas12, ephas24, ephas36
};
struct jkim
{
	enum jkim_phas e0phas;
	sint g0omega;
	sint g18cita[18];
	sint d18cmpr[18];
	sint d0cent;
};
//
void jakctrl_jkim12_step(struct jkim *jkim);
void jakctrl_jkim8_step(struct jkim *jkim);
//
#endif /* THIRD_PARTY_JAKCTRL_JAKCTRL_JKIM_H_ */
