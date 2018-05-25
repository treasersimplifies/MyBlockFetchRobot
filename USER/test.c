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
//	PF10下拉输出
//  PF9下拉输出
//	
#define FULL_SPEED 328

	int ground[7][9]={			//用一个7行9列的矩阵存放比赛地图
        { 1, 0, 0, 0, 1, 0, 0, 0, 1},// 	---------------->x
        {-1, 0, 3, 0, 0, 0, 3, 0,-1},//|
        {-1, 0, 0, 0, 0, 0, 0, 0,-1},//|
        { 0, 1, 0, 0,-1, 0, 0, 1, 0},//|
        {-1, 0, 0, 0, 0, 0, 0, 0,-1},//|
        {-1, 0, 3, 0, 0, 0, 3, 0,-1},//|
        { 1, 0, 0, 0, 1, 0, 0, 0, 1}// V	y
    };	
	extern int	y;//记录初始位置
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
void go_out(void){//在进入我方home区后调用的函数，使得方块在home区内，并且小车不与接触。
	
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
	ServoF_Set(100);	//打开前挡板，放出前方块
	delay_ms(1500);		//走到最后端
	
	head_front();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(100);	//打开后挡板，放出后方块
	delay_ms(900);		//走到中间端
	
	anti_clock();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(0);	
	delay_ms(700);		//假设逆时针转90度
	
	head_right();
	ServoB_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoR_Set(0);
	delay_ms(800);		//走到最前端
	
	head_left();
	ServoB_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoR_Set(100);	//打开右挡板，放出右方块
	delay_ms(1500);		//走到最后端
	
	head_right();
	ServoB_Set(0);
	ServoF_Set(0);
	ServoR_Set(0);
	ServoL_Set(100);	//打开左挡板，放出左方块
	delay_ms(700);		//走到中间端
	
	head_behind();
	ServoB_Set(0);
	ServoF_Set(0);
	ServoR_Set(0);
	ServoL_Set(0);
	delay_ms(600);		
	
	clock_wise();		
	delay_ms(700);
	
	while(1){	//放完所有方块，准备保护home区
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
	ServoF_Set(0);	//打开前挡板，放出前方块
	delay_ms(1500);		//走到最后端
	
	
	head_front();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(0);	//打开后挡板，放出后方块
	delay_ms(1000);		//走到中间端
	
	head_behind();
	ServoR_Set(0);
	ServoL_Set(0);
	ServoF_Set(0);
	ServoB_Set(0);	//打开后挡板，放出后方块
	delay_ms(1500);		//走到中间端
	
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
	
	RED_LIGHT_ON;//指示灯
	delay_ms(200);
	RED_LIGHT_OFF;
	//按优先级对按键按下情况进行处理：
	//普通键
	if(ckstate->key[2][6]==1){
		GREEN_LIGHT_ON;
		YELLOW_LIGHT_ON;
		RED_LIGHT_ON;
		delay_ms(200);
		go_one();
		YELLOW_LIGHT_OFF;
		GREEN_LIGHT_OFF;
	}	
	//按下攻敌键：
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
	
	//按下默认键：
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
	
	
	
	//取方块的优先级：先绿，后黄，先近后远。优先级体现如下：
	//只按下1个按键
	if(keynum==1){
		//行列扫描，注意优先级！
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
			RED_LIGHT_OFF;//指示灯熄灭，表示按到了[7][x]
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

		//单个方块
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
			RED_LIGHT_ON;//指示灯熄灭，表示按到了[7][x]
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
			RED_LIGHT_ON;//指示灯熄灭，表示按到了[7][x]
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
	//按下2个按键时：
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
	keystate * ckstate;		//keystate结构，用于传递场地的情况。
	//keystate * ckstate_use;
	int keynum;	
	//int keynum_use;
	int i,j;
	
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化   
	uart_init(84,115200);	//串口初始化为115200
	
	KEY_Init();  //矩阵键盘初始化，其中包括了LEDinit（）
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







