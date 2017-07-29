#include  "Landzo_motor.h"

//extern uint32_t count_init[16];


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Motor_double_PWM_Init
*  功能说明：电机驱动初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-5
*  备    注：
*************************************************************************/

void Motor_double_PWM_init(void)
{
	ftm_pwm_init(FTM0 , FTM_CH0, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
	ftm_pwm_init(FTM0 , FTM_CH1, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
	ftm_pwm_init(FTM0 , FTM_CH2, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
	ftm_pwm_init(FTM0 , FTM_CH3, 80000,0);                        //电机占空比设置初始化   MOD =313 ;  占空比 = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
}


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Motor_double_test
*  功能说明：电机驱动初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-11
*  备    注：
*************************************************************************/
void Motor_double_test(uint16 speedL,uint16 speedR)
{

		ftm_pwm_duty(FTM0 , FTM_CH0,0);
		ftm_pwm_duty(FTM0 , FTM_CH1,speedL);
		ftm_pwm_duty(FTM0 , FTM_CH2,0);
		ftm_pwm_duty(FTM0 , FTM_CH3,speedR);

}
