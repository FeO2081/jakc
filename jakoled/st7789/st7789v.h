/*
 * st7789v.h
 *
 *  Created on: Jun 14, 2025
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKOLED_ST7789_ST7789V_H_
#define THIRD_PARTY_JAKOLED_ST7789_ST7789V_H_
//
#include "stdint.h"
#include "cmsis_os.h"
#include "main.h"
#include "spi.h"
//
extern int txing;
//
#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏
#define LCD_W 240
#define LCD_H 240
//
#define LCD_RST_Clr()	LL_GPIO_ResetOutputPin(LCDRS_GPIO_Port, LCDRS_Pin)
#define LCD_RST_Set()	LL_GPIO_SetOutputPin(LCDRS_GPIO_Port, LCDRS_Pin)

#define LCD_DC_Clr()	LL_GPIO_ResetOutputPin(LCDDC_GPIO_Port, LCDDC_Pin)
#define LCD_DC_Set()	LL_GPIO_SetOutputPin(LCDDC_GPIO_Port, LCDDC_Pin)

#define LCD_CS_Clr()	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin)
#define LCD_CS_Set()	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin)

#define LCD_BLK_Clr()	LL_TIM_OC_SetCompareCH1(TIM1, 1)
#define LCD_BLK_Set()	LL_TIM_OC_SetCompareCH1(TIM1, LL_TIM_GetAutoReload(TIM1) - 1)
//
void st7789v_Rite(uint8_t cmmd, uint8_t *buf, int datalen);
void st7789v_Addr(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); //设置坐标函数
void st7789v_Init(void); //LCD初始化
void st7789v_Fill(int x0, int y0, int x1, int y1, int color);
void st7789v_Draw(uint8_t *buf, int x, int y, int w, int h);
//
#endif /* THIRD_PARTY_JAKOLED_ST7789_ST7789V_H_ */
