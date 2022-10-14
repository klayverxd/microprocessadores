
#include <p18f4550.inc>

CONFIG  FOSC = XT_XT          ; Oscillator Selection bits (XT oscillator)
CONFIG  WDT = OFF             ; Watchdog desabilitado
CONFIG  PBADEN = OFF          ; PORTB as analog input disabled
    
;*******************************************************************************
; Vetor de interrup��o do reset do microprocessador
;*******************************************************************************

RES_VECT  CODE    0x0000 
    GOTO    START  ; desvia para o programa principal

;****************************************************************
; Vetor de interrup��o de alta prioridade
;****************************************************************

INT_HIGH_VECT CODE    0X0008
    GOTO INT_IRQ  ; Desvia para rotina de interrup��o

;*****************************************************************
; Declara��o das vari�veis    
;*******************************************************************************

AUX_VARS   UDATA_ACS
TEMP1         RES        1 ; Contador usado no atraso de 1s      
TEMP2         RES        1 ; Contador usado no atraso de 1,6 ms 
DISP1         RES        1 ; Informa��o do display #1
DISP2         RES        1 ; Informa��o do display #2

;*******************************************************************************
; Programa principal
;*******************************************************************************

MAIN_PROG CODE
 
START
;*******************************************************************************
; Inicializa��es do programa principal
;*******************************************************************************
    MOVLW 0x01   ; Configura RB0 como entrada (Push button)
    MOVWF TRISB
    MOVLW 0x00   ; Configura todos pinos de PORTD como saida (Displays)
    MOVWF TRISD
    MOVWF PORTD  ; Para mostrar "00" nos displays
    CLRF DISP1   ; Informa��o do display #1
    CLRF DISP2   ; Informa��o do display #2
    BSF INTCON,INT0IE;	HABILITA A INTERRUP�AO DO Push button em RB0
    BCF RCON,IPEN; DESABILITANDO A PRIORIDADE DE INTERRUP�AO
    BSF INTCON,GIE; HABILITA TODAS INTERRUP�OES
    BSF INTCON,PEIE; HABILITA INTER. PARA TODOS PERIFERICOS 

;*******************************************************************************
; Loop do programa principal
;*******************************************************************************
REPETE
    BTG PORTB,RB1       ; Muda estado logico do RB1
    CALL ATRASO_1s      ; Espera 1 segundo
    CALL CONTA          ; Atualiza os valores em DISP1 e DISP2
    CALL ATUALIZA_PORTD ; Envia valores para Porta D
    GOTO REPETE         ; Repete processo
    
;*******************************************************************************
; Rotina ATRASO_1s
; Gera um atraso correspondente a 1 segundo
; para o microcontrolador operando a um clock
; de 4MHz    
;*******************************************************************************
    
ATRASO_1s
    MOVLW .190  ; Executa 190 vezes 3 chamadas da rotina ATRASO
    MOVWF TEMP2
L1
    CALL ATRASO
    CALL ATRASO
    CALL ATRASO
    DECFSZ TEMP2
    BRA L1
    RETURN
    
;*******************************************************************************
; Rotina ATRASO
; Gera um atraso correspondente a 1,6 ms
; para o microcontrolador operando a um clock
; de 4MHz    
;*******************************************************************************   

ATRASO
    MOVLW 0xFF  ; Executa 255 vezes 4 instru��es nop
    MOVWF TEMP1
LOOP2
    NOP                  ; Gasta tempo de 4 NOP
    NOP
    NOP
    NOP
    DECFSZ TEMP1
    BRA LOOP2
    RETURN
    
;*******************************************************************************
; Rotina CONTA
; Atualiza valores em DISP1 e DISP2 para realizar
; a contagem de 00 a 99 nos displays    
;*******************************************************************************

CONTA
    MOVLW .9
    INCF DISP1
    CPFSGT DISP1
    RETURN
    CLRF DISP1
    INCF DISP2
    CPFSGT DISP2
    RETURN
    CLRF DISP2
    RETURN

;*******************************************************************************
; Rotina ATUALIZA_PORTD
; Transfere valores em DISP2 e DISP1 para os dois displays
; conectados � porta D        
;*******************************************************************************

ATUALIZA_PORTD    
    SWAPF DISP2,W
    IORWF DISP1,W
    MOVWF PORTD
    RETURN

;*******************************************************************************
; Rotina de atendimento � interrup��o externa INT0
; Toda vez que ocorre um evento de pressionar o 
; push button conectado ao pino RB0/INT0 dispara essa interrup��o   
;*******************************************************************************

INT_IRQ
	BCF INTCON,INT0IF ; limpa flag de interrup��o
        CLRF DISP1 ; Reseta contagem para 00
	CLRF DISP2
	CLRF PORTD ; Mostra valor correspondente nos displays
	RETFIE ; Retorna da interrup��o
END