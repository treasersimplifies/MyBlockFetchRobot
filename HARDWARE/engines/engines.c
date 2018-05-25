#include "engines.h"
#include "delay.h" 
#include "pwm10111314.h"
#include "gps.h"
#include "pwm912.h"//舵机
#include "usart.h"
//	under the circumstance of: my wheels are in the position of:
//
//		(1)pB7 pB6 10//	^	\\11 pB10 pB11(2)
//						 |
//		(3)pA5 pA4 13\\		//14 pB0 pA8 (4)
//

int	x=1,y=0;//记录位置

void ENGINE1_cor(void){
	PBout(7)=1;
	PBout(6)=0;
}
void ENGINE2_cor(void){
	PBout(11)=1;
	PBout(10)=0;
} 
void ENGINE3_cor(void){
	PAout(5)=1;
	PAout(4)=0;
}
void ENGINE4_cor(void){
	PBout(0)=1;
	PAout(8)=0;
}


void ENGINE1_res(void){
	PBout(7)=0;
	PBout(6)=1;
}
void ENGINE2_res(void){
	PBout(11)=0;
	PBout(10)=1;
}
void ENGINE3_res(void){
	PAout(5)=0;
	PAout(4)=1;
}
void ENGINE4_res(void){
	PBout(0)=0;
	PAout(8)=1;
}
void ENGINES_stop(void){
	PBout(7)=0;
	PBout(6)=0;
	PBout(11)=0;
	PBout(10)=0;
	PAout(5)=0;
	PAout(4)=0;
	PBout(0)=0;
	PAout(8)=0;
}
int ENGINES_Test(void){
	
	return 0;
}
void ENGINES_Init(void){
	
	PWM10111314_Init();	//pwm10111314的全部初始化
	
	RCC->AHB1ENR|=1<<1;//使能PORTB时钟 
	RCC->AHB1ENR|=1<<0;//使能PORTA时钟
	PWM10111314_Init();
	//pwm10-pb8,  int-pb7,pb6,当6低，7高电平时，engine_10正转。
	GPIO_Set(GPIOB,PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PB6,PB7设置,都下拉,
	ENGINE1_cor();
	//pwm11-pb9,  int-pb10,pb11,当10低，11高时，engine_11正转。
	GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PB10,PB11设置,都下拉,
	ENGINE2_cor();
	//pwm13-PA6,  int-PA4,PA5,当4低，5高时，engine_13正转。
	GPIO_Set(GPIOA,PIN4|PIN5,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PA4,PA5设置,都下拉,
	ENGINE3_cor();
	//pwm14-PA7,  int-PA8,PB0,当8低，0高时，engine_14正转。
	GPIO_Set(GPIOA,PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PA8设置,都下拉,
	GPIO_Set(GPIOB,PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PB0设置,都下拉,
	ENGINE4_cor();
	
	SERVO_Init();
}


	

void head_front(void)
{	
	
	ENGINE1_cor();
	ENGINE2_cor();
	ENGINE3_cor();
	ENGINE4_cor();
	//printf("head_front\n");
	/*
	由于直接全速，所以不需要pwm来控制电机速度了
	PWM10_Set(FULL_SPEED);
	PWM11_Set(FULL_SPEED);
	PWM13_Set(FULL_SPEED);
	PWM14_Set(FULL_SPEED);
	ServoB_Set(0);
	ServoR_Set(0);
	ServoF_Set(90);
	ServoL_Set(0);*/
	
}

void head_behind(void){
	
	ENGINE1_res();
	ENGINE2_res();
	ENGINE3_res();
	ENGINE4_res();	
}

void head_left(void){
	
	ENGINE1_res();
	ENGINE2_cor();
	ENGINE3_cor();
	ENGINE4_res();
}


void head_right(void){
	
	ENGINE1_cor();
	ENGINE2_res();
	ENGINE3_res();
	ENGINE4_cor();
}

void head_front_right(void){	//向右上斜45度行进
	
	PBout(7)=1;
	PBout(6)=0;

	PBout(11)=0;
	PBout(10)=0;

	PAout(5)=0;
	PAout(4)=0;

	PBout(0)=1;
	PAout(8)=0;
	
}
void head_front_left(void){		//向左上斜45度行进
	
	PBout(7)=0;
	PBout(6)=0;

	PBout(11)=1;
	PBout(10)=0;

	PAout(5)=1;
	PAout(4)=0;

	PBout(0)=0;
	PAout(8)=0;
	
}
void head_behind_right(void){	//向右下斜45度行进
	
	PBout(7)=0;
	PBout(6)=0;

	PBout(11)=0;
	PBout(10)=1;

	PAout(5)=0;
	PAout(4)=1;

	PBout(0)=0;
	PAout(8)=0;
	
}
void head_behind_left(void){	//向左下斜45度行进
	
	PBout(7)=0;
	PBout(6)=1;

	PBout(11)=0;
	PBout(10)=0;

	PAout(5)=0;
	PAout(4)=0;

	PBout(0)=0;
	PAout(8)=1;
	
}
void clock_wise_right(void){
	PBout(7)=0;
	PBout(6)=0;

	PBout(11)=0;
	PBout(10)=1;

	PAout(5)=0;
	PAout(4)=0;

	PBout(0)=0;
	PAout(8)=1;
}
void clock_wise_left(void){
	PBout(7)=1;
	PBout(6)=0;

	PBout(11)=0;
	PBout(10)=0;

	PAout(5)=1;
	PAout(4)=0;

	PBout(0)=0;
	PAout(8)=0;
}
void anti_clock_front(void){
	PBout(7)=1;
	PBout(6)=0;

	PBout(11)=0;
	PBout(10)=0;

	PAout(5)=1;
	PAout(4)=0;

	PBout(0)=0;
	PAout(8)=0;
}
void anti_clock_behind(void);
//
//
//		(1)10//	^	\\11(2)
//				|
//		(3)13\\		//14(4)
//
//
void clock_wise(void){
	ENGINE1_cor();
	ENGINE2_res();
	ENGINE3_cor();
	ENGINE4_res();
}
void anti_clock(void){
	ENGINE1_res();
	ENGINE2_cor();
	ENGINE3_res();
	ENGINE4_cor();
	//printf("anti_clock\n");
	/*
	由于直接全速，所以不需要pwm来控制电机速度了
	PWM10_Set(FULL_SPEED);
	PWM11_Set(FULL_SPEED);
	PWM13_Set(FULL_SPEED);
	PWM14_Set(FULL_SPEED);*/
}

void clock_wise_90(void){

	clock_wise();
	delay_ms(300);
	
	while(IR_Front()!=-1){
		clock_wise();
	}
	while(IR_Front()!=0){
		clock_wise();
	}
	ENGINES_stop();
}
void anti_clock_90(void){
	anti_clock();
	delay_ms(300);
	
	while(IR_Front()!=1){
		anti_clock();
	}
	while(IR_Front()!=0){
		anti_clock();
	}
	ENGINES_stop();
}

//int IR_Front(void);
//int IR_Behind(void);
//int IR_Left(void);
//int IR_Right(void);
//有以下组合：(0,0) (1,0) (0,1) (1,1) (-1,0) (0,-1) (-1,-1)  

//没有考虑丢失路径的情况，即返回407；
int gof_error2(void){
	int f = IR_Front();
	int b = IR_Behind();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(80);
	ServoF_Set(0);
	
	if((f==0&&b==0)||(f==407&&b==407)||(f==0&&b==407)||(f==407&&b==0)||(f==-1&&b==407)||(f==407&&b==1)||(f==1&&b==407)||(f==407&&b==-1))
		head_front();
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//表示该顺时针转了,小车形如：'\'
	{	
		ENGINES_stop();
		if(f==0&&b==1)
		{
			ENGINE1_cor();
			ENGINE2_cor();
			ENGINE3_cor();
		}
		if(f==-1&&b==0)
		{
			ENGINE1_cor();
			ENGINE3_cor();
			ENGINE4_cor();
		}
		if(f==-1&&b==1)
		{
			ENGINE1_cor();
			ENGINE3_cor();
		}
		
		
	}
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//表示该逆时针转了,小车形如：'/'
	{	
		ENGINES_stop();
		if(f==0&&b==-1)
		{
			ENGINE1_cor();
			ENGINE2_cor();
			ENGINE4_cor();
		}
		if(f==1&&b==0)
		{
			ENGINE2_cor();
			ENGINE3_cor();
			ENGINE4_cor();
		}
		if(f==1&&b==-1)
		{
			ENGINE2_cor();
			ENGINE4_cor();
		}
		
	}
	if(f==1&&b==1)	//小车太偏右了,不考虑407
		head_front_left();
	if(f==-1&&b==-1)	//小车太偏左了
		head_front_right();
	return 0;

}
int gof_error(void){
	int f = IR_Front();
	int b = IR_Behind();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	
	if((f==0&&b==0)||(f==407&&b==407)||(f==0&&b==407)||(f==407&&b==0)||(f==-1&&b==407)||(f==407&&b==1)||(f==1&&b==407)||(f==407&&b==-1))
		head_front();
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//表示该顺时针转了,小车形如：'\'
	{	
		ENGINES_stop();
		if(f==0&&b==1)
		{
			ENGINE1_cor();
			ENGINE2_cor();
			ENGINE3_cor();
		}
		if(f==-1&&b==0)
		{
			ENGINE1_cor();
			ENGINE3_cor();
			ENGINE4_cor();
		}
		if(f==-1&&b==1)
		{
			ENGINE1_cor();
			ENGINE3_cor();
		}
		
		
	}
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//表示该逆时针转了,小车形如：'/'
	{	
		ENGINES_stop();
		if(f==0&&b==-1)
		{
			ENGINE1_cor();
			ENGINE2_cor();
			ENGINE4_cor();
		}
		if(f==1&&b==0)
		{
			ENGINE2_cor();
			ENGINE3_cor();
			ENGINE4_cor();
		}
		if(f==1&&b==-1)
		{
			ENGINE2_cor();
			ENGINE4_cor();
		}
		
	}
	if(f==1&&b==1)	//小车太偏右了,不考虑407
		head_front_left();
	if(f==-1&&b==-1)	//小车太偏左了
		head_front_right();
	return 0;

}

int gof(void){//check
	int f = IR_Front();
	int b = IR_Behind();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(75);
	
	if((f==0&&b==0)||(f==407&&b==407)||(f==0&&b==407)||(f==407&&b==0)||(f==-1&&b==407)||(f==407&&b==1)||(f==1&&b==407)||(f==407&&b==-1))
		head_front();
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//表示该顺时针转了,小车形如：'\'
	{	
		ENGINES_stop();
		if(f==0&&b==1)
		{
			ENGINE1_cor();
			ENGINE2_cor();
			ENGINE3_cor();
		}
		if(f==-1&&b==0)
		{
			ENGINE1_cor();
			ENGINE3_cor();
			ENGINE4_cor();
		}
		if(f==-1&&b==1)
		{
			ENGINE1_cor();
			ENGINE3_cor();
		}
		
		
	}
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//表示该逆时针转了,小车形如：'/'
	{	
		ENGINES_stop();
		if(f==0&&b==-1)
		{
			ENGINE1_cor();
			ENGINE2_cor();
			ENGINE4_cor();
		}
		if(f==1&&b==0)
		{
			ENGINE2_cor();
			ENGINE3_cor();
			ENGINE4_cor();
		}
		if(f==1&&b==-1)
		{
			ENGINE2_cor();
			ENGINE4_cor();
		}
		
	}
	if(f==1&&b==1)	//小车太偏右了,不考虑407
		head_front_left();
	if(f==-1&&b==-1)	//小车太偏左了
		head_front_right();
	return 0;
}


int gob_error2(void){
	int f = IR_Front();
	int b = IR_Behind();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(80);
	ServoF_Set(0);
	if((f==0&&b==0)||(f==407&&b==407)||(f==0&&b==407)||(f==407&&b==0)||(f==-1&&b==407)||(f==407&&b==1)||(f==1&&b==407)||(f==407&&b==-1))
		head_behind();
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//表示该顺时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(f==0&&b==1)
		{
			ENGINE1_res();
			ENGINE2_res();
			ENGINE4_res();
		}
		if(f==-1&&b==0)
		{
			ENGINE2_res();
			ENGINE3_res();
			ENGINE4_res();
		}
		if(f==-1&&b==1)
		{
			ENGINE2_res();
			ENGINE4_res();
		}
		
	}
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//表示该逆时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(f==0&&b==-1)
		{
			ENGINE1_res();
			ENGINE2_res();
			ENGINE3_res();
		}
		if(f==1&&b==0)
		{
			ENGINE1_res();
			ENGINE3_res();
			ENGINE4_res();
		}
		if(f==1&&b==-1)
		{
			ENGINE1_res();
			ENGINE3_res();
		}
		
	}
	if(f==1&&b==1)	//小车太偏右了,不考虑407
		head_behind_left();
	if(f==-1&&b==-1)	//小车太偏左了
		head_behind_right();
	return 0;

}


int gob_error(void){
	int f = IR_Front();
	int b = IR_Behind();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	if((f==0&&b==0)||(f==407&&b==407)||(f==0&&b==407)||(f==407&&b==0)||(f==-1&&b==407)||(f==407&&b==1)||(f==1&&b==407)||(f==407&&b==-1))
		head_behind();
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//表示该顺时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(f==0&&b==1)
		{
			ENGINE1_res();
			ENGINE2_res();
			ENGINE4_res();
		}
		if(f==-1&&b==0)
		{
			ENGINE2_res();
			ENGINE3_res();
			ENGINE4_res();
		}
		if(f==-1&&b==1)
		{
			ENGINE2_res();
			ENGINE4_res();
		}
		
	}
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//表示该逆时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(f==0&&b==-1)
		{
			ENGINE1_res();
			ENGINE2_res();
			ENGINE3_res();
		}
		if(f==1&&b==0)
		{
			ENGINE1_res();
			ENGINE3_res();
			ENGINE4_res();
		}
		if(f==1&&b==-1)
		{
			ENGINE1_res();
			ENGINE3_res();
		}
		
	}
	if(f==1&&b==1)	//小车太偏右了,不考虑407
		head_behind_left();
	if(f==-1&&b==-1)	//小车太偏左了
		head_behind_right();
	return 0;

}


