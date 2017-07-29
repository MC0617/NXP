#include "Landzo_MeasureSpeed.h"


extern uint32_t count_init[16];

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：MeasureSpeed_one_init
*  功能说明：单电机测速初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
void MeasureSpeed_one_init(void)
{
//  FTM_IRQ_DIS(FTM2,FTM_CH0) ;
//	gpio_init (PTC4, GPO,HIGH);                            //电机使能
//
//	ftm_pwm_init(FTM0 , FTM_CH1, 8000,0);       //电机占空比设置初始化    占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
//	ftm_pwm_init(FTM0 , FTM_CH2, 8000,0);
//
//	lptmr_pulse_init(LPT0_ALT2, LIN_COUNT,LPT_Rising)  ;   //初始化脉冲计数器 ，PTC5输入捕获脚，LIN_cout =100，上升沿捕获
//  ftm_input_init(FTM2,FTM_CH0,FTM_Rising,FTM_PS_2);
//  set_vector_handler(FTM2_IRQn , FTM2_Input_test_handler);
//  enable_irq (FTM2_IRQn);                                     //使能FTM0中断

}



/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：MeasureSpeed_one_test
*  功能说明：单电机测速程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
uint16_t MeasureSpeed_one_test(void)
{
	uint16_t count=0;
//	extern vuint8 LPT_INT_count;
//
//	ftm_pwm_duty(FTM0 , FTM_CH1,0);
//	ftm_pwm_duty(FTM0 , FTM_CH2,20);
//
//	count = lptmr_pulse_get();                                                     //保存脉冲计数器计算值
//	count = LPT_INT_count * LIN_COUNT +  count;
count =ftm_input_get(FTM2,FTM_CH0);
ftm_input_clean(FTM2);
	return count;
}
