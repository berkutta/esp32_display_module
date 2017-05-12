#include "freertos/FreeRTOS.h"
#include "esp_event.h"
#include "esp_event_loop.h"

#include "esp_system.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "st7735.h"

#include <string.h>

spi_device_handle_t spi;

void st7725_add_transaction(bool rs, unsigned char data) {

}

void st7725_set_rs(spi_transaction_t *t) {
  int dc=(int)t->user;
  gpio_set_level(ST7735_RS, dc);
}

void st7735_write_command(unsigned char command)
{
  esp_err_t ret;
  spi_transaction_t trans;

  memset(&trans, 0, sizeof(trans));
  trans.length=8;
  trans.flags=SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
  trans.tx_data[0]=command;
  trans.user=(void*)0;

  ret=spi_device_transmit(spi, &trans);
  assert(ret==ESP_OK);
}

void st7735_write_data(unsigned char data)
{
  esp_err_t ret;
  spi_transaction_t trans;

  memset(&trans, 0, sizeof(trans));
  trans.length=8;
  trans.flags=SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
  trans.tx_data[0]=data;
  trans.user=(void*)1;

  ret=spi_device_transmit(spi, &trans);
  assert(ret==ESP_OK);
}

void st7735_write_data_n(unsigned char *data, unsigned char length)
{
	unsigned char ack = 0;



	unsigned char i;
	for(i = 0; i < length; i++) {

	}

}

void st7735_init(void) {
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = (1<<ST7735_RS) | (1<<ST7735_RST) | (1<<ST7735_BL);
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;
  gpio_config(&io_conf);

  esp_err_t ret;
  spi_bus_config_t buscfg={
    .miso_io_num=-1,
    .mosi_io_num=ST7735_SDA,
    .sclk_io_num=ST7735_CLK,
    .quadwp_io_num=-1,
    .quadhd_io_num=-1
  };
  spi_device_interface_config_t devcfg={
    .clock_speed_hz=10000000,
    .mode=0,
    .spics_io_num=ST7735_CS,
    .queue_size=7,
    .pre_cb=st7725_set_rs,
  };

  gpio_set_level(ST7735_BL, 1);

  ret=spi_bus_initialize(HSPI_HOST, &buscfg, 1);
  assert(ret==ESP_OK);

  ret=spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
  assert(ret==ESP_OK);

  // Init http://www.edaboard.com/thread258790.html
  gpio_set_level(ST7735_RST, 0);
  vTaskDelay(500 / portTICK_RATE_MS);
  gpio_set_level(ST7735_RST, 1);
  vTaskDelay(500 / portTICK_RATE_MS);

  printf("Start writing command\n");
  st7735_write_command(0x11);//Sleep out
  printf("Stopped writing command\n");
  vTaskDelay(120 / portTICK_RATE_MS);
  //ST7735R Frame Rate
  st7735_write_command(0xB1);
  st7735_write_data(0x01);
  st7735_write_data(0x2C);
  st7735_write_data(0x2D);
  st7735_write_command(0xB2);
  st7735_write_data(0x01);
  st7735_write_data(0x2C);
  st7735_write_data(0x2D);
  st7735_write_command(0xB3);
  st7735_write_data(0x01);
  st7735_write_data(0x2C);
  st7735_write_data(0x2D);
  st7735_write_data(0x01);
  st7735_write_data(0x2C);
  st7735_write_data(0x2D);
  //------------------------------------End ST7735R Frame Rate-----------------------------------------//
  st7735_write_command(0xB4);//Column inversion
  st7735_write_data(0x07);
  //------------------------------------ST7735R Power Sequence-----------------------------------------//
  st7735_write_command(0xC0);
  st7735_write_data(0xA2);
  st7735_write_data(0x02);
  st7735_write_data(0x84);
  st7735_write_command(0xC1);
  st7735_write_data(0xC5);
  st7735_write_command(0xC2);
  st7735_write_data(0x0A);
  st7735_write_data(0x00);
  st7735_write_command(0xC3);
  st7735_write_data(0x8A);
  st7735_write_data(0x2A);
  st7735_write_command(0xC4);
  st7735_write_data(0x8A);
  st7735_write_data(0xEE);
  //---------------------------------End ST7735R Power Sequence-------------------------------------//
  st7735_write_command(0xC5);//VCOM
  st7735_write_data(0x0E);
  st7735_write_command(0x36);//MX, MY, RGB mode
  st7735_write_data(0xC8);
  //------------------------------------ST7735R Gamma Sequence-----------------------------------------//
  st7735_write_command(0xe0);
  st7735_write_data(0x02);
  st7735_write_data(0x1c);
  st7735_write_data(0x07);
  st7735_write_data(0x12);
  st7735_write_data(0x37);
  st7735_write_data(0x32);
  st7735_write_data(0x29);
  st7735_write_data(0x2d);
  st7735_write_data(0x29);
  st7735_write_data(0x25);
  st7735_write_data(0x2b);
  st7735_write_data(0x39);
  st7735_write_data(0x00);
  st7735_write_data(0x01);
  st7735_write_data(0x03);
  st7735_write_data(0x10);
  st7735_write_command(0xe1);
  st7735_write_data(0x03);
  st7735_write_data(0x1d);
  st7735_write_data(0x07);
  st7735_write_data(0x06);
  st7735_write_data(0x2e);
  st7735_write_data(0x2c);
  st7735_write_data(0x29);
  st7735_write_data(0x2d);
  st7735_write_data(0x2e);
  st7735_write_data(0x2e);
  st7735_write_data(0x37);
  st7735_write_data(0x3f);
  st7735_write_data(0x00);
  st7735_write_data(0x00);
  st7735_write_data(0x02);
  st7735_write_data(0x10);
  st7735_write_command(0x2A);
  st7735_write_data(0x00);
  st7735_write_data(0x02);
  st7735_write_data(0x00);
  st7735_write_data(0x81);

  st7735_write_command(0x2B);
  st7735_write_data(0x00);
  st7735_write_data(0x01);
  st7735_write_data(0x00);
  st7735_write_data(0xA0);
  //------------------------------------End ST7735R Gamma Sequence-----------------------------------------//

  st7735_write_command(0x3A);
  st7735_write_data(0x05);
  //st7735_write_command(0x3A);//65k mode
  //st7735_write_data(0x05);
  st7735_write_command(0x2C);//Display on off?
  st7735_fill(0xFFFF);
  st7735_write_command(0x29);//Display on
}

