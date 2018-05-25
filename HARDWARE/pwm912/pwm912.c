#include "pwm912.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//若对写作本程序及硬件团队有意合作请联系   18258583270
//All rights reserved
//2017.2.13
//新增TIM14_PWM_Init函数,用于PWM输出
//0.5ms-------------0度； 	1/40
//1.0ms------------45度；	2/40
//1.5ms------------90度；	3/40
//2.0ms-----------135度；	4/40
//2.5ms-----------180度；	5/40
//
//			PA2-servoF
// 
//	PB14-servoL		PB15-servoR
//
//			PA3-servoB
//

//timer9的pwm ch1 初始化函数-PA2/PA3
void PWM9_1_2_Init(u32 arr,u32 psc)
{
	RCC->APB2ENR|=1<<16; 	//TIM9时钟使能    
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,xia拉输出
	GPIO_AF_Set(GPIOA,2,3);	//PA2,AF3 
	GPIO_AF_Set(GPIOA,3,3);	//PA3,AF3
	
	TIM9->ARR=arr;			//设定计数器自动重装值 
	TIM9->PSC=psc;			//预分频器不分频 
	TIM9->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM9->CCMR1|=1<<3; 		//CH1 预装载使能	   
	TIM9->CCER|=1<<0;   	//OC1 输出使能	
	TIM9->CCER|=0<<1;   	//OC1 高电平有效	   
	
	TIM9->CCMR1|=6<<12;  	//CH2 PWM2模式		 
	TIM9->CCMR1|=1<<11; 	//CH2 预装载使能	    
	TIM9->CCER|=1<<4;   	//OC2 输出使能
	TIM9->CCER|=0<<5;   	//OC2 高电平有效
	
	TIM9->CR1|=1<<7;   		//ARPE使能 
	TIM9->CR1|=1<<0;    	//使能定时器9 	

}
//timer12的pwm ch1 初始化函数-PB14/PB15
void PWM12_1_2_Init(u32 arr,u32 psc){
	RCC->APB1ENR|=1<<6; 	//TIM12时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN14|PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,14,9);	//PB14,AF9 
	GPIO_AF_Set(GPIOB,15,9);	//PA15,AF9 
	
	TIM12->ARR=arr;			//设定计数器自动重装值 
	TIM12->PSC=psc;			//预分频器不分频 
	TIM12->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM12->CCMR1|=1<<3; 		//CH1 预装载使能	   
	TIM12->CCER|=1<<0;   	//OC1 输出使能	
	TIM12->CCER|=0<<1;   	//OC1 高电平有效	   
	
	TIM12->CCMR1|=6<<12;  	//CH2 PWM2模式		 
	TIM12->CCMR1|=1<<11; 	//CH2 预装载使能	    
	TIM12->CCER|=1<<4;   	//OC2 输出使能	
	TIM12->CCER|=0<<5;   	//OC2 高电平有效
	
	TIM12->CR1|=1<<7;   		//ARPE使能 
	TIM12->CR1|=1<<0;    	//使能定时器12 


}

void SERVO_Init(void){
	PWM9_1_2_Init(1800-1,84-1);//原为20ms,取50Hz，现在由于加入了控制板，改成84-1
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

	RCC->APB2ENR|=1<<18; 	//TIM11时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,9,3);	//PB9,AF3
	
	TIM11->ARR=arr;			//设定计数器自动重装值 
	TIM11->PSC=psc;			//预分频器不分频 
	TIM11->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM11->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM11->CCER|=1<<0;   	//OC1 输出使能	
	TIM11->CCER|=1<<1;   	//OC1 低电平有效	   
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
	TIM10->CCER|=1<<1;   	//OC1 低电平有效	   
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

*/








