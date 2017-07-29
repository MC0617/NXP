#include <caculation.h>
#include <math.h>
#include "CHILDREN.H"

extern RUN_STATEn_e RunState;
extern uint8 RingFlag;
extern uint8 TIME2flag_1s;
extern uint8 TIME2flag_2s;
extern uint8 TIME2flag_1s5;
extern uint8 TIME2flag_2s5;
extern uint16 TimeCount1;
struct T_S Turn_Speed;

struct T_S GetTrack(uint8 Image_Data[ROW][COLUMN])
{
	uint8 ZebraCount=0;
	uint8 EmptyFlag=0;

	uint16 u16ReferToGetTrack=COLUMN/2;

	uint8 GetRingFlag=0;
	uint16 RingLeftLast=0;
	uint16 RingLeftPrev=0;
	uint16 RingRightLast=0;
	uint16 RingRightPrev=0;

	uint16 u16LeftBorder[COLUMN]= {0};
	uint16 u16RightBorder[COLUMN]= {0};

	int16 i16R_L_DiffValue=0;
	int16 i16R_L_DiffMidValue=0;
	int16 i16R_L_DiffFarValue=0;

	Turn_Speed.MotorTurn=0;
	Turn_Speed.MotorSpeed=0;
	/*********************************************/
	//处理图像
	uint8 CentreFlag=0;
	for(uint8 i=ROW-1; i>1; i--)
	{
		if(Image_Data[i][COLUMN/2-1]==0
		        &&Image_Data[i-1][COLUMN/2]==0)
		{
			CentreFlag=1;
			break;
		}
	}

