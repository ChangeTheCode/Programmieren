/*
 * scheduler.h
 *
 *  Created on: 14 Jan 2016
 *      Author: offic
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <msp430.h>
#include <inttypes.h>
#include <setjmp.h>

// the states my thread can be in
typedef enum {
	RUNNING,
	WAITING,
	BLOCKED,
	FREE
} states_t;

// what info am I keeping per thread
typedef struct _thread {
	states_t state;
	void (*funcPtr)();
	jmp_buf context;
	//int threadId;

} thread_t;

#define MAX_THREADS 5
#define ERROR_THREAD -1
#define NO_THREAD -2

extern thread_t threadList [MAX_THREADS];
extern int currThread;
extern int semThreadID;

int scheduler_startThread (void (*funcPtr)());
void scheduler_runNextThread ();
void scheduler_killThread (int threadNo);

void scheduler_suspend(int threadID);
void scheduler_continueThread(int toStartedThreadId);


#endif /* SCHEDULER_H_ */
