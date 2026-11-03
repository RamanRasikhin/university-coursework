#include <8051.h>
#define FALSE 0
#define TRUE 1
#define BLINK_VALUE 300
#define TH_0 253
#define LP_0 1200
#define HOURS 2
#define MINUTES 1
#define SECONDS 0
#define ENTER 0b000001
#define ESC 0b000010
#define RIGHT 0b000100
#define UP 0b001000
#define DOWN 0b010000
#define LEFT 0b100000

unsigned char HH, MM, SS;
__sbit __at (0x96) SEG_OFF;
__bit BLINK;
__bit EDIT_MODE;
__xdata unsigned char * CSDS = (__xdata unsigned char *) 0xFF30;
__xdata unsigned char * CSDB = (__xdata unsigned char *) 0xFF38;
__code unsigned char WZOR[10] = {
    0b0111111, 0b0000110, 0b1011011,
    0b1001111, 0b1100110, 0b1101101,
    0b1111101, 0b0000111, 0b1111111,
    0b1101111
};
unsigned char SEG, SEG_IDX;
unsigned char ARR[6] = { 0, 0, 0, 0, 0, 0};

unsigned int BLINK_COUNTER;
__bit T0_FLAG;
__bit SEC_FLAG;
unsigned int LP;

__sbit __at (0xB5) KBD;
unsigned char PREV_TIME[3] = { 0, 0, 0};
unsigned char UNIT;
unsigned char MUX_KEY;
unsigned char PREV_SEG;


void t0_int(void) __interrupt(1) {
    TH0 = TH_0;
    T0_FLAG = TRUE;
    ++LP;
    ++BLINK_COUNTER;
    if(LP >= LP_0) {
        SEC_FLAG = TRUE;
    }
    if(BLINK_COUNTER >= BLINK_VALUE) {
        BLINK_COUNTER -= BLINK_VALUE;
        BLINK = !BLINK;
    }
}

void timer_reset() {
    LP = 0;
    TH0 = TH_0;
    TL0 = 0;
    SEC_FLAG = FALSE;
}

void timer_init() {
    TMOD = 0b00100001;
    TH0 = TH_0;
    ET0 = TRUE;
    EA = TRUE;
    TR0 = TRUE;
    SEC_FLAG = FALSE;
    T0_FLAG = FALSE;
    LP = 0;
    BLINK_COUNTER = 0;
}



void update_seconds() {
    ARR[0] = SS%10;
    ARR[1] = (SS/10)%10;
}

void update_minutes() {
    ARR[2] = MM%10;
    ARR[3] = (MM/10)%10;
}

void update_hours() {
    ARR[4] = HH%10;
    ARR[5] = (HH/10)%10;
}



void check_seconds() {
    if(SS == 60) {
        SS = 0;
        if(EDIT_MODE == FALSE){
            ++MM;
        }

    }
    else if(SS > 60) {
        SS = 59;
    }
}

void check_minutes() {
    if(MM == 60) {
        MM = 0;
        if(EDIT_MODE == FALSE){
            ++HH;
        }
    }
    else if(MM > 60) {
        MM = 59;
    }
}

void check_hours() {
    if(HH == 24) {
        HH = 0;
    }
    else if(HH > 24) {
        HH = 23;
    }
}

void check_time() {
    check_seconds();
    check_minutes();
    check_hours();
}
void update_time() {

    update_seconds();
    update_minutes();
    update_hours();
}
void handle_time() {
    if(EDIT_MODE == FALSE){
        ++SS;
    }
    check_time();
    update_time();
}

void clock_init() {
    HH = 23;
    MM = 59;
    SS = 35;
    EDIT_MODE = FALSE;
    update_time();
}

void save_previous_time(){
    PREV_TIME[0] = SS;
    PREV_TIME[1] = MM;
    PREV_TIME[2] = HH;
}

void get_previous_time(){
    SS = PREV_TIME[0];
    MM = PREV_TIME[1];
    HH = PREV_TIME[2];
}

void SEG7_refresh() {
    SEG_OFF = TRUE;
    if(EDIT_MODE && BLINK && (SEG_IDX/2) != UNIT){
		*CSDB = 0;
	}
	else{
		*CSDB = WZOR[ARR[SEG_IDX]];
	}
    *CSDS = SEG;
    SEG_OFF = FALSE;
    ++SEG_IDX;
    PREV_SEG = SEG;
    SEG <<= 1;
    if(SEG > 0b00100000) {
        SEG = 0b00000001;
        SEG_IDX = 0;
        return;
    }
}

void SEG7_init() {
    SEG = 0b00000001;
    SEG_IDX = 0;
    SEG7_refresh();
}

void mux_kbd(){
    MUX_KEY = PREV_SEG;
    if(MUX_KEY == RIGHT){
		if(EDIT_MODE == FALSE){
			EDIT_MODE = TRUE;
			save_previous_time();
		}
		else{
			--UNIT;
			if(UNIT>2){
				UNIT = 2;
			}
		}
	}
	else if(MUX_KEY == LEFT){
		if(EDIT_MODE == FALSE){
			EDIT_MODE = TRUE;
			save_previous_time();
		}
		else{
			++UNIT;
			if(UNIT>2){
				UNIT = 0;
			}
		}
	}
	else if(EDIT_MODE == TRUE){
		if(MUX_KEY == UP){
			if(UNIT == SECONDS){
				++SS;
				check_seconds();
				update_seconds();
			}
			else if(UNIT == MINUTES){
				++MM;
				check_minutes();
				update_minutes();
			}
			else if(UNIT == HOURS){
				++HH;
				check_hours();
				update_hours();
			}
		}
		else if(MUX_KEY == DOWN){
			if(UNIT == SECONDS){
				--SS;
				check_seconds();
				update_seconds();
			}
			else if(UNIT == MINUTES){
				--MM;
				check_minutes();
				update_minutes();
			}
			else if(UNIT == HOURS){
				--HH;
				check_hours();
				update_hours();
			}
		}
		else if(MUX_KEY == ENTER){
			EDIT_MODE = FALSE;
			timer_reset();
			UNIT = 0;
		}
		else if(MUX_KEY == ESC){
			get_previous_time();
			update_time();
			EDIT_MODE = FALSE;
			timer_reset();
			UNIT = 0;
		}
	}
}

void mux_init(){
   	UNIT = SECONDS;
   	MUX_KEY = 0;
   	PREV_SEG = 0;
}


void init() {
    timer_init();
    clock_init();
    mux_init();
    SEG7_init();
}

void main() {
    init();
    while(1) {
        if(SEC_FLAG) {
            SEC_FLAG = FALSE;
            LP -= LP_0;
            handle_time();
        }
        if(T0_FLAG){
		T0_FLAG = FALSE;
		SEG7_refresh();
		if(KBD && MUX_KEY == 0){
		       mux_kbd();
		}
		else if(MUX_KEY == PREV_SEG && !KBD){
  		     MUX_KEY = 0;
		}
        }
    }
}




