#include "sys.h"
#include "delay.h"  
#include "led.h"
#include "engines.h"
#include "gps.h"
#include "usart.h"
#include "usmart.h"
#include "key.h"
//
//  PA7-pwm14
//	PA6-pwm13
//	PB9-pwm11
//	PB8-pwm10
//	PF10�������
//  PF9�������
//	
#define FULL_SPEED 328

	int ground[7][9]={			//��һ��7��9�еľ����ű�����ͼ
        { 1, 0, 0, 0, 1, 0, 0, 0, 1},// 	---------------->x
        {-1, 0, 3, 0, 0, 0, 3, 0,-1},//|
        {-1, 0, 0, 0, 0, 0, 0, 0,-1},//|
        { 0, 1, 0, 0,-1, 0, 0, 1, 0},//|
        {-1, 0, 0, 0, 0, 0, 0, 0,-1},//|
        {-1, 0, 3, 0, 0, 0, 3, 0,-1},//|
        { 1, 0, 0, 0, 1, 0, 0, 0, 1}// V	y
    };	
	extern int	y;//��¼��ʼλ��
	extern int	x;
	
void go_testone(void){
	go_delta_f(5);
	go_delta_r(1);
	go_delta_b(5);
	go_delta_l(1);
}
void go_test(void){
	go_delta_f(3);
	go_delta_l(1);
	ServoB_Set(90);
	ServoR_Set(90);
	ServoL_Set(90);
	ServoF_Set(90);
	go_delta_r(1);
	go_delta_b(3);
	ENGINES_stop();
	delay_ms(10000);
}
void go_out(void){//�ڽ����ҷ�home������õĺ�����ʹ�÷�����home���ڣ�����С������Ӵ���
	
	ENGINES_stop();
	
	head_left();
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	delay_ms(2100);
	
	head_front();
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	delay_ms(800);
	
	head_behind();
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(100);	//��ǰ���壬�ų�ǰ����
	delay_ms(1500);		//�ߵ�����
	
	head_front();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(100);	//�򿪺󵲰壬�ų��󷽿�
	delay_ms(900);		//�ߵ��м��
	
	anti_clock();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(0);	
	delay_ms(700);		//������ʱ��ת90��
	
	head_right();
	ServoB_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoR_Set(0);
	delay_ms(800);		//�ߵ���ǰ��
	
	head_left();
	ServoB_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoR_Set(100);	//���ҵ��壬�ų��ҷ���
	delay_ms(1500);		//�ߵ�����
	
	head_right();
	ServoB_Set(0);
	ServoF_Set(0);
	ServoR_Set(0);
	ServoL_Set(100);	//���󵲰壬�ų��󷽿�
	delay_ms(700);		//�ߵ��м��
	
	head_behind();
	ServoB_Set(0);
	ServoF_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	delay_ms(600);		
	
	clock_wise();		
	delay_ms(700);
	
	while(1){	//�������з��飬׼������home��
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ENGINES_stop();
	}
	
	/*ServoB_Set(100);
	ServoR_Set(100);
	ServoL_Set(100);
	ServoF_Set(100);*/
	
}
void go_enemy_74(void){
	
	go_delta_f_error(1);
	go_delta_r_error(6);
	go_delta_f_error(2);
	go_delta_f_error2(1);
	go_delta_l_error2(1);
	go_delta_r_error2(1);
	go_delta_f_error2(1);
	head_right();
	delay_ms(300);
	
	while(1){
		ENGINES_stop();
	}
}
	
void go_enemy_72(void){
	go_delta_f_error(1);
	go_delta_r_error(6);
	go_delta_f_error(3);
	
	head_right();
	delay_ms(300);
	
	while(1){
		ENGINES_stop();
		
	}
		
}
void go_enemy_73(void){
	
	go_delta_f(1);
	go_delta_r_error(6);
	go_delta_f_error(3);
	
	ENGINES_stop();
	
	head_right();
	ServoB_Set(0);
	ServoR_Set(100);
	ServoL_Set(0);
	ServoF_Set(0);
	delay_ms(2100);
	
	head_front();
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(100);
	delay_ms(1000);
	
	head_behind();
	ServoB_Set(100);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);	//��ǰ���壬�ų�ǰ����
	delay_ms(1500);		//�ߵ�����
	
	
	head_front();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(0);	//�򿪺󵲰壬�ų��󷽿�
	delay_ms(1000);		//�ߵ��м��
	
	head_behind();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(0);	//�򿪺󵲰壬�ų��󷽿�
	delay_ms(1500);		//�ߵ��м��
	
	head_front();
	ServoB_Set(0);
	ServoF_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	delay_ms(600);		

	
	while(1){
	ServoB_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ENGINES_stop();
	}
}
void go_one(void){
	
	go_delta_f_error(1);
	go_delta_f(5);
	go_delta_r(1);
	go_delta_b(4);
	go_delta_r(4);
	go_delta_b_error(1);
	go_delta_l(6);
	go_delta_r(1);
	go_delta_f_error(3);
	go_out();
	
}

