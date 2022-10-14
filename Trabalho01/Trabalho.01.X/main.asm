#include "p18f4550.inc"	    ;Importando a biblioteca do microcontrolador

CONFIG FOSC = XT_XT	; Oscillator com Cristal de 4 MHz
CONFIG WDT = OFF	; Watchdog Timer Enable bit (WDT enabled)
CONFIG LVP = OFF	; Single-Supply ICSP Enable bit

VARIAVEIS UDATA_ACS 0	
    CONT RES 1		    ;Variavel contadora - endereco 0x00
    ATR1 RES 1		    ;Primeira variavel de atraso - endereço 0x01
    ATR2 RES 1		    ;Segunda variavel de atraso - endereço 0x02	
    SW1	EQU 1		    ;Pino 1 para o botao SW1
    SW2	EQU 2		    ;Pino 2 para o botao SW2

RES_VECT  CODE    0x0000    ;O rotulo para a posicao 0x0000 da memoria
    GOTO    START	    ;Indo para o inicio do programa

MAIN_PROG CODE		    ;let linker place main program

START
    BSF TRISC, SW1	    ;Pino RC1 para o botao SW1
    BSF TRISC, SW2	    ;Pino RC2 para o botao SW2
    CLRF CONT		    ;Zera a primeira variavel contadora
    CLRF ATR1		    ;Zera a segunda variavel de atraso
    CLRF ATR2		    ;Zera a variavel contadora
    CLRF TRISD		    ;Define PORTD como saída

LOOP			    ;Loop principal da execucao do programa
    BTFSC PORTC, SW1	    ;Se o botão SW1 for pressionado chama o incremento
    CALL INCREMENTO

    BTFSC PORTC, SW2	    ;Se o botão 02 for pressionado chama o decremento
    CALL DECREMENTO

    MOVFF CONT, PORTD	    ;Ao final atualiza PORTD com o valor atual da variável contadora
    GOTO LOOP		    ;Retorna para o Loop principal

INCREMENTO
    CALL DELAY1S
    BTFSC PORTC, SW1	    ;Se depois de 1s o botao SW1 permaneceu pressionado
    INCF CONT		    ;Entao incrementa a variavel contadora
    RETURN 

DECREMENTO
    CALL DELAY1S
    BTFSC PORTC, SW2	    ;Se depois de 1s o botao SW2 permaneceu pressionado
    DECFSZ CONT		    ;Decrementa em 1 a variavel contadora, pula se já tiver em 0
    RETURN

;Delay de 1s
DELAY1S
    MOVLW .200	    ;Coloca o valor 200 em W
    MOVWF ATR1	    ;Coloca o valor de W em ATR2

LOOP_DELAY1S
    RCALL DELAY1MS
    RCALL DELAY1MS
    RCALL DELAY1MS
    RCALL DELAY1MS
    RCALL DELAY1MS
    DECFSZ ATR1    ;Chama DELAY1MS 1000 vezes 
    BRA LOOP_DELAY1S
    RETURN

;Delay de 1ms
DELAY1MS
    MOVLW .100	    ;Coloca o valor 100 em W
    MOVWF ATR2	    ;Coloca o valor de W em ATR2

LOOP_DELAY1MS
    NOP
    NOP
    NOP
    NOP
    NOP
    DECFSZ ATR2	    ;Executa 100x
    BRA LOOP_DELAY1MS
    RETURN
END