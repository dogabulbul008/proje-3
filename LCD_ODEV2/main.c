#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "inc/hw_uart.h"
#include "driverlib/adc.h"
#include "inc/tm4c123gh6pm.h"

// Delay fonksiyonu
void delayMs(int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3180; j++) {} // Yakla��k 1 ms gecikme
}

// Komut g�nderme fonksiyonu
void LCD_Command(unsigned char command) {
    GPIO_PORTB_DATA_R = command & 0xF0;  // �st 4 bit
    GPIO_PORTB_DATA_R &= ~0x04;          // RS = 0
    GPIO_PORTB_DATA_R |= 0x08;           // E = 1
    delayMs(1);
    GPIO_PORTB_DATA_R &= ~0x08;          // E = 0
    delayMs(1);

    GPIO_PORTB_DATA_R = (command << 4) & 0xF0;  // Alt 4 bit
    GPIO_PORTB_DATA_R &= ~0x04;                 // RS = 0
    GPIO_PORTB_DATA_R |= 0x08;                  // E = 1
    delayMs(1);
    GPIO_PORTB_DATA_R &= ~0x08;                 // E = 0
    delayMs(2);
}

// Veri (karakter) g�nderme fonksiyonu
void LCD_Data(unsigned char data) {
    GPIO_PORTB_DATA_R = data & 0xF0;    // �st 4 bit
    GPIO_PORTB_DATA_R |= 0x04;          // RS = 1
    GPIO_PORTB_DATA_R |= 0x08;          // E = 1
    delayMs(1);
    GPIO_PORTB_DATA_R &= ~0x08;         // E = 0
    delayMs(1);

    GPIO_PORTB_DATA_R = (data << 4) & 0xF0;  // Alt 4 bit
    GPIO_PORTB_DATA_R |= 0x04;               // RS = 1
    GPIO_PORTB_DATA_R |= 0x08;               // E = 1
    delayMs(1);
    GPIO_PORTB_DATA_R &= ~0x08;              // E = 0
    delayMs(2);
}

// LCD ba�latma fonksiyonu
void LCD_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x02;         // Port B'yi etkinle�tir
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);
    GPIO_PORTB_DIR_R = 0xFF;           // Port B pinlerini ��k�� yap
    GPIO_PORTB_DEN_R = 0xFF;           // Dijital fonksiyonu etkinle�tir

    delayMs(20);
    LCD_Command(0x30);                 // 8-bit mod i�in
    delayMs(5);
    LCD_Command(0x30);                 // 8-bit mod i�in
    delayMs(1);
    LCD_Command(0x30);                 // 8-bit mod i�in
    LCD_Command(0x20);                 // 4-bit mod i�in
    LCD_Command(0x28);                 // 2 sat�r, 5x7 matris
    LCD_Command(0x06);                 // �mleci art�r
    LCD_Command(0x01);                 // Ekran� temizle
    LCD_Command(0x0F);                 // Ekran� a�, imle� a��k
}

// Ana fonksiyon
int main(void) {
    LCD_Init();               // LCD'yi ba�lat
    LCD_Command(0x01);        // Ekran� temizle
    LCD_Command(0x80);        // �lk sat�r, ilk s�tuna git

    // "DOGA" yazd�r
    LCD_Data('D');
    LCD_Data('O');
    LCD_Data('G');
    LCD_Data('A');

    while (1);                // Sonsuz d�ng�
}