void running(keystate * ckstate,int keynum){
	
	RED_LIGHT_ON;//ָʾ��
	delay_ms(200);
	RED_LIGHT_OFF;
	//�����ȼ��԰�������������д���
	//��ͨ��
	if(ckstate->key[2][6]==1){
		GREEN_LIGHT_ON;
		YELLOW_LIGHT_ON;
		RED_LIGHT_ON;
		delay_ms(200);
		go_one();
		YELLOW_LIGHT_OFF;
		GREEN_LIGHT_OFF;
	}	
	//���¹��м���
	if(ckstate->key[7][3]==1){
		RED_LIGHT_ON;
		delay_ms(200);
		go_enemy_73();
		RED_LIGHT_OFF;
	}	
	if(ckstate->key[7][2]==1){
		RED_LIGHT_ON;
		delay_ms(200);
		go_enemy_72();
		RED_LIGHT_OFF;
	}	
	if(ckstate->key[7][4]==1){
		RED_LIGHT_ON;
		delay_ms(200);
		go_enemy_74();
		RED_LIGHT_OFF;
	}	
	
	//����Ĭ�ϼ���
	if(ckstate->key[0][0]==1)
		go_one();
	if(ckstate->key[6][7]==1){
		GREEN_LIGHT_ON;
		
		
		delay_ms(200);
		go_delta_f_error(1);
		go_delta_l(1);
		go_delta_r(6);
		
		go_delta_f(1);
		go_delta_l(4);
		
		go_delta_f(4);
		go_delta_l(1);
		go_delta_b(2);
		
		go_out();
		GREEN_LIGHT_OFF;
		
		
	}
	if(ckstate->key[7][7]==1){
		GREEN_LIGHT_ON;
		YELLOW_LIGHT_ON;
		RED_LIGHT_ON;
		delay_ms(200);
		go_delta_f_error(1);
		go_delta_r_error(1);
		go_delta_r(4);
		
		go_delta_f(6);
		go_delta_l(4);
	
		go_delta_b(3);
		go_delta_l(1);
		go_out();
		GREEN_LIGHT_OFF;
		YELLOW_LIGHT_OFF;
		RED_LIGHT_OFF;
	}
	
	
	
	//ȡ��������ȼ������̣���ƣ��Ƚ���Զ�����ȼ��������£�
	//ֻ����1������
	if(keynum==1){
		//����ɨ�裬ע�����ȼ���
		if(ckstate->key[4][3]==1){//test
			RED_LIGHT_ON;
			delay_ms(200);
			go_delta_f(1);
			go_delta_r(5);
			go_delta_f(6);
			go_delta_l(6);
			go_delta_r_error(2);
			go_delta_b(5);
			go_delta_f_error(2);
			go_delta_l_error(1);
			go_out();
			RED_LIGHT_OFF;
		}
		if(ckstate->key[0][4]==1){//good to take
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(4);
			go_delta_f(1);
			go_delta_l(5);
			go_delta_f(2);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[0][5]==1)//   [8][6]out  
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(6);
			go_delta_l(8);
			go_delta_r_error(2);
			go_delta_f(3);
			go_delta_l(1);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[0][3]==1){//good
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(3);
			go_delta_r(1);
			go_delta_b(2);
			go_delta_r(4);
			go_delta_f_error(3);
			go_delta_r_error(1);
			go_delta_b(3);
			
			go_delta_l_error(5);
			go_delta_f_error(2);  
			go_delta_l(1);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[0][2]==1)
		{
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(5);
			go_delta_r(5);
			go_delta_l_error(5);
			go_delta_b_error(2);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[0][1]==1){//good
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(6);
			go_delta_r(7);
			go_delta_l(8);
			go_delta_r_error(1);
			go_delta_b(3);
			go_out();
			YELLOW_LIGHT_OFF;
		}

		

		//
		if(ckstate->key[1][0]==1)//good
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_l(1);
			go_delta_r(1);
			go_delta_f(6);
			go_delta_l(1);
			go_delta_r(1);
			go_delta_b(3);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[2][0]==1){	//
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(6);
			go_delta_b(3);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[3][0]==1){
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_f(6);
			go_delta_b(3);
			go_delta_l(1);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[4][0]==1)//good
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(2);
			go_delta_f(1);
			go_delta_l(2);
			go_delta_f(4);
			go_delta_r_error(2);
			go_delta_f(1);
			go_delta_l_error(3);
			go_delta_b(3);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[5][0]==1)
		{	
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(4);
			go_delta_f(6);
			go_delta_l(4);
			go_delta_b(3);
			go_delta_l(1);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[6][0]==1)//good
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(5);
			go_delta_f(6);
			go_delta_l(5);
			go_delta_b(3);
			go_delta_l_error(1);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[7][0]==1){//good
			YELLOW_LIGHT_ON;
			RED_LIGHT_OFF;//ָʾ��Ϩ�𣬱�ʾ������[7][x]
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(6);
			go_delta_l(1);
			go_delta_f(6);
			go_delta_r(1);
			go_delta_l(6);
			go_delta_b(3);
			go_delta_l(1);
			go_out();
			YELLOW_LIGHT_OFF;
			RED_LIGHT_OFF;
		}

		//��������
		if(ckstate->key[1][1]==1)//good
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(6);
			go_delta_l(1);
			go_delta_r(1);
			go_delta_b(3);
			go_out();
			YELLOW_LIGHT_ON;
		}
		if(ckstate->key[4][1]==1)//good
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(6);
			go_delta_r(3);
			go_delta_l(2);
			go_delta_b(3);
			go_delta_l(1);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[7][1]==1)
		{
			YELLOW_LIGHT_ON;
			RED_LIGHT_ON;//ָʾ��Ϩ�𣬱�ʾ������[7][x]
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(6);
			go_delta_r(7);
			go_delta_l(2);
			go_delta_b(1);
			go_delta_l(4);
			go_delta_b_error(2);
			go_delta_l(1);
			go_out();
			YELLOW_LIGHT_OFF;
			RED_LIGHT_OFF;
		}
		if(ckstate->key[3][2]==1)
		{
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_f(5);
			go_delta_b(2);
			go_delta_l(1);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[5][2]==1)
		{
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(5);
			go_delta_r(5);
			go_delta_l(5);
			go_delta_b(2);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[2][3]==1)
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(3);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[6][3]==1)
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(5);
			go_delta_f(5);
			go_delta_l(5);
			go_delta_b(2);
			go_delta_l(1);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[3][4]==1)
		{
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_f(1);
			go_delta_r(1);
			go_delta_f(2);
			go_delta_l(1);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[5][4]==1)
		{
			GREEN_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(4);
			go_delta_f(1);
			go_delta_l(5);
			go_delta_f(2);
			go_out();
			GREEN_LIGHT_OFF;
		}
		if(ckstate->key[1][5]==1)
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_l(1);
			go_delta_r(1);
			go_delta_f(3);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[4][5]==1)
		{
			YELLOW_LIGHT_ON;
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(2);
			go_delta_f(1);
			go_delta_l(3);
			go_delta_f(2);
			go_out();
			YELLOW_LIGHT_OFF;
		}
		if(ckstate->key[7][5]==1)
		{
			YELLOW_LIGHT_ON;
			RED_LIGHT_ON;//ָʾ��Ϩ�𣬱�ʾ������[7][x]
			delay_ms(200);
			go_delta_f_error(1);
			go_delta_r_error(1);
			go_delta_r(6);
			go_delta_l(6);
			go_delta_f(3);
			go_delta_l(1);
			go_out();
			YELLOW_LIGHT_OFF;
			RED_LIGHT_OFF;
		}
	}
	//����2������ʱ��
	if(keynum==2){
		if(ckstate->key[0][1]==1&&ckstate->key[0][2]==1)
		{
			go_delta_f(1);
			go_delta_l(1);
			go_delta_r(8);
			go_delta_l(2);
			go_delta_b(1);
			go_delta_l(5);
			go_delta_b(2); 
			go_out();
		}
	}

}


