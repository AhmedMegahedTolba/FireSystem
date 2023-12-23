


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum{
	STOP,
	CW,
	CCW,
	
}MOTOR_State_type;

typedef enum{
	MLOW,
	MHIGH
	
}MOTOR_PinVoltage_type;

typedef enum{
	M1,
	M2,
	M3,
	M4,
	
}MOTOR_type;
/*
typedef struct{
	DIO_Pin_type IN1_Pin;
	MOTOR_PinVoltage_type IN1_Val;
	DIO_Pin_type IN2_Pin;
	MOTOR_PinVoltage_type IN2_Val;
	DIO_Pin_type EN_Pin;
	MOTOR_PinVoltage_type EN_Val;
	
}MOTOR_Pins_type;
*/


void MOTOR_Init(void);
void MOTOR_Stop(MOTOR_type m);
void MOTOR_Cw(MOTOR_type m);
void MOTOR_Ccw(MOTOR_type m);
/**** speed 0:100 percentage***/
void MOTOR_Speed(MOTOR_type m,u8 speed);



#endif /* MOTOR_INTERFACE_H_ */