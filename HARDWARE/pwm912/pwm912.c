#include "pwm912.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����д��������Ӳ���Ŷ������������ϵ   18258583270
//All rights reserved
//2017.2.13
//����TIM14_PWM_Init����,����PWM���
//0.5ms-------------0�ȣ� 	1/40
//1.0ms------------45�ȣ�	2/40
//1.5ms------------90�ȣ�	3/40
//2.0ms-----------135�ȣ�	4/40
//2.5ms-----------180�ȣ�	5/40
//
//			PA2-servoF
// 
//	PB14-servoL		PB15-servoR
//
//			PA3-servoB
//

//timer9��pwm ch1 ��ʼ������-PA2/PA3
void PWM9_1_2_Init(u32 arr,u32 psc)
{
	RCC->APB2ENR|=1<<16; 	//TIM9ʱ��ʹ��    
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,xia�����
	GPIO_AF_Set(GPIOA,2,3);	//PA2,AF3 
	GPIO_AF_Set(GPIOA,3,3);	//PA3,AF3
	
	TIM9->ARR=arr;			//�趨�������Զ���װֵ 
	TIM9->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM9->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM9->CCMR1|=1<<3; 		//CH1 Ԥװ��ʹ��	   
	TIM9->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM9->CCER|=0<<1;   	//OC1 �ߵ�ƽ��Ч	   
	
	TIM9->CCMR1|=6<<12;  	//CH2 PWM2ģʽ		 
	TIM9->CCMR1|=1<<11; 	//CH2 Ԥװ��ʹ��	    
	TIM9->CCER|=1<<4;   	//OC2 ���ʹ��
	TIM9->CCER|=0<<5;   	//OC2 �ߵ�ƽ��Ч
	
	TIM9->CR1|=1<<7;   		//ARPEʹ�� 
	TIM9->CR1|=1<<0;    	//ʹ�ܶ�ʱ��9 	

}
//timer12��pwm ch1 ��ʼ������-PB14/PB15
void PWM12_1_2_Init(u32 arr,u32 psc){
	RCC->APB1ENR|=1<<6; 	//TIM12ʱ��ʹ��    
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN14|PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,�������
	GPIO_AF_Set(GPIOB,14,9);	//PB14,AF9 
	GPIO_AF_Set(GPIOB,15,9);	//PA15,AF9 
	
	TIM12->ARR=arr;			//�趨�������Զ���װֵ 
	TIM12->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM12->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM12->CCMR1|=1<<3; 		//CH1 Ԥװ��ʹ��	   
	TIM12->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM12->CCER|=0<<1;   	//OC1 �ߵ�ƽ��Ч	   
	
	TIM12->CCMR1|=6<<12;  	//CH2 PWM2ģʽ		 
	TIM12->CCMR1|=1<<11; 	//CH2 Ԥװ��ʹ��	    
	TIM12->CCER|=1<<4;   	//OC2 ���ʹ��	
	TIM12->CCER|=0<<5;   	//OC2 �ߵ�ƽ��Ч
	
	TIM12->CR1|=1<<7;   		//ARPEʹ�� 
	TIM12->CR1|=1<<0;    	//ʹ�ܶ�ʱ��12 


}

void SERVO_Init(void){
	PWM9_1_2_Init(1800-1,84-1);//ԭΪ20ms,ȡ50Hz���������ڼ����˿��ư壬�ĳ�84-1
	PWM12_1_2_Init(1800-1,84-1);
	
	ServoF_Set(0);
	ServoB_Set(0);
	ServoL_Set(0);
	ServoR_Set(0);
	
}

void ServoF_Set(u8 angle){
	ServoF_VAL=angle*10;
}
void ServoB_Set(u8 angle){
	ServoB_VAL=angle*10;
}
void ServoL_Set(u8 angle){
	ServoL_VAL=angle*10;
}
void ServoR_Set(u8 angle){
	ServoR_VAL=angle*10;
}

/*void PWM11_Init(u32 arr,u32 psc)
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
	TIM11->CCER|=1<<1;   	//OC1 �͵�ƽ��Ч	   
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
	TIM10->CCER|=1<<1;   	//OC1 �͵�ƽ��Ч	   
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

*/








