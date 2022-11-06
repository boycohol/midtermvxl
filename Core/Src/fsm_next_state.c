/*
 * fsm_next_state.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Admin
 */
#include <fsm_state.h>
#include "input_reading.h"
#include "global.h"

void fsm_simple_buttons_run() {
	if(isButtonPressed3s(1)||isButtonPressed3s(2)){
		status = PRESS_3S;
	}
	if(isButtonPressedMore1s(1)||isButtonPressedMore1s(2)){
		status=PRESS_MORE_1S;
	}
}

