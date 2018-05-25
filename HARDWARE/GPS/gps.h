#ifndef __GPS_H
#define __GPS_H	 
#include "sys.h" 




void GPS_Init(void);
int GPS_Test(void);
void IR_gpsInit(void);
void SR_gpsInit(void);
int IR_Front(void);
int IR_Behind(void);
int IR_Left(void);
int IR_Right(void);


#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 		PAin(0)		//PA0 

#define KEY0_PRES 	1	//KEY0按
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define WKUP_PRES   4	//KEY_UP按下(即WK_UP)


				    
#endif
