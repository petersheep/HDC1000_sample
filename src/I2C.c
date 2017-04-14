
/*******************************************************************************
                               *
*******************************************************************************/
#include <xc.h>
#include "I2C.h"

void I2C_init(void){
    //I2Cの設定
    I2C1BRG = 157; //100KHz @fcy=16MHz
    I2C1MSK = 0;
    I2C1CON = 0x8000; //I2C1イネーブル(PORTB設定前にすること)
}

void I2C_start(void) {
    I2C1CONbits.SEN = 1; //スタート
    while (I2C1CONbits.SEN) {
        //スタート終了待ち
    }
}

void I2C_restart(void) {
    I2C1CONbits.RSEN = 1; //リスタート
    while (I2C1CONbits.RSEN) {
        //リスタート終了待ち
    }
}

void I2C_stop(void) {
    I2C1CONbits.PEN = 1; //ストップ
    while (I2C1CONbits.PEN) {
        //ストップコンディション終了待ち
    }
}

void I2C_send(unsigned char data) {
    char i;
    I2C1TRN = data;
    while (I2C1STATbits.TRSTAT) {
        //データの送信終了待ち
    }
    
    
    for(i=0;i<20;i++){
        //ちょっと待つ
    }
}

int I2C_receive(void){
    I2C1CONbits.RCEN = 1; //データ受信
    while (I2C1CONbits.RCEN) {
        //受信終了待ち
    }
    return (I2C1RCV); //EEP読み出し値を返り値にセット    
}