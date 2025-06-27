/*
 * _jakstm32_uart.h
 *
 *  Created on: Nov 7, 2024
 *      Author: JAK
 */

#ifndef THIRD_PARTY_JAKSTM32_JAKSTM32_USART_H_
#define THIRD_PARTY_JAKSTM32_JAKSTM32_USART_H_
//
#include "main.h"
//
volatile struct download_cmmd
{
	uint8_t header55;
	uint8_t headerAA;
	uint8_t cmmd;
	uint8_t addr;
	//
	uint8_t spee;
	uint8_t umen;
	uint8_t sumH;
	uint8_t sumL;
};
volatile struct download_para
{
	uint8_t header55;
	uint8_t headerAA;
	uint8_t cmmd;
	uint8_t addr;
	//
	uint8_t KVEL;
	uint8_t KVEH;
	uint8_t msecL;
	uint8_t msecH;
	//
	uint8_t peakUDCL;
	uint8_t peakUDCH;
	uint8_t peakIDCL;
	uint8_t peakIDCH;
	//
	uint8_t mohmL;
	uint8_t mohmH;
	uint8_t wattL;
	uint8_t wattH;
	//
	uint8_t sumH;
	uint8_t sumL;
};
volatile struct upload_cmmd
{
	uint8_t headerAA;
	uint8_t header55;
	uint8_t stat;
	uint8_t addr;
	//
	uint8_t spee;
	uint8_t umen;
	uint8_t vbus;
	uint8_t temp;
	//
	uint8_t sumH;
	uint8_t sumL;
};
volatile struct upload_para
{
	uint8_t headerAA;
	uint8_t header55;
	uint8_t cmmd;
	uint8_t addr;
	//
	uint8_t KVEL;
	uint8_t KVEH;
	uint8_t msecL;
	uint8_t msecH;
	//
	uint8_t peakUDCL;
	uint8_t peakUDCH;
	uint8_t peakIDCL;
	uint8_t peakIDCH;
	//
	uint8_t mohmL;
	uint8_t mohmH;
	uint8_t wattL;
	uint8_t wattH;
	//
	uint8_t sumH;
	uint8_t sumL;
};
//
#ifndef exeDE485_GPIO_Port
#define exeDE485_GPIO_Port 0
#error	"485 drive pin undefined."
#endif
#ifndef exeDE485_Pin
#define exeDE485_Pin 0
#error	"485 drive pin undefined."
#endif
//
void thread_232rx(UART_HandleTypeDef *huart);
void thread_232tx(UART_HandleTypeDef *huart);
void thread_485rxtx(UART_HandleTypeDef *huart);
void thread_485txrx(UART_HandleTypeDef *huart);
//
int call_485rxed(uint8_t *rxbuff, int rxlen, uint8_t *txbuff);
void call_wake485();
void call_wait485();
//
#endif /* THIRD_PARTY_JAKSTM32_JAKSTM32_USART_H_ */
