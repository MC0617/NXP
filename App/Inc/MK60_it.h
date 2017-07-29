/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_it.h
 * @brief      ɽ��K60 ƽ̨�жϷ����ض���ͷ�ļ�
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-06-26
 */


#ifndef __MK60_IT_H__
#define __MK60_IT_H__

/*                          ���¶����ж�������
 *  ��ȡ��Ĭ�ϵ��ж�����Ԫ�غ궨��        #undef  VECTOR_xxx
 *  �����¶��嵽�Լ���д���жϺ���      #define VECTOR_xxx    xxx_IRQHandler
 *  ���磺
 *       #undef  VECTOR_003                         ��ȡ��ӳ�䵽�ж�����������жϺ�����ַ�궨��
 *       #define VECTOR_003    HardFault_Handler    ���¶���Ӳ���Ϸ��жϷ�����
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
///*                          ���¶����ж�������
// *  ��ȡ��Ĭ�ϵ��ж�����Ԫ�غ궨��       #undef  VECTOR_xxx
// *  �����¶��嵽�Լ���д���жϺ���       #define VECTOR_xxx    xxx_IRQHandler
// *  ���磺
// *       #undef  VECTOR_003
// *       #define VECTOR_003    HardFault_Handler    ���¶���Ӳ���Ϸ��жϷ�����
// */
//#undef  VECTOR_014
//#undef  VECTOR_015
//#if     USOC_EN > 0u    //�����������ucosϵͳ  ��ucos�ĵδ�ʱ���жϷ�����
//#define VECTOR_014    OS_CPU_PendSVHandler
//#define VECTOR_015    OS_CPU_SysTickHandler
//#else
//#define VECTOR_014    PendSV_Handler
//#define VECTOR_015    SysTick_Handler   //�δ�ʱ��  OS�õõ�
//#endif
//
//#undef  VECTOR_003
//#define VECTOR_003    HardFault_Handler   //����Ӳ���Ϸ� �����ǳ����ܷ��ˣ�     �Ƽ����Գ���ʱ���ø�LED��ʾ��ָʾ�����ܷ���
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
//#undef  VECTOR_063                        //Ҫ��ȡ���ˣ���Ϊ��vectors.h��Ĭ���Ƕ���Ϊ default_isr  
//#define VECTOR_063    USART1_IRQHandler   //���¶���63���жϵ�ISR��UART1��Single interrupt vector for UART status sources
//
////#undef  VECTOR_078
////#define VECTOR_078    FTM0_IRQHandler     //FTM0���벶׽�ж� 
//
//#undef  VECTOR_079
//#define VECTOR_079    FTM1_IRQHandler     //FTM0���벶׽�ж�
//
//#undef  VECTOR_080
//#define VECTOR_080    FTM2_IRQHandler     //FTM0���벶׽�ж�
//
//#undef  VECTOR_084
//#define VECTOR_084    PIT0_IRQHandler     //���¶���84���ж�ΪPIT0_IRQHandler�ж�
//
//#undef  VECTOR_085
//#define VECTOR_085    PIT1_IRQHandler     //���¶���85���ж�ΪPIT0_IRQHandler�ж�
//
//#undef  VECTOR_105
//#define VECTOR_105    LPT_Handler        //LPT�ж�
//
//#undef  VECTOR_104
//#define VECTOR_104    PORTB_IRQHandler    //PORTB�ж�
//
//#undef  VECTOR_106
//#define VECTOR_106    PORTD_IRQHandler    //PORTD�ж�
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
//extern void PendSV_Handler(void);         //�������ϵͳ�����жϷ�����
//extern void HardFault_Handler(void);      //����Ӳ���Ϸã������ܷɣ�
//extern void SysTick_Handler(void);        //�δ�ʱ��(os �õ�)
//extern void USART1_IRQHandler();          //����1 �жϽ��պ���
extern void PIT0_IRQHandler();            //PIT0 ��ʱ�жϷ�����
extern void PIT1_IRQHandler();            //PIT1 ��ʱ�жϷ�����
//extern void PORTD_IRQHandler();           //PORTD�жϷ�����
//extern void PORTB_IRQHandler();           //PORTB�жϷ�����
//extern void FTM2_IRQHandler();            //FTM0���벶׽�ж�
//extern void FTM1_IRQHandler();            //FTM0���벶׽�ж�
//extern void LPT_Handler(void);           //LPT�����ж�
//extern void DMA_CH0_Handler(void);
//extern void DMA_CH4_Handler(void);              //DMAͨ��4���жϷ�����
//
////#endif  //__ISR_H
//
//void LPT_Handler(void);           //LPT�����ж�
//void DMA_CH6_Handler(void);
//void DMA_CH4_Handler(void);              //DMAͨ��4���жϷ�����
//__RAMFUNC  void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ) ;
//

#endif  //__MK60_IT_H__
