/*
 * jak_cir.c
 *
 *  Created on: Nov 16, 2024
 *      Author: JAK
 */
#include "jakmath.h"
//
FASTFUNC void push_to_cir16(struct cir16 *cir, sint val)
{
	cir->d0idx &= 16 - 1;
	cir->d16pool[cir->d0idx++] = val;
}
FASTFUNC sint d0_aver_of_cir16(struct cir16 *cir)
{
	sint64 sum = 0;
	if (cir->d0idx < 8)
	{
		for (int i = 8; i < 16; i++)
		{
			sum += cir->d16pool[i];
		}
		return sum >> 3;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			sum += cir->d16pool[i];
		}
		return sum >> 3;
	}
}
void push_to_cir64(struct cir64 *ptr, const sint dep, sint val)
{
//	if (ptr == 0) return;
//	if (dep <= 0) return;
//	if (dep > cirlen) return;
	//
	ptr->d0dep = dep;
	ptr->d0curr = val;
	//
	if (ptr->d0idx >= dep) ptr->d0idx = 0;
	ptr->d64pool[ptr->d0idx++] = val;
}
sint d0_aver_of_cir64(struct cir64 *ptr)
{
	sint64 sum = 0;
	for (int i = 0; i < ptr->d0dep; i++)
	{
		sum += ptr->d64pool[i];
	}
	return sum / ptr->d0dep;
}
void push_to_stk(struct stk *ptr, const sint dep, const word val)
{
	if (ptr->wxpool == 0) return;
	//
	ptr->d0dep = dep;
	ptr->d0new = val;
	if (ptr->d0idx >= dep) ptr->d0idx = 0;
	ptr->wxpool[ptr->d0idx++] = ptr->d0new;
	if (ptr->d0idx >= dep) ptr->d0idx = 0;
	ptr->d0old = ptr->wxpool[ptr->d0idx];
	//
	ptr->d0sum += ptr->d0new - ptr->d0old;
}
sint aver_of_stk(struct stk *ptr)
{
	return ptr->d0sum / ptr->d0dep;
}
void log_to_sinc2(struct sinc2 *ptr, const sint dep, const sint val)
{
	;
}
void push_to_stk512(struct stk512 *ptr, const sint dep, const sint val)
{
	ptr->d0dep = dep;
	ptr->d0new = val;
	if (ptr->d0idx >= dep) ptr->d0idx = 0;
	ptr->d512pool[ptr->d0idx++] = ptr->d0new;
	if (ptr->d0idx >= dep) ptr->d0idx = 0;
	ptr->d0old = ptr->d512pool[ptr->d0idx];
	//
	ptr->q0sum += ptr->d0new - ptr->d0old;
}
sint aver_of_stk512(struct stk512 *ptr)
{
	return ptr->q0sum / ptr->d0dep;
}
void zero_stk512(struct stk512 *stk)
{
	memset(stk, 0, sizeof(struct stk512));
}
//
FASTFUNC sint d0_log_to_cirword512(struct cirword512 *cir, word w0in, int d0dep)
{
	cir->d0dep = d0dep;
	cir->w512pool[cir->d0idx] = w0in;
	sint tmp = cir->d0idx + 1;
	cir->d0idx = tmp == d0dep ? 0 : tmp;
	//
	cir->d0dt = w0in - cir->w512pool[cir->d0idx];
	cir->d0sum += cir->d0dt;
	return cir->d0sum;
}
//
FASTFUNC sint d0_log_to_cirbyte512(struct cirbyte512 *cir, char c0in, int d0dep)
{
	cir->d0dep = d0dep;
	cir->c512pool[cir->d0idx] = c0in;
	sint tmp = cir->d0idx + 1;
	cir->d0idx = tmp == d0dep ? 0 : tmp;
	//
	cir->d0sum += c0in - cir->c512pool[cir->d0idx];
	return cir->d0sum;
}
