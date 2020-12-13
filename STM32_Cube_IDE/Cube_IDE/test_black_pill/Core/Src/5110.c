/*
 * 5110.c
 *
 *  Created on: Jul 26, 2020
 *      Author: Dat UTC
 */
#include "5110.h"
#include "main.h"


void setup_LCD_GPIOs()
{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,1); // Back Light
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1); // CE(SS)
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1); // D/C
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0); // Reset
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0); // MOSI
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0); // SCLK
			HAL_Delay(10);
}


void PCD8544_write(unsigned char type, unsigned char value)
{
     unsigned char s = 0x08;

     if(type != 0)
     {
          // GPIOB_pin_high(DC_pin);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);
     }
     else
     {
           //GPIOB_pin_low(DC_pin);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
     }

          //GPIOB_pin_low(CE_pin);
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);

     while(s > 0)
     {
               //GPIOB_pin_low(SCK_pin);
			     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);

         if((value & 0x80) == 0)
         {
                   //GPIOB_pin_low(SDO_pin);
					 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
         }
         else
         {
                    //GPIOB_pin_high(SDO_pin);
					  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
         }

         value <<= 1;
               //GPIOB_pin_high(SCK_pin);
				 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
         s--;
     };

       //GPIOB_pin_high(CE_pin);
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
}


void PCD8544_reset()
{
//     GPIOB_pin_low(RST_pin);
//     delay_us(100);
//     GPIOB_pin_high(RST_pin);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
				HAL_Delay(100);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,1);
}


void PCD8544_init()
{
    setup_LCD_GPIOs();
    PCD8544_reset();
    PCD8544_write(CMD, (PCD8544_extended_instruction | PCD8544_function_set));
    PCD8544_write(CMD, (PCD8544_set_bias | 0x02));
    PCD8544_set_contrast(0x39);
    PCD8544_write(CMD, PCD8544_set_temp);
    PCD8544_write(CMD, (PCD8544_display_normal | PCD8544_display_control));
    PCD8544_write(CMD, PCD8544_function_set);
    PCD8544_write(CMD, PCD8544_display_all_on);
    PCD8544_write(CMD, PCD8544_display_normal);
    PCD8544_clear_buffer(OFF);
}


void PCD8544_backlight_state(unsigned char value)
{
     if(value != 0)
     {
         //GPIOB_pin_low(BL_pin);
			  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,0);
     }
     else
     {
        // GPIOB_pin_high(BL_pin);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,1);
     }
}


void PCD8544_set_contrast(unsigned char value)
{
    if(value >= 0x7F)
    {
       value = 0x7F;
    }

    PCD8544_write(CMD, (PCD8544_extended_instruction | PCD8544_function_set));
    PCD8544_write(CMD, (PCD8544_set_VOP | value));
    PCD8544_write(CMD, PCD8544_function_set);
}


void PCD8544_set_cursor(unsigned char x_pos, unsigned char y_pos)
{
    PCD8544_write(CMD, (PCD8544_set_X_addr | x_pos));
    PCD8544_write(CMD, (PCD8544_set_Y_addr | y_pos));
}


void PCD8544_print_char(unsigned char ch, unsigned char colour)
{
     unsigned char s = 0;
     unsigned char chr = 0;

     for(s = 0; s <= 4; s++)
     {
           chr = font[(ch - 0x20)][s];
           if(colour == BLACK)
           {
               chr = ~chr;
           }
           PCD8544_write(DAT, chr);
     }
}


void PCD8544_print_custom_char(unsigned char *map)
{
    unsigned char s = 0;

    for(s = 0; s <= 4; s++)
    {
        PCD8544_write(DAT, *map++);
    }
}


void PCD8544_fill(unsigned char bufr)
{
    unsigned int s = 0;

    PCD8544_set_cursor(0, 0);

    for(s = 0; s < buffer_size; s++)
    {
        PCD8544_write(DAT, bufr);
    }
}


void PCD8544_clear_buffer(unsigned char colour)
{
    unsigned char x_pos = 0;
    unsigned char y_pos = 0;

    for(x_pos; x_pos < X_max; x_pos++)
    {
        for(y_pos; y_pos < Rows; y_pos++)
        {
            PCD8544_buffer[x_pos][y_pos] = colour;
        }
    }
}


void PCD8544_clear_screen(unsigned char colour)
{
    unsigned char x_pos = 0;
    unsigned char y_pos = 0;

    for(y_pos = 0; y_pos < Rows; y_pos++)
    {
        for(x_pos = 0; x_pos < X_max; x_pos++)
        {
            PCD8544_print_string(x_pos, y_pos, " ", colour);
        }
    }
}