int gob(void){//check
	int f = IR_Front();
	int b = IR_Behind();
	
	ServoB_Set(75);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	if((f==0&&b==0)||(f==407&&b==407)||(f==0&&b==407)||(f==407&&b==0)||(f==-1&&b==407)||(f==407&&b==1)||(f==1&&b==407)||(f==407&&b==-1))
		head_behind();
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//表示该顺时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(f==0&&b==1)
		{
			ENGINE1_res();
			ENGINE2_res();
			ENGINE4_res();
		}
		if(f==-1&&b==0)
		{
			ENGINE2_res();
			ENGINE3_res();
			ENGINE4_res();
		}
		if(f==-1&&b==1)
		{
			ENGINE2_res();
			ENGINE4_res();
		}
		
	}
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//表示该逆时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(f==0&&b==-1)
		{
			ENGINE1_res();
			ENGINE2_res();
			ENGINE3_res();
		}
		if(f==1&&b==0)
		{
			ENGINE1_res();
			ENGINE3_res();
			ENGINE4_res();
		}
		if(f==1&&b==-1)
		{
			ENGINE1_res();
			ENGINE3_res();
		}
		
	}
	if(f==1&&b==1)	//小车太偏右了,不考虑407
		head_behind_left();
	if(f==-1&&b==-1)	//小车太偏左了
		head_behind_right();
	return 0;
	/*if(((IR_Front())==0&&(IR_Behind()==0))||((IR_Front()==407)&&(IR_Behind()==407)))
		head_behind();
	else if(IR_Front()<IR_Behind())	//表示该顺时针转了,小车形如：'\'
		clock_wise();
	else if(IR_Front()>IR_Behind())	//表示该逆时针转了,小车形如：'/'
		anti_clock();
	else if((IR_Front()==IR_Behind())&&(IR_Front()>0)&&(IR_Front()<3))	//小车太偏右了,不考虑407
		head_left();
	else if((IR_Front()==IR_Behind())&&(IR_Front()<0))	//小车太偏左了
		head_right();*/
}

