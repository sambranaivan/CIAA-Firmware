#define RGB_RED_LED    	0x01
#define RGB_GREEN_LED   0x02
#define RGB_BLUE_LED    0x04
#define RED_LED    		0x08
#define YELLOW_LED      0x10
#define GREEN_LED       0x20
#define ORANGE_LED		RGB_RED_LED
#define WHITE_LED		(RGB_RED_LED|RGB_GREEN_LED|RGB_BLUE_LED)


#define LED_			RGB_BLUE_LED
#define ALL_LED			(RGB_BLUE_LED | YELLOW_LED | RED_LED | GREEN_LED)

#define BUTTON_1		0x01
#define BUTTON_2		0x02
#define BUTTON_3		0x04
#define BUTTON_4		0x08

#define BUTTON_			BUTTON_1
#define ANY_BUTTON		(BUTTON_1 | BUTTON_2 | BUTTON_3 | BUTTON_4)

