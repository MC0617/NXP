//添加头文件
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

////全局变量定义
int16 SpeedCurrent=0;
volatile uint32 counter = 0,cnvtime=1;                //输入捕捉值
uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 imgbit[CAMERA_SIZE];
uint8 img[CAMERA_H][CAMERA_W];
char bt_rec;

//函数声明
void PIT2_IRQHandler(void);
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void Run(void);
uint16 SPEED_MAX,SPEED_MIN;
void  main(void)
{

	// 禁止总中断
	DisableInterrupts;
	//初始化
#ifdef __DAUGHTER__
	ultrasonic_init();
#endif
	key_init();															//拨码开关初始化
	uart_init(VCAN_PORT,VCAN_BAUD);										//串口
	uart_init(BT_PORT,BT_BAUD);											//蓝牙
	Motor_double_PWM_init();											//电机驱动初始化
	Servo_motor_S3010_init();											//舵机驱动初始化
	camera_init(imgbuff);												//摄像头初始化
	ftm_quad_init(FTM2);           									//初始化FTM的正交解码功能
//	adc_init(ADC0_DP0);
	pit_init_ms(PIT0,20);
	pit_init_ms(PIT1,50);
//#ifdef __SON__
//	pit_init_ms(PIT2,2500);
//#elif defined __DAUGHTER__
//	pit_init_ms(PIT2,1500);
//#endif
	port_init_NoALT(PTD5,PULLUP);                                  	//蓝牙EN端
	port_init_NoALT(PTD4,PULLDOWN);                                	//蓝牙STATE端
//	//配置中断服务函数
	set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
	set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler
	set_vector_handler(PIT0_VECTORn , PIT0_IRQHandler);
	set_vector_handler(PIT1_VECTORn , PIT1_IRQHandler);
	set_vector_handler(PORTD_VECTORn , PORTD_IRQHandler);
//	// 开启中断
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
		camera_get_img();                                   //摄像头获取图像
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
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
	uint8  n;    //引脚号
	uint32 flag;

	while(!PORTA_ISFR);
	flag = PORTA_ISFR;
	PORTA_ISFR  = ~0;                                   //清中断标志位

	n = 29;                                             //场中断
	if(flag & (1 << n))                                 //PTA29触发中断
	{
		camera_vsync();
	}
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
	n = 28;
	if(flag & (1 << n))                                 //PTA28触发中断
	{
		camera_href();
	}
#endif
}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
	camera_dma();
}

