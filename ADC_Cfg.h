/*
 * ADC_Cfg.h
 *
 * Created: 6/23/2023 2:46:12 PM
 *  Author: HIFINE
 */ 


#ifndef ADC_CFG_H_
#define ADC_CFG_H_

#define  ADC_VREF VREF_AVCC  /*****
                               VREF_AREF
							   VREF_AVCC
							   VREF_2_56V
							   
							   ***////
                                
#define ADC_PRESCALAR   ADC_SCALER_64 /**** 
										   ADC_SCALER_2
										   ADC_SCALER_4
										   ADC_SCALER_8
										   ADC_SCALER_16
										   ADC_SCALER_32
										   ADC_SCALER_64
										   ADC_SCALER_128
                           
						   
										   ****////
                            

#define  VREF  5000 //to calculate Vin ->vref-> mv


#endif /* ADC_CFG_H_ */