#include "can.h"
#include "led.h"
#include "usart.h"
#include "stm32f0xx_can.h"

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* ���жϴ������з��� */
uint8_t Receive_Buffer_Len=0;
uint8_t ReceiveBuffer[255];
uint8_t *pReceiveBuffer=ReceiveBuffer;

volatile TestStatus TestRx;	
static void CAN_NVIC_Configuration(void)
{

	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
static void CAN_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);	                        											 
	/* CAN1 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);
	
	//GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_4);
  //GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_4); //GPIOA11����ΪCAN1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_4); //GPIOA12����ΪCAN1	
	/* Configure CAN pin: RX */									             
	
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure CAN pin: TX */									        

	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void CAN_InterruptMode_Configuration(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN register init */
	CAN_DeInit(CAN);
	CAN_StructInit(&CAN_InitStructure);
	
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM=DISABLE;           // ʱ�䴥��ͨ�Ž�ֹ
	CAN_InitStructure.CAN_ABOM=DISABLE;	          // �����˳������ж���λ��0���˳�
	CAN_InitStructure.CAN_AWUM=DISABLE;	          // �Զ�����ģʽ������sleep
	CAN_InitStructure.CAN_NART=DISABLE;	          // �Զ����´��ͱ��ƣ�֪�����ͳɹ�
	CAN_InitStructure.CAN_RFLM=DISABLE;	          // FIFOû���������±��ĸ��Ǿɱ���
	CAN_InitStructure.CAN_TXFP=DISABLE;           // ���ͱ������ȼ�ȷ������־��
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; // ����ģʽ
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;        // 1tq��BS1��BS2��ֵ���������й�
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=3;					  // ��Ƶϵ��Ϊ1
	CAN_Init(CAN, &CAN_InitStructure);						// ��ʼ��CAN1
	
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber=1;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/* CAN FIFO0 message pending interrupt enable */ 
	CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE); //�ж�ʹ��
}
void CAN_Transmit_Buffer(uint8_t* pBuffer,uint16_t NumByteToWrite)
{
	uint8_t NumOfPake=0,NumOfSingle=0,cnt=0;
	CanTxMsg TxMessage;
	NumOfPake=NumByteToWrite/8 ;
	NumOfSingle=NumByteToWrite%8 ;
	TxMessage.StdId=0x00;					 // ��׼��ʶ��Ϊ0
	TxMessage.ExtId=0x1234;				 // ������չ��ʾ����29λ��
	TxMessage.IDE=CAN_ID_EXT;			 // ʹ����չ��ʶ��
	TxMessage.RTR=CAN_RTR_DATA;		 // ��Ϣ����Ϊ����֡��һ֡8λ
	while(NumOfPake--)
	{
				/* transmit 1 message */
			TxMessage.DLC=8;							
			for(cnt=0;cnt<8;cnt++)
			{
				TxMessage.Data[cnt]=* pBuffer;				 
				pBuffer++;
			}
			CAN_Transmit(CAN, &TxMessage);	
	}
	if(NumOfSingle)
	{
		TxMessage.DLC=NumOfSingle;							 
		for(cnt=0;cnt<NumOfSingle;cnt++)
		{
			TxMessage.Data[cnt]=* pBuffer;				 
			pBuffer++;
		}
		CAN_Transmit(CAN, &TxMessage);
	}
	
}
void USER_CAN_Init(void)
{
	CAN_NVIC_Configuration();
	CAN_GPIO_Configuration();
}


