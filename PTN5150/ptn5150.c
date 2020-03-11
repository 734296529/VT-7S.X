#include "ptn5150.h"
#include "stdio.h"

#define PTN5150_Address 0X3C
void Idle(void)//I2C���м��
{
    while((SSP2CON2 & 0X1F) | (SSP2STATbits.R_nW))
        continue;
}
/*
 * ����: ����������д��������
 * ����: Address д��ĵ�ַ(�Ĵ�����ַ) 
 *       Data    д�������
 *       Num     д����ֽ���
 */
void write_nbyte(u8 Address,u8 Data[],u8 Num)
{
    u8 i;
    SSP2CON2bits.SEN = 1;           //������ʼ����
    while(SSP2CON2bits.SEN);        //SEN��Ӳ���Զ�����ǰѭ���ȴ�
    SSP2BUF = PTN5150_Address;      //���ʹ�������ַ
    Idle();                         //���м��
    if(!SSP2CON2bits.ACKSTAT) ;     //�Ƿ���Ӧ��
    else                            //ACKSTAT=1,��������Ӧ��ֱ�ӷ���
        return;
    SSP2BUF = Address;              //��ַд��SSPBUF
    Idle();
    if(!SSP2CON2bits.ACKSTAT);      //Ӧ��λ��⣬ACKSTAT=0 ��������Ӧ��
    else                            //ACKSTAT=1 ��������Ӧ��ֱ�ӷ���
        return;                     
    for(i=0;i<Num;i++)
    {
        SSP2BUF = Data[i];          //����д��SSPBUF
        Idle();                     //���м��
        if(!SSP2CON2bits.ACKSTAT);  //Ӧ��λ��⣬ACKSTAT=0 ��������Ӧ��
        else
            return;                 //ACKSTAT=1 ��������Ӧ��ֱ�ӷ���
    }
    SSP2CON2bits.PEN = 1;           //��ʼ���ظ�ֹͣλ
    while(SSP2CON2bits.PEN);        //PEN��Ӳ���Զ�����֮ǰѭ��
    for(;;)
    {
        SSP2CON2bits.SEN = 1;       //������ʼλ
        while(SSP2CON2bits.SEN);    //SEN��Ӳ���Զ�����ǰѭ���ȴ�
        SSP2BUF = PTN5150_Address;  //���ʹ�������ַ
        Idle();                     //���м��
        SSP2CON2bits.PEN = 1;       //����ֹͣλ
        while(SSP2CON2bits.PEN);    //PEN��Ӳ���Զ�����֮ǰѭ��
        if(!SSP2CON2bits.ACKSTAT)   //Ӧ��λ��⣬ACKSTAT=0 ��������Ӧ��
            break;                  //ACKSTAT=1 ��������Ӧ��ֱ�ӷ���
    }
}

/*
 * ����: ��������ж����������
 * ����: Address �����ĵ�ַ(�Ĵ�����ַ) 
 *       Data    ��Ŷ���������
 *       Num     �������ֽ���
 */
void read_nbyte(u8 Address,u8 Data[],u8 Num)
{
    u8 i;
    SSP2CON2bits.SEN = 1;       //������ʼ����
    while(SSP2CON2bits.SEN);    //SEN��Ӳ���Զ�����ǰѭ���ȴ�
    SSP2BUF = PTN5150_Address;  //���ʹ�������ַ
    Idle();                     //���м��
    if(!SSP2CON2bits.ACKSTAT);  //Ӧ��λ��⣬ACKSTAT=0 ��������Ӧ��
    else                        //ACKSTAT=1,��������Ӧ��ֱ�ӷ���
        return;
    SSP2BUF = Address;          //��ַд��SSPBUF
    Idle();
    if(!SSP2CON2bits.ACKSTAT);  //Ӧ��λ��⣬ACKSTAT=0 ��������Ӧ��
    else                        //ACKSTAT=1 ��������Ӧ��ֱ�ӷ���
        return;
    for(i=0;i<Num;i++)
    {
        SSP2CON2bits.RSEN = 1;          //�ظ�START״̬
        while(SSP2CON2bits.RSEN);       //�ȴ�START״̬����
        SSP2BUF = PTN5150_Address+1;    //���ʹ�������ַ(����ַ)
        Idle();                         //���м��
        if(!SSP2CON2bits.ACKSTAT);      //Ӧ��λ��⣬ACKSTAT=0 ��������Ӧ��
        else                            //ACKSTAT=1 ��������Ӧ��ֱ�ӷ���
            return;
        SSP2CON2bits.RCEN = 1;          //�������
        while(SSP2CON2bits.RCEN);       //�ȴ����ս���
        SSP2CON2bits.ACKDT = 1;         //���ս����󲻷���Ӧ��λ
        SSP2CON2bits.ACKEN = 1;
        while(SSP2CON2bits.ACKEN);      //ACKEN��Ӳ���Զ�����ǰѭ���ȴ�
        Data[i] = SSP2BUF;              //����SSPBUF����
    }
    SSP2CON2bits.PEN = 1;       //����ֹͣλ
    while(SSP2CON2bits.PEN);    //PEN��Ӳ���Զ�����֮ǰѭ��  
}
