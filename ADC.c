#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Cfg.h"
#include "ADC_Interface.h"

#define F_CPU 8000000
#include <util/delay.h>

static  ADC_BusyFlag;

void ADC_Init(void)
{
	/* Vref  *///
	ADC_VoltRef_type i=ADC_VREF;
	WRITE_BIT(ADMUX,REFS1,VrefArr[i][0]);
	WRITE_BIT(ADMUX,REFS0,VrefArr[i][1]);
	
// 	switch(vref)
// 	{
// 		case VREF_AREF:
// 		CLR_BIT(ADMUX,REFS1);
// 		CLR_BIT(ADMUX,REFS0);
// 	}
// 	
	
	/* Prescalar  */
	
	ADCSRA= ADCSRA & 0XF8 | ADC_PRESCALAR ;
	
	
	
	/* ENABLE ADC */
	
	SET_BIT(ADCSRA,ADEN);
}

/* busy wait design */
u16 ADC_Read(ADC_Channel_type CH)
{
	
	/* Set channel in mux  *///
	ADMUX=ADMUX & 0xE0 |CH ;
	
	
	/* start conversion *///
	SET_BIT(ADCSRA,ADSC);
	
	/* wait ADC finishes *///
	while(READ_BIT(ADCSRA,ADSC)==1);
	
	
	/* get read */ 
	
	/*
	//ADLAR=0
	u16 adc=ADCL; //read low first
	adc=adc |(ADCH<<8) ;
	*/
	
	
	//ADLAR=1
	/*
	//10 bit resolution
	/*
	u16 adc=ADCL>>6;
	adc|=ADCH<<2;
	*/
	/*
	//8 bit resolution
	u16 adc=ADCH;
     */
	
	
	return ADC;//ADLAR=0
	
}

/* busy wait design   */

// void ADC_StartConversion(ADC_Channel_type CH)
// {
// 	/* Set channel in mux  *///
// 	ADMUX=ADMUX & 0xE0 |CH ;
// 	
// 	
// 	/* start conversion *///
// 	SET_BIT(ADCSRA,ADSC);
// }
// u16 ADC_GetRead(void)
// {
// 	/* wait ADC finishes *///
// 	while(READ_BIT(ADCSRA,ADSC)==1);
// 	return ADC;
// }

/* polling periodic check design   */

// void ADC_StartConversion(ADC_Channel_type CH)
// {
// 	if(ADC_BusyFlag==0)
// 	{
// 		/* Set channel in mux  *///
// 		ADMUX=ADMUX & 0xE0 |CH ;
// 
// 
// 		/* start conversion *///
// 		SET_BIT(ADCSRA,ADSC);
// 		ADC_BusyFlag=1;
// 	}
// }
// //
// u8 ADC_GetReadPeriodic(u16*pdata)
// {
// 	/* wait ADC finishes *///
// 	if(!(READ_BIT(ADCSRA,ADSC)))
// 	{
// 		*pdata=ADC;
// 		ADC_BusyFlag=0;
// 		//LCD_WriteChar('1');
// 		return 1;
// 	}
// 	else
// 	{
// 		return 0;
// 	}
// 	
// }

/* interrupt design   */

void ADC_StartConversion(ADC_Channel_type CH)
 {
	/* Set channel in mux  *///
 	ADMUX=ADMUX & 0xE0 |CH ;
 	/* start conversion *///
 	SET_BIT(ADCSRA,ADSC);
 }
 u16 ADC_GetReadNoblock(void)
 {
 	return ADC;
}
u16 ADC_VoltRead(ADC_Channel_type CH)
{
	u16 adc=ADC_Read(CH);
	u16 volt=0;
	volt=((VREF*(u32)adc)+512/* To increase accuracy we add half of the num that we divide by */)/1024;// divide by 1024 > max volt=4995  ->best
	//volt=((VREF*(u32)adc)+512/* To increase accuracy we add half of the num that we divide by */)/1023;// divide by 1024 > max volt=5000
	return volt;
}