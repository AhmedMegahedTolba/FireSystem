

#ifndef TEMP_FILTER_INTERFACE_H_
#define TEMP_FILTER_INTERFACE_H_


void FILTER_init(void);
void FILTER_Runnable(void);
u16 FILTER_GetFilteredTemp(void);
u16 FILTER_GetUnFilteredTemp(void);


#endif /* TEMP_FILTER_INTERFACE_H_ */