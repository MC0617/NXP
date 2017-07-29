#include "include.h"
#include "bt_communication.h"
#include "CHILDREN.H"

uint8 bt_init(void)
{
	uint8 RunFlagTmp=0;
	char bt_rec=0;
	uint8 ConnectFlag=0;
	//�ȴ�1��ʱ��Ҫһֱ�������ݣ������������ӻ�Ͽ�
	while(!TIME1flag_1s)
	{
		uart_querychar(UART5,&bt_rec);
		uart_putchar(UART5,0xff);
	}
	
	//����Ƿ�����
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
	
	//����Ѿ����ӣ�����
	bt_rec=0;
	if(ConnectFlag)
	{
		while(bt_rec!='R')
		{
			while( uart_querychar (UART5,&bt_rec) != 1)     //��ѯ����1���ַ������浽 bt_rec��
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
	
   PIT_Flag_Clear(PIT1);       //�嶨ʱ��1�жϱ�־λ
	TIME1flag_1s = 0;
	TIME1flag_1s5 = 0;
	TIME1flag_2s = 0;
	TIME1flag_2s5 = 0;
	return RunFlagTmp;
}