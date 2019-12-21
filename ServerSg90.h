#ifndef __SERVERSG90_H
#define __SERVERSG90_H	

#include <stdint.h>	
enum PWM_MODE
{
	PIN_MODE = 0,
	PWM_MODE = 1
};
typedef struct SERVERSG90_DEV
{
	void(*serversg90_pwm_l)(void);
	void(*serversg90_pwm_h)(void);
	enum PWM_MODE pwm_mode;
	float angle;

	uint32_t count_us;
	uint16_t serversg90_h_timeus;

	uint32_t period_count;
	void(*serversg90_pwm)(float pwm_pulse);
}SERVERSG90_DEV;

void ServerSg90_Inter(SERVERSG90_DEV *base,uint16_t interupt_frequs);
void ServerSg90_Init(SERVERSG90_DEV *base,void(*serversg90_pwm_l)(void),void(*serversg90_pwm_h)(void));
void ServerSg90_InitPwmMode(SERVERSG90_DEV *base,void(*serversg90_pwm)(float pwm_pulse));
void ServerSg90Control(SERVERSG90_DEV *base,float angle);
#endif