#include "led.h"   
#include "usart.h"

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */

void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE); 											   
		GPIO_InitStructure.GPIO_Pin = LED1;	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;  
		GPIO_Init(LEDPort, &GPIO_InitStructure);		  
		GPIO_SetBits(LEDPort, LED1);
}

void LED_Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*----------------------------------------------------------------*/
void LED_Test(void)
{

}


/*********************************************END OF FILE**********************/
