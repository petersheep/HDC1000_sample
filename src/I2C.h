/* 
 * File:   I2C.h
 * Author: NAOYA
 *
 * Created on 2017/04/05, 14:59
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

// 定数の定義
#define ACK   0
#define NOACK 1
#define RW_0  0
#define RW_1  1

//#define I2C_MSSP2_USE    // MSSP2を利用する場合はコメントを外します。
// ＭＳＳＰモジュールのレジスター定義
#if defined(_16F1933)||defined(_16F1934)||defined(_16F1936)||\
    defined(_16F1937)||defined(_16F1938)||defined(_16F1939)
// 16F193x用のMSSPを利用する場合の定義
#define I2C_SSPCON1         SSPCON1
#define I2C_SSPCON2         SSPCON2
#define I2C_SSPSTAT         SSPSTAT
#define I2C_SSPADD          SSPADD
#define I2C_SSPBUF          SSPBUF
#define I2C_SSPIF           SSPIF
#define I2C_SSPIE           SSPIE
#define I2C_BCLIF           BCLIF
#define I2C_BCLIE           BCLIE
#define I2C_SSPSTAT_SMP     SSPSTATbits.SMP
#define I2C_SSPCON2_SEN     SSPCON2bits.SEN
#define I2C_SSPCON2_RSEN    SSPCON2bits.RSEN
#define I2C_SSPCON2_PEN     SSPCON2bits.PEN
#define I2C_SSPCON2_RCEN    SSPCON2bits.RCEN
#define I2C_SSPCON2_ACKSTAT SSPCON2bits.ACKSTAT
#define I2C_SSPCON2_ACKDT   SSPCON2bits.ACKDT
#define I2C_SSPCON2_ACKEN   SSPCON2bits.ACKEN
#else
#ifdef  I2C_MSSP2_USE
// MSSP2を利用する場合の定義
#define I2C_SSPCON1         SSP2CON1
#define I2C_SSPCON2         SSP2CON2
#define I2C_SSPSTAT         SSP2STAT
#define I2C_SSPADD          SSP2ADD
#define I2C_SSPBUF          SSP2BUF
#define I2C_SSPIF           SSP2IF
#define I2C_SSPIE           SSP2IE
#define I2C_BCLIF           BCL2IF
#define I2C_BCLIE           BCL2IE
#define I2C_SSPSTAT_SMP     SSP2STATbits.SMP
#define I2C_SSPCON2_SEN     SSP2CON2bits.SEN
#define I2C_SSPCON2_RSEN    SSP2CON2bits.RSEN
#define I2C_SSPCON2_PEN     SSP2CON2bits.PEN
#define I2C_SSPCON2_RCEN    SSP2CON2bits.RCEN
#define I2C_SSPCON2_ACKSTAT SSP2CON2bits.ACKSTAT
#define I2C_SSPCON2_ACKDT   SSP2CON2bits.ACKDT
#define I2C_SSPCON2_ACKEN   SSP2CON2bits.ACKEN
#else
// MSSP1を利用する場合の定義
#define I2C_SSPCON1         SSP1CON1
#define I2C_SSPCON2         SSP1CON2
#define I2C_SSPSTAT         SSP1STAT
#define I2C_SSPADD          SSP1ADD
#define I2C_SSPBUF          SSP1BUF
#define I2C_SSPIF           SSP1IF
#define I2C_SSPIE           SSP1IE
#define I2C_BCLIF           BCL1IF
#define I2C_BCLIE           BCL1IE
#define I2C_SSPSTAT_SMP     SSP1STATbits.SMP
#define I2C_SSPCON2_SEN     SSP1CON2bits.SEN
#define I2C_SSPCON2_RSEN    SSP1CON2bits.RSEN
#define I2C_SSPCON2_PEN     SSP1CON2bits.PEN
#define I2C_SSPCON2_RCEN    SSP1CON2bits.RCEN
#define I2C_SSPCON2_ACKSTAT SSP1CON2bits.ACKSTAT
#define I2C_SSPCON2_ACKDT   SSP1CON2bits.ACKDT
#define I2C_SSPCON2_ACKEN   SSP1CON2bits.ACKEN
#endif
#endif


void I2C_init(void);
void I2C_start(void);
void I2C_restart(void) ;
void I2C_stop(void) ;
void I2C_send(unsigned char data);
int  I2C_receive(void);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

