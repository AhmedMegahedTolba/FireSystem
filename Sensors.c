#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Cfg.h"
#include "Sensors_Interface.h"


u16 Temp_Read(void)
{
	/* relation between temp and volt ->vref= 5v *////

	u16 volt=ADC_VoltRead(LM35_CH);
	//u16 temp=((volt*1)+5)/10;// C
	u16 temp=((volt*10)+5)/10;// c*10 (Temp ->volt)
	
	
	/*
	u16 adc=ADC_Read(LM35_CH);
	//u16 temp=((adc*(u32)150)+512)/1024;//c (Temp ->adc)
	u16 temp=((adc*(u32)150*10)+512)/1024;//c*10 (Temp ->adc)
	*/
	
	/* relation between temp and adc ->vref= 5? *////
	//temp=((adc*(u32)1500)+512)/308;//c (Temp ->adc)//vref 5v
	return temp;
}
u16 Pressure_Read(void)
{
	u16 volt=ADC_VoltRead(MPX4115_CH);
	u16 pressure=Interpolation(268,4770,150,1150,volt);
	return pressure ;
}
/* use it with any sensor need interpolation *///
s16 Interpolation(s16 x1,s16 x2,s16 y1,s16 y2,s16 x)
{
	u16 y;
	s16 xdiff=x2-x1;
	s16 ydiff=y2-y1;
	
	y=(((((((s32)ydiff*(x-x1)))+.5*xdiff)/xdiff))+y1);
	return y;
}

