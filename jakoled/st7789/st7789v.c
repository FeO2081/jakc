//
#include "st7789v.h"
#include "jakmath/jakmath.h"
//
int txing;
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	txing = efals;
}
//
static VOID riteSPI(uint8_t *dat, int len)
{
	LCD_CS_Clr();
	txing = etrue;
	HAL_SPI_Transmit_DMA(&hspi1, dat, len);
	while (etrue == txing)
	{
		asm("nop");
	}
	LCD_CS_Set();
}
//
VOID st7789v_Rite(uint8_t cmmd, uint8_t *buf, int datalen)
{
	uint8_t tmp = cmmd;
	LCD_DC_Clr();
	riteSPI(&tmp, 1);
	LCD_DC_Set();
	if (NULL == buf) return;
	if (0 == datalen) return;
	riteSPI(buf, datalen);
}
void st7789v_Byte(uint8_t byte)
{
	uint8_t tmp = byte;
	LCD_DC_Set();
	riteSPI(&tmp, 1);
}
void st7789v_Data(uint8_t *pix, int len)
{
	LCD_DC_Set();
	riteSPI(pix, len);
}
static uint8_t addrtmp[4];
void st7789v_Addr(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if ((USE_HORIZONTAL == 0) || (USE_HORIZONTAL == 2))
	{
//		LCD_WR_REG(0x2a); //列地址设置
//		LCD_WR_DATA(x1);
//		LCD_WR_DATA(x2);
		addrtmp[0] = x1 >> 8;
		addrtmp[1] = x1;
		addrtmp[2] = x2 >> 8;
		addrtmp[3] = x2;
		st7789v_Rite(0x2a, addrtmp, 4);
//		LCD_WR_REG(0x2b); //行地址设置
//		LCD_WR_DATA(y1);
//		LCD_WR_DATA(y2);
		addrtmp[0] = y1 >> 8;
		addrtmp[1] = y1;
		addrtmp[2] = y2 >> 8;
		addrtmp[3] = y2;
		st7789v_Rite(0x2b, addrtmp, 4);
//		LCD_WR_REG(0x2c); //储存器写
	}
	else if (USE_HORIZONTAL == 1)
	{
//		LCD_WR_REG(0x2a); //列地址设置
//		LCD_WR_DATA(x1);
//		LCD_WR_DATA(x2);
		addrtmp[0] = x1;
		addrtmp[1] = x2;
		st7789v_Rite(0x2a, addrtmp, 2);
//		LCD_WR_REG(0x2b); //行地址设置
//		LCD_WR_DATA(y1 + 80);
//		LCD_WR_DATA(y2 + 80);
		addrtmp[0] = y1 + 80;
		addrtmp[1] = y2 + 80;
		st7789v_Rite(0x2b, addrtmp, 2);
//		LCD_WR_REG(0x2c); //储存器写
	}
	else
	{
//		LCD_WR_REG(0x2a); //列地址设置
//		LCD_WR_DATA(x1 + 80);
//		LCD_WR_DATA(x2 + 80);
		addrtmp[0] = x1 + 80;
		addrtmp[1] = x2 + 80;
		st7789v_Rite(0x2a, addrtmp, 2);
//		LCD_WR_REG(0x2b); //行地址设置
//		LCD_WR_DATA(y1);
//		LCD_WR_DATA(y2);
		addrtmp[0] = y1;
		addrtmp[1] = y2;
		st7789v_Rite(0x2b, addrtmp, 2);
//		LCD_WR_REG(0x2c); //储存器写
	}
}
//
uint8_t st7789initseq[64];
void st7789v_Init(void)
{
	LCD_CS_Set();
	LCD_RST_Clr(); //复位
	osDelay(100);
	LCD_RST_Set();
	osDelay(100);

	LCD_BLK_Set(); //打开背光
	osDelay(100);

	//************* Start Initial Sequence **********//
	//LCD_WR_REG(0x11); //Sleep out
	st7789v_Rite(0x11, NULL, 0);
	osDelay(100);          //Delay 120ms
	//************* Start Initial Sequence **********//
	//LCD_WR_REG(0x36);
	if (USE_HORIZONTAL == 0)
	{
		st7789initseq[0] = 0x00;
	}
	else	//
	if (USE_HORIZONTAL == 1)
	{
		st7789initseq[0] = 0xc0;
	}
	else	//
	if (USE_HORIZONTAL == 2)
	{
		st7789initseq[0] = 0x70;
	}
	else
	{
		st7789initseq[0] = 0xa0;
	}
	st7789v_Rite(0x36, st7789initseq, 1);

//	LCD_WR_REG(0x3A);
//	LCD_WR_DATA8(0x05);
	st7789initseq[0] = 0x55;
	st7789v_Rite(0x3a, st7789initseq, 1);
//
	st7789initseq[0] = 0x00;
	st7789initseq[1] = 0xf8;
	st7789v_Rite(0xb0, st7789initseq, 2);

//	LCD_WR_REG(0xB2);
//	LCD_WR_DATA8(0x0C);
//	LCD_WR_DATA8(0x0C);
//	LCD_WR_DATA8(0x00);
//	LCD_WR_DATA8(0x33);
//	LCD_WR_DATA8(0x33);
	st7789initseq[0] = 0x0c;
	st7789initseq[1] = 0x0c;
	st7789initseq[2] = 0x00;
	st7789initseq[3] = 0x33;
	st7789initseq[4] = 0x33;
	st7789v_Rite(0xb2, st7789initseq, 5);

//	LCD_WR_REG(0xB7);
//	LCD_WR_DATA8(0x35);
	st7789initseq[0] = 0x35;
	st7789v_Rite(0xb7, st7789initseq, 1);

//	LCD_WR_REG(0xBB);
//	LCD_WR_DATA8(0x32); //Vcom=1.35V
	st7789initseq[0] = 0x32;
	st7789v_Rite(0xbb, st7789initseq, 1);

//	LCD_WR_REG(0xC2);
//	LCD_WR_DATA8(0x01);
	st7789initseq[0] = 0x01;
	st7789v_Rite(0xC2, st7789initseq, 1);
//
//	LCD_WR_REG(0xC3);
//	LCD_WR_DATA8(0x15); //GVDD=4.8V  颜色深度
	st7789initseq[0] = 0x15;
	st7789v_Rite(0xC3, st7789initseq, 1);
//
//	LCD_WR_REG(0xC4);
//	LCD_WR_DATA8(0x20); //VDV, 0x20:0v
	st7789initseq[0] = 0x20;
	st7789v_Rite(0xC4, st7789initseq, 1);
//
//	LCD_WR_REG(0xC6);
//	LCD_WR_DATA8(0x0F); //0x0F:60Hz
	st7789initseq[0] = 0x0F;
	st7789v_Rite(0xC6, st7789initseq, 1);
//
//	LCD_WR_REG(0xD0);
//	LCD_WR_DATA8(0xA4);
//	LCD_WR_DATA8(0xA1);
	st7789initseq[0] = 0xA4;
	st7789initseq[1] = 0xA1;
	st7789v_Rite(0xd0, st7789initseq, 2);
//
//	LCD_WR_REG(0xE0);
//	LCD_WR_DATA8(0xD0);
//	LCD_WR_DATA8(0x08);
//	LCD_WR_DATA8(0x0E);
//	LCD_WR_DATA8(0x09);
//	LCD_WR_DATA8(0x09);
//	LCD_WR_DATA8(0x05);
//	LCD_WR_DATA8(0x31);
//	LCD_WR_DATA8(0x33);
//	LCD_WR_DATA8(0x48);
//	LCD_WR_DATA8(0x17);
//	LCD_WR_DATA8(0x14);
//	LCD_WR_DATA8(0x15);
//	LCD_WR_DATA8(0x31);
//	LCD_WR_DATA8(0x34);
	st7789initseq[0] = 0xd0;
	st7789initseq[1] = 0x08;
	st7789initseq[2] = 0x0e;
	st7789initseq[3] = 0x09;
	st7789initseq[4] = 0x09;
	st7789initseq[5] = 0x05;
	st7789initseq[6] = 0x31;
	st7789initseq[7] = 0x33;
	st7789initseq[8] = 0x48;
	st7789initseq[9] = 0x17;
	st7789initseq[10] = 0x14;
	st7789initseq[11] = 0x15;
	st7789initseq[12] = 0x31;
	st7789initseq[13] = 0x34;
	st7789v_Rite(0xe0, st7789initseq, 14);
//
//	LCD_WR_REG(0xE1);
//	LCD_WR_DATA8(0xD0);
//	LCD_WR_DATA8(0x08);
//	LCD_WR_DATA8(0x0E);
//	LCD_WR_DATA8(0x09);
//	LCD_WR_DATA8(0x09);
//	LCD_WR_DATA8(0x15);
//	LCD_WR_DATA8(0x31);
//	LCD_WR_DATA8(0x33);
//	LCD_WR_DATA8(0x48);
//	LCD_WR_DATA8(0x17);
//	LCD_WR_DATA8(0x14);
//	LCD_WR_DATA8(0x15);
//	LCD_WR_DATA8(0x31);
//	LCD_WR_DATA8(0x34);
	st7789initseq[0] = 0xd0;
	st7789initseq[1] = 0x08;
	st7789initseq[2] = 0x0e;
	st7789initseq[3] = 0x09;
	st7789initseq[4] = 0x09;
	st7789initseq[5] = 0x15;
	st7789initseq[6] = 0x31;
	st7789initseq[7] = 0x33;
	st7789initseq[8] = 0x48;
	st7789initseq[9] = 0x17;
	st7789initseq[10] = 0x14;
	st7789initseq[11] = 0x15;
	st7789initseq[12] = 0x31;
	st7789initseq[13] = 0x34;
	st7789v_Rite(0xe1, st7789initseq, 14);
//
//	LCD_WR_REG(0x21);
//	LCD_WR_REG(0x29);
	st7789v_Rite(0x21, NULL, 0);
	st7789v_Rite(0x29, NULL, 0);
}
//
void st7789v_Fill(int x0, int y0, int x1, int y1, int color)
{
	uint8_t pix[2];
	pix[0] = color;
	pix[1] = color >> 8;
	st7789v_Addr(x0, y0, x1 - 1, y1 - 1);
	st7789v_Rite(0x2c, NULL, 0);
	for (int i = 0; i < (x1 - x0) * (y1 - y0); i++)
	{
		st7789v_Data(pix, 2);
	}
}
VOID st7789v_Draw(uint8_t *buf, int x, int y, int w, int h)
{
	st7789v_Addr(x, y, x + w - 1, y + h - 1);
	int len = w * h;
	if (len > 65533) return;
	st7789v_Rite(0x2c, buf, len * 2);
}
