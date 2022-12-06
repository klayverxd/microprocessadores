
// CONFIG1H
#pragma config FOSC = XT_XT     // Oscillator Selection bits (XT oscillator (XT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#include "lcd.h"
#include <stdio.h>
#include <xc.h>

// para escrever caracteres no lcd com printf()
void putch(char data) {
  escreve_lcd(data);   
}

void main(void) {
    PORTB = 0;
    TRISB = 0x01;  // define RB como input
    
    PORTC = 0;
    TRISC = 0x00;  // define RA como output
    
    PORTD = 0;
    TRISD = 0x00;  // define RD como output
    
    inicializa_lcd();
    limpa_lcd();
    
    caracter_inicio(1,3);
    printf("Aperte para");
    caracter_inicio(2,3);
    printf("iniciar!!!");
    
    while(1) {
        int start_reset = 0;
        int pressedJ1 = 0;
        int pressedJ2 = 0;
        long int timeJ1 = 0;
        long int timeJ2 = 0;
        long int counter = 0;
        
        if(PORTBbits.RB0 == 0x01){
            PORTCbits.RC0 = 1;
            __delay_ms(500);
            PORTCbits.RC0 = 0;
            
            limpa_lcd();
            printf("Rodando...");
            
            start_reset = 1;
        }
        
        while(start_reset) {
            __delay_ms(1);
            counter++;
            
            if(PORTBbits.RB1 == 0x01){
                pressedJ1 = 1;
                timeJ1 = counter;
                
                PORTCbits.RC1 = 1;
            }
            
            if(PORTBbits.RB2 == 0x01){
                pressedJ2 = 1;
                timeJ2 = counter;
                
                PORTCbits.RC2 = 1;
            }
            
            if(pressedJ1 == 1 && pressedJ2 == 1){
                limpa_lcd();
                caracter_inicio(1,1);
                printf("Tempo 1: %ldms", timeJ1);
                caracter_inicio(2,1);
                printf("Tempo 2: %ldms", timeJ2);
                
                while(1) {
                    if(PORTBbits.RB0 == 0x01){
                        
                        PORTCbits.RC0 = 0;
                        PORTCbits.RC1 = 0;
                        PORTCbits.RC2 = 0;
                        
                        limpa_lcd();
                        printf("Reiniciando...");
                        __delay_ms(1000);
                        limpa_lcd();
                                                
                        start_reset = 0;
                        
                        caracter_inicio(1,3);
                        printf("Aperte para");
                        caracter_inicio(2,3);
                        printf("iniciar!!!");
                        
                        break;
                    }
                }
                break;
            }
        }
    }
}
