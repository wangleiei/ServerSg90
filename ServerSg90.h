#ifndef __SERVERSG90_H
#define __SERVERSG90_H	

#include <stdint.h>	

typedef struct SERVERSG90_BASE
{
	void(*serversg90_pwm_l)(void);
	void(*serversg90_pwm_h)(void);
	float angle;

	uint32_t count_us;
	uint16_t serversg90_h_timeus;

	uint32_t period_count;
}SERVERSG90_BASE;

void ServerSg90_Inter(SERVERSG90_BASE *base,uint16_t interupt_frequs);
void ServerSg90_Init(SERVERSG90_BASE *base,void(*serversg90_pwm_l)(void),void(*serversg90_pwm_h)(void));
void ServerSg90Control(SERVERSG90_BASE *base,float angle);
#endif