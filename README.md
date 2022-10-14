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
