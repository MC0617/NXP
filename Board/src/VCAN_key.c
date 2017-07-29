#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"
#include "VCAN_key.h"

/*
 * ���� KEY ��Ŷ�Ӧ�Ĺܽ�
 */
PTXn_e KEY_PTxn[8] = {PTC12, PTC13, PTC14, PTC15, PTC16, PTC17, PTC18, PTC19};

/*!
 *  @brief      ��ʼ�����뿪��
 *  @since      v5.0
 */
void key_init(void)
{
  uint8 key=8;
		while(key--)
		{
			gpio_init(KEY_PTxn[key], GPI, 0);
			port_init_NoALT(KEY_PTxn[key], PULLUP);         //���ָ��ò��䣬�����ı�����ѡ��
		}

	
}
/*!
 *  @brief      ��ȡ���뿪��ֵ
 *  @since      v5.0
 *  Sample usage:       uint8 button=button_get();	//��ȡ���뿪��ֵ
 */
uint8 key_get(void)
{
  uint8 value=0;
  for(uint8 i=0;i<8;i++)
  {
	value+=gpio_get(KEY_PTxn[i]);
	if(7!=i)
	value<<=1;
  }
  return value;
}