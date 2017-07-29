#ifndef __CACULATION_H__
#define __CACULATION_H__

#include "include.h"
#include "common.h"

#define ROW 120
#define COLUMN 160

extern uint8 TIME1flag_1s ;
extern uint8 TIME1flag_2s ;
extern uint8 TIME1flag_3s ;

typedef enum
{
	RUN,
	GO,
	CATCH,
	WAIT,
	GIVE_WAY,
	TURN,
	STOP
}RUN_STATEn_e;

struct T_S
{
	int16 MotorTurn;
	uint16 MotorSpeed;
} ;

extern uint8 img[CAMERA_H][CAMERA_W];

struct T_S  GetTrack(uint8 Image_Data[ROW][COLUMN]);
void Run(void);
int16 CalcSpeed(uint16 SpeedTarget,int16 );
#endif		//__CACULATION_H__