int gor_error2(void){
	int r = IR_Right();
	int l = IR_Left();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(80);
	ServoF_Set(0);
	if((r==0&&l==0)||(r==407&&l==407)||(r==0&&l==407)||(r==407&&l==0)||(r==-1&&l==407)||(r==407&&l==1)||(r==1&&l==407)||(r==407&&l==-1))
		head_right();
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//表示该顺时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(r==0&&l==1)
		{
			ENGINE1_cor();
			ENGINE2_res();
			ENGINE4_cor();
		}
		if(r==-1&&l==0)
		{
			ENGINE1_cor();
			ENGINE2_res();
			ENGINE3_res();	
		}
		if(r==-1&&l==1)
		{
			ENGINE1_cor();
			ENGINE2_res();	
		}
	}
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//表示该逆时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(r==0&&l==-1)
		{
			ENGINE2_res();
			ENGINE3_res();
			ENGINE4_cor();
		}
		if(r==1&&l==0)
		{
			ENGINE1_cor();
			ENGINE3_res();
			ENGINE4_cor();
		}
		if(r==1&&l==-1)
		{
			ENGINE3_res();
			ENGINE4_cor();
		}
	}
	if(r==1&&l==1)	//小车太偏下了,不考虑407
		head_front_right();
	if(r==-1&&l==-1)	//小车太偏上了
		head_behind_right();
	return 0;
}
int gor_error(void){
	int r = IR_Right();
	int l = IR_Left();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	if((r==0&&l==0)||(r==407&&l==407)||(r==0&&l==407)||(r==407&&l==0)||(r==-1&&l==407)||(r==407&&l==1)||(r==1&&l==407)||(r==407&&l==-1))
		head_right();
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//表示该顺时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(r==0&&l==1)
		{
			ENGINE1_cor();
			ENGINE2_res();
			ENGINE4_cor();
		}
		if(r==-1&&l==0)
		{
			ENGINE1_cor();
			ENGINE2_res();
			ENGINE3_res();	
		}
		if(r==-1&&l==1)
		{
			ENGINE1_cor();
			ENGINE2_res();	
		}
	}
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//表示该逆时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(r==0&&l==-1)
		{
			ENGINE2_res();
			ENGINE3_res();
			ENGINE4_cor();
		}
		if(r==1&&l==0)
		{
			ENGINE1_cor();
			ENGINE3_res();
			ENGINE4_cor();
		}
		if(r==1&&l==-1)
		{
			ENGINE3_res();
			ENGINE4_cor();
		}
	}
	if(r==1&&l==1)	//小车太偏下了,不考虑407
		head_front_right();
	if(r==-1&&l==-1)	//小车太偏上了
		head_behind_right();
	return 0;
}


