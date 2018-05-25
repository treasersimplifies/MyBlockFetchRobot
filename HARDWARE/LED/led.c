#include "led.h" 


//PE0  PE1  方块指示灯
//PC3      CMD指示灯

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
	RCC->AHB1ENR|=1<<5;		//使能PORTF时钟 
	RCC->AHB1ENR|=1<<2;  	//使能PORTC时钟
	RCC->AHB1ENR|=1<<4;		//使能PORTE时钟 
	
	GPIO_Set(GPIOF,PIN10,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF10设置,都下拉
	
	GPIO_Set(GPIOC,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);	//PC3
	GPIO_Set(GPIOE,PIN0|PIN1,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PE0,PE1设置,都下拉
	PCout(3)=0;
	PEout(0)=0;
	PEout(1)=0;
}






