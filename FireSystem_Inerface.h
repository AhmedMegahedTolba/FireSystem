/*
 * FireSystem_Inerface.h
 *
 * Created: 6/30/2023 10:58:58 AM
 *  Author: HIFINE
 */ 


#ifndef FIRESYSTEM_INERFACE_H_
#define FIRESYSTEM_INERFACE_H_

void FireSystem_Init(void);
void FireSystem_Runnable(void);
typedef enum{
	FINE,
	HEAT,
	FIRE
	
	}system_Status_type;



#endif /* FIRESYSTEM_INERFACE_H_ */