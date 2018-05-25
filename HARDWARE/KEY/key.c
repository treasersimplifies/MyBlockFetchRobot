#include "key.h"
#include "sys.h"
#include "led.h"
#include "delay.h" 
#include "usart.h"
//������̳�ʼ������

void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<2;     //ʹ��PORTCʱ�� 
	RCC->AHB1ENR|=1<<4;     //ʹ��PORTEʱ��
	RCC->AHB1ENR|=1<<5;     //ʹ��PORTFʱ��
	
						    //| |
	//��ֱ�ߣ�[x][0]���������� 0 1
	//PE2/4/6����,���������
	GPIO_Set(GPIOE,PIN2|PIN4|PIN6,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);	
	//PF0/2/4/6/8����Ϊ�������
	GPIO_Set(GPIOF,PIN0|PIN2|PIN4|PIN6|PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);

	//�������	
	//��0
	//��1
	GPIO_Set(GPIOE,PIN3|PIN5,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PE3/5������������
	GPIO_Set(GPIOC,PIN13,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PC13������������
	GPIO_Set(GPIOF,PIN1|PIN3|PIN5|PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PF1/3/5/7��������
	GPIO_Set(GPIOC,PIN2,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);//PC2��������
	
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

//���ڱ�������̼�⺯����1��Ҹ��ҵĵ�·ͼ��ʵ�ʵ����������г��룺���������������Ҫ����
//						 2��1�еİ����������ò���
//						 3Ϊ��������Ҫ���Ұѵ�8�еİ���ģ����˵�1��

u8 KEY_Scan(keystate * ckstate){//�Ż�ֵ��
	int keynum=0;
	int i,j;	
	
	for(i=0;i<8;i++)//��key������г�ʼ��
	{
		for(j=0;j<8;j++){
			ckstate->key[i][j]=0;
		}
	}
	
	i=8;//���󰴼�����8������û�б�����
	j=8;
	
	delay_ms(10);//����
	
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
		else{//VER0=1ʱ��һ������Ϊ1��������else
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
			else{	//VER1=1ʱ��һ������Ϊ1��������else
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
					if(HOR7==1){j=7;ckstate->key[0][5]=1;}//ԭ����[5][7]����[0][5]
				}
				else{//VER2=1ʱ��һ������Ϊ1��������else
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
						if(HOR7==1){j=7;ckstate->key[0][4]=1;}//ԭ����[4][7]����[0][4]
					}
					else{//VER3=1ʱ��һ������Ϊ1��������else
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
							if(HOR7==1){j=7;ckstate->key[0][3]=1;}//ԭ����[3][7]����[0][3]

						}
						else{//VER4=1ʱ��һ������Ϊ1��������else
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
								if(HOR7==1){j=7;ckstate->key[0][2]=1;}//ԭ����[2][7]����[0][2]
							}
							else{//VER5=1ʱ��һ������Ϊ1��������else
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
									if(HOR7==1){j=7;ckstate->key[0][1]=1;}//ԭ����[1][7]����[0][1]
								}	
								else{//VER6=1ʱ��һ������Ϊ1��������else
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

									else{//ɨ����ɣ������else��ʾ��û��һ������������
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
	for(i=0;i<8;i++)//��key������б���
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
		//�������ȼ���������CMD
		//Ȼ��������ɨ��
		//Ȼ����ǵ�������
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
		//����ɨ��
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
		//��������
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
	for(i=0;i<8;i++)//��key������б�����ͳ�Ƴ��������µ���Ŀ�����ܳ���2��
	{
		for(j=0;j<8;j++){
			if(ckstate->key[i][j]==1)
				keynum++;
		}
	}
	return keynum;*/


/*
��ֱ���߶��壺
#define HOR0 	PE2   	
#define HOR1 	PE4  
#define HOR2 	PE6

#define HOR3 	PF0 
#define HOR4 	PF2  
#define HOR5 	PF4 
#define HOR6 	PF6  
#define HOR7 	PF8 
ˮƽ���߶��壺
#define VER0 	PE3
#define VER1 	PE5
#define VER2 	PC13  
#define VER3  	PF1  
#define VER4  	PF3  
#define VER5 	PF5  
#define VER6  	PF7  
#define VER7 	PF9  */

//y=1,ʱ��3����ɫ����
/*u8 KEY_Scan11(void){
	//λ�� 1,1
	if(HOR1==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan41(void){
	//λ�� 4,1
	if(HOR4==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan71(void){
	//λ�� 7,1
	if(HOR7==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=2��ʱ��2����ɫ����
u8 KEY_Scan32(void){
	//λ�� 3,2
	if(HOR3==1&&VER2==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan52(void){
	//λ�� 5,2
	if(HOR5==1&&VER2==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=3��ʱ��2����ɫ����
u8 KEY_Scan23(void){
	//λ�� 2,3
	if(HOR2==1&&VER3==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan63(void){
	//λ�� 6,3
	if(HOR6==1&&VER3==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=4��ʱ��2����ɫ����
u8 KEY_Scan34(void){
	//λ�� 3,4
	if(HOR3==1&&VER4==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan54(void){
	//λ�� 5,4
	if(HOR5==1&&VER4==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}

//y=5��ʱ��3����ɫ����
u8 KEY_Scan15(void){
	//λ�� 1,5
	if(HOR1==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan45(void){
	//λ�� 4,5
	if(HOR4==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan75(void){
	//λ�� 7,5
	if(HOR7==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//ˮƽɨ�躯����ץȡͬһ��yֵ�����еķ��顣

u8 KEY_Scan01(void){//λ�� 0,1
	if(HOR0==1&&VER1==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan02(void){	//λ�� 0,2
	if(HOR0==1&&VER2==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan03(void){//λ�� 0,3
	if(HOR0==1&&VER3==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan04(void){//λ�� 0,4
	if(HOR0==1&&VER4==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan05(void){//λ�� 0,5
	if(HOR0==1&&VER5==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}


//��ֱɨ�躯����ץȡͬһ��xֵ�����еķ��顣

u8 KEY_Scan10(void){//λ�� 1��0
	if(HOR1==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan20(void){//λ�� 2��0
	if(HOR2==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan30(void){//λ�� 3��0
	if(HOR3==1&&VER0==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan40(void){//λ�� 4��0
	if(HOR4==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan50(void){//λ�� 5��0
	if(HOR5==1&&VER0==1){
		GREEN_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan60(void){//λ�� 6��0
	if(HOR6==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan70(void){//λ�� 7��0
	if(HOR7==1&&VER0==1){
		YELLOW_LIGHT;
		return 1;
	}
	else
		return 0;
}

//CMD���������ж����������:
u8 KEY_Scan73(void)//����home������
{		//λ�� 7,3
	if(HOR7==1&&VER3==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan00(void){	//λ�� 0,0	HOR0==1&&
	if(VER0==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan26(void){	//λ�� 2,6
	if(HOR2==1&&VER6==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}

u8 KEY_Scan07(void){	//λ�� 0,7
	if(HOR0==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan17(void){	//λ�� 1,7
	if(HOR1==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan27(void){	//λ�� 2,7
	if(HOR2==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan37(void){	//λ�� 3,7
	if(HOR3==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan47(void){	//λ�� 4,7
	if(HOR4==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan57(void){	//λ�� 5,7
	if(HOR5==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan67(void){	//λ�� 6,7
	if(HOR6==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
u8 KEY_Scan77(void){	//λ�� 7,7
	if(HOR7==1&&VER7==1){
		RED_LIGHT;
		return 1;
	}
	else
		return 0;
}
*/
