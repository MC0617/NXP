#include "Landzo_MeasureSpeed.h"


extern uint32_t count_init[16];

/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�MeasureSpeed_one_init
*  ����˵������������ٳ�ʼ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-11
*  ��    ע��
*************************************************************************/
void MeasureSpeed_one_init(void)
{
//  FTM_IRQ_DIS(FTM2,FTM_CH0) ;
//	gpio_init (PTC4, GPO,HIGH);                            //���ʹ��
//
//	ftm_pwm_init(FTM0 , FTM_CH1, 8000,0);       //���ռ�ձ����ó�ʼ��    ռ�ձ� = duty /(MOD +1 ) ;FTM_CnV_REG(FTMx[ftmn], ch) = cv;
//	ftm_pwm_init(FTM0 , FTM_CH2, 8000,0);
//
//	lptmr_pulse_init(LPT0_ALT2, LIN_COUNT,LPT_Rising)  ;   //��ʼ����������� ��PTC5���벶��ţ�LIN_cout =100�������ز���
//  ftm_input_init(FTM2,FTM_CH0,FTM_Rising,FTM_PS_2);
//  set_vector_handler(FTM2_IRQn , FTM2_Input_test_handler);
//  enable_irq (FTM2_IRQn);                                     //ʹ��FTM0�ж�

}



/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�MeasureSpeed_one_test
*  ����˵������������ٳ���
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-11
*  ��    ע��
*************************************************************************/
uint16_t MeasureSpeed_one_test(void)
{
	uint16_t count=0;
//	extern vuint8 LPT_INT_count;
//
//	ftm_pwm_duty(FTM0 , FTM_CH1,0);
//	ftm_pwm_duty(FTM0 , FTM_CH2,20);
//
//	count = lptmr_pulse_get();                                                     //�����������������ֵ
//	count = LPT_INT_count * LIN_COUNT +  count;
count =ftm_input_get(FTM2,FTM_CH0);
ftm_input_clean(FTM2);
	return count;
}