int gor(void){//check
	int r = IR_Right();
	int l = IR_Left();
	
	ServoB_Set(0);
	ServoR_Set(75);
	ServoL_Set(0);
	ServoF_Set(0);
	
	if((r==0&&l==0)||(r==407&&l==407)||(r==0&&l==407)||(r==407&&l==0)||(r==-1&&l==407)||(r==407&&l==1)||(r==1&&l==407)||(r==407&&l==-1))
		head_right();
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//表示该顺时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(r==0&&l==1)
		{
			ENGINE1_cor();
			ENGINE2_res();
			ENGINE4_cor();
		}
		if(r==-1&&l==0)
		{
			ENGINE1_cor();
			ENGINE2_res();
			ENGINE3_res();	
		}
		if(r==-1&&l==1)
		{
			ENGINE1_cor();
			ENGINE2_res();	
		}
	}
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//表示该逆时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(r==0&&l==-1)
		{
			ENGINE2_res();
			ENGINE3_res();
			ENGINE4_cor();
		}
		if(r==1&&l==0)
		{
			ENGINE1_cor();
			ENGINE3_res();
			ENGINE4_cor();
		}
		if(r==1&&l==-1)
		{
			ENGINE3_res();
			ENGINE4_cor();
		}
	}
	if(r==1&&l==1)	//小车太偏下了,不考虑407
		head_front_right();
	if(r==-1&&l==-1)	//小车太偏上了
		head_behind_right();
	return 0;
}


