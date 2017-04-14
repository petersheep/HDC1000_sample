/*
 * File:   HDC1000.c
 * Author: NAOYA
 *
 * Created on 2017/04/05, 14:51
 */

#include <xc.h>
#include <math.h>
#include "HDC1000.h"
#include "I2C.h"
#include "delay.h"

static int Sensor_adrs ;      // デバイスのI2Cアドレスを保存する変数

float Humi ;                       // 湿度の値を保存する変数
float Temp ;                       // 温度の値を保存する変数

/*******************************************************************************
*  ans = HDC_Init(id, address)                                                 *
*    デバイスの初期化を行う処理                                                *
*    デバイスの動作を確かめる為にデバイスIDのチェックを行います。              *
*    温度(14bit)･湿度(14bit)を個別に読出す様に設定を初期化します。             *
*    設定データを変更する場合は、HDC.hのCONFIG_DT_Hを書き換え変更して下さい。  *
*    id      : デバイスの識別IDを指定します                                    *
*    address : デバイス(スレーブ)のI2Cアドレスを指定します                     *
*    ans     : 0=正常　                                                        *
*              1=異常(相手からACKが返ってこない)                               *
*              6=デバイスのIDチェックエラー                                    *
*******************************************************************************/
int HDC_Init(int id ,int address)
{
     union {
          unsigned int  i ;
          unsigned char c[2] ;
     } data ;
     int  ans ;

     Sensor_adrs = address ;

    
     delay_ms(15) ;
     // デバイスの識別ＩＤをチェックする処理
     ans = HDC_Receive(DEVICE_ID_ADRS,(unsigned char *)data.c) ;
     if (ans == 0) {
          if (data.i == HDC1000_ID) {
               // ＩＤは一致したならデバイスを初期化する処理
               data.c[0] = CONFIG_DT_H ;
               data.c[1] = CONFIG_DT_L ;
               HDC_Send(CONFIG_ADRS,data.c) ;
          } else ans = 6 ; // ＩＤが一致しない
     }
     return ans ;
}
/*******************************************************************************
*  ans = HDC_Receive(reg_adrs,*data)                                           *
*  デバイスのレジスターからデータを読込む処理                                  *
*    reg_adrs : 読出すデータのレジスターアドレスを指定する                     *
*    *data    : 読出したデータの格納先を指定する(2byte読込む)                  *
*    ans      : 0=正常　1=異常(相手からACKが返ってこない)                      *
*******************************************************************************/
int HDC_Receive(char reg_adrs,unsigned char *data)
{
    int  ans =0;
    I2C_start();
    I2C_send((Sensor_adrs<<1)+RW_0);
    I2C_send(reg_adrs);
    if ( (reg_adrs == TEMP_ADRS) || (reg_adrs == HUMI_ADRS) )  {
        delay_ms(7) ;
    }
    I2C_restart();
    I2C_send((Sensor_adrs<<1)+RW_1);
    
    
    I2C_stop();
    data++ ;
    *data = (char)I2C_receive() ;   // HIGHバイト読出し
    data-- ;
    *data = (char)I2C_receive() ; // LOWバイト読出し 

    return ans;
}
/*******************************************************************************
*  ans = HDC_Send(reg_adrs,*data)                                              *
*  デバイスのレジスターへデータを書込む処理                                    *
*    reg_adrs : 書出すデータのレジスターアドレスを指定する                     *
*    *data    : 書出すデータの格納先を指定する(2byte書込む)                    *
*    ans      : 0=正常　1=異常(相手からACKが返ってこない)                      *
*******************************************************************************/
int HDC_Send(char reg_adrs,unsigned char *data)
{
    int  ans , i ;
    ans=0;
    
    I2C_start();
    I2C_send((Sensor_adrs<<1)+RW_0);
    I2C_send(reg_adrs);
    I2C_send(reg_adrs) ;               // レジスタアドレスを指定
    for (i=0 ; i<2 ; i++) {
        I2C_send(*data);             // 指定個数分書き込む(送信する)
        data++ ;
    }
     I2C_stop() ;                            // ストップコンディションを発行する
     return ans ;
}
/*******************************************************************************
*  ans = HDC_Read()                                                            *
*  湿度･温度を読込む処理                                                       *
*  読み込まれた湿度(％)はHumi変数に、温度値(℃)はTemp変数に其々格納されます。  *
*  この処理は約15ms程時間が掛かります。                                        *
*    ans  : 0=正常　1=異常(相手からACKが返ってこない)                          *
*******************************************************************************/
int HDC_Read()
{
     union {
          unsigned int  i ;
          unsigned char c[2] ;
     } data ;
     int ans ;

     // 湿度データを受信する
     ans = HDC_Receive(HUMI_ADRS,(unsigned char *)data.c) ;
     if (ans == 0) {
          Humi = (float)data.i / 65536.0 ;
          Humi = Humi * 100.0 ;
          // 温度データを受信する
          ans = HDC_Receive(TEMP_ADRS,(unsigned char *)data.c) ;
          if (ans == 0) {
               Temp = (float)data.i / 65536.0 ;
               Temp = (Temp * 165.0) - 40.0 ;
          }
     }
     return ans ;
}
