#include "utility.h"

#define F_CPU 16000000
#define button_1 PIND & 0x80
#define button_2 PIND & 0x40
#define button_3 PIND & 0x20
#define button_4 PIND & 0x10
#define button_u PIND & 0x08
#define button_pressed (31 - (PIND>>3))
#define led_r 0x04
#define led_g 0x02
#define led_b 0x01
#define N 4
#define OPEN_H 2684 & 0xff00;
#define OPEN_L 2684 & 0x00ff;
#define CLOSE_H (2684/2) & 0xff00;
#define CLOSE_L (2684/2) & 0x00ff;
#define MIDDLE_H (2684/2 + 2684/4) & 0xff00;
#define MIDDLE_L (2684/2 + 2684/4) & 0x00ff;

typedef enum _PASSWORD {IDLE, ADDED, FULL, CORRECT, WRONG} PASSWORD;

int main()
{
	char admin_press = 0;
	char i_pass[N] = { 0 };
	char pass[N] = { 1,2,3,4 };
	char admin_pass[N] = { 2,3,1,4 };
	char button = 0;
	PASSWORD password = IDLE;
	initialize();
	PORTD = 0xFC;
	update_port(PORTD_);
	DDRD = 0x07;
	update_port(DDRD_);
	
	TCCR1A = 0xC0;
	TCCR1B = 0x10;

	ICR1H = 26844 & 0xff00;
	ICR1L = 26844 & 0x00ff;
	while(1)
	{
		if ( button_pressed && !button)
		{
			_delay_ms(100);
			if (~button_1) button = 1;
			else if (~button_2) button = 2;
			else if (~button_3) button = 3;
			else if (~button_4) button = 4;
			else if (~button_u) button = 5;

			char i;
			if (button == 5)
			{
				if (PORTD & led_b)
				{
					if (!(PORTD & led_g))
					{
						for (i = 0; i < N; ++i)
						{
							if (i_pass[i] != admin_pass[i]) password = WRONG;
							i_pass[i] = 0;
						}
					}
					if (password == WRONG)
					{
						password = IDLE;
						admin_press = 0;
						PORTD &= ~led_b;
						print_bit_state(PORTD_, led_b - 1);
					}
					else
					{
						for (i = 0; i < N; ++i)
						{
							pass[i] = 0;
						}
						PORTD |= led_r | led_g;
						PORTD &= ~led_b;
						update_port(PORTD_);
					}
				}
				else
				{
					if (!(PORTD & led_g))
					{
						for (i = 0; i < N; ++i)
						{
							if (i_pass[i] != pass[i]) password = WRONG;
							i_pass[i] = 0;
						}
					}
					if (password == WRONG)
					{
						password = IDLE;
					}
					else
					{
						if (PORTD & led_g)
						{
							PORTD &= ~led_g;
							PORTD |= led_r;
							OCR1AL = CLOSE_L;
							OCR1AH = CLOSE_H;
							TCCR1B |= 0x01;
							_delay_ms(1000);
							TCCR1B &= ~0x01;
						}
						else
						{
							PORTD &= ~led_r;
							PORTD |= led_g;								
							OCR1AL = OPEN_L;
							OCR1AH = OPEN_H;
							TCCR1B |= 0x01;
							_delay_ms(1000);
							OCR1AL = MIDDLE_L;
							OCR1AH = MIDDLE_H;
							_delay_ms(1000);
							TCCR1B &= ~0x01;

						}
						update_port(PORTD_);
					}
				}

				if (i_pass[0] == 0) ++admin_press;
				else
				{
					admin_press = 0;
					PORTD &= ~led_b;
					print_bit_state(PORTD_, led_b - 1);
				}
				if (admin_press == 5)
				{
					PORTD |= led_b;
					print_bit_state(PORTD_, led_b - 1);
				}
				else if (admin_press > 5)
				{
					admin_press = 0;
					PORTD &= ~led_b;
					print_bit_state(PORTD_, led_b - 1);
				}

			}
			else
			{
				if (PORTD & led_r && PORTD & led_g)
				{
					for (i = 0; i < N; ++i)
					{
						if (!pass[i])
						{
							pass[i] = button;
							password = ADDED;
							break;
						}
					}
					if (password == ADDED) password = IDLE;
					else 
					{
						PORTD &= ~led_g;
						PORTD |= led_b;
						update_port(PORTD_);
					}

				}
				else
				{
					for (i = 0; i < N; ++i)
					{
						if (!i_pass[i])
						{
							i_pass[i] = button;
							password = ADDED;
							break;
						}
					}
					if (password == ADDED) password = IDLE;
					else password = FULL;
				}
			}
		}
		else if(!button_pressed && button) button = 0;
		pressed();
	}
	return 0;
}

