#include "engines.h"
#include "delay.h" 
#include "pwm10111314.h"
#include "gps.h"
#include "pwm912.h"//���
#include "usart.h"
//	under the circumstance of: my wheels are in the position of:
//
//		(1)pB7 pB6 10//	^	\\11 pB10 pB11(2)
//						 |
//		(3)pA5 pA4 13\\		//14 pB0 pA8 (4)
//

int	x=1,y=0;//��¼λ��

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
	
	PWM10111314_Init();	//pwm10111314��ȫ����ʼ��
	
	RCC->AHB1ENR|=1<<1;//ʹ��PORTBʱ�� 
	RCC->AHB1ENR|=1<<0;//ʹ��PORTAʱ��
	PWM10111314_Init();
	//pwm10-pb8,  int-pb7,pb6,��6�ͣ�7�ߵ�ƽʱ��engine_10��ת��
	GPIO_Set(GPIOB,PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PB6,PB7����,������,
	ENGINE1_cor();
	//pwm11-pb9,  int-pb10,pb11,��10�ͣ�11��ʱ��engine_11��ת��
	GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PB10,PB11����,������,
	ENGINE2_cor();
	//pwm13-PA6,  int-PA4,PA5,��4�ͣ�5��ʱ��engine_13��ת��
	GPIO_Set(GPIOA,PIN4|PIN5,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PA4,PA5����,������,
	ENGINE3_cor();
	//pwm14-PA7,  int-PA8,PB0,��8�ͣ�0��ʱ��engine_14��ת��
	GPIO_Set(GPIOA,PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PA8����,������,
	GPIO_Set(GPIOB,PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,
	GPIO_SPEED_100M,GPIO_PUPD_PD); //PB0����,������,
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
	����ֱ��ȫ�٣����Բ���Ҫpwm�����Ƶ���ٶ���
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

void head_front_right(void){	//������б45���н�
	
	PBout(7)=1;
	PBout(6)=0;

	PBout(11)=0;
	PBout(10)=0;

	PAout(5)=0;
	PAout(4)=0;

	PBout(0)=1;
	PAout(8)=0;
	
}
void head_front_left(void){		//������б45���н�
	
	PBout(7)=0;
	PBout(6)=0;

	PBout(11)=1;
	PBout(10)=0;

	PAout(5)=1;
	PAout(4)=0;

	PBout(0)=0;
	PAout(8)=0;
	
}
void head_behind_right(void){	//������б45���н�
	
	PBout(7)=0;
	PBout(6)=0;

	PBout(11)=0;
	PBout(10)=1;

	PAout(5)=0;
	PAout(4)=1;

	PBout(0)=0;
	PAout(8)=0;
	
}
void head_behind_left(void){	//������б45���н�
	
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
	����ֱ��ȫ�٣����Բ���Ҫpwm�����Ƶ���ٶ���
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
//��������ϣ�(0,0) (1,0) (0,1) (1,1) (-1,0) (0,-1) (-1,-1)  

//û�п��Ƕ�ʧ·���������������407��
int gof_error2(void){
	int f = IR_Front();
	int b = IR_Behind();
	
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(80);
	ServoF_Set(0);
	
	if((f==0&&b==0)||(f==407&&b==407)||(f==0&&b==407)||(f==407&&b==0)||(f==-1&&b==407)||(f==407&&b==1)||(f==1&&b==407)||(f==407&&b==-1))
		head_front();
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//��ʾ��˳ʱ��ת��,С�����磺'\'
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
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//��ʾ����ʱ��ת��,С�����磺'/'
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
	if(f==1&&b==1)	//С��̫ƫ����,������407
		head_front_left();
	if(f==-1&&b==-1)	//С��̫ƫ����
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
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//��ʾ��˳ʱ��ת��,С�����磺'\'
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
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//��ʾ����ʱ��ת��,С�����磺'/'
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
	if(f==1&&b==1)	//С��̫ƫ����,������407
		head_front_left();
	if(f==-1&&b==-1)	//С��̫ƫ����
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
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//��ʾ��˳ʱ��ת��,С�����磺'\'
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
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//��ʾ����ʱ��ת��,С�����磺'/'
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
	if(f==1&&b==1)	//С��̫ƫ����,������407
		head_front_left();
	if(f==-1&&b==-1)	//С��̫ƫ����
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
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//��ʾ��˳ʱ��ת��,С�����磺'\'
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
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//��ʾ����ʱ��ת��,С�����磺'/'
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
	if(f==1&&b==1)	//С��̫ƫ����,������407
		head_behind_left();
	if(f==-1&&b==-1)	//С��̫ƫ����
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
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//��ʾ��˳ʱ��ת��,С�����磺'\'
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
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//��ʾ����ʱ��ת��,С�����磺'/'
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
	if(f==1&&b==1)	//С��̫ƫ����,������407
		head_behind_left();
	if(f==-1&&b==-1)	//С��̫ƫ����
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
	if((f==0&&b==1)||(f==-1&&b==0)||(f==-1&&b==1))	//��ʾ��˳ʱ��ת��,С�����磺'\'
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
	if((f==0&&b==-1)||(f==1&&b==0)||(f==1&&b==-1))	//��ʾ����ʱ��ת��,С�����磺'/'
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
	if(f==1&&b==1)	//С��̫ƫ����,������407
		head_behind_left();
	if(f==-1&&b==-1)	//С��̫ƫ����
		head_behind_right();
	return 0;
	/*if(((IR_Front())==0&&(IR_Behind()==0))||((IR_Front()==407)&&(IR_Behind()==407)))
		head_behind();
	else if(IR_Front()<IR_Behind())	//��ʾ��˳ʱ��ת��,С�����磺'\'
		clock_wise();
	else if(IR_Front()>IR_Behind())	//��ʾ����ʱ��ת��,С�����磺'/'
		anti_clock();
	else if((IR_Front()==IR_Behind())&&(IR_Front()>0)&&(IR_Front()<3))	//С��̫ƫ����,������407
		head_left();
	else if((IR_Front()==IR_Behind())&&(IR_Front()<0))	//С��̫ƫ����
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
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//��ʾ��˳ʱ��ת��,С�����磺'/'
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
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//��ʾ����ʱ��ת��,С�����磺'\'
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
	if(r==1&&l==1)	//С��̫ƫ����,������407
		head_front_right();
	if(r==-1&&l==-1)	//С��̫ƫ����
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
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//��ʾ��˳ʱ��ת��,С�����磺'/'
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
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//��ʾ����ʱ��ת��,С�����磺'\'
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
	if(r==1&&l==1)	//С��̫ƫ����,������407
		head_front_right();
	if(r==-1&&l==-1)	//С��̫ƫ����
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
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//��ʾ��˳ʱ��ת��,С�����磺'/'
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
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//��ʾ����ʱ��ת��,С�����磺'\'
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
	if(r==1&&l==1)	//С��̫ƫ����,������407
		head_front_right();
	if(r==-1&&l==-1)	//С��̫ƫ����
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
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//��ʾ��˳ʱ��ת��,С�����磺'/'
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
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//��ʾ����ʱ��ת��,С�����磺'\'
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
	if(r==1&&l==1)	//С��̫ƫ����,������407
		head_front_left();
	if(r==-1&&l==-1)	//С��̫ƫ����
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
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//��ʾ��˳ʱ��ת��,С�����磺'/'
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
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//��ʾ����ʱ��ת��,С�����磺'\'
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
	if(r==1&&l==1)	//С��̫ƫ����,������407
		head_front_left();
	if(r==-1&&l==-1)	//С��̫ƫ����
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
	if((r==0&&l==1)||(r==-1&&l==0)||(r==-1&&l==1))	//��ʾ��˳ʱ��ת��,С�����磺'/'
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
	if((r==0&&l==-1)||(r==1&&l==0)||(r==1&&l==-1))	//��ʾ����ʱ��ת��,С�����磺'\'
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
	if(r==1&&l==1)	//С��̫ƫ����,������407
		head_front_left();
	if(r==-1&&l==-1)	//С��̫ƫ����
		head_behind_left();
	return 0;
	/*if(((IR_Left()==0)&&(IR_Right()==0))||((IR_Left()==407)&&(IR_Right()==407)))
		head_left();
	else if(IR_Right()>IR_Left())	//��ʾ�� ��ʱ��ת��,С�����磺'\'
		anti_clock();
	else if(IR_Right()<IR_Left())	//��ʾ�� ˳ʱ��ת��,С�����磺'/'
		clock_wise();
	else if((IR_Right()==IR_Left())&&(IR_Left()>0)&&(IR_Left()<3))	//С��̫ƫ����,������407
		head_front();
	else if((IR_Right()==IR_Left())&&(IR_Left()<0))	//С��̫ƫ����
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
	//��ʼ״̬������IR���Ƿ���0
	
	while(count!=dx){
		if(dx>0){
			
			gol_error2();			
			
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;						//��ʼ״̬������IR���Ƿ���0
			if(IR_Behind()==1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{								//����flag���ж�������Ϊ��ʹ�����ڳ�ʼ���Ժ���жϲ�����Ч
				while(IR_Behind()!=-1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0
	
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
				flag=0;						//��ʼ״̬������IR���Ƿ���0
			if(IR_Behind()==1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{								//����flag���ж�������Ϊ��ʹ�����ڳ�ʼ���Ժ���жϲ�����Ч
				while(IR_Behind()!=-1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0
	
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
				flag=0;						//��ʼ״̬������IR���Ƿ���0
			if(IR_Behind()==1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{								//����flag���ж�������Ϊ��ʹ�����ڳ�ʼ���Ժ���жϲ�����Ч
				while(IR_Behind()!=-1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0

	while(count!=dx){
		if(dx>0){
			gor_error2();
		}	
		if(dx>0){
			if(IR_Front()==0&&IR_Behind()==0)
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Behind()==-1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
			{	
				while(IR_Behind()!=1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==-1&&flag==0)		//IRǰ���ȵ��˽�������  ��ʱС������  '/'
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
	//��ʼ״̬������IR���Ƿ���0

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
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Behind()==-1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
			{	
				while(IR_Behind()!=1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==-1&&flag==0)		//IRǰ���ȵ��˽�������  ��ʱС������  '/'
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
	//��ʼ״̬������IR���Ƿ���0

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
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Behind()==-1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
			{	
				while(IR_Behind()!=1);
				flag=1;
				count++;
				continue;
			}	
			if(IR_Front()==-1&&flag==0)		//IRǰ���ȵ��˽�������  ��ʱС������  '/'
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
	//��ʼ״̬������IR���Ƿ���0
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
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Right()==1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{	
				while(IR_Right()!=-1);
				flag=1;					//��flag��1����ֹ���ڽ������϶����һ��
				count++;
				continue;
			}	
			if(IR_Left()==1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0
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
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Right()==1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{	
				while(IR_Right()!=-1);
				flag=1;					//��flag��1����ֹ���ڽ������϶����һ��
				count++;
				continue;
			}	
			if(IR_Left()==1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0
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
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Right()==1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{	
				while(IR_Right()!=-1);
				flag=1;					//��flag��1����ֹ���ڽ������϶����һ��
				count++;
				continue;
			}	
			if(IR_Left()==1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0
	
	while(count!=dy){
		if(dy>0){	
			gob_error2();			
		}
		if(dy>0){	
			if(IR_Right()==0&&IR_Left()==0)
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Right()==-1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{	
				while(IR_Right()!=1);
				flag=1;
				count++; 
				continue;
			}	
			if(IR_Left()==-1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0
	
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
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Right()==-1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{	
				while(IR_Right()!=1);
				flag=1;
				count++; 
				continue;
			}	
			if(IR_Left()==-1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//��ʼ״̬������IR���Ƿ���0
	
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
				flag=0;			//��ʼ״̬������IR���Ƿ���0
			if(IR_Right()==-1&&flag==0)		//IR�ұ��ȵ��˽�������  ��ʱС������  '/'
			{	
				while(IR_Right()!=1);
				flag=1;
				count++; 
				continue;
			}	
			if(IR_Left()==-1&&flag==0)		//IR����ȵ��˽�������  ��ʱС������  '\'
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
	//go_delta_x���������ҵ��ƶ�����ʱ��Ҫ�õ�ǰ���IR�����м���
	int	x0=x;//��¼��ʹ�øú���ʱ��xλ��
	u8 state=IR_Behind()||IR_Front();
	u8 flag;
	if(dx>x0)
		flag=-1;     //=-1ʱ��Ϊx++��־
	else if(dx<x0)
		flag=1;      //=1ʱ��Ϊx++��־
	while(x!=dx)
	{	
		if(dx>x)	//Ŀ��λ�ô��ڵ�ǰλ��
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
	int	y0=y;//��¼��ʹ�øú���ʱ��λ��
	u8 state=IR_Right()||IR_Left();
	u8 flag;
	if(dy>y0)
		flag=-1;     //=-1ʱ��Ϊx++��־
	else if(dy<y0)
		flag=1;      //=1ʱ��Ϊx++��־
	while(y!=dy)
	{	
		if(dy>y)	//Ŀ��λ�ô��ڵ�ǰλ��
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





