#ifndef __PWM10111314_H
#define __PWM10111314_H
#include "sys.h"
//本函数为2017年1月29日的test
//PWM10~14_Init(u32 arr,u32 psc);用于单路PWM的初始化
//所有定时器为最简单的通用Tim10/11/13/14
//通过pwmset函数来一次性设置四路的pwm输出
//新开放了单独设置四路PWM输出的函数PWM1X_Set();value从0到3.3V对应于0到3300
//
//通过改变TIM10~14->CCR1的值来改变占空比，从而改变输出


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























