#include  "Landzo_servomotor.h"
#include "CHILDREN.H"

#ifdef __SON__
#define MIDSTRING1  7440        //S3010�����ֵ
//#define MIDSTRING1  8210
#elif defined __DAUGHTER__
#define MIDSTRING1  7620        //SD5  �����ֵ
//#define MIDSTRING1  7450
#endif

//#define FTM_CnV_REG(base,index)                  ((base)->CONTROLS[index].CnV)
/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�Servo_motor_S3010_init
*  ����˵����S3010�ŷ�����ʼ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-12
*  ��    ע��
*************************************************************************/
void Servo_motor_S3010_init(void)
{
	ftm_pwm_init(FTM1, FTM_CH0 , 100,10);                           //���ռ�ձ����ó�ʼ��   MOD =19531 ;
	FTM_CnV_REG(FTMN[FTM1], FTM_CH0)=MIDSTRING1;
}

/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�Servo_motor_S3010_centre
*  ����˵����S3010�ŷ������г���
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-12
*  ��    ע��
*************************************************************************/
void Servo_motor_S3010_centre(void)
{
	uint16_t TurnPWM = MIDSTRING1;

	FTM_CnV_REG(FTMN[FTM1], FTM_CH0) = TurnPWM ;

}



/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�Servo_motor_S3010_test
*  ����˵����S3010�ŷ������Գ���
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-9-12
*  ��    ע��
*************************************************************************/
void Servo_motor_S3010_test(int16 tep)
{
  if(tep>=42)
	tep=42;
  if(tep<=-42)
	tep=-42;
  uint16_t TurnPWM;

  TurnPWM = MIDSTRING1 + tep*20;
  FTM_CnV_REG(FTMN[FTM1], FTM_CH0) = TurnPWM ;
}