int main(void)
{  
	keystate * ckstate;		//keystate�ṹ�����ڴ��ݳ��ص������
	//keystate * ckstate_use;
	int keynum;	
	//int keynum_use;
	int i,j;
	
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ��   
	uart_init(84,115200);	//���ڳ�ʼ��Ϊ115200
	
	KEY_Init();  //������̳�ʼ�������а�����LEDinit����
	GPS_Init();
	ENGINES_Init();
	usmart_dev.init(84);
	


   	while(1)
	{	
		ServoB_Set(0);
		ServoR_Set(0);
		ServoL_Set(0);
		ServoF_Set(0);
		
		ENGINES_stop();

		keynum = KEY_Scan(ckstate);
		printf("keynum=%d\n",keynum);
		
		running(ckstate,keynum);
		
		delay_ms(300);
	}
}
		   



void go_two(void){
	go_delta_f(7);
	go_delta_l(1);
	go_delta_r(8);
	go_delta_l(1);
	go_delta_b(6);
	go_delta_r(1);
	go_delta_l(8);
	go_delta_r(2);
	go_delta_f(5);
	go_delta_r(4);
	go_delta_b(4);
	go_delta_l(4);
	go_delta_f(2);
	go_delta_l(3);
}



/*delay_ms(1000);
		ServoB_Set(50);
		ServoR_Set(50);
		ServoL_Set(50);
		ServoF_Set(50);
		printf("50");
		delay_ms(1000);
		ServoB_Set(80);
		ServoR_Set(80);
		ServoL_Set(80);
		ServoF_Set(80);
		printf("80");
		delay_ms(10000);
		
		ServoB_Set(90);
		ServoR_Set(90);
		ServoL_Set(90);
		ServoF_Set(90);
		printf("90");
		delay_ms(10000);
		
		*/







