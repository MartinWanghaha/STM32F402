#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

extern uint8_t phasecw[4];// ��ʱ��
extern uint8_t phaseccw[4];// ˳ʱ��


#define M1_XQ0 GPIOA,GPIO_Pin_5 //���1���Ŷ���
#define M1_XQ1 GPIOB,GPIO_Pin_8 //���1���Ŷ���
#define M1_XQ2 GPIOB,GPIO_Pin_9 //���1���Ŷ���
#define M1_XQ3 GPIOB,GPIO_Pin_3 //���1���Ŷ���

#define M2_XQ4 GPIOB,GPIO_Pin_4 //���2���Ŷ���
#define M2_XQ5 GPIOB,GPIO_Pin_5 //���2���Ŷ���
#define M2_XQ6 GPIOB,GPIO_Pin_6 //���2���Ŷ���
#define M2_XQ7 GPIOB,GPIO_Pin_7 //���2���Ŷ���

#define M3_XQ8  GPIOB,GPIO_Pin_2  //���3���Ŷ���
#define M3_XQ9  GPIOB,GPIO_Pin_10 //���3���Ŷ���
#define M3_XQ10 GPIOB,GPIO_Pin_11 //���3���Ŷ���
#define M3_XQ11 GPIOB,GPIO_Pin_12 //���3���Ŷ���

#define M4_XQ12 GPIOB,GPIO_Pin_13 //���4���Ŷ���
#define M4_XQ13 GPIOB,GPIO_Pin_14 //���4���Ŷ���
#define M4_XQ14 GPIOB,GPIO_Pin_15 //���4���Ŷ���
#define M4_XQ15 GPIOA,GPIO_Pin_8  //���4���Ŷ���

#define M5_XQ16 GPIOA,GPIO_Pin_6 //���5���Ŷ���
#define M5_XQ17 GPIOA,GPIO_Pin_7 //���5���Ŷ���
#define M5_XQ18 GPIOB,GPIO_Pin_0 //���5���Ŷ���
#define M5_XQ19 GPIOB,GPIO_Pin_1 //���5���Ŷ���

extern uint16_t M1_Position; //���λ������
extern uint16_t M2_Position; //���λ������
extern uint16_t M3_Position; //���λ������
extern uint16_t M4_Position; //���λ������
extern uint16_t M5_Position; //���λ������

extern uint16_t M1_Speed; //����ٶ�����
extern uint16_t M2_Speed; //����ٶ�����
extern uint16_t M3_Speed; //����ٶ�����
extern uint16_t M4_Speed; //����ٶ�����
extern uint16_t M5_Speed; //����ٶ�����

void MOTOR_GPIO_Config(void);
void SetMotor1(unsigned char InputData); 
void SetMotor2(unsigned char InputData);
void SetMotor3(unsigned char InputData);
void SetMotor4(unsigned char InputData);
void SetMotor5(unsigned char InputData);
void Set_Speed(uint8_t Motor,uint16_t Speed);
void Set_Position(uint8_t Motor,uint16_t Position);








#endif /* __DELAY_H */

