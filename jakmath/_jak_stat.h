/*
 * _jak_stat.h
 *
 *  Created on: Nov 19, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKMATH__JAK_STAT_H_
#define THIRD_PARTY_JAKMATH__JAK_STAT_H_
//
struct stat2
{
	sint d0val;
	sint d0valex;
};
//
void statrite(struct stat2 *ptr, sint d0val);
sint statread(struct stat2 *ptr);
//
#endif /* THIRD_PARTY_JAKMATH__JAK_STAT_H_ */
