#include "ultrasonic.h"

#include "include.h"

void ultrasonic_init()
{
	gpio_init(US_TRIG,GPO,0);
	port_init(US_ECHO,IRQ_EITHER|PULLDOWN|ALT1);
}

void ultrasonic_start()
{
	gpio_set(US_TRIG,1);
	dwt_delay_us(11);
	gpio_set(US_TRIG,0);
	
	enable_irq(PORTD_IRQn);
}

uint32 USValueLast=0;
uint32 USValuePrev=0;
uint32 UltraSonicDistance=0;

void PORTD_IRQHandler(void)
{
	uint8  n = 0;    //引脚号

	n = 2;
	if(PORTD_ISFR & (1 << n))           //PTD2触发中断
	{
		PORTD_ISFR  = (1 << n);        //写1清中断标志位
		
		/*  以下为用户任务  */
		uint32 USAverage=0;
		if(gpio_get(US_ECHO))
		{
			pit_time_start  (PIT2); 
		}
		else
		{
			uint32 tmp=pit_time_get_us(PIT2)*340/20000;
			USAverage=(USValueLast+USValuePrev+tmp)/3;
			if(((tmp-USAverage)*(tmp-USAverage)+(USValueLast-USAverage)*(USValueLast-USAverage)+(USValuePrev-USAverage)*(USValuePrev-USAverage))<400)
			{
				UltraSonicDistance=tmp;
			}
			USValuePrev=USValueLast;
			USValueLast=tmp;
//			printf("%3dcm\n\n",UltraSonicDistance);
		}
		/*  以上为用户任务  */
	}
}
