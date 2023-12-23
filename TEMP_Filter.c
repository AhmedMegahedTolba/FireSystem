#include "StdTypes.h" 
#include "LCD_Inerface.h"
#include "Sensors_Interface.h"
#include "TEMP_Filter_Cfg.h"
#include "TEMP_Filter_Interface.h"


#define F_CPU 8000000
#include <util/delay.h>

u16 temp_arr[NUMBER_OF_ELES_IN_FILTER]={0};
static  u8  i=0,j=0,k=0;
u16 MeanTemp=0,temp=0;
u32 SumTemp=0;
static  filter_flag=0; 
void FILTER_init(void)
{
	
	temp=Temp_Read();
	MeanTemp=temp;
	//LCD_Clear();
	
}
/* not more than 250us */
void FILTER_Runnable(void)
{
	temp=Temp_Read();
	
	
	if(j<NUMBER_OF_ELES_IN_FILTER)
	{
		
		temp_arr[j]=temp;
		
		SumTemp=SumTemp+temp_arr[j];
		
		if(filter_flag==1)
		{
			j=NUMBER_OF_ELES_IN_FILTER-1;
		}
		
		if(j==NUMBER_OF_ELES_IN_FILTER-1)
		{
			MeanTemp=(SumTemp+(NUMBER_OF_ELES_IN_FILTER/2))/NUMBER_OF_ELES_IN_FILTER;
			SumTemp=SumTemp-temp_arr[k];
			j=k;
			k++;
			if(k==NUMBER_OF_ELES_IN_FILTER)
			{
				k=0;
			}
			filter_flag=1;
// 			LCD_WriteNum(SumTemp);
// 			LCD_WriteString(" ");
// 			_delay_ms(500);
			
						
		}
		else
		{
			j++;

		}
	}
	

	
	
}

u16 FILTER_GetFilteredTemp(void)
{
	return MeanTemp;
	
}

u16 FILTER_GetUnFilteredTemp(void)
{
	return temp;
}