	for(uint8 i=ROW-1; i>0; i--)
	{
//		printf("\n%d	",i);
		ZebraCount=0;
		EmptyFlag=0;
		if(i<ROW-3)
		{
			//设置标记
			//如果前两行两边都没有边界并且这一行也没有，标记这一行边界为row/2
			if(
			    u16LeftBorder[i+1]==0
			    &&u16LeftBorder[i+2]==0
			    &&u16RightBorder[i+1]==0
			    &&u16RightBorder[i+2]==0
			    &&Image_Data[i][0]==0xff
			    &&Image_Data[i][1]==0xff
			    &&Image_Data[i][COLUMN-1]==0xff
			    &&Image_Data[i][COLUMN-2]==0xff
			)
			{
				EmptyFlag=1;
				u16ReferToGetTrack=COLUMN/2;
			}

			else if(
			    u16LeftBorder[i+1]==0
			    &&u16LeftBorder[i+2]==0
			    &&u16LeftBorder[i+3]==0
			    &&Image_Data[i][0]==0xff
			    &&Image_Data[i][1]==0xff
			    &&Image_Data[i][2]==0xff
			)
			{
				u16ReferToGetTrack=0;
			}
			else if(
			    u16RightBorder[i+1]==0
			    &&u16RightBorder[i+2]==0
			    &&u16RightBorder[i+3]==0
			    &&Image_Data[i][COLUMN-1]==0xff
			    &&Image_Data[i][COLUMN-2]==0xff
			    &&Image_Data[i][COLUMN-3]==0xff
			)
			{
				u16ReferToGetTrack=COLUMN;
			}
			//如果前两行两边都有边界，标记值为前一行中点
			else if(
			    u16LeftBorder[i+1]!=0
			    &&u16RightBorder[i+1]!=0
			)
			{
				u16ReferToGetTrack=(u16LeftBorder[i+1]+u16RightBorder[i+1])/2;
			}

			else
			{
				u16ReferToGetTrack=COLUMN/2;
			}

		}
		else
		{
			u16ReferToGetTrack=COLUMN/2;
		}
		//设置标记值完毕
		/********************************************/
		//判断停车
		if(u16ReferToGetTrack!=0&&u16ReferToGetTrack!=COLUMN&&GO_FLAG==1)
		{
			for(uint8 j=u16ReferToGetTrack; j>u16LeftBorder[i+1]; j--)
			{
				if((Image_Data[i-3][j]==0xff
				  &&Image_Data[i-3][j-1]==0xff
				  &&Image_Data[i-3][j-2]==0
				  &&Image_Data[i-3][j-3]==0)
				 ||(Image_Data[i-3][j]==0
				  &&Image_Data[i-3][j-1]==0
				  &&Image_Data[i-3][j-2]==0xff
				  &&Image_Data[i-3][j-3]==0xff))
				{
					ZebraCount++;
				}
			}
			for(uint8 j=u16ReferToGetTrack; j<u16RightBorder[i+1]; j++)
			{
				if((Image_Data[i-3][j]==0xff
				  &&Image_Data[i-3][j-1]==0xff
				  &&Image_Data[i-3][j-2]==0
				  &&Image_Data[i-3][j-3]==0)
				 ||(Image_Data[i-3][j]==0
				  &&Image_Data[i-3][j-1]==0
				  &&Image_Data[i-3][j-2]==0xff
				  &&Image_Data[i-3][j-3]==0xff))
				{
					ZebraCount++;
				}
			}
			if(ZebraCount>13)
			{
				RunState=STOP;
				STOP_FLAG = 0;
				TimeCount1=0;
				PIT_Flag_Clear(PIT1);       //清中断标志位
				return Turn_Speed;
			}
		}
		//停车判断完毕
		/*********************************************/
		//判断圆环
		if((EmptyFlag==1||GetRingFlag==1)&&RingFlag==0&&CentreFlag==1)
		{
			//提取边界
				for(uint8 j=COLUMN/2-COLUMN/10;j>4;j--)
				{
					if(
					    Image_Data[i][j]==0xff
					    &&Image_Data[i][j-1]==0xff
					    &&Image_Data[i][j-3]==0
					    &&Image_Data[i][j-2]==0
					)
					{
						u16LeftBorder[i]=j-2;
						break;
					}
				}
			
				for(uint16 j=COLUMN/2+COLUMN/10;j<COLUMN-4;j++)
				{
					if(
					    Image_Data[i][j]==0xff
					    &&Image_Data[i][j+1]==0xff
					    &&Image_Data[i][j+3]==0
					    &&Image_Data[i][j+2]==0
					)
					{
						u16RightBorder[i]=j+2;
						break;
					}
				}
			
			if(u16LeftBorder[i]==0&&u16RightBorder[i]==0)
			{
				uint16 RingLeftCurrent=0;
				uint16 RingRightCurrent=0;
				GetRingFlag=1;
				for(uint16 j=0; j<COLUMN-3; j++)
				{
					if(
					    Image_Data[i][j]==0xff
					    &&Image_Data[i][j+1]==0xff
					    &&Image_Data[i][j+3]==0
					    &&Image_Data[i][j+2]==0
					)
					{
						RingLeftCurrent=j+2;
						break;
					}
				}
				for(uint16 j=COLUMN-1; j>0; j--)
				{
					if(
					    Image_Data[i][j]==0xff
					    &&Image_Data[i][j-1]==0xff
					    &&Image_Data[i][j-3]==0
					    &&Image_Data[i][j-2]==0
					)
					{
						RingRightCurrent=j-2;
						break;
					}
				}
				if(RingRightCurrent>RingLeftCurrent)
				{
					if(
					    (RingRightCurrent-RingLeftCurrent)>(RingRightLast-RingLeftLast)
					    &&(RingRightLast-RingLeftLast)>(RingRightPrev-RingLeftPrev)
					)
					{
						RingFlag=1;
						GetRingFlag=0;
					}
					RingLeftPrev=RingLeftLast;
					RingLeftLast=RingLeftCurrent;
					RingRightPrev=RingRightLast;
					RingRightLast=RingRightCurrent;
				}
				else
				{
					RingLeftLast=0;
					RingLeftPrev=0;
					RingRightLast=0;
					RingRightPrev=0;
					GetRingFlag=0;
				}
			}

		}
		if(RingFlag||GetRingFlag)
		{
			u16ReferToGetTrack=COLUMN;
		//u16ReferToGetTrack=0;
		}
		//圆环判断完毕
		/******************************************************/
		//提取边界
		if(u16ReferToGetTrack!=0)
		{
			for(uint8 j=0; j<u16ReferToGetTrack-4; j++)
			{

				if(
				    Image_Data[i][u16ReferToGetTrack-j]==0xff
				    &&Image_Data[i][u16ReferToGetTrack-j-1]==0xff
				    &&Image_Data[i][u16ReferToGetTrack-j-3]==0
				    &&Image_Data[i][u16ReferToGetTrack-j-2]==0
				)
				{
					u16LeftBorder[i]=u16ReferToGetTrack-j-2;
					break;
				}
			}
		}
		if(u16ReferToGetTrack!=COLUMN)
		{
			for(uint16 j=0; j<(COLUMN-u16ReferToGetTrack-4); j++)
			{
				if(
				    Image_Data[i][u16ReferToGetTrack+j]==0xff
				    &&Image_Data[i][u16ReferToGetTrack+j+1]==0xff
				    &&Image_Data[i][u16ReferToGetTrack+j+3]==0
				    &&Image_Data[i][u16ReferToGetTrack+j+2]==0
				)
				{
					u16RightBorder[i]=u16ReferToGetTrack+j+2;
					break;
				}
			}
		}
		//边界提取完毕
		if(
		    ( (i<ROW/2)&&((u16RightBorder[i]==0&&u16LeftBorder[i]>=COLUMN-6)
		                  ||(u16LeftBorder[i]==0&&(u16RightBorder[i]<=6&&u16RightBorder!=0)) ))
		    &&RingFlag!=0&&GetRingFlag!=0
		)
		{
			break;
		}
	}
	//图像处理完毕
	/********************************************************************/
	/********************************************************************/
	//处理数据
	//处理近处的70-90行
	for(uint8 i=80; i<100; i++)
	{
		if(u16RightBorder[i]!=0)
		{
			i16R_L_DiffValue+=((COLUMN-u16RightBorder[i])-u16LeftBorder[i]);
		}
		else
		{
			i16R_L_DiffValue-=u16LeftBorder[i];
		}
	}//得到70-90行面积差 i16R_L_DiffValue

