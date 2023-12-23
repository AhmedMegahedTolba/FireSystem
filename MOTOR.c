#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Cfg.h"
#include "MOTOR_Privateh.h"



#define F_CPU 8000000
#include <util/delay.h>




void MOTOR_Stop(MOTOR_type m)
{
	
	
	DIO_WritePin(MOTOR_PinsStatusArr[m][IN1],LOW);
	DIO_WritePin(MOTOR_PinsStatusArr[m][IN2],LOW);
	DIO_WritePin(MOTOR_PinsStatusArr[m][EN],LOW);
	
}
/*

void MOTOR_Stop(MOTOR_type m)
{
	
	
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,LOW);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,LOW);
		break;
		
		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,LOW);
		break;
		
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,LOW);
		break;
		
	}
	
}
*/

void MOTOR_Cw(MOTOR_type m)
{
	
	
	
	DIO_WritePin(MOTOR_PinsStatusArr[m][IN1],HIGH);
	DIO_WritePin(MOTOR_PinsStatusArr[m][IN2],LOW);
	DIO_WritePin(MOTOR_PinsStatusArr[m][EN],HIGH);

	
}

/*
void MOTOR_Cw(MOTOR_type m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,HIGH);
		DIO_WritePin(M1_IN2,LOW);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,HIGH);
		DIO_WritePin(M2_IN2,LOW);
		break;
		
		case M3:
		DIO_WritePin(M3_IN1,HIGH);
		DIO_WritePin(M3_IN2,LOW);
		break;
		
		case M4:
		DIO_WritePin(M4_IN1,HIGH);
		DIO_WritePin(M4_IN2,LOW);
		break;
		
	}
}
*/

void MOTOR_Ccw(MOTOR_type m)
{
	   
	DIO_WritePin(MOTOR_PinsStatusArr[m][IN1],LOW);
	DIO_WritePin(MOTOR_PinsStatusArr[m][IN2],HIGH);
	DIO_WritePin(MOTOR_PinsStatusArr[m][EN],HIGH);
	
}

/*
void MOTOR_Ccw(MOTOR_type m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,HIGH);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,HIGH);
		break;
		
		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,HIGH);
		break;
		
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,HIGH);
		break;
		
	}
}
*/

void MOTOR_Init(void)
{
	MOTOR_Stop(M1);
// 	MOTOR_Stop(M2);
// 	MOTOR_Stop(M3);
// 	MOTOR_Stop(M4);
	//_delay_ms(5000);
	
}
/*
void MOTOR_Init(void)
{
	MOTOR_State_type state=MOTOR_INIT_STATE;
	switch(state)
	{
		case STOP:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,LOW);
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,LOW);
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,LOW);
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,LOW);
		break;
		
		case CW:
		break;
		
		case CCW:
		break;
	}
	_delay_ms(5000);
	
}
*/
