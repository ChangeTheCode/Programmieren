/*
 * semaphor.c
 *
 *  Created on: 21.01.2016
 *      Author: Jim
 */

#include <msp430.h>
#include "scheduler.h"


int counter = 1;
int queueIndex = 0;
int threadQueue[10];


void semaphor_P(int id) {  // expand waiting queue
	__disable_interrupt();
	counter --;
	if (counter == 0) { // add thread in waiting, after all ressources are off
		threadQueue[queueIndex ++] = currThread; // currthread is threadID

		scheduler_suspend(currThread);  //set thread.state to blocked
		scheduler_runNextThread();
	}
	__enable_interrupt();
}
void semaphor_V() { // kürze die waiting queue  // nur eine 1 ressource
	__disable_interrupt();
	counter++;
	if (counter <= 0) {
		scheduler_continueThread(queue_dequeue());
	}
	__enable_interrupt();
}

int queue_dequeue(){
	int tmp = 0; int i;
	tmp	= threadQueue[0]; // always the next starting thread
	for (i = 1; i< 10; i++){ // start at 1, because the first element will always removed
		threadQueue[i-1 ]= threadQueue[i];
	}
	return tmp;
}

