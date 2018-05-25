#ifndef __PWM912_H
#define __PWM912_H
#include "sys.h"
//������Ϊ2017��1��29�յ�test
//PWM10~14_Init(u32 arr,u32 psc);���ڵ�·PWM�ĳ�ʼ��
//���ж�ʱ��Ϊ��򵥵�ͨ��Tim10/11/13/14
//ͨ��pwmset������һ����������·��pwm���
//�¿����˵���������·PWM����ĺ���PWM1X_Set();value��0��3.3V��Ӧ��0��3300
//
//ͨ���ı�TIM10~14->CCR1��ֵ���ı�ռ�ձȣ��Ӷ��ı����

//			PA2-servoF
//
//	PB14-servoL		PB15-servoR
//
//			PA3-servoB
//

//designed by Treaser.L-2017-1-29


#define ServoF_VAL TIM9->CCR1    
#define ServoB_VAL TIM9->CCR2 
#define ServoL_VAL TIM12->CCR1 
#define ServoR_VAL TIM12->CCR2 

void SERVO_Init(void);
void PWM9_1_2_Init(u32 arr,u32 psc);
void PWM12_1_2_Init(u32 arr,u32 psc);
void ServoF_Set(u8 angle);
void ServoB_Set(u8 angle);
void ServoL_Set(u8 angle);
void ServoR_Set(u8 angle);

/*void TIM3_Int_Init(u16 arr,u16 psc);
void PWM10111314_Init(void);
void PWM13_Init(u32 arr,u32 psc);
void PWM14_Init(u32 arr,u32 psc);
void PWM_Set(u16 pwm10,u16 pwm11,u16 pwm13,u16 pwm14);
void PWM10_Set(u16 value);
void PWM11_Set(u16 value);
void PWM13_Set(u16 value);
void PWM14_Set(u16 value);
*/
#endif























