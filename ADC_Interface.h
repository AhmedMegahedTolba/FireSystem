


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

extern const u8 VrefArr[3][2];
typedef enum{
	VREF_AREF,
	VREF_AVCC,
	VREF_2_56V,

	}ADC_VoltRef_type;
	
typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
	
	}ADC_Prescalar_type;
	

typedef enum{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7,
	
	}ADC_Channel_type;
	
void ADC_Init(void);

/*  return mv  *///
u16 ADC_Read(ADC_Channel_type CH);

u16 ADC_VoltRead(ADC_Channel_type CH);
void ADC_StartConversion(ADC_Channel_type CH);
u16 ADC_GetRead(void);
u8 ADC_GetReadPeriodic(u16*pdata);
 u16 ADC_GetReadNoblock(void);



#endif /* ADC_INTERFACE_H_ */