#include "hcsr04.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//
//		SR_F
//SR_L		 SR_R
//		SR_B
//
//��ʱ��5ͨ��1���벶������,     PA0
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<3;   	//TIM5 ʱ��ʹ�� 
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	GPIO_Set(GPIOA,PIN0,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,����
	GPIO_AF_Set(GPIOA,0,2);	//PA0,AF2
	  
 	TIM5->ARR=arr;  		//�趨�������Զ���װֵ   
	TIM5->PSC=psc;  		//Ԥ��Ƶ�� 

	TIM5->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
 	TIM5->CCMR1|=0<<4; 		//IC1F=0000 ���������˲��� ���˲�
 	TIM5->CCMR1|=0<<10; 	//IC1PS=00 	���������Ƶ,����Ƶ 

	TIM5->CCER|=0<<1; 		//CC1P=0	�����ز���
	TIM5->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����

	TIM5->EGR=1<<0;			//������Ʋ��������¼�,ʹд��PSC��ֵ������Ч,���򽫻�Ҫ�ȵ���ʱ������Ż���Ч!
	TIM5->DIER|=1<<1;   	//������1�ж�				
	TIM5->DIER|=1<<0;   	//��������ж�	
	TIM5->CR1|=0x01;    	//ʹ�ܶ�ʱ��2
	MY_NVIC_Init(2,0,TIM5_IRQn,2);//��ռ2�������ȼ�0����2	   
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM5->SR;
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(tsr&0X01)//���
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			    TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM5->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM5->CR1&=~(1<<0)		;    	//ʹ�ܶ�ʱ��2
	 			TIM5->CNT=0;					//���������
	 			TIM5->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز���
				TIM5->CR1|=0x01;    			//ʹ�ܶ�ʱ��2
			}		    
		}			     	    					   
 	}
	TIM5->SR=0;//����жϱ�־λ   
}
////arr���Զ���װֵ(TIM2,TIM5��32λ��!!,TIM4,TIM3:16)
//PB6
void TIM4_CH1_Cap_Init(u16 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<2;   	//TIM4 ʱ��ʹ�� 
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,����
	GPIO_AF_Set(GPIOB,6,2);	//PB6,AF2
	  
 	TIM4->ARR=arr;  		//�趨�������Զ���װֵ   
	TIM4->PSC=psc;  		//Ԥ��Ƶ�� 

	TIM4->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
 	TIM4->CCMR1|=0<<4; 		//IC1F=0000 ���������˲��� ���˲�
 	TIM4->CCMR1|=0<<10; 	//IC1PS=00 	���������Ƶ,����Ƶ 

	TIM4->CCER|=0<<1; 		//CC1P=0	�����ز���
	TIM4->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����

	TIM4->EGR=1<<0;			//������Ʋ��������¼�,ʹд��PSC��ֵ������Ч,���򽫻�Ҫ�ȵ���ʱ������Ż���Ч!
	TIM4->DIER|=1<<1;   	//������1�ж�				
	TIM4->DIER|=1<<0;   	//��������ж�	
	TIM4->CR1|=0x01;    	//ʹ�ܶ�ʱ��4
	MY_NVIC_Init(2,0,TIM4_IRQn,2);//��ռ2�������ȼ�0����2	   
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM4CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ(TIM3/TIM4��16λ)
//��ʱ��4�жϷ������	 
void TIM4_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM4->SR;
 	if((TIM4CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(tsr&0X01)//���
		{	     
			if(TIM4CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM4CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//����1���������¼�
		{	
			if(TIM4CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM4CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			    TIM4CH1_CAPTURE_VAL=TIM4->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM4->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH1_CAPTURE_STA=0;			//���
				TIM4CH1_CAPTURE_VAL=0;
				TIM4CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM4->CR1&=~(1<<0)		;    	//ʹ�ܶ�ʱ��4
	 			TIM4->CNT=0;					//���������
	 			TIM4->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز���
				TIM4->CR1|=0x01;    			//ʹ�ܶ�ʱ��4 
			}		    
		}			     	    					   
 	}
	TIM4->SR=0;//����жϱ�־λ   
}

///PB4---TIM3_CH1
void TIM3_CH1_Cap_Init(u16 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<1;   	//TIM3 ʱ��ʹ�� 
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN4,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,����
	GPIO_AF_Set(GPIOB,4,2);	//PB4,AF2
	  
 	TIM3->ARR=arr;  		//�趨�������Զ���װֵ   
	TIM3->PSC=psc;  		//Ԥ��Ƶ�� 

	TIM3->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
 	TIM3->CCMR1|=0<<4; 		//IC1F=0000 ���������˲��� ���˲�
 	TIM3->CCMR1|=0<<10; 	//IC1PS=00 	���������Ƶ,����Ƶ 

	TIM3->CCER|=0<<1; 		//CC1P=0	�����ز���
	TIM3->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����

	TIM3->EGR=1<<0;			//������Ʋ��������¼�,ʹд��PSC��ֵ������Ч,���򽫻�Ҫ�ȵ���ʱ������Ż���Ч!
	TIM3->DIER|=1<<1;   	//������1�ж�				
	TIM3->DIER|=1<<0;   	//��������ж�	
	TIM3->CR1|=0x01;    	//ʹ�ܶ�ʱ��2
	MY_NVIC_Init(2,0,TIM3_IRQn,2);//��ռ2�������ȼ�0����2	   
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM3CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM3CH1_CAPTURE_VAL;	//���벶��ֵ(TIM3/TIM4��16λ)
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM3->SR;
 	if((TIM3CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(tsr&0X01)//���
		{	     
			if(TIM3CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM3CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//����1���������¼�
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			    TIM3CH1_CAPTURE_VAL=TIM3->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM3->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH1_CAPTURE_STA=0;			//���
				TIM3CH1_CAPTURE_VAL=0;
				TIM3CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM3->CR1&=~(1<<0)		;    	//ʹ�ܶ�ʱ��3
	 			TIM3->CNT=0;					//���������
	 			TIM3->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز���
				TIM3->CR1|=0x01;    			//ʹ�ܶ�ʱ��3
			}		    
		}			     	    					   
 	}
	TIM3->SR=0;//����жϱ�־λ   
}
void TIM2_CH1_Cap_Init(u32 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<0;   	//TIM2 ʱ��ʹ�� 
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,����
	GPIO_AF_Set(GPIOA,5,1);	//PA5,AF1
	  
 	TIM2->ARR=arr;  		//�趨�������Զ���װֵ   
	TIM2->PSC=psc;  		//Ԥ��Ƶ�� 

	TIM2->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
 	TIM2->CCMR1|=0<<4; 		//IC1F=0000 ���������˲��� ���˲�
 	TIM2->CCMR1|=0<<10; 	//IC1PS=00 	���������Ƶ,����Ƶ 

	TIM2->CCER|=0<<1; 		//CC1P=0	�����ز���
	TIM2->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����

	TIM2->EGR=1<<0;			//������Ʋ��������¼�,ʹд��PSC��ֵ������Ч,���򽫻�Ҫ�ȵ���ʱ������Ż���Ч!
	TIM2->DIER|=1<<1;   	//������1�ж�				
	TIM2->DIER|=1<<0;   	//��������ж�	
	TIM2->CR1|=0x01;    	//ʹ�ܶ�ʱ��2
	MY_NVIC_Init(2,0,TIM2_IRQn,2);//��ռ2�������ȼ�0����2	   
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������	 
void TIM2_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM2->SR;
 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(tsr&0X01)//���
		{	     
			if(TIM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM2CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//����1���������¼�
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			    TIM2CH1_CAPTURE_VAL=TIM2->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM2->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH1_CAPTURE_STA=0;			//���
				TIM2CH1_CAPTURE_VAL=0;
				TIM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM2->CR1&=~(1<<0)		;    	//ʹ�ܶ�ʱ��2
	 			TIM2->CNT=0;					//���������
	 			TIM2->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز���
				TIM2->CR1|=0x01;    			//ʹ�ܶ�ʱ��2
			}		    
		}			     	    					   
 	}
	TIM2->SR=0;//����жϱ�־λ   
}


void HCSR04_Init(void){
	RCC->AHB1ENR|=1<<5;//ʹ��PORTFʱ�� 
	
	//��װ��SR_F:tim5-PA0,en-PF3
	TIM5_CH1_Cap_Init(0XFFFFFFFF,84-1);//��1Mhz��Ƶ�ʼ��� 
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF3����
	
	//��װ��SR_L:tim4-PB6,en-PF4
	TIM4_CH1_Cap_Init(0XFFFF,84-1);
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF4����
	
	//��װ��SR_R:tim3-PB4,en-PF5
	TIM3_CH1_Cap_Init(0XFFFF,84-1);
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF5����
	
	//��װ��SR_B:tim2-PA5,en-PF6
	TIM2_CH1_Cap_Init(0XFFFFFFFF,84-1);
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF6����
	
}

int SR_Front(void){
		long long temp=0;  
		u8 dis;
	
		PFout(3)=0;
		delay_ms(10);
		PFout(3)=1;
		delay_us(10);
		PFout(3)=0;
		while(!(TIM5CH1_CAPTURE_STA&0X80));
 
		temp=TIM5CH1_CAPTURE_STA&0X3F; 
		temp*=0XFFFFFFFF;		 		//���ʱ���ܺ�
		temp+=TIM5CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
		printf("HIGH:%lld us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
		dis=temp*340*100/2000000;		//cm
		printf("DIS:%d cm\r\n",dis);
		TIM5CH1_CAPTURE_STA=0;			//������һ�β���
		return dis;
}
int SR_Behind(void){
		long long temp=0;  
		u8 dis;
	
		PFout(6)=0;
		delay_ms(10);
		PFout(6)=1;
		delay_us(10);
		PFout(6)=0;
	
		while(!(TIM2CH1_CAPTURE_STA&0X80));
 
		temp=TIM2CH1_CAPTURE_STA&0X3F; 
		temp*=0XFFFFFFFF;		 		//���ʱ���ܺ�
		temp+=TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
		printf("HIGH:%lld us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
		dis=temp*340*100/2000000;		//cm
		printf("DIS:%d cm\r\n",dis);
		TIM5CH1_CAPTURE_STA=0;			//������һ�β���
		return dis;
}
int SR_Left(void);
int SR_Right(void);








