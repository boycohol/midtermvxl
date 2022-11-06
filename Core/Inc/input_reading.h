/*
 * input_reading.h
 *
 *  Created on: Nov 5, 2022
 *      Author: Admin
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

void buttons_reading();		// set value for flags
int isButtonPressed(int numButton);		// check if button press or not
int isButtonPressedMore1s(int numButton);	// check if button press more than 1s
int isButtonPressed3s(int numButton);		// check if button press 3s
int isTimeout();							// check if time out 10s
void generateStartValue();

#endif /* INC_INPUT_READING_H_ */
