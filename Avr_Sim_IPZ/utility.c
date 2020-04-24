#include "utility.h"

void initialize()
{
	print_cpu();
	print_state(DDRB_);
	print_state(DDRC_);
	print_state(DDRD_);
	print_state(PORTB_);
	print_state(PORTC_);
	print_state(PORTD_);
	print_state(PINB_);
	print_state(PINC_);
	print_state(PIND_);
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1AL = 0;
	OCR1AH = 0;
	ICR1H = 0;
	ICR1L = 0;
	TCNT1H = 0;
	TCNT1L = 0;
	return;
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void print_cpu()
{
	int y = 4;
	int x = 60;
	gotoxy(x, ++y); printf("  ____   ____  ");
	gotoxy(x, ++y); printf("  |   \\_/   |  ");
	gotoxy(x, ++y); printf("==|PC6   PC5|==");
	gotoxy(x, ++y); printf("==|PD0   PC4|==");
	gotoxy(x, ++y); printf("==|PD1   PC3|==");
	gotoxy(x, ++y); printf("==|PD2   PC2|==");
	gotoxy(x, ++y); printf("==|PD3   PC1|==");
	gotoxy(x, ++y); printf("==|PD4   PC0|==");
	gotoxy(x, ++y); printf("==|VCC   GND|==");
	gotoxy(x, ++y); printf("==|GND  AREF|==");
	gotoxy(x, ++y); printf("==|PB6  AVCC|==");
	gotoxy(x, ++y); printf("==|PB7   PB5|==");
	gotoxy(x, ++y); printf("==|PD5   PB4|==");
	gotoxy(x, ++y); printf("==|PD6   PB3|==");
	gotoxy(x, ++y); printf("==|PD7   PB2|==");
	gotoxy(x, ++y); printf("==|PB0   PB1|==");
	gotoxy(x, ++y); printf("  |_________|  ");
}

void print_state(REGISTER type)
{
	switch (type)
	{
	case DDRC_:
		gotoxy(0, 1);
		printf("DDRC: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(DDRC));
		break;
	case DDRB_:
		gotoxy(0, 2);
		printf("DDRB: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(DDRB));
		break;
	case DDRD_:
		gotoxy(0, 3);
		printf("DDRD: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(DDRD));
		break;
	case PORTB_:
		gotoxy(0, 5);
		printf("PORTB: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PORTB));
		break;
	case PORTC_:
		gotoxy(0, 6);
		printf("PORTC: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PORTC));
		break;
	case PORTD_:
		gotoxy(0, 7);
		printf("PORTD: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PORTD));
		break;
	case PINB_:
		gotoxy(0, 9);
		printf("PINB: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PINB));
		break;
	case PINC_:
		gotoxy(0, 10);
		printf("PINC: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PINC));
		break;
	case PIND_:
		gotoxy(0, 11);
		printf("PIND: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PIND));
		break;
	default:
		gotoxy(0, 0);
		printf("Your code is retarded <3");
		break;
	}
	return;
}

void print_bit_state(REGISTER type, byte n)
{
	switch (type)
	{
	case DDRC_:
		gotoxy(13 - n, 1);
		printf("%d", (DDRC & 1 << n) >> n);
		break;
	case DDRB_:
		gotoxy(13 - n, 2);
		printf("%d", (DDRB & 1 << n) >> n);
		break;
	case DDRD_:
		gotoxy(13 - n, 3);
		printf("%d", (DDRD & 1 << n) >> n);
		break;
	case PORTB_:
		gotoxy(14 - n, 5);
		printf("%d", (PORTB & 1 << n) >> n);
		break;
	case PORTC_:
		gotoxy(14 - n, 6);
		printf("%d", (PORTC & 1 << n) >> n);
		break;
	case PORTD_:
		gotoxy(14 - n, 7);
		printf("%d", (PORTD & 1 << n) >> n);
		break;
	case PINB_:
		gotoxy(13 - n, 9);
		printf("%d", (PINB & 1 << n) >> n);
		break;
	case PINC_:
		gotoxy(13 - n, 10);
		printf("%d", (PINC & 1 << n) >> n);
		break;
	case PIND_:
		gotoxy(13 - n, 11);
		printf("%d", (PIND & 1 << n) >> n);
		break;
	default:
		gotoxy(0, 0);
		printf("Your code is retarded <3");
		break;
	}
	return;
}

void pressed()
{
	static byte pressedB;
	static byte pressedC;
	static byte pressedD;
	static byte countdown;
	if (GetKeyState(VK_Z) & 0x8000 && !(DDRD & 0x80))
	{
		if (!(pressedD & 0x80))
		{
			if (PORTD & 0x80) PIND &= 0x7F;
			else PIND |= 0x80;
			print_bit_state(PIND_, 7);
			pressedD |= 0x80;
		}
	}
	else
	{
		if (pressedD & 0x80)
		{
			if (PORTD & 0x80) PIND |= 0x80;
			else PIND &= 0x7F;
			print_bit_state(PIND_, 7);
			pressedD &= 0x7F;
		}
	}
	if (GetKeyState(VK_X) & 0x8000 && !(DDRD & 0x40))
	{
		if (!(pressedD & 0x40))
		{
			if (PORTD & 0x40) PIND &= 0xBF;
			else PIND |= 0x40;
			print_bit_state(PIND_, 6);
			pressedD |= 0x40;
		}
	}
	else
	{
		if (pressedD & 0x40)
		{
			if (PORTD & 0x40) PIND |= 0x40;
			else PIND &= 0xBF;
			print_bit_state(PIND_, 6);
			pressedD &= 0xBF;
		}
	}
	if (GetKeyState(VK_C) & 0x8000 && !(DDRD & 0x20))
	{
		if (!(pressedD & 0x20))
		{
			if (PORTD & 0x20) PIND &= 0xDF;
			else PIND |= 0x20;
			print_bit_state(PIND_, 5);
			pressedD |= 0x20;
		}
	}
	else
	{
		if (pressedD & 0x20)
		{
			if (PORTD & 0x20) PIND |= 0x20;
			else PIND &= 0xDF;
			print_bit_state(PIND_, 5);
			pressedD &= 0xDF;
		}
	}
	if (GetKeyState(VK_V) & 0x8000 && !(DDRD & 0x10))
	{
		if (!(pressedD & 0x10))
		{
			if (PORTD & 0x10) PIND &= 0xEF;
			else PIND |= 0x10;
			print_bit_state(PIND_, 4);
			pressedD |= 0x10;
		}
	}
	else
	{
		if (pressedD & 0x10)
		{
			if (PORTD & 0x10) PIND |= 0x10;
			else PIND &= 0xEF;
			print_bit_state(PIND_, 4);
			pressedD &= 0xEF;
		}
	}
	if (GetKeyState(VK_B) & 0x8000 && !(DDRD & 0x08))
	{
		if (!(pressedD & 0x08))
		{
			if (PORTD & 0x08) PIND &= 0xF7;
			else PIND |= 0x08;
			print_bit_state(PIND_, 3);
			pressedD |= 0x08;
		}
	}
	else
	{
		if (pressedD & 0x08)
		{
			if (PORTD & 0x08) PIND |= 0x08;
			else PIND &= 0xF7;
			print_bit_state(PIND_, 3);
			pressedD &= 0xF7;
		}
	}
	if (GetKeyState(VK_N) & 0x8000 && !(DDRD & 0x04))
	{
		if (!(pressedD & 0x04))
		{
			if (PORTD & 0x04) PIND &= 0xFB;
			else PIND |= 0x04;
			print_bit_state(PIND_, 2);
			pressedD |= 0x04;
		}
	}
	else
	{
		if (pressedD & 0x04)
		{
			if (PORTD & 0x04) PIND |= 0x04;
			else PIND &= 0xFB;
			print_bit_state(PIND_, 2);
			pressedD &= 0xFB;
		}
	}
	if (GetKeyState(VK_M) & 0x8000 && !(DDRD & 0x02))
	{
		if (!(pressedD & 0x02))
		{
			if (PORTD & 0x02) PIND &= 0xFD;
			else PIND |= 0x02;
			print_bit_state(PIND_, 1);
			pressedD |= 0x02;
		}
	}
	else
	{
		if (pressedD & 0x02)
		{
			if (PORTD & 0x02) PIND |= 0x02;
			else PIND &= 0xFD;
			print_bit_state(PIND_, 1);
			pressedD &= 0xFD;
		}
	}
	if (GetKeyState(VK_OEM_COMMA) & 0x8000 && !(DDRD & 0x01))
	{
		if (!(pressedD & 0x01))
		{
			if (PORTD & 0x01) PIND &= 0xFE;
			else PIND |= 0x01;
			print_bit_state(PIND_, 0);
			pressedD |= 0x01;
		}
	}
	else
	{
		if (pressedD & 0x01)
		{
			if (PORTD & 0x01) PIND |= 0x01;
			else PIND &= 0xFE;
			print_bit_state(PIND_, 0);
			pressedD &= 0xFE;
		}
	}

	if (GetKeyState(VK_A) & 0x8000 && !(DDRC & 0x80))
	{
		if (!(pressedC & 0x80))
		{
			if (PORTC & 0x80) PINC &= 0x7F;
			else PINC |= 0x80;
			print_bit_state(PINC_, 7);
			pressedC |= 0x80;
		}
	}
	else
	{
		if (pressedC & 0x80)
		{
			if (PORTC & 0x80) PINC |= 0x80;
			else PINC &= 0x7F;
			print_bit_state(PINC_, 7);
			pressedC &= 0x7F;
		}
	}
	if (GetKeyState(VK_S) & 0x8000 && !(DDRC & 0x40))
	{
		if (!(pressedC & 0x40))
		{
			if (PORTC & 0x40) PINC &= 0xBF;
			else PINC |= 0x40;
			print_bit_state(PINC_, 6);
			pressedC |= 0x40;
		}
	}
	else
	{
		if (pressedC & 0x40)
		{
			if (PORTC & 0x40) PINC |= 0x40;
			else PINC &= 0xBF;
			print_bit_state(PINC_, 6);
			pressedC &= 0xBF;
		}
	}
	if (GetKeyState(VK_D) & 0x8000 && !(DDRC & 0x20))
	{
		if (!(pressedC & 0x20))
		{
			if (PORTC & 0x20) PINC &= 0xDF;
			else PINC |= 0x20;
			print_bit_state(PINC_, 5);
			pressedC |= 0x20;
		}
	}
	else
	{
		if (pressedC & 0x20)
		{
			if (PORTC & 0x20) PINC |= 0x20;
			else PINC &= 0xDF;
			print_bit_state(PINC_, 5);
			pressedC &= 0xDF;
		}
	}
	if (GetKeyState(VK_F) & 0x8000 && !(DDRC & 0x10))
	{
		if (!(pressedC & 0x10))
		{
			if (PORTC & 0x10) PINC &= 0xDF;
			else PINC |= 0x10;
			print_bit_state(PINC_, 4);
			pressedC |= 0x10;
		}
	}
	else
	{
		if (pressedC & 0x10)
		{
			if (PORTC & 0x10) PINC |= 0x10;
			else PINC &= 0xEF;
			print_bit_state(PINC_, 4);
			pressedC &= 0xEF;
		}
	}
	if (GetKeyState(VK_G) & 0x8000 && !(DDRC & 0x08))
	{
		if (!(pressedC & 0x08))
		{
			if (PORTC & 0x08) PINC &= 0xF7;
			else PINC |= 0x08;
			print_bit_state(PINC_, 3);
			pressedC |= 0x08;
		}
	}
	else
	{
		if (pressedC & 0x08)
		{
			if (PORTC & 0x08) PINC |= 0x08;
			else PINC &= 0xF7;
			print_bit_state(PINC_, 3);
			pressedC &= 0xF7;
		}
	}
	if (GetKeyState(VK_H) & 0x8000 && !(DDRC & 0x04))
	{
		if (!(pressedC & 0x04))
		{
			if (PORTC & 0x04) PINC &= 0xFB;
			else PINC |= 0x04;
			print_bit_state(PINC_, 2);
			pressedC |= 0x04;
		}
	}
	else
	{
		if (pressedC & 0x04)
		{
			if (PORTC & 0x04) PINC |= 0x04;
			else PINC &= 0xFB;
			print_bit_state(PINC_, 2);
			pressedC &= 0xFB;
		}
	}
	if (GetKeyState(VK_J) & 0x8000 && !(DDRC & 0x02))
	{
		if (!(pressedC & 0x02))
		{
			if (PORTC & 0x02) PINC &= 0xFD;
			else PINC |= 0x02;
			print_bit_state(PINC_, 1);
			pressedC |= 0x02;
		}
	}
	else
	{
		if (pressedC & 0x02)
		{
			if (PORTC & 0x02) PINC |= 0x02;
			else PINC &= 0xFD;
			print_bit_state(PINC_, 1);
			pressedC &= 0xFD;
		}
	}
	if (GetKeyState(VK_K) & 0x8000 && !(DDRC & 0x01))
	{
		if (!(pressedC & 0x01))
		{
			if (PORTC & 0x01) PINC &= 0xFE;
			else PINC |= 0x01;
			print_bit_state(PINC_, 0);
			pressedC |= 0x01;
		}
	}
	else
	{
		if (pressedC & 0x01)
		{
			if (PORTC & 0x01) PINC |= 0x01;
			else PINC &= 0xFE;
			print_bit_state(PINC_, 0);
			pressedC &= 0xFE;
		}
	}

	if (GetKeyState(VK_Q) & 0x8000 && !(DDRB & 0x80))
	{
		if (!(pressedB & 0x80))
		{
			if (PORTB & 0x80) PINB &= 0x7F;
			else PINB |= 0x80;
			print_bit_state(PINB_, 7);
			pressedB |= 0x80;
		}
	}
	else
	{
		if (pressedB & 0x80)
		{
			if (PORTB & 0x80) PINB |= 0x80;
			else PINB &= 0x7F;
			print_bit_state(PINB_, 7);
			pressedB &= 0x7F;
		}
	}
	if (GetKeyState(VK_W) & 0x8000 && !(DDRB & 0x40))
	{
		if (!(pressedB & 0x40))
		{
			if (PORTB & 0x40) PINB &= 0xBF;
			else PINB |= 0x40;
			print_bit_state(PINB_, 6);
			pressedB |= 0x40;
		}
	}
	else
	{
		if (pressedB & 0x40)
		{
			if (PORTB & 0x40) PINB |= 0x40;
			else PINB &= 0xBF;
			print_bit_state(PINB_, 6);
			pressedB &= 0xBF;
		}
	}
	if (GetKeyState(VK_E) & 0x8000 && !(DDRB & 0x20))
	{
		if (!(pressedB & 0x20))
		{
			if (PORTB & 0x20) PINB &= 0xDF;
			else PINB |= 0x20;
			print_bit_state(PINB_, 5);
			pressedB |= 0x20;
		}
	}
	else
	{
		if (pressedB & 0x20)
		{
			if (PORTB & 0x20) PINB |= 0x20;
			else PINB &= 0xDF;
			print_bit_state(PINB_, 5);
			pressedB &= 0xDF;
		}
	}
	if (GetKeyState(VK_R) & 0x8000 && !(DDRB & 0x10))
	{
		if (!(pressedB & 0x10))
		{
			if (PORTB & 0x10) PINB &= 0xDF;
			else PINB |= 0x10;
			print_bit_state(PINB_, 4);
			pressedB |= 0x10;
		}
	}
	else
	{
		if (pressedB & 0x10)
		{
			if (PORTB & 0x10) PINB |= 0x10;
			else PINB &= 0xEF;
			print_bit_state(PINB_, 4);
			pressedB &= 0xEF;
		}
	}
	if (GetKeyState(VK_T) & 0x8000 && !(DDRB & 0x08))
	{
		if (!(pressedB & 0x08))
		{
			if (PORTB & 0x08) PINB &= 0xF7;
			else PINB |= 0x08;
			print_bit_state(PINB_, 3);
			pressedB |= 0x08;
		}
	}
	else
	{
		if (pressedB & 0x08)
		{
			if (PORTB & 0x08) PINB |= 0x08;
			else PINB &= 0xF7;
			print_bit_state(PINB_, 3);
			pressedB &= 0xF7;
		}
	}
	if (GetKeyState(VK_Y) & 0x8000 && !(DDRB & 0x04))
	{
		if (!(pressedB & 0x04))
		{
			if (PORTB & 0x04) PINB &= 0xFB;
			else PINB |= 0x04;
			print_bit_state(PINB_, 2);
			pressedB |= 0x04;
		}
	}
	else
	{
		if (pressedB & 0x04)
		{
			if (PORTB & 0x04) PINB |= 0x04;
			else PINB &= 0xFB;
			print_bit_state(PINB_, 2);
			pressedB &= 0xFB;
		}
	}
	if (GetKeyState(VK_U) & 0x8000 && !(DDRB & 0x02))
	{
		if (!(pressedB & 0x02))
		{
			if (PORTB & 0x02) PINB &= 0xFD;
			else PINB |= 0x02;
			print_bit_state(PINB_, 1);
			pressedB |= 0x02;
		}
	}
	else
	{
		if (pressedB & 0x02)
		{
			if (PORTB & 0x02) PINB |= 0x02;
			else PINB &= 0xFD;
			print_bit_state(PINB_, 1);
			pressedB &= 0xFD;
		}
	}
	if (GetKeyState(VK_I) & 0x8000 && !(DDRB & 0x01))
	{
		if (!(pressedB & 0x01))
		{
			if (PORTB & 0x01) PINB &= 0xFE;
			else PINB |= 0x01;
			print_bit_state(PINB_, 0);
			pressedB |= 0x01;
		}
	}
	else
	{
		if (pressedB & 0x01)
		{
			if (PORTB & 0x01) PINB |= 0x01;
			else PINB &= 0xFE;
			print_bit_state(PINB_, 0);
			pressedB &= 0xFE;
		}
	}

	if (TCCR1B & 0x01)
	{
		if (countdown)
		{
			if (!--TCNT1L)
			{
				--TCNT1H;
			}
			if (!TCNT1L && !TCNT1H) 
			{
				countdown = 0;
			}
		}
		else 
		{
			if (!++TCNT1L)
			{
				++TCNT1H;
			}
			if (TCNT1L == 0xff && TCNT1H == 0xff)
			{
				countdown = 1;
			}
		}
		if(TCNT1L == OCR1AL && TCNT1H == OCR1AH)
		{
			if (countdown) 
			{
				PORTB &= ~0x02;
				print_bit_state(PORTB_, 1);
			}
			else
			{
				PORTB |= 0x02;
				print_bit_state(PORTB_, 1);
			}
		}
	}

	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		exit(0);
	}
}

void update_port(REGISTER type)
{
	switch (type)
	{
	case PORTD_:
		print_state(PORTD_);
		PIND = (0xff - DDRD) & PORTD;
		print_state(PIND_);
		break;
	case PORTC_:
		print_state(PORTC_);
		PINC = (0xff - DDRC) & PORTC;
		print_state(PINC_);
		break;
	case PORTB_:
		print_state(PORTB_);
		PINB = (0xff - DDRB) & PORTB;
		print_state(PINB_);
		break;
	default:
		print_state(type);
		break;
	}
	return;
}