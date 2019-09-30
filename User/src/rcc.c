/******************** (C) COPYRIGHT  ���Ƕ��ʽ���������� ********************
 * �ļ���  ��iso_rcc.c
 * ����    ��STM32F0-LED       
 * ʵ��ƽ̨��M0-ISO������
 * ��汾  ��V1.3.0
 * ����    ����� QQ:779814207/2366260464
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 * �޸�ʱ��: 2014-12-15
**********************************************************************************/	
/**
  ******************************************************************************
  * @file    iso_led.c 
  * @author  Fengchi  Technology Team
  * @version V1.3.0
  * @date    15-December-2014
  * @brief   led
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */
	
#include "rcc.h"	
void SystemClock_Configuration(void)
{
	
    	/* ѡ�����໷��PLL��ʱ��ԴΪHSE 1��Ƶ����Ƶ��Ϊ6����PLL���Ƶ��Ϊ 8MHz * 6 = 48MHz */
    	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);

    	/* ʹ��PLL */ 
    	RCC_PLLCmd(ENABLE);

    	/* �ȴ�PLL����ȶ� */
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    	/* ѡ��SYSCLKʱ��ԴΪPLL */
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    	/* �ȴ�PLL��ΪSYSCLKʱ��Դ */
    	while(RCC_GetSYSCLKSource() != PLL);
	
}


