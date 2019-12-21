#include "ServerSg90.h"
/**********************************************************************************************************
*	函 数 名: void ServerSg90_Inter(SERVERSG90_BASE *base,uint16_t interupt_frequs)
*	功能说明: 该函数放入间隔调用的函数内(pin 模式下，pwm模式下不用)，调用周期最好是10us
*	传    参: interupt_frequs调用间隔时间（单位us）
*	返 回 值: 
*   说    明: 
*     PWM周期信号20ms；正脉冲为2ms，负脉冲为20ms-2ms=18ms
*     控制的角度精度是可以达到180/1024度约0.18度
	  0.5ms-------------0度；   2.5% 
	  1.0ms------------45度；   5.0% 
	  1.5ms------------90度；   7.5%
	  2.0ms-----------135度；  10.0%
	  2.5ms-----------180度；  12.5% 
*********************************************************************************************************/
void ServerSg90_Inter(SERVERSG90_BASE *base,uint16_t interupt_frequs){
	base->count_us += interupt_frequs;
	if(base->count_us >= 20000){
		base->count_us = 0;

		base->period_count++;
	}

	if(base->count_us <= base->serversg90_h_timeus ){
		base->serversg90_pwm_h();
	}else{
		base->serversg90_pwm_l();
	}
}
/**********************************************************************************************************
*	函 数 名: void ServerSg90_Init(SERVERSG90_BASE *base,void(*serversg90_pwm_l)(void),void(*serversg90_pwm_h)(void))
*	功能说明: 控制接口初始化，确定控制接口，
*	传    参: serversg90_pwm_l 将pwm管脚拉低的函数
			  serversg90_pwm_h 将pwm管脚拉高的函数
*	返 回 值: 
*   说    明: 
*********************************************************************************************************/
void ServerSg90_Init(SERVERSG90_BASE *base,void(*serversg90_pwm_l)(void),void(*serversg90_pwm_h)(void)){
	base->serversg90_pwm_h = serversg90_pwm_h;
	base->serversg90_pwm_l = serversg90_pwm_l;

	base->angle = 0;	
	base->period_count = 0;
	
	base->serversg90_h_timeus = 500;
	base->pwm_mode	= PIN_MODE;
}
//增加直接使用pwm模式的方式
void ServerSg90_InitPwmMode(SERVERSG90_BASE *base,void(*serversg90_pwm)(float pwm_pulse)){
	base->serversg90_pwm_h = serversg90_pwm_h;
	base->serversg90_pwm_l = serversg90_pwm_l;

	base->pwm_mode	= PWM_MODE;
	base->serversg90_pwm = serversg90_pwm;
	
	base->angle = 0;	
	ServerSg90Control(base,0);
}
/**********************************************************************************************************
*	函 数 名: void ServerSg90Control(SERVERSG90_BASE *base,float angle){
*	功能说明: 控制角度，angle的范围是0.00度-180.00度
*	传    参: 
*	返 回 值: 
*   说    明:  控制的角度精度是可以达到180/1024度约0.18度
*********************************************************************************************************/
void ServerSg90Control(SERVERSG90_BASE *base,float angle){
	if((angle >= 0.00) && (angle <= 180.00)){
		base->angle = angle;	
		if(base->pwm_mode == PWM_MODE){
			base->serversg90_pwm(angle/18+2.5);
		}else{
			base->serversg90_h_timeus = 100.0/9.0*base->angle + 500.0;
		}
	}
}
