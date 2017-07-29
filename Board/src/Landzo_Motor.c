#include  "Landzo_motor.h"

//extern uint32_t count_init[16];


/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�Motor_double_PWM_Init
*  ����˵�������������ʼ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-5
*  ��    ע��
*************************************************************************/

void Motor_double_PWM_init(void)
{
	ftm_pwm_init(FTM0 , FTM_CH0, 80000,0);                        //���ռ�ձ����ó�ʼ��   MOD =313 ;  ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
	ftm_pwm_init(FTM0 , FTM_CH1, 80000,0);                        //���ռ�ձ����ó�ʼ��   MOD =313 ;  ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
	ftm_pwm_init(FTM0 , FTM_CH2, 80000,0);                        //���ռ�ձ����ó�ʼ��   MOD =313 ;  ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
	ftm_pwm_init(FTM0 , FTM_CH3, 80000,0);                        //���ռ�ձ����ó�ʼ��   MOD =313 ;  ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
}


/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�Motor_double_test
*  ����˵�������������ʼ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-11
*  ��    ע��
*************************************************************************/
void Motor_double_test(uint16 speedL,uint16 speedR)
{

		ftm_pwm_duty(FTM0 , FTM_CH0,0);
		ftm_pwm_duty(FTM0 , FTM_CH1,speedL);
		ftm_pwm_duty(FTM0 , FTM_CH2,0);
		ftm_pwm_duty(FTM0 , FTM_CH3,speedR);

}