void PCD8544_print_string(unsigned char x_pos, unsigned char y_pos, unsigned char *ch, unsigned char colour)
{
    PCD8544_set_cursor(x_pos, y_pos);

    do
    {
       PCD8544_print_char(*ch++, colour);
    }while((*ch >= 0x20) && (*ch <= 0x7F));
}


void print_chr(unsigned char x_pos, unsigned char y_pos, signed int value, unsigned char colour)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        PCD8544_set_cursor(x_pos, y_pos);
        PCD8544_print_char(0x2D, colour);
        value = -value;
    }
    else
    {
        PCD8544_set_cursor(x_pos, y_pos);
        PCD8544_print_char(0x20, colour);
    }

     if((value > 99) && (value <= 999))
     {
         ch = (value / 100);
         PCD8544_set_cursor((x_pos + 6), y_pos);
         PCD8544_print_char((48 + ch), colour);

         ch = ((value % 100) / 10);
         PCD8544_set_cursor((x_pos + 12), y_pos);
         PCD8544_print_char((48 + ch), colour);

         ch = (value % 10);
         PCD8544_set_cursor((x_pos + 18), y_pos);
         PCD8544_print_char((48 + ch), colour);
     }
     else if((value > 9) && (value <= 99))
     {
         ch = ((value % 100) / 10);
         PCD8544_set_cursor((x_pos + 6), y_pos);
         PCD8544_print_char((48 + ch), colour);

         ch = (value % 10);
         PCD8544_set_cursor((x_pos + 12), y_pos);
         PCD8544_print_char((48 + ch), colour);

         PCD8544_set_cursor((x_pos + 18), y_pos);
         PCD8544_print_char(0x20, colour);
     }
     else if((value >= 0) && (value <= 9))
     {
         ch = (value % 10);
         PCD8544_set_cursor((x_pos + 6), y_pos);
         PCD8544_print_char((48 + ch), colour);

         PCD8544_set_cursor((x_pos + 12), y_pos);
         PCD8544_print_char(0x20, colour);

         PCD8544_set_cursor((x_pos + 18), y_pos);
         PCD8544_print_char(0x20, colour);
     }
}


