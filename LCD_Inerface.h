


#ifndef LCD_INERFACE_H_
#define LCD_INERFACE_H_

void LCD_Init(void);
void LCD_WriteChar(u8 ch);
void LCD_WriteString(u8*str);
void LCD_WriteNum(s64 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u32 num);
void LCD_Write_4D(u16);


void LCD_GoTO(u8 line,u8 cell);  /**  lines -> 0:1
                                      cell  -> 0:15
								 
								   ***/
void LCD_Clear(void);
void LCD_WriteStringGoTo(u8 line,u8 cell,u8*str);
void LCD_ClearPart(u8 line,u8 cell,u8 N_of_cells);





#endif /* LCD_INERFACE_H_ */