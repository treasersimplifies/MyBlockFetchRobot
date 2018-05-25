#include "gps.h"
#include "delay.h" 
#include "usart.h"
//PA13/14  PB2  PC0/1/4/5  PD0/1  PG13/14/15 
//
//  the sensitor positions are:
//
//			PA13/PA14/PB2
//
//PC0							PC5
//PC1							PD0
//PC4							PD1
//
//			PG13/PG14/PG15

//  NOW  NOW  NOW！ sensitor positions are:
//
//			PB2   PA14
//
//PC0							PD0
//
//PC1							PD1						
//
//			PG13   PG14
//
//可以以IR_Front和IR_Right为基准，如果遇到意外，就再使用其他2个IR
//ATN:这里除了IR-Front和IR-Right是符合顺时针规则的，其他2个都只是跟从前2个而已，看清楚

void IR_gpsInit(){

	RCC->AHB1ENR|=1<<0;//使能PORTA时钟 
	GPIO_Set(GPIOA,PIN13|PIN14,GPIO_MODE_IN,
		GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PA13,PA14设置,都下拉输入
	RCC->AHB1ENR|=1<<1;//使能PORTB时钟 
	GPIO_Set(GPIOB,PIN2,GPIO_MODE_IN,
		GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PB2设置,都下拉输入
	
	RCC->AHB1ENR|=1<<2;//使能PORTC时钟 
	GPIO_Set(GPIOC,PIN0|PIN1,GPIO_MODE_IN,
		GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PC0/1设置,都下拉输入
	GPIO_Set(GPIOC,PIN4,GPIO_MODE_IN,
		GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PC4设置,都下拉输入
	
	GPIO_Set(GPIOC,PIN5,GPIO_MODE_IN,
		GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PC5设置,都下拉输入
	RCC->AHB1ENR|=1<<3;//使能PORTD时钟 
	GPIO_Set(GPIOD,PIN0|PIN1,GPIO_MODE_IN,
		GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PD0/1设置,都下拉输入
	
	RCC->AHB1ENR|=1<<6;//使能PORTG时钟 
	GPIO_Set(GPIOG,PIN13|PIN14|PIN15,GPIO_MODE_IN,
		GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PG13/14/15设置,都下拉输入

}
void GPS_Init(void){

	IR_gpsInit();
}
int GPS_Test(void){
	int f=IR_Front();
	int b=IR_Behind();
	int r=IR_Right();
	int l=IR_Left();
	
	printf("IR_test starting...");
	printf("\n");
	printf("IR_Front = %d\n",f);
	printf("\n");
	printf("IR_Behind = %d\n",b);
	printf("\n");
	printf("IR_Right = %d\n",r);
	printf("\n");
	printf("IR_Left = %d\n",l);
	printf("\n");
	
	return 0;
}
//   PA13  PA14   PB2
//		|1 1 1|		-good, 0
//		|  1 1|0	-toor, 1
//	   0|1 1  |		-toof,-1
//	 0 0|1    |		-sol, -2
//		|    1|0 0 	-sor,  2
//     
//   PA13    PA14 
//		0|   |0
//		 |1  |0			,太靠右，return 1；
//  	0|  1|
//      11  ,return 407
int IR_Front(void){//沿黑边者  !
	int F1=PBin(2);
	int F2=PAin(14);
	
	if(F1==0&&F2==0)
		return 0;
	else if(F1==1&&F2==0)
		return 1;
	else if(F1==0&&F2==1)
		return -1;
	else 
		return 407;				//更糟糕的情况：出错了
}
//   PG13  PG14   PG15
//		|1 1 1|		-good, 0
//		|  1 1|0	-toor, 1
//	   0|1 1  |		-toof,-1
//	 0 0|1    |		-sol, -2
//		|    1|0 0 	-sor,  2
//
//   PG13    PG14 
//		0|   |0
//		 |1  |0		,1
//  	0|  1|
int IR_Behind(void){
	int F1=PGin(13);
	int F2=PGin(14);

	
	if(F1==0&&F2==0)
		return 0;
	else if(F1==1&&F2==0)
		return 1;
	else if(F1==0&&F2==1)
		return -1;
	else 
		return 407;
}
//   PC5  PD0   PD1
//		|1 1 1|		-good, 0
//		|  1 1|0	-toor, 1
//	   0|1 1  |		-toof,-1
//	 0 0|1    |		-sol, -2
//		|    1|0 0 	-sor,  2

//
//    PD0      PD1 
//		0|   |0
//		 |1  |0		,1
//  	0|  1|
//
int IR_Right(void){

	int F1=PDin(0);
	int F2=PDin(1);
	
	if(F1==0&&F2==0)
		return 0;
	else if(F1==1&&F2==0)
		return 1;
	else if(F1==0&&F2==1)
		return -1;
	else 
		return 407;
}
//
//   PC0  PC1   PC4
//		|1 1 1|		-good, 0
//		|  1 1|0	-toor, 1
//	   0|1 1  |		-toof,-1
//	 0 0|1    |		-sol, -2
//		|    1|0 0 	-sor,  2
//
int IR_Left(void){
	int F1=PCin(0);
	int F2=PCin(1);

	
	if(F1==0&&F2==0)
		return 0;
	else if(F1==1&&F2==0)
		return 1;
	else if(F1==0&&F2==1)
		return -1;
	else 
		return 407;
}








