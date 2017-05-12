#ifndef GRAPHIC_H
#define GRAPHIC_H

void graphic_init(void);

void graphic_show_image(uint8_t image[64][16]);

void graphic_line(int x0, int y0, int x1, int y1, uint16_t color);

void graphic_circle(int x0, int y0, int radius);

void graphic_rectangle(int x1, int y1, int x2, int y2, unsigned char fill);

void graphic_putc_5x7(unsigned char x0, unsigned char y0, char ch);

void graphic_puts_5x7(unsigned char x0, unsigned char y0, char *str);

void graphic_putc_10x8(unsigned char x0, unsigned char y0, char ch);

void graphic_puts_10x8(unsigned char x0, unsigned char y0, char *str);

void graphic_clear(void);

void graphic_update(void);

#endif
