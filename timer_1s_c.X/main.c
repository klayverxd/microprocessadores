/*
 * File:   main.c
 * Author: Klayver Ximenes
 *
 * Created on 21 de Outubro de 2022, 07:53
 */


#include <xc.h>

void main(void) {
    // Gerar onda quadrada
    TRISDbits.RD0 = 0;  // Configura RD0 como saída
    
    // PRESCALER Fcpu/16
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2CKPS0 = 1;
    
    // POSTSCALER (0001) 16:1 (16 estouros)
    T2CONbits.T2OUTPS3 = 1;
    T2CONbits.T2OUTPS2 = 1;
    T2CONbits.T2OUTPS1 = 1;
    T2CONbits.T2OUTPS0 = 1;
    
    // Estouro a cada 1ms
    PR2 = 39;
    
    // Inicializar o timer
    T2CONbits.TMR2ON = 1;
    
    int conta10ms = 0;

    while(1) {
        while (TMR2IF == 0);
        // zera a flag quando tiver em 1
        TMR2IF = 0;
        
        conta10ms++;
        
        // inverte sinal a cada 1s
        if (conta10ms == 100) {
            conta10ms = 0;
            PORTDbits.RD0 = ~PORTDbits.RD0;
        }
    }
}
