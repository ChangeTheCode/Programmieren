/*
 * testFunc.c
 *
 *  Created on: 14 Jan 2016
 *      Author: offic
 */
#include <msp430.h>
#include "testFunc.h"
#include "interrupt.h"


void setupTestFuncs () {

	// preabmle
	WDTCTL = WDTPW + WDTHOLD; 		// stop using the watchdog

	// LED initial setup
	P1DIR |= RED_LED + GREEN_LED;	// ENABLE GREEN AND RED LED
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT &= ~RED_LED;		// Red off

	P1DIR &= ~BUTTON; // set bit3 as a Input
	P1OUT |= BUTTON;
	P1REN |= BUTTON;
	P1IE |= BUTTON; //set interrupt enable
	P1IES |= BUTTON; // set interrupt high-> low transition

	P1IFG &= ~BUTTON; // clear interrupt flag
}

// delay a couple of secs
void delay (int secsToWait) {
	int i, j, k;
	for (i = 1; i <= secsToWait; i++) {
		// 16 000 000 cycles is a second
		for (j = 1; j <= 16; j++)
			for (k = 1; k <= 50; k++)
				__delay_cycles (1000); // delay program execution for 1000 cycles
	}

	// MCU clock MCLK = 16MHz --> instruction cycle time = 62.5ns (= 1/MCLK)
	// Required delay = 5s
    //
	// --> 5s/62.5ns = 80.000.000
	// --> 1s 		 = 16.000.000

}

// red for 2 secs
void functionGreen () {
	timeThread = 0;

	while(1){

		if(timeThread <= REPEATTIMEFUNC){
			// everything off
				P1OUT ^= ~GREEN_LED;	// toggle Green
				P1OUT &= ~RED_LED;		// Red off
		}

	}
}
// green for 2 secs
void functionRed () {
	timeThread = 0;

		// switch red on
	P1OUT |= GREEN_LED;		// Green on
	P1OUT &= ~RED_LED;		// Red off

	//wait
	int i;

	while(timeThread <= REPEATTIMEFUNC){
		i = timeThread;
	}

	// everything off
	P1OUT &= ~GREEN_LED;	// Green off
	P1OUT &= ~RED_LED;		// Red off

}
