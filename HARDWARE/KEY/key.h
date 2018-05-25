#ifndef __KEY_H
#define __KEY_H	

#include "sys.h" 
#include "led.h"
#include "delay.h" 
#include "usart.h"

//��ֱ�߶��壺
#define VER0 		PEout(2)   	
#define VER1 		PEout(4)  
#define VER2 		PEout(6)  
#define VER3 		PFout(0)  
#define VER4 		PFout(2)  
#define VER5 		PFout(4)  
#define VER6 		PFout(6)  
#define VER7 		PFout(8) 
//ˮƽ�߶��壺 
#define HOR0 		PEin(3) 
#define HOR1 		PEin(5) 
#define HOR2 		PCin(13)  
#define HOR3  		PFin(1)  
#define HOR4  		PFin(3)  
#define HOR5 		PFin(5)  
#define HOR6  		PFin(7)  
#define HOR7 		PCin(2)  


#define GREEN_LIGHT_ON  	PEout(0)=1	
#define GREEN_LIGHT_OFF  	PEout(0)=0	
#define YELLOW_LIGHT_ON	 	PEout(1)=1	
#define YELLOW_LIGHT_OFF	PEout(1)=0

#define RED_LIGHT_ON		PCout(3)=1
#define RED_LIGHT_OFF		PCout(3)=0	

typedef struct{
		int key[8][8];//8*8�ľ�����ʵֻ�õ���7-5���洢�����״̬
		/*int block11;
		int block41;
		int block71;
		int block32;
		int block52;
		int block23;
		int block63;
		int block34;
		int block54;
		int block15;
		int block45;
		int block75;
		int key00;
		int key73;
		int key26;*/
} keystate;

u8 KEY_Scan(keystate * ckstate);  		//����ɨ�躯��	



void KEY_Init(void);
//y=1,ʱ��3����ɫ����
u8 KEY_Scan11(void);
u8 KEY_Scan41(void);
u8 KEY_Scan71(void);
//y=2��ʱ��2����ɫ����
u8 KEY_Scan32(void);
u8 KEY_Scan52(void);
//y=3��ʱ��2����ɫ����
u8 KEY_Scan23(void);
u8 KEY_Scan63(void);
//y=4��ʱ��2����ɫ����
u8 KEY_Scan34(void);
u8 KEY_Scan54(void);
//y=5��ʱ��3����ɫ����
u8 KEY_Scan15(void);
u8 KEY_Scan45(void);
u8 KEY_Scan75(void);
//����ɨ�谴��
u8 KEY_Scan10(void);
u8 KEY_Scan20(void);
u8 KEY_Scan30(void);
u8 KEY_Scan40(void);
u8 KEY_Scan50(void);
u8 KEY_Scan60(void);
u8 KEY_Scan70(void);

u8 KEY_Scan01(void);
u8 KEY_Scan02(void);
u8 KEY_Scan03(void);
u8 KEY_Scan04(void);
u8 KEY_Scan05(void);
//CMD���������ж����������
u8 KEY_Scan73(void);//����home������
u8 KEY_Scan00(void);//��Ĭ�ϳ���
u8 KEY_Scan26(void);//��ʼ����
u8 KEY_Scan07(void);
u8 KEY_Scan17(void);
u8 KEY_Scan27(void);
u8 KEY_Scan37(void);
u8 KEY_Scan47(void);
u8 KEY_Scan57(void);
u8 KEY_Scan67(void);
u8 KEY_Scan77(void);

//������������������y��1��7����Ҫʱ�ٶ���
u8 KEY_Scan21(void);
u8 KEY_Scan31(void);
u8 KEY_Scan51(void);
u8 KEY_Scan61(void);




#endif
