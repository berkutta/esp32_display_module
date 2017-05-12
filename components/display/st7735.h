#ifndef ST7735_H
#define ST7735_H

#include "driver/spi_master.h"

//Defines for later use
#define ST7735_LCDWIDTH            128
#define ST7735_LCDHEIGHT           160

#define ST7735_CS 16
#define ST7735_CLK 17
#define ST7735_SDA 5
#define ST7735_RS 18
#define ST7735_RST 19
#define ST7735_BL 21

void st7725_add_transaction(bool rs, unsigned char data);

void st7725_set_rs(spi_transaction_t *t);

void st7735_write_command(unsigned char command);

void st7735_write_data(unsigned char data);

void st7735_write_data_n(unsigned char *data, unsigned char length);

void st7735_init(void);

void st7735_goto_x_y(uint8_t x, uint8_t y);

void st7735_update();

void st7735_setarea(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);

void st7735_drawpixel(uint8_t x, uint8_t y, uint16_t color);

void st7735_fill(uint16_t color);

#endif
