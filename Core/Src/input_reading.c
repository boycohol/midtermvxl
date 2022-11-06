/*
 * input_reading.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Admin
 */
#include "input_reading.h"
#include "main.h"
#include "global.h"

#define NUMBER_OF_BUTTON 			 3
#define DURATION_FOR_AUTO_INCREASING 100
#define DURATION_FOR_PRESSED		 300
#define DURATION_FOR_WAITING		 1000

//the buffer that the final result is stored after debouncing
static GPIO_PinState buttonBuffer[NUMBER_OF_BUTTON];

//two buffers for debouncing
static GPIO_PinState debounceButtonBuffer0[NUMBER_OF_BUTTON];
static GPIO_PinState debounceButtonBuffer1[NUMBER_OF_BUTTON];
static GPIO_PinState debounceButtonBuffer2[NUMBER_OF_BUTTON];

static GPIO_PinState debounceButtonBuffer3[NUMBER_OF_BUTTON];

//flag time-out 10s
static int flagTimeout;
//flag for a button pressed and release
static int flagButtonPressed[NUMBER_OF_BUTTON];
//flag for a button pressed more than 3s
static int flagButtonPressed3s[NUMBER_OF_BUTTON];
//flag for a button pressed more than 1s
static int flagButtonPressedMore1s[NUMBER_OF_BUTTON];
//Time for presskey
static int TimeForPressKey[NUMBER_OF_BUTTON];
//Time for presskey more 1s
static int TimeForPressKeyMore1s[NUMBER_OF_BUTTON];
//Time for waiting
static int TimeForWaiting[NUMBER_OF_BUTTON];

int isButtonPressed(int numButton) {
	if (numButton > NUMBER_OF_BUTTON) {
		return 0;
	}
	if (flagButtonPressed[numButton]) {
		flagButtonPressed[numButton] = 0;
		return 1;
	}
	return 0;
}

int isButtonPressed3s(int numButton) {
	if (numButton > NUMBER_OF_BUTTON) {
		return 0;
	}
	if (flagButtonPressed3s[numButton]) {
		flagButtonPressed3s[numButton] = 0;
		return 1;
	}
	return 0;
}

int isButtonPressedMore1s(int numButton) {
	if (numButton > NUMBER_OF_BUTTON) {
		return 0;
	}
	if (flagButtonPressedMore1s[numButton]) {
		flagButtonPressedMore1s[numButton] = 0;
		return 1;
	}
	return 0;
}

int isTimeout() {
	if (flagTimeout) {
		flagTimeout = 0;
		return 1;
	}
	return 0;
}

void generateStartValue() {
	for (int i = 0; i < NUMBER_OF_BUTTON; i++) {
		debounceButtonBuffer0[i] = debounceButtonBuffer1[i] =
				debounceButtonBuffer2[i] = debounceButtonBuffer3[i] = 0;
		flagButtonPressed[i] = flagButtonPressed3s[i] =
				flagButtonPressedMore1s[i] = flagTimeout = 0;
		TimeForPressKey[i] = DURATION_FOR_PRESSED;
		TimeForWaiting[i] = DURATION_FOR_WAITING;
		TimeForPressKeyMore1s[i] = DURATION_FOR_AUTO_INCREASING;
		status = 0;
	}
}

void buttons_reading() {
	for (int i = 0; i < NUMBER_OF_BUTTON; i++) {
		debounceButtonBuffer0[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = debounceButtonBuffer2[i];
		if (i == 0) {
			debounceButtonBuffer2[i] = HAL_GPIO_ReadPin(Button1_GPIO_Port,
			Button1_Pin);
		}
		if (i == 1) {
			debounceButtonBuffer2[i] = HAL_GPIO_ReadPin(Button2_GPIO_Port,
			Button2_Pin);
		}
		if (i == 2) {
			debounceButtonBuffer2[i] = HAL_GPIO_ReadPin(Button3_GPIO_Port,
			Button3_Pin);
		}
		if ((debounceButtonBuffer0[i] == debounceButtonBuffer1[i])
				&& (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])) {
			buttonBuffer[i] = debounceButtonBuffer2[i];
			if (debounceButtonBuffer3[i] != buttonBuffer[i]) {
				debounceButtonBuffer3[i] = buttonBuffer[i];
				if (buttonBuffer[i] == PRESSED_STATE) {
					flagButtonPressed[i] = 1;
					TimeForPressKey[i] = DURATION_FOR_PRESSED;
					TimeForPressKeyMore1s[i] = DURATION_FOR_AUTO_INCREASING;
					//todo, push and release
				} else {
					flagButtonPressed[i] = 0;
					flagButtonPressed3s[i]=0;
					flagButtonPressedMore1s[i]=0;
					TimeForWaiting[i]--;
					if (TimeForWaiting[i] == 0) {
						//if time-out 10s
						TimeForWaiting[i] = DURATION_FOR_WAITING;
						flagTimeout = 1;
					}
				}
			} else {
				if (flagButtonPressed3s[i] == 0) {
					TimeForPressKey[i]--;
					if (TimeForPressKey[i] == 0) {
						if (buttonBuffer[i] == PRESSED_STATE) {
							//if pressed
							flagButtonPressed3s[i] = 1;

						} else {
							flagButtonPressed3s[i] = 0;
						}
					}
				} else {
					TimeForPressKeyMore1s[i]--;
					if (TimeForPressKeyMore1s[i] == 0) {
						if (buttonBuffer[i] == PRESSED_STATE) {
							flagButtonPressedMore1s[i] = 1;
							TimeForPressKeyMore1s[i] =
							DURATION_FOR_AUTO_INCREASING;
						} else {
							flagButtonPressedMore1s[i] = 0;
						}
					}
				}
			}

		}
	}
}

