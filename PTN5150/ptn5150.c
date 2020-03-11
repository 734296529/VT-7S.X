#include "ptn5150.h"
#include "stdio.h"

#define PTN5150_Address 0X3C
void Idle(void)//I2C空闲检测
{
    while((SSP2CON2 & 0X1F) | (SSP2STATbits.R_nW))
        continue;
}
/*
 * 功能: 往从器件中写入多个数据
 * 参数: Address 写入的地址(寄存器地址) 
 *       Data    写入的数据
 *       Num     写入的字节数
 */
void write_nbyte(u8 Address,u8 Data[],u8 Num)
{
    u8 i;
    SSP2CON2bits.SEN = 1;           //发送起始命令
    while(SSP2CON2bits.SEN);        //SEN被硬件自动清零前循环等待
    SSP2BUF = PTN5150_Address;      //发送从器件地址
    Idle();                         //空闲检测
    if(!SSP2CON2bits.ACKSTAT) ;     //是否有应答
    else                            //ACKSTAT=1,从器件无应答，直接返回
        return;
    SSP2BUF = Address;              //地址写入SSPBUF
    Idle();
    if(!SSP2CON2bits.ACKSTAT);      //应答位检测，ACKSTAT=0 从器件有应答
    else                            //ACKSTAT=1 从器件无应答，直接返回
        return;                     
    for(i=0;i<Num;i++)
    {
        SSP2BUF = Data[i];          //数据写入SSPBUF
        Idle();                     //空闲检测
        if(!SSP2CON2bits.ACKSTAT);  //应答位检测，ACKSTAT=0 从器件有应答
        else
            return;                 //ACKSTAT=1 从器件无应答，直接返回
    }
    SSP2CON2bits.PEN = 1;           //初始化重复停止位
    while(SSP2CON2bits.PEN);        //PEN被硬件自动清零之前循环
    for(;;)
    {
        SSP2CON2bits.SEN = 1;       //发送起始位
        while(SSP2CON2bits.SEN);    //SEN被硬件自动清零前循环等待
        SSP2BUF = PTN5150_Address;  //发送从器件地址
        Idle();                     //空闲检测
        SSP2CON2bits.PEN = 1;       //发送停止位
        while(SSP2CON2bits.PEN);    //PEN被硬件自动清零之前循环
        if(!SSP2CON2bits.ACKSTAT)   //应答位检测，ACKSTAT=0 从器件有应答
            break;                  //ACKSTAT=1 从器件无应答，直接返回
    }
}

/*
 * 功能: 向从器件中读出多个数据
 * 参数: Address 读出的地址(寄存器地址) 
 *       Data    存放读出的数据
 *       Num     读出的字节数
 */
void read_nbyte(u8 Address,u8 Data[],u8 Num)
{
    u8 i;
    SSP2CON2bits.SEN = 1;       //发送起始命令
    while(SSP2CON2bits.SEN);    //SEN被硬件自动清零前循环等待
    SSP2BUF = PTN5150_Address;  //发送从器件地址
    Idle();                     //空闲检测
    if(!SSP2CON2bits.ACKSTAT);  //应答位检测，ACKSTAT=0 从器件有应答
    else                        //ACKSTAT=1,从器件无应答，直接返回
        return;
    SSP2BUF = Address;          //地址写入SSPBUF
    Idle();
    if(!SSP2CON2bits.ACKSTAT);  //应答位检测，ACKSTAT=0 从器件有应答
    else                        //ACKSTAT=1 从器件无应答，直接返回
        return;
    for(i=0;i<Num;i++)
    {
        SSP2CON2bits.RSEN = 1;          //重复START状态
        while(SSP2CON2bits.RSEN);       //等待START状态结束
        SSP2BUF = PTN5150_Address+1;    //发送从器件地址(读地址)
        Idle();                         //空闲检测
        if(!SSP2CON2bits.ACKSTAT);      //应答位检测，ACKSTAT=0 从器件有应答
        else                            //ACKSTAT=1 从器件无应答，直接返回
            return;
        SSP2CON2bits.RCEN = 1;          //允许接收
        while(SSP2CON2bits.RCEN);       //等待接收结束
        SSP2CON2bits.ACKDT = 1;         //接收结束后不发送应答位
        SSP2CON2bits.ACKEN = 1;
        while(SSP2CON2bits.ACKEN);      //ACKEN被硬件自动清零前循环等待
        Data[i] = SSP2BUF;              //读出SSPBUF数据
    }
    SSP2CON2bits.PEN = 1;       //发送停止位
    while(SSP2CON2bits.PEN);    //PEN被硬件自动清零之前循环  
}
