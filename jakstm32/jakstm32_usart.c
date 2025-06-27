//
#include "jakstm32.h"
#if JAKUART
//
static int d0rxlen;
static int d0txlen;
//
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART3)
	{
		d0rxlen = Size;
		call_wake485();
	}
	else //
	if (huart->Instance == USART2)
	{
	}
	else
	{
	}
}
//
void thread_232rx(UART_HandleTypeDef *huart)
{

}
void thread_232tx(UART_HandleTypeDef *huart)
{

}
static uint8_t C128rx485[128];
static uint8_t C128tx485[128];
void thread_485rxtx(UART_HandleTypeDef *huart)
{
	d0rxlen = 0;
	HAL_GPIO_WritePin(exeDE485_GPIO_Port, exeDE485_Pin, GPIO_PIN_RESET);
	HAL_UARTEx_ReceiveToIdle_DMA(huart, C128rx485, sizeof(C128rx485));
	call_wait485();
	d0txlen = call_485rxed(C128rx485, d0rxlen, C128tx485);
	if (d0txlen == 0) return;
	HAL_GPIO_WritePin(exeDE485_GPIO_Port, exeDE485_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(huart, C128tx485, d0txlen, -1L);
}
void thread_485txrx(UART_HandleTypeDef *huart)
{

}
//
__weak int call_485rxed(uint8_t *rxbuff, int rxlen, uint8_t *txbuff)
{
	return 0;
}
__weak void call_wake485()
{
}
__weak void call_wait485()
{
}
#endif
