#include "pwm10111314.h"
#include "led.h"
 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//����д��������Ӳ���Ŷ��������,����ϵ   18258583270
//All rights reserved
//2017.2.13
//����TIM14_PWM_Init����,����PWM���
//
//	under the circumstance of: my wheels are in the position of:
//
//		10//	^	\\11
//				|
//		13\\		//14
//



//pwm 14 ��ʼ������-PA7
void PWM14_Init(u32 arr,u32 psc)
{
	RCC->APB1ENR|=1<<8; 	//TIM14ʱ��ʹ��    
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	GPIO_Set(GPIOA,PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,�������
	GPIO_AF_Set(GPIOA,7,9);	//PA7,AF9 
	
	TIM14->ARR=arr;			//�趨�������Զ���װֵ 
	TIM14->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM14->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��	   
	TIM14->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM14->CCER|=0<<1;   	//OC1 �ߵ�ƽ��Ч	   
	TIM14->CR1|=1<<7;   	//ARPEʹ�� 
	TIM14->CR1|=1<<0;    	//ʹ�ܶ�ʱ��14 	

}
//pwm 13��ʼ������-PA6
void PWM13_Init(u32 arr,u32 psc)
{

	RCC->APB1ENR|=1<<7; 	//TIM13ʱ��ʹ��    
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	GPIO_Set(GPIOA,PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,�������
	GPIO_AF_Set(GPIOA,6,9);	//PA6,AF9 
	
	TIM13->ARR=arr;			//�趨�������Զ���װֵ 
	TIM13->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM13->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM13->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��	   
	TIM13->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM13->CCER|=0<<1;   	//OC1 �͸ߵ�ƽ��Ч	   
	TIM13->CR1|=1<<7;   	//ARPEʹ�� 
	TIM13->CR1|=1<<0;    	//ʹ�ܶ�ʱ��13 	

}
//pwm 11���ʹ��-PB9
void PWM11_Init(u32 arr,u32 psc)
{

	RCC->APB2ENR|=1<<18; 	//TIM11ʱ��ʹ��    
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,�������
	GPIO_AF_Set(GPIOB,9,3);	//PB9,AF3
	
	TIM11->ARR=arr;			//�趨�������Զ���װֵ 
	TIM11->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM11->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM11->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��	   
	TIM11->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM11->CCER|=0<<1;   	//OC1 �ߵ�ƽ��Ч	   
	TIM11->CR1|=1<<7;   	//ARPEʹ�� 
	TIM11->CR1|=1<<0;    	//ʹ�ܶ�ʱ��11	

}
//pwm 10���ʹ��-PB8
void PWM10_Init(u32 arr,u32 psc)
{

	RCC->APB2ENR|=1<<17; 	//TIM10ʱ��ʹ��    
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,�������
	GPIO_AF_Set(GPIOB,8,3);	//PB8,AF3
	
	TIM10->ARR=arr;			//�趨�������Զ���װֵ 
	TIM10->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM10->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM10->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��	   
	TIM10->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM10->CCER|=0<<1;   	//OC1 �ߵ�ƽ��Ч	   
	TIM10->CR1|=1<<7;   	//ARPEʹ�� 
	TIM10->CR1|=1<<0;    	//ʹ�ܶ�ʱ��10	

}

//TIM14 PWM���ֳ�ʼ�� 


//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void PWM10111314_Init(void)
{		 					 
	PWM14_VAL=0;   
	PWM13_VAL=0;
	PWM11_VAL=0;
	PWM10_VAL=0; 
	PWM14_Init(330-1,84-1);
	PWM13_Init(330-1,84-1);
	PWM11_Init(330-1,84-1);
	PWM10_Init(330-1,84-1);
	
}  

void PWM_Set(u16 pwm10,u16 pwm11,u16 pwm13,u16 pwm14)
{
	PWM14_VAL=pwm14;
	PWM13_VAL=pwm13;
	PWM11_VAL=pwm11;
	PWM10_VAL=pwm10;
}

void PWM10_Set(u16 value)
{
	PWM10_VAL=value;
}

void PWM11_Set(u16 value){
	PWM11_VAL=value;
}
void PWM13_Set(u16 value){
	PWM13_VAL=value;
}
void PWM14_Set(u16 value){
	PWM14_VAL=value;
}










