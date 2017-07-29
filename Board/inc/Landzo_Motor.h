#ifndef _LANDZOmotor_H
#define _LANDZOmotor_H

#include "include.h"

/************************
#define  定义
************************/
#define  LPTMRCOUNT    65535


/***************************************************/
/************************
函数声明
************************/
//void Motor_one_PWM_init(void);
void Motor_double_PWM_init(void);
//void Motor_one_test(void);
void Motor_double_test(uint16,uint16 );

#endif
//end


