/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       MK60_it.h
 * @brief      山外K60 平台中断服务重定向头文件
 * @author     山外科技
 * @version    v5.0
 * @date       2013-06-26
 */


#ifndef __MK60_IT_H__
#define __MK60_IT_H__

/*                          重新定义中断向量表
 *  先取消默认的中断向量元素宏定义        #undef  VECTOR_xxx
 *  在重新定义到自己编写的中断函数      #define VECTOR_xxx    xxx_IRQHandler
 *  例如：
 *       #undef  VECTOR_003                         先取消映射到中断向量表里的中断函数地址宏定义
 *       #define VECTOR_003    HardFault_Handler    重新定义硬件上访中断服务函数
 */

#include  "common.h"
//
//
////#ifndef __ISR_H
////#define __ISR_H 1
//
#include  "include.h"
//
//typedef struct  speedcount
//{
//	uint8   porta;
//	vint16  speedcount;
//
//} SPEEDCOUT;
//
//
///*                          重新定义中断向量表
// *  先取消默认的中断向量元素宏定义       #undef  VECTOR_xxx
// *  在重新定义到自己编写的中断函数       #define VECTOR_xxx    xxx_IRQHandler
// *  例如：
// *       #undef  VECTOR_003
// *       #define VECTOR_003    HardFault_Handler    重新定义硬件上访中断服务函数
// */
//#undef  VECTOR_014
//#undef  VECTOR_015
//#if     USOC_EN > 0u    //如果定义了用ucos系统  用ucos的滴答定时器中断服务函数
//#define VECTOR_014    OS_CPU_PendSVHandler
//#define VECTOR_015    OS_CPU_SysTickHandler
//#else
//#define VECTOR_014    PendSV_Handler
//#define VECTOR_015    SysTick_Handler   //滴答定时器  OS用得到
//#endif
//
//#undef  VECTOR_003
//#define VECTOR_003    HardFault_Handler   //发生硬件上访 （就是程序跑飞了）     推荐调试程序时，用个LED显示来指示程序跑飞了
//
//
//
//#undef  VECTOR_016
//#define VECTOR_016    DMA_CH0_Handler
//
//#undef  VECTOR_020
//#define VECTOR_020    DMA_CH4_Handler
//
//
//
//
//
//#undef  VECTOR_063                        //要先取消了，因为在vectors.h里默认是定义为 default_isr  
//#define VECTOR_063    USART1_IRQHandler   //重新定义63号中断的ISR：UART1：Single interrupt vector for UART status sources
//
////#undef  VECTOR_078
////#define VECTOR_078    FTM0_IRQHandler     //FTM0输入捕捉中断 
//
//#undef  VECTOR_079
//#define VECTOR_079    FTM1_IRQHandler     //FTM0输入捕捉中断
//
//#undef  VECTOR_080
//#define VECTOR_080    FTM2_IRQHandler     //FTM0输入捕捉中断
//
//#undef  VECTOR_084
//#define VECTOR_084    PIT0_IRQHandler     //重新定义84号中断为PIT0_IRQHandler中断
//
//#undef  VECTOR_085
//#define VECTOR_085    PIT1_IRQHandler     //重新定义85号中断为PIT0_IRQHandler中断
//
//#undef  VECTOR_105
//#define VECTOR_105    LPT_Handler        //LPT中断
//
//#undef  VECTOR_104
//#define VECTOR_104    PORTB_IRQHandler    //PORTB中断
//
//#undef  VECTOR_106
//#define VECTOR_106    PORTD_IRQHandler    //PORTD中断
//
extern uint8 TIME0flag_10ms  ;
extern uint8 TIME0flag_20ms  ;
extern uint8 TIME0flag_30ms  ;
extern uint8 TIME0flag_40ms  ;
extern uint8 TIME0flag_50ms  ;

extern uint8 TIME1flag_250ms ;
extern uint8 TIME1flag_500ms ;
extern uint8 TIME1flag_1s ;
extern uint8 TIME1flag_1s5 ;
extern uint8 TIME1flag_2s ;
extern uint8 TIME1flag_2s5 ;
//extern void PendSV_Handler(void);         //可悬起的系统调用中断服务函数
//extern void HardFault_Handler(void);      //发生硬件上访（程序跑飞）
//extern void SysTick_Handler(void);        //滴答时钟(os 用到)
//extern void USART1_IRQHandler();          //串口1 中断接收函数
extern void PIT0_IRQHandler();            //PIT0 定时中断服务函数
extern void PIT1_IRQHandler();            //PIT1 定时中断服务函数
//extern void PORTD_IRQHandler();           //PORTD中断服务函数
//extern void PORTB_IRQHandler();           //PORTB中断服务函数
//extern void FTM2_IRQHandler();            //FTM0输入捕捉中断
//extern void FTM1_IRQHandler();            //FTM0输入捕捉中断
//extern void LPT_Handler(void);           //LPT脉冲中断
//extern void DMA_CH0_Handler(void);
//extern void DMA_CH4_Handler(void);              //DMA通道4的中断服务函数
//
////#endif  //__ISR_H
//
//void LPT_Handler(void);           //LPT脉冲中断
//void DMA_CH6_Handler(void);
//void DMA_CH4_Handler(void);              //DMA通道4的中断服务函数
//__RAMFUNC  void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ) ;
//

#endif  //__MK60_IT_H__