int gol_error2(void){
	int r = IR_Right();
	int l = IR_Left();
	
	ServoB_Set(0);
	ServoR_Set(80);
	ServoL_Set(0);
	ServoF_Set(0);
	if((r==0&&l==0)||(r==407&&l==407)||(r==0&&l==407)||(r==407&&l==0)||(r==-1&&l==407)||(r==407&&l==1)||(r==1&&l==407)||(r==407&&l==-1))
		head_left();
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//表示该顺时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(r==0&&l==1)
		{
			ENGINE2_cor();
			ENGINE3_cor();
			ENGINE4_res();
		}
		if(r==-1&&l==0)
		{
			ENGINE1_res();
			ENGINE3_cor();
			ENGINE4_res();
		}
		if(r==-1&&l==1)
		{
			ENGINE3_cor();
			ENGINE4_res();
		}
	}
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//表示该逆时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(r==0&&l==-1)
		{
			ENGINE1_res();
			ENGINE2_cor();
			ENGINE4_res();
		}
		if(r==1&&l==0)
		{
			ENGINE1_res();
			ENGINE2_cor();
			ENGINE3_cor();
		}
		if(r==1&&l==-1)
		{
			ENGINE1_res();
			ENGINE2_cor();
		}
	}
	if(r==1&&l==1)	//小车太偏下了,不考虑407
		head_front_left();
	if(r==-1&&l==-1)	//小车太偏上了
		head_behind_left();
	return 0;

}
int gol_error(void){
	int r = IR_Right();
	int l = IR_Left();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	if((r==0&&l==0)||(r==407&&l==407)||(r==0&&l==407)||(r==407&&l==0)||(r==-1&&l==407)||(r==407&&l==1)||(r==1&&l==407)||(r==407&&l==-1))
		head_left();
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//表示该顺时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(r==0&&l==1)
		{
			ENGINE2_cor();
			ENGINE3_cor();
			ENGINE4_res();
		}
		if(r==-1&&l==0)
		{
			ENGINE1_res();
			ENGINE3_cor();
			ENGINE4_res();
		}
		if(r==-1&&l==1)
		{
			ENGINE3_cor();
			ENGINE4_res();
		}
	}
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//表示该逆时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(r==0&&l==-1)
		{
			ENGINE1_res();
			ENGINE2_cor();
			ENGINE4_res();
		}
		if(r==1&&l==0)
		{
			ENGINE1_res();
			ENGINE2_cor();
			ENGINE3_cor();
		}
		if(r==1&&l==-1)
		{
			ENGINE1_res();
			ENGINE2_cor();
		}
	}
	if(r==1&&l==1)	//小车太偏下了,不考虑407
		head_front_left();
	if(r==-1&&l==-1)	//小车太偏上了
		head_behind_left();
	return 0;

}


