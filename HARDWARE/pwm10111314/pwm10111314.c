#include "pwm10111314.h"
#include "led.h"
 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//若对写作本程序及硬件团队有意合作,请联系   18258583270
//All rights reserved
//2017.2.13
//新增TIM14_PWM_Init函数,用于PWM输出
//
//	under the circumstance of: my wheels are in the position of:
//
//		10//	^	\\11
//				|
//		13\\		//14
//



//pwm 14 初始化函数-PA7
void PWM14_Init(u32 arr,u32 psc)
{
	RCC->APB1ENR|=1<<8; 	//TIM14时钟使能    
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	GPIO_Set(GPIOA,PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,上拉输出
	GPIO_AF_Set(GPIOA,7,9);	//PA7,AF9 
	
	TIM14->ARR=arr;			//设定计数器自动重装值 
	TIM14->PSC=psc;			//预分频器不分频 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM14->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM14->CCER|=1<<0;   	//OC1 输出使能	
	TIM14->CCER|=0<<1;   	//OC1 高电平有效	   
	TIM14->CR1|=1<<7;   	//ARPE使能 
	TIM14->CR1|=1<<0;    	//使能定时器14 	

}
//pwm 13初始化函数-PA6
void PWM13_Init(u32 arr,u32 psc)
{

	RCC->APB1ENR|=1<<7; 	//TIM13时钟使能    
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	GPIO_Set(GPIOA,PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,上拉输出
	GPIO_AF_Set(GPIOA,6,9);	//PA6,AF9 
	
	TIM13->ARR=arr;			//设定计数器自动重装值 
	TIM13->PSC=psc;			//预分频器不分频 
	TIM13->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM13->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM13->CCER|=1<<0;   	//OC1 输出使能	
	TIM13->CCER|=0<<1;   	//OC1 低高电平有效	   
	TIM13->CR1|=1<<7;   	//ARPE使能 
	TIM13->CR1|=1<<0;    	//使能定时器13 	

}
//pwm 11输出使能-PB9
void PWM11_Init(u32 arr,u32 psc)
{

	RCC->APB2ENR|=1<<18; 	//TIM11时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,9,3);	//PB9,AF3
	
	TIM11->ARR=arr;			//设定计数器自动重装值 
	TIM11->PSC=psc;			//预分频器不分频 
	TIM11->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM11->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM11->CCER|=1<<0;   	//OC1 输出使能	
	TIM11->CCER|=0<<1;   	//OC1 高电平有效	   
	TIM11->CR1|=1<<7;   	//ARPE使能 
	TIM11->CR1|=1<<0;    	//使能定时器11	

}
//pwm 10输出使能-PB8
void PWM10_Init(u32 arr,u32 psc)
{

	RCC->APB2ENR|=1<<17; 	//TIM10时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,8,3);	//PB8,AF3
	
	TIM10->ARR=arr;			//设定计数器自动重装值 
	TIM10->PSC=psc;			//预分频器不分频 
	TIM10->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM10->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM10->CCER|=1<<0;   	//OC1 输出使能	
	TIM10->CCER|=0<<1;   	//OC1 高电平有效	   
	TIM10->CR1|=1<<7;   	//ARPE使能 
	TIM10->CR1|=1<<0;    	//使能定时器10	

}

//TIM14 PWM部分初始化 


//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
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










