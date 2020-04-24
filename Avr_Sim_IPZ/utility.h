#pragma once
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

#define _delay_ms(x) Sleep(x)

typedef enum REGISTER_ { DDRD_, DDRC_, DDRB_, PORTB_, PORTC_, PORTD_, PINB_, PINC_, PIND_ } REGISTER;
byte DDRD, DDRC, DDRB, PORTB, PORTC, PORTD, PINB, PINC, PIND, TCCR1A, TCCR1B, OCR1AL, OCR1AH, ICR1H, ICR1L, TCNT1H, TCNT1L;
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 



void gotoxy(int, int);
void initialize(void);
void print_cpu();
void print_state(REGISTER);
void print_bit_state(REGISTER, byte);
void pressed();
void update_port(REGISTER);