int gol(void){//check
	int r = IR_Right();
	int l = IR_Left();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(75);
	ServoF_Set(0);
	if((r==0&&l==0)||(r==407&&l==407)||(r==0&&l==407)||(r==407&&l==0)||(r==-1&&l==407)||(r==407&&l==1)||(r==1&&l==407)||(r==407&&l==-1))
		head_left();
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//表示该顺时针转了,小车形如：'/'
	{
		ENGINES_stop();
		if(r==0&&l==1)
		{
			ENGINE2_cor();
			ENGINE3_cor();
			ENGINE4_res();
		}
		if(r==-1&&l==0)
		{
			ENGINE1_res();
			ENGINE3_cor();
			ENGINE4_res();
		}
		if(r==-1&&l==1)
		{
			ENGINE3_cor();
			ENGINE4_res();
		}
	}
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//表示该逆时针转了,小车形如：'\'
	{
		ENGINES_stop();
		if(r==0&&l==-1)
		{
			ENGINE1_res();
			ENGINE2_cor();
			ENGINE4_res();
		}
		if(r==1&&l==0)
		{
			ENGINE1_res();
			ENGINE2_cor();
			ENGINE3_cor();
		}
		if(r==1&&l==-1)
		{
			ENGINE1_res();
			ENGINE2_cor();
		}
	}
	if(r==1&&l==1)	//小车太偏下了,不考虑407
		head_front_left();
	if(r==-1&&l==-1)	//小车太偏上了
		head_behind_left();
	return 0;
	/*if(((IR_Left()==0)&&(IR_Right()==0))||((IR_Left()==407)&&(IR_Right()==407)))
		head_left();
	else if(IR_Right()>IR_Left())	//表示该 逆时针转了,小车形如：'\'
		anti_clock();
	else if(IR_Right()<IR_Left())	//表示该 顺时针转了,小车形如：'/'
		clock_wise();
	else if((IR_Right()==IR_Left())&&(IR_Left()>0)&&(IR_Left()<3))	//小车太偏右了,不考虑407
		head_front();
	else if((IR_Right()==IR_Left())&&(IR_Left()<0))	//小车太偏左了
		head_behind();*/
}

