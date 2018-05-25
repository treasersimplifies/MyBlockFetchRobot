#ifndef __HCSR04_H
#define __HCSR04_H
#include "usart.h"
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.2
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//V1.1 20140504
//����TIM14_PWM_Init����,����PWM���
//V1.2 20140504
//����TIM5_CH1_Cap_Init����,�������벶��
////////////////////////////////////////////////////////////////////////////////// 	

//ͨ���ı�TIM14->CCR1��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define LED0_PWM_VAL TIM14->CCR1    

void HCSR04_Init(void);

void TIM5_CH1_Cap_Init(u32 arr,u16 psc);
void TIM4_CH1_Cap_Init(u16 arr,u16 psc);
void TIM3_CH1_Cap_Init(u16 arr,u16 psc);
void TIM2_CH1_Cap_Init(u32 arr,u16 psc);

int SR_Front(void);
int SR_Behind(void);
int SR_Left(void);
int SR_Right(void);
void
#endif























