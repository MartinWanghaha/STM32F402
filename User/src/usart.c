	/******************** (C) COPYRIGHT  ���Ƕ��ʽ���������� ********************
 * �ļ���  ��iso_usart1.c
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
  * USART1_TX<----->PA9
  * USART1_RX<----->PA10
  ******************************************************************************
  */
#include "usart.h"
#include "led.h" 

UsartReceiveNumBit_TypeDef UsartReceiveNum;

uint8_t USART_RX_Buffer[Max_RX_Buffer_Len];
 /**
  * @brief  USART1 �����ж�����
  * @param  ��
  * @retval ��
  */
static void USART1_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

 
 /**
  * @brief  USART1 GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	USART_Cmd(USART1, DISABLE);
	USART_DeInit(USART1);
	
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	/*����GPIOA������ʱ��*/
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE); 
	/*����ӳ������ܽ�*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);  
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin    = USART1_TX;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PA.10) as input mode */
	GPIO_InitStructure.GPIO_Pin    = USART1_RX;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	/* ʹ�ܴ���1�����ж� */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART1, ENABLE);
  USART_ClearFlag(USART1, USART_FLAG_TC);
  
  USART1_NVIC_Config();
}

void AutoBauRate_StartBitMethod(void)
{ 
 
  /* Configure the AutoBaudRate method */
  USART_AutoBaudRateConfig(USART1, USART_AutoBaudRate_StartBit);
  
  /* Enable AutoBaudRate feature */
  USART_AutoBaudRateCmd(USART1, ENABLE);
  
  /* Wait until Receive enable acknowledge flag is set */
  while(USART_GetFlagStatus(USART1, USART_FLAG_REACK) == RESET);
	
  /* Wait until Transmit enable acknowledge flag is set */  
  while(USART_GetFlagStatus(USART1, USART_FLAG_TEACK) == RESET);

  /* Loop until the end of Autobaudrate phase */
  while(USART_GetFlagStatus(USART1, USART_FLAG_ABRF) == RESET);
 
  /* If AutoBaudBate error occurred */
  if (USART_GetFlagStatus(USART1, USART_FLAG_ABRE) != RESET)
  {
    /* Turn on LED3 */
    ISO_LED(LED3,ON);
  }
  else
  {
    /* Turn on LED2 */
    ISO_LED(LED2,ON);
	}
    
  
}





 /**
  * @brief  �ض���c�⺯��printf��USART1
  * @param  
  * @retval 
  */
#pragma import(__use_no_semihosting) 
struct __FILE
{
    int handle;
};
FILE __stdout;   
_sys_exit(int x)
{
	x = x;
}
int fputc(int ch, FILE *f)
{
	 USART_SendData(USART1,ch);
	 while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	 return ch;
}

void USART_SendString(char *str)
 
{
         uint8_t index=0;
 
         do
 
         {
 
                   USART_SendData(USART1,str[index]);
 
                   while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
 
                   index++;
 
         }
 
         while(str[index]!=0);
}



 /**
  * @brief  �ض���c�⺯��scanf��USART1
  * @param  
  * @retval 
  */
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
/*********************************************END OF FILE**********************/