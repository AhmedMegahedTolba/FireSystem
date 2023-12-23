

#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_
/**********************************PIN_COFIG***************************/
/*
#define M1_IN1  PIND0 
#define M1_IN2  PIND1
#define M1_EN  PIND4// if not put on 5v

#define M2_IN1  PIND2
#define M2_IN2  PIND3
#define M2_EN  PIND5// if not put on 5v

#define M3_IN1  PINC0
#define M3_IN2  PINC1
#define M3_EN  PINC4// if not put on 5v

#define M4_IN1  PINC2
#define M4_IN2  PINC3
#define M4_EN  PINC5// if not put on 5v

#define MOTOR_INIT_STATE STOP

#define  MOTOR_TOTAL_PINS 12
*/
#define  MOTOR_TOTAL_PINS 12
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
#define MOTORS_NUMBERS 4

#define M1_IN1  PINC0
#define M1_IN2  PINC1
#define M1_EN   PINC2// if not put on 5v

#define M2_IN1  PIND2
#define M2_IN2  PIND3
#define M2_EN  PIND5// if not put on 5v

#define M3_IN1  PINC0
#define M3_IN2  PINC1
#define M3_EN  PINC4// if not put on 5v

#define M4_IN1  PINC2
#define M4_IN2  PINC3
#define M4_EN  PINC5// if not put on 5v


#endif /* MOTOR_CFG_H_ */