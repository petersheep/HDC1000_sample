/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

#include "system_config.h"
#include "system.h"
#include <xc.h>
#include <stdbool.h>

/** CONFIGURATION Bits **********************************************/
/*
#pragma config GWRP = OFF
#pragma config GSS = OFF
#pragma config GSSK = OFF
#pragma config FNOSC = PRIPLL
#pragma config IESO = OFF
#pragma config POSCMD = HS
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = ON
#pragma config FCKSM = CSDCMD
#pragma config FWDTEN = OFF
#pragma config ICS = PGD2
#pragma config JTAGEN = OFF
*/

void SYSTEM_Initialize (void)
{
    AD1PCFG = 0xFFFF; //Never use AD converter
    
    TRISAbits.TRISA0= 1;   //for measuring battery voltage  

    TRISBbits.TRISB0 = 1;   //State of wireless module
    TRISBbits.TRISB1 = 0;   //RESET pin of wireless module.
    //LATBbits.LATB1 = 0;     //wake_sw : active
    TRISAbits.TRISA2 = 0;   //9:wake_up pin of wireless module
    LATAbits.LATA2 = 1;     

    TRISBbits.TRISB2 = 1;   //P6: set to Input  ffor UART1 Rx
    PORTBbits.RB2 = 1;
    TRISBbits.TRISB3 = 0;   //P7: set to Output for UART1 Tx

    TRISBbits.TRISB15 = 1;   //P15: set to Output for UART2 Rx
    TRISBbits.TRISB14 = 0;   //P14: set to Input  for UART2 Tx

    TRISAbits.TRISA3 = 0;   //P10: set to Output for high side switch
    LATAbits.LATA3 = 0;     //turn off high side switch

    TRISBbits.TRISB5 = 0;   //P14: wake_measurement module
    LATBbits.LATB5 = 1;     //

    TRISBbits.TRISB13 = 1;   //P24: set to Input for analog in

    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB10 = 0;

    TRISBbits.TRISB7 = 0;   //set 
    RPINR20bits.SDI1R = 11; // SDI??RP7??
    RPOR5bits.RP10R = 8;    // SCK1??RP2??
    RPOR3bits.RP7R = 7;     // SDO1??RP3??
    
}

void USER_SdSpiConfigurePins_1 (void)
{
    /*
    // Deassert the chip select pin
    LATBbits.LATB1 = 1;
    // Configure CS pin as an output
    TRISBbits.TRISB1 = 0;
    // Configure CD pin as an input
    TRISFbits.TRISF0 = 1;
    // Configure WP pin as an input
    TRISFbits.TRISF1 = 1;
    */
    // Deassert the chip select pin
    LATBbits.LATB9 = 1;
    // Configure CS pin as an output
    TRISBbits.TRISB9 = 0;
    // Configure CD pin as an input
    TRISBbits.TRISB8 = 1;
    // Configure WP pin as an input
    //TRISBbits.TRISB9 = 1;
}

inline void USER_SdSpiSetCs_1(uint8_t a)
{
    LATBbits.LATB9 = a;
}

inline bool USER_SdSpiGetCd_1(void)
{    //TRISBbits.TRISB9 = 1;

    return (!PORTBbits.RB8) ? true : false;
}

inline bool USER_SdSpiGetWp_1(void)
{
    //return (PORTBbits.RB9) ? true : false;
    return false;
}