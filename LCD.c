#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Inerface.h"
#include "LCD_Private.h"

#define F_CPU 8000000
#include <util/delay.h>

//u8 Index;
static u8 LINE,CELL;


int string_len(c8*str)
{
	u8 i=0;
	for(i=0;str[i]!='\0';i++);
	return i;

}
void string_reverse(c8*str)
{
	s8 i=0,j,temp;
	u8 len=string_len(str);
	for(i=0,j=(len-1);i<=j;i++,j--)
	{
		temp=str[i];
		str[i]=str[j];
		str[j]=temp;

	}
}

void decimal_to_string(s32 n,c8*str)
{
	u8 rem,m=0;
	s32 n2=n,n3=n;
	u8 i=0;
	
	if(n2<0)
	{
		n2=n2*-1;
	}
	n3=n2;
	while(n3)
	{
		m++;
		n3=n3/10;
		
	}
	if(n2==0)
	{
		str[i]='0';
		i++;
	}
	while(n2)
	{
		rem=n2%10;
		str[i]=rem+'0';
		i++;
		n2=n2/10;
		//printf("rem=%d   n2=%d\n",rem,n2);

	}
	if(n<0)
	{
		str[i]='-';
		i++;
	}
	str[i]=0;
	string_reverse(str);

}
void decimal_to_hex(u8 num,u8*str)
{
	u8 i=0,rem;
	u8 n2=num;
	str[0]='0';
	str[1]='x';
	i=2;
	while(n2)
	{
		
	  rem=n2%16;
		
		if(rem>=0&&rem<=9)
		{
			rem=rem+'0';
		}
		else if(rem==10)
		{
			rem='A';
		}
		else if(rem==11)
		{
			rem='B';
		}
		else if(rem==12)
		{
			rem='C';
		}
		else if(rem==13)
		{
			rem='D';
		}
		else if(rem==14)
		{
			rem='E';
		}
		else if(rem==15)
		{
			rem='F';
		}
		
		str[i++]=rem;
		n2=n2/16;
		
	}
	str[i]=0;
	string_reverse(str+2);
	
	
}

void decimal_to_binary(u8 num,c8*str)
{
	u8 j=0,flag=0;
	s8 i=7;
	str[0]='0';
	str[1]='b';
	j=2;
	for(i=7;i>=0;i--)
	{
		if(READ_BIT(num,i)==1)
		{
			str[j++]='1';
			
			flag=1;
		}
		else if(READ_BIT(num,i)==0&&flag==1)
		{
			str[j++]='0';
		}
	}
	str[j]=0;
	
}

#if LCD_MODE==_8_BIT

static void Write_Ins(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	
}

static void Write_Data(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	
}


void LCD_Init(void)
{
	_delay_ms(50);
	Write_Ins(FUNCTION_SET);
	_delay_ms(1);
	Write_Ins(DISPLAY_ON);
	_delay_ms(1);
	Write_Ins(CLR_SCREEN);
	_delay_ms(2);
	Write_Ins(ENTRY_MODE);
	
	
	
}
	

#else

static void Write_Ins(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	
	
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	
	
	
}

static void Write_Data(u8 data)
{
	DIO_WritePin(RS,HIGH);
	
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	
}


void LCD_Init(void)
{
	_delay_ms(50);
	Write_Ins(0x02);
	Write_Ins(FUNCTION_SET);
	_delay_ms(1);
	Write_Ins(DISPLAY_ON);
	_delay_ms(1);
	Write_Ins(CLR_SCREEN);
	_delay_ms(2);
	Write_Ins(ENTRY_MODE);
	
	
	
}
#endif

void LCD_Clear(void)
{
	Write_Ins(CLR_SCREEN);
	LINE=0;
	CELL=0;
	_delay_ms(2);
}
void LCD_ClearPart(u8 line,u8 cell,u8 N_of_cells)
{
	LCD_GoTO(line,cell);
	for (u8 i=0;i<N_of_cells;i++)
	{
		LCD_WriteChar(' ');
	}
	
}

void LCD_GoTO(u8 line,u8 cell)
{
	LINE=line;
	CELL=cell;
	//SET_BIT(cell,7);
	cell=cell+0x80;
	if(line==0)
	{
		Write_Ins(cell);
	}
	else
	{
		cell=cell+0x40;
		Write_Ins(cell);
		
	}
	//Index=cell;
	//CLR_BIT(Index,7);
}
void LCD_WriteChar(u8 ch)
{

  Write_Data(ch);
  CELL++;
  if(LINE==0&&CELL==16)
  {
	  LINE=1;
	  CELL=0;
	  LCD_GoTO(1,0);
	  
  }
  
  /*Index++;
  if(Index==0x10)
  {
	  Index=0x40;
	  LCD_GoTO(1,0);
  }
  */
	
}