void st7735_goto_x_y(uint8_t x, uint8_t y) {
		// Set column (x) address
		st7735_write_command(0x00 | (x & 0x0F));
		st7735_write_command(0x10 | ((x & 0xF0) >> 4));

		// Set page (y) address
		st7735_write_command(0xB0 | y);
}

void st7735_update() {
	uint8_t line, width;

	for(line = 0; line < 8; line++) {
		st7735_goto_x_y(0, line);

		//st7735_write_data_n(&SSD1306_buffer[SSD1306_LCDWIDTH * line], SSD1306_LCDWIDTH);
	}
}

void st7735_setarea(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2) {
    st7735_write_command(0x2A);
    st7735_write_data(x1 >> 8);
    st7735_write_data(x1 & 0xFF);
    st7735_write_data(x2 >> 8);
    st7735_write_data(x2 & 0xFF);

    st7735_write_command(0x2B);
    st7735_write_data(y1 >> 8);
    st7735_write_data(y1 & 0xFF);
    st7735_write_data(y2 >> 8);
    st7735_write_data(y2 & 0xFF);
}

void st7735_drawpixel(uint8_t x, uint8_t y, uint16_t color) {
	if( x >= ST7735_LCDWIDTH || y >= ST7735_LCDHEIGHT) {
		return;
	}

  st7735_setarea(x,y,x+1,y+1);
  st7735_write_command(0x2C);

  st7735_write_data(color >> 8);
  st7735_write_data(color & 0xFF);
}

void st7735_fill(uint16_t color) {
  int x, y;
  for(x = 0; x <= 128; x++) {
    for(y = 0; y <= 160; y++) {
      st7735_drawpixel(x, y, color);
    }
  }
}

/* end-of-file-found */
