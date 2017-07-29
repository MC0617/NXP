#include  "Landzo_servomotor.h"
#include "CHILDREN.H"

#ifdef __SON__
#define MIDSTRING1  7440        //S3010舵机中值
//#define MIDSTRING1  8210
#elif defined __DAUGHTER__
#define MIDSTRING1  7620        //SD5  舵机中值
//#define MIDSTRING1  7450
#endif

//#define FTM_CnV_REG(base,index)                  ((base)->CONTROLS[index].CnV)
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_S3010_init
*  功能说明：S3010伺服机初始化程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_S3010_init(void)
{
	ftm_pwm_init(FTM1, FTM_CH0 , 100,10);                           //舵机占空比设置初始化   MOD =19531 ;
	FTM_CnV_REG(FTMN[FTM1], FTM_CH0)=MIDSTRING1;
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_S3010_centre
*  功能说明：S3010伺服机对中程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
*************************************************************************/
void Servo_motor_S3010_centre(void)
{
	uint16_t TurnPWM = MIDSTRING1;

	FTM_CnV_REG(FTMN[FTM1], FTM_CH0) = TurnPWM ;

}



/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：Servo_motor_S3010_test
*  功能说明：S3010伺服机测试程序
*  参数说明：
*  函数返回：无
*  修改时间：2014-9-12
*  备    注：
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