//
//			PB2   PA14
//
//PC0							PD0
//
//PC1							PD1						
//
//			PG13   PG14
void go_delta_l_error2(u8 dx){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	
	while(count!=dx){
		if(dx>0){
			
			gol_error2();			
			
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;						//初始状态，左右IR都是返回0
			if(IR_Behind()==1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{								//加上flag的判断条件是为了使得其在初始化以后的判断才是有效
				while(IR_Behind()!=-1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Front()!=-1);
				flag=-1;
				count++;
				continue;
			}	
			
		}
		else
			ENGINES_stop();
	}
	gor();		
}
void go_delta_l_error(u8 dx){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	
	while(count!=dx){
		if(dx>0){
			
			gol_error();
			ServoL_Set(0);
			ServoF_Set(0);
			ServoB_Set(0);
			ServoR_Set(0);			
			
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;						//初始状态，左右IR都是返回0
			if(IR_Behind()==1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{								//加上flag的判断条件是为了使得其在初始化以后的判断才是有效
				while(IR_Behind()!=-1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Front()!=-1);
				flag=-1;
				count++;
				continue;
			}	
			
		}
		else
			ENGINES_stop();
	}
	gor();		
}

void go_delta_l(u8 dx){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	
	while(count!=dx){
		if(dx>0){
			ServoL_Set(75);
			ServoF_Set(0);
			ServoB_Set(0);
			ServoR_Set(0);
			gol();	
			
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;						//初始状态，左右IR都是返回0
			if(IR_Behind()==1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{								//加上flag的判断条件是为了使得其在初始化以后的判断才是有效
				while(IR_Behind()!=-1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Front()!=-1);
				flag=-1;
				count++;
				continue;
			}	
			
		}
		else
			ENGINES_stop();
	}
	gor();		
	/*ENGINE1_cor();
	ENGINE2_res();
	ENGINE3_res();
	ENGINE4_cor();*/
	//ENGINES_stop();
}


void go_delta_r_error2(u8 dx){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0

	while(count!=dx){
		if(dx>0){
			gor_error2();
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Behind()==-1&&flag==0)		//IR后边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Behind()!=1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==-1&&flag==0)		//IR前边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Front()!=1);
				flag=-1;
				count++;
				continue;
			}	
			
		}
		else
			ENGINES_stop();
	}	
	gol();
}

void go_delta_r_error(u8 dx){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0

	while(count!=dx){
		if(dx>0){
			
			gor_error();
			ServoR_Set(0);
			ServoF_Set(0);
			ServoB_Set(0);
			ServoL_Set(0);
			
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Behind()==-1&&flag==0)		//IR后边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Behind()!=1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==-1&&flag==0)		//IR前边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Front()!=1);
				flag=-1;
				count++;
				continue;
			}	
			
		}
		else
			ENGINES_stop();
	}	
	gol();
}

void go_delta_r(u8 dx){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0

	while(count!=dx){
		if(dx>0){
			ServoR_Set(75);
			ServoF_Set(0);
			ServoB_Set(0);
			ServoL_Set(0);
			gor();
			
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Behind()==-1&&flag==0)		//IR后边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Behind()!=1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==-1&&flag==0)		//IR前边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Front()!=1);
				flag=-1;
				count++;
				continue;
			}	
			
		}
		else
			ENGINES_stop();
	}	
	gol();
	/*ENGINE1_res();
	ENGINE2_cor();
	ENGINE3_cor();
	ENGINE4_res();*/
	//ENGINES_stop();
}
//
//			PB2   PA14
//
//PC0							PD0
//
//PC1							PD1						
//
//			PG13   PG14
//
//

void go_delta_f_error2(u8 dy){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	/*if(IR_Right()!=0||IR_Left()!=0)		
	{	
		gof();
		delay_ms(300);
	}	*/
	while(count!=dy){
		if(dy>0){	
			gof_error2();
		}
		if(dy>0){	
			if(IR_Right()==0&&IR_Left()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Right()==1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Right()!=-1);
				flag=1;					//将flag置1，防止其在交叉线上多计数一次
				count++;
				continue;
			}	
			if(IR_Left()==1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Left()!=-1);
				flag=-1;
				count++;
				continue;
			}	
		}
		else
			ENGINES_stop();
			
	}
	gob();
}

void go_delta_f_error(u8 dy){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	/*if(IR_Right()!=0||IR_Left()!=0)		
	{	
		gof();
		delay_ms(300);
	}	*/
	while(count!=dy){
		if(dy>0){	
			
			gof_error();
			ServoF_Set(0);
			ServoB_Set(0);
			ServoR_Set(0);
			ServoL_Set(0);
			
		}
		if(dy>0){	
			if(IR_Right()==0&&IR_Left()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Right()==1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Right()!=-1);
				flag=1;					//将flag置1，防止其在交叉线上多计数一次
				count++;
				continue;
			}	
			if(IR_Left()==1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Left()!=-1);
				flag=-1;
				count++;
				continue;
			}	
		}
		else
			ENGINES_stop();
			
	}
	gob();
}


