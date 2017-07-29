#include "include.h"
#include "bt_communication.h"
#include "CHILDREN.H"

uint8 bt_init(void)
{
	uint8 RunFlagTmp=0;
	char bt_rec=0;
	uint8 ConnectFlag=0;
	//等待1秒时需要一直发送数据，否则蓝牙连接会断开
	while(!TIME1flag_1s)
	{
		uart_querychar(UART5,&bt_rec);
		uart_putchar(UART5,0xff);
	}
	
	//检测是否连接
	bt_rec=0;
	while(bt_rec!=0xf0)
	{
		while( uart_querychar (UART5,&bt_rec) != 1)    
		{
			uart_putchar(UART5,0xf0);
		}
	}
	uart_putchar(UART5,0xf0);
	if(bt_rec==0xf0)
	{
		ConnectFlag=1;
	}
	
	//如果已经连接，启动
	bt_rec=0;
	if(ConnectFlag)
	{
		while(bt_rec!='R')
		{
			while( uart_querychar (UART5,&bt_rec) != 1)     //查询接收1个字符，保存到 bt_rec里
			{
				uart_putchar(UART5,'R');
			}
		}
		uart_putchar(UART5,'R');

		if(bt_rec=='R'||bt_rec=='G')
		{
			RunFlagTmp=1;
		}

#ifdef __SON__
		pit_delay_ms(PIT3,10);
#elif defined __DAUGHTER__
		pit_delay_ms(PIT3,500);
#endif
	}
	bt_rec=0;
	
   PIT_Flag_Clear(PIT1);       //清定时器1中断标志位
	TIME1flag_1s = 0;
	TIME1flag_1s5 = 0;
	TIME1flag_2s = 0;
	TIME1flag_2s5 = 0;
	return RunFlagTmp;
}