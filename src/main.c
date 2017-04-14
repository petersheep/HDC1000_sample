/******************************************************************************
 *
 * PIC24 DATALOGGER BOARD
 *
 * Author   Naoya Miyamoro
 * date     20170405
 * 
 * Summary:
 *
 * Operation
 *
 * Hardware connection
 * 
********************************************************************/
#include <stdio.h>
#include "HDC1000.h"            // HDC1000用関数ライブラリ
#include "uart1_serial.h"
#include "system.h"
#include "I2C.h"
#include "config.h"
#include "delay.h"

/*******************************************************************************
*  メインの処理                                                                *
*******************************************************************************/
int main(void)
{
    
    config_init();
	SYSTEM_Initialize();
    uart1_init();
    I2C_init();
    
    int  ans ;

     // 湿度センサーの初期化を行う
     ans = HDC_Init(HDC1000_ID,HDC1000_ADRS) ;


    delay_ms(3000) ;       // ３秒後に開始

     while(1) {
          // 湿度センサーから湿度・温度値を読出す
          ans = HDC_Read() ;
     }
    return 0;
}

