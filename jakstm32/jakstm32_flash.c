/*
 * jakflash.c
 *
 *  Created on: Nov 7, 2024
 *      Author: JAK
 */
#include "jakstm32.h"
//
static FLASH_EraseInitTypeDef EraseInitStruct;
void thread_flash(uint32_t *para, int len)
{
	call_waitFLASH();
	if (para == 0) return;
	if (len == 0) return;
	//
	HAL_FLASH_Unlock();
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = ADDR_FLASH_PAGE_63;
	EraseInitStruct.NbPages = 1;
	uint32_t dum;
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &dum) != HAL_OK) ;
	uint32_t Address = ADDR_FLASH_PAGE_63;
	uint32_t idx = 0;
	while (Address < ADDR_FLASH_PAGE_63 + len / 4)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, para[idx]) == HAL_OK)
		{
			Address = Address + 4;
			idx++;
		}
	}
}
__weak void call_wakeFLASH()
{
}
__weak void call_waitFLASH()
{
}