void print_int(unsigned char x_pos, unsigned char y_pos, signed long value, unsigned char colour)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        PCD8544_set_cursor(x_pos, y_pos);
        PCD8544_print_char(0x2D, colour);
        value = -value;
    }
    else
    {
        PCD8544_set_cursor(x_pos, y_pos);
        PCD8544_print_char(0x20, colour);
    }

    if(value > 9999)
    {
        ch = (value / 10000);
        PCD8544_set_cursor((x_pos + 6), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = ((value % 10000)/ 1000);
        PCD8544_set_cursor((x_pos + 12), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = ((value % 1000) / 100);
        PCD8544_set_cursor((x_pos + 18), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = ((value % 100) / 10);
        PCD8544_set_cursor((x_pos + 24), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = (value % 10);
        PCD8544_set_cursor((x_pos + 30), y_pos);
        PCD8544_print_char((48 + ch), colour);
    }

    else if((value > 999) && (value <= 9999))
    {
        ch = ((value % 10000)/ 1000);
        PCD8544_set_cursor((x_pos + 6), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = ((value % 1000) / 100);
        PCD8544_set_cursor((x_pos + 12), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = ((value % 100) / 10);
        PCD8544_set_cursor((x_pos + 18), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = (value % 10);
        PCD8544_set_cursor((x_pos + 24), y_pos);
        PCD8544_print_char((48 + ch), colour);

        PCD8544_set_cursor((x_pos + 30), y_pos);
        PCD8544_print_char(0x20, colour);
    }
    else if((value > 99) && (value <= 999))
    {
        ch = ((value % 1000) / 100);
        PCD8544_set_cursor((x_pos + 6), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = ((value % 100) / 10);
        PCD8544_set_cursor((x_pos + 12), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = (value % 10);
        PCD8544_set_cursor((x_pos + 18), y_pos);
        PCD8544_print_char((48 + ch), colour);

        PCD8544_set_cursor((x_pos + 24), y_pos);
        PCD8544_print_char(0x20, colour);

        PCD8544_set_cursor((x_pos + 30), y_pos);
        PCD8544_print_char(0x20, colour);
    }
    else if((value > 9) && (value <= 99))
    {
        ch = ((value % 100) / 10);
        PCD8544_set_cursor((x_pos + 6), y_pos);
        PCD8544_print_char((48 + ch), colour);

        ch = (value % 10);
        PCD8544_set_cursor((x_pos + 12), y_pos);
        PCD8544_print_char((48 + ch), colour);

        PCD8544_set_cursor((x_pos + 18), y_pos);
        PCD8544_print_char(0x20, colour);

        PCD8544_set_cursor((x_pos + 24), y_pos);
        PCD8544_print_char(0x20, colour);

        PCD8544_set_cursor((x_pos + 30), y_pos);
        PCD8544_print_char(0x20, colour);
    }
    else
    {
        ch = (value % 10);
        PCD8544_set_cursor((x_pos + 6), y_pos);
        PCD8544_print_char((48 + ch), colour);

        PCD8544_set_cursor((x_pos + 12), y_pos);
        PCD8544_print_char(0x20, colour);

        PCD8544_set_cursor((x_pos + 18), y_pos);
        PCD8544_print_char(0x20, colour);

        PCD8544_set_cursor((x_pos + 24), y_pos);
        PCD8544_print_char(0x20, colour);

        PCD8544_set_cursor((x_pos + 30), y_pos);
        PCD8544_print_char(0x20, colour);
    }
}

void print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points, unsigned char colour)
{
    unsigned char ch = 0x00;

    PCD8544_set_cursor(x_pos, y_pos);
    PCD8544_print_char(0x2E, colour);

    ch = (value / 1000);
    PCD8544_set_cursor((x_pos + 6), y_pos);
    PCD8544_print_char((48 + ch), colour);

    if(points > 1)
    {
        ch = ((value % 1000) / 100);
        PCD8544_set_cursor((x_pos + 12), y_pos);
        PCD8544_print_char((48 + ch), colour);


        if(points > 2)
        {
            ch = ((value % 100) / 10);
            PCD8544_set_cursor((x_pos + 18), y_pos);
            PCD8544_print_char((48 + ch), colour);

            if(points > 3)
            {
                ch = (value % 10);
                PCD8544_set_cursor((x_pos + 24), y_pos);
                PCD8544_print_char((48 + ch), colour);;
            }
        }
    }
}


void print_float(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points, unsigned char colour)
{
    signed long tmp = 0x00;

    tmp = ((signed long)value);
    print_int(x_pos, y_pos, tmp, colour);
    tmp = ((value - tmp) * 10000);

    if(tmp < 0)
    {
       tmp = -tmp;
    }

    if((value >= 9999) && (value < 99999))
    {
        print_decimal((x_pos + 36), y_pos, tmp, points, colour);
    }
    else if((value >= 999) && (value < 9999))
    {
        print_decimal((x_pos + 30), y_pos, tmp, points, colour);
    }
    else if((value >= 99) && (value < 999))
    {
        print_decimal((x_pos + 24), y_pos, tmp, points, colour);
    }
    else if((value >= 9) && (value < 99))
    {
        print_decimal((x_pos + 18), y_pos, tmp, points, colour);
    }
    else if(value < 9)
    {
        print_decimal((x_pos + 12), y_pos, tmp, points, colour);
        if((value) < 0)
        {
            PCD8544_set_cursor(x_pos, y_pos);
            PCD8544_print_char(0x2D, colour);
        }
        else
        {
            PCD8544_set_cursor(x_pos, y_pos);
            PCD8544_print_char(0x20, colour);
        }
    }
}


void Draw_Pixel(unsigned char x_pos, unsigned char y_pos, unsigned char colour)
{
    unsigned char row = 0;
    unsigned char value = 0;

    if((x_pos < 0) || (x_pos >= X_max) || (y_pos < 0) || (y_pos >= Y_max))
    {
        return;
    }

    row = (y_pos >> 3);

    value = PCD8544_buffer[x_pos][row];

    if(colour == BLACK)
    {
        value |= (1 << (y_pos % 8));
    }
    else if(colour == WHITE)
    {
        value &= (~(1 << (y_pos % 8)));
    }
    else if(colour == PIXEL_XOR)
    {
        value ^= (1 << (y_pos % 8));
    }

    PCD8544_buffer[x_pos][row] = value;

    PCD8544_set_cursor(x_pos, row);
    PCD8544_write(DAT, value);
}

void LCD5110_setup()
{
    PCD8544_init();
    PCD8544_clear_screen(WHITE);
}