void go_delta_f(u8 dy){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	/*if(IR_Right()!=0||IR_Left()!=0)		
	{	
		gof();
		delay_ms(300);
	}	*/
	while(count!=dy){
		if(dy>0){	
			ServoF_Set(75);
			ServoB_Set(0);
			ServoR_Set(0);
			ServoL_Set(0);
			gof();
			
		}
		if(dy>0){	
			if(IR_Right()==0&&IR_Left()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Right()==1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Right()!=-1);
				flag=1;					//将flag置1，防止其在交叉线上多计数一次
				count++;
				continue;
			}	
			if(IR_Left()==1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Left()!=-1);
				flag=-1;
				count++;
				continue;
			}	
		}
		else
			ENGINES_stop();
			
	}
	gob();
	/*ENGINE1_res();
	ENGINE2_res();
	ENGINE3_res();
	ENGINE4_res();*/
	//ENGINES_stop();
	
}



void go_delta_b_error2(u8 dy){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	
	while(count!=dy){
		if(dy>0){	
			gob_error2();			
		}
		if(dy>0){	
			if(IR_Right()==0&&IR_Left()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Right()==-1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Right()!=1);
				flag=1;
				count++; 
				continue;
			}	
			if(IR_Left()==-1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Left()!=1);
				flag=-1;
				count++;
				continue;
			}	
		}	
		else
			ENGINES_stop();
	}
	gof();
}


void go_delta_b_error(u8 dy){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	
	while(count!=dy){
		if(dy>0){	
			
			gob_error();
			ServoB_Set(0);
			ServoF_Set(0);
			ServoR_Set(0);
			ServoL_Set(0);
			
		}
		if(dy>0){	
			if(IR_Right()==0&&IR_Left()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Right()==-1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Right()!=1);
				flag=1;
				count++; 
				continue;
			}	
			if(IR_Left()==-1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Left()!=1);
				flag=-1;
				count++;
				continue;
			}	
		}	
		else
			ENGINES_stop();
	}
	gof();
}


void go_delta_b(u8 dy){
	int count=0;
	int flag=404;
	//初始状态，左右IR都是返回0
	
	while(count!=dy){
		if(dy>0){	
			ServoB_Set(75);
			ServoF_Set(0);
			ServoR_Set(0);
			ServoL_Set(0);
			gob();
			
		}
		if(dy>0){	
			if(IR_Right()==0&&IR_Left()==0)
				flag=0;			//初始状态，左右IR都是返回0
			if(IR_Right()==-1&&flag==0)		//IR右边先到了交叉线上  此时小车形如  '/'
			{	
				while(IR_Right()!=1);
				flag=1;
				count++; 
				continue;
			}	
			if(IR_Left()==-1&&flag==0)		//IR左边先到了交叉线上  此时小车形如  '\'
			{	
				while(IR_Left()!=1);
				flag=-1;
				count++;
				continue;
			}	
		}	
		else
			ENGINES_stop();
	}
	gof();
	/*ENGINE1_cor();
	ENGINE2_cor();
	ENGINE3_cor();
	ENGINE4_cor();*/
	//ENGINES_stop();
	
}

/*
void gox(u8 dx){
	//go_delta_x用于向左右的移动。此时需要用到前后的IR来进行计数
	int	x0=x;//记录刚使用该函数时的x位置
	u8 state=IR_Behind()||IR_Front();
	u8 flag;
	if(dx>x0)
		flag=-1;     //=-1时，为x++标志
	else if(dx<x0)
		flag=1;      //=1时，为x++标志
	while(x!=dx)
	{	
		if(dx>x)	//目标位置大于当前位置
		{	gor();
			if(state==flag)
			{	
				x++;
				if(x==dx)break;
				while(state==flag);
			}
		}
		else if(dx<x)
			{	gol();
			if(state==flag)
			{	
				x--;
				if(x==dx)break;
				while(state==flag);
			}
		}			
	}

}



void goy(u8 dy){
	int	y0=y;//记录刚使用该函数时的位置
	u8 state=IR_Right()||IR_Left();
	u8 flag;
	if(dy>y0)
		flag=-1;     //=-1时，为x++标志
	else if(dy<y0)
		flag=1;      //=1时，为x++标志
	while(y!=dy)
	{	
		if(dy>y)	//目标位置大于当前位置
		{	gof();
			if(state==flag)
			{	
				y++;
				if(y==dy)break;
				while(state==flag);
			}
		}
		else if(dy<y)
			{	gob();
			if(state==flag)
			{	
				y--;
				if(y==dy)break;
				while(state==flag);
			}
		}			
	}
	
}
*/





