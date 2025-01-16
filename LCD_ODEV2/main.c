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
        for (j = 0; j < 3180; j++) {} // Yaklaþýk 1 ms gecikme
}

// Komut gönderme fonksiyonu
void LCD_Command(unsigned char command) {
    GPIO_PORTB_DATA_R = command & 0xF0;  // Üst 4 bit
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

// Veri (karakter) gönderme fonksiyonu
void LCD_Data(unsigned char data) {
    GPIO_PORTB_DATA_R = data & 0xF0;    // Üst 4 bit
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

// LCD baþlatma fonksiyonu
void LCD_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x02;         // Port B'yi etkinleþtir
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);
    GPIO_PORTB_DIR_R = 0xFF;           // Port B pinlerini çýkýþ yap
    GPIO_PORTB_DEN_R = 0xFF;           // Dijital fonksiyonu etkinleþtir

    delayMs(20);
    LCD_Command(0x30);                 // 8-bit mod için
    delayMs(5);
    LCD_Command(0x30);                 // 8-bit mod için
    delayMs(1);
    LCD_Command(0x30);                 // 8-bit mod için
    LCD_Command(0x20);                 // 4-bit mod için
    LCD_Command(0x28);                 // 2 satýr, 5x7 matris
    LCD_Command(0x06);                 // Ýmleci artýr
    LCD_Command(0x01);                 // Ekraný temizle
    LCD_Command(0x0F);                 // Ekraný aç, imleç açýk
}

// Ana fonksiyon
int main(void) {
    LCD_Init();               // LCD'yi baþlat
    LCD_Command(0x01);        // Ekraný temizle
    LCD_Command(0x80);        // Ýlk satýr, ilk sütuna git

    // "DOGA" yazdýr
    LCD_Data('D');
    LCD_Data('O');
    LCD_Data('G');
    LCD_Data('A');

    while (1);                // Sonsuz döngü
}
