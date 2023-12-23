#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Sensors_Interface.h"
#include "LCD_Inerface.h"
#include "KEYPAD_Interface.h"
#include "MOTOR_Interface.h"
#include "TEMP_Filter_Interface.h"
#include "FireSystem_Cfg.h"
#include "FireSystem_Inerface.h"

#define F_CPU 8000000
#include <util/delay.h>
//u16 temp_arr[NUMBER_OF_ELES_IN_FILTER]={0};
u16 temp,pressure,MainTemp;
u16 sum_temp=0;
static  key=NO_KEY;
u8 alarm_flag=0,f_start=0,i=0,f1=0,f2=0,j=0,filter_flag=0,PassFlag=0;
system_Status_type status=FINE;
u8 Pass1[20]="1567";
u8 pass2[20]={0};
int string_cmpare(char*str1,char*str2)
{
	int i=0;
	char c1,c2,flag=1;
	for(i=0;(str1[i]&&flag==1)||(str2[i]&&flag==1);i++)
	{
		c1=str1[i];
		c2=str2[i];
		if(c1>='A'&&c1<='Z')
		{
			c1=c1-'A'+'a';
		}
		if(c2>='A'&&c2<='Z')
		{
			c2=c2-'A'+'a';
		}
		if(c1!=c2)
		{
			flag=0;
		}
	}
	return flag;
}
void FireSystem_Init(void)
{
	MOTOR_Stop(M1);
	DIO_WritePin(FINE_LED,HIGH);
	DIO_WritePin(FIRE_LED,LOW);
	DIO_WritePin(MPX4115_ON,LOW);
	LCD_WriteStringGoTo(0,5,"Fine");
	temp=Temp_Read();
	MainTemp=temp;
	LCD_GoTO(1,0);
	LCD_WriteNum(MainTemp/10);
	LCD_WriteChar('.');
	LCD_WriteNum(MainTemp%10);
	LCD_WriteString("    ");
	LCD_Clear();
	
	
}

void FireSystem_Runnable(void)
{
	//MainTemp=Temp_Read();
	MainTemp=FILTER_GetFilteredTemp();

	
	pressure=Pressure_Read();
	key=KEYPAD_GetKey();
	pressure=((pressure*100)+575)/1150;
	
	if(PassFlag==1)
	{
		if(f1==0)
		{
			LCD_Clear();
			LCD_WriteStringGoTo(0,0,"please enter 1");
			LCD_WriteStringGoTo(1,0,"to close motor");
			f1=1;
		}
		
		
		if(key!=NO_KEY)
		{
			
			
			
			if(f_start==0&&key=='1')
			{
				LCD_Clear();
				LCD_WriteStringGoTo(0,0,"Enter Pass");
				f_start=1;
				key=NO_KEY;
				LCD_GoTO(1,0);
			}
			if(f_start==1)
			{
				if(key>='0'&&key<='9')
				{
					LCD_WriteChar(key);
					pass2[i++]=key;
					
				}
				else if(key=='=')
				{
					if(string_cmpare(Pass1,pass2)==1)
					{
						LCD_Clear();
						LCD_WriteStringGoTo(0,2,"right pass");
						_delay_ms(2000);
						LCD_Clear();
						alarm_flag=0;
						PassFlag=0;
						f1=0;
						f_start=0;
						status=FINE;
					}
					else
					{
						LCD_Clear();
						LCD_WriteStringGoTo(0,2,"wrong entry");
						_delay_ms(2000);
						f1=0;
						f_start=0;
						i=0;
					}
					
				}
				
				
			}
			
			

			
			
		}
		
		
	}
	else
	{
		
		if(MainTemp<450)
		{
			if(alarm_flag==1)
			{
				PassFlag=1;
			}
			else
			{
				status=FINE;
			}
			
			
			
			
			
		}
		else if (MainTemp>=500&&pressure<45&&alarm_flag==0)
		{
			status=HEAT;
			
			
			
			
		}
		else if(MainTemp>=500&&pressure>=50)
		{
			status=FIRE;
			alarm_flag=1;
		}
		
		if(status==FINE)
		{
			LCD_WriteStringGoTo(0,5,"Fine");
			
			LCD_GoTO(1,0);
			LCD_WriteNum(MainTemp/10);
			LCD_WriteChar('.');
			LCD_WriteNum(MainTemp%10);
			LCD_WriteString("  ");
			DIO_WritePin(FINE_LED,HIGH);
			DIO_WritePin(HEAT_LED,LOW);
			DIO_WritePin(FIRE_LED,LOW);
			MOTOR_Stop(M1);
			DIO_WritePin(MPX4115_ON,LOW);
			LCD_ClearPart(1,8,5);
			
		}
		else if(status==HEAT)
		{
			DIO_WritePin(MPX4115_ON,HIGH);
			LCD_WriteStringGoTo(0,5,"HEAT  ");
			LCD_GoTO(1,8);
			LCD_WriteNum(pressure);
			LCD_WriteString("%  ");
			DIO_WritePin(HEAT_LED,HIGH);
			DIO_WritePin(FINE_LED,LOW);
			DIO_WritePin(FIRE_LED,LOW);
			MOTOR_Stop(M1);
			LCD_GoTO(1,0);
			LCD_WriteNum(MainTemp/10);
			LCD_WriteChar('.');
			LCD_WriteNum(MainTemp%10);
			LCD_WriteString("  ");
			
		}
		else if(status==FIRE)
		{
			LCD_WriteStringGoTo(0,5,"FIRE  ");
			LCD_GoTO(1,0);
			LCD_WriteNum(MainTemp/10);
			LCD_WriteChar('.');
			LCD_WriteNum(MainTemp%10);
			LCD_WriteString("  ");
			LCD_GoTO(1,8);
			LCD_WriteNum(pressure);
			LCD_WriteString("%  ");
			DIO_WritePin(HEAT_LED,LOW);
			DIO_WritePin(FIRE_LED,HIGH);
			MOTOR_Cw(M1);
			
			
		}
	}
	
	
	
	
// 	if(alarm_flag==1)
// 	{
// 		pressure=Pressure_Read();
// 		pressure=((pressure*100)+575)/1150;
// 		LCD_GoTO(1,8);
// 		LCD_WriteNum(pressure);
// 		LCD_WriteString("  ");
// 		if(pressure>50)
// 		{
// 			
// 			LCD_WriteStringGoTo(0,5,"FIRE  ");
// 			DIO_WritePin(HEAT,LOW);
// 			DIO_WritePin(FIRE,HIGH);
// 			MOTOR_Cw(M1);
// 			
// 		}
// 		
// 	}

	
}