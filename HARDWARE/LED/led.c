#include "led.h" 


//PE0  PE1  ����ָʾ��
//PC3      CMDָʾ��

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
	RCC->AHB1ENR|=1<<5;		//ʹ��PORTFʱ�� 
	RCC->AHB1ENR|=1<<2;  	//ʹ��PORTCʱ��
	RCC->AHB1ENR|=1<<4;		//ʹ��PORTEʱ�� 
	
	GPIO_Set(GPIOF,PIN10,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF10����,������
	
	GPIO_Set(GPIOC,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);	//PC3
	GPIO_Set(GPIOE,PIN0|PIN1,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PE0,PE1����,������
	PCout(3)=0;
	PEout(0)=0;
	PEout(1)=0;
}






