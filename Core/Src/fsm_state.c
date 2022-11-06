/*
 * fsm_midterm.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Admin
 */

#include <fsm_state.h>
#include "global.h"
#include "main.h"
#include "input_reading.h"
#include "7segment.h"


void fsm_run() {
	switch (status) {
	case INIT:
		if (isButtonPressed(0)) {
			count = 0;
			display7SEG(count);
		} else if (isButtonPressed(1)) {
			count++;
			if(count>9) count=0;
			display7SEG(count);
		} else if (isButtonPressed(2)) {
			count--;
			if(count<0) count=9;
			display7SEG(count);
		} else {
			break;
		}
		break;
	case PRESS_3S:
		if (isButtonPressed3s(1)) {
			count++;
			if(count>9) count=0;
			display7SEG(count);
		} else if (isButtonPressed3s(2)) {
			count--;
			if(count<0) count=9;
			display7SEG(count);
		}
		break;
	case PRESS_MORE_1S:
		if (isButtonPressedMore1s(1)) {
			count++;
			if(count>9) count=0;
			display7SEG(count);
		}
		if (isButtonPressedMore1s(2)) {
			count--;
			if(count<0) count=9;
			display7SEG(count);
		}
		break;
	case TIME_OUT:
		break;
	default:
		break;
	}
}