	//处理50-70行
	for(uint8 i=60; i>40; i--)
	{
		if(u16RightBorder[i]!=0)
		{
			i16R_L_DiffMidValue+=((COLUMN-u16RightBorder[i])-u16LeftBorder[i]);
		}
		else
		{
			i16R_L_DiffMidValue-=u16LeftBorder[i];
		}
	}//得到50-70行面积差 i16R_L_DiffMidValue
	if(ABS(i16R_L_DiffMidValue)>(32*ABS(i16R_L_DiffValue)))//&&RingFlag==1 )
	{
		Turn_Speed.MotorTurn=i16R_L_DiffMidValue;
	}
	else
	{
		Turn_Speed.MotorTurn=i16R_L_DiffValue;
	}

	//处理远处的10-20行
	//求10-20行的面积差(右边界外面积-左边界外面积)
	for(uint8 i=30; i<50; i++)
	{
		if(u16RightBorder[i]!=0)
		{
			i16R_L_DiffFarValue+=((COLUMN-u16RightBorder[i])-u16LeftBorder[i]);
		}
		else
		{
			i16R_L_DiffFarValue-=u16LeftBorder[i];
		}
	}

	if(ABS(i16R_L_DiffFarValue)>(16*ABS(i16R_L_DiffValue)))
	{
		//RingFlag=1;
	}
//对面积差取绝对值确定速度大小
	int n= MAX(ABS(i16R_L_DiffValue),3*ABS(i16R_L_DiffFarValue));
	float u16Product=1;
//速度与面积差的对应关系 1/(1.01^面积差)*400	面积差指数变换,求倒数,乘400
	for(uint16 i=0; i<n; i++)
	{
		//u16Product+=i;
		u16Product*=1.01;
	}
	u16Product=4000/(u16Product);

	Turn_Speed.MotorSpeed=(uint16)u16Product;

	return Turn_Speed;
}
