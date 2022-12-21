#include "./yushichecng.h"
void main()
{
    u8 key;//用以接收按键输入的值
    External_Interrupt_0();//外部中断0初始化
    External_Interrupt_1();//外部中断1初始化
    Timer_Interrupt_0_1();//计时器中断0初始化
    while(1)
    {
        u8 i=0;
        for(i=0;i<8;i++)
        {
            scanpasswdcode[i]=changenum(scanpasswd[i]);//将用户输入化为对应的数码管编码初始为“--------”
        }
        display(scanpasswdcode,8);//将输入的密码显示
        key=key_matrix_ranks_scan_2();//获取按键输入的值
        if(key<10&&n!=7)//输入值小于10并且还未输入满八位时才允许输入
        {
            n++;//到scanpasswd[]的下一位
            scanpasswd[n]=key;//将获取的按键输入存到用户密码存储的数组里
        }
        if(n==7)//输入满八位
        {
            flag=check();//检查密码是否正确
            if(flag)//正确
            {
                while(flag_2)
                {
                    PassOrLock[0]=0x73;
                    display(PassOrLock,2);//输出’P‘
                }
            }
            else//不正确
            {
                while(flag_2)
                {
                    PassOrLock[0]=0x38;
                    display(PassOrLock,2);//输出’L‘
                    if(flag_1>=3&&flag==0)//如果错误已经大于等于三次，并且还错
                    {
                        flag_3=flag_1;//头文件有说flag_3是干嘛的
                        ET0=1;//打开定时器中断
                        TR0=1;//打开定时器
                        break;//退出循环到>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                    }                                              //
                }                                                  //
                while(flag_2)//这<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                {
                    PassOrLock[0]=0x38;//继续输出’L‘，跳出上一个循环是为了防止重复处罚导致无法在输入
                    display(PassOrLock,2);//处罚时间里一直在这个循环
                }
            }
            n=-1;
        }
        
        
    }
}
void extend_0() interrupt 0//中断0函数，清空重新输入
{
    u8 z=0;
    flag_2=0;//使数码管不在显示P
    for(z=0;z<8;z++)//将用户输入的密码清空，并使数码管恢复初始状态
    {
        scanpasswd[z]=16;
    }
    n=-1;//使n=-1，用户可以再次输入
}
void extend_1() interrupt 2//中断1函数，删除一个输入
{
    scanpasswd[n]=16;
    if(n>=0)
    n--;
    else
    n=-1;
}
void Timer() interrupt 1//定时器中断0函数，用以密码输入错误处罚
{
    static int t=0;
    t++;
    EX0=0;//关闭清空按钮
    EX1=0;//关闭删除按钮
    TH0=0xfc;//1ms一个中断
    TL0=0x18;
    if(t==2000)//2000个1ms=2s后
    {
        t=0;
        flag_3--;//处罚力度-1
    }
    if(flag_3==0)//处罚力度为0时解除处罚
    {
        EX0=1;//开启清除按钮
        EX1=1;//开启删除按钮
        n=-1;//使用户可以重新输入
        ET0=0;//关闭计时器中断
        TR0=0;//关闭计时器
    }
    
}