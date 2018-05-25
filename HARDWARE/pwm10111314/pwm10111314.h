#ifndef __PWM10111314_H
#define __PWM10111314_H
#include "sys.h"
//������Ϊ2017��1��29�յ�test
//PWM10~14_Init(u32 arr,u32 psc);���ڵ�·PWM�ĳ�ʼ��
//���ж�ʱ��Ϊ��򵥵�ͨ��Tim10/11/13/14
//ͨ��pwmset������һ����������·��pwm���
//�¿����˵���������·PWM����ĺ���PWM1X_Set();value��0��3.3V��Ӧ��0��3300
//
//ͨ���ı�TIM10~14->CCR1��ֵ���ı�ռ�ձȣ��Ӷ��ı����


//designed by Treaser.L-2017-1-29


#define PWM14_VAL TIM14->CCR1    
#define PWM13_VAL TIM13->CCR1 
#define PWM11_VAL TIM11->CCR1 
#define PWM10_VAL TIM10->CCR1 

void TIM3_Int_Init(u16 arr,u16 psc);
void PWM10111314_Init(void);
void PWM10_Init(u32 arr,u32 psc);
void PWM11_Init(u32 arr,u32 psc);
void PWM13_Init(u32 arr,u32 psc);
void PWM14_Init(u32 arr,u32 psc);
void PWM_Set(u16 pwm10,u16 pwm11,u16 pwm13,u16 pwm14);
void PWM10_Set(u16 value);
void PWM11_Set(u16 value);
void PWM13_Set(u16 value);
void PWM14_Set(u16 value);

#endif























