//���ͷ�ļ�
#include "common.h"
#include "include.h"
#include "math.h"

#include "ultrasonic.h"
#include "bt_communication.h"
#include "caculation.h"
#include "CHILDREN.H"

uint8 RingFlag=0;
RUN_STATEn_e RunState;

uint8 TIME0flag_10ms=0;
uint8 TIME0flag_20ms=0;
uint8 TIME0flag_30ms=0;
uint8 TIME0flag_40ms=0;
uint8 TIME0flag_50ms=0;

uint8 TIME1flag_250ms=0;
uint8 TIME1flag_500ms=0;
uint8 TIME1flag_1s=0;
uint8 TIME1flag_1s5=0;
uint8 TIME1flag_2s=0;
uint8 TIME1flag_2s5=0;

//uint8 TIME2flag_1s=0;
//uint8 TIME2flag_2s=0;
//uint8 TIME2flag_1s5=0;
//uint8 TIME2flag_2s5=0;

////ȫ�ֱ�������
int16 SpeedCurrent=0;
volatile uint32 counter = 0,cnvtime=1;                //���벶׽ֵ
uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 imgbit[CAMERA_SIZE];
uint8 img[CAMERA_H][CAMERA_W];
char bt_rec;

//��������
void PIT2_IRQHandler(void);
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void Run(void);
uint16 SPEED_MAX,SPEED_MIN;
void  main(void)
{

	// ��ֹ���ж�
	DisableInterrupts;
	//��ʼ��
#ifdef __DAUGHTER__
	ultrasonic_init();
#endif
	key_init();															//���뿪�س�ʼ��
	uart_init(VCAN_PORT,VCAN_BAUD);										//����
	uart_init(BT_PORT,BT_BAUD);											//����
	Motor_double_PWM_init();											//���������ʼ��
	Servo_motor_S3010_init();											//���������ʼ��
	camera_init(imgbuff);												//����ͷ��ʼ��
	ftm_quad_init(FTM2);           									//��ʼ��FTM���������빦��
//	adc_init(ADC0_DP0);
	pit_init_ms(PIT0,20);
	pit_init_ms(PIT1,50);
//#ifdef __SON__
//	pit_init_ms(PIT2,2500);
//#elif defined __DAUGHTER__
//	pit_init_ms(PIT2,1500);
//#endif
	port_init_NoALT(PTD5,PULLUP);                                  	//����EN��
	port_init_NoALT(PTD4,PULLDOWN);                                	//����STATE��
//	//�����жϷ�����
	set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
	set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ PORTA_IRQHandler
	set_vector_handler(PIT0_VECTORn , PIT0_IRQHandler);
	set_vector_handler(PIT1_VECTORn , PIT1_IRQHandler);
	set_vector_handler(PORTD_VECTORn , PORTD_IRQHandler);
//	// �����ж�
	enable_irq(PIT0_IRQn);
	enable_irq(PIT1_IRQn);
	EnableInterrupts;

	uint8 RunFlag=0;
	RunFlag=bt_init();
//	RunFlag=1;
	RunState=RUN;
	
//	SPEED_MAX=(KeyValue&0x0f)*20+500;
	SPEED_MAX=500+(key_get()&0x0f)*20;
	SPEED_MIN=(uint16)(SPEED_MAX*0.8);
	while(RunFlag)
	{
		camera_get_img();                                   //����ͷ��ȡͼ��
		img_extract(img, imgbuff, CAMERA_SIZE);

		RingFlag=0;
		Run();

//		Motor_double_test(350,400);
//		Motor_double_test(800,800);
/*		
		for(uint16 i=0;i<20;i++)
		{
		  imgbuff[59*20+i]=0xff;
		}
		for(uint8 i=0;i<120;i++)
		{
		  imgbuff[i*20+9]|=0x01;
		}
		vcan_sendimg(BT_PORT,imgbuff, sizeof(imgbuff));
*/		
	}
}
int16 SpeedLast,SpeedPrev;
void Run(void)
{
	struct T_S tmp;
	tmp=GetTrack(img);

	uint8 KeyValue=0;
	char GetState=0;

	uart_querychar(UART5,&GetState);
	KeyValue=key_get();
	
	if(TIME0flag_20ms==1)
	{
		TIME0flag_20ms=0;
		SpeedCurrent=(int16)(ftm_quad_get(FTM2)*1.68);
		ftm_quad_clean(FTM2);
//		printf("%d\n",SpeedCurrent);
	}
	if(tmp.MotorSpeed<SPEED_MIN)
	{
		uart_putchar(UART5,'T');
		tmp.MotorSpeed=SPEED_MIN;
	}
	if(tmp.MotorSpeed>SPEED_MAX)
	{
		uart_putchar(UART5,'F');
		tmp.MotorSpeed=SPEED_MAX;
	}

	uint16 speedTmp;
	int16 SpeedDiffTmp=(SpeedCurrent+SpeedLast+SpeedPrev)/3;

	if(RingFlag)
	{
		RingFlag=0;
//		if(SpeedDiffTmp>(SPEED_MAX*0.8))
//		{
//			tmp.MotorSpeed=100;
//		}
//		else
//		{
			tmp.MotorSpeed=200;
			uart_putchar(UART5,'S');
//		}
	}
	else
	{
#ifdef __DAUGHTER__
		if(tmp.MotorSpeed==SPEED_MAX&&GetState=='F')
		{
			if(UltraSonicDistance>200)
			{
				tmp.MotorSpeed=SPEED_MAX+(UltraSonicDistance-150)*1;
			}
			if(UltraSonicDistance<100)
			{
				tmp.MotorSpeed=SPEED_MAX-(150-UltraSonicDistance)*1;
			}
		}
		else if(tmp.MotorSpeed==SPEED_MAX&&GetState=='S')
		{
			if(UltraSonicDistance<200)
			{
				tmp.MotorSpeed=tmp.MotorSpeed-(300-UltraSonicDistance);
			}
		}
		else
		{
			if(UltraSonicDistance<100)
			{
				tmp.MotorSpeed=tmp.MotorSpeed-(150-UltraSonicDistance);
			}
		}
#endif
	}
	tmp.MotorSpeed=(2*tmp.MotorSpeed-SpeedCurrent)>0?(2*tmp.MotorSpeed-SpeedCurrent):0;
	//	speedTmp=(tmp.MotorSpeed)*sqrt(tmp.MotorTurn>0?tmp.MotorTurn:-tmp.MotorTurn)*(SPEED_MAX/800);
	//	speedTmp=(tmp.MotorSpeed)*sqrt(ABS(tmp.MotorTurn/30))/2;
	//	speedTmp=(tmp.MotorSpeed-speedTmp)>0?(tmp.MotorSpeed-speedTmp):0;
	int16 turnTmp;
	SpeedPrev=SpeedLast;
	SpeedLast=SpeedCurrent;
	turnTmp=(int16)((tmp.MotorTurn/30)+((int8)(ABS(SpeedDiffTmp-SPEED_MIN))/(SPEED_MAX-SPEED_MIN))*((tmp.MotorTurn/30)*0.01));
	if(turnTmp>42)
	{
		turnTmp=42;
	}
	if(turnTmp<-42)
	{
		turnTmp=-42;
	}
	speedTmp=(uint16)(tmp.MotorSpeed-(tmp.MotorSpeed)*0.1*(turnTmp/42));

	if((KeyValue&0x40)==0x40)
	{
		Servo_motor_S3010_test(turnTmp);
	}
	else
	{
		Servo_motor_S3010_centre();
	}
	if(((KeyValue&0x80)!=0x80)||(RunState==STOP)&&STOP_FLAG==1)
	{
		Motor_double_test(0,0);
	}
	else
	{
		if(tmp.MotorTurn<0)
		{
			Motor_double_test(tmp.MotorSpeed,speedTmp);
		}
		else
		{
			Motor_double_test(speedTmp,tmp.MotorSpeed);
		}
	}
}

/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
	uint8  n;    //���ź�
	uint32 flag;

	while(!PORTA_ISFR);
	flag = PORTA_ISFR;
	PORTA_ISFR  = ~0;                                   //���жϱ�־λ

	n = 29;                                             //���ж�
	if(flag & (1 << n))                                 //PTA29�����ж�
	{
		camera_vsync();
	}
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
	n = 28;
	if(flag & (1 << n))                                 //PTA28�����ж�
	{
		camera_href();
	}
#endif
}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
	camera_dma();
}

