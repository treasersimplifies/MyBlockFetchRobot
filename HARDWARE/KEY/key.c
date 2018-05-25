#include "key.h"
#include "sys.h"
#include "led.h"
#include "delay.h" 
#include "usart.h"
//矩阵键盘初始化函数

void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<2;     //使能PORTC时钟 
	RCC->AHB1ENR|=1<<4;     //使能PORTE时钟
	RCC->AHB1ENR|=1<<5;     //使能PORTF时钟
	
						    //| |
	//垂直线：[x][0]，用于输入 0 1
	//PE2/4/6设置,都下拉输出
	GPIO_Set(GPIOE,PIN2|PIN4|PIN6,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);	
	//PF0/2/4/6/8设置为下拉输出
	GPIO_Set(GPIOF,PIN0|PIN2|PIN4|PIN6|PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);

	//用于输出	
	//—0
	//—1
	GPIO_Set(GPIOE,PIN3|PIN5,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PE3/5设置下拉输入
	GPIO_Set(GPIOC,PIN13,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PC13设置下拉输入
	GPIO_Set(GPIOF,PIN1|PIN3|PIN5|PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PF1/3/5/7下拉输入
	GPIO_Set(GPIOC,PIN2,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PC2下拉输入
	
	VER0=0;
	VER1=0;
	VER2=0;
	VER3=0;
	VER4=0;
	VER5=0;
	VER6=0;
	VER7=0;

	LED_Init();

} 

//关于本矩阵键盘检测函数：1店家给我的电路图与实际的物理连接有出入：第六行与第五行需要互换
//						 2第1列的按键检测基本用不了
//						 3为了满足需要，我把第8行的按键模拟成了第1列

u8 KEY_Scan(keystate * ckstate){//放回值是
	int keynum=0;
	int i,j;	
	
	for(i=0;i<8;i++)//对key数组进行初始化
	{
		for(j=0;j<8;j++){
			ckstate->key[i][j]=0;
		}
	}
	
	i=8;//矩阵按键超过8，表明没有被按下
	j=8;
	
	delay_ms(10);//防抖
	
		VER0=1;i=7;
		if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
			if(HOR0==1){j=0;ckstate->key[i][j]=1;}
			if(HOR1==1){j=1;ckstate->key[i][j]=1;}
			if(HOR2==1){j=2;ckstate->key[i][j]=1;}
			if(HOR3==1){j=3;ckstate->key[i][j]=1;}
			if(HOR4==1){j=4;ckstate->key[i][j]=1;}
			if(HOR5==1){j=5;ckstate->key[i][j]=1;}
			if(HOR6==1){j=6;ckstate->key[i][j]=1;}
			if(HOR7==1){j=7;ckstate->key[i][j]=1;}
		}
		else{//VER0=1时无一个按键为1，则进入该else
			VER0=0;
			VER1=1;i=6;
			if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
				if(HOR0==1){j=0;ckstate->key[i][j]=1;}
				if(HOR1==1){j=1;ckstate->key[i][j]=1;}
				if(HOR2==1){j=2;ckstate->key[i][j]=1;}
				if(HOR3==1){j=3;ckstate->key[i][j]=1;}
				if(HOR4==1){j=4;ckstate->key[i][j]=1;}
				if(HOR5==1){j=5;ckstate->key[i][j]=1;}
				if(HOR6==1){j=6;ckstate->key[i][j]=1;}
				if(HOR7==1){j=7;ckstate->key[i][j]=1;}
			}
			else{	//VER1=1时无一个按键为1，则进入该else
				VER0=0;VER1=0;
				VER2=1;i=5;
				if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
					if(HOR0==1){j=0;ckstate->key[i][j]=1;}
					if(HOR1==1){j=1;ckstate->key[i][j]=1;}
					if(HOR2==1){j=2;ckstate->key[i][j]=1;}
					if(HOR3==1){j=3;ckstate->key[i][j]=1;}
					if(HOR4==1){j=4;ckstate->key[i][j]=1;}
					if(HOR5==1){j=5;ckstate->key[i][j]=1;}
					if(HOR6==1){j=6;ckstate->key[i][j]=1;}
					if(HOR7==1){j=7;ckstate->key[0][5]=1;}//原来的[5][7]换成[0][5]
				}
				else{//VER2=1时无一个按键为1，则进入该else
					VER0=0;VER1=0;VER2=0;
					VER3=1;i=4;
					if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
						if(HOR0==1){j=0;ckstate->key[i][j]=1;}
						if(HOR1==1){j=1;ckstate->key[i][j]=1;}
						if(HOR2==1){j=2;ckstate->key[i][j]=1;}
						if(HOR3==1){j=3;ckstate->key[i][j]=1;}
						if(HOR4==1){j=4;ckstate->key[i][j]=1;}
						if(HOR5==1){j=5;ckstate->key[i][j]=1;}
						if(HOR6==1){j=6;ckstate->key[i][j]=1;}
						if(HOR7==1){j=7;ckstate->key[0][4]=1;}//原来的[4][7]换成[0][4]
					}
					else{//VER3=1时无一个按键为1，则进入该else
						VER0=0;VER1=0;VER2=0;VER3=0;
						VER4=1;i=3;
						if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
							if(HOR0==1){j=0;ckstate->key[i][j]=1;}
							if(HOR1==1){j=1;ckstate->key[i][j]=1;}
							if(HOR2==1){j=2;ckstate->key[i][j]=1;}
							if(HOR3==1){j=3;ckstate->key[i][j]=1;}
							if(HOR4==1){j=4;ckstate->key[i][j]=1;}
							if(HOR5==1){j=5;ckstate->key[i][j]=1;}
							if(HOR6==1){j=6;ckstate->key[i][j]=1;}
							if(HOR7==1){j=7;ckstate->key[0][3]=1;}//原来的[3][7]换成[0][3]

						}
						else{//VER4=1时无一个按键为1，则进入该else
							VER0=0;VER1=0;VER2=0;VER3=0;VER4=0;
							VER5=1;i=2;
							if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
								if(HOR0==1){j=0;ckstate->key[i][j]=1;}
								if(HOR1==1){j=1;ckstate->key[i][j]=1;}
								if(HOR2==1){j=2;ckstate->key[i][j]=1;}
								if(HOR3==1){j=3;ckstate->key[i][j]=1;}
								if(HOR4==1){j=4;ckstate->key[i][j]=1;}
								if(HOR5==1){j=5;ckstate->key[i][j]=1;}
								if(HOR6==1){j=6;ckstate->key[i][j]=1;}
								if(HOR7==1){j=7;ckstate->key[0][2]=1;}//原来的[2][7]换成[0][2]
							}
							else{//VER5=1时无一个按键为1，则进入该else
								VER0=0;VER1=0;VER2=0;VER3=0;VER4=0;VER5=0;
								VER6=1;i=1;
								if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
									if(HOR0==1){j=0;ckstate->key[i][j]=1;}
									if(HOR1==1){j=1;ckstate->key[i][j]=1;}
									if(HOR2==1){j=2;ckstate->key[i][j]=1;}
									if(HOR3==1){j=3;ckstate->key[i][j]=1;}
									if(HOR4==1){j=4;ckstate->key[i][j]=1;}
									if(HOR5==1){j=5;ckstate->key[i][j]=1;}
									if(HOR6==1){j=6;ckstate->key[i][j]=1;}
									if(HOR7==1){j=7;ckstate->key[0][1]=1;}//原来的[1][7]换成[0][1]
								}	
								else{//VER6=1时无一个按键为1，则进入该else
									VER0=0;VER1=0;VER2=0;VER3=0;VER4=0;VER5=0;VER6=0;
									VER7=1;i=0;
									if(HOR0==1||HOR1==1||HOR2==1||HOR3==1||HOR4==1||HOR5==1||HOR6==1||HOR7==1){
										if(HOR0==1){j=0;ckstate->key[i][j]=1;}
										if(HOR1==1){j=1;ckstate->key[i][j]=1;}
										if(HOR2==1){j=2;ckstate->key[i][j]=1;}
										if(HOR3==1){j=3;ckstate->key[i][j]=1;}
										if(HOR4==1){j=4;ckstate->key[i][j]=1;}
										if(HOR5==1){j=5;ckstate->key[i][j]=1;}
										if(HOR6==1){j=6;ckstate->key[i][j]=1;}
										if(HOR7==1){j=7;ckstate->key[i][j]=1;}

									else{//扫描完成，进入此else表示，没有一个按键被按下
										i=8;
										j=8;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for(i=0;i<8;i++)//对key数组进行遍历
	{
		for(j=0;j<8;j++){
			if(ckstate->key[i][j]==1)
			{
				printf("key[%d][%d]is pressed",i,j);
				keynum++;
			}
			
		}
	}
	printf("key_Scan over\n");
	return keynum;
}
	/*
	
	while(KEY_Scan26()==0){
		//按照优先级来，先是CMD
		//然后是行列扫描
		//然后才是单个方块
		if(KEY_Scan00()==1)
		{
			ckstate->key[0][0]=1;
			printf("key_00 has been pressed");
		}
		if(KEY_Scan73()==1)
		{
			ckstate->key[7][3]=1;
			printf("key_00 has been pressed");
		}
		//行列扫描
		if(KEY_Scan01()==1)
		{
			ckstate->key[0][1]=1;
			printf("key_01 has been pressed");
		}
		if(KEY_Scan02()==1)
		{
			ckstate->key[0][2]=1;
			printf("key_02 has been pressed");
		}
		if(KEY_Scan03()==1)
		{
			ckstate->key[0][3]=1;
			printf("key_03 has been pressed");
		}
		if(KEY_Scan04()==1)
		{
			ckstate->key[0][4]=1;
			printf("key_04 has been pressed");
		}
		if(KEY_Scan05()==1)
		{
			ckstate->key[0][5]=1;
			printf("key_05 has been pressed");
		}
		//
		if(KEY_Scan10()==1)
		{
			ckstate->key[1][0]=1;
			printf("key_10 has been pressed");
		}
		if(KEY_Scan20()==1)
		{
			ckstate->key[2][0]=1;
			printf("key_20 has been pressed");
		}
		if(KEY_Scan30()==1)
		{
			ckstate->key[3][0]=1;
			printf("key_30 has been pressed");
		}
		if(KEY_Scan40()==1)
		{
			ckstate->key[4][0]=1;
			printf("key_40 has been pressed");
		}
		if(KEY_Scan50()==1)
		{
			ckstate->key[5][0]=1;
			printf("key_50 has been pressed");
		}
		if(KEY_Scan60()==1)
		{
			ckstate->key[6][0]=1;
			printf("key_60 has been pressed");
		}
		if(KEY_Scan70()==1)
		{
			ckstate->key[7][0]=1;
			printf("key_70 has been pressed");
		}
		//单个方块
		if(KEY_Scan11()==1)
		{
			ckstate->key[1][1]=1;
			printf("key_11 has been pressed");
		}
		if(KEY_Scan41()==1)
		{
			ckstate->key[4][1]=1;
			printf("key_41 has been pressed");
		}
		if(KEY_Scan71()==1)
		{
			ckstate->key[7][1]=1;
			printf("key_71 has been pressed");
		}
		
		if(KEY_Scan32()==1)
		{
			ckstate->key[3][2]=1;
			printf("key_32 has been pressed");
		}
		if(KEY_Scan52()==1)
		{
			ckstate->key[5][2]=1;
			printf("key_52 has been pressed");
		}
		
		if(KEY_Scan23()==1)
		{
			ckstate->key[2][3]=1;
			printf("key_23 has been pressed");
		}
		if(KEY_Scan63()==1)
		{
			ckstate->key[6][3]=1;
			printf("key_63 has been pressed");
		}
		
		if(KEY_Scan34()==1)
		{
			ckstate->key[3][4]=1;
			printf("key_34 has been pressed");
		}
		if(KEY_Scan54()==1)
		{
			ckstate->key[5][4]=1;
			printf("key_54 has been pressed");
		}
		
		if(KEY_Scan15()==1)
		{
			ckstate->key[1][5]=1;
			printf("key_15 has been pressed");
		}
		if(KEY_Scan45()==1)
		{
			ckstate->key[4][5]=1;
			printf("key_45 has been pressed");
		}
		if(KEY_Scan75()==1)
		{
			ckstate->key[7][5]=1;
			printf("key_75 has been pressed");
		}
		
		if(KEY_Scan07()==1)
		{
			ckstate->key[0][7]=1;
			printf("key_07 has been pressed");
		}
		if(KEY_Scan17()==1)
		{
			ckstate->key[1][7]=1;
			printf("key_17 has been pressed");
		}
		if(KEY_Scan27()==1)
		{
			ckstate->key[2][7]=1;
			printf("key_27 has been pressed");
		}
		if(KEY_Scan37()==1)
		{
			ckstate->key[3][7]=1;
			printf("key_37 has been pressed");
		}
		if(KEY_Scan47()==1)
		{
			ckstate->key[4][7]=1;
			printf("key_47 has been pressed");
		}
		if(KEY_Scan57()==1)
		{
			ckstate->key[5][7]=1;
			printf("key_57 has been pressed");
		}
		if(KEY_Scan67()==1)
		{
			ckstate->key[6][7]=1;
			printf("key_67 has been pressed");
		}
		if(KEY_Scan77()==1)
		{
			ckstate->key[7][7]=1;
			printf("key_77 has been pressed");
		}
		
	}
	for(i=0;i<8;i++)//对key数组进行遍历，统计出按键按下的数目，不能超过2个
	{
		for(j=0;j<8;j++){
			if(ckstate->key[i][j]==1)
				keynum++;
		}
	}
	return keynum;*/


/*
垂直总线定义：
#define HOR0 	PE2   	
#define HOR1 	PE4  
#define HOR2 	PE6

#define HOR3 	PF0 
#define HOR4 	PF2  
#define HOR5 	PF4 
#define HOR6 	PF6  
#define HOR7 	PF8 
水平总线定义：
#define VER0 	PE3
#define VER1 	PE5
#define VER2 	PC13  
#define VER3  	PF1  
#define VER4  	PF3  
#define VER5 	PF5  
#define VER6  	PF7  
#define VER7 	PF9  */

//y=1,时的3个黄色方块
/*u8 KEY_Scan11(void){
	//位置 1,1
	if(HOR1==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan41(void){
	//位置 4,1
	if(HOR4==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan71(void){
	//位置 7,1
	if(HOR7==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=2，时的2个绿色方块
u8 KEY_Scan32(void){
	//位置 3,2
	if(HOR3==1&&VER2==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan52(void){
	//位置 5,2
	if(HOR5==1&&VER2==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=3，时的2个黄色方块
u8 KEY_Scan23(void){
	//位置 2,3
	if(HOR2==1&&VER3==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan63(void){
	//位置 6,3
	if(HOR6==1&&VER3==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=4，时的2个绿色方块
u8 KEY_Scan34(void){
	//位置 3,4
	if(HOR3==1&&VER4==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan54(void){
	//位置 5,4
	if(HOR5==1&&VER4==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=5，时的3个黄色方块
u8 KEY_Scan15(void){
	//位置 1,5
	if(HOR1==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan45(void){
	//位置 4,5
	if(HOR4==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan75(void){
	//位置 7,5
	if(HOR7==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//水平扫描函数，抓取同一个y值上所有的方块。

u8 KEY_Scan01(void){//位置 0,1
	if(HOR0==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan02(void){	//位置 0,2
	if(HOR0==1&&VER2==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan03(void){//位置 0,3
	if(HOR0==1&&VER3==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan04(void){//位置 0,4
	if(HOR0==1&&VER4==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan05(void){//位置 0,5
	if(HOR0==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}


//垂直扫描函数，抓取同一个x值上所有的方块。

u8 KEY_Scan10(void){//位置 1，0
	if(HOR1==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan20(void){//位置 2，0
	if(HOR2==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan30(void){//位置 3，0
	if(HOR3==1&&VER0==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan40(void){//位置 4，0
	if(HOR4==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan50(void){//位置 5，0
	if(HOR5==1&&VER0==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan60(void){//位置 6，0
	if(HOR6==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan70(void){//位置 7，0
	if(HOR7==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//CMD按键，进行额外任务控制:
u8 KEY_Scan73(void)//进敌home区控制
{		//位置 7,3
	if(HOR7==1&&VER3==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan00(void){	//位置 0,0	HOR0==1&&
	if(VER0==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan26(void){	//位置 2,6
	if(HOR2==1&&VER6==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan07(void){	//位置 0,7
	if(HOR0==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan17(void){	//位置 1,7
	if(HOR1==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan27(void){	//位置 2,7
	if(HOR2==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan37(void){	//位置 3,7
	if(HOR3==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan47(void){	//位置 4,7
	if(HOR4==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan57(void){	//位置 5,7
	if(HOR5==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan67(void){	//位置 6,7
	if(HOR6==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan77(void){	//位置 7,7
	if(HOR7==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
*/
