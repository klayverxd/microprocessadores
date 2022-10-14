# Trabalho01 - Polling Button

[Microchip PIC18F Instruction Set](http://technology.niagarac.on.ca/staff/mboldin/18F_Instruction_Set/)

<img src="Trabalho01/imagem_2022-10-06_200824121.png" alt="proteus" width="500px">

TRISX -> Direção das portas, onde X é a porta (1 in, 0 out)

PORTAS B - ENTRADAS
MOVLW 0XFF
MOVWF TRISB

PORTAS D - SAIDAS
MOVLW 0
MOVWF TRISD
OU
CLRF TRISD

# Interrupções

<img src="display_button_int0_asm.X/img.png" alt="proteus" width="500px">

## Interrupções externas

### Prioridades
0X0008 - Alta
0X0018 - Baixa

Pinos de interrupção externa (Sensíveis à borda ~ subida ou descida)
- INT0 (RB0)
- INT1 (RB1)
- INT2 (RB2)

Registros de configuração
- INTCON
- INTCON1
- INTCON2

Bits de configuração

- INTXIE - Habilita INTX (Interruption enable)
- INTXIF - Sinaliza evento INTX (Interruption flag)
- IEDGX - Configura borda INTX
