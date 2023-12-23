


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define ROWS  4
#define  COLS 4

#define FIRST_OUTPUT    PINB4


#define FIRST_INPUT     PIND2

#define NO_KEY 'T'

#if KEYPAD_PRG

const u8 KEYPADArr[ROWS][COLS]={
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'},
	
};

#endif



#endif /* KEYPAD_CFG_H_ */