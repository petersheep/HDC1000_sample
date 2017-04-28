#ifdef __XC16
#include <xc.h>
#endif
#include "I2C.h"

void I2C_init(void) {
#ifdef __XC16
    //I2Cの設定
    unsigned int config1 = 0x8000;
    unsigned int config2 = 157;
    OpenI2C1(config1, config2);
    IdleI2C1();
#endif
}

void I2C_start(void) {
#ifdef __XC16
    StartI2C1();
    //IFS1bits.MI2C1IF = 0;
    IdleI2C1();
#endif
}

void I2C_restart(void) {
#ifdef __XC16
    RestartI2C1();
    IdleI2C1();
#endif
}

void I2C_stop(void) {
#ifdef __XC16
    StopI2C1();
    //IFS1bits.MI2C1IF = 0;
    IdleI2C1();
#endif
}

int I2C_send(unsigned char data) {
    int ans = 0;
#ifdef __XC16
    ans = MasterWriteI2C1(data);
    while (I2C1STATbits.TBF) {
        //データの送信終了待ち
    }
    while (I2C1STATbits.ACKSTAT);
    //IFS1bits.MI2C1IF = 0;
    IdleI2C1();
#endif
    return ans;
}

unsigned char I2C_receive(int ack) {
    unsigned char data = 0;
#ifdef __XC16
    data = MasterReadI2C1();
    if (ack)
        AckI2C1();
    else
        NotAckI2C1();
    IdleI2C1();
#endif
    return data;
}

int I2C_puts(unsigned int len, unsigned char *data) {
    int n = 0;
#ifdef __XC16
    int i;
    for (i = 0; i < len; ++i) {
        if (I2C_send(data[i]) == 0) {
            ++n;
        }
    }
#else
    n = len;
#endif
    if (n == len) {
        return 0;
    }
    else {
        return -1;
    }
}

int I2C_gets(unsigned int len, unsigned char *data) {
#ifdef __XC16
    return MastergetsI2C1(len, data, 152);
#else
    return 0;
#endif
}
