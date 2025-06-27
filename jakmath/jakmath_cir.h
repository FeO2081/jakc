/*
 * _jak_cir.h
 *
 *  Created on: Nov 16, 2024
 *      Author: JAK
 */

#ifndef JAK_CIR_H_
#define JAK_CIR_H_
//
struct cir16
{
	struct cir16 *next;
	struct cir16 *prev;
	sint d16pool[16];
	sint d0idx;
};
void push_to_cir16(struct cir16 *cir, sint val);
sint d0_aver_of_cir16(struct cir16 *cir);
struct cir64
{
	sint d64pool[64];
	int d0idx;
	int d0dep;
	int d0curr;
};
void push_to_cir64(struct cir64 *ptr, const sint dep, sint val);
sint aver_of_cir64(struct cir64 *ptr);
struct cirword512
{
	word w512pool[512];
	int d0idx;
	int d0dep;
	int d0sum;
	int d0dt;
};
sint d0_log_to_cirword512(struct cirword512 *cir, word w0in, int d0dep);
struct cirbyte512
{
	char c512pool[512];
	int d0idx;
	int d0dep;
	int d0sum;
};
sint d0_log_to_cirbyte512(struct cirbyte512 *cir, char c0in, int d0dep);
//
struct stk
{
	word *wxpool;
	sint d0idx;
	sint d0dep;
	sint d0new;
	sint d0old;
	sint d0sum;
};
struct stk512
{
	sint d512pool[512];
	sint d0idx;
	sint d0dep;
	sint d0new;
	sint d0old;
	sint64 q0sum;
};
struct sinc2
{
	struct stk s0stk1st;
	struct stk s0stk2nd;
	sint64 q0sum;
};
void push_to_stk(struct stk *ptr, const sint dep, const word val);
sint aver_of_stk(struct stk *ptr);
void log_to_sinc2(struct sinc2 *ptr, const sint dep, const sint val);
//
void push_to_stk512(struct stk512 *ptr, const sint dep, const sint val);
sint aver_of_stk512(struct stk512 *ptr);
//
void zero_stk512(struct stk512 *stk);
//
#endif /* JAK_CIR_H_ */