void LCD_WriteString(u8*str)
{
	int i=0;
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}
void LCD_WriteNum(s64 num)
{
	u8 str[32];
	s8 i=0,rem,j;
	if(num<0)
	{
		LCD_WriteChar('-');
		num=num*-1;
	}
	else if(num==0)
	{
		LCD_WriteChar('0');
	}
	while(num)
	{
		rem=(num%10)+'0';
		
		str[i++]=rem;
		num=num/10;
		
	}
	str[i]=0;
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
	
}
/*
void LCD_WriteNum(s32 num)
{  
	u8 str[32];
	
	int i=0;
	decimal_to_string(num,str);
     for(i=0;str[i];i++)
	 {
		 LCD_WriteChar(str[i]);
	 }
	 
}
*/
/*
void LCD_WriteBinary(u8 num)
{
	u8 str[32];
	int i=0;
	decimal_to_binary(num,str);
	 for(i=0;str[i];i++)
	 {
		 LCD_WriteChar(str[i]);
	 }
	
}
*/
void LCD_WriteBinary(u8 num)
{
	u8 j=0,flag=0;
	s8 i=7;
	//LCD_WriteString("0b");
	for(i=7;i>=0;i--)
	{
		if(READ_BIT(num,i)==1)
		{
			LCD_WriteChar('1');
			
			flag=1;
		}
		else if(READ_BIT(num,i)==0&&flag==1)
		{
			LCD_WriteChar('0');
		}
	}

	
	
}

void LCD_WriteHex(u32 num)
{
	u32 rem;
	u8 flag=0;
	//LCD_WriteString("0x");
	for(u8 i=0;i<8;i++)
	{
		rem=num/268435456;
		
		if(rem>=0&&rem<=9)
		{
			rem=rem+'0';
			
		}
		else
		{
			rem=rem-10+'A';
		}
		
		if(rem!='0')
		{
			LCD_WriteChar(rem);
			flag=1;
			
		}
		else if(rem=='0'&&flag==1)
		{
			LCD_WriteChar(rem);
		}
		
		num=num<<4;
		
		
	}
	
}
/*
void LCD_WriteHex(u8 num)
{
	u8 str[32];
	int i=0;
	decimal_to_hex(num,str);
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}
*/
/*
void LCD_Write_4D(u16 num)
{
	u8 str[32];
	s8 rem,i=0,j;
	for(i=0;i<4;i++)
	{
		rem=num%10+'0';
		str[i]=rem;
		num=num/10;
		
	}
	for(i=3;i>=0;i--)
	{
		LCD_WriteChar(str[i]);
			
	}
}
*/
void LCD_Write_4D(u16 num)
{
	u8 str[32];
	s8 rem,i=0,j;
	str[i++]=(num%10000)/1000+'0';
	str[i++]=(num%1000)/100+'0';
	str[i++]=(num%100)/10+'0';
	str[i++]=(num%10)/1+'0';
	str[i]=0;
	LCD_WriteString(str);
}

void LCD_CustomChar(u8 address,u8*pattern)
{
	u8 i=0;
	address=0x40+address*8;
	Write_Ins(address);
	for(i=0;i<8;i++)
	{
		
		Write_Data(pattern[i]);
		
	}
	LCD_GoTO(0,0);
	
}
void LCD_WriteStringGoTo(u8 line,u8 cell,u8*str)
{
	LCD_GoTO(line,cell);
	LCD_WriteString(str);
	
}
void LCD_name(u8 line,u8 cell)
{
	LCD_GoTO(line,cell+4);
	LCD_WriteChar(0);
	LCD_GoTO(line,cell+3);
	LCD_WriteChar(1);
	LCD_GoTO(line,cell+2);
	LCD_WriteChar(2);
	LCD_GoTO(line,cell+1);
	LCD_WriteChar(3);
	LCD_GoTO(line,cell);
	LCD_WriteChar(4);
}
void LCD_Man(void)
{
	LCD_GoTO(0,0);
	LCD_WriteChar(0);
	LCD_GoTO(0,15);
	LCD_WriteChar(0);
	_delay_ms(300);
	
	for(u8 i=2;i<15;i++)
	{
		LCD_GoTO(0,i);
		LCD_WriteChar('>');
		_delay_ms(300);
		LCD_GoTO(0,i);
		LCD_WriteChar(' ');
		
		
	}
	LCD_GoTO(0,15);
	LCD_WriteChar(1);
	_delay_ms(300);
	LCD_Clear();
	LCD_GoTO(0,3);
	LCD_WriteString("GAME OVER");
	
	
	
	
}
void LCD_shift(c8*str)//hammer
{
	u8 len=string_len(str);
	s8 i=0,j=0;
	LCD_GoTO(0,0);
	for(i=len-1;i>=0;i--)//
	{
		LCD_GoTO(0,0);
		for(j=i;j<=len-1;j++)//4
		{
			LCD_WriteChar(str[j]);
		}
		_delay_ms(300);
		LCD_Clear();
		
	}
	for(i=2;i<=15;i++)
	{
		if(i<=(15-len))
		{
			LCD_GoTO(0,i);
			LCD_WriteString(str);
			_delay_ms(300);
			LCD_Clear();
			
		}
		else
		{
			LCD_GoTO(0,i);
			LCD_WriteString(str);
			LCD_GoTO(1,0);
			LCD_WriteString("                     ");
			_delay_ms(300);
			LCD_Clear();
			
		}
		
	}
	LCD_GoTO(1,0);
	for(i=len-1;i>=0;i--)//43
	{
		LCD_GoTO(1,0);
		for(j=i;j<=len-1;j++)//4
		{
			LCD_WriteChar(str[j]);
		}
		_delay_ms(300);
		LCD_Clear();
		LCD_GoTO(1,0);
		
	}
		
	for(i=2;i<=15;i++)
	{
		if(i<=(15-len))
		{
			LCD_GoTO(1,i);
			LCD_WriteString(str);
			_delay_ms(300);
			LCD_Clear();
			
		}
		else
		{
			LCD_GoTO(1,i);
			LCD_WriteString(str);
			LCD_GoTO(1,0);
			_delay_ms(300);
			LCD_Clear();
			
		}
		
	}
	
}
