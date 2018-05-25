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
//定时器5通道1输入捕获配置,     PA0
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<3;   	//TIM5 时钟使能 
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	GPIO_Set(GPIOA,PIN0,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,下拉
	GPIO_AF_Set(GPIOA,0,2);	//PA0,AF2
	  
 	TIM5->ARR=arr;  		//设定计数器自动重装值   
	TIM5->PSC=psc;  		//预分频器 

	TIM5->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
 	TIM5->CCMR1|=0<<4; 		//IC1F=0000 配置输入滤波器 不滤波
 	TIM5->CCMR1|=0<<10; 	//IC1PS=00 	配置输入分频,不分频 

	TIM5->CCER|=0<<1; 		//CC1P=0	上升沿捕获
	TIM5->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中

	TIM5->EGR=1<<0;			//软件控制产生更新事件,使写入PSC的值立即生效,否则将会要等到定时器溢出才会生效!
	TIM5->DIER|=1<<1;   	//允许捕获1中断				
	TIM5->DIER|=1<<0;   	//允许更新中断	
	TIM5->CR1|=0x01;    	//使能定时器2
	MY_NVIC_Init(2,0,TIM5_IRQn,2);//抢占2，子优先级0，组2	   
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM5->SR;
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(tsr&0X01)//溢出
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			    TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//获取当前的捕获值.
	 			TIM5->CCER&=~(1<<1);			//CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM5->CR1&=~(1<<0)		;    	//使能定时器2
	 			TIM5->CNT=0;					//计数器清空
	 			TIM5->CCER|=1<<1; 				//CC1P=1 设置为下降沿捕获
				TIM5->CR1|=0x01;    			//使能定时器2
			}		    
		}			     	    					   
 	}
	TIM5->SR=0;//清除中断标志位   
}
////arr：自动重装值(TIM2,TIM5是32位的!!,TIM4,TIM3:16)
//PB6
void TIM4_CH1_Cap_Init(u16 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<2;   	//TIM4 时钟使能 
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,下拉
	GPIO_AF_Set(GPIOB,6,2);	//PB6,AF2
	  
 	TIM4->ARR=arr;  		//设定计数器自动重装值   
	TIM4->PSC=psc;  		//预分频器 

	TIM4->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
 	TIM4->CCMR1|=0<<4; 		//IC1F=0000 配置输入滤波器 不滤波
 	TIM4->CCMR1|=0<<10; 	//IC1PS=00 	配置输入分频,不分频 

	TIM4->CCER|=0<<1; 		//CC1P=0	上升沿捕获
	TIM4->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中

	TIM4->EGR=1<<0;			//软件控制产生更新事件,使写入PSC的值立即生效,否则将会要等到定时器溢出才会生效!
	TIM4->DIER|=1<<1;   	//允许捕获1中断				
	TIM4->DIER|=1<<0;   	//允许更新中断	
	TIM4->CR1|=0x01;    	//使能定时器4
	MY_NVIC_Init(2,0,TIM4_IRQn,2);//抢占2，子优先级0，组2	   
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM4CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值(TIM3/TIM4是16位)
//定时器4中断服务程序	 
void TIM4_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM4->SR;
 	if((TIM4CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(tsr&0X01)//溢出
		{	     
			if(TIM4CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM4CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//捕获1发生捕获事件
		{	
			if(TIM4CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM4CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			    TIM4CH1_CAPTURE_VAL=TIM4->CCR1;	//获取当前的捕获值.
	 			TIM4->CCER&=~(1<<1);			//CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM4CH1_CAPTURE_STA=0;			//清空
				TIM4CH1_CAPTURE_VAL=0;
				TIM4CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM4->CR1&=~(1<<0)		;    	//使能定时器4
	 			TIM4->CNT=0;					//计数器清空
	 			TIM4->CCER|=1<<1; 				//CC1P=1 设置为下降沿捕获
				TIM4->CR1|=0x01;    			//使能定时器4 
			}		    
		}			     	    					   
 	}
	TIM4->SR=0;//清除中断标志位   
}

///PB4---TIM3_CH1
void TIM3_CH1_Cap_Init(u16 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<1;   	//TIM3 时钟使能 
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN4,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,下拉
	GPIO_AF_Set(GPIOB,4,2);	//PB4,AF2
	  
 	TIM3->ARR=arr;  		//设定计数器自动重装值   
	TIM3->PSC=psc;  		//预分频器 

	TIM3->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
 	TIM3->CCMR1|=0<<4; 		//IC1F=0000 配置输入滤波器 不滤波
 	TIM3->CCMR1|=0<<10; 	//IC1PS=00 	配置输入分频,不分频 

	TIM3->CCER|=0<<1; 		//CC1P=0	上升沿捕获
	TIM3->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中

	TIM3->EGR=1<<0;			//软件控制产生更新事件,使写入PSC的值立即生效,否则将会要等到定时器溢出才会生效!
	TIM3->DIER|=1<<1;   	//允许捕获1中断				
	TIM3->DIER|=1<<0;   	//允许更新中断	
	TIM3->CR1|=0x01;    	//使能定时器2
	MY_NVIC_Init(2,0,TIM3_IRQn,2);//抢占2，子优先级0，组2	   
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM3CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM3CH1_CAPTURE_VAL;	//输入捕获值(TIM3/TIM4是16位)
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM3->SR;
 	if((TIM3CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(tsr&0X01)//溢出
		{	     
			if(TIM3CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM3CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//捕获1发生捕获事件
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			    TIM3CH1_CAPTURE_VAL=TIM3->CCR1;	//获取当前的捕获值.
	 			TIM3->CCER&=~(1<<1);			//CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH1_CAPTURE_STA=0;			//清空
				TIM3CH1_CAPTURE_VAL=0;
				TIM3CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM3->CR1&=~(1<<0)		;    	//使能定时器3
	 			TIM3->CNT=0;					//计数器清空
	 			TIM3->CCER|=1<<1; 				//CC1P=1 设置为下降沿捕获
				TIM3->CR1|=0x01;    			//使能定时器3
			}		    
		}			     	    					   
 	}
	TIM3->SR=0;//清除中断标志位   
}
void TIM2_CH1_Cap_Init(u32 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<0;   	//TIM2 时钟使能 
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//复用功能,下拉
	GPIO_AF_Set(GPIOA,5,1);	//PA5,AF1
	  
 	TIM2->ARR=arr;  		//设定计数器自动重装值   
	TIM2->PSC=psc;  		//预分频器 

	TIM2->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
 	TIM2->CCMR1|=0<<4; 		//IC1F=0000 配置输入滤波器 不滤波
 	TIM2->CCMR1|=0<<10; 	//IC1PS=00 	配置输入分频,不分频 

	TIM2->CCER|=0<<1; 		//CC1P=0	上升沿捕获
	TIM2->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中

	TIM2->EGR=1<<0;			//软件控制产生更新事件,使写入PSC的值立即生效,否则将会要等到定时器溢出才会生效!
	TIM2->DIER|=1<<1;   	//允许捕获1中断				
	TIM2->DIER|=1<<0;   	//允许更新中断	
	TIM2->CR1|=0x01;    	//使能定时器2
	MY_NVIC_Init(2,0,TIM2_IRQn,2);//抢占2，子优先级0，组2	   
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM2CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM2CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器5中断服务程序	 
void TIM2_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM2->SR;
 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(tsr&0X01)//溢出
		{	     
			if(TIM2CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM2CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//捕获1发生捕获事件
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			    TIM2CH1_CAPTURE_VAL=TIM2->CCR1;	//获取当前的捕获值.
	 			TIM2->CCER&=~(1<<1);			//CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH1_CAPTURE_STA=0;			//清空
				TIM2CH1_CAPTURE_VAL=0;
				TIM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM2->CR1&=~(1<<0)		;    	//使能定时器2
	 			TIM2->CNT=0;					//计数器清空
	 			TIM2->CCER|=1<<1; 				//CC1P=1 设置为下降沿捕获
				TIM2->CR1|=0x01;    			//使能定时器2
			}		    
		}			     	    					   
 	}
	TIM2->SR=0;//清除中断标志位   
}


void HCSR04_Init(void){
	RCC->AHB1ENR|=1<<5;//使能PORTF时钟 
	
	//包装成SR_F:tim5-PA0,en-PF3
	TIM5_CH1_Cap_Init(0XFFFFFFFF,84-1);//以1Mhz的频率计数 
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF3设置
	
	//包装成SR_L:tim4-PB6,en-PF4
	TIM4_CH1_Cap_Init(0XFFFF,84-1);
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF4设置
	
	//包装成SR_R:tim3-PB4,en-PF5
	TIM3_CH1_Cap_Init(0XFFFF,84-1);
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF5设置
	
	//包装成SR_B:tim2-PA5,en-PF6
	TIM2_CH1_Cap_Init(0XFFFFFFFF,84-1);
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PF6设置
	
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
		temp*=0XFFFFFFFF;		 		//溢出时间总和
		temp+=TIM5CH1_CAPTURE_VAL;		//得到总的高电平时间
		printf("HIGH:%lld us\r\n",temp);//打印总的高点平时间
		dis=temp*340*100/2000000;		//cm
		printf("DIS:%d cm\r\n",dis);
		TIM5CH1_CAPTURE_STA=0;			//开启下一次捕获
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
		temp*=0XFFFFFFFF;		 		//溢出时间总和
		temp+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
		printf("HIGH:%lld us\r\n",temp);//打印总的高点平时间
		dis=temp*340*100/2000000;		//cm
		printf("DIS:%d cm\r\n",dis);
		TIM5CH1_CAPTURE_STA=0;			//开启下一次捕获
		return dis;
}
int SR_Left(void);
int SR_Right(void);








