#ifndef __ENGINES_H
#define __ENGINES_H	 
#include "sys.h" 
#include "pwm10111314.h"
#include "gps.h"
#include "pwm912.h"
#define FULL_SPEED 328

void ENGINES_Init(void);
int ENGINES_Test(void);

void ENGINES_stop(void);
void ENGINE1_cor(void);
void ENGINE2_cor(void);
void ENGINE3_cor(void);
void ENGINE4_cor(void);
void ENGINE1_res(void);
void ENGINE2_res(void);
void ENGINE3_res(void);
void ENGINE4_res(void);


void head_front(void);
void head_behind(void);
void head_left(void);
void head_right(void);
void clock_wise(void);
void anti_clock(void);
void clock_wise_right(void);
void clock_wise_left(void);
void anti_clock_front(void);
void anti_clock_behind(void);

void clock_wise_90(void);
void anti_clock_90(void);
void head_front_right(void);
void head_front_left(void);
void head_behind_right(void);
void head_behind_left(void);

int gof(void);
int gof_error(void);
int gof_error2(void);
int gob(void);
int gob_error(void);
int gob_error2(void);
int gol(void);
int gol_error(void);
int gol_error2(void);
int gor(void);
int gor_error(void);
int gor_error2(void);

void go_delta_r_error(u8 dx);
void go_delta_r_error2(u8 dx);
void go_delta_r(u8 dx);			//相对距离行走函数

void go_delta_f_error(u8 dy);
void go_delta_f_error2(u8 dy);
void go_delta_f(u8 dy);

void go_delta_b_error(u8 dy);
void go_delta_b_error2(u8 dy);
void go_delta_b(u8 dy);

void go_delta_l_error(u8 dx);
void go_delta_l_error2(u8 dx);
void go_delta_l(u8 dx);			//相对距离行走函数

void gox(u8 dx);				//绝对距离行走函数
void goy(u8 dy);
void go_delta(u8 dx, u8 dy);  //相对

#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 		PAin(0)		//PA0 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define WKUP_PRES   4	//KEY_UP按下(即WK_UP)

				    
